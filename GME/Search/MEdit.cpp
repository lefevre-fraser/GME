// MEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Search.h"
#include ".\medit.h"
#include "SearchDlg.h"
#include "SearchCtl.h"

// CMEdit

IMPLEMENT_DYNAMIC(CMEdit, CEdit)
CMEdit::CMEdit()
{
}

CMEdit::~CMEdit()
{
}


BEGIN_MESSAGE_MAP(CMEdit, CEdit)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// CMEdit message handlers


void CMEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CSearchDlg* dlg = (CSearchDlg*) GetParent();
	if( dlg) {
		if( nChar == VK_TAB)
		{
			dlg->tabPressed( this, ::GetKeyState( VK_SHIFT) < 0);
		}
		else if( nChar == VK_RETURN)
		{
			CWnd* nxt = 0;
			nxt = &dlg->m_lstResults;//nxt = &dlg->m_btnGO;
			if( nxt) 
			{
				dlg->clickGo();
				nxt->SetFocus();
				return;
			}
		}
		else if( nChar == VK_ESCAPE)
		{
			dlg->getMyParent()->WantToBeClosed();
		}
	}

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}
