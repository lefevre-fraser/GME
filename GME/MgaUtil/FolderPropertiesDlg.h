#if !defined(AFX_FOLDERPROPERTIESDLG_H__7639BD38_555B_42C0_889C_55853D86E85D__INCLUDED_)
#define AFX_FOLDERPROPERTIESDLG_H__7639BD38_555B_42C0_889C_55853D86E85D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FolderPropertiesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFolderPropertiesDlg dialog

class CFolderPropertiesDlg : public CDialog
{
// Construction
public:
	CFolderPropertiesDlg( IMgaFolder *f, CWnd* pParent = NULL);   // standard constructor

//	CGMEView *view;
	CComPtr<IMgaFolder> folder;

// Dialog Data
	//{{AFX_DATA(CFolderPropertiesDlg)
	enum { IDD = IDD_FOLDERPROPERTIES_DIALOG };
	CEdit	nameBox;
	CEdit	kind;
	CEdit	objectid;
	CEdit	library;
	CEdit	type;
	CEdit	metaid;
	CString	name;
	CString	m_relid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFolderPropertiesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	bool editflag;
protected:

	// Generated message map functions
	//{{AFX_MSG(CFolderPropertiesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetrelid();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

	CString m_sz_pre_edit_name;
	long relid;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOLDERPROPERTIESDLG_H__7639BD38_555B_42C0_889C_55853D86E85D__INCLUDED_)
