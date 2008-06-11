// MListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "Search.h"
#include ".\mlistctrl.h"
#include "SearchDlg.h"
#include "SearchCtl.h"


// CMListCtrl

IMPLEMENT_DYNAMIC(CMListCtrl, CListCtrl)
CMListCtrl::CMListCtrl()
{
}

CMListCtrl::~CMListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMListCtrl, CListCtrl)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CMListCtrl message handlers


void CMListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if( nChar == VK_DOWN || nChar == VK_UP)
	{
		// update to that item:
		CSearchDlg* dlg = (CSearchDlg*) GetParent();
		if( dlg) dlg->itemClicked();
	}
	if( nChar == VK_RETURN)
	{
		// show selected item:
		CSearchDlg* dlg = (CSearchDlg*) GetParent();
		if( dlg) dlg->itemDblClicked();
	}
	else if( nChar == VK_TAB)
	{
		CSearchDlg* dlg = (CSearchDlg*) GetParent();
		if( dlg) dlg->tabPressed( this, ::GetKeyState( VK_SHIFT) < 0);
	}
	else if( nChar == VK_ESCAPE)
	{
		CSearchDlg *dlg = (CSearchDlg *) GetParent();
		if( dlg) dlg->getMyParent()->WantToBeClosed();
	}

	CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}
