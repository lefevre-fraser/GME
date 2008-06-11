// VSSLoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include ".\VSSLoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVSSLoginDlg dialog


CVSSLoginDlg::CVSSLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVSSLoginDlg::IDD, pParent)
	, m_aborted( false)
	, m_leftPad( 20)
	, m_rightPad( 20)
{
	//{{AFX_DATA_INIT(CVSSLoginDlg)
	m_password = _T("");
	m_user = _T("");
	m_database = _T("");
	m_project = _T("");
	//}}AFX_DATA_INIT
}


void CVSSLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVSSLoginDlg)
	DDX_Text(pDX, IDC_EDIT_PWD, m_password);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	DDX_Text(pDX, IDC_STATIC_DATABASE, m_database);
	DDX_Text(pDX, IDC_STATIC_PROJECT, m_project);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVSSLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CVSSLoginDlg)
	ON_BN_CLICKED(IDC_ABORT, OnBnClickedAbort)
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSSLoginDlg message handlers

BOOL CVSSLoginDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_aborted = false;

	CWnd * db = GetDlgItem( IDC_STATIC_DATABASE);
	CRect db_rect;
	if( db && db->GetSafeHwnd()) {
		db->GetWindowRect( &db_rect);
		ScreenToClient( &db_rect);

		CRect win_rect;
		GetWindowRect( &win_rect);
		ScreenToClient( &win_rect);

		m_leftPad = db_rect.left - win_rect.left;
		m_rightPad = win_rect.right - db_rect.right;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CVSSLoginDlg::OnBnClickedAbort()
{
	m_aborted = true;
	EndDialog( IDCANCEL);
	//throw hresult_exception( E_FAIL);
}

bool CVSSLoginDlg::wasAborted()
{
	return m_aborted;
}

void CVSSLoginDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	CWnd * db = GetDlgItem( IDC_STATIC_DATABASE);
	CWnd * pj = GetDlgItem( IDC_STATIC_PROJECT);
	CRect db_rect, pj_rect;
	if( db && pj && db->GetSafeHwnd() && pj->GetSafeHwnd()) {
		db->GetWindowRect( &db_rect);
		pj->GetWindowRect( &pj_rect);
		ScreenToClient( &db_rect);
		ScreenToClient( &pj_rect);
		int width = cx - m_leftPad - m_rightPad;

		db->SetWindowPos( NULL, m_leftPad, db_rect.top, width > 20? width: 20, db_rect.Height(), SWP_NOZORDER);
		pj->SetWindowPos( NULL, m_leftPad, pj_rect.top, width > 20? width: 20, pj_rect.Height(), SWP_NOZORDER);
	}
}
