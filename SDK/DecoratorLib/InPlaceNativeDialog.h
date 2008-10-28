#if !defined(AFX_INPLACENATIVEDIALOG_H__CA86F78D_1072_4ad9_8A65_7B10CD14B422__INCLUDED_)
#define AFX_INPLACENATIVEDIALOG_H__CA86F78D_1072_4ad9_8A65_7B10CD14B422__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InPlaceNativeDialog.h : header file
//

#include "stdafx.h"
#include "Resource.h"

// CInPlaceNativeDialog dialog

class CInPlaceNativeDialog
{
public:
	CInPlaceNativeDialog(CWnd* pParent = NULL);
	virtual ~CInPlaceNativeDialog();

// Dialog Data
	CString	m_Text;
	CWnd*	m_parentCWnd;
	HWND	m_parentHWnd;
	CRect	m_initialRect;
	CFont*	m_font;
	long	m_zoomVal;

	int		DoModal(void);
	void	SetParentWnd(HWND parentWnd, CWnd* parentCWnd) { m_parentHWnd = parentWnd; m_parentCWnd = parentCWnd; };
	void	SetInitialRect(const CRect& rect) { m_initialRect = rect; };
	void	SetFont(CFont* font) { m_font = font; };
	CString GetText() const { return m_Text; };
	void	SetText(const CString& text) { m_Text = text; };

	CRect	GetWindowSizeFromResource(void) const;
};

// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPLACENATIVEDIALOG_H__CA86F78D_1072_4ad9_8A65_7B10CD14B422__INCLUDED_)
