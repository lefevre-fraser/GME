//{{AFX_INCLUDES()
#include "console.h"
//}}AFX_INCLUDES
#if !defined(AFX_GMECONSOLE_H__C58BF4E8_E3F7_4717_BBDA_B908B0DD4D5E__INCLUDED_)
#define AFX_GMECONSOLE_H__C58BF4E8_E3F7_4717_BBDA_B908B0DD4D5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GMEConsole.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGMEConsole dialog

class CGMEConsole : public CDockablePane
{
// Construction
public:
	CGMEConsole(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGMEConsole(){theInstance = 0;};

	void Clear();
	void Message(CString str, short type);
	CString GetContents();
	void SetContents(const CString& contents);
	void SetGMEApp(IDispatch *idp);
	void SetGMEProj(IDispatch *idp);
	void NavigateTo(CString url);
	IDispatch * GetInterface() {return NULL;};

// Dialog Data
	//{{AFX_DATA(CGMEConsole)
	enum { IDD = IDD_CONSOLE_DIALOG };
	CConsole	m_Console;
	//}}AFX_DATA

	static CGMEConsole *theInstance;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGMEConsole)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGMEConsole)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClickMGAIDConsoleCtrl(LPCTSTR objid);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GMECONSOLE_H__C58BF4E8_E3F7_4717_BBDA_B908B0DD4D5E__INCLUDED_)
