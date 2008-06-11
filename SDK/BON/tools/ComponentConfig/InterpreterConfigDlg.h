// InterpreterConfigDlg.h : header file
//

#if !defined(AFX_INTERPRETERCONFIGDLG_H__AB9BE06A_0665_48A9_A7E1_6ACE6D39DE9A__INCLUDED_)
#define AFX_INTERPRETERCONFIGDLG_H__AB9BE06A_0665_48A9_A7E1_6ACE6D39DE9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning ( disable : 4786 )

#include <vector>
#include <string>

/////////////////////////////////////////////////////////////////////////////
// CInterpreterConfigDlg dialog

class CInterpreterConfigDlg : public CDialog
{
// Construction
public:
	int componenttechnology;
	CInterpreterConfigDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CInterpreterConfigDlg();
	CString sPreviousComponentName;

// Dialog Data
	//{{AFX_DATA(CInterpreterConfigDlg)
	enum { IDD = IDD_COMPONENTCONFIG_DIALOG };
	BOOL	m_Autofield;
	CString	m_CompName;
	CString	m_ClassName;
	CString	m_ClassUUID;
	int		m_Interpreter;
	CString	m_Paradigms;
	CString	m_ProgID;
	CString	m_TlbName;
	CString	m_TlbUUID;
	BOOL	m_parindep;
	CString	m_evmaskedit;
	BOOL	m_toolbaricon;
	BOOL	m_customtrans;
	CString	m_tooltipText;
	CString	m_strGmePath;
	BOOL	m_systemreg;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterpreterConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON                       m_hIcon;
    CString                     parnamehidden;
    CString                     m_gmeSourcePath;
    std::vector<std::string>    m_gmeSourceFiles;
	CString						m_initialGMEPath;

	// Generated message map functions
	//{{AFX_MSG(CInterpreterConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeName();
	afx_msg void OnBNInterpreter();
	virtual void OnOK();
	afx_msg void OnRegen();
	afx_msg void OnParindep();
	afx_msg void OnEvmask();
	afx_msg void OnBNPlugin();
	afx_msg void OnBNAddon();
	afx_msg void OnParadd();
	afx_msg void OnTbicon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


	void RefreshOthers();

	static const CString typetoken[3];

private:
	bool ReadConfig();

    void readGmeSourceFileList      ();
    void updateVcprojFile              ( const char * vcprojFileName );
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERPRETERCONFIGDLG_H__AB9BE06A_0665_48A9_A7E1_6ACE6D39DE9A__INCLUDED_)
