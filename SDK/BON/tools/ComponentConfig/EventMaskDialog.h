#if !defined(AFX_EVENTMASKDIALOG_H__1BA2B578_8F7B_4B6F_B2EC_F2C051D7BD95__INCLUDED_)
#define AFX_EVENTMASKDIALOG_H__1BA2B578_8F7B_4B6F_B2EC_F2C051D7BD95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EventMaskDialog.h : header file
//
#include <fstream>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CEventMaskDialog dialog

class CEventMaskDialog : public CDialog
{
// Construction
public:
	ULONG mask;
	ifstream fin;
	BOOL OnInitDialog();
	CEventMaskDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEventMaskDialog)
	enum { IDD = IDD_EVENTMASK_DIALOG };
	CListCtrl	m_evlist;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEventMaskDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEventMaskDialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EVENTMASKDIALOG_H__1BA2B578_8F7B_4B6F_B2EC_F2C051D7BD95__INCLUDED_)
