#if !defined(AFX_CONNPROPERTIESDLG_H__5FADE7E1_3BE1_11D4_AEF1_00E029342AAF__INCLUDED_)
#define AFX_CONNPROPERTIESDLG_H__5FADE7E1_3BE1_11D4_AEF1_00E029342AAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnPropertiesDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConnPropertiesDlg dialog

class CConnPropertiesDlg : public CDialog
{
// Construction
public:
	CConnPropertiesDlg(		CString s,CString sp,CString d,CString dp,
							CString rol,CString id,CString nm,bool type,
							
							CString metaid, CString kind, CString aspect,
							
							long relid, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConnPropertiesDlg)
	enum { IDD = IDD_CONNPROPERTIES_DIALOG };
	CEdit	nameBox;
	CString	dst;
	CString	dstPort;
	CString	id;
	CString	name;
	CString	src;
	CString	srcPort;
	CString	m_objectid;
	CString	m_metaid;
	CString	m_aspect;
	CString	m_kind;
	CString	m_role;
	CString	m_relid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConnPropertiesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	bool isType;
	bool editflag;
protected:

	// Generated message map functions
	//{{AFX_MSG(CConnPropertiesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetrelid();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:

	CString m_sz_pre_edit_name;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONNPROPERTIESDLG_H__5FADE7E1_3BE1_11D4_AEF1_00E029342AAF__INCLUDED_)
