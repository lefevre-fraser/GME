// InPlaceEditDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TextPart.h"
#include "InPlaceEditDialog.h"
#include "InPlaceEditMultiLineDialog.h"

#define WM_USER_ENDEDITINGWITHOK	(WM_USER + 115)

// CInPlaceEditDialog dialog

IMPLEMENT_DYNAMIC(CInPlaceEditDialog, CDialog)
CInPlaceEditDialog::CInPlaceEditDialog(short iDD, CWnd* pParent /*=NULL*/)
	: CDialog(iDD, pParent),
	m_IDD(iDD),
	m_bDlgResult(false)
{
}

CInPlaceEditDialog::~CInPlaceEditDialog()
{
}

void CInPlaceEditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInPlaceEditDialog)
	DDX_Control(pDX, IDC_TEXTEDIT, m_edtInPlace);
	//}}AFX_DATA_MAP
}

void CInPlaceEditDialog::PostNcDestroy(void)
{
	CDialog::PostNcDestroy();

	if (m_bDlgResult) {
		m_parentPart->LabelChanged(m_Text);
		// transaction operation begin
		m_parentPart->ExecuteOperation(m_Text);
		// transaction operation end
	}
	m_parentPart->LabelEditingFinished(m_initialRect);
	if (!m_bPermanentCWnd)
		m_parentCWnd->Detach();
	delete m_font;
	delete this;
}


BEGIN_MESSAGE_MAP(CInPlaceEditDialog, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_USER_ENDEDITINGWITHOK, OnEndEditingWithOk)
END_MESSAGE_MAP()


// CInPlaceEditDialog message handlers

BOOL CInPlaceEditDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_edtInPlace.SetWindowText(m_Text);

	CRect rectInResource = GetWindowSizeFromResource();
	long width = (long)(m_initialRect.Width() * 1.5) + 4;
	double heightRatio = 1.0;
	if (IsKindOf(RUNTIME_CLASS(CInPlaceEditMultiLineDialog)))
		heightRatio = 1.5;
	long height = (long)(m_initialRect.Height() * heightRatio) + 4;
	long left = m_bInflateToRight ? m_initialRect.left : (m_initialRect.left - (long)(m_initialRect.Width() * 0.5));

	MoveWindow(left, m_initialRect.top, width, height);

	m_edtInPlace.SetFont(m_font);
	long dWidth = width - rectInResource.Width();
	long dHeight = height - rectInResource.Height();
	if (dWidth != 0 || dHeight != 0) {
		CRect editRect;
		m_edtInPlace.GetWindowRect(&editRect);
		m_edtInPlace.MoveWindow(0, 0, editRect.Width() + dWidth, editRect.Height() + dHeight);
	}

	m_edtInPlace.SetFocus();
	// Capture the mouse, this allows the dialog to close when the user clicks outside.
	// The dialog has no "close" button.
	m_edtInPlace.SetCapture();

	m_parentPart->LabelEditingStarted(m_initialRect);

	return FALSE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}

void CInPlaceEditDialog::OnDestroy()
{
	ReleaseCapture();

	CDialog::OnDestroy();
}

void CInPlaceEditDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	m_edtInPlace.GetWindowText(m_Text);
	ReleaseCapture();
	m_bDlgResult = false;

	DestroyWindow();
//	OnCancel();	-> calls EndDialog, which is for Modal dialogs, avoid it!
}

void CInPlaceEditDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_edtInPlace.GetWindowText(m_Text);
	if (UpdateData(true)) {
		ReleaseCapture();
		m_bDlgResult = true;

		DestroyWindow();
//		OnOK();	-> calls EndDialog, which is for Modal dialogs, avoid it!
	}
}

void CInPlaceEditDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	RECT r;

	POINT p;
	p.x = point.x;
	p.y = point.y;

	ClientToScreen(&p);

	GetWindowRect(&r);

	if (!PtInRect(&r, p)) {
		// If the user clicked outside of the dialog, close (and apply changes).
		OnBnClickedOk();	// Windows Explorer default behavior
		return;
	} else {
		// inside the dialog. Since this window
		// has the mouse captured, its children
		// get no messages. So, check to see
		// if the click was in one of its children
		// and tell him.

		// If the user clicks inside the dialog
		// but not on any of the controls,
		// ChildWindowFromPoint returns a
		// pointer to the dialog. In this
		// case we do not resend the message
		// (obviously) because it would cause
		// a stack overflow.

		CWnd* child = ChildWindowFromPoint(point);

		if (child && child != this) {
			child->SendMessage(WM_LBUTTONDOWN, nFlags, MAKELPARAM(point.x, point.y));
			return;
		}
	}

	CDialog::OnLButtonDown(nFlags, point);
}

LRESULT CInPlaceEditDialog::OnEndEditingWithOk(WPARAM wParam, LPARAM lParam)
{
	OnBnClickedOk();	// Windows Explorer default behavior
	return 0;
}

void CInPlaceEditDialog::SetProperties(const CString& text, DecoratorSDK::TextPart* parentPart, const CRect& initialRect,
									   HWND parentWnd, CWnd* parentCWnd, CFont* font, bool isPermanentCWnd,
									   bool inflateToRight)
{
	m_Text				= text;
	m_parentPart		= parentPart;
	m_initialRect		= initialRect;
	m_parentHWnd		= parentWnd;
	m_parentCWnd		= parentCWnd;
	m_font				= font;
	m_bPermanentCWnd	= isPermanentCWnd;
	m_bInflateToRight	= inflateToRight;
}

CString CInPlaceEditDialog::GetText() const
{
	return m_Text;
}

BOOL CInPlaceEditDialog::PreTranslateMessage(MSG* pMsg) 
{
	// Fix (Adrian Roman): Sometimes if the editor loses capture it is should be setcaptured again
	CWnd* captureCWnd = m_edtInPlace.GetCapture();
	if (captureCWnd ==  NULL || captureCWnd->m_hWnd != m_edtInPlace.m_hWnd) {
		CRect editRect;
		m_edtInPlace.GetWindowRect(&editRect);
		BOOL inRect = editRect.PtInRect(pMsg->pt);
		if (!inRect && pMsg->message == WM_MOUSELEAVE && m_edtInPlace.m_hWnd) {
			// No recapture, quitting with ok
			this->PostMessage(WM_USER_ENDEDITINGWITHOK, 0, 0);
		} else {
			// Recapture
			m_edtInPlace.SetCapture();
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

// CodeGuru: Finding Display Size of Dialog From Resource
//		by Shridhar Guravannavar
CRect CInPlaceEditDialog::GetWindowSizeFromResource(void) const
{
	CRect rectSize;

	// if the dialog resource resides in a DLL ...
	//

	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(m_IDD), RT_DIALOG);

	ASSERT(hInst != NULL);

	HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(m_IDD), RT_DIALOG);
	ASSERT(hRsrc != NULL);

	HGLOBAL hTemplate = ::LoadResource(hInst, hRsrc);
	ASSERT(hTemplate != NULL);

	DLGTEMPLATE* pTemplate = (DLGTEMPLATE*)::LockResource(hTemplate);

	//Load coresponding DLGINIT resource
	//(if we have any ActiveX components)
	//
	void* lpDlgInit;
	HGLOBAL hDlgInit = NULL;
	CDialog dlg;

	HRSRC hsDlgInit = ::FindResource(hInst, MAKEINTRESOURCE(m_IDD), RT_DLGINIT);
	if (hsDlgInit != NULL) {
		// load it
		hDlgInit = ::LoadResource(hInst, hsDlgInit);
		ASSERT(hDlgInit != NULL);

		// lock it
		lpDlgInit = ::LockResource(hDlgInit);
		ASSERT(lpDlgInit != NULL);

		dlg.CreateIndirect(pTemplate, NULL, lpDlgInit);
	} else {
		dlg.CreateIndirect(pTemplate, NULL);
	}

	CRect rect;
	dlg.GetWindowRect(rectSize);

	dlg.DestroyWindow();

	::UnlockResource(hTemplate);
	::FreeResource(hTemplate);
	if (hDlgInit) {
		::UnlockResource(hDlgInit);
		::FreeResource(hDlgInit);
	}

	return rectSize;
}
