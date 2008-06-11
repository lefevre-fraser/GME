#if !defined(AFX_DIALOGLIST_H__56AB0CFA_ADAB_49E8_8215_2BECE389A707__INCLUDED_)
#define AFX_DIALOGLIST_H__56AB0CFA_ADAB_49E8_8215_2BECE389A707__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmergencySaveDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// EmergencySaveDlg dialog

#include "resource.h"


class EmergencySaveDlg: public CDialog
{
	DECLARE_DYNAMIC(EmergencySaveDlg)

public:
	EmergencySaveDlg(CWnd* pParent = NULL);
	virtual ~EmergencySaveDlg();

// Dialog Data
	//{{AFX_DATA(EmergencySaveDlg)
	enum { IDD = IDD_EMERGENCY_DIALOG };
	CButton	m_buttonOK;
	CButton	m_checkboxMinidump;
	CStatic	m_staticEmergencySaveInfo;
	CStatic	m_staticMinidumpSaveInfo;
	BOOL	m_minidumpChecked;
	CString	m_strEmergencySaveInfo;
	CString	m_strMinidumpSaveInfo;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EmergencySaveDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	afx_msg void OnMinidumpCheckboxClicked();
	//}}AFX_VIRTUAL


	// Generated message map functions
	//{{AFX_MSG(EmergencySaveDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	void	SetStrings(CString emergencySaveInfo, CString minidumpSaveInfo);
	BOOL	ShouldWriteMiniDump(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGLIST_H__56AB0CFA_ADAB_49E8_8215_2BECE389A707__INCLUDED_)
