// MgaOpenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GMEApp.h"
#include "MgaOpenDlg.h"
#include "NewXmlbackendProjDlg.h"
#include <afxdb.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMgaOpenDlg dialog


CMgaOpenDlg::CMgaOpenDlg(DialogTypes dType, CWnd* pParent /*=NULL*/)
	: CDialog(CMgaOpenDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMgaOpenDlg)
	m_radio = 1;
	//}}AFX_DATA_INIT

	switch (dType){
	case OpenDialog:
		title = "Open";
		filemsg = "Open project file";
        xmlfilemsg = "Open multi user project";
		flag_isopen = true;
		flag_back = false;
		flag_create = false;
		flag_meta = false;
		break;
	case SaveDialog:
		title = "Save";
		filemsg = "Save project file";
		xmlfilemsg = "Save multi user project";
		flag_isopen = false;
		flag_back = false;
		flag_create = false;
		flag_meta = false;
		break;
	case SaveAsDialog:
		title = "Save As";
		filemsg = "Save project file";
		xmlfilemsg = "Save multi user project";
		flag_isopen = false;
		flag_back = false;
		flag_create = false;
		flag_meta = false;
		break;
	case NewDialog:
		title = "New";
		filemsg = "Create project file";
        xmlfilemsg = "Create multi user project";
		flag_isopen = true;
		flag_back = true;
		flag_create = true;
		flag_meta = false;
		break;
	case ImportDialog:
		title = "Import to new project";
		filemsg = "Create project file";
		xmlfilemsg = "Create multi user project";
		flag_isopen = true;
		flag_back = false;
		flag_create = true;
		flag_meta = false;
		break;
	case ClearLocksDialog:
		title = "Select project";
		filemsg = "Open project file";
		xmlfilemsg = "Open multi user project";
		flag_isopen = true;
		flag_back = false;
		flag_create = false;
		flag_meta = false;
		break;
	}

	
}

static char mgafilter[] = "MGA Files (*.mga)|*.mga|Exported Files (*.xme;*.xml)|*.xme; *.xml|"
	"All files (*.*)|*.*||";

static char xmemgafilter[] = "GME Model Files (*.mga;*.xme;*.mgx)|*.mga; *.xme; *.mgx|MGA Files (*.mga)|*.mga|Exported Files (*.xme;*.xml)|*.xme; *.xml|"
	"Multi-user files (*.mgx)|*.mgx|All files (*.*)|*.*||";

static char mgaonlyfilter[] = "MGA Files (*.mga)|*.mga||";

static char metafilter[] = "MGA Meta Files (*.mta)|*.mta|XML Paradigm Files (*.xmp)|*.xmp|"
	"All files (*.*)|*.*||";


CString CMgaOpenDlg::AskMGAConnectionString(const CString& spec_ext)
{
	CString filters = mgaonlyfilter;
	if( !spec_ext.IsEmpty())
	{
		CString SPEC_EXT = spec_ext; SPEC_EXT.MakeUpper();
		CString spec_filter;
		// as "MGA Files (*.mga)|*.mga|"
		spec_filter.Format( "%s Files (*.%s)|*.%s|", SPEC_EXT, spec_ext, spec_ext);
		// insert this filter at the beginning (thus preferred)
		filters.Insert( 0, spec_filter);
	}

	const char* initialFile = NULL; // NULL or points into currentMgaPath
	char currentMgaPath[MAX_PATH];
	if (theApp.isMgaProj()) {
		CString conn = theApp.connString();
		const char* zsConn = conn;
		zsConn += 4; // skip MGA=
		char* filename;
		if (!GetFullPathName(zsConn, MAX_PATH, currentMgaPath, &filename) || filename == 0) {
		} else {
			initialFile = filename;
		}
	}

	CString conn;
	CFileDialog dlg(flag_isopen ? TRUE : FALSE, NULL, initialFile, 
			OFN_EXPLORER | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | 
			0, filters);

	// if preferred path was set by the user then change to that directory
	if( !theApp.m_preferredPath.IsEmpty())
	{
		OPENFILENAME &ofn = dlg.GetOFN();
		// better be successful in order to use in ofn structure
		if( theApp.SetWorkingDirectory( theApp.m_preferredPath))
			ofn.lpstrInitialDir = theApp.m_preferredPath;
	}

	if( dlg.DoModal() == IDOK )	{
		conn = CString("MGA=") + dlg.GetPathName();
		if(dlg.GetFileExt() == "") // no extension specified by the user
		{
			conn += ".";
			// if spec_ext is NOT empty then 
			// filterindex = 1 stands for special extension
			//             = 2 is the MGA
			conn += dlg.m_ofn.nFilterIndex == 1 && !spec_ext.IsEmpty() ? spec_ext:"mga";
		}
	}
	return conn;
}

CString CMgaOpenDlg::AskConnectionString(bool allowXme)
{
	CString conn;

	try
	{
		if( (allowXme && (m_radio = 1)) || (DoModal() == IDOK && !pressed_back) )
		{
			if( m_radio == 0 || m_radio == 2)
			{
				CDatabase db;
				
				CString hint = fileNameHint;
				int pos = hint.ReverseFind('\\');
				if(pos >= 0) hint = hint.Mid(pos+1);
				pos = hint.Find('.');
				if(pos >= 0) hint = hint.Left(pos);

				if( db.OpenEx("DSN="+hint, CDatabase::forceOdbcDialog) ) {
					conn.Empty();
					if(m_radio == 2) conn = "ODBC;";
					conn += PruneConnectionString(db.GetConnect());
				}
				db.Close();
			}
			else if( m_radio == 1 )
			{
				CFileDialog dlg(true, NULL, fileNameHint.IsEmpty() ? NULL : (LPCTSTR)fileNameHint,
					OFN_EXPLORER | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |
					(flag_create ? 0 : OFN_FILEMUSTEXIST), allowXme ? xmemgafilter : mgafilter);
				if (!folderPathHint.IsEmpty())
					dlg.m_ofn.lpstrInitialDir = folderPathHint.GetBuffer(_MAX_PATH);

				if( dlg.DoModal() == IDOK )
				{
					CString ext = dlg.GetFileExt();
					ext.MakeLower();

					if( ext == "mga" || ext == "mta" )
						conn = CString("MGA=") + dlg.GetPathName();
                    else if( ext == "mgx" )
						conn = CString("MGX=") + dlg.GetPathName();
					else if( (ext == "xml") || (ext == "xme") || (ext == "xmp") )
						conn = CString("XML=") + dlg.GetPathName();
					else if( ext == "mdb" )
						conn = CString("DBQ=") + dlg.GetPathName();
					else if( ext == "" )
					{
						switch( dlg.m_ofn.nFilterIndex )
						{
						case 4:
						case 1:
							conn = CString("MGA=") + dlg.GetPathName() + ".mga";
							break;

						case 2:
							conn = CString("XML=") + dlg.GetPathName() + ".xme";
							break;

						case 3:
							conn = CString("DBQ=") + dlg.GetPathName() + ".mdb";
							break;
						}
					}
					else
					{
						switch( dlg.m_ofn.nFilterIndex )
						{
						case 4:
						case 1:
							conn = CString("MGA=") + dlg.GetPathName();
							break;

						case 2:
							conn = CString("XML=") + dlg.GetPathName();
							break;

						case 3:
							conn = CString("DBQ=") + dlg.GetPathName();
							break;
						}
					}
				}
			}
            else if( m_radio == 3 )
            {
                if( flag_create )
                {
                    // create new multiuser project
                    CNewXmlbackendProjDlg dlg;
                    if( dlg.DoModal() == IDOK )
                        conn = dlg.m_connectionString;
                }
                else
                {
                    // open existing multiuser project
                    BROWSEINFO bi;

                    char szDisplayName[MAX_PATH];
                    char szPath[MAX_PATH];

	                bi.hwndOwner      = m_hWnd;
	                bi.pidlRoot       = NULL;
	                bi.lpszTitle      = "Select the project location.";
	                bi.pszDisplayName = szDisplayName;
	                bi.ulFlags        = BIF_RETURNONLYFSDIRS;
	                bi.lpfn           = NULL;
	                bi.lParam         = 0;

                    LPITEMIDLIST idlist = SHBrowseForFolder(&bi);

                    if( idlist )
                    {
                        if( SHGetPathFromIDList(idlist, szPath) ) 
                        {
                            conn = "MGX=\"";
                            conn += szPath;
                            conn += "\"";
                        }
                    }
                }
            }
		}
	}
	catch(...)
	{
	}

	return conn;
}

CString CMgaOpenDlg::PruneConnectionString(const CString& conn)
{
	CString ret;

	int p = 0;
	while( p < conn.GetLength() )
	{
		int q = conn.Find(';', p);
		if( q < 0 )
			q = conn.GetLength();

		CString part((const char*)conn + p, q-p);

		int r = part.Find('=');
		if( r < 0 )
			r = part.GetLength();

		CString key((const char*)part, r);

		if( key == "UID" ||
			key == "PWD" ||
			key == "USER" ||
			key == "PASSWORD" )
		{
			if( !ret.IsEmpty() )
				ret += ";";

			ret += part;
		}

		p = q+1;
	}

	return ret;
}

CString CMgaOpenDlg::FilterInvalidCharacters(const CString& path, bool isPath)
{
	CString str = path;
	// are there invalid characters in the suggested file name?
	if (str.FindOneOf( _T("\\/:*?\"<>|")) != -1)
	{
		TCHAR nc = _T('_');
		int rpl = 0;
		if (!isPath) {
			rpl += str.Replace(_T('\\'), nc);
			rpl += str.Replace(_T('/'), nc);
			rpl += str.Replace(_T(':'), nc);
		}
		rpl += str.Replace(_T('*'), nc);
		rpl += str.Replace(_T('?'), nc);
		rpl += str.Replace(_T('"'), nc);
		rpl += str.Replace(_T('<'), nc);
		rpl += str.Replace(_T('>'), nc);
		rpl += str.Replace(_T('|'), nc);
		// rpl chars replaced in total
	}
	return str;
}

void CMgaOpenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMgaOpenDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMgaOpenDlg, CDialog)
	//{{AFX_MSG_MAP(CMgaOpenDlg)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMgaOpenDlg message handlers


BOOL CMgaOpenDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_BACK)->EnableWindow(flag_back);
	SetWindowText(title);
	GetDlgItem(IDC_RADIO2)->SetWindowText(filemsg);
    GetDlgItem(IDC_RADIO4)->SetWindowText(xmlfilemsg);

	if( flag_meta )
	{
		GetDlgItem(IDC_MGAOPEN_BMP)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_METAOPEN_BMP)->ShowWindow(SW_SHOW);
	}
	else
	{
		GetDlgItem(IDC_MGAOPEN_BMP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_METAOPEN_BMP)->ShowWindow(SW_HIDE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMgaOpenDlg::OnBack() 
{
	// TODO: Add your control notification handler code here

	pressed_back = true;
	CDialog::OnOK();
}


void CMgaOpenDlg::OnNext() 
{
	// TODO: Add your control notification handler code here

	pressed_back = false;
	CDialog::OnOK();
}

void CMgaOpenDlg::SetFileNameHint(const CString& hint)
{
	fileNameHint = FilterInvalidCharacters(hint);
}

void CMgaOpenDlg::SetFolderPathHint(const CString& hint)
{
	folderPathHint = FilterInvalidCharacters(hint, true);
}
