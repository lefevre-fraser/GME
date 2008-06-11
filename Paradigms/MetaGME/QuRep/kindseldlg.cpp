// KindSelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KindSelDlg.h"


// KindSelDlg dialog

IMPLEMENT_DYNAMIC(KindSelDlg, CDialog)
KindSelDlg::KindSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(KindSelDlg::IDD, pParent)
	, m_ranOnceAlready( false)
	, m_applyAllSelected( false)
	, m_breakOnCancelSelected( false)
	, m_selection( -1)
{
}

KindSelDlg::~KindSelDlg()
{
}

void KindSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1,  m_knds);
	DDX_Control(pDX, IDC_CHECK1, m_quitOnCancel);
	DDX_Control(pDX, IDC_CHECK2, m_applyForAll);
	DDX_Control(pDX, IDC_EDIT1,  m_curElem);
	DDX_Control(pDX, IDC_EDIT2,  m_oldKind);
}


BEGIN_MESSAGE_MAP(KindSelDlg, CDialog)
	ON_LBN_DBLCLK(IDC_LIST1, OnLbnDblclkList1)
END_MESSAGE_MAP()


// KindSelDlg message handlers
bool KindSelDlg::shouldApplyForAll()
{
	return m_ranOnceAlready && m_applyAllSelected;
}

bool KindSelDlg::shouldFinish()
{
	return m_ranOnceAlready && m_breakOnCancelSelected;
}

bool KindSelDlg::init( CString p_nms, CString p_oldKind)
{
	m_currElemName = p_nms;
	m_oldKindName  = p_oldKind;
	return true;
}

bool KindSelDlg::setup()
{
	m_knds.AddString( "Atom");
	m_knds.AddString( "Reference");
	m_knds.AddString( "Set");
	m_knds.AddString( "Model");
	m_knds.AddString( "Connection");
	m_knds.AddString( "FCO");

	m_curElem.SetWindowText( m_currElemName);
	m_knds.SetCurSel( -1);

	m_oldKind.SetWindowText( "<<" + m_oldKindName + ">>");

	return true;
}

CString KindSelDlg::selection()
{
	return m_resKindName;
}

BOOL KindSelDlg::OnInitDialog()
{
	BOOL ret = CDialog::OnInitDialog();
	m_ranOnceAlready = true;
	setup();

	return TRUE;
}

void KindSelDlg::OnOK()
{
	m_applyAllSelected      = m_applyForAll.GetCheck()  == BST_CHECKED;
	m_breakOnCancelSelected = m_quitOnCancel.GetCheck() == BST_CHECKED;
	m_selection             = m_knds.GetCurSel();

	switch( m_selection)
	{
		case 0: m_resKindName = "Atom";          break;
		case 1: m_resKindName = "Reference";     break;
		case 2: m_resKindName = "Set";           break;
		case 3: m_resKindName = "Model";         break;
		case 4: m_resKindName = "Connection";    break;
		case 5: m_resKindName = "FCO";           break;
		default: 
			m_oldKind.GetWindowText( m_resKindName);
			break;
	}

	CDialog::OnOK();
}

void KindSelDlg::OnCancel()
{
	m_applyAllSelected      = m_applyForAll.GetCheck()  == BST_CHECKED;
	m_breakOnCancelSelected = m_quitOnCancel.GetCheck() == BST_CHECKED;
	m_selection             = -1;

	CDialog::OnCancel();
}

void KindSelDlg::OnLbnDblclkList1()
{
	OnOK();
}
