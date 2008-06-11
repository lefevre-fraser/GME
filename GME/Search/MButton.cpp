// MButton.cpp : implementation file
//

#include "stdafx.h"
#include "Search.h"
#include ".\mbutton.h"
#include "SearchDlg.h"
#include "SearchCtl.h"


// CMButton

IMPLEMENT_DYNAMIC(CMButton, CButton)
CMButton::CMButton()
{
}

CMButton::~CMButton()
{
}


BEGIN_MESSAGE_MAP(CMButton, CButton)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CMButton message handlers


void CMButton::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if( nChar == VK_TAB)
	{
		CSearchDlg* dlg = (CSearchDlg*) GetParent();
		if( dlg) dlg->tabPressed( this, ::GetKeyState( VK_SHIFT) < 0);
	}
	else if( nChar == VK_ESCAPE)
	{
		CSearchDlg *dlg = (CSearchDlg *) GetParent();
		if( dlg) dlg->getMyParent()->WantToBeClosed();
	}

	CButton::OnKeyDown(nChar, nRepCnt, nFlags);
}
