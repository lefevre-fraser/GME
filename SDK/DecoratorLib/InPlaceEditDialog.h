#if !defined(AFX_INPLACEEDITDIALOG_H__0D3F6303_5878_489e_ADB0_FFBF2A4CA609__INCLUDED_)
#define AFX_INPLACEEDITDIALOG_H__0D3F6303_5878_489e_ADB0_FFBF2A4CA609__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InPlaceEditDialog.h : header file
//

#include "stdafx.h"
#include "DecoratorDefs.h"

namespace DecoratorSDK {
	class TextPart;
}

// CInPlaceEditDialog dialog

class CInPlaceEditDialog : public CDialog
{
	DECLARE_DYNAMIC(CInPlaceEditDialog)

public:
	CInPlaceEditDialog(short iDD, CWnd* pParent = NULL);   // standard constructor
	virtual ~CInPlaceEditDialog();

// Dialog Data
	//{{AFX_DATA(CInPlaceEditDialog)
	CEdit	m_edtInPlace;
	//}}AFX_DATA

	short m_IDD;
	CString	m_Text;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy(void);

	DECLARE_MESSAGE_MAP()
public:
	// Generated message map functions
	//{{AFX_MSG(CInPlaceEditDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnEndEditingWithOk(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

protected:
	enum EditState {
		Initial				= 0,
		LButtonDownOutside	= 1,
		MouseMoveAfterDown	= 2,
		LButtonUpOutside	= 3
	};

	DecoratorSDK::TextPart*	m_parentPart;
	CWnd*					m_parentCWnd;
	HWND					m_parentHWnd;
	CRect					m_initialRect;
	CPoint					m_mouseClick;	// Screen coordinates of the mouse click which invoked the in-place edit
	CFont*					m_font;
	bool					m_bPermanentCWnd;
	bool					m_bInflateToRight;
	bool					m_bDlgResult;
	bool					m_leftMouseButtonPressed;
	EditState				m_editState;

public:
	void	SetProperties(const CString& text, DecoratorSDK::TextPart* parentPart, const CRect& initialRect,
						  const CPoint& mouseClick, HWND parentWnd, CWnd* parentCWnd, CFont* font,
						  bool isPermanentCWnd, bool inflateToRight = true);
	CString GetText() const;

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CInPlaceEditDialog)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    //}}AFX_VIRTUAL

	CRect	GetWindowSizeFromResource(void) const;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPLACEEDITDIALOG_H__0D3F6303_5878_489e_ADB0_FFBF2A4CA609__INCLUDED_)
