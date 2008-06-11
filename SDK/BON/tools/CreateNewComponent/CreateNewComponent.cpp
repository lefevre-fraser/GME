// CreateNewComponent.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#define DIM(x) (sizeof(x)/sizeof((x)[0]))
#include "CreateNewComponent.h"
#include "CreateNewComponentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCreateNewComponentApp

BEGIN_MESSAGE_MAP(CCreateNewComponentApp, CWinApp)
	//{{AFX_MSG_MAP(CCreateNewComponentApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateNewComponentApp construction

CCreateNewComponentApp::CCreateNewComponentApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCreateNewComponentApp object

CCreateNewComponentApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCreateNewComponentApp initialization

int unzip(const char *, const char *);
int replaceSTLLibrary( const CString& strPath, const CString& strSTLPath );


struct {
	char fnam[50];
	bool ronly;
	bool needed;
} flist[50];

BOOL CCreateNewComponentApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CCreateNewComponentDlg dlg;
	m_pMainWnd = &dlg;
	dlg.m_radio = 3;
	char dirbuf[80];
	GetCurrentDirectory(DIM(dirbuf)-10, dirbuf);
	if(dirbuf[strlen(dirbuf)-1] != '\\') strcat(dirbuf, "\\");
	strcat(dirbuf, "Component");
	dlg.m_path = dirbuf;
	int nResponse = dlg.DoModal();
	
	{
		MSG msg;
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
	}


//	CCreateNewComponentDlg dlg2;
//	nResponse = dlg2.DoModal();
	if (nResponse == IDOK)	{
		{
				HRSRC hrsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_LISTFILE), "LISTFILE");
			    if(!hrsrc) AfxMessageBox("Cannot find filelist resource");
				HGLOBAL hres = LoadResource(NULL,hrsrc);
				LPVOID lr;
				if(!hres || !(lr = LockResource(hres))) AfxMessageBox("Cannot load filelist resource");
				char *p = (char *)lr;
				char *pend = p + SizeofResource(NULL,hrsrc);
				int i = 0;
				while(*p) {
					if(i == DIM(flist)) {
						AfxMessageBox("Error: filelist is too long");
						break;
					}					
					if(p >= pend) {
						AfxMessageBox("Error: filelist end of text hit");
						break;
					}
					char mask[8];
					int add;
					if(sscanf(p," %40s %6[-+] %n", flist[i].fnam,  mask, &add) != 2) {
						AfxMessageBox("Error scanning filelist");
						break;
					}
					flist[i].ronly = mask[0] == '+'; 
					if(mask[dlg.m_radio+1] == '+') i++;  // increment if we need it
					else flist[i].fnam[0] = '\0';
					p += add;
				}
		}

		HRSRC hrsrc = FindResource(NULL, MAKEINTRESOURCE(IDR_ZIPFILE), "ZIPFILE");
		if(!hrsrc) AfxMessageBox("Cannot find zipfile resource");
		HGLOBAL hres = LoadResource(NULL,hrsrc);
		LPVOID lr;
		if(!hres || !(lr = LockResource(hres))) AfxMessageBox("Cannot load zipfile resource");

		// VC6 is gone, now we support only VC7 and greater
		//if ( dlg.m_radio == 3 )
		//	AfxMessageBox( "Do not forget to set the directory of 3Party STL library if you use VC6!\nVC7 users never mind." );
	
		char memfilnam[40];
		sprintf(memfilnam, "(beg:0x%x,end:0x%x)", (char *)lr, (char *)lr+SizeofResource(NULL,hrsrc));
		if(unzip(memfilnam, dlg.m_path)) return -1;
		PROCESS_INFORMATION pinfo;
		STARTUPINFO suinfo;
		GetStartupInfo(&suinfo);
		CreateProcess("ConfigureComponent.exe", 
			NULL,    // same as cmdline
			NULL,    // sec descr
			NULL,	 // thread attrs
			FALSE,	 // do not inherit
			0,		 // default flags
			NULL,	 // orig environment
			NULL,    // use current directory
			&suinfo, // use my own startup info
			&pinfo	 // output info
			);
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


#include "direct.h"
#include <io.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../zlib113/unzip.h"

int unzip(const char *memfnam, const char *path) { 
	char ee[200];
	unzFile zipf = NULL;
	int filenum = 0;
	int s; 
	char filename[100];
	filename[0] = 0;
	int files = 0, dirs = 0, skips = 0;
	try {
		strncpy(filename,memfnam, DIM(filename));
	    zipf = unzOpen(memfnam);
		if(zipf == NULL) throw "Cannot open inputfile";

		strncpy(filename, path, DIM(filename));

		if(!SetCurrentDirectory(path)) {
			CreateDirectory(path,NULL);
		}
		if(!SetCurrentDirectory(path)) {
			throw("Cannot access target directory");
		}
		filename[0] = '\0';

		if(unzGoToFirstFile(zipf) != UNZ_OK) throw "Cannot locate first file";
		do {
			filenum++;
			unz_file_info file_info;
			s = unzGetCurrentFileInfo(zipf, &file_info, filename, sizeof(filename), NULL, 0, NULL, 0);
			if(s != UNZ_OK) throw "Error accessing file info";
			s = unzOpenCurrentFile(zipf);
			if(s != UNZ_OK) throw "Error opening file in archive";
			char *p;
			while(p = strchr(filename,'/')) *p = '\\';
			bool isdir = false;
			if(filename[strlen(filename)-1] == '\\') {
				filename[strlen(filename)-1] = '\0';
				isdir = true;
				// it is a directory??
			}
			bool skip = false;
			bool ronly;
			{
				int i;
				for(i = 0; stricmp(flist[i].fnam, filename); i++) {
					if(i == DIM(flist) || flist[i].fnam[0] == '\0') {
						skip = true;
						break;
					}
				}
				if(!skip) ronly = flist[i].ronly;
			}					
			if(!skip) {
				struct stat statbuffer;
				if(_access( filename, 2) == EACCES) throw "No permission to write to file";
				if(!stat(filename, &statbuffer)) {
					if(isdir) {
						if(!(statbuffer.st_mode & _S_IFDIR)) throw "Cannot extract a directory on a non-dir file"; 
						skip = true;
					}
					else {
						if(!(statbuffer.st_mode & _S_IFREG))  throw "File exists and not a regular file";
						else if(unlink(filename)) throw "Cannot remove original file";
					}	
				}
			}
			if(skip) skips++;
			else if(isdir) {   // it is a directory
				if(_mkdir(filename)) throw "Error creating directory";
				dirs++;
			}	
			else {

				FILE *newf = fopen(filename, "wb");
				if(newf == NULL) throw "Cannot open output file in OS filesystem";
				char buf[8192];
				while((s = unzReadCurrentFile(zipf, buf, sizeof(buf))) > 0) {
					if(fwrite(buf, s, 1, newf) != 1) throw "Error writing to filesystem file";
				} 
				if(s < 0) throw "Error reading file in archive";
				if(fclose(newf)) throw "error closeing filesystem file";
				files++;
				if(ronly) chmod(filename,_S_IREAD);
			}
			s = unzCloseCurrentFile(zipf);
			if(s != UNZ_OK) throw "Error closeing file in archive";
			filename[0] = '\0';
		} while((s = unzGoToNextFile(zipf)) == UNZ_OK);
		if(s != UNZ_END_OF_LIST_OF_FILE) throw "Error reading file";
	}
	catch( char *e) {
		sprintf(ee, "Error: %s [at archive item %s (#%d)]\n", e, filename, filenum);
		AfxMessageBox(ee);
		return -1;
	}
	if( zipf) unzClose(zipf);
	sprintf(ee, "%d files and %d directories extracted ", files, dirs);
//	if(skips) 	printf("(%d items skipped)", skips);
	AfxMessageBox(ee);
	return 0;

}

int replaceSTLLibrary( const CString& strPath, const CString& strSTLPath )
{
	try {
		CStdioFile fIn( strPath + "\\BON2Component.dsp", CFile::modeRead );
		CStdioFile fOut( strPath + "\\temp.dsp", CFile::modeCreate | CFile::modeWrite );
	
		CString strLine;
		while( fIn.ReadString( strLine ) ) {
			strLine.Replace( "../include/stl", strSTLPath );
			fOut.WriteString( strLine + "\n" );
		}
		
		fIn.Close();
	
		fOut.Flush();
		fOut.Close();
	
	} catch ( ... ) { 
		AfxMessageBox( "Error has just occured reading file BON2Component.dsp" );
		return -1;
	}

	DeleteFile( strPath + "\\BON2Component.dsp" );
	MoveFile( strPath + "\\temp.dsp", strPath + "\\BON2Component.dsp" );

	return 0;
}