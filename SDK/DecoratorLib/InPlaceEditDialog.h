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
	CInPlaceEditDialog();
	virtual ~CInPlaceEditDialog();

	CRichEditCtrl* m_richWnd;
	CString	m_Text;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy(void);

	DECLARE_MESSAGE_MAP()
public:
	// Generated message map functions
	//{{AFX_MSG(CInPlaceEditDialog)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg LRESULT OnInPlaceEditing(WPARAM wParam, LPARAM lParam);
	afx_msg void OnRequestResize(NMHDR* pNMHDR, LRESULT* pResult);
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
	bool					m_bPermanentCWnd;
	HWND					m_parentHWnd;
	CRect					m_initialRect;
	CRect					m_labelRect;
	CSize					m_minSize;
	CRect					m_boundsLimit;
	long					m_minLeft;
	long					m_minTop;
	long					m_maxRight;
	long					m_maxBottom;
	CPoint					m_mouseClick;	// Screen coordinates of the mouse click which invoked the in-place edit
	CFont*					m_font;
	double					m_viewZoom;
	bool					m_bInflateToRight;
	bool					m_bMultiLine;
	bool					m_bDlgResult;
	bool					m_leftMouseButtonPressed;
	EditState				m_editState;

public:
	void	SetProperties(const CString& text, DecoratorSDK::TextPart* parentPart, const CRect& initialRect,
						  const CRect& labelRect, const CSize& minSize, const CRect& boundsLimit,
						  const CPoint& mouseClick, HWND parentWnd, CWnd* parentCWnd, bool isPermanentCWnd,
						  CFont* font, double viewZoom, bool inflateToRight = true, bool multiLine = false);
	CString GetText() const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceEditDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPLACEEDITDIALOG_H__0D3F6303_5878_489e_ADB0_FFBF2A4CA609__INCLUDED_)
