// MEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Search.h"
#include ".\medit.h"
#include "SearchDlg.h"
#include "SearchCtl.h"

// CMEdit

IMPLEMENT_DYNAMIC(CMEdit, CComboBox)
CMEdit::CMEdit()
{
    //m_edit.set
}

CMEdit::~CMEdit()
{
}


BEGIN_MESSAGE_MAP(CMEdit, CComboBox)
    ON_WM_CTLCOLOR()
    ON_WM_DESTROY()
END_MESSAGE_MAP()



// CMEdit message handlers




HBRUSH CMEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    if (nCtlColor == CTLCOLOR_EDIT)
    {
        //[ASCII 160][ASCII 160][ASCII 160]Edit control
        if (m_edit.GetSafeHwnd() == NULL)
            m_edit.SubclassWindow(pWnd->GetSafeHwnd());
    }
    else if (nCtlColor == CTLCOLOR_LISTBOX)
    {
        //ListBox control
        if (m_listbox.GetSafeHwnd() == NULL)
            m_listbox.SubclassWindow(pWnd->GetSafeHwnd());
    }
    HBRUSH hbr = CComboBox::OnCtlColor(pDC, pWnd, nCtlColor);
    return hbr;
}

void CMEdit::OnDestroy()
{
    if (m_edit.GetSafeHwnd() != NULL)
        m_edit.UnsubclassWindow();
    if (m_listbox.GetSafeHwnd() != NULL)
        m_listbox.UnsubclassWindow();
    CComboBox::OnDestroy();
}