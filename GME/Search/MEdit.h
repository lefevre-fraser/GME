#pragma once

#include "DummyEdit.h"
// CMEdit

class CMEdit : public CComboBox
{
    DECLARE_DYNAMIC(CMEdit)

public:
    CMEdit();
    virtual ~CMEdit();

protected:
    DECLARE_MESSAGE_MAP()
public:
    CDummyEdit      m_edit;
    CListBox   m_listbox;
protected:
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnDestroy();

};
