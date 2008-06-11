#if !defined(AFX_VSSLOGINDLG_H__912CEEC2_1AD6_4BCD_B827_E8604CEE7889__INCLUDED_)
#define AFX_VSSLOGINDLG_H__912CEEC2_1AD6_4BCD_B827_E8604CEE7889__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VSSLoginDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVSSLoginDlg dialog

class CVSSLoginDlg : public CDialog
{
// Construction
public:
	CVSSLoginDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVSSLoginDlg)
	enum { IDD = IDD_DIALOG_VSSLOGIN };
	CString	m_password;
	CString	m_user;
	CString	m_database;
	CString	m_project;
	//}}AFX_DATA

public:
	bool wasAborted();

protected:
	bool m_aborted;
	int  m_leftPad;
	int  m_rightPad;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSSLoginDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CVSSLoginDlg)
	afx_msg void OnBnClickedAbort();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSSLOGINDLG_H__912CEEC2_1AD6_4BCD_B827_E8604CEE7889__INCLUDED_)
