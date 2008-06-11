// MComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "Search.h"
#include ".\mcombobox.h"
#include "SearchDlg.h"
#include "SearchCtl.h"


// MComboBox

IMPLEMENT_DYNAMIC(CMComboBox, CComboBox)
CMComboBox::CMComboBox()
{
}

CMComboBox::~CMComboBox()
{
}


BEGIN_MESSAGE_MAP(CMComboBox, CComboBox)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// MComboBox message handlers


void CMComboBox::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if( nChar == VK_TAB)
	{
		CWnd* nxt = 0;
		CSearchDlg* dlg = (CSearchDlg*) GetParent();
		if( dlg) nxt = dlg->GetNextDlgTabItem( this, ::GetKeyState( VK_SHIFT) < 0);
		if( nxt) {
			nxt->SetFocus();
			return;
		}
	}
	else if( nChar == VK_ESCAPE)
	{
		CSearchDlg *dlg = (CSearchDlg *) GetParent();
		if( dlg) dlg->getMyParent()->WantToBeClosed();
	}
	// TODO: Add your message handler code here and/or call default

	CComboBox::OnKeyDown(nChar, nRepCnt, nFlags);
}
