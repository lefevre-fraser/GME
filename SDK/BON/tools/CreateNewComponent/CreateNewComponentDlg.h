// CreateNewComponentDlg.h : header file
//

#if !defined(AFX_CREATENEWCOMPONENTDLG_H__267ADEDF_1FA9_45C2_A3A4_1B5EC39EDA3C__INCLUDED_)
#define AFX_CREATENEWCOMPONENTDLG_H__267ADEDF_1FA9_45C2_A3A4_1B5EC39EDA3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCreateNewComponentDlg dialog

class CCreateNewComponentDlg : public CDialog
{
// Construction
public:
	CCreateNewComponentDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateNewComponentDlg)
	enum { IDD = IDD_CREATENEWCOMPONENT_DIALOG };
	CString	m_path;
	int		m_radio;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateNewComponentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString getDestDirectory( const CString& );
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCreateNewComponentDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowse();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATENEWCOMPONENTDLG_H__267ADEDF_1FA9_45C2_A3A4_1B5EC39EDA3C__INCLUDED_)
