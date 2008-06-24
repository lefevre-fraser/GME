#if !defined(AFX_CONSOLECTL_H__06A2BBCD_6B16_4C6F_A339_6685CEC1DF65__INCLUDED_)
#define AFX_CONSOLECTL_H__06A2BBCD_6B16_4C6F_A339_6685CEC1DF65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HtmlCtrl.h"
#include "ScriptEdit.h"
// ConsoleCtl.h : Declaration of the CConsoleCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CConsoleCtrl : See ConsoleCtl.cpp for implementation.

class CConsoleCtrl : public COleControl
{
	friend class CHtmlCtrl;
	DECLARE_DYNCREATE(CConsoleCtrl)

// Constructor
public:
	CConsoleCtrl();

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConsoleCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
// protected:
	~CConsoleCtrl();
	void LoadScript( const CString& fileName);
	void RunScript();

	CHtmlCtrl   m_browser;
	CScriptEdit	m_edit;
	CButton	    m_cmdButton;
	CButton	    m_exeButton;
	CButton     m_clrButton;
	CButton     m_upButton;
	CButton     m_dnButton;
	CButton     m_retButton;
	CString     m_recent1;
	CString     m_recent2;
	CString     m_recent3;
	CString     m_recent4;
	CString     m_recent5;

	DECLARE_OLECREATE_EX(CConsoleCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CConsoleCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CConsoleCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CConsoleCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CConsoleCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShowMenu();
	afx_msg void LoadScriptDlg();
	afx_msg void runScript();
	afx_msg void relScript();
	afx_msg void rlrScript();
	afx_msg void selectEngine();
	afx_msg void prevCommand();
	afx_msg void nextCommand();
	afx_msg void retCommand();
	afx_msg void loadRecent( UINT);
	afx_msg BOOL OnToolTipNotify(UINT id, NMHDR *pNMHDR, LRESULT *pResult);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
// Dispatch maps
	//{{AFX_DISPATCH(CConsoleCtrl)
	afx_msg BSTR GetContents();
	afx_msg void SetContents(LPCTSTR lpszNewValue);
	afx_msg void Message(LPCTSTR str, short type);
	afx_msg void Clear();
	afx_msg void SetGMEApp(IDispatch *disp);
	afx_msg void SetGMEProj(IDispatch *disp);
	afx_msg void AboutBox();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Event maps
	//{{AFX_EVENT(CConsoleCtrl)
	void FireClickMGAID(LPCTSTR objid)
		{FireEvent(eventidClickMGAID,EVENT_PARAM(VTS_BSTR), objid);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CConsoleCtrl)
	dispidContents = 1L,
	dispidMessage = 2L,
	dispidClear = 3L,
	eventidClickMGAID = 1L,
	//}}AFX_DISP_ID
	};

private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONSOLECTL_H__06A2BBCD_6B16_4C6F_A339_6685CEC1DF65__INCLUDED)
