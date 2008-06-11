#if !defined(AFX_HTMLCTRL_H__24472601_5F31_49E1_A4BC_D5855C8786D7__INCLUDED_)
#define AFX_HTMLCTRL_H__24472601_5F31_49E1_A4BC_D5855C8786D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HtmlCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHtmlCtrl html view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include <afxhtml.h>

class CConsoleCtl;

class CHtmlCtrl : public CHtmlView
{
public:
	CHtmlCtrl();
	~CHtmlCtrl() { }

// html Data
public:
	//{{AFX_DATA(CHtmlCtrl)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	BOOL CreateFromStatic(UINT nID, CWnd* pParent);
 
	// Normally, CHtmlView destroys itself in PostNcDestroy,
    // but we don't want to do that for a control since a control
    // is usually implemented as a stack object in a dialog.
    //
    virtual void PostNcDestroy() {  }


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHtmlCtrl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

    // override to trap "app:" pseudo protocol
    virtual void OnBeforeNavigate2( LPCTSTR lpszURL,
       DWORD nFlags,
       LPCTSTR lpszTargetFrameName,
       CByteArray& baPostedData,
       LPCTSTR lpszHeaders,
       BOOL* pbCancel );

	// override to handle links to "app:mumble...". lpszWhere will be "mumble"
    virtual void OnMgaURL(LPCTSTR lpszWhere);




// Implementation
protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	const CConsoleCtl *m_control;

	// Generated message map functions
	//{{AFX_MSG(CHtmlCtrl)
	afx_msg void OnDestroy();
	afx_msg int  OnMouseActivate(CWnd* pDesktopWnd,UINT nHitTest,UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CHtmlCtrl)
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HTMLCTRL_H__24472601_5F31_49E1_A4BC_D5855C8786D7__INCLUDED_)
