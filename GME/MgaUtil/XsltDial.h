#if !defined(AFX_XSLTDIAL_H__92B9B425_E2C1_49E3_96AF_961C570AF5AB__INCLUDED_)
#define AFX_XSLTDIAL_H__92B9B425_E2C1_49E3_96AF_961C570AF5AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// XSLTDial.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CXSLTDial dialog

class CXSLTDial : public CDialog
{
// Construction
public:
	CXSLTDial(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CXSLTDial)
	enum { IDD = IDD_XSLTDIAL };
	CString	m_stylesheetFileName;
	CString	m_inputXmlFileName;
	CString	m_outputXmlFileName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXSLTDial)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CXSLTDial)
	afx_msg void OnFileSelection1();
	afx_msg void OnFileSelection2();
	afx_msg void OnFileSelection3();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XSLTDIAL_H__92B9B425_E2C1_49E3_96AF_961C570AF5AB__INCLUDED_)
