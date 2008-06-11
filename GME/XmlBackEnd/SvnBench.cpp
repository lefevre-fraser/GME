// SvnBench.cpp : implementation file
//

#include "stdafx.h"
#include "SvnBench.h"
#include "SvnHelper.h"
#include <process.h>


// CSvnBench dialog

IMPLEMENT_DYNAMIC(CSvnBench, CDialog)
CSvnBench::CSvnBench(CWnd* pParent /*=NULL*/)
	: CDialog(CSvnBench::IDD, pParent)
	, m_bRecursive(FALSE)
	, m_bCmdExeOrAPI(FALSE) // API
	, m_lstStringVal(_T(""))
	, m_leftPad( 20)
	, m_rightPad( 20)
{
}

CSvnBench::~CSvnBench()
{
}

void CSvnBench::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_bRecursive);
	DDX_Radio(pDX, IDC_RADIO1, m_bCmdExeOrAPI);
	DDX_Control(pDX, IDC_COMBO_URL_AND_PATH, m_lst);
	DDX_CBString(pDX, IDC_COMBO_URL_AND_PATH, m_lstStringVal);
}

void CSvnBench::init( CString p_connString)
{
	m_connStr = p_connString;
}

void CSvnBench::exec( CString p_cmd, CString p_startupDir)
{
	STARTUPINFO          startup_info;
	PROCESS_INFORMATION  process_info;

	char *env_CMD        = NULL;
	char *default_CMD    = "CMD.EXE";
	char  args[4096];

	memset(&startup_info, 0, sizeof(startup_info)); // clear all members
	startup_info.cb = sizeof(STARTUPINFO);
	startup_info.dwFlags = STARTF_USESHOWWINDOW;
	startup_info.wShowWindow = SW_SHOW;

	args[0] = 0;

	env_CMD = getenv("COMSPEC");

	if(env_CMD) strcpy( args, env_CMD);
	else        strcpy( args, default_CMD);

	strcat( args, " ");
	strcat( args, (LPCTSTR) p_cmd); // p_cmd could be a subcommand of cmd.exe

	// if startup dir exists
	WIN32_FILE_ATTRIBUTE_DATA attr;
	BOOL  sc;
	BOOL fexists = GetFileAttributesEx( (LPCTSTR) p_startupDir, GetFileExInfoStandard, &attr );
	if( fexists)
	{
		if( FILE_ATTRIBUTE_DIRECTORY == ( attr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{} // nop, everything all right
		else // if( FILE_ATTRIBUTE_DIRECTORY != ( attr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			p_startupDir = p_startupDir.Mid( 0, p_startupDir.ReverseFind( '\\'));

	}
	else
	{
		AfxMessageBox( "Specified startup directory not found! Defaulting to current directory.");
		p_startupDir = "";
	}

	sc = CreateProcess( NULL, args, NULL, NULL, FALSE,
	                    CREATE_NEW_CONSOLE, NULL, fexists? (LPCTSTR) p_startupDir : NULL,
	                    &startup_info, &process_info
	                  );
	
	if( !sc)
	{
		long err = GetLastError();
		AfxMessageBox( "Could not launch cmd.exe!");
	}
}

BEGIN_MESSAGE_MAP(CSvnBench, CDialog)
	ON_BN_CLICKED(IDC_INFO_BUTTON, OnBnClickedInfoButton)
	ON_BN_CLICKED(IDC_STATUS_BUTTON, OnBnClickedStatusButton)
	ON_BN_CLICKED(IDC_CLEANUP_BUTTON, OnBnClickedCleanupButton)
	ON_BN_CLICKED(IDC_RESOLVE_BUTTON, OnBnClickedResolveButton)
	ON_BN_CLICKED(IDC_COMMIT_BUTTON, OnBnClickedCommitButton)
	ON_BN_CLICKED(IDC_CHECKOUT_BUTTON, OnBnClickedCheckoutButton)
	ON_BN_CLICKED(IDC_CMDEXE_BUTTON, OnBnClickedCmdexeButton)
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, OnBnClickedCloseButton)
	ON_BN_CLICKED(IDC_UPDATE_BUTTON, OnBnClickedUpdateButton)
	ON_BN_CLICKED(IDC_LOCK_BUTTON, OnBnClickedLockButton)
	ON_BN_CLICKED(IDC_UNLOCK_BUTTON, OnBnClickedUnlockButton)
	ON_BN_CLICKED(IDC_TESTCONN_BUTTON, OnBnClickedTestConnButton)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_HELPINFO()
	ON_NOTIFY_EX( TTN_NEEDTEXT, 0, OnToolTipNotify)
	ON_CBN_EDITCHANGE(IDC_COMBO_URL_AND_PATH, OnCbnEditchangeComboUrlAndPath)
END_MESSAGE_MAP()



BOOL CSvnBench::OnInitDialog()
{
	CDialog::OnInitDialog();
	EnableToolTips(TRUE);

	CRect lst_rect;
	if( m_lst.GetSafeHwnd()) {
		m_lst.GetWindowRect( &lst_rect);
		ScreenToClient( &lst_rect);

		CRect win_rect;
		GetWindowRect( &win_rect);
		ScreenToClient( &win_rect);

		m_leftPad = lst_rect.left - win_rect.left;
		m_rightPad = win_rect.right - lst_rect.right;
	}

	int p1 = m_connStr.Find( '"'); // MGX = "c:\t\myprojects\" svn="https://svn.isis.vanderbilt.edu/testrepo/gme/zoli" otherkey2="..."
	int p2 = m_connStr.Find( '"', p1 + 1);
	int p3 = m_connStr.Find( "svn=\"", p2 + 1);
	int p4 = m_connStr.Find( '"', p3 + 6);
	CString local_folder;
	CString server_path;
	if( p1 != -1 && p2 != -1)
		local_folder = m_connStr.Mid( p1 + 1, p2 - p1 - 1);

	if( p3 != -1 && p4 != -1)
		server_path = m_connStr.Mid( p3 + 5, p4 - p3 - 5);

	m_lst.InsertString( 0, server_path);
	m_lst.InsertString( 1, local_folder);

	//m_lst.SetCurSel( 0);
	//m_lst.InsertString( 0, "<<select from path below>>");
	m_lst.SetWindowText( "<<select from paths below>>");


	return TRUE;
}

int CSvnBench::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CSvnBench::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CRect lst_rect;
	if (m_lst.GetSafeHwnd()) {
		m_lst.GetWindowRect( &lst_rect);
		ScreenToClient( &lst_rect);
		int width = cx - m_leftPad - m_rightPad;

		m_lst.SetWindowPos( NULL, m_leftPad, lst_rect.top, width > 20? width: 20, lst_rect.Height(), SWP_NOZORDER);
		Invalidate(); // just for the sake of SIZEGRIP, which would leave spots otherwise
	}
}

// CSvnBench message handlers

void CSvnBench::OnOK()
{
	// when Enter is pressed, it should not end the Dialog
	//CDialog::OnOK();
}

void CSvnBench::OnBnClickedInfoButton()
{
	UpdateData( TRUE);
	BeginWaitCursor();
	save();
	try
	{
		CSvnHelper::invokeInfo( (LPCTSTR) m_lstStringVal, !m_bCmdExeOrAPI, m_bRecursive != 0);
	}
	catch(...) { ASSERT(0); }
	EndWaitCursor();
}

void CSvnBench::OnBnClickedStatusButton()
{
	UpdateData( TRUE);
	BeginWaitCursor();
	save();
	try
	{
		CSvnHelper::invokeStatus( (LPCTSTR) m_lstStringVal, !m_bCmdExeOrAPI);
	}
	catch(...) { ASSERT(0); }
	EndWaitCursor();
}

void CSvnBench::OnBnClickedCleanupButton()
{
	UpdateData( TRUE);
	BeginWaitCursor();
	save();
	try
	{
		CSvnHelper::invokeCleanUp( (LPCTSTR) m_lstStringVal, !m_bCmdExeOrAPI);
	}
	catch(...) { ASSERT(0); }
	EndWaitCursor();
}

void CSvnBench::OnBnClickedResolveButton()
{
	UpdateData( TRUE);
	BeginWaitCursor();
	save();
	try
	{
		CSvnHelper::invokeResolve( (LPCTSTR) m_lstStringVal, !m_bCmdExeOrAPI, m_bRecursive != 0);
	}
	catch(...) { ASSERT(0); }
	EndWaitCursor();
}


void CSvnBench::OnBnClickedCommitButton()
{
	UpdateData( TRUE);
	BeginWaitCursor();
	save();
	try
	{
		CSvnHelper::invokeCommit( (LPCTSTR) m_lstStringVal, !m_bCmdExeOrAPI);
	}
	catch(...) { ASSERT(0); }
	EndWaitCursor();
}

void CSvnBench::OnBnClickedUpdateButton()
{
	UpdateData( TRUE);
	BeginWaitCursor();
	save();
	try
	{
		CSvnHelper::invokeUpdate( (LPCTSTR) m_lstStringVal, !m_bCmdExeOrAPI);
	}
	catch(...) { ASSERT(0); }
	EndWaitCursor();
}

void CSvnBench::OnBnClickedLockButton()
{
	UpdateData( TRUE);
	BeginWaitCursor();
	save();
	try
	{
		CSvnHelper::invokeLock( (LPCTSTR) m_lstStringVal, !m_bCmdExeOrAPI);
	}
	catch(...) { ASSERT(0); }
	EndWaitCursor();
}

void CSvnBench::OnBnClickedUnlockButton()
{
	UpdateData( TRUE);
	BeginWaitCursor();
	save();
	try
	{
		CSvnHelper::invokeUnlock( (LPCTSTR) m_lstStringVal, !m_bCmdExeOrAPI);
	}
	catch(...) { ASSERT(0); }
	EndWaitCursor();
}

void CSvnBench::OnBnClickedCheckoutButton()
{
	UpdateData( TRUE);
	BeginWaitCursor();
	save();
	try
	{
		CString url_and_loc = m_lstStringVal.Trim();
		int pos = url_and_loc.Find(" ");
		if( -1 == pos)
		{
			AfxMessageBox( "Please give two parameters for checkout, separated by space!");
			EndWaitCursor();
			return;
		}
		else
			CSvnHelper::invokeCheckout( (LPCTSTR) url_and_loc.Left( pos), (LPCTSTR) url_and_loc.Mid( pos + 1), !m_bCmdExeOrAPI);
	}
	catch(...) { ASSERT(0); }
	EndWaitCursor();
}

void CSvnBench::OnBnClickedCmdexeButton()
{
	UpdateData( TRUE);
	save();
	//CString cmd = "cd /d ";
	//cmd += m_lstStringVal;
	//CString cmd2 = "cmd.exe";
	//system( (std::string( "cmd.exe /k cd /d ") + (LPCTSTR) m_lstStringVal).c_str());
	//_spawnl( _P_NOWAIT, (LPCTSTR) cmd2, (LPCTSTR) cmd2, NULL );
	//_spawnl( _P_NOWAIT, m_lstStringVal, m_lstStringVal);
	exec( "", m_lstStringVal);
}

void CSvnBench::OnBnClickedTestConnButton()
{
	CSvnHelper::invokeTestSubDirs();
}

void CSvnBench::OnBnClickedCloseButton()
{
	CDialog::EndDialog(IDOK);
}

void CSvnBench::OnPaint()
{
	// just for the sake of SIZEGRIP
	CPaintDC dc(this); // device context for painting
	CRect rc;
	GetClientRect(&rc);

	rc.left = rc.right - ::GetSystemMetrics(SM_CXHSCROLL);
	rc.top = rc.bottom - ::GetSystemMetrics(SM_CYVSCROLL);

	dc.DrawFrameControl(rc, DFC_SCROLL, DFCS_SCROLLSIZEGRIP);
}

void CSvnBench::save()
{
	if( m_lstStringVal == "<<select from paths below>>")
		return;
	if( -1 == m_lst.FindStringExact( 0, m_lstStringVal))
		m_lst.InsertString( 0, /*m_lst.GetCount(),*/ m_lstStringVal);
}

BOOL CSvnBench::OnHelpInfo(HELPINFO* pHelpInfo)
{
	// TODO: Add your message handler code here and/or call default

	return CDialog::OnHelpInfo(pHelpInfo);
}

//Notification handler
BOOL CSvnBench::OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult)
{
	// need to handle both ANSI and UNICODE versions of the message
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	UINT            nID = pNMHDR->idFrom;
	
	CString tip;

	if( pNMHDR->code == TTN_NEEDTEXTA && (pTTTA->uFlags & TTF_IDISHWND) ||
	    pNMHDR->code == TTN_NEEDTEXTW && (pTTTW->uFlags & TTF_IDISHWND))
	{
		// idFrom is actually the HWND of the tool
		nID = ::GetDlgCtrlID((HWND)nID);
	}

	if( nID != 0) // will be zero on a separator
	{
		//tip.Format("Control ID = %d", nID);
		switch( nID)
		{
			      case IDC_INFO_BUTTON:    tip = "Information about a given local directory/file or url identified resource";
			break;case IDC_STATUS_BUTTON:  tip = "Status of a local directory/file";
			break;case IDC_CLEANUP_BUTTON: tip = "Resume/continue a suspended operation, including removing locks on directories";
			break;case IDC_RESOLVE_BUTTON: tip = "Indicates to the server that conflict resolution has been finished";
			break;case IDC_COMMIT_BUTTON:  tip = "Send local modifications to the server and save them";
			break;case IDC_CHECKOUT_BUTTON:tip = "Download a versioned directory to a local directory. Two parameters!";
			break;case IDC_CMDEXE_BUTTON:  tip = "Command prompt, parameter indicates startup directory";
			break;case IDC_CLOSE_BUTTON:   tip = "Closes dialog";
			break;case IDC_UPDATE_BUTTON:  tip = "Update your local copy with changes from the server";
			break;case IDC_TESTCONN_BUTTON:tip = "Check and create configuration directories and files for Subversion";
		};

	}

	if( pNMHDR->code == TTN_NEEDTEXTA)
		lstrcpyn(pTTTA->szText, tip, sizeof(pTTTA->szText));
	else
		::MultiByteToWideChar( CP_ACP , 0, tip, -1, pTTTW->szText, sizeof(pTTTW->szText));

	*pResult = 0;
	return TRUE;    // message was handled
}

void CSvnBench::OnCbnEditchangeComboUrlAndPath()
{
	// this code is responsible for stretching the window horizontally
	// as the dropdown combobox's horizontal edit field is filling up with
	// user typed content, because no more characters allowed than the width :(
	CString url_text;
	m_lst.GetWindowText( url_text); // thus we didn't do UpdateData() here

	CSize   url_len;
	{
		CClientDC g( this);
		g.SelectObject( m_lst.GetFont());
		url_len = g.GetTextExtent( url_text);
	}

	CRect r;
	GetWindowRect( r);

	if( m_leftPad + url_len.cx + m_rightPad + 50 > r.Width()) // the text almost filled up the provided space in the Dropdown list's header box
	{
		r.right += m_leftPad + url_len.cx + m_rightPad + 50 - r.Width(); // increase the width of the window by the overused space
		SetWindowPos( 0, r.left, r.top, r.Width(), r.Height(), SWP_NOZORDER);
	}
}
