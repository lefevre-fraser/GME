// GMEApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <afxwin.h> // for CWaitCursor
#include "GMEApp.h"


#include "Gme_i.c"
#include "GmeLib_i.c"
#include "../Mga/MgaLib_i.c"
#include "Parser.h"

#include "GMEstd.h"
#include "GuiMeta.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "GMEDoc.h"
#include "GMEView.h"
#include "GMEChildFrame.h"
#include "GMEBrowser.h"
#include "GMEObjectInspector.h"
#include <locale.h>
#include "MgaOpenDlg.h"
#include "GmeDocTemplate.h"
#include "ProjectPropertiesDlg.h"
#include "GmeLib.h"
#include "GMEOLEApp.h"
#include "GMEEventLogger.h"
#include "GMEPrintDialog.h"
#include "ExceptionHandler.h"
#include "EmergencySaveDlg.h"
#include "CrashTest.h"
#include <Gdiplus.h>
#include "GraphicsUtil.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ATL ///////////////////////////////////////////////////////////////////////////
#include "mga_i.c"
#include "meta_i.c"
#include "Splash.h"

CComModule _Module;


/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CGMEApp

BEGIN_MESSAGE_MAP(CGMEApp, CWinApp)
	//{{AFX_MSG_MAP(CGMEApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_CLOSEPROJECT, OnUpdateFileCloseproject)
	ON_COMMAND(ID_FILE_CLOSEPROJECT, OnFileCloseproject)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO, OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, OnUpdateEditRedo)
	ON_UPDATE_COMMAND_UI(ID_FILE_EXPORTXML, OnUpdateFileExportxml)
	ON_COMMAND(ID_FILE_EXPORTXML, OnFileExportxml)
	ON_COMMAND(ID_FILE_IMPORTXML, OnFileImportxml)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PROJECTPROPERTIES, OnUpdateEditProjectproperties)
	ON_COMMAND(ID_EDIT_PROJECTPROPERTIES, OnEditProjectproperties)
	ON_COMMAND(ID_FILE_SETTINGS, OnFileSettings)
	ON_COMMAND(ID_FILE_CLEARLOCKS, OnFileClearLocks)
	ON_COMMAND(ID_EDIT_CLEARUNDO, OnEditClearUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEARUNDO, OnUpdateEditClearUndo)
	ON_COMMAND(ID_HELP_CONTENTS, OnHelpContents)
	ON_COMMAND(ID_FILE_CHECKALL, OnFileCheckall)
	ON_UPDATE_COMMAND_UI(ID_FILE_CHECKALL, OnUpdateFileCheckall)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVEPROJECT, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVEPROJECTAS, OnUpdateFileSaveAs)
	ON_COMMAND(ID_FILE_SAVEPROJECTAS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_SAVEPROJECT, OnFileSave)
	ON_COMMAND(ID_FILE_ABORTPROJECT, OnFileAbortProject)
	ON_UPDATE_COMMAND_UI(ID_FILE_ABORTPROJECT, OnUpdateFileAbortProject)
	ON_COMMAND(ID_FILE_REGCOMPONENTS, OnFileRegcomponents)
	ON_COMMAND(ID_FILE_REGPARADIGMS, OnFileRegparadigms)
	ON_UPDATE_COMMAND_UI(ID_FILE_REGCOMPONENTS, OnUpdateFileRegcomponents)
	ON_UPDATE_COMMAND_UI(ID_FILE_UPDATETHROUGHXML, OnUpdateFileXMLUpdate)
	ON_COMMAND(ID_FILE_UPDATETHROUGHXML, OnFileXMLUpdate)
	ON_COMMAND(ID_FILE_DISPLAY_CONSTRAINTS, OnFileDisplayConstraints)
	ON_UPDATE_COMMAND_UI(ID_FILE_DISPLAY_CONSTRAINTS, OnUpdateFileDisplayConstraints)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	//}}AFX_MSG_MAP
	// Standard file based document commands
//	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
//	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, OnUniquePrintSetup) // CWinApp::OnFilePrintSetup)
	// MRU - most recently used project menu
	ON_UPDATE_COMMAND_UI(ID_FILE_MRU_PRJ1, OnUpdateRecentProjectMenu)
	ON_COMMAND_EX_RANGE(ID_FILE_MRU_PRJ1, ID_FILE_MRU_PRJ16, OnOpenRecentProject)
	ON_COMMAND_RANGE(ID_FILE_RUNPLUGIN1, ID_FILE_RUNPLUGIN8, OnRunPlugin)
	ON_COMMAND_RANGE(ID_FILE_INTERPRET1, ID_FILE_INTERPRET18, OnRunInterpreter)
	ON_UPDATE_COMMAND_UI_RANGE( ID_FILE_RUNPLUGIN1, ID_FILE_RUNPLUGIN8, OnUpdateFilePluginX)
	ON_UPDATE_COMMAND_UI_RANGE( ID_FILE_INTERPRET1, ID_FILE_INTERPRET18, OnUpdateFileInterpretX)
	ON_COMMAND(ID_FOCUS_BROWSER, OnFocusBrowser)
	ON_COMMAND(ID_FOCUS_INSPECTOR, OnFocusInspector)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// The one and only CGMEApp object

CGMEApp theApp;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.


/*static*/ const char * CGMEApp::m_no_model_open_string = "_NO_MODEL_IS_OPEN_";

/////////////////////////////////////////////////////////////////////////////
// CGMEApp construction

CGMEApp::CGMEApp() :
    m_RecentProjectList(0, "Recent Project List", "Project%d", 4)
  , m_compFilterOn( false)
{
	multipleView = false;
	labelAvoidance = false;
	defZoomLev = "100";
	mouseOverNotify = false;
	maintainHistory = false;
	realFmtStr = "%.12g";
	// TODO: add construction code here,
	set_terminate(EmergencyTerminate);
	// Place all significant initialization in InitInstance
}

CGMEApp::~CGMEApp()
{
}

class CGMECommandLineInfo : public CCommandLineInfo {
public:
 	bool bNoProtect, bOpenLast;
 	CGMECommandLineInfo() : bNoProtect(false), bOpenLast(false) { ; }

	virtual void ParseParam(const char* pszParam, BOOL bFlag, BOOL bLast) {
		if(bFlag && !strcmp(pszParam, "d")) bNoProtect = true;
 		else if(bFlag && !strcmp(pszParam, "l")) bOpenLast = true;
		else if(bFlag && !strcmp(pszParam, "REGSERVER")) {
			char c[200];
			GetModuleFileName(NULL, c, sizeof(c));
			CComPtr<ITypeLib> it;
			HRESULT hr = LoadTypeLibEx(CComBSTR(c),REGKIND_REGISTER, &it);
			if(hr == S_OK) { AfxMessageBox("Registered"); exit(0); }
			else { AfxMessageBox("Registration error: " + hr); exit(-1); }
		}
		else if(bFlag && !strcmp(pszParam, "UNREGSERVER")) {
			HRESULT hr = UnRegisterTypeLib(LIBID_GmeLib, 1, 0, LANG_NEUTRAL, SYS_WIN32);
			if(hr == S_OK) { AfxMessageBox("Unregistered"); exit(0); }
			else { AfxMessageBox("Unregistration error: " + hr); exit(-1); }
		}
		else CCommandLineInfo::ParseParam(pszParam, bFlag, bLast);
	}

};


bool CheckInterfaceVersions()	{
		bool err = false;
		LPCOLESTR components[] = {
			L"Mga.MgaProject",
			L"Mga.MgaMetaProject",
			L"Mga.CoreProject",
			L"Mga.MgaRegistrar",
			L"Mga.MgaParser",
			L"Mga.AddOn.ConstraintManager",
			NULL };
		CString errstring;
#if (_WIN32_WINNT >= 0x0400 ) || defined(_WIN32_DCOM) // DCOM
		HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
#else
		HRESULT hr = CoInitialize(NULL);
#endif // DCOM
		char hrbuf[20];
		if(hr != S_OK) AfxMessageBox(CString("Coinitialize failure. Err: #") + _ltoa(hr,hrbuf,16));
		for(LPCOLESTR *p = components; *p; p++) {
			MgaInterfaceVersion verid = MgaInterfaceVersion_None;
			CComPtr<IUnknown> unk;
			CString ee;
			if(S_OK != (hr = unk.CoCreateInstance(*p))) {
				errstring.Format("Cannot create object %%S (Err: #%X)", hr);
gerr:
				CString a;
				a.Format(errstring, *p, verid/0x1000, verid%0x1000, MgaInterfaceVersion_Current/0x1000,MgaInterfaceVersion_Current%0x1000);
				AfxMessageBox(a);
				err = true;
				continue;
			}
			CComQIPtr<IMgaVersionInfo> vinf = unk;
			if(!vinf) {
				errstring = "Incompatible version of object %S (does not support version information)";
				goto gerr;
			}
			if(S_OK != vinf->get_version(&verid)) {
				errstring = "Get_Version failed for object %S";
				goto gerr;
			}
			if(verid != MgaInterfaceVersion_Current) {
				errstring = "Interface version for class %S (%d.%d) differs from GME interface version (%d.%d)";
				goto gerr;
			}
		}
		return err;
}


/////////////////////////////////////////////////////////////////////////////
// CGMEApp initialization

BOOL CGMEApp::InitInstance()
{
	// CG: The following block was added by the Splash Screen component.
	CGMECommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	
	if( cmdInfo.m_nShellCommand == CCommandLineInfo::FileOpen )
		cmdInfo.m_bShowSplash = false;

	CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
	// CG: The following block was inserted by 'Status Bar' component.
	{
		//Set up date and time defaults so they're the same as system defaults
		setlocale(LC_ALL, "");
	}

	if(CheckInterfaceVersions()) return FALSE;


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	//Enable3dControls(); // deprecated
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


	// Enable assigning shortcut keys to the menus
	InitKeyboardManager();

	// Enabling user tools
	EnableUserTools(ID_TOOLS_EXTERNAL_TOOLS, ID_USER_TOOL1, ID_USER_TOOL10, RUNTIME_CLASS(CUserTool)/*, IDR_MENU_ARGS, IDR_MENU_DIRS*/);

	InitContextMenuManager();

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("GME\\GUI"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	m_RecentProjectList.ReadList();

	// Load Accelerator Table for CGMEView

	m_GMEView_hAccel = LoadAccelerators(m_hInstance, MAKEINTRESOURCE(IDR_GMEVIEW));
	ASSERT( m_GMEView_hAccel );

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	pDocTemplate = new CGmeDocTemplate(
		IDR_GMETYPE,
		RUNTIME_CLASS(CGMEDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
#if !defined(ACTIVEXGMEVIEW)
		RUNTIME_CLASS(CGMEView));
#else
		RUNTIME_CLASS(CGMEChildFrame));
#endif
	pDocTemplate->SetContainerInfo(IDR_GMETYPE_CNTR_IP);
	AddDocTemplate(pDocTemplate);

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleObjectFactory::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.


	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

#if !defined(ADDCRASHTESTMENU) && defined(_DEBUG)
	bNoProtect = true;
#else
	bNoProtect = cmdInfo.bNoProtect;
#endif
	
	//initialize the logfile - first check registry to see if the user wants logging
	MSGTRY
	{
		CComPtr<IMgaRegistrar> registrar;
		COMTHROW(registrar.CoCreateInstance(CComBSTR("Mga.MgaRegistrar")));
		VARIANT_BOOL enablelogging;
		COMTHROW( registrar->get_EventLoggingEnabled(REGACCESS_USER, &enablelogging) );
		if(enablelogging != VARIANT_FALSE)
		{
			CGMEEventLogger::initialize();
			CGMEEventLogger::LogGMEEvent("GME started\r\n");
		}
	}
	MSGCATCH("Error while trying to get logfile settings",;);

	if( (CMainFrame*)m_pMainWnd)
	{
		CGMEOLEApp *t_pGmeOleApp = new CGMEOLEApp();
		((CMainFrame*)m_pMainWnd)->setGmeOleApp( t_pGmeOleApp );
	}
	else ASSERT(0);

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.

		//
		// load settings in this case as well
		GetSettings();

		return TRUE;
	}

	// Updates system registry with all creatable classes (_OLECREATE)
	// PETER: It works only with administrator priviledges
	COleObjectFactory::UpdateRegistryAll();
	
	// Make sure the type library is registered or dual interface won't work.
	AfxOleRegisterTypeLib(AfxGetInstanceHandle(), LIBID_GmeLib);

	// We don't want a new document at startup
	if( cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew )
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	if( cmdInfo.m_nShellCommand == CCommandLineInfo::FileOpen ) {
		CString conn = cmdInfo.m_strFileName;
		if(conn.Find("=") < 0) {
			conn.Insert(0,"MGA=");
		}
		OpenProject(conn);

		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	}
 	else if(cmdInfo.bOpenLast && !m_RecentProjectList[0].IsEmpty()) {
 		OpenProject(m_RecentProjectList[0]);
 		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
 	}

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();


	dynmenus_need_refresh = true;

	GetSettings();
	m_pMainWnd->DragAcceptFiles(TRUE);

	return TRUE;
}

BOOL CGMEApp::PreTranslateMessage(MSG* pMsg)
{
	// CG: The following lines were added by the Splash Screen component.
	if (CSplashWnd::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinApp::PreTranslateMessage(pMsg);
}



/////////////////////////////////////////////////////////////////////////////
// CGMEApp emergency

void CGMEApp::EmergencyTerminate()
{
	theApp.EmergencySave(SaveAndBringUpMessageBox);
}

BOOL CGMEApp::EmergencySave(EmergencySaveMode saveMode)
{
	CGMEEventLogger::LogGMEEvent("EMERGENCY EVENT\r\n");
	CString emergencySaveMsg;
	CString embackupname;
	if (mgaProject && (proj_type_is_mga || proj_type_is_xmlbackend)) {
		if (saveMode == DoTheSaveOnly && emergencyBackupName.GetLength() > 0) {
			embackupname = emergencyBackupName;
		} else {
			embackupname = currentConnection;
			int p = embackupname.ReverseFind('.');
			if ((p == -1) || embackupname.Find('\\', p) != -1)
				p = embackupname.GetLength();
			CString emcode;
			static int emnum;
			emcode.Format("-emergency%ld", ++emnum);
			embackupname.Insert(p, emcode);
		}
		HRESULT hr = S_OK;
		if (saveMode == SaveAndBringUpMessageBox || saveMode == DoTheSaveOnly) {
#pragma warning(disable: 4310) // cast truncates constant value
			hr = mgaProject->Save(PutInBstr(embackupname), VARIANT_TRUE);
#pragma warning(default: 4310) // cast truncates constant value
			emergencyBackupName.Empty();
		}
		if (proj_type_is_xmlbackend) {
			if (saveMode != DoTheSaveOnly)
				emergencySaveMsg.LoadString(IDS_EMERGENCY_XML);
		} else {
			if (saveMode != DoTheSaveOnly)
				emergencySaveMsg.FormatMessage(IDS_EMERGENCY_PROJ, (hr == S_OK)? "has" : "may have", embackupname);

			m_RecentProjectList.Add(embackupname);
			m_RecentProjectList.WriteList();
		}
	} else {
		if (saveMode != DoTheSaveOnly)
			emergencySaveMsg.LoadString(IDS_EMERGENCY_NOPROJ);
	}
	if (saveMode == SaveAndBringUpMessageBox) {
		AfxMessageBox(emergencySaveMsg);
	} else if (saveMode == BringUpDialogOnly) {
		emergencyBackupName = embackupname;
		CString miniDumpMsg;
		miniDumpMsg.LoadString(IDS_CRASHDUMP_INFO);
		EmergencySaveDlg cdl(NULL);
		cdl.SetStrings(emergencySaveMsg, miniDumpMsg);
		if (cdl.DoModal() == IDOK) {
			return cdl.ShouldWriteMiniDump();
		}
		return FALSE;
	}
	return TRUE;
}

int CGMEApp::Run()
{
	Gdiplus::GdiplusStartupInput  gdiplusStartupInput;
	Gdiplus::GdiplusStartupOutput  gdiplusStartupOutput;
	ULONG_PTR gdiplusToken;
	ULONG_PTR gdiplusHookToken;

	// Tihamer: Initializing GDI+
	// See "Special CWinApp Services" MSDN topic http://msdn.microsoft.com/en-us/library/001tckck.aspx
	gdiplusStartupInput.SuppressBackgroundThread = TRUE;
	VERIFY(Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, &gdiplusStartupOutput) == Gdiplus::Ok);
	gdiplusStartupOutput.NotificationHook(&gdiplusHookToken);
	graphics.Initialize();

	if(bNoProtect) {
		return CWinApp::Run();
	} else {
		__try {
			return CWinApp::Run();
		}
		__except(ExceptionHandler::UnhandledExceptionFilterOfMain(GetExceptionCode(), GetExceptionInformation())) {
			EmergencySave(DoTheSaveOnly);

			// Modified by Peter:let's exit after emergency event
			abort_on_close = true;
			BeginWaitCursor();
			if(CGMEDoc::theInstance) {
				CGMEDoc::theInstance->OnCloseDocument(true);
			}
			EndWaitCursor();

			// Closing GDI+
			Gdiplus::GdiplusShutdown(gdiplusToken);
			return -1;
			// End by Peter
		}
	}
	// Closing GDI+
	graphics.Uninitialize();
	gdiplusStartupOutput.NotificationUnhook(gdiplusHookToken);
	Gdiplus::GdiplusShutdown(gdiplusToken);
}

/////////////////////////////////////////////////////////////////////////////
// CGMEApp Autosave
void CGMEApp::Autosave()
{

	if(mgaProject == NULL || (0&&!proj_type_is_mga) || (!autosaveEnabled)) {
		// The KillTimer function does not remove WM_TIMER messages 
		// already posted to the message queue ...
		CGMEEventLogger::LogGMEEvent("WARNING: CGMEApp::Autosave was called with no active project or autosave disabled.\r\n");
		return;
	}

	// Figure out the filename
	CString conn;
	if (autosaveUseDir) {
		int p = currentConnection.ReverseFind('\\');
		CString fname = currentConnection.Mid(p + 1);

		conn = CString("MGA=") + autosaveDir + CString("\\") + fname + GME_AUTOSAVE_EXTENSION;
	}
	else {
		conn = currentConnection + GME_AUTOSAVE_EXTENSION;
	}

	// autosave in case of xmlbackend means saving into the sourcecontrol
	if( proj_type_is_xmlbackend)
		conn = currentConnection;

	// Check if in transaction
	bool inTrans;
	try {
		long status;
		COMTHROW(mgaProject->get_ProjectStatus(&status));
		inTrans = (status & 0x08L) != 0;
	}
	catch(hresult_exception &) {
		// Safe presumption
		inTrans = true;
	}

	if (inTrans) {
		CGMEEventLogger::LogGMEEvent("WARNING: CGMEApp::Autosave failed " + 
			conn + ". We are in transaction.\r\n");
		return;
	}

	// Save the project
	try {
#pragma warning(disable: 4310) // cast truncates constant value
		COMTHROW(mgaProject->Save(CComBSTR(conn), VARIANT_TRUE));
#pragma warning(default: 4310) // cast truncates constant value
		CGMEEventLogger::LogGMEEvent("CGMEApp::Autosave succeeded " + 
			conn + "\r\n");
	}
	catch(hresult_exception &e) {
		CGMEEventLogger::LogGMEEvent("WARNING: CGMEApp::Autosave failed " + 
			conn + " " + e.what() + "\r\n");
	}
}


/////////////////////////////////////////////////////////////////////////////
// CGMEApp MGA project management


void CGMEApp::CloseProject(bool updateStatusBar)
{

	CWaitCursor wait;
	
	if(CGMEDataSource::myData) // it is true when object copied to the clipboard from the view
		OleFlushClipboard();
	
	if( CMainFrame::theInstance != NULL ) {
		CMainFrame::theInstance->StopAutosaveTimer();
		CMainFrame::theInstance->SetPartBrowserMetaModel(NULL);
		CMainFrame::theInstance->SetPartBrowserBg(::GetSysColor(COLOR_APPWORKSPACE));
	}

	if( CGMEBrowser::theInstance != NULL )
		CGMEBrowser::theInstance->CloseProject();
	
	if(CGMEObjectInspector::theInstance!=NULL)
		CGMEObjectInspector::theInstance->CloseProject();

	if(CGMESearch::theInstance!=NULL)
		CGMESearch::theInstance->CloseProject();



	if( guiMetaProject != NULL )
	{
		delete guiMetaProject;
		guiMetaProject = NULL;
	}

	mgaMetaProject = NULL;
	UpdateComponentLists();

#pragma warning(disable: 4310) // cast truncates constant value
	if( mgaProject != NULL ) {
		mgaClient = NULL;
		if(mgaProject->Close(abort_on_close ? VARIANT_TRUE : VARIANT_FALSE) != S_OK) {
			AfxMessageBox(CString("Error occured ") + (abort_on_close ? "aborting" : "closing") + " the project");
		}
		mgaProject.Release();
	}
#pragma warning(default: 4310) // cast truncates constant value
	

	if(updateStatusBar) {
		CMainFrame::theInstance->WriteStatusParadigm("-");
		CMainFrame::theInstance->WriteStatusMode("EDIT");
		CMainFrame::theInstance->WriteStatusZoom(100);
	}
	projectName.Empty();
	ChangedProjectConnStrings();

	if(CGMEDoc::theInstance)
		CGMEDoc::theInstance->SetTitle("");
	if(CMainFrame::theInstance) {
		CMainFrame::theInstance->SetTitle(m_pszAppName);
		CMainFrame::theInstance->UpdateTitle(0);//WAS: "" .By passing 0 instead of "" we won't get title such as "GME-" after a project was closed
	}
}


void CGMEApp::ChangedProjectConnStrings() {
	if(!mgaProject) {  // project closed
		paradigmDir.Empty();
		projectDir.Empty();
		proj_type_is_mga = false;
        proj_type_is_xmlbackend = false;
		return;
	}
	CString conn, metaconn;
	CComBstrObj cc;
	conn = cc;
	COMTHROW(mgaProject->get_ProjectConnStr(PutOut(cc)));
	conn = cc;
	cc.Empty();
	COMTHROW(mgaProject->get_ParadigmConnStr(PutOut(cc)));
	metaconn = cc;
	if(!conn.IsEmpty()) {
		TCHAR cd[200];
		GetCurrentDirectory(200, cd);
		projectDir = cd;
		if (conn.Find("MGA=") == 0) {
			proj_type_is_mga = true;
			int epos = conn.ReverseFind('\\');
			if(epos >= 4) {
				projectDir = conn.Mid(4, epos-4);
				if(projectDir.IsEmpty()) projectDir= '\\';
				SetCurrentDirectory(projectDir);
			}
		}
		else proj_type_is_mga = false;

        if( conn.Find("MGX=") == 0 ) 
            proj_type_is_xmlbackend = true;
        else
            proj_type_is_xmlbackend = false;
	}       
	if(!metaconn.IsEmpty()) {
		if (metaconn.Find("MGA=") == 0) {
			int epos = metaconn.ReverseFind('\\');
			if(epos >= 4) {
				paradigmDir = metaconn.Mid(4, epos-4);
				if(paradigmDir.IsEmpty()) paradigmDir= '\\';
			}
		}
	}
}


// throws exceptions!!
void CGMEApp::UpdateProjectName() {
	if( mgaProject == NULL ) {
		projectName.Empty();
	}
	else {


		CComObjPtr<IMgaTerritory> terry;
		COMTHROW(mgaProject->CreateTerritory(NULL, PutOut(terry)) );
		CComBSTR nm;
	
		MSGTRY
		{
			COMTHROW(mgaProject->BeginTransaction(terry,TRANSACTION_GENERAL));
			COMTHROW(mgaProject->get_Name(&nm));
			COMTHROW(mgaProject->CommitTransaction());
		}
		MSGCATCH("Error getting project name", mgaProject->AbortTransaction())

		CopyTo(nm,projectName);
	}

	if(CGMEDoc::theInstance)
		CGMEDoc::theInstance->SetTitle(projectName);
	CMainFrame::theInstance->UpdateTitle(projectName);
}

void CGMEApp::FindConstraintManager() {
		CComPtr<IMgaComponents> comps;
		COMTHROW( mgaProject->get_AddOnComponents(&comps));
		MGACOLL_ITERATE(IMgaComponent, comps) {
			CComBSTR name;
			COMTHROW(MGACOLL_ITER->get_ComponentName(&name));
			if(name == "ConstraintManager") {
				mgaConstMgr = CComQIPtr<IMgaComponentEx>(MGACOLL_ITER); 
#pragma warning(disable: 4310) // cast truncates constant value
				COMTHROW(mgaConstMgr->put_InteractiveMode(VARIANT_TRUE));
#pragma warning(default: 4310) // cast truncates constant value
				break;
			}
		} MGACOLL_ITERATE_END;
}


void CGMEApp::UpdateComponentToolbar()
{
		if(!mgaMetaProject) return;

		// Updating the Component toolbar
		CComPtr<IMgaRegistrar> registrar;
		if(registrar.CoCreateInstance(L"Mga.MgaRegistrar") != S_OK) return;

		if(!CMainFrame::theInstance) return;
		CComponentBar &componentBar = CMainFrame::theInstance->m_wndComponentBar;


		// Removing the add-in and plug-in buttons
		const CObList &componentButtons = componentBar.GetAllButtons();
		for(POSITION pos = componentButtons.GetHeadPosition(); pos!= NULL; )
		{
			const CMFCToolBarButton* pCurrent = (const CMFCToolBarButton*) componentButtons.GetNext(pos); 
			if(pCurrent->m_bUserButton == TRUE)
			{
				componentBar.RemoveButton(componentBar.ButtonToIndex(pCurrent));
			}
		}

		
		// Traversing  the plugins and interpreters
		for(int i = 0; i < plugins.GetSize() + interpreters.GetSize(); ++i)	
		{        				 						
			// Querying component name
			CComBSTR componentName;
			if(i < plugins.GetSize()) // if it is a plugin
			{
				componentName = plugins[i];
			}
			else					// if it is an interpreter
			{
				componentName = interpreters[i-plugins.GetSize()];
			}

			// Obtaining ToolTip
			HRESULT errCode;
			CString toolTip;
			errCode = registrar->get_ComponentExtraInfo(REGACCESS_PRIORITY, componentName, CComBSTR("Tooltip"), PutOut(toolTip));
			if(errCode != S_OK || toolTip.IsEmpty())
			{
				toolTip = componentName;
			}
            if(i < plugins.GetSize())
			{
				pluginTooltips.Add(toolTip);
			}
            else
			{
				interpreterTooltips.Add(toolTip);
			}

			// Querying icon information
			CString iconInfo;
			errCode = registrar->get_ComponentExtraInfo(REGACCESS_PRIORITY, componentName, CComBSTR("Icon"), PutOut(iconInfo));
			if(errCode != S_OK || iconInfo.IsEmpty()) 
			{
				continue;
			}
			
			// Loading icon
			HICON hIcon = NULL; //, hictofree = NULL;
			int commaPos;
			HMODULE hModule = NULL;
			CComPtr<IMgaComponent> loadedConmponent; // GetModuleHandle works with loaded DLL only
			if((commaPos = iconInfo.Find(',')) >= 0)  //Format:   <modulename>,<resourceID>
			{
				if(commaPos)  // module name present;
				{
					hModule = GetModuleHandle(iconInfo.Left(commaPos));
					if(!hModule) 
					{
						loadedConmponent.CoCreateInstance(componentName);
						hModule = GetModuleHandle(iconInfo.Left(commaPos));
					}
				}
				else // No module name provided, 
				{
					CString modulePath;
					registrar->get_LocalDllPath(componentName, PutOut(modulePath));			
					if(modulePath) 
					{
						hModule = ::GetModuleHandle(modulePath);
						if(!hModule)
						{
							loadedConmponent.CoCreateInstance(componentName);
							hModule = ::GetModuleHandle(modulePath);
						}
						DWORD test = ::GetLastError();
						TRACE1("%ul",test);
					}
				}
			}

			if( hModule != NULL ) 
			{
				hIcon = (HICON)::LoadImage(hModule, iconInfo.Mid(commaPos+1), IMAGE_ICON, 0,0, LR_DEFAULTCOLOR);
			}
			else 
			{				  
				// simple .ico file with path
				hIcon =(HICON)LoadImage(NULL, iconInfo, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
			}
			
			// If icon is not found either in the DLL or a standalone file
			if(!hIcon) 
			{
				hIcon = LoadIcon(IDI_COMPNOTFOUND); // Displaying component not found icon
			}


			//Adding button icon
			CMFCToolBarImages* pToolBarImages = componentBar.GetImages();
			int nIndex = pToolBarImages->AddIcon(hIcon);

			// Adding button
			int commandID = (i< plugins.GetSize()) ? ID_FILE_RUNPLUGIN1 + i:ID_FILE_INTERPRET1 + i-plugins.GetSize();
			CMFCToolBarButton toolBarButton(commandID,nIndex, componentName + '\n'+ toolTip,TRUE);			
			componentBar.InsertButton(toolBarButton);
		}		
}


void CGMEApp::UpdateComponentLists(bool restart_addons) {
		ClearDisabledComps();	
		plugins .RemoveAll();
        pluginTooltips.RemoveAll();
		interpreters.RemoveAll();
        interpreterTooltips.RemoveAll();
		CStringArray tempaddons; tempaddons.Copy(addons);
		addons.RemoveAll();
		mgaConstMgr = NULL;
		if(mgaMetaProject) {
			CComBSTR b;            
			COMTHROW(mgaMetaProject->get_Name(&b));
			CComPtr<IMgaRegistrar> reg;
			COMTHROW(reg.CoCreateInstance(CComBSTR("Mga.MgaRegistrar")));
			{
				CComVariant v;
				COMTHROW(reg->get_AssociatedComponents(b, COMPONENTTYPE_PLUGIN, REGACCESS_BOTH, &v));
				CopyTo(v, plugins);			    
			}
			{
				CComVariant v;
				COMTHROW(reg->get_AssociatedComponents(b, COMPONENTTYPE_INTERPRETER, REGACCESS_BOTH, &v));
				CopyTo(v, interpreters);
			}
			{
				CComVariant v;
				COMTHROW(reg->get_AssociatedComponents(b, COMPONENTTYPE_ADDON, REGACCESS_BOTH, &v));

				CopyTo(v, addons);
				if(restart_addons) {
					bool redo = false;
					if(tempaddons.GetSize() != addons.GetSize()) redo = true;
					else {
						for(int j = 0 ; j < tempaddons.GetSize(); j++) {
							if(addons[j].Compare(tempaddons[j])) {
								redo = true;
								break;
							}
						}
					}
					if(redo && AfxMessageBox("AddOn configuration has changed.\nRestart addons?", MB_YESNO) == IDYES) {
						COMTHROW(mgaProject->EnableAutoAddOns(VARIANT_FALSE));
#pragma warning(disable: 4310) // cast truncates constant value
						COMTHROW(mgaProject->EnableAutoAddOns(VARIANT_TRUE));
#pragma warning(default: 4310) // cast truncates constant value
					}
				}
			}
			// access constraint mgr
			FindConstraintManager();
	
		}
		dynmenus_need_refresh = true;
		UpdateComponentToolbar();
}

void CGMEApp::UpdateDynMenus(CMenu *filemenu)   {
	if(!dynmenus_need_refresh) return;
	ASSERT(filemenu);
	for(UINT idx = 0; idx < filemenu->GetMenuItemCount(); idx++) {
		CString label;
		filemenu->GetMenuString(idx,label,MF_BYPOSITION);
		if(!label.CompareNoCase("R&un Plug-In")) {
			filemenu->DeleteMenu(idx,MF_BYPOSITION);
			CMenu pluginmenu;
			pluginmenu.CreatePopupMenu();
			for(int i = 0; i < plugins.GetSize(); ++i)	{
				pluginmenu.AppendMenu(MF_ENABLED, ID_FILE_RUNPLUGIN1 + i,pluginTooltips[i]);
			}
			filemenu->InsertMenu(idx,
						plugins.GetSize() ? MF_BYPOSITION|MF_POPUP|MF_ENABLED: MF_BYPOSITION|MF_POPUP|MF_GRAYED,
						(UINT)pluginmenu.Detach(),label);
		}
		if(!label.CompareNoCase("Run In&terpreter")) {
			filemenu->DeleteMenu(idx,MF_BYPOSITION);
			CMenu pluginmenu;
			pluginmenu.CreatePopupMenu();
			for(int i = 0; i < interpreters.GetSize(); ++i)	{
				pluginmenu.AppendMenu(MF_ENABLED, ID_FILE_INTERPRET1 + i,interpreterTooltips[i]);
			}
			filemenu->InsertMenu(idx,
						interpreters.GetSize() ? MF_BYPOSITION|MF_POPUP|MF_ENABLED: MF_BYPOSITION|MF_POPUP|MF_GRAYED,
						(UINT)pluginmenu.Detach(),label);
		}
	}
	dynmenus_need_refresh = false;
}


// throws exceptions!!
void CGMEApp::AfterOpenOrCreateProject(const CString &conn) {
	UpdateProjectName();
	if( mgaProject != NULL ) {
		abort_on_close = false;
// get meta
		COMTHROW( mgaProject->get_RootMeta(&mgaMetaProject) );
		UpdateComponentLists();

// create guimetaproject
		ASSERT( guiMetaProject == NULL );
		guiMetaProject = new CGuiMetaProject(mgaMetaProject);
		CMainFrame::theInstance->WriteStatusParadigm(guiMetaProject->displayedName);
		CMainFrame::theInstance->SetTitle(guiMetaProject->displayedName);
		UpdateProjectName();

// Register OLE Server / MGA Client
		CGMEOLEApp *oleApp = ((CMainFrame*)m_pMainWnd)->mGmeOleApp;
		CComBSTR clientName(OLESTR("GME.Application"));
		COMTHROW(mgaProject->RegisterClient(clientName, oleApp->GetIDispatch(FALSE), &mgaClient)); // mgaClient increments the refcount of oleApp->idispatch by 1

		((CMainFrame*)m_pMainWnd)->setMgaProj();

// notify object inspector
		ASSERT(CGMEObjectInspector::theInstance!=NULL);
		CGMEObjectInspector::theInstance->SetProject(mgaProject);

// notify Part Browser
		ASSERT(CGMEPartBrowser::theInstance!=NULL);
		CGMEPartBrowser::theInstance->SetProject(mgaProject);

// by swapping the order of SetProject (first ObjectInspector, then Browser), 
// the user will see the properties of the initally selected project at once
// notify browser
		ASSERT( CGMEBrowser::theInstance != NULL );
		CGMEBrowser::theInstance->SetProject(mgaProject);

// notify search control
		ASSERT(CGMESearch::theInstance!=NULL);
		CGMESearch::theInstance->SetProject(mgaProject);


// change dir
		ChangedProjectConnStrings();
// record connection name
		currentConnection = conn;
		m_RecentProjectList.Add(conn);
		m_RecentProjectList.WriteList();
		if (!CGMEDoc::theInstance) {
			CWinApp::OnFileNew();
		}
// start autosave
		if (autosaveEnabled) {
			CMainFrame::theInstance->StartAutosaveTimer(autosaveFreq);
		}
	}
}


static int guidcmp(VARIANT &qGUID, VARIANT &pGUID)	{
	GUID g1, g2;
	CopyTo(qGUID, g1);
	CopyTo(pGUID, g2);
	return memcmp(&g1, &g2, sizeof(g1));
}

static int versioncmp(CComBSTR &qVer, CComBSTR &pVer) {
	CString q(qVer);
	CString p(pVer);

	if ((!p.IsEmpty()) && (!q.IsEmpty())) {
		return p.Compare(q);
	}
	return 1;
}


bool DiagnoseParadigm(CString metaname, bool syscheck = false) {
	CComPtr<IMgaRegistrar> reg;
	try {
		HRESULT hr = reg.CoCreateInstance(CComBSTR("Mga.MgaRegistrar"));
		if(hr != S_OK) {
			throw CString("Cannot create the registrar component\n"
						  "We recommend you to reinstall GME");
		}
		CComBSTR conn;
		CComVariant guid;
		hr = reg->QueryParadigm(CComBSTR(metaname), &conn, &guid, 
			syscheck ? REGACCESS_SYSTEM : REGACCESS_PRIORITY);
		if(hr != S_OK) {
			throw CString("Cannot access registry info for paradigm " + metaname +
						  "\nWe recommend you remove and re-register the paradigm");
		}
		CComObjPtr<IMgaMetaProject> paradigm;
		hr =  paradigm.CoCreateInstance(OLESTR("MGA.MgaMetaProject"));
		if(hr != S_OK) {
			throw CString("Cannot create the meta component\n"
						  "We recommend you reinstall GME");
		}

		hr = paradigm->Open(conn);

		if(hr != S_OK) {
			throw CString("Cannot open the paradigm " + metaname + "\n"
						  "Probable cause is file non-existence,\n"
						  "insufficient access, or format error\n"
						  "Connection string: " + CString(conn));
		}


		CComBSTR parname;
		CComVariant gguid;
		hr = paradigm->get_Name(&parname);
		if(hr == S_OK) paradigm->get_GUID(&gguid);
		hr |= paradigm->Close();

		if(hr != S_OK) {
			throw CString("Cannot read the paradigm " + metaname + "\n"
						  "Probable cause is file format error\n"
						  "Connection string: " + CString(conn));
		}
		if(!( parname == CComBSTR( (LPCTSTR) metaname))) {
			throw CString("The paradigm opened '" + CString(parname) + "'\n"
		 				  "differs from the requested paradigm '"+ metaname + "'\n"
						  "We recommend you unregister '" + metaname + "'\n"
						  "Connection string: " + CString(conn));

		}

		CComBstrObj parg1, parg2;
		GUID g;
		CopyTo(gguid, g);
		CopyTo(g, parg1);
		CopyTo(guid, g);
		CopyTo(g, parg2);
		if(parg1 != parg2) {
			throw CString("The GUID in paradigm '" + CString(parname) + "'\n"
						  "{" + CString(parg1) + "}\n"
		 				  "differs from the requested GUID for '"+ metaname + "'\n"
						  "{" + CString(parg2) + "}\n"
						  "We recommend you unregister '" + metaname + "'\n"
						  "Connection string: " + CString(conn));
		}
	} catch( CString &c) {
		if(!syscheck) {
			AfxMessageBox(c); 
			CComBSTR cc; CComVariant gg;
			if(reg && E_NOTFOUND != reg->QueryParadigm(CComBSTR(metaname), &cc, &gg, REGACCESS_SYSTEM)) {
				if(DiagnoseParadigm(metaname, true)) {
					AfxMessageBox("SYSTEM registry for '" + metaname + "' is correct\n"
								"We recommend you remove the USER registration for " + metaname);
				}
				else {
					AfxMessageBox("SYSTEM registry for '" + metaname + "' is also incorrect\n"
								"We recommend you reinstall the paradigm.");
				}
			}
		}
		return false;
	}
	catch(...) {
		return false;
	}
	return true;
}



void CGMEApp::OpenProject(const CString &conn) {

	MSGTRY
	{
		CWaitCursor wait;

		ASSERT( mgaProject == 0 );
		COMTHROW( mgaProject.CoCreateInstance(OLESTR("Mga.MgaProject")) );

		VARIANT_BOOL readable_only;

#pragma warning(disable: 4310) // cast truncates constant value
		COMTHROW( mgaProject->EnableAutoAddOns(VARIANT_TRUE));
#pragma warning(default: 4310) // cast truncates constant value
		HRESULT hr = mgaProject->Open(PutInBstr(conn), &readable_only);
		if(hr != S_OK) {
			CComBSTR parn;
			CComBSTR parv;
			long version;
			CComVariant parg;
			VARIANT_BOOL ro_mode;
			if( conn.Left(5) == "MGX=\"")
			{
				if( E_FILEOPEN == hr) // multi user project could not be open
					consoleMessage( "Could not open project!", MSG_ERROR);
				else if( E_UNKNOWN_STORAGE == hr) { } // so additional comment in this case
				CloseProject();
				return; // ensures no more exception handlers or explanatory messages (or QueryProjectInfo calls)
			}

			if(S_OK != mgaProject->QueryProjectInfo(PutInBstr(conn), &version, &parn, &parv, &parg, &ro_mode)) {
				AfxMessageBox("Cannot query project information. Possible cause: missing/corrupt project file or database");
				COMTHROW(hr);
			}
			while(hr) {
				CString msg;
				CComVariant guidpar;
				CString newparname;
				bool tryit = false;

				if(hr == E_MGA_MODULE_INCOMPATIBILITY) {
					msg = "WARNING: The project data is not in the current MGA format\n"
						"Do you want to upgrade it?";
					if (AfxMessageBox(msg ,MB_OKCANCEL) == IDOK) {
						tryit = true;
					}
				}
				if(hr == E_MGA_PARADIGM_INVALID) {
					msg = "WARNING: Project could not access its original version of\n"
						"paradigm '" + CString(parn) + "'\n"
						"Do you want to try with the current version of the paradigm?";
					if (AfxMessageBox(msg ,MB_OKCANCEL) == IDOK) {
						guidpar = true;
						tryit = true;
					}
				}
				if(hr == E_MGA_PARADIGM_NOTREG) {
					msg = "WARNING: Project could not access its paradigm '" + CString(parn) + "'\n" 
						" (Eg.: In GME3 the MetaGME2000 paradigm was renamed to MetaGME)\n"
						"Do you want to open it with an other registered paradigm ?";
					if (AfxMessageBox(msg ,MB_OKCANCEL) == IDOK) {
					
						CComObjPtr<IMgaLauncher> launcher;
						COMTHROW( launcher.CoCreateInstance(CComBSTR(L"Mga.MgaLauncher")) );
						if (SUCCEEDED(launcher->MetaDlg(METADLG_NONE))) {
							guidpar = true;
							tryit = true;
							newparname.Empty();
							COMTHROW( launcher->get_ParadigmName(PutOut(newparname)) );
							tryit = !newparname.IsEmpty(); // zolmol
						}
					}
				}
				if(hr == E_MGA_META_INCOMPATIBILITY && (parv.Length() > 0)) {
					msg = "WARNING: Versioned project is not compatible with the paradigm '" + CString(parn) + "'\n" 
						" (Eg.: Same version string was assigned to incompatible paradigms)\n"
						"Do you want to open it based on the paradigm GUID?";
					if (AfxMessageBox(msg ,MB_OKCANCEL) == IDOK) {
						guidpar = parg;
						tryit = true;
						newparname = parn;
					}
				}
				if(tryit) {
					hr = mgaProject->OpenEx(PutInBstr(conn), CComBSTR(newparname), guidpar);
					if(hr == E_MGA_PARADIGM_NOTREG || hr == E_MGA_PARADIGM_INVALID) {
						DiagnoseParadigm(CString(parn));
					}
				}
				else break;
			}
			if(hr == E_MGA_COMPONENT_ERROR) {
				AfxMessageBox("ERROR: Some automatic addon components could not start up\n");
			}
			COMTHROW(hr);
		}

		if(readable_only != VARIANT_FALSE) {
			AfxMessageBox("WARNING: Project file is read-only\nChange file access or use Save As to save your work");
		}
		else {
			CComVariant g, g2;
			CComBSTR pname; 
			CComBSTR pver, pver2;
			{
				CComPtr<IMgaTerritory> t;
				COMTHROW(mgaProject->CreateTerritory(NULL, &t, NULL));
				COMTHROW(mgaProject->BeginTransaction(t, TRANSACTION_READ_ONLY));
				COMTHROW(mgaProject->get_MetaName(&pname));
				COMTHROW(mgaProject->get_MetaGUID(&g));
				COMTHROW(mgaProject->get_MetaVersion(&pver));
				// COMTHROW(mgaProject->AbortTransaction()); PETER: Why abort ?
				COMTHROW(mgaProject->CommitTransaction());
				CComPtr<IMgaRegistrar> mgareg;
				COMTHROW(mgareg.CoCreateInstance(OLESTR("MGA.MgaRegistrar")));
				CComBSTR connstr;
				COMTHROW(mgareg->QueryParadigm(pname, &connstr, &g2, REGACCESS_PRIORITY));
				mgareg->VersionFromGUID(pname, g2, &pver2, REGACCESS_PRIORITY);
			}
			if(guidcmp(g, g2) && versioncmp(pver, pver2)) {
				int answer = AfxMessageBox("The paradigm used to open this file is not the current version\n"
								"Do you want to upgrade to the current paradigm?"	,MB_YESNO);
				if(answer == IDYES) {
					COMTHROW(mgaProject->Close());

					// PETER: Create new MgaProject COM object (workaround MGA addon bug)
					mgaProject.Release();
					COMTHROW( mgaProject.CoCreateInstance(OLESTR("Mga.MgaProject")) );
					#pragma warning(disable: 4310) // cast truncates constant value
					COMTHROW( mgaProject->EnableAutoAddOns(VARIANT_TRUE));
					#pragma warning(default: 4310) // cast truncates constant value
					
					HRESULT hr = mgaProject->OpenEx(PutInBstr(conn), pname, g2);
					if(hr == E_MGA_PARADIGM_NOTREG || hr == E_MGA_PARADIGM_INVALID) {
						AfxMessageBox("Paradigm error");
						DiagnoseParadigm(CString(pname));
					}
					else if(hr != S_OK) {
						AfxMessageBox("Upgrade failed, probably due to incompatibility.\n"
									   "You can probably reopen the file without upgrade,\n"
									   "and use the 'Upgrade through XML' function later.");
					}
					else readable_only = false;
					COMTHROW(hr);
				}
			}	
		}
		AfterOpenOrCreateProject(conn);
	}
	MSGCATCH("Could not open project", CloseProject())
	
	UpdateProjectName();

}



void CGMEApp::CreateProject(const CString &metaname, const CString &conn)
{
	CString msg;
	try
	{
		CWaitCursor wait;

		// create the project
		msg = "Fatal error while initializing project";
		ASSERT( mgaProject == 0 );
		COMTHROW( mgaProject.CoCreateInstance(L"Mga.MgaProject") );
		ASSERT( mgaProject != NULL );

#pragma warning(disable: 4310) // cast truncates constant value
		COMTHROW( mgaProject->EnableAutoAddOns(VARIANT_TRUE));
#pragma warning(default: 4310) // cast truncates constant value
		msg = "Could not create project";
		HRESULT hr = mgaProject->Create(PutInBstr(conn), PutInBstr(metaname)) ;
	    if(hr == E_MGA_PARADIGM_NOTREG || hr == E_MGA_PARADIGM_INVALID) {
			TCHAR buf[200];
		    sprintf(buf, "Could not open current version of paradigm %s", 
				metaname);

			AfxMessageBox(buf);
			DiagnoseParadigm(metaname);
		}
	    if(hr == E_MGA_COMPONENT_ERROR) {
			AfxMessageBox("ERROR: Some automatic addon components could not start up\n");
		}
		if( hr == E_UNKNOWN_STORAGE && conn.Left(5) == "MGX=\"") {
			CloseProject();
			return; // no more exception handler explanatory messages
		}
	    COMTHROW(hr);

		AfterOpenOrCreateProject(conn);
	}
	MSGCATCH("Could not create project", CloseProject())
}


void CGMEApp::SaveProject(const CString &conn) {
	if( mgaProject != NULL ) {
		HRESULT hr = mgaProject->Save(CComBSTR(conn));
		if(hr != S_OK) {
			AfxMessageBox("ERROR: Could not save project\nCheck access permissions");
		}
	}

	if ((!conn.IsEmpty()) && (currentConnection != conn)) {
		ChangedProjectConnStrings();
		currentConnection = conn;
		m_RecentProjectList.Add(conn);
		m_RecentProjectList.WriteList();
	}
}	



// ********************************************************************************************


void CGMEApp::GetSettings()
{
	MSGTRY
	{
		CComObjPtr<IMgaRegistrar> registrar;
		COMTHROW( registrar.CoCreateInstance(L"Mga.MgaRegistrar") );

		// Icons
		CComBSTR bstr;
		COMTHROW( registrar->get_IconPath(REGACCESS_BOTH,&bstr));
		CopyTo(bstr,bitmapPath);

		// Multiview
		VARIANT_BOOL enabledmv;
		COMTHROW( registrar->get_ShowMultipleView(REGACCESS_USER, &enabledmv) );
		multipleView = (enabledmv != VARIANT_FALSE);

		// Autosave
		VARIANT_BOOL autosaveenable;
		COMTHROW( registrar->get_AutosaveEnabled(REGACCESS_USER, &autosaveenable) );
		autosaveEnabled = (autosaveenable == VARIANT_FALSE) ? FALSE : TRUE;

		long autosavefreq;
		COMTHROW( registrar->get_AutosaveFreq(REGACCESS_USER, &autosavefreq) );
		autosaveFreq = (int)autosavefreq;

		VARIANT_BOOL autosaveusedir;
		COMTHROW( registrar->get_AutosaveUseDir(REGACCESS_USER, &autosaveusedir) );
		autosaveUseDir = (autosaveusedir == VARIANT_FALSE) ? 0 : 1;

		COMTHROW( registrar->get_AutosaveDir(REGACCESS_USER, PutOut(autosaveDir)) );

		//Event Logging
		VARIANT_BOOL enablelogging;
		COMTHROW( registrar->get_EventLoggingEnabled(REGACCESS_USER, &enablelogging) );
		if(enablelogging != VARIANT_FALSE)
		{
			CGMEEventLogger::initialize();
			CGMEEventLogger::LogGMEEvent("CGMEApp::GetSettings() Event Logging Enabled\r\n");
		}
		else
		{
			CGMEEventLogger::LogGMEEvent("CGMEApp::GetSettings() Event Logging Disabled\r\n");
			CGMEEventLogger::StopLogging();
		}

		
		// Autorouter
		VARIANT_BOOL labelavoidance;
		COMTHROW( registrar->get_LabelAvoidance(REGACCESS_USER, &labelavoidance) );
		labelAvoidance = (labelavoidance != VARIANT_FALSE);

		// Default Zoom Level
		CComBSTR bstr_zl;
		COMTHROW( registrar->GetDefZoomLevel( REGACCESS_USER, &bstr_zl));
		if( bstr_zl)
			CopyTo( bstr_zl, defZoomLev);

		// SendMouseOver notification
		VARIANT_BOOL send_mouse_over;
		COMTHROW( registrar->GetMouseOverNotify(REGACCESS_USER, &send_mouse_over));
		mouseOverNotify = ( send_mouse_over != VARIANT_FALSE);

		// Real number format string
		CComBSTR bstr_fmt;
		COMTHROW( registrar->GetRealNmbFmtStr( REGACCESS_USER, &bstr_fmt));
		if( bstr_fmt)
			CopyTo( bstr_fmt, realFmtStr);

		// History Maintained?
		VARIANT_BOOL history_maintained;
		COMTHROW( registrar->GetNavigation( REGACCESS_USER, &history_maintained));
		maintainHistory = ( history_maintained != VARIANT_FALSE);
	}
	MSGCATCH("Error while trying to get program settings",;);
	if(CGMEDoc::theInstance) {
		if (autosaveEnabled) {
			CMainFrame::theInstance->StartAutosaveTimer(autosaveFreq);
		}
		else {
			CMainFrame::theInstance->StopAutosaveTimer();
		}
		CGMEDoc::theInstance->ResetAllViews();
	}
}

LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{
	HKEY hKey;
    LONG lResult = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hKey); 
  
    if( lResult == ERROR_SUCCESS)
	{
         long lDataSize = MAX_PATH;
		TCHAR data[MAX_PATH];
  
		RegQueryValue( hKey, NULL, data, &lDataSize);
		lstrcpy( retdata,data);
		RegCloseKey( hKey);
    }
  
    return lResult;
}
  
HINSTANCE GotoURL(LPCTSTR url, int showcmd)
{
	TCHAR key[MAX_PATH + MAX_PATH];
  
    // First try ShellExecute()
    HINSTANCE hResult = ShellExecute( NULL, _T("open"), url, NULL,NULL, showcmd);
    //HINSTANCE hResult;
    // If it failed, get the .htm regkey and lookup the program
    if((UINT)hResult <= HINSTANCE_ERROR)
	{
		if( GetRegKey( HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS)
		{
             lstrcat( key, _T("\\shell\\open\\command")); 
  
             if( GetRegKey( HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS)
			 {
				TCHAR *pos;
                 pos = _tcsstr( key, _T("\"%1\"")); 
  
                 if( pos == NULL)
				 {
					// No quotes found
                    pos = strstr( key, _T("%1")); // Check for % 1, without quotes
                    if( pos == NULL)    // No  parameter at all...
                         pos = key+lstrlen( key)-1;
                     else
                         *pos = '\0';    //  Remove the parameter
                 }
                 else
                     *pos = '\0';
					// Remove the parameter
  
                 lstrcat(pos, _T(" "));
                 lstrcat(pos, url);
  
                 hResult = (HINSTANCE)WinExec( key,showcmd);
             }
         }
	}
  
     return hResult;
}

/////////////////////////////////////////////////////////////////////////////
// CGMEApp message handlers

// *******************************************************************************
// *******************************************************************************
//								FILE
// *******************************************************************************
// *******************************************************************************


void CGMEApp::OnFileOpen() 
{
	CMgaOpenDlg dlg(CMgaOpenDlg::OpenDialog);
	CString conn = dlg.AskConnectionString(false);

	CGMEEventLogger::LogGMEEvent("CGMEApp::OnFileOpen "+conn+"\r\n");

	if( conn.IsEmpty() )
		return;

	CWaitCursor wait;

	if( mgaProject != NULL )
		CloseProject();

	OpenProject(conn);

}


#define PROJECT_STATUS_CHANGED 4

BOOL CGMEApp::SaveAllModified() 
{
	if (mgaProject != NULL && (proj_type_is_mga || proj_type_is_xmlbackend)) {
		long l;
		COMTHROW(mgaProject->get_ProjectStatus(&l));
		int ret;
		if (!(l & PROJECT_STATUS_CHANGED))
			ret = IDNO;
		else
			ret = AfxMessageBox("Save project '" + projectName + "'?",  MB_YESNOCANCEL);
		if (ret == IDCANCEL) {
			return FALSE;
		} else if (ret == IDNO) {
			abort_on_close = true;
			OnFileAbortProject();
		} else {
			((CMainFrame*)m_pMainWnd)->clearMgaProj();
			return SafeCloseProject();
		}
	}
	return TRUE;
}

int CGMEApp::ExitInstance() 
{
	CloseProject(false);
	return CWinApp::ExitInstance();
}

void CGMEApp::OnFileNew() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnFileNew\r\n");

	MSGTRY	{
		CString metaname;
		CString dataconn;
		CMgaOpenDlg dlg(CMgaOpenDlg::NewDialog);

		CComObjPtr<IMgaLauncher> launcher;
		COMTHROW( launcher.CoCreateInstance(CComBSTR(L"Mga.MgaLauncher")) );

	meta_label:
		HRESULT hr = launcher->MetaDlg(METADLG_NONE);
		if( hr == S_FALSE )
			return;
		COMTHROW( hr );

		metaname.Empty();
		COMTHROW( launcher->get_ParadigmName(PutOut(metaname)) );

		dataconn = dlg.AskConnectionString(false);

		if( dlg.pressed_back )
			goto meta_label;

		if( dataconn.IsEmpty() )
			return;

		CWaitCursor wait;

		if( mgaProject != NULL )
			CloseProject();

		CreateProject(metaname, dataconn);

		if (mgaProject != NULL && (proj_type_is_mga||proj_type_is_xmlbackend)) {
			OnFileSave();
		}
	}
	MSGCATCH("Error creating new project",;)

}

BOOL CGMEApp::OnOpenRecentProject(UINT nID)
{
	ASSERT_VALID(this);

	ASSERT(nID >= ID_FILE_MRU_PRJ1);
	ASSERT(nID < ID_FILE_MRU_PRJ1 + (UINT)m_RecentProjectList.GetSize());

	int nIndex = nID - ID_FILE_MRU_PRJ1;
	CString conn = m_RecentProjectList[nIndex];

	ASSERT(conn.GetLength() != 0);

	CGMEEventLogger::LogGMEEvent("CGMEApp::OnOpenRecentProject "+conn+"\r\n");

	CWaitCursor wait;

	if( mgaProject != NULL )
		CloseProject();

	OpenProject(conn);

	return TRUE;
}


bool CGMEApp::SafeCloseProject() {
// In case of an MGA file, try to save it first to find out 
	abort_on_close = false;
	if(mgaProject != NULL && (proj_type_is_mga||proj_type_is_xmlbackend)) {
		HRESULT hr = mgaProject->Save(NULL);
		if(hr != S_OK) {
			AfxMessageBox("ERROR: Could not save project\nCheck access permissions");
			return false;
		}
		abort_on_close = true;
	}

	BeginWaitCursor();
	if(CGMEDoc::theInstance)
		CGMEDoc::theInstance->OnCloseDocument();
	EndWaitCursor();
	return true;
}

void CGMEApp::OnFileCloseproject() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnFileCloseproject\r\n");
	SaveAllModified();
}


void CGMEApp::OnFileSaveAs() {
	CMgaOpenDlg dlg(CMgaOpenDlg::SaveAsDialog);
	CString spec_ext;
	if( currentConnection.Left(4) == "MGA=") // if MGA format
	{
		int rps = currentConnection.ReverseFind('.');
		if( rps != -1 && rps < currentConnection.GetLength())
		{
			spec_ext = currentConnection.Mid( rps + 1);
			if( spec_ext.CompareNoCase( "mga") == 0)    // oh, just the plain 'mga' extension
				spec_ext = "";                          // we need not have specific behaviour
		}
	}
	CString conn = dlg.AskMGAConnectionString( spec_ext);

	CGMEEventLogger::LogGMEEvent("CGMEApp::OnFileSaveAs "+conn+"\r\n");

	if( conn.IsEmpty() )
		return;
	BeginWaitCursor();
	SaveProject(conn);
	EndWaitCursor();
}

void CGMEApp::OnFileSave() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnFileSave\r\n");
	BeginWaitCursor();
	SaveProject("");
	EndWaitCursor();
}

void CGMEApp::OnFileAbortProject() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnFileAbortProject\r\n");
	((CMainFrame*)m_pMainWnd)->clearMgaProj();

	if(!mgaProject) return;
	long l;
	COMTHROW(mgaProject->get_ProjectStatus(&l));
	if(!abort_on_close && (l & PROJECT_STATUS_CHANGED) &&
		AfxMessageBox("Discard edits to project " + projectName + "?", 
		MB_OKCANCEL) == IDCANCEL) {
		return;
	}
	abort_on_close = true;

	BeginWaitCursor();
	if(CGMEDoc::theInstance)
		CGMEDoc::theInstance->OnCloseDocument(true);
	EndWaitCursor();
}


void CGMEApp::OnFileExportxml() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnFileExportxml ");
	MSGTRY
	{
		CComPtr<IMgaDumper> dumper;
		COMTHROW( dumper.CoCreateInstance(L"Mga.MgaDumper") );
		ASSERT( dumper != NULL );

		CFileDialog dlg(FALSE, "xme", NULL,
			OFN_EXPLORER | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			"Exported Files (*.xme)|*.xme|GME 1.x XML Format (*.xml)|*.xml|All Files (*.*)|*.*||");
		if( dlg.DoModal() != IDOK )
		{
			CGMEEventLogger::LogGMEEvent("Canceled\r\n");
			return;
		}
		CGMEEventLogger::LogGMEEvent(dlg.GetPathName()+"\r\n");

		CWaitCursor wait;
		if(dlg.m_ofn.nFilterIndex == 2) {
			AfxMessageBox(
				"WARNING Saving in GME 1.x XML format.\n"
				"Libraries are converted to normal model data,\n"
				"thus resulting XML file may need some editing\n"
				"to avoid paradigm violations on import");
			COMTHROW(dumper->put_FormatVersion(0));
		}
		COMTHROW( dumper->DumpProject(theApp.mgaProject,PutInBstr(dlg.GetPathName())) );

		if( CMainFrame::theInstance) CMainFrame::theInstance->m_console.Message( CString( "Project successfully exported into ") + dlg.GetPathName() + ".", 1);
	}
	MSGCATCH("Error while generating XML file",;)
}


void CGMEApp::OnFileImportxml() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnFileImportxml ");

	bool keep_on( true); // if true then keep working even after a failed import: try to apply an xslt script
	CString file_name;
	CString new_file_name = "";

	while (keep_on)
	{
		keep_on = false;
		MSGTRY
		{
			CComPtr<IMgaParser> parser;
			COMTHROW( parser.CoCreateInstance(L"Mga.MgaParser") );
			ASSERT( parser != NULL );

			CFileDialog dlg(TRUE, "xme", (LPCTSTR) new_file_name,
				OFN_EXPLORER | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |
				OFN_FILEMUSTEXIST,
				"GME Exported Files (*.xme;*.xml)|*.xme; *.xml|All Files (*.*)|*.*||");
			if( dlg.DoModal() != IDOK )
			{
				CGMEEventLogger::LogGMEEvent("Cancelled\r\n");
				return;
			}
			CGMEEventLogger::LogGMEEvent(dlg.GetPathName()+"\r\n");

			if (dlg.GetFileExt().CompareNoCase("xml") == 0 ) {
				AfxMessageBox(
						"Newer versions of GME use the \".xme.\" filename extension\n"
						"for exported XML data files.\n"
						"Please, rename your existing files to avoid further problems!\n", 
						MB_OK | MB_ICONINFORMATION);
			}

			bool newproject = !mgaProject;
			if (newproject) {
				CString dataconn;
				COMTRY {
					CComBstrObj paradigm, parversion, basename, version;
					CComVariant parguid;

					COMTHROW( parser->GetXMLInfo(PutInBstr(dlg.GetPathName()), PutOut(paradigm), PutOut(parversion), &parguid, PutOut(basename), PutOut(version)) );

					CMgaOpenDlg opdlg(CMgaOpenDlg::ImportDialog);
					opdlg.SetFileNameHint( PutInCString(basename));//opdlg.filenamehint = basename;
					dataconn = opdlg.AskConnectionString(false);
					if (dataconn.IsEmpty()) {
					   CGMEEventLogger::LogGMEEvent("CGMEApp::OnFileImportxml exited because empty connection string has been given");
					   return;
					}

					{
						CComPtr<IMgaRegistrar> reg;
						COMTHROW( reg.CoCreateInstance(L"Mga.MgaRegistrar") );
						CComBstrObj conn;
						HRESULT h1 = reg->QueryParadigm(paradigm, PutOut(conn), &parguid, REGACCESS_PRIORITY);
						CComVariant pg2;
						conn.Empty();
						HRESULT h2 = reg->QueryParadigm(paradigm, PutOut(conn), &pg2, REGACCESS_PRIORITY);
						char buf[300];
						if(h2 != S_OK) {
							ASSERT(h1 != S_OK);
							CString msg = "Could not find paradigm paradigm '" + CString(paradigm) + "'\n" 
									" (Eg.: In GME3 the MetaGME2000 paradigm was renamed to MetaGME)\n"
									"Do you want to import with an other registered paradigm ?";
							if (AfxMessageBox(msg ,MB_OKCANCEL) == IDOK) {	
								CComObjPtr<IMgaLauncher> launcher;
								COMTHROW( launcher.CoCreateInstance(CComBSTR(L"Mga.MgaLauncher")) );
								if (SUCCEEDED(launcher->MetaDlg(METADLG_NONE))) {
									// parguid = true;
									parguid.Clear();
									paradigm.Empty();
									COMTHROW( launcher->get_ParadigmName(PutOut(paradigm)) );
								}
								else {
									return;   // safe before create
								}
							}
							else {
								return;   // safe before create
							}
						}
						else {
							CComBstrObj parguid1, parguid2;
							GUID gg;

							CopyTo(parguid,gg);
							CopyTo(gg, parguid1);

							CopyTo(pg2,gg);
							CopyTo(gg, parguid2);

							if(h1 != S_OK) {
								sprintf(buf, "Could not locate paradigm %s\nVersion ID: %s\n"
											 "Do you want to upgrade to the current version instead?\nCurrent ID: %s", 
											 PutInCString(paradigm), PutInCString(parguid1), PutInCString(parguid2));
											 if(AfxMessageBox(buf,MB_OKCANCEL | MB_ICONQUESTION) == IDOK) {
												parguid = pg2;
											 }
											 else {
												AfxMessageBox("Import canceled");
												return; // safe before create
											 }	

							}
							else if(parguid1.Compare(parguid2)) {
								sprintf(buf, "This model was exported using paradigm %s\nVersion ID: %s\n"
											 "Do you want to upgrade to the current version?\nCurrent ID: %s", 
											 PutInCString(paradigm), PutInCString(parguid1), PutInCString(parguid2));
											 int answer = AfxMessageBox(buf,MB_YESNOCANCEL | MB_ICONQUESTION);
											 if(answer == IDYES) {
												parguid = pg2;
											 }
											 else if(answer == IDCANCEL) {
												AfxMessageBox("Import canceled");
												return;  // safe before create
											 }
							}
						}
					}
					COMTHROW( mgaProject.CoCreateInstance(L"Mga.MgaProject") );
#pragma warning(disable: 4310) // cast truncates constant value
					COMTHROW( mgaProject->EnableAutoAddOns(VARIANT_TRUE));
#pragma warning(default: 4310) // cast truncates constant value
					HRESULT hr = mgaProject->CreateEx(PutInBstr(dataconn), PutInBstr(paradigm), parguid);
					if(hr == E_MGA_PARADIGM_NOTREG || hr == E_MGA_PARADIGM_INVALID) {
						char buf[300];
						CComBstrObj parguid1;
						GUID gg;
						CopyTo(parguid,gg);
						CopyTo(gg, parguid1);
						sprintf(buf, "Could not open paradigm %s\nVersion ID: %s", 
							PutInCString(paradigm), PutInCString(parguid1));

						AfxMessageBox(buf);
					}
					if(hr == E_MGA_COMPONENT_ERROR) {
						AfxMessageBox("ERROR: Some automatic addon components could not start up\n");
					}
					COMTHROW(hr);
					AfterOpenOrCreateProject(dataconn); 
				} catch(hresult_exception &e) {
					CloseProject();
					DisplayError("Could not create the project", e.hr); 
					throw;
				}
			}

			//UpdateProjectName(); // moved below

			CWaitCursor wait;
			if(mgaConstMgr) COMTHROW(mgaConstMgr->Enable(false));

			keep_on = true;
			file_name = dlg.GetPathName();
			if( CMainFrame::theInstance) CMainFrame::theInstance->m_console.Message( CString( "Importing ") + file_name + "...", 1);
			COMTHROW(parser->ParseProject(theApp.mgaProject,PutInBstr(dlg.GetPathName())) );
			
			// mgaproject has been filled with data, let's update title:
			UpdateProjectName();

			if(newproject && (proj_type_is_mga||proj_type_is_xmlbackend)) {
				OnFileSave();
			}
			if( CMainFrame::theInstance) CMainFrame::theInstance->m_console.Message( dlg.GetPathName() + " was successfully imported.", 1);
			else AfxMessageBox( dlg.GetPathName() + " was successfully imported.");
			keep_on = false;
		}
		MSGCATCH("Error importing XML file",;)

	} // while keep_on

	if (mgaConstMgr) COMTHROW(mgaConstMgr->Enable(true));
}



void CGMEApp::OnFileXMLUpdate() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnFileXMLUpdate\r\n");
    ASSERT(mgaProject);
    ASSERT(mgaMetaProject);

	TCHAR xmlname[MAX_PATH];
	GetTempFileName(".", "XEX",0, xmlname);
	
	if(currentConnection.Find("MGA=") != 0) {
		AfxMessageBox("Function is available only for .mga models");
	}

	CString fname = currentConnection.Mid(4);
	CString backupname;

	MSGTRY
	{
		CWaitCursor wait;
		CComBstrObj parname;
		COMTHROW( mgaMetaProject->get_Name(PutOut(parname)) );
		CComBstrObj metaconn;

		CComBstrObj currentguid;
		{
			CComVariant parguid;
			COMTHROW( mgaMetaProject->get_GUID(&parguid) );

			CComPtr<IMgaRegistrar> reg;
			COMTHROW( reg.CoCreateInstance(L"Mga.MgaRegistrar") );
			CComVariant pg2;

			COMTHROW(reg->QueryParadigm(parname, PutOut(metaconn), &pg2, REGACCESS_PRIORITY));

			CComBstrObj parguid1;
			GUID gg;
			CopyTo(parguid,gg);
			CopyTo(gg, parguid1);

			CopyTo(pg2,gg);
			CopyTo(gg, currentguid);

			if(!parguid1.Compare(currentguid)) {
				char buf[200];
				sprintf(buf, "There is no need to upgrade this model\nIts Meta Version ID is the current ID\nCurrent ID: %s", 
					PutInCString(currentguid));
				AfxMessageBox(buf);
				return;
			}
		}

		CComPtr<IMgaDumper> dumper;
		COMTHROW( dumper.CoCreateInstance(L"Mga.MgaDumper") );
		ASSERT( dumper != NULL );

		COMTHROW( dumper->DumpProject(theApp.mgaProject, PutInBstr(xmlname)) );


		SafeCloseProject();
		ASSERT(!mgaProject);

		backupname = fname;
		int p = backupname.ReverseFind('.');
		if(!p || backupname.Find('\\',p) != -1) p = backupname.GetLength();
		backupname.Insert(p,"-backup");
		DeleteFile(backupname);
		if(!MoveFile(fname, backupname)) {
			backupname = fname;
			char buf[300];
			sprintf( buf, "Could not save original file '%s' to '%s'", fname, backupname); 
			AfxMessageBox(buf);
			COMTHROW(E_NOTFOUND);
		}



		CreateProject(PutInCString(parname), currentConnection);

		if(!mgaProject || !mgaMetaProject) {
			AfxMessageBox("Error creating project");
			return;
		}

		UpdateComponentLists();
		ChangedProjectConnStrings();

		CComPtr<IMgaParser> parser;
		COMTHROW( parser.CoCreateInstance(L"Mga.MgaParser") );
		ASSERT( parser != NULL );
	    if(mgaConstMgr) COMTHROW(mgaConstMgr->Enable(false));
	    COMTHROW(parser->ParseProject(mgaProject, PutInBstr(xmlname)) );
		{
			char buf[200];
			sprintf(buf, "The model has been updated\nCurrent ID: %s\nThe original model has been saved to %s", 
					PutInCString(currentguid), backupname);
			AfxMessageBox(buf);
		}
	}
	catch(hresult_exception &e)	{
		char buf[200];
		if(backupname.IsEmpty()) {
			sprintf(buf, "The upgrade failed: %ld\nThe model has not been closed", e.hr);
			AfxMessageBox(buf);
		}
		else {
			if(backupname.Compare(fname)) {
				if(MoveFile(backupname, fname)) backupname = fname;
			}
			sprintf(buf, "The upgrade failed: %ld\nThe original model is in file %s", e.hr, backupname);
			AfxMessageBox(buf);
		}
	}

    if (mgaConstMgr) COMTHROW(mgaConstMgr->Enable(true));
}



void CGMEApp::OnFileRegcomponents() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnFileRegcomponents ");
	MSGTRY
	{
		CComObjPtr<IMgaLauncher> launcher;
		COMTHROW( launcher.CoCreateInstance(L"Mga.MgaLauncher") );
		COMTHROW( launcher->put_ParadigmName(PutInBstr(guiMetaProject->name)));
		COMTHROW( launcher->put_ComponentType(COMPONENTTYPE_ALL) );

		ATLASSERT(mgaProject);
		CComBSTR runningcomps;
		{
			CComPtr<IMgaComponents> comps;
			COMTHROW(mgaProject->get_AddOnComponents(&comps));
			MGACOLL_ITERATE(IMgaComponent, comps) {
				CComQIPtr<IMgaComponentEx> compx = MGACOLL_ITER;
				CComBSTR p;
				if(compx) COMTHROW(compx->get_ComponentProgID(&p));
				else COMTHROW(MGACOLL_ITER->get_ComponentName(&p));
				if(runningcomps) runningcomps += " ";
				runningcomps += p;
			}
			MGACOLL_ITERATE_END;
		}
		COMTHROW(launcher->put_Parameter(CComVariant(runningcomps)));

		CGMEEventLogger::LogGMEEvent(CString(runningcomps)+"\r\n");

		COMTHROW( launcher->ComponentDlg(COMPONENTDLG_INTERP));
		UpdateComponentLists(true);
	}
	MSGCATCH("Error while trying to register the interpreter",;)
}

void CGMEApp::OnFileSettings() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnFileSettings\r\n");
	MSGTRY
	{
		CComObjPtr<IMgaLauncher> launcher;
		COMTHROW( launcher.CoCreateInstance(L"Mga.MgaLauncher") );
		COMTHROW( launcher->GmeDlg());
	}
	MSGCATCH("Error while trying to get GME settings",;)
	GetSettings();
}

void CGMEApp::OnFileClearLocks() 
{
	if( mgaProject != NULL || mgaMetaProject != NULL )
		return;

	MSGTRY
	{
		CMgaOpenDlg dlg(CMgaOpenDlg::ClearLocksDialog);
		CString conn = dlg.AskConnectionString(false);

		if( conn.IsEmpty() )
			return;

		CWaitCursor wait;

		CComObjPtr<IMgaProject> project;
		COMTHROW( project.CoCreateInstance(OLESTR("MGA.MgaProject")) );
		ASSERT( project != NULL );
#pragma warning(disable: 4310) // cast truncates constant value
		COMTHROW( project->CheckLocks(PutInBstr(conn), VARIANT_TRUE) );
#pragma warning(default: 4310) // cast truncates constant value

		AfxMessageBox("Database locks are cleared");
	}
	MSGCATCH("Error while clearing locks in database",;)
}

void CGMEApp::OnHelpContents() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnHelpContents\r\n");

	MSGTRY {
		CComObjPtr<IMgaLauncher> launcher;
		COMTHROW( launcher.CoCreateInstance(L"Mga.MgaLauncher") );
		COMTHROW( launcher->ShowHelp(NULL) );
	}
	MSGCATCH("Error while showing help contents.",;)
}

void CGMEApp::OnFileCheckall() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnFileCheckall\r\n");
	ASSERT(mgaConstMgr);
	if(!mgaConstMgr) return;
	// message boxes displayed from constraint manager if in interactive mode
	mgaConstMgr->ObjectsInvokeEx(mgaProject, NULL, NULL, NULL);
}

void CGMEApp::OnFileDisplayConstraints() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnFileDisplayConstraints\r\n");
	ASSERT(mgaConstMgr);
	mgaConstMgr->ObjectsInvokeEx(mgaProject, NULL, NULL, CONSTMGR_SHOW_CONSTRAINTS);
	
}



void CGMEApp::OnFileRegparadigms() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnFileRegparadigms\r\n");
	MSGTRY
	{
		CComPtr<IMgaLauncher> launcher;
		COMTHROW( launcher.CoCreateInstance(L"Mga.MgaLauncher") );

		while(1) {
			HRESULT hr = launcher->MetaDlg(METADLG_PARREG);
			if( hr == S_FALSE )	return;

			COMTHROW( launcher->put_ComponentType(COMPONENTTYPE_ALL) );

			bool workonrunningparadigm = false;
			if(guiMetaProject) {
				CComBstrObj metaname;
				COMTHROW( launcher->get_ParadigmName(PutOut(metaname)) );
				if(metaname == PutInBstr(guiMetaProject->name)) workonrunningparadigm = true;
			}

			if(workonrunningparadigm) {
				ATLASSERT(mgaProject);
				CComBSTR runningcomps;
				CComPtr<IMgaComponents> comps;
				COMTHROW(mgaProject->get_AddOnComponents(&comps));
				MGACOLL_ITERATE(IMgaComponent, comps) {
					CComQIPtr<IMgaComponentEx> compx = MGACOLL_ITER;
					CComBSTR p;
					if(compx) COMTHROW(compx->get_ComponentProgID(&p));
					else COMTHROW(MGACOLL_ITER->get_ComponentName(&p));
					if(runningcomps) runningcomps += " ";
					runningcomps += p;
				}
				MGACOLL_ITERATE_END;
				COMTHROW(launcher->put_Parameter(CComVariant(runningcomps)));
			}

			COMTHROW( launcher->ComponentDlg(COMPONENTDLG_INTERP));

			if(workonrunningparadigm) UpdateComponentLists(true);
		}
	} MSGCATCH("Error registering paradigms", ;);
}


// *******************************************************************************

void CGMEApp::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(guiMetaProject == NULL);
}

void CGMEApp::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(guiMetaProject == NULL);
}

void CGMEApp::OnUpdateFileCloseproject(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(guiMetaProject != NULL);
}

void CGMEApp::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(mgaProject != NULL && (proj_type_is_mga||proj_type_is_xmlbackend));
}

void CGMEApp::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(mgaProject != NULL && proj_type_is_mga);
}

void CGMEApp::OnUpdateFileAbortProject(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(mgaProject != NULL && proj_type_is_mga);
}

void CGMEApp::OnUpdateFileExportxml(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(guiMetaProject != NULL);
}

void CGMEApp::OnUpdateFileXMLUpdate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(mgaProject != NULL && proj_type_is_mga);
}

void CGMEApp::OnUpdateFileCheckall(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(mgaConstMgr != NULL);
}

void CGMEApp::OnUpdateFileDisplayConstraints(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(mgaConstMgr != NULL);	
	
}

void CGMEApp::OnUpdateFileRegcomponents(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(guiMetaProject != NULL);
}

void CGMEApp::OnUpdateRecentProjectMenu(CCmdUI* pCmdUI)
{
	ASSERT_VALID(this);
	m_RecentProjectList.UpdateMenu(pCmdUI,guiMetaProject == NULL);
}


// *******************************************************************************
// *******************************************************************************
//								EDIT
// *******************************************************************************
// *******************************************************************************


void CGMEApp::OnEditProjectproperties() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnEditProjectproperties " + projectName +"\r\n");
	CProjectPropertiesDlg dlg;
	if(dlg.DoModal() == IDOK) {
		if(CGMEDoc::theInstance)
			CGMEDoc::theInstance->SetTitle(projectName);
		CMainFrame::theInstance->UpdateTitle(projectName);
	}
}


void CGMEApp::OnEditUndo() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnEditUndo\r\n");
	mgaProject->Undo();
}

void CGMEApp::OnEditRedo() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnEditRedo\r\n");
	mgaProject->Redo();
}

void CGMEApp::OnEditClearUndo() 
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnEditClearUndo\r\n");
	if( mgaProject == NULL )
		return;

	if(AfxMessageBox("You are about to loose all Undo/Redo information. Proceed?",MB_YESNO | MB_ICONQUESTION) == IDYES) {
		MSGTRY
		{
			COMTHROW( mgaProject->FlushUndoQueue() );
		}
		MSGCATCH("Error while clearing the undo queue",;)
	}
}


// *******************************************************************************

void CGMEApp::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	if(guiMetaProject != NULL) {
		short undoSize;
		short redoSize;
		mgaProject->UndoRedoSize(&undoSize,&redoSize);
		pCmdUI->Enable(undoSize > 0);
	}
	else
		pCmdUI->Enable(FALSE);
}

void CGMEApp::OnUpdateEditRedo(CCmdUI* pCmdUI) 
{
	if(guiMetaProject != NULL) {
		short undoSize;
		short redoSize;
		mgaProject->UndoRedoSize(&undoSize,&redoSize);
		pCmdUI->Enable(redoSize > 0);
	}
	else
		pCmdUI->Enable(FALSE);
}

void CGMEApp::OnUpdateEditClearUndo(CCmdUI* pCmdUI) 
{
	if(mgaProject != NULL) {
		short undoSize;
		short redoSize;
		mgaProject->UndoRedoSize(&undoSize,&redoSize);
		pCmdUI->Enable(undoSize > 0);
	}
	else
		pCmdUI->Enable(FALSE);
}

void CGMEApp::OnUpdateEditProjectproperties(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(CGMEDoc::theInstance != 0);
}



/*
void CGMEApp::OnUpdateFileRunplugin1(CCmdUI* pCmdUI) 
{
	
	CMenu *filemenu = pCmdUI->m_pMenu;
	UINT idx = pCmdUI->m_nIndex;
if(idx == 0) return;
	CString label;
	ASSERT(filemenu);
	filemenu->GetMenuString(idx,label,MF_BYPOSITION);
	filemenu->DeleteMenu(idx,MF_BYPOSITION);
	CMenu pluginmenu;
	pluginmenu.CreatePopupMenu();
	pluginmenu.GetMenuItemID
	for(int i = 0; i < comps.GetSize(); ++i)	{
			pluginmenu.AppendMenu(MF_ENABLED, pCmdUI->m_nID + i,comps[i]);
	}
	filemenu->InsertMenu(idx,
						comps.GetSize() ? MF_BYPOSITION|MF_POPUP|MF_ENABLED: MF_BYPOSITION|MF_POPUP|MF_GRAYED,
						(UINT)pluginmenu.Detach(),label);
	
}
*/

void CGMEApp::OnRunPlugin(UINT nID) {
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnRunPlugin "+plugins[nID - ID_FILE_RUNPLUGIN1]+"\r\n");

	// Focus must be killed to flush ObjectInspector and Browser
	::SetFocus(NULL);

	RunComponent(plugins[nID - ID_FILE_RUNPLUGIN1]);
}

void CGMEApp::OnRunInterpreter(UINT nID) {
	CGMEEventLogger::LogGMEEvent("CGMEApp::OnRunInterpreter "+interpreters[nID - ID_FILE_INTERPRET1]+"\r\n");

	// Focus must be killed to flush ObjectInspector and Browser
	::SetFocus(NULL);

	RunComponent(interpreters[nID - ID_FILE_INTERPRET1]);
}



void CGMEApp::RunComponent(const CString &compname)
{

	CComPtr<IMgaLauncher> launcher;
	launcher.CoCreateInstance(CComBSTR(L"Mga.MgaLauncher") );
	if(!launcher) {
		AfxMessageBox("Cannot start up component launcher");
	}
	else {
		CComPtr<IMgaFCO> focus;
		CComPtr<IMgaFCOs> selfcos;
		COMTHROW(selfcos.CoCreateInstance(OLESTR("Mga.MgaFCOs")));
		CMDIChildWnd *pChild  = CMainFrame::theInstance->MDIGetActive();
		if (pChild) {
#if !defined (ACTIVEXGMEVIEW)
			CGMEView *view = (CGMEView*)pChild->GetActiveView();
			if (view) {
				COMTHROW(view->currentModel.QueryInterface(&focus));
				POSITION pos = view->selected.GetHeadPosition();
				while (pos) {
					CGuiFco *gfco = view->selected.GetNext(pos);
					COMTHROW(selfcos->Append(gfco->mgaFco));
				}
			}
#endif
		}

		if(theApp.bNoProtect) COMTHROW( launcher->put_Parameter(CComVariant(true)));
		if(launcher->RunComponent(PutInBstr(compname), mgaProject, focus, selfcos, GME_MENU_START) != S_OK) {
			AfxMessageBox("Component execution failed");
		}
	}
}

class CGmePrintSetup : public CPrintDialog
{
public:
	enum { IDD = IDD_PRINT_DIALOG  };
	CGmePrintSetup() : CPrintDialog(true, 0, NULL) {}
};

void CGMEApp::OnUniquePrintSetup()
{
	CGmePrintSetup setup;
	setup.m_pd.Flags =	PD_PRINTSETUP |  // actually the current aspect
								PD_ENABLESETUPTEMPLATE |
								PD_ENABLEPRINTHOOK | PD_ENABLESETUPHOOK ;
	setup.m_pd.hInstance = AfxGetInstanceHandle();
	setup.m_pd.lpSetupTemplateName = MAKEINTRESOURCE(PRNSETUPDLGORD);
	DoPrintDialog(&setup);
}

void CGMEApp::ImportDroppedFile( const CString& fname)
{
	CGMEEventLogger::LogGMEEvent("CGMEApp::ImportFile ");

	bool keep_on( true); // if true then keep working even after a failed import: try to apply an xslt script
	CString file_name = fname;

	while (keep_on)
	{
		keep_on = false;
		MSGTRY
		{
			CComPtr<IMgaParser> parser;
			COMTHROW( parser.CoCreateInstance(L"Mga.MgaParser") );
			ASSERT( parser != NULL );

			bool newproject = !mgaProject;
			if (newproject) {
				CString dataconn;
				COMTRY {
					CComBstrObj paradigm, parversion, basename, version;
					CComVariant parguid;

					COMTHROW( parser->GetXMLInfo(PutInBstr(file_name), PutOut(paradigm), PutOut(parversion), &parguid, PutOut(basename), PutOut(version)) );

					CMgaOpenDlg opdlg(CMgaOpenDlg::ImportDialog);
					opdlg.SetFileNameHint( PutInCString( basename));//opdlg.filenamehint = basename;
					dataconn = opdlg.AskConnectionString(false);
					if (dataconn.IsEmpty()) {
					   return;
					}

					{
						CComPtr<IMgaRegistrar> reg;
						COMTHROW( reg.CoCreateInstance(L"Mga.MgaRegistrar") );
						CComBstrObj conn;
						HRESULT h1 = reg->QueryParadigm(paradigm, PutOut(conn), &parguid, REGACCESS_PRIORITY);
						CComVariant pg2;
						conn.Empty();
						HRESULT h2 = reg->QueryParadigm(paradigm, PutOut(conn), &pg2, REGACCESS_PRIORITY);
						char buf[300];
						if(h2 != S_OK) {
							ASSERT(h1 != S_OK);
							CString msg = "Could not find paradigm paradigm '" + CString(paradigm) + "'\n" 
									" (Eg.: In GME3 the MetaGME2000 paradigm was renamed to MetaGME)\n"
									"Do you want to import with an other registered paradigm ?";
							if (AfxMessageBox(msg ,MB_OKCANCEL) == IDOK) {	
								CComObjPtr<IMgaLauncher> launcher;
								COMTHROW( launcher.CoCreateInstance(CComBSTR(L"Mga.MgaLauncher")) );
								if (SUCCEEDED(launcher->MetaDlg(METADLG_NONE))) {
									// parguid = true;
									parguid.Clear();
									paradigm.Empty();
									COMTHROW( launcher->get_ParadigmName(PutOut(paradigm)) );
								}
								else {
									return;   // safe before create
								}
							}
							else {
								return;   // safe before create
							}
						}
						else {
							CComBstrObj parguid1, parguid2;
							GUID gg;

							CopyTo(parguid,gg);
							CopyTo(gg, parguid1);

							CopyTo(pg2,gg);
							CopyTo(gg, parguid2);

							if(h1 != S_OK) {
								sprintf(buf, "Could not locate paradigm %s\nVersion ID: %s\n"
											 "Do you want to upgrade to the current version instead?\nCurrent ID: %s", 
											 PutInCString(paradigm), PutInCString(parguid1), PutInCString(parguid2));
											 if(AfxMessageBox(buf,MB_OKCANCEL | MB_ICONQUESTION) == IDOK) {
												parguid = pg2;
											 }
											 else {
												AfxMessageBox("Import canceled");
												return; // safe before create
											 }	

							}
							else if(parguid1.Compare(parguid2)) {
								sprintf(buf, "This model was exported using paradigm %s\nVersion ID: %s\n"
											 "Do you want to upgrade to the current version?\nCurrent ID: %s", 
											 PutInCString(paradigm), PutInCString(parguid1), PutInCString(parguid2));
											 int answer = AfxMessageBox(buf,MB_YESNOCANCEL | MB_ICONQUESTION);
											 if(answer == IDYES) {
												parguid = pg2;
											 }
											 else if(answer == IDCANCEL) {
												AfxMessageBox("Import canceled");
												return;  // safe before create
											 }
							}
						}
					}
					COMTHROW( mgaProject.CoCreateInstance(L"Mga.MgaProject") );
#pragma warning(disable: 4310) // cast truncates constant value
					COMTHROW( mgaProject->EnableAutoAddOns(VARIANT_TRUE));
#pragma warning(default: 4310) // cast truncates constant value
					HRESULT hr = mgaProject->CreateEx(PutInBstr(dataconn), PutInBstr(paradigm), parguid);
					if(hr == E_MGA_PARADIGM_NOTREG || hr == E_MGA_PARADIGM_INVALID) {
						char buf[300];
						CComBstrObj parguid1;
						GUID gg;
						CopyTo(parguid,gg);
						CopyTo(gg, parguid1);
						sprintf(buf, "Could not open paradigm %s\nVersion ID: %s", 
							PutInCString(paradigm), PutInCString(parguid1));

						AfxMessageBox(buf);
					}
					if(hr == E_MGA_COMPONENT_ERROR) {
						AfxMessageBox("ERROR: Some automatic addon components could not start up\n");
					}
					COMTHROW(hr);
					AfterOpenOrCreateProject(dataconn); 
				} catch(hresult_exception &e) {
					CloseProject();
					DisplayError("Could not create the project", e.hr); 
					throw;
				}
			}

			//UpdateProjectName(); // moved below

			CWaitCursor wait;
			if(mgaConstMgr) COMTHROW(mgaConstMgr->Enable(false));

			keep_on = true;
			COMTHROW(parser->ParseProject(theApp.mgaProject,PutInBstr(file_name)) );
			
			// mgaproject has been filled with data, let's update title:
			UpdateProjectName();

			if(newproject && (proj_type_is_mga||proj_type_is_xmlbackend)) {
				OnFileSave();
			}

			if( CMainFrame::theInstance) CMainFrame::theInstance->m_console.Message( file_name + " was successfully imported.", 1);
			else AfxMessageBox(file_name + " was successfully imported.");
			keep_on = false;
		}
		MSGCATCH("Error importing XML file",;)
	} // while keep_on

	if (mgaConstMgr) COMTHROW(mgaConstMgr->Enable(true));
}

void CGMEApp::RegisterDroppedFile( const CString& fname, bool userReg/* = true*/)
{
	try
	{
		CWaitCursor wait;
		CComPtr<IMgaRegistrar> registrar;
		COMTHROW(registrar.CoCreateInstance(CComBSTR("Mga.MgaRegistrar")));

		regaccessmode_enum reg_access = REGACCESS_USER;	//REGACCESS_SYSTEM;
											//REGACCESS_USER;
											//REGACCESS_BOTH;
		CComBSTR newname;
		COMTHROW(registrar->RegisterParadigmFromData(PutInBstr( fname), &newname, reg_access));

		CMainFrame::theInstance->m_console.Message( "Done.", 1);
	}
	catch( hresult_exception &)
	{
		CMainFrame::theInstance->m_console.Message( "Error while registering paradigm!", 3);
	}
}

void CGMEApp::OnUpdateFilePluginX(CCmdUI* pCmdUI)
{
	bool enabled = m_vecDisabledPlugIns.find( pCmdUI->m_nID) == m_vecDisabledPlugIns.end();
	if( pCmdUI->m_nID >= ID_FILE_RUNPLUGIN1 && pCmdUI->m_nID <= ID_FILE_RUNPLUGIN8)
		pCmdUI->Enable( enabled );
}

void CGMEApp::OnUpdateFileInterpretX(CCmdUI* pCmdUI)
{
	bool enabled = m_vecDisabledComps.find( pCmdUI->m_nID) == m_vecDisabledComps.end();
	if( pCmdUI->m_nID >= ID_FILE_INTERPRET1 && pCmdUI->m_nID <= ID_FILE_INTERPRET18)
		pCmdUI->Enable( enabled );
}

// this method is used internally
void CGMEApp::ClearDisabledComps()
{
	m_vecDisabledPlugIns.clear();
	m_vecDisabledComps.clear();
}

// this method is called from CGMEOLEApp::DisableComp
//                        and CGMEApp::UpdateCompList4CurrentKind
void CGMEApp::DisableComp( const CString& pCompToFind, bool pbHide)
{
	UINT id_of_comp = 0;
	bool is_plugin = false;
	for(int i = 0; !id_of_comp && i < plugins.GetSize(); ++i)	
	{
		if( plugins[i] == pCompToFind)
		{
			id_of_comp = ID_FILE_RUNPLUGIN1 + i;
			is_plugin = true;
		}
	}

	for(int i = 0; !id_of_comp && i < interpreters.GetSize(); ++i)
	{
		if( interpreters[i] == pCompToFind)
		{
			id_of_comp = ID_FILE_INTERPRET1 + i;
			is_plugin = false;
		}
	}

	if( id_of_comp) // a valid command ID
	{
		//ActivateComp( id_of_comp, is_plugin, pbShow);
		if( is_plugin)
		{
			ONE_ID_LIST::const_iterator pos = m_vecDisabledPlugIns.find( id_of_comp);
			if( pbHide) // disable, so id_of_comp must be inserted into the vector
			{
				if( m_vecDisabledPlugIns.end() == pos) // not found
					m_vecDisabledPlugIns.insert( m_vecDisabledPlugIns.end(), id_of_comp);
			}
			else // enable, so remove id_of_comp from the vector
			{
				if( m_vecDisabledPlugIns.end() != pos) // if really found
					m_vecDisabledPlugIns.erase( pos);
			}
		}
		else
		{
			ONE_ID_LIST::const_iterator pos = m_vecDisabledComps.find( id_of_comp);
			if( pbHide) // disable, so id_of_comp must be inserted into the vector
			{
				if( m_vecDisabledComps.end() == pos) // not found
					m_vecDisabledComps.insert( m_vecDisabledComps.end(), id_of_comp);
			}
			else // enable, so remove id_of_comp from the vector
			{
				if( m_vecDisabledComps.end() != pos) // if really found
					m_vecDisabledComps.erase( pos);
			}
		}
	}
}

// this method is called from CGMEOLEApp::DisableCompForKinds
void CGMEApp::DisableCompForKinds( const CString& pComp, const CString& pKindSeq)
{
	int nm_of_tokens = 0; // will count the parsed kind names
	int pos = 0;
	CString t_kind;
	t_kind = pKindSeq.Tokenize( ";", pos); // tokenize by ';'
	while( t_kind != "")
	{
		ONE_COMP_LIST &my_comps = m_compsOfKind[ t_kind ];
		ONE_COMP_LIST::const_iterator it = my_comps.find( pComp);
		if( it == my_comps.end()) // not found, so insert it
			m_compsOfKind[ t_kind ].insert( pComp);

		++nm_of_tokens;
		t_kind = pKindSeq.Tokenize( ";", pos); // move to next token
	}
}

// this method is called from CGMEView::OnActivateView    (with the kindname shown)
//                            CGMEView::~CGMEView         (with the special string: _NO_MODEL_IS_OPEN_ == m_no_model_open_string)
//                            CGMEApp::SetCompFiltering   (with one from the items above)
void CGMEApp::UpdateCompList4CurrentKind( const CString& pKind)
{
	// if filter is OFF return
	if( !m_compFilterOn) 
	{
		return;
	}

	// kind name should not be empty
	if( pKind.IsEmpty()) { ASSERT(0); return; }

	ClearDisabledComps(); // reset all to original state (enabled)

	if( m_compsOfKind.find( pKind) != m_compsOfKind.end()) // if it has an entry
	{
		ONE_COMP_LIST &my_comps = m_compsOfKind[ pKind]; // this key already existed
		for( ONE_COMP_LIST::const_iterator it = my_comps.begin(); it != my_comps.end(); ++it)
		{
			DisableComp( *it, true); // disable comps which are registered for this kind
		}
	} // if this kind has no assigned [excluded] component set: NOP [every component is enabled]
}

void CGMEApp::SetCompFiltering( bool pOn)
{ 
	m_compFilterOn = pOn;
	if( !m_compFilterOn) // if turned OFF
	{
		ClearDisabledComps(); // reset all to original state (enabled)
	}
	else // turned ON
	{
		// find the current view
		bool found = false;
		CMDIChildWnd *pChild  = CMainFrame::theInstance->MDIGetActive();
		if( pChild) 
		{
#if !defined (ACTIVEXGMEVIEW)
			CGMEView *view = (CGMEView*)pChild->GetActiveView();
			if( view && view->guiMeta)
			{
				found = true;
				this->UpdateCompList4CurrentKind( view->guiMeta->name);
			}
#endif
		}

		if( !found)
			this->UpdateCompList4CurrentKind( CGMEApp::m_no_model_open_string);
	}
}

bool CGMEApp::GetCompFiltering()
{
	return m_compFilterOn;
}

bool CGMEApp::SetWorkingDirectory( LPCTSTR pPath)
{
	m_preferredPath = pPath;
	return SetCurrentDirectory( pPath) == TRUE;
	//int sc = _chdir( pPath);
	//return sc == 0;
}

void CGMEApp::UpdateMainTitle()
{
	if( CMainFrame::theInstance)
		CMainFrame::theInstance->UpdateTitle( projectName);
}

void CGMEApp::OnFocusBrowser()
{
	if( !mgaProject) return;

	CComObjPtr<IMgaTerritory> terry;
	COMTHROW(mgaProject->CreateTerritory(NULL, PutOut(terry)) );

	LPUNKNOWN objs = CGMEObjectInspector::theInstance->GetObjects();
	CComQIPtr<IMgaObjects> one_obj_coll( objs);
	long len = 0;
	if( one_obj_coll) COMTHROW( one_obj_coll->get_Count( &len));
	if( len >= 1)
	{
		MSGTRY
		{
			CComPtr<IMgaObject> one_obj, one_obj2;
			long status = OBJECT_ZOMBIE;
			CComBSTR id;
			COMTHROW( one_obj_coll->get_Item( 1, &one_obj));
			COMTHROW( mgaProject->BeginTransaction(terry,TRANSACTION_READ_ONLY));

			if( one_obj)  COMTHROW( terry->OpenObj( one_obj, &one_obj2));
			if( one_obj2) {
				COMTHROW( one_obj2->get_Status( &status));
				COMTHROW( one_obj2->get_ID( &id));
			}

			COMTHROW( mgaProject->CommitTransaction());

			if( id.Length() > 0 && status == OBJECT_EXISTS) 
			{
				CGMEBrowser::theInstance->FocusItem( id);
				return;
			}
		}
		MSGCATCH("Error getting project rootfolder", mgaProject->AbortTransaction())
	}

	MSGTRY
	{
		CComBSTR id;
		CComPtr<IMgaFolder> rf;
		COMTHROW(mgaProject->BeginTransaction(terry,TRANSACTION_READ_ONLY));
		COMTHROW(mgaProject->get_RootFolder( &rf));
		if( rf) COMTHROW(rf->get_ID(&id));
		COMTHROW(mgaProject->CommitTransaction());

		if( id.Length() > 0) 
			CGMEBrowser::theInstance->FocusItem( id);
	}
	MSGCATCH("Error getting project rootfolder", mgaProject->AbortTransaction())
}

void CGMEApp::OnFocusInspector()
{
	HWND hwnd = CGMEObjectInspector::theInstance->GetSafeHwnd();
	if( hwnd) ::SetFocus( hwnd);
}

void CGMEApp::consoleMessage( const CString& p_msg, short p_type)
{
	if( CMainFrame::theInstance) // 99.99% of cases
		CMainFrame::theInstance->m_console.Message( p_msg, p_type);
	else
		AfxMessageBox( p_msg);
}
