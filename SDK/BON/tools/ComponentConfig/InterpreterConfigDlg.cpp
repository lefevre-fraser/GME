#pragma warning( disable:4786 )

#include "stdafx.h"
#include <fstream>
#include "InterpreterConfig.h"
#include "InterpreterConfigDlg.h"
#include "EventMaskDialog.h"
#include "RenameComponent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



#define DIM(x) (sizeof(x)/sizeof((x)[0]))
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterpreterConfigDlg dialog

CInterpreterConfigDlg::CInterpreterConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInterpreterConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInterpreterConfigDlg)
	m_Autofield = FALSE;
	m_CompName = _T("");
	m_ClassName = _T("");
	m_ClassUUID = _T("");
	m_Interpreter = -1;
	m_Paradigms = _T("");
	m_ProgID = _T("");
	m_TlbName = _T("");
	m_TlbUUID = _T("");
	m_parindep = FALSE;
	m_evmaskedit = _T("");
	m_toolbaricon = FALSE;
	m_customtrans = FALSE;
	m_tooltipText = _T("");
	m_strGmePath = _T("");
	m_systemreg = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );
}

CInterpreterConfigDlg::~CInterpreterConfigDlg()
{
	CoUninitialize();
}

void CInterpreterConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterpreterConfigDlg)
	DDX_Check(pDX, IDC_AUTOFIELDS, m_Autofield);
	DDX_Text(pDX, IDC_COMPNAME, m_CompName);
	DDX_Text(pDX, IDC_CLASSNAME, m_ClassName);
	DDX_Text(pDX, IDC_CLASSUUID, m_ClassUUID);
	DDX_Radio(pDX, IDC_INTERPRETER, m_Interpreter);
	DDX_Text(pDX, IDC_PARNAME, m_Paradigms);
	DDX_Text(pDX, IDC_PROGID, m_ProgID);
	DDX_Text(pDX, IDC_TLBNAME, m_TlbName);
	DDX_Text(pDX, IDC_TLBUUID, m_TlbUUID);
	DDX_Check(pDX, IDC_PARINDEP, m_parindep);
	DDX_Text(pDX, IDC_EVMASKED, m_evmaskedit);
	DDX_Check(pDX, IDC_TBICON, m_toolbaricon);
	DDX_Check(pDX, IDC_CUSTOMTRANS, m_customtrans);
	DDX_Text(pDX, IDC_EDIT_TOOLTIP, m_tooltipText);
	DDX_Text(pDX, IDC_GMEPATH, m_strGmePath);
	DDX_Check(pDX, IDC_SYSTEMREG, m_systemreg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInterpreterConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CInterpreterConfigDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_COMPNAME, OnChangeName)
	ON_BN_CLICKED(IDC_INTERPRETER, OnBNInterpreter)
	ON_BN_CLICKED(IDC_REGEN, OnRegen)
	ON_BN_CLICKED(IDC_PARINDEP, OnParindep)
	ON_BN_CLICKED(IDC_EVMASK, OnEvmask)
	ON_BN_CLICKED(IDC_PLUGIN, OnBNPlugin)
	ON_BN_CLICKED(IDC_ADDON, OnBNAddon)
	ON_BN_CLICKED(IDC_PARADD, OnParadd)
	ON_BN_CLICKED(IDC_TBICON, OnTbicon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterpreterConfigDlg message handlers

const CString CInterpreterConfigDlg::typetoken[3] = { "Interpreter", "PlugIn", "AddOn" };

BOOL CInterpreterConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_Autofield = true;
	m_Interpreter = 0;
	componenttechnology = 0;


	DWORD type;
	static char name[51];
	DWORD namelen = sizeof(name)-1;
	HKEY hn;

	LONG l = RegOpenKeyEx(HKEY_LOCAL_MACHINE,"SOFTWARE\\Microsoft\\Windows\\CurrentVersion", 0, KEY_READ, &hn);
	if(l == ERROR_SUCCESS)	l = RegQueryValueEx(hn,"ProgramFilesDir", NULL, &type, (LPBYTE)name, &namelen);
	if(l != ERROR_SUCCESS) strcpy(name,  "c:\\Program Files\\GME");
	else strncat(name, "\\GME", sizeof(name)-1 - namelen);
	m_strGmePath = name;
	m_evmaskedit = "0x00000000";

	OnRegen();

	RefreshOthers();

    readGmeSourceFileList();

	if(!ReadConfig()) exit(-1);
	m_initialGMEPath = m_strGmePath; // save it, to check it later if it changes

	GetDlgItem(IDC_PARNAME)->EnableWindow(!m_parindep);
	GetDlgItem(IDC_EVMASK)->EnableWindow(m_Interpreter == 2);
	GetDlgItem(IDC_ADDON)->EnableWindow(componenttechnology == 3 || componenttechnology == 4 );
	if(m_parindep != 0) 	m_Paradigms = "*";

	{
		CString str;
		GetWindowText(str);
		switch(componenttechnology) {
		case 1: str += " -- BON"; break; 
		case 2: str += " -- OLD BON"; break; 
		case 3: str += " -- RAW COM"; break; 
		case 4: str += " -- BON 2"; break; 
		default: 
			AfxMessageBox("Cannot identify component technology.\n" 
			"Please #define BONCOMPONENT, OLDBONCOMPONENT, RAWCOMPONENT or BON2COMPONENT manually\n"
			"in the ComponentConfig.h file");
		}
		SetWindowText(str);
	}    

	UpdateData(FALSE);

    OnTbicon();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInterpreterConfigDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CInterpreterConfigDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInterpreterConfigDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CInterpreterConfigDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CInterpreterConfigDlg::RefreshOthers() {
	UpdateData(TRUE);
	if(m_Autofield) {
		if(!m_parindep) m_Paradigms = m_CompName;
		m_ProgID = "MGA."+typetoken[m_Interpreter] + "." + m_CompName;
		m_ClassName = "MGA "+typetoken[m_Interpreter] + " CoClass (" + m_CompName + ")";
		m_TlbName = "MGA "+typetoken[m_Interpreter] + " TypeLibrary (" + m_CompName + ")";
        m_tooltipText = m_CompName + " " + typetoken[m_Interpreter];
	}
	UpdateData(FALSE);
}

void CInterpreterConfigDlg::OnParindep() 
{
	UpdateData();
	GetDlgItem(IDC_PARNAME)->EnableWindow(!m_parindep);
	if(m_parindep) m_Paradigms = "*";
	else m_Paradigms = m_CompName;
	UpdateData(FALSE);
}


void CInterpreterConfigDlg::OnChangeName() 
{
	RefreshOthers();
}

void CInterpreterConfigDlg::OnBNInterpreter() {
	GetDlgItem(IDC_EVMASK)->EnableWindow(FALSE);
	RefreshOthers();
}

void CInterpreterConfigDlg::OnBNPlugin() 
{
	GetDlgItem(IDC_EVMASK)->EnableWindow(FALSE);
	RefreshOthers();
}

void CInterpreterConfigDlg::OnBNAddon() 
{
	GetDlgItem(IDC_EVMASK)->EnableWindow(TRUE);
	RefreshOthers();
}

//DEL void CInterpreterConfigDlg::GenUUIDs() {
//DEL    HANDLE hChildStdoutRd, hChildStdoutWr, hChildStdoutRdDup, hSaveStdout; 
//DEL    SECURITY_ATTRIBUTES saAttr; 
//DEL    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
//DEL    saAttr.bInheritHandle = TRUE; 
//DEL    saAttr.lpSecurityDescriptor = NULL; 
//DEL     
//DEL    hSaveStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
//DEL  
//DEL    if (! CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0)) return;
//DEL    if (! SetStdHandle(STD_OUTPUT_HANDLE, hChildStdoutWr)) return;
//DEL    if(!DuplicateHandle(GetCurrentProcess(), hChildStdoutRd, 
//DEL       GetCurrentProcess(), &hChildStdoutRdDup, 0, 
//DEL       FALSE,                  // not inherited 
//DEL       DUPLICATE_SAME_ACCESS) ) return; 
//DEL    CloseHandle(hChildStdoutRd); 
//DEL  
//DEL 
//DEL    PROCESS_INFORMATION piProcInfo; 
//DEL    STARTUPINFO siStartInfo; 
//DEL    ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
//DEL    siStartInfo.cb = sizeof(STARTUPINFO); 
//DEL 
//DEL    siStartInfo.dwFlags    = STARTF_USESTDHANDLES;
//DEL    siStartInfo.hStdInput  = GetStdHandle (STD_INPUT_HANDLE);
//DEL    siStartInfo.hStdOutput = GetStdHandle (STD_OUTPUT_HANDLE);
//DEL    siStartInfo.hStdError  = GetStdHandle (STD_ERROR_HANDLE);
//DEL 
//DEL    if(! CreateProcess(NULL, 
//DEL       "uuidgen -n2", // command line 
//DEL       NULL,          // process security attributes 
//DEL       NULL,          // primary thread security attributes 
//DEL       TRUE,          // handles are inherited 
//DEL       0,             // creation flags 
//DEL       NULL,          // use parent's environment 
//DEL       NULL,          // use parent's current directory 
//DEL       &siStartInfo,  // STARTUPINFO pointer 
//DEL       &piProcInfo)   // receives PROCESS_INFORMATION 
//DEL 	) return;
//DEL   
//DEL  
//DEL    if (! SetStdHandle(STD_OUTPUT_HANDLE, hSaveStdout)) return;
//DEL  
//DEL    if (!CloseHandle(hChildStdoutWr)) return;
//DEL  
//DEL #define BUFSIZE 100
//DEL    char chBuf[BUFSIZE+1];
//DEL    DWORD dwRead;
//DEL    int s;
//DEL    if( !(s = ReadFile( hChildStdoutRdDup, chBuf, BUFSIZE, &dwRead, NULL)) 
//DEL 	   || dwRead == 0 || dwRead >= BUFSIZE) {
//DEL 		DWORD xx = GetLastError();
//DEL 		return;
//DEL    }
//DEL 
//DEL    chBuf[dwRead] = '\0';
//DEL    m_TlbUUID = strtok(chBuf,"\n\r ");
//DEL    m_ClassUUID = strtok(NULL,"\n\r ");
//DEL } 
 

#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>

CString configfilename = "ComponentConfig.h";

bool CInterpreterConfigDlg::ReadConfig()
{
	FILE *ff = fopen(configfilename, "r");
	if(ff == NULL) {
		MessageBox(configfilename + " is not found in current directory\n"
					"Please make sure you have a proper component source set, including a " + configfilename,
					"ComponentConfig WARNING");
		return false;
	}
	char line[160];
	while(fgets(line, DIM(line), ff)) {
		char *p = strtok(strdup(line)," \t");
		if(*p == '\n' || (p[0] == '/' && p[1] == '/') || !strcmp(p, "#error")) continue;  // empty line, comment, or original file
		else if(strcmp(p, "#define")) {
warn:
			MessageBox(CString("Unknown line in config file (will be deleted):\n	") + line, "ComponentConfig WARNING");
			continue;
		}
		p = strtok(NULL, " \t\"\n");
		char *p2 = strtok(NULL, "\"\n");
		     if(!strcmp(p, "TYPELIB_UUID"))  m_TlbUUID = p2;
		else if(!strcmp(p, "TYPELIB_NAME"))  m_TlbName = p2;
		else if(!strcmp(p, "COCLASS_UUID"))  m_ClassUUID = p2;
		else if(!strcmp(p, "COCLASS_NAME"))  m_ClassName = p2;
		else if(!strcmp(p, "COCLASS_PROGID"))  m_ProgID = p2;
		else if(!strcmp(p, "COMPONENT_NAME"))  { m_CompName = p2; sPreviousComponentName = p2; }
		else if(!strcmp(p, "PARADIGMS"))      m_Paradigms = p2;
		else if(!strcmp(p, "ADDON_EVENTMASK"))      m_evmaskedit = p2;
		else if(!strcmp(p, "GME_INTERPRETER"))   m_Interpreter = 0;
		else if(!strcmp(p, "BONCOMPONENT"))   componenttechnology = 1;
		else if(!strcmp(p, "OLDBONCOMPONENT"))   componenttechnology = 2;
		else if(!strcmp(p, "RAWCOMPONENT"))   componenttechnology = 3;
		else if(!strcmp(p, "BON2COMPONENT"))   componenttechnology = 4;
		else if(!strcmp(p, "GME_PLUGIN"))   m_Interpreter = 1;
		else if(!strcmp(p, "GME_ADDON"))    m_Interpreter = 2;
		else if(!strcmp(p, "PARADIGM_INDEPENDENT"))    m_parindep = TRUE;
		else if(!strcmp(p, "BON_ICON_SUPPORT"))    m_toolbaricon = TRUE;
		else if(!strcmp(p, "BON_CUSTOM_TRANSACTIONS"))	m_customtrans = TRUE;
		else if(!strcmp(p, "REGISTER_SYSTEMWIDE"))	m_systemreg = TRUE;
		else if(!strcmp(p, "GME_BASE")) m_strGmePath = p2;
		else if(!strncmp(p, "COCLASS_UUID_EXPLODED", strlen("COCLASS_UUID_EXPLODED"))) ;
        else if(!strcmp(p, "TOOLTIP_TEXT")) m_tooltipText = p2;
		else goto warn;
	}
	fclose(ff);
	if(componenttechnology == 0) {
		if(access("Component.h",0) != -1) componenttechnology = 1;
		else if(access("Interpreter.h",0) != -1) componenttechnology = 2;
		else if(access("RawComponent.h",0) != -1) componenttechnology = 3;
		else if(access("BON2Component.h",0) != -1) componenttechnology = 4;
	}
	return true;
}

void CInterpreterConfigDlg::readGmeSourceFileList()
{
    std::ifstream is( "GMESources.txt" );
    m_gmeSourceFiles.clear();

    while( !is.eof() && is.good() )
    {
        std::string str;
        std::getline( is, str );

        if( is.good() )
            m_gmeSourceFiles.push_back( str );
    }
}
  
void CInterpreterConfigDlg::updateVcprojFile( const char * vcprojFileName )
{
    std::ifstream is( vcprojFileName );
    if( !is.good() )
        return;
	is.close();


	bool is_gmeloc_changed = false, is_compname_changed = false;

	CString t1 = m_initialGMEPath;
	CString t2 = m_strGmePath;
	t1.Replace("\\","/");
	t2.Replace("\\","/");

	if( t1.CompareNoCase( t2) != 0) // the location of GME has changed
		is_gmeloc_changed = true;
	if( m_CompName != sPreviousComponentName) // the component name has changed
		is_compname_changed = true;

	try
	{
		std::string sdkBONPath = m_strGmePath;
		sdkBONPath += "/sdk/BON/";

		RenameComponent7 component
			( is_gmeloc_changed
			, is_compname_changed
			, componenttechnology
			, m_gmeSourceFiles
			, sdkBONPath
			, (LPCTSTR)vcprojFileName
			, (LPCTSTR)m_CompName
			, (LPCTSTR)sPreviousComponentName
			);

	}
	catch( const char *)
	{
		AfxMessageBox( "VCProject setup failed. Check if you have VS 2003 installed.\
					   \nNOTE: VS 2005 users download new version of CreateNewComponent from \
					   \nhttp://escher.isis.vanderbilt.edu/JIRA/browse/GME-137");
	}
	catch(...)
	{
		AfxMessageBox( "Could not perform component rename");
	}

/*    std::ofstream os( "temp.dsp" );

    std::string sdkBONPath = m_strGmePath;
    sdkBONPath += "/sdk/BON/";

    while( !is.eof() && is.good() )
    {
        std::string str;
        std::getline( is, str );
        if( is.good() )
        {
            CString str2 = str.c_str();
            int pos = -1;
            for( i=0; i<m_gmeSourceFiles.size(); ++i )
            {
                pos = str2.Find( m_gmeSourceFiles[i].c_str(), 0 );
                if( pos != -1 )
                    break;
            }

            if( pos != -1 )
            {
                if( _strnicmp( str.c_str(), "SOURCE", 6 ) == 0 )
                {
                    // update source file path
                    os  << "SOURCE=\"" << sdkBONPath << m_gmeSourceFiles[i].c_str() << "\"\n";
                }
                else if( strncmp( str.c_str(), "InputPath", 9 ) == 0 )
                {
                    // update custom build source file path
                    os  << "InputPath=\"" << sdkBONPath << m_gmeSourceFiles[i].c_str() << "\"\n";
                }
                else if( str2.Find( "midl", 0 ) >= 0 )
                {
                    // update midl parameter
                    os  << "\tmidl /I.\\ /server none /client none \""
                        << sdkBONPath << m_gmeSourceFiles[i].c_str() << "\"\n";
                }
                else
                {
                    os << str << "\n";
                }
            }
            else
            {               
                if( strncmp( str.c_str(), "# ADD CPP", 9 ) == 0 && str.size() > 30 )
                {
                    // update c compiler include path
                    os << str << " /I.\\ /I\"" << sdkBONPath << "\"\n";
                }
                else
                {
                    os << str << "\n";
                }
            }
        }
    }

    os.close();
    is.close();

    CopyFile( "temp.dsp", dspFileName, FALSE );
    DeleteFile( "temp.dsp" );*/
}


void CInterpreterConfigDlg::OnOK() 
{
	UpdateData(TRUE);
	CString backupname = configfilename;
	if(backupname.Right(2) != ".h") {
		MessageBox(configfilename + " is an incorrect header name", "ComponentConfig");
		return;
	}
	backupname.Replace(".h",".old");
	unlink(backupname);
	rename(configfilename,backupname);
	int f = creat(configfilename, _S_IWRITE);
	if(f == 0) {
		MessageBox(configfilename + " cannot be created", "ComponentConfig");
		return;
	}
	time_t t;
	time(&t);
	char *time = ctime(&t);
	CString uuid_exploded = "0x"+m_ClassUUID;
	uuid_exploded.Insert(36,"-");
	uuid_exploded.Insert(34,"-");
	uuid_exploded.Insert(32,"-");
	uuid_exploded.Insert(30,"-");
	uuid_exploded.Insert(28,"-");
	uuid_exploded.Insert(23,"-");
	uuid_exploded.Replace("-",", 0x");


	FILE *ff = fdopen(f, "w");

	fprintf(ff, "// Component configuration file automatically generated as %s\n"
				"// by ConfigureComponent on %s\n\n",
				(LPCSTR)configfilename, time );

    static char *technames[4] = { "BONCOMPONENT", "OLDBONCOMPONENT", "RAWCOMPONENT", "BON2COMPONENT" };
	if(componenttechnology) fprintf(ff, "#define %s\n\n", technames[componenttechnology-1]); 

    fprintf(ff, "// COM UUID-s, names and progID\n\n"
				"#define TYPELIB_UUID \"%s\"\n"
				"#define TYPELIB_NAME \"%s\"\n"
				"#define COCLASS_UUID \"%s\"\n"
				"#define COCLASS_NAME \"%s\"\n"
				"#define COCLASS_PROGID \"%s\"\n\n\n"
				"// This name will appear in the popup window for interpreter selection.\n"
				"#define COMPONENT_NAME \"%s\"\n\n\n"
                "// This text will appear in the toolbar icon tooltip and in the menu.\n"
                "#define TOOLTIP_TEXT \"%s\"\n\n\n"
				"// This #define determines the interpreter type:\n",
				 (LPCSTR)m_TlbUUID, (LPCSTR)m_TlbName,
                 (LPCSTR)m_ClassUUID, (LPCSTR)m_ClassName, 
				 (LPCSTR)m_ProgID, (LPCSTR)m_CompName, (LPCSTR)m_tooltipText 
                 );
	switch(m_Interpreter) {
	case 0:
		fprintf(ff, "#define GME_INTERPRETER\n");
		break;
	case 1: 
		fprintf(ff, "#define GME_PLUGIN\n");
		break;
	case 2:
		fprintf(ff, "#define GME_ADDON\n");
		fprintf(ff, "#define ADDON_EVENTMASK %s\n", m_evmaskedit);
		break;
	}

	if(m_parindep) fprintf(ff, "#define PARADIGM_INDEPENDENT\n");
	else		   fprintf(ff, "// The name of the paradigm(s). The GME will use this component\n"
				"// for this paradigm. Separate the names of paradigms by commas.\n"
				"#define PARADIGMS \"%s\"\n",
				m_Paradigms);

	m_strGmePath.Replace("\\\\","/");
	m_strGmePath.Replace("\\","/");
	fprintf(ff, "\n\n// This is the location of the GME interfaces file (Mga.idl, Meta.idl, etc)\n"
				"#define GME_BASE %s\n\n\n", m_strGmePath);

	if(m_toolbaricon) fprintf(ff, "#define BON_ICON_SUPPORT\n\n");
	else			  fprintf(ff, "// not defined: #define BON_ICON_SUPPORT\n\n");
	
	if(m_customtrans) fprintf(ff, "#define BON_CUSTOM_TRANSACTIONS\n\n");
	else			  fprintf(ff, "// not defined: #define BON_CUSTOM_TRANSACTIONS\n\n");

	if(m_systemreg)   fprintf(ff, "#define REGISTER_SYSTEMWIDE\n\n");
	else			  fprintf(ff, "// not defined: #define REGISTER_SYSTEMWIDE\n\n");

	fprintf(ff, "// Just to please the whims of those Microsoft jerks:\n");
	int n = 1;
	for(char *a = strtok((LPSTR)(LPCSTR)uuid_exploded,","); a; a = strtok(NULL, ",")) {
		fprintf(ff, "#define COCLASS_UUID_EXPLODED%d %s\n", n++, a);
	}


	fclose(ff);
	close(f);

	updateVcprojFile( "BONComponent.vcproj" );
    updateVcprojFile( "Component.vcproj" );
    updateVcprojFile( "OLDBONComponent.vcproj" );
	updateVcprojFile( "BON2Component.vcproj" );
	
	updateVcprojFile( sPreviousComponentName + "BONComponent.vcproj" );
	updateVcprojFile( sPreviousComponentName + "Component.vcproj" );
	updateVcprojFile( sPreviousComponentName + "OLDBONComponent.vcproj" );
	updateVcprojFile( sPreviousComponentName + "BON2Component.vcproj" );

	CDialog::OnOK();
	MessageBox(configfilename + " has been successfully created.\n"
			   "You may open the ...component.sln solution now.\n", "ConfigureComponent");

}


void CInterpreterConfigDlg::OnRegen() 
{
	GUID uid;
	OLECHAR buf[60];
	if(CoCreateGuid(&uid) != S_OK || !StringFromGUID2(uid, buf, DIM(buf))) {
		m_ClassUUID = "<UUIDgen failure, enter manually!>";
	}
	else { 
		buf[wcslen(buf)-1] = OLECHAR(0);
		m_ClassUUID = buf+1;
	}

	if(CoCreateGuid(&uid) != S_OK || !StringFromGUID2(uid, buf, DIM(buf))) {
		m_TlbUUID = "<UUIDgen failure, enter manually!>";
	}
	else { 
		buf[wcslen(buf)-1] = OLECHAR(0);
		m_TlbUUID = buf+1;
	}
	UpdateData(FALSE);
}



void CInterpreterConfigDlg::OnEvmask() 
{
	UpdateData();
	CEventMaskDialog dlg;	
	dlg.fin.open(m_strGmePath+"\\Interfaces\\Mga.idl" );//, ios::open_mode);
	if(dlg.fin.rdstate() != ios::goodbit) {
		AfxMessageBox("Cannot open Mga.h at specified interface path");
	}
	dlg.mask = 0;
	sscanf(m_evmaskedit, "%lx", &dlg.mask);
	if(dlg.DoModal()) {
		m_evmaskedit.Format("0x%08LX", dlg.mask);
		UpdateData(FALSE);
	}	
}



void CInterpreterConfigDlg::OnParadd() 
{
	AfxMessageBox("Not yet implemented");	
}

void CInterpreterConfigDlg::OnTbicon() 
{
    UpdateData();
    //m_editIconPath.EnableWindow( m_toolbaricon );
    //m_btnBrowseIcon.EnableWindow( m_toolbaricon );
	
}
