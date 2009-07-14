// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__BD235B51_BD3F_11D3_91E2_00104B98EAD9__INCLUDED_)
#define AFX_CHILDFRM_H__BD235B51_BD3F_11D3_91E2_00104B98EAD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ModelPropertiesDlgBar.h"

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:
	CString title;
	bool sendEvent;
	CView *view;

// Operations
public:
	virtual void OnUpdateFrameTitle(BOOL /* x */) { 
		TCHAR szOld[256];
		if (GetWindowText(szOld, _countof(szOld)) != title.GetLength() ||
			lstrcmp(szOld, title) != 0) {
			SetWindowText(title); 
		}
	};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	CModelPropertiesDlgBar propBar;
// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__BD235B51_BD3F_11D3_91E2_00104B98EAD9__INCLUDED_)
