 //###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	GMESmallMessageBox.cpp
//
//###############################################################################################################################################

#include "stdafx.h"
#include "constraintmanager.h"
#include "GMESmallMessageBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//##############################################################################################################################################
//
//	C L A S S : CSmallMessageBox <<< + CDialog
//
//##############################################################################################################################################

CSmallMessageBox::CSmallMessageBox( CWnd* pParent /*=NULL*/)
	: CDialog(CSmallMessageBox::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSmallMessageBox)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSmallMessageBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSmallMessageBox)
	DDX_Control(pDX, NOEX_PROGRESS, m_ctrlProgress);
	DDX_Control(pDX, NOEX_LBLMESSAGE, m_lblMessage);
	DDX_Control(pDX, NOEX_BTNOK, m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSmallMessageBox, CDialog)
	//{{AFX_MSG_MAP(CSmallMessageBox)
	ON_BN_CLICKED(NOEX_BTNOK, OnClickOK)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()





BOOL CSmallMessageBox::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lblMessage.SetWindowText( "No Constraint violations were found." );
	m_ctrlProgress.SetRange32( 0, 100 );
	m_ctrlProgress.SetPos( 100 );
	m_btnOK.EnableWindow( true );
	m_btnOK.SetWindowText( "OK" );
	m_btnOK.ShowWindow( SW_SHOW );

	return TRUE;
}

void CSmallMessageBox::OnClickOK()
{
	CDialog::OnOK();
}

BOOL CSmallMessageBox::PreTranslateMessage( MSG* pMsg )
{
	return ( pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE ) ? FALSE : CDialog::PreTranslateMessage( pMsg );
}

void CSmallMessageBox::IncrementProgress()
{
	m_ctrlProgress.SetPos( m_ctrlProgress.GetPos() + 1 );
}

void CSmallMessageBox::DoModeless( int iRange )
{
	AfxGetApp()->DoWaitCursor( 1 );
	Create( IDD_PROGRESS_DIALOG );
	ShowWindow( SW_SHOW );
	m_lblMessage.SetWindowText( "Evaluation of Constraints is in progress...." );
	m_ctrlProgress.SetRange32( 0, iRange );
	m_ctrlProgress.SetPos( 0 );
	// m_btnOK.SetWindowText( "Cancel" );
}

void CSmallMessageBox::UndoModeless()
{
	ShowWindow( SW_HIDE );
	DestroyWindow();
	AfxGetApp()->DoWaitCursor( -1 );
}
