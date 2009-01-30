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
	bool	m_bInflateToRight;

	int		DoModal(void);
	void	SetProperties(const CString& text, const CRect& initialRect, HWND parentWnd, CWnd* parentCWnd, CFont* font,
						  bool inflateToRight = true)
				{ m_Text = text; m_initialRect = initialRect; m_parentHWnd = parentWnd; m_parentCWnd = parentCWnd;
				  m_font = font; m_bInflateToRight = inflateToRight; };
	CString GetText() const { return m_Text; };
	void	SetText(const CString& text) { m_Text = text; };

	CRect	GetWindowSizeFromResource(void) const;
};

// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPLACENATIVEDIALOG_H__CA86F78D_1072_4ad9_8A65_7B10CD14B422__INCLUDED_)
