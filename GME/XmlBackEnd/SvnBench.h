#pragma once
#include "resource.h"
#include "afxwin.h"


// CSvnBench dialog

class CSvnBench : public CDialog
{
	DECLARE_DYNAMIC(CSvnBench)

	int      m_rightPad;
	int      m_leftPad;
	CString  m_connStr;
public:
	CSvnBench(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSvnBench();

	void init( CString p_path);
	void exec( CString p_cmd, CString p_startupDir);

// Dialog Data
	enum { IDD = IDD_SVN_BENCH_DIALOG };

protected:
	void save();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedInfoButton();
	afx_msg void OnBnClickedStatusButton();
	afx_msg void OnBnClickedCleanupButton();
	afx_msg void OnBnClickedCloseButton();
	afx_msg void OnBnClickedCmdexeButton();
	afx_msg void OnBnClickedResolveButton();
	afx_msg void OnBnClickedCommitButton();
	afx_msg void OnBnClickedCheckoutButton();
	afx_msg void OnBnClickedUpdateButton();
	afx_msg void OnBnClickedLockButton();
	afx_msg void OnBnClickedUnlockButton();
	afx_msg void OnBnClickedTestConnButton();
	afx_msg void OnPaint();
	afx_msg BOOL OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnCbnEditchangeComboUrlAndPath();

	BOOL         m_bRecursive;
	BOOL         m_bCmdExeOrAPI;
	CComboBox    m_lst;
	CString      m_lstStringVal;
};
