// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GMEApp.h"

#include "GMEstd.h"
#include "MainFrm.h"
#include "GMEDoc.h"
#include "GMEChildFrame.h"
#include "Splash.h"
#include "GMEEventLogger.h"
#include "..\XmlBackEnd\svauto.h"
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Tooltip helper for components

afx_msg BOOL CComponentBar::OnTT(UINT, NMHDR * pNMHDR, LRESULT * ) {
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
	UINT nIndex =pNMHDR->idFrom;

	if(nIndex == 1)
	{
		strncpy(pTTT->szText, "Check constraints", 79);
		return FALSE;
	}

	if(nIndex == 2)
	{
		strncpy(pTTT->szText, "Interpret the current model", 79);
		return FALSE;
	}


	CMFCToolBarButton* pButton = GetButton(nIndex-1);
	UINT nID = pButton->m_nID;

	if(nID >= ID_FILE_RUNPLUGIN1 && nID <= ID_FILE_RUNPLUGIN8) {
		strncpy(pTTT->szText, theApp.pluginTooltips[nID-ID_FILE_RUNPLUGIN1], 79);
		return FALSE;
	}
	if(nID >= ID_FILE_INTERPRET1 && nID <= ID_FILE_INTERPRET18) {
		strncpy(pTTT->szText, theApp.interpreterTooltips[nID-ID_FILE_INTERPRET1], 79);
			return FALSE;
	}
	return TRUE;
}

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;



IMPLEMENT_DYNCREATE(CComponentBar, CMFCToolBar)

BEGIN_MESSAGE_MAP(CComponentBar, CMFCToolBar)
	ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnTT )
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainFrame

CMainFrame *CMainFrame::theInstance = 0;

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWndEx)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_TIME, OnUpdateTime)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_SEARCH, OnEditSearch)
	ON_UPDATE_COMMAND_UI(ID_EDIT_SEARCH, OnUpdateEditSearch)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_NEW, OnUpdateWindowNew)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	
	ON_COMMAND(ID_VIEW_REFRESH_SOURCECONTROL, OnViewMultiUserRefreshSourceControl)
	ON_UPDATE_COMMAND_UI(ID_VIEW_REFRESH_SOURCECONTROL, OnUpdateViewMultiUserRefreshSourceControl)
	ON_COMMAND(ID_MULTIUSER_ACTIVEUSERS, OnViewMultiUserActiveUsers)
	ON_COMMAND(ID_MULTIUSER_SUBVERSION,  OnViewMultiUserSubversion)
	ON_UPDATE_COMMAND_UI(ID_MULTIUSER_ACTIVEUSERS, OnUpdateViewMultiUserActiveUsers)
	ON_UPDATE_COMMAND_UI(ID_MULTIUSER_SUBVERSION, OnUpdateViewMultiUserSubversion)
	ON_COMMAND(ID_VIEW_CLEARCONSOLE, OnViewClearConsole)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CLEARCONSOLE, OnUpdateViewClearConsole)
	ON_WM_CLOSE()
	ON_WM_DROPFILES()
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_OFF_2007_AQUA, &CMainFrame::OnApplicationLook)
	ON_COMMAND(ID_WINDOW_MANAGER, &CMainFrame::OnWindowManager)
	ON_COMMAND(ID_VIEW_CUSTOMIZE, &CMainFrame::OnViewCustomize)
	ON_COMMAND(ID_VIEW_FULLSCREEN, OnViewFullScreen)
	ON_REGISTERED_MESSAGE(AFX_WM_CREATETOOLBAR, OnToolbarCreateNew)
//}}AFX_MSG_MAP
	// By making the Menu IDs that same as the ToolBar IDs
	// we can leverage off of code that is already provided
	// in MFCs implementation of CFrameWnd to check, uncheck
	// show and hide toolbars.
	ON_COMMAND_EX(IDW_TOOLBAR_MAIN, OnBarCheck)
	ON_COMMAND_EX(IDW_TOOLBAR_WINS, OnBarCheck)
	ON_COMMAND_EX(IDW_TOOLBAR_DUMMY, OnBarCheck)
	ON_COMMAND_EX(IDW_TOOLBAR_MODE, OnBarCheck)
	ON_COMMAND_EX(IDW_TOOLBAR_NAVIG, OnBarCheck)
	ON_UPDATE_COMMAND_UI(IDW_TOOLBAR_MAIN, OnUpdateControlBarMenu)
	ON_UPDATE_COMMAND_UI(IDW_TOOLBAR_WINS, OnUpdateControlBarMenu)
	ON_UPDATE_COMMAND_UI(IDW_TOOLBAR_DUMMY, OnUpdateControlBarMenu)
	ON_UPDATE_COMMAND_UI(IDW_TOOLBAR_MODE, OnUpdateControlBarMenu)
	ON_UPDATE_COMMAND_UI(IDW_TOOLBAR_NAVIG, OnUpdateControlBarMenu)
	ON_COMMAND(ID_BUTTON33020, OnBtnBack)
	ON_COMMAND(ID_BUTTON33022, OnBtnHome)
	ON_UPDATE_COMMAND_UI(ID_BUTTON33020, OnUpdateBtnBack)
	ON_UPDATE_COMMAND_UI(ID_BUTTON33022, OnUpdateBtnHome)
	ON_COMMAND(ID_WINDOW_NEWHORIZONTALTABGROUP, &CMainFrame::OnWindowNewhorizontaltabgroup)
	ON_COMMAND(ID_WINDOW_NEWVERTICALTABGROUP, &CMainFrame::OnWindowNewverticaltabgroup)
	ON_COMMAND(ID_WINDOW_MOVETOPREVIOUSTABGROUP, &CMainFrame::OnWindowMovetoprevioustabgroup)
	ON_COMMAND(ID_WINDOW_MOVETONEXTTABGROUP, &CMainFrame::OnWindowMovetonexttabgroup)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	theInstance = this;	
	m_autosaveTimerID = NULL;
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_WIN_2000);
}

CMainFrame::~CMainFrame()
{
	theInstance = 0;	
}

void CMainFrame::setGmeOleApp( CGMEOLEApp * the_ole_app)
{
	mGmeOleApp = the_ole_app;

	IDispatch *disp;							// REFCOUNT is initially 1 ( ONE )

	disp = mGmeOleApp->GetIDispatch(FALSE);	// do not increment the refcount

	m_console.SetGMEApp(disp); // increments the refcount to 2 (since it stores the value in a smart pointer)

	// decrement the refcount, relying on the other components maintaining the correct refcounts
	//this line is needed either in setGmeOleApp or here
	ULONG ul = mGmeOleApp->GetIDispatch(FALSE)->Release();
	//ul = mGmeOleApp->GetIDispatch(FALSE)->Release(); //decrement the refcount to 1

	// later when a project is opened the "mGmeOleApp" will be registered as a client of the "MgaProject", thus
	// it will be incremented once again the refcount
	
	// when the project is closed, then the CGMEApp::CloseProject will erase this reference to the "mGmeOleApp"  with a  "mgaClient = NULL;" call

	// so the Mga component is referencing the GmeOleApp by its MgaProject's client member
	//        Console compt is referencing the GmeOleApp by its member
	//
	// beware that when the main GME would like to destruct the Console upon exiting
	// then the Console has to be the last referring to the GmeOleApp, so that it 
	// can be released
}

void CMainFrame::setMgaProj()
{
	IDispatch *disp;

	disp = mGmeOleApp->GetIDispatch(FALSE);	// do not increment the refcount

	m_console.SetGMEProj(disp);
}

void CMainFrame::clearGmeOleApp()
{
	m_console.SetGMEProj( 0 );
	m_console.SetGMEApp( 0 );

	//this line is needed either in setGmeOleApp or here
	//mGmeOleApp->GetIDispatch(FALSE)->Release();

	// make sure
	mGmeOleApp = 0;
}

void CMainFrame::clearMgaProj()
{
	m_console.SetGMEProj( 0 );
}


void CMainFrame::OnClose()
{
	clearGmeOleApp();
	CMDIFrameWndEx::OnClose();
}

int CMainFrame::CreateToolBars()
{
	
	// 3 separate TOOLBARs are created
	//#define AFX_IDW_CONTROLBAR_FIRST        0xE800 = 59392
	//#define AFX_IDW_CONTROLBAR_LAST         0xE8FF
	//
	//#define AFX_IDW_TOOLBAR                 0xE800  // main Toolbar for window
	//#define AFX_IDW_STATUS_BAR              0xE801  // Status bar window
	//#define AFX_IDW_PREVIEW_BAR             0xE802  // PrintPreview Dialog Bar
	//#define AFX_IDW_RESIZE_BAR              0xE803  // OLE in-place resize bar
	//#define AFX_IDW_REBAR                   0xE804  // COMCTL32 "rebar" Bar
	//#define AFX_IDW_DIALOGBAR               0xE805  // CDialogBar
	//#define AFX_IDW_DOCKBAR_TOP             0xE81B
	//#define AFX_IDW_DOCKBAR_LEFT            0xE81C
	//#define AFX_IDW_DOCKBAR_RIGHT           0xE81D
	//#define AFX_IDW_DOCKBAR_BOTTOM          0xE81E
	//#define AFX_IDW_DOCKBAR_FLOAT           0xE81F = 59423

	// thus the IDW_TOOLBAR_* ids conform to these limits
	// being assigned numbers from 0xE820


		// Checking resolution
	CWindowDC dc(NULL);
	bool bHiColorIcons = dc.GetDeviceCaps(BITSPIXEL) >= 16;






	// -- MAIN ToolBar
/*	if( !m_wndToolBarMain.CreateEx(this
		, TBSTYLE_FLAT
		, WS_CHILD |  WS_VISIBLE | CBRS_ALIGN_TOP
		, CRect(0,0,0,0)
		, IDW_TOOLBAR_MAIN) // provide unqiue ID for each toolbar [important !!!]
		||
		!m_wndToolBarMain.LoadToolBar(IDR_TOOLBAR_MAIN)
		)
	{
		TRACE0("Failed to create main toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBarMain.SetPaneStyle(m_wndToolBarMain.GetPaneStyle()
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

*/

	if( !m_wndToolBarMain.CreateEx(this
		, TBSTYLE_FLAT
		, WS_CHILD |  WS_VISIBLE | CBRS_ALIGN_TOP
		, CRect(0,0,0,0)
		, IDW_TOOLBAR_MAIN) // provide unqiue ID for each toolbar [important !!!]
		||
		!m_wndToolBarMain.LoadToolBar(IDR_TOOLBAR_MAIN, 0, 0, FALSE, 0, 0, bHiColorIcons ? IDB_MAIN_TOOLBAR24 : 0)
		)
	{
		TRACE0("Failed to create main toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBarMain.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));

	// Enable toolbar and docking window menu replacement
	EnablePaneMenu(TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."), ID_VIEW_TOOLBAR, FALSE, TRUE);


	// -- Modeling ToolBar
	if( !m_wndToolBarModeling.CreateEx(this
		, TBSTYLE_FLAT
		, WS_CHILD |  WS_VISIBLE | CBRS_ALIGN_TOP
		, CRect(0,0,0,0)
		, IDW_TOOLBAR_MODELING) // provide unqiue ID for each toolbar [important !!!]
		||
		!m_wndToolBarModeling.LoadToolBar(IDR_TOOLBAR_MODELING, 0, 0, FALSE, 0, 0, bHiColorIcons ? IDB_MODELING_TOOLBAR24 : 0)
		)
	{
		TRACE0("Failed to create modeling toolbar\n");
		return -1;      // fail to create
	}

	m_wndToolBarModeling.SetPaneStyle( m_wndToolBarModeling.GetPaneStyle()
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBarModeling.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));

	// -- Window Arrangement ToolBar
	if( !m_wndToolBarWins.CreateEx( this
		, TBSTYLE_FLAT
		, WS_CHILD |  WS_VISIBLE | CBRS_ALIGN_TOP
		, CRect(0,0,0,0)
		, IDW_TOOLBAR_WINS) // provide unqiue ID for each toolbar
		||
		!m_wndToolBarWins.LoadToolBar(IDR_TOOLBAR_WINS, 0, 0, FALSE, 0, 0, bHiColorIcons ? IDB_WINS_TOOLBAR24 : 0)
		)
	{
		TRACE0("Failed to create windows toolbar\n");
		return -1;
	}

	m_wndToolBarWins.SetPaneStyle( m_wndToolBarWins.GetPaneStyle()
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	m_wndToolBarWins.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));

	// -- User-defined Component ToolBar
	if( !m_wndComponentBar.CreateEx(this
		, TBSTYLE_FLAT
		, WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP
		, CRect(0, 0, 0, 0)
		, IDW_TOOLBAR_DUMMY) // provide unqiue ID for each toolbar
		||
	   !m_wndComponentBar.LoadToolBar(IDR_TOOLBAR_DUMMY, 0, 0, TRUE)
	   )
	{
		TRACE0("Failed to create component toolbar\n");
		return -1;      // fail to create
	}
	m_wndComponentBar.SetPaneStyle(m_wndComponentBar.GetPaneStyle()
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	m_wndComponentBar.SetBorders( 5, 0, 5, 0);


//	m_wndComponentBar.EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));


	// Mode toolbar

	modeBar.CreateEx(CMainFrame::theInstance,
		TBSTYLE_TRANSPARENT | TBSTYLE_FLAT, 
		WS_CHILD|WS_VISIBLE|CBRS_ALIGN_LEFT, 
		CRect(0,0,0,0),
		IDW_TOOLBAR_MODE);	// provide unqiue ID for each toolbar [important !!!] 
							// see MainFrm.cpp OnCreate for other details
	modeBar.LoadToolBar(IDR_TOOLBAR_MODE, 0, 0, FALSE, 0, 0, bHiColorIcons ? IDB_MODE_TOOLBAR24 : 0);
	modeBar.SetPaneStyle(modeBar.GetPaneStyle() 
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);


	// Navigation toolbar
	naviBar.CreateEx( CMainFrame::theInstance,
		TBSTYLE_TRANSPARENT | TBSTYLE_FLAT,
		WS_CHILD|WS_VISIBLE|CBRS_ALIGN_LEFT,
		CRect(0,0,0,0),
		IDW_TOOLBAR_NAVIG); // unique!
	naviBar.LoadToolBar(IDR_TOOLBAR_NAVIG, 0, 0, FALSE, 0, 0, bHiColorIcons ? IDB_NAVIG_TOOLBAR24 : 0);
	naviBar.SetPaneStyle(naviBar.GetPaneStyle()
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);



	// --- Docking ---
	// Toolbars are dockable to any side of the frame
	m_wndToolBarMain.SetWindowText(_T("Standard"));
	m_wndToolBarMain.EnableDocking(CBRS_ALIGN_ANY);

	m_wndToolBarModeling.SetWindowText(_T("Modeling"));
	m_wndToolBarModeling.EnableDocking(CBRS_ALIGN_ANY);

	m_wndToolBarWins.SetWindowText(_T("Windows"));
	m_wndToolBarWins.EnableDocking(CBRS_ALIGN_ANY);

	m_wndComponentBar.SetWindowText(_T("Components"));
	m_wndComponentBar.EnableDocking(CBRS_ALIGN_ANY);

	modeBar.SetWindowText(_T("Mode")); // will show this title when floating
	modeBar.EnableDocking(CBRS_ALIGN_ANY);

	naviBar.EnableDocking(CBRS_ALIGN_ANY);
	naviBar.SetWindowText(_T("Navigator")); // will show this title when floating



	DockPane(&m_wndToolBarMain/*,AFX_IDW_DOCKBAR_TOP*/);

	// place next to the main toolbar
	DockPane(&m_wndToolBarModeling/*, AFX_IDW_DOCKBAR_TOP*/);

	// place next to the modeling toolbar
	DockPane(&m_wndToolBarWins/*, AFX_IDW_DOCKBAR_TOP*/);

	// place next to the wins toolbar
	DockPane(&m_wndComponentBar/*, AFX_IDW_DOCKBAR_TOP*/);

	DockPane(&modeBar,AFX_IDW_DOCKBAR_LEFT);
	
	DockPane(&naviBar,AFX_IDW_DOCKBAR_LEFT);

	// Hide navigation and mode panels first, they are visible when a model is open
	ShowNavigationAndModeToolbars(false);


	// Allow user-defined toolbars operations:
	InitUserToolbars(NULL, uiFirstUserToolBarId, uiLastUserToolBarId);


	return 0;
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Creating tabs for the MDI Children (documents)
	CMDITabInfo mdiTabParams;
	mdiTabParams.m_style = CMFCTabCtrl::STYLE_3D_VS2005; // other styles available...
	mdiTabParams.m_bActiveTabCloseButton = TRUE;      // set to FALSE to place close button at right of tab area
	mdiTabParams.m_bTabIcons = FALSE;    // set to TRUE to enable document icons on MDI taba
	mdiTabParams.m_bAutoColor = TRUE;    // set to FALSE to disable auto-coloring of MDI tabs
	mdiTabParams.m_bDocumentMenu = TRUE; // enable the document menu at the right edge of the tab area
	EnableMDITabbedGroups(TRUE, mdiTabParams);

	CMFCToolBar::EnableQuickCustomization ();

	// Set the visual manager and style based on persisted value
	OnApplicationLook(theApp.m_nAppLook);
	
	EnableDocking(CBRS_ALIGN_ANY);



	// STATUS BAR
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	
	CMFCToolBar::EnableQuickCustomization();
	
	// MENU BAR
	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndMenuBar.EnableDocking(CBRS_ALIGN_TOP);
	DockPane(&m_wndMenuBar, AFX_IDW_DOCKBAR_TOP);
	
	// prevent the menu bar from taking the focus on activation
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	// TOOLBARS
	if(CreateToolBars())
	{
		return -1;
	}


	// Enable enhanced windows management dialog
	EnableWindowsDialog(ID_WINDOW_MANAGER, _T("Model windows..."), TRUE);

	


	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);

	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);



	// PART BROWSER
	if (!m_partBrowser.Create(_T("Part Browser"), this, CSize(240,480),
		TRUE, ID_PARTBROWSER, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT| CBRS_FLOAT_MULTI))
	{
			TRACE0("Failed to create part browser\n");
			return -1;	// fail to create
	}
	m_partBrowser.EnableDocking(CBRS_ALIGN_ANY);


	// terge 
	// PANNING WINDOW
	if (!m_panningWindow.Create(_T("Panning Window"), this, CSize(240, 160),
		TRUE, ID_PANNWIN, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create panning Window\n");
		return -1;      // fail to create
	}
	
	m_panningWindow.EnableDocking(CBRS_ALIGN_ANY);


	// GME ACTIVE BROWSER TREE
	if (!m_browser.Create(_T("GME Browser"), this, CSize(240, 80),
        	TRUE, ID_GMEBROWSER, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create browser\n");
		return -1;      // fail to create
	}
	
	m_browser.EnableDocking(CBRS_ALIGN_ANY);
	

	// OBJECT INSPECTOR
	if(!m_objectInspector.Create(_T("Object Inspector"), this, CSize(240, 160),
		TRUE,IDD_OBJECT_INSPECTOR_DIALOG, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
        TRACE0("Failed to create Object Inspector\n");
        return -1;      // fail to create
	}
	
	m_objectInspector.EnableDocking(CBRS_ALIGN_ANY);



	// CONSOLE
	if(!m_console.Create(_T("Console"), this, CSize(80, 160),
		TRUE,IDD_CONSOLE_DIALOG, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
        TRACE0("Failed to create Console\n");
        return -1;      // fail to create
	}

	m_console.EnableDocking(CBRS_ALIGN_ANY);



	// SEARCH - Modal Dialog
	if(!m_search.Create(MAKEINTRESOURCE(CGMESearch::IDD), this))
	{
        TRACE0("Failed to create Search Control\n");
        return -1;      // fail to create
	}


	// --- Docking ---

	DockPane(&m_browser, AFX_IDW_DOCKBAR_RIGHT);
	
	DockPane(&m_partBrowser, AFX_IDW_DOCKBAR_LEFT);

	m_panningWindow.DockToWindow(&m_partBrowser, CBRS_ALIGN_BOTTOM);
	
	
	m_objectInspector.DockToWindow(&m_browser,CBRS_ALIGN_BOTTOM);

	DockPane(&m_console,AFX_IDW_DOCKBAR_BOTTOM);



	// CG: The following block was inserted by 'Status Bar' component.
	{
		// Find out the size of the static variable 'indicators' defined
		// by AppWizard and copy it
		int nOrigSize = sizeof(indicators) / sizeof(UINT);

		UINT pIndicators[16];
		memcpy(pIndicators, indicators, sizeof(indicators));

		// Call the Status Bar Component's status bar creation function
		if (!InitStatusBar(pIndicators, nOrigSize, 60))
		{
			TRACE0("Failed to initialize Status Bar\n");
			return -1;
		}
	}

	// hide initially, openProject will show it if components available
	// thus we ignore the registry settings
	m_wndComponentBar.ShowWindow(SW_HIDE);

	// CG: The following line was added by the Splash Screen component.
	CSplashWnd::ShowSplashScreen(this);

	// Adding full screen functionality
	EnableFullScreenMode(ID_VIEW_FULLSCREEN);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWndEx::Dump(dc);
}

#endif //_DEBUG

void CMainFrame::UpdateTitle(LPCTSTR title)
{
	UpdateFrameTitleForDocument(title);
}

void CMainFrame::DestroyView(CView *view)
{
	ASSERT(view);
	CFrameWnd *frame = view->GetParentFrame();
	ASSERT(frame);
	frame->DestroyWindow();
}

void CMainFrame::ActivateView(CView *view)
{
	ActivateFrame();
	ASSERT(view);
	CFrameWnd *frame = view->GetParentFrame();
	ASSERT(frame);
	CFrameWnd *activeFrame = GetActiveFrame();
	ASSERT(activeFrame);
	if(frame != activeFrame)
		frame->ActivateFrame(frame->IsIconic() ? SW_SHOWNORMAL : -1);
}

void CMainFrame::CreateNewView(CView *view, CComPtr<IMgaModel>& model)
{
	CMultiDocTemplate *docTemplate = theApp.pDocTemplate;
	if(view != 0) {
		ActivateView(view);
	}
	else {
		CDocument *pDocument = CGMEDoc::theInstance;
		ASSERT( pDocument );

		CFrameWnd *pFrame = docTemplate->CreateNewFrame(pDocument, NULL);
		if(pFrame == NULL) {
			AfxMessageBox("Failed to create window",MB_OK | MB_ICONSTOP);
			return;
		}
		docTemplate->InitialUpdateFrame(pFrame,pDocument);

#if defined(ACTIVEXGMEVIEW)
		CMainFrame* pMainFrame = (CMainFrame*)theApp.m_pMainWnd;
		// Get the active MDI child window.
		CMDIChildWnd* pChild = (CMDIChildWnd*)pMainFrame->GetActiveFrame();
		// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
		// Get the active view attached to the active MDI child window.
		CGMEChildFrame* pView = (CGMEChildFrame*)pChild->GetActiveView();
		pView->SetProject(theApp.mgaProject);

		m_partBrowser.SetProject(theApp.mgaProject);
		try {
			long status;
			COMTHROW(theApp.mgaProject->get_ProjectStatus(&status));
			bool inTrans = (status & 0x08L) != 0;
			CComPtr<IMgaTerritory> terr;
			if (!inTrans) {
				COMTHROW(theApp.mgaProject->CreateTerritory(NULL, &terr));
				COMTHROW(theApp.mgaProject->BeginTransaction(terr, TRANSACTION_READ_ONLY));
			} else {
				COMTHROW(theApp.mgaProject->get_ActiveTerritory(&terr));
			}

			CComPtr<IMgaFCO> modelFco;
			COMTHROW(terr->OpenFCO(model, &modelFco));
			CComQIPtr<IMgaModel> model2 = modelFco;

			status = OBJECT_ZOMBIE;
			COMTHROW(model2->get_Status(&status));
			if (status == OBJECT_EXISTS) {
				CComPtr<IMgaMetaFCO> ccpMetaFCO;
				COMTHROW(model2->get_Meta(&ccpMetaFCO));
				CComQIPtr<IMgaMetaModel> metaModel = ccpMetaFCO;
				metaref_type metaid;
				COMTHROW(metaModel->get_MetaRef(&metaid));
				CGuiMetaModel* guiMeta = CGuiMetaProject::theInstance->GetGuiMetaModel(metaid);
				m_partBrowser.SetMetaModel(guiMeta);
				pView->SetMetaModel(guiMeta);
				pView->ChangeAspect(0);
				m_partBrowser.SetBgColor(RGB(0xFF, 0xFF, 0xFF));
				m_partBrowser.ChangeAspect(0);
				m_partBrowser.RePaint();
			}

			if (!inTrans) {
				theApp.mgaProject->CommitTransaction();
			}
		} catch(...) {
			ASSERT(0);
		}
		pView->SetModel(model);
#endif
	}
}

void CMainFrame::WriteStatusMode(const CString& txt)
{
	WriteStatusText(modePaneNo,txt);
}

void CMainFrame::WriteStatusParadigm(const CString& txt)
{
	WriteStatusText(paradigmPaneNo,txt);
}

void CMainFrame::WriteStatusZoom(int zoomPct)
{
	CString txt;
	txt.Format("%d%%", zoomPct);
	WriteStatusText(zoomPaneNo,txt);
}

void CMainFrame::WriteStatusText(int pane, const CString& txt)
{
	CSize size;
	{
		HGDIOBJ hOldFont = NULL;
		HFONT hFont = (HFONT)m_wndStatusBar.SendMessage(WM_GETFONT);
		CClientDC dc(NULL);
		if (hFont != NULL) 
			hOldFont = dc.SelectObject(hFont);
		size = dc.GetTextExtent(txt);
		if (hOldFont != NULL) 
			dc.SelectObject(hOldFont);
	}
	
	int lng;
	UINT nID,nStyle;
	m_wndStatusBar.GetPaneInfo(pane, nID, nStyle, lng);
	m_wndStatusBar.SetPaneInfo(pane, nID, nStyle, size.cx);
    m_wndStatusBar.SetPaneText(pane,txt);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnUpdateTime(CCmdUI* /*pCmdUI*/)
{
	// CG: This function was inserted by 'Status Bar' component.

	// Get current date and format it
	CTime time = CTime::GetCurrentTime();
	CString strTime = time.Format(_T("%I:%M  "));
	strTime = (time.GetHour() < 12 ? _T("") : _T(""))+ strTime +(time.GetHour() < 12 ? _T("AM "):_T("PM "));

	WriteStatusText(timePaneNo,strTime);
}

BOOL CMainFrame::InitStatusBar(UINT *pIndicators, int nSize, int nSeconds)
{
	modePaneNo = nSize++;
	pIndicators[modePaneNo] = ID_INDICATOR_MODE;
	zoomPaneNo = nSize++;
	pIndicators[zoomPaneNo] = ID_INDICATOR_ZOOM;
	paradigmPaneNo = nSize++;
	pIndicators[paradigmPaneNo] = ID_INDICATOR_PARADIGM;
	timePaneNo = nSize++;
	pIndicators[timePaneNo] = ID_INDICATOR_TIME;

	nSeconds = 10;
	m_wndStatusBar.SetTimer(0x1000, nSeconds * 1000, NULL);

	return m_wndStatusBar.SetIndicators(pIndicators, nSize);
}


void CMainFrame::OnEditSearch() 
{
	m_search.ShowWindow(SW_SHOWNORMAL);
	CComPtr<IMgaObjects> objs;
	if( CGMEBrowser::theInstance->GetSelectedItems( objs))
		m_search.SetSelMgaObjects( objs);
	m_search.SetFocus(); // allows for easy 'Find Next' feature
	// the user might press ^F whenever she'd like to jump
	// to a focused searchbox
}

void CMainFrame::OnUpdateEditSearch(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(
		(CGMEDoc::theInstance != 0) &&
		m_search &&
		1 //(!m_search.IsWindowVisible()) 
		// from now on will allow multiple ^F-s, and as a result it 
		// will set focus back to search window (like in VStudio).
		// allows for easy 'Find Next'-like functionality
		);
}


void CMainFrame::SetGMEViewMetaModel(CGuiMetaModel* meta)
{
	CDocument* pDocument = CGMEDoc::theInstance;
	POSITION pos = pDocument->GetFirstViewPosition();
	if (pos) {
		while (pos != NULL) {
#if defined(ACTIVEXGMEVIEW)
			CGMEChildFrame* pView = (CGMEChildFrame*) pDocument->GetNextView(pos);
			pView->SetMetaModel(meta);
#endif
		}
	}
}

void CMainFrame::ChangeGMEViewAspect(int ind)
{
	CDocument* pDocument = CGMEDoc::theInstance;
	POSITION pos = pDocument->GetFirstViewPosition();
	if (pos) {
		while (pos != NULL) {
#if defined(ACTIVEXGMEVIEW)
			CGMEChildFrame* pView = (CGMEChildFrame*) pDocument->GetNextView(pos);
			pView->ChangeAspect(ind);
#endif
		}
	}
}

void CMainFrame::CycleGMEViewAspect()
{
	CDocument* pDocument = CGMEDoc::theInstance;
	POSITION pos = pDocument->GetFirstViewPosition();
	if (pos) {
		while (pos != NULL) {
#if defined(ACTIVEXGMEVIEW)
			CGMEChildFrame* pView = (CGMEChildFrame*) pDocument->GetNextView(pos);
			pView->CycleAspect();
#endif
		}
	}
}

void CMainFrame::GMEViewInvalidate()
{
	CDocument* pDocument = CGMEDoc::theInstance;
	POSITION pos = pDocument->GetFirstViewPosition();
	if (pos) {
		while (pos != NULL) {
#if defined(ACTIVEXGMEVIEW)
			CGMEChildFrame* pView = (CGMEChildFrame*) pDocument->GetNextView(pos);
			pView->Invalidate();
#endif
		}
	}
}


// This function is Copyright (c) 2000, Cristi Posea.
// See www.datamekanix.com for more control bars tips&tricks.
BOOL CMainFrame::VerifyBarState(LPCTSTR lpszProfileName)
{
    CDockState state;
    state.LoadState(lpszProfileName);

    for (int i = 0; i < state.m_arrBarInfo.GetSize(); i++)
    {
        CControlBarInfo* pInfo = (CControlBarInfo*)state.m_arrBarInfo[i];
        ASSERT(pInfo != NULL);
        int nDockedCount = pInfo->m_arrBarID.GetSize();
        if (nDockedCount > 0)
        {
            // dockbar
            for (int j = 0; j < nDockedCount; j++)
            {
                UINT nID = (UINT) pInfo->m_arrBarID[j];
                if (nID == 0) continue; // row separator
                if (nID > 0xFFFF)
                    nID &= 0xFFFF; // placeholder - get the ID
                if (GetControlBar(nID) == NULL)
                    return FALSE;
            }
        }
        
        if (!pInfo->m_bFloating) // floating dockbars can be created later
            if (GetControlBar(pInfo->m_nBarID) == NULL)
                return FALSE; // invalid bar ID
    }

    return TRUE;
}

void CMainFrame::OnDeleteDCForPanningVindowCtrl(CDC* bCDC)
{
	// TODO: forward to view control later
	if (bCDC != NULL) {
		CBitmap* bmp = bCDC->GetCurrentBitmap();
		delete bCDC;
		if (bmp)
			delete bmp;
	}
}

BOOL CMainFrame::DestroyWindow() 
{	
	return CMDIFrameWndEx::DestroyWindow();
}

void CMainFrame::ShowObjectInspector()
{
    ShowPane(&m_objectInspector, TRUE, FALSE, TRUE);
}

void CMainFrame::ShowFindDlg()
{
	OnEditSearch();
}

void CMainFrame::HideFindDlg()
{
	m_search.SetSelMgaObjects( CComPtr<IMgaObjects>( 0));
	m_search.ShowWindow( SW_HIDE);
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == GME_AUTOSAVE_EVENT_ID) {
		theApp.Autosave();
	}
	
	CMDIFrameWndEx::OnTimer(nIDEvent);
}


void CMainFrame::StartAutosaveTimer(int secs)
{
	StopAutosaveTimer();
	ASSERT(m_autosaveTimerID == NULL);

	m_autosaveTimerID = SetTimer(GME_AUTOSAVE_EVENT_ID, 1000 * secs, NULL);
}

void CMainFrame::StopAutosaveTimer()
{
	if (m_autosaveTimerID) {
		KillTimer(m_autosaveTimerID);
		m_autosaveTimerID = NULL;
	}	
}



void CMainFrame::OnDestroy() 
{
	CMDIFrameWndEx::OnDestroy();
	
	StopAutosaveTimer();
}


/*
IMgaObject*	CMainFrame::folderFindByPath(IMgaFolder* folder, const wstring& strPath)
{
	wstring strPath2;
	wstring strName;
	wstring::size_type iPos = strPath.find( L"/" );
	if ( iPos == wstring::npos ) 
	{
		strName = strPath;
		strPath2 = L"";
	}
	else {
		if ( iPos == 0 )
			strPath2 = strPath.substr( iPos + 1);
		iPos = strPath2.find( L"/" );
		if ( iPos == wstring::npos ) 
		{
			strName = strPath2;
			strPath2 = L"";
*		}
		else 
		{
			strName = strPath2.substr( 0, iPos );
			strPath2 = strPath2.substr( iPos );
		}
	}
	COMTRY {
		CComPtr<IMgaFolder> root;
		if (!folder)
		{
			COMTHROW(theApp.mgaProject->get_RootFolder(&root));
			if (!root)
				return NULL;
			CComBSTR strname;
			COMTHROW(root->get_Name(&strname));
			if ( strName == (wstring)(WCHAR*)(BSTR)strname) 
			{
				if ( strPath2.empty() )
				{
					CComPtr<IMgaObject> obj;
					root.QueryInterface(&obj);
					return obj.Detach();
				}
				else 
				{
					IMgaObject* o = folderFindByPath(root,  strPath2);
					if (o)
						return o;
				}
			}
			return NULL;
		}

		CComPtr<IMgaObjects> iobjects;
		COMTHROW(folder->get_ChildObjects(&iobjects));
		CComPtr<IMgaObject> item;
		long count = 0;
		COMTHROW(iobjects->get_Count(&count));
		for (int i=1; i<=count; i++)
		{
			COMTHROW(iobjects->get_Item(i, &item));
			CComBSTR strname;
			COMTHROW(item->get_Name(&strname));
			if ( strName == (wstring)(WCHAR*)(BSTR)strname) 
			{
				if ( strPath2.empty() )
					return item.Detach();
				else 
				{
					CComPtr<IMgaModel> model;
					CComPtr<IMgaFolder> folder;
					item.QueryInterface(&model);
					item.QueryInterface(&folder);
					if ( model) 
					{
						IMgaObject *o = modelFindByPath(model,  strPath2);
						if (o)
							return o;
					}
					if ( folder) 
					{
						IMgaObject* o = folderFindByPath(folder,  strPath2);
						if (o)
							return o;
					}
				}
			}
			item.Release();
		}
	} 
	catch(hresult_exception &e) 
	{ 
		// SetErrorInfo(e.hr); 
		return NULL; 
	} 

	return NULL;
}


IMgaObject*	CMainFrame::modelFindByPath(IMgaModel *model,  const wstring& strPath)
{
	wstring strPath2;
	wstring strName;
	wstring::size_type iPos = strPath.find( L"/" );
	if ( iPos == wstring::npos ) 
	{
		strName = strPath;
		strPath2 = L"";
	}
	else 
	{
		if ( iPos == 0 )
			strPath2 = strPath.substr( iPos + 1);
		iPos = strPath2.find( L"/" );
		if ( iPos == wstring::npos ) 
		{
			strName = strPath2;
			strPath2 = L"";
		}
		else 
		{
			strName = strPath2.substr( 0, iPos );
			strPath2 = strPath2.substr( iPos );
		}
	}

	COMTRY {
		CComPtr<IMgaFCOs> fcos;
		COMTHROW(model->get_ChildFCOs(&fcos));
		CComPtr<IMgaFCO> item;
		long count = 0;
		COMTHROW(fcos->get_Count(&count));
		for (int i=1; i<=count; i++)
		{
			COMTHROW(fcos->get_Item(i, &item));
			CComBSTR strname;
			COMTHROW(item->get_Name(&strname));
			if ( strName == (wstring)(WCHAR*)(BSTR)strname) 
			{
				if ( strPath2.empty() )
					return item.Detach();
				else 
				{
					CComPtr<IMgaModel> model;
					item.QueryInterface(&model);
					if (model )
					{
						IMgaObject* o = modelFindByPath(model,  strPath2);
						if (o)
							return o;
					}

				}
			}
			item.Release();
		}
	} 
	catch(hresult_exception &e) 
	{ 
		// SetErrorInfo(e.hr); 
		return NULL; 
	} 

	return NULL;
}
*/



void CMainFrame::OnViewMultiUserRefreshSourceControl() 
{
	BeginWaitCursor();
	try
	{
		theApp.mgaProject->UpdateSourceControlInfo( 0);
		m_browser.RefreshAll();
	}
	catch(...)
	{
	}  
	EndWaitCursor();
}

void CMainFrame::OnUpdateViewMultiUserRefreshSourceControl(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( theApp.isMultiUserProj() && CGMEDoc::theInstance != 0);
}

void CMainFrame::OnViewMultiUserActiveUsers() 
{
	BeginWaitCursor();
	try
	{
		theApp.mgaProject->SourceControlActiveUsers();
	}
	catch(...) { ASSERT(0); }
	EndWaitCursor();
}

void CMainFrame::OnUpdateViewMultiUserActiveUsers(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( !CGMEDoc::theInstance || !theApp.isMgaProj()); // always TRUE (also when no project is open) except when mga_proj is open
}

void CMainFrame::OnUpdateViewMultiUserSubversion(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( !CGMEDoc::theInstance || !theApp.isMgaProj()); // always TRUE (also when no project is open) except when mga_proj is open
}

void CMainFrame::OnViewMultiUserSubversion()
{
	try
	{
		CComPtr<ISvnWorkBench> wb;
		HRESULT hr = wb.CoCreateInstance( L"Mga.XmlBackEnd.SvnWorkBench");
		if( FAILED( hr) || !wb) {
			AfxMessageBox( "Could not create Svn Work Bench!");
			return;
		}

		wb->SetClues( CComBSTR( (LPCTSTR) theApp.connString()));
		wb->ShowWorkBenchDlg();
	}
	catch(...) { ASSERT(0); }
}

void CMainFrame::OnViewClearConsole() 
{
	m_console.Clear();
}

void CMainFrame::OnUpdateViewClearConsole(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
}

void CMainFrame::OnDropFiles(HDROP p_hDropInfo)
{
	CGMEEventLogger::LogGMEEvent("MainFrame:OnDropFiles\r\n");
	
	// get the number of files dropped
	UINT nFiles = DragQueryFile( p_hDropInfo, 0xFFFFFFFF, NULL, 0);
	if( nFiles < 1)
	{
		CGMEEventLogger::LogGMEEvent("Can't inquire file information!\r\n");
		m_console.Message( "No file dropped or can't inquire file information!", 3);
	}

	bool one_just_opened = false; // we opened/imported one project just now -> disables opening of more .mga files
	for( UINT iF = 0; iF < nFiles; ++iF)
	{
		TCHAR szFileName[_MAX_PATH];
		UINT res = DragQueryFile( p_hDropInfo, iF, szFileName, _MAX_PATH);
		if (res > 0)
		{
			bool is_dir = false; 
			struct _stat fstatus;
			if( 0 == _tstat( szFileName, &fstatus))
				is_dir = (fstatus.st_mode & _S_IFDIR) == _S_IFDIR;
			
			CString conn( szFileName);
			if( is_dir || conn.Right(4).CompareNoCase(".mga") == 0 || conn.Right(4).CompareNoCase(".mgx") == 0)
			{
				if( one_just_opened)
					m_console.Message( "Project already open. No other MGA file can be dropped!", 3);
				else if( theApp.guiMetaProject == NULL && theApp.mgaProject == 0)
				{
					if( conn.Right(4).CompareNoCase(".mga") == 0) {
						m_console.Message( "Opening " + conn + ".", 1);
						conn = "MGA=" + conn;
					} else {
						int pos = conn.ReverseFind( '\\'); // we don't need the file name, only the path
						if( is_dir)
							conn = "MGX=\"" + conn + "\""; // directory dropped
						else if( pos != -1)
							conn = "MGX=\"" + conn.Left( pos) + "\""; // the .mgx file dropped, cut off the file part
						m_console.Message( "Opening multiuser project " + conn + ".", 1);
					}
					theApp.OpenProject(conn);
					one_just_opened = true;
				}
				else
					m_console.Message( "Another MGA file can't be opened while a project is open.", 3);
			}
			else if( conn.Right(4).CompareNoCase(".xme")==0)
			{
				m_console.Message( "Importing " + conn + ".", 1);	
				theApp.ImportDroppedFile(conn);
				one_just_opened = true;
			}
			else if( conn.Right(4).CompareNoCase(".xmp")==0 || conn.Right(4).CompareNoCase(".mta")==0)
			{
				if( theApp.guiMetaProject == NULL && theApp.mgaProject == 0) // no project opened
				{
					m_console.Message( "Registering " + conn + " as a paradigm.", 1);

					theApp.RegisterDroppedFile( conn.Right(4).CompareNoCase(".xmp")==0?"XML=" + conn:"MGA=" + conn);
					one_just_opened = false; // we did not open a file, just registered
				}
				else
					m_console.Message( "Can't register paradigm file while project is open!", 3);
			}
			else
				m_console.Message( ".MGX, .MGA, .XME, .MTA, .XMP files may be dropped only. Can't open file: " + conn + "!", 3);
		}
		else
			m_console.Message( "Can't inquire file information!", 3);
	}
}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	return CMDIFrameWndEx::PreTranslateMessage(pMsg);
}


void CMainFrame::OnBtnBack()
{
	if( !theApp.isHistoryEnabled() || !CGMEDoc::theInstance) return;
	CGMEDoc::theInstance->back();
}

void CMainFrame::OnUpdateBtnBack(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( theApp.isHistoryEnabled() && CGMEDoc::theInstance && CGMEDoc::theInstance->m_historian.isEnabledBack());
}

void CMainFrame::OnBtnHome()
{
	if( !theApp.isHistoryEnabled() || !CGMEDoc::theInstance) return;
	CGMEDoc::theInstance->home();
}

void CMainFrame::OnUpdateBtnHome(CCmdUI* pCmdUI)
{
	pCmdUI->Enable( theApp.isHistoryEnabled() && CGMEDoc::theInstance && CGMEDoc::theInstance->m_historian.isEnabledHome());
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);

}


void CMainFrame::OnWindowManager()
{
	ShowWindowsDialog();
}

void CMainFrame::OnViewCustomize()
{
	CMFCToolBarsCustomizeDialog* pDlgCust = new CMFCToolBarsCustomizeDialog(this, TRUE /* scan menus */);
	pDlgCust->EnableUserDefinedToolbars();
	pDlgCust->Create();
}

void CMainFrame::OnViewFullScreen()
{
	ShowFullScreen();
}


/*

void CMainFrame::OnHelpKeyboardmap()
{
	CMFCKeyMapDialog dlg(this, TRUE ); // Enable Print
	dlg.DoModal();
}

*/

LRESULT CMainFrame::OnToolbarCreateNew(WPARAM wp,LPARAM lp)
{
	LRESULT lres = CMDIFrameWndEx::OnToolbarCreateNew(wp,lp);
	if (lres == 0)
	{
		return 0;
	}

	CMFCToolBar* pUserToolbar = (CMFCToolBar*) lres;
	ASSERT_VALID(pUserToolbar);

	pUserToolbar->EnableCustomizeButton(TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));
	return lres;
}

void CMainFrame::OnWindowNewhorizontaltabgroup()
{
	MDITabNewGroup(FALSE);
}

void CMainFrame::OnWindowNewverticaltabgroup()
{
	MDITabNewGroup();
}

void CMainFrame::OnWindowMovetoprevioustabgroup()
{
	MDITabMoveToNextGroup(FALSE);
}

void CMainFrame::OnWindowMovetonexttabgroup()
{
	MDITabMoveToNextGroup();
}



void CMainFrame::ShowNavigationAndModeToolbars(bool isVisible)
{
	ShowPane(&modeBar, isVisible, FALSE, FALSE);
	ShowPane(&naviBar, isVisible, FALSE, FALSE);	
}

void CMainFrame::OnUpdateWindowNew(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(FALSE);
}
