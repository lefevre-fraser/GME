#if !defined(AFX_COMBOBOXSELECTDLG_H__681E99E2_6596_4511_9CED_D7F2F2FC194E__INCLUDED_)
#define AFX_COMBOBOXSELECTDLG_H__681E99E2_6596_4511_9CED_D7F2F2FC194E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboBoxSelectDlg.h : header file
//

#include "HooverListBox.h"

class CListItem;

class CComboBoxSelectDlg : public CDialog
{
	bool m_bInited;
	bool m_bClosed;
// Construction
public:
	CComboBoxSelectDlg(CWnd* pParent = NULL);   // standard constructor

// Attributes
public :
	CHooverListBox m_lstBox;
	CRect m_rectWnd;
	CFont* m_pFontWnd;
	CListItem* m_pListItem;

// Dialog Data
	//{{AFX_DATA(CComboBoxSelectDlg)
	enum { IDD = IDD_DIALOG_COMBOBOX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboBoxSelectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComboBoxSelectDlg)
	afx_msg BOOL OnNcActivate(BOOL bActive);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg LONG OnComboSelEnd(UINT lParam, LONG wParam);
	void OnOK();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOBOXSELECTDLG_H__681E99E2_6596_4511_9CED_D7F2F2FC194E__INCLUDED_)
