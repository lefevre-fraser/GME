// InPlaceEditDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TextPart.h"
#include "InPlaceEditDialog.h"

// CInPlaceEditDialog dialog

IMPLEMENT_DYNAMIC(CInPlaceEditDialog, CDialog)
CInPlaceEditDialog::CInPlaceEditDialog() :
	CDialog(),
	m_richWnd(NULL),
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
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_USER_INPLACEEDITING, OnInPlaceEditing)
	ON_NOTIFY(EN_REQUESTRESIZE, IDC_INPLACETEXTEDIT, OnRequestResize)
END_MESSAGE_MAP()


// CInPlaceEditDialog message handlers

BOOL CInPlaceEditDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_richWnd = (CRichEditCtrl*)GetDlgItem(IDC_INPLACETEXTEDIT);
	m_richWnd->SetFont(m_font);
	m_richWnd->SetWindowText(m_Text);

	// m_richWnd is a CRichEditCtrl object
	// Set the ENM_REQUESTRESIZE event flag
	DWORD currEventMask = m_richWnd->GetEventMask();
	m_richWnd->SetEventMask(currEventMask | ENM_REQUESTRESIZE);
	// Force the control to issue a EN_REQUESTRESIZE notification
	m_richWnd->RequestResize();

	// Smart positioning of the caret
	CRect richWndCRect;
	m_richWnd->GetClientRect(&richWndCRect);
	m_richWnd->ScreenToClient(&m_mouseClick);
	m_mouseClick.x = (long)(m_mouseClick.x * m_initialRect.Width() / (m_labelRect.Width() * m_viewZoom));
	m_mouseClick.y = (long)(m_mouseClick.y * m_initialRect.Height() / (m_labelRect.Height() * m_viewZoom));

	int n = m_richWnd->CharFromPos(m_mouseClick);
	int nLineIndex = HIWORD(n);
	int nCharIndex = LOWORD(n);
	TRACE("nLineIndex = %d, nCharIndex = %d\n", nCharIndex, nCharIndex);
	m_richWnd->SetSel(nCharIndex, nCharIndex);

	m_parentPart->LabelEditingStarted(m_initialRect);

	m_editState = Initial;

	// Capture the mouse, this allows the dialog to close when the user clicks outside.
	// The dialog has no "close" button.
	m_richWnd->SetCapture();
	m_richWnd->SetFocus();

	return FALSE;	// return TRUE unless you set the focus to a control
					// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CInPlaceEditDialog::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CInPlaceEditDialog::OnDestroy()
{
	ReleaseCapture();

	CDialog::OnDestroy();
}

void CInPlaceEditDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	m_richWnd->GetWindowText(m_Text);
	ReleaseCapture();
	m_bDlgResult = false;

	DestroyWindow();
//	OnCancel();	-> calls EndDialog, which is for Modal dialogs, avoid it!
}

void CInPlaceEditDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_richWnd->GetWindowText(m_Text);
	if (UpdateData(true)) {
		ReleaseCapture();
		m_bDlgResult = true;

		DestroyWindow();
//		OnOK();	-> calls EndDialog, which is for Modal dialogs, avoid it!
	}
}

LRESULT CInPlaceEditDialog::OnInPlaceEditing(WPARAM wParam, LPARAM lParam)
{
	// wParam > 0: OK, else Cancel
	// lParam > 0: mouse click initiated else keyboard input initiated
	if (wParam == VK_RETURN) {
		if (lParam > 0 || !m_bMultiLine)
			OnBnClickedOk();	// Windows Explorer default behavior
	} else if (wParam == VK_ESCAPE) {
		OnBnClickedCancel();
	} else if (wParam == ID_EDIT_SELECT_ALL) {
		m_richWnd->SetSel(0, -1);
	} else if (wParam == ID_EDIT_UNDO) {
		m_richWnd->Undo();
	} else if (wParam == ID_EDIT_REDO) {
		m_richWnd->Redo();
	}
	return 0;
}

void CInPlaceEditDialog::OnRequestResize(NMHDR* pNMHDR, LRESULT* pResult)
{
	ASSERT(pNMHDR->code == EN_REQUESTRESIZE);

	REQRESIZE* prr = (REQRESIZE*)pNMHDR;

	long horizontalClearance = 4;
	long verticalClearance = horizontalClearance;
	CRect requestedRect(prr->rc.left,
						prr->rc.top,
						prr->rc.right + horizontalClearance,
						prr->rc.bottom + verticalClearance);
	long dWidth = 0;
	long dHeight = 0;
	if (requestedRect.Width() > m_boundsLimit.Width())
		dWidth = m_boundsLimit.Width() - requestedRect.Width();
	if (requestedRect.Height() > m_boundsLimit.Height())
		dHeight = m_boundsLimit.Height() - requestedRect.Height();
	if (requestedRect.Width() < m_minSize.cx)
		dWidth = m_boundsLimit.Width() - requestedRect.Width();
	if (requestedRect.Height() < m_minSize.cy)
		dHeight = m_boundsLimit.Height() - requestedRect.Height();
	if (dWidth != 0 || dHeight != 0)
		requestedRect.InflateRect(0, 0, dWidth, dHeight);

	if (m_bInflateToRight) {
		requestedRect.OffsetRect(m_initialRect.TopLeft());
	} else {
		long xOffset = m_initialRect.right - requestedRect.right;
		requestedRect.OffsetRect(xOffset, m_initialRect.top);
	}

	CRect limitedRect;
	BOOL isIntersectionNotEmpty = limitedRect.IntersectRect(requestedRect, m_boundsLimit);
	ASSERT(isIntersectionNotEmpty != FALSE);

	if (limitedRect.Width() < m_minSize.cx)
		dWidth = m_minSize.cx - limitedRect.Width();
	if (limitedRect.Height() < m_minSize.cy)
		dHeight = m_minSize.cy - limitedRect.Height();
	if (dWidth != 0 || dHeight != 0)
		limitedRect.InflateRect(0, 0, dWidth, dHeight);

	MoveWindow(limitedRect);
	m_richWnd->MoveWindow(0, 0, limitedRect.Width(), limitedRect.Height());

	*pResult = NULL;
}

void CInPlaceEditDialog::SetProperties(const CString& text, DecoratorSDK::TextPart* parentPart,
									   const CRect& initialRect, const CRect& labelRect, const CSize& minSize,
									   const CRect& boundsLimit, const CPoint& mouseClick, HWND parentWnd,
									   CWnd* parentCWnd, bool isPermanentCWnd, CFont* font, double viewZoom,
									   bool inflateToRight, bool multiLine)
{
	m_Text						= text;
	m_parentPart				= parentPart;
	m_initialRect				= initialRect;
	m_labelRect					= labelRect;
	m_minSize					= minSize;
	m_boundsLimit				= boundsLimit;
	m_mouseClick				= mouseClick;
	m_parentHWnd				= parentWnd;
	m_parentCWnd				= parentCWnd;
	m_bPermanentCWnd			= isPermanentCWnd;
	m_font						= font;
	m_viewZoom					= viewZoom;
	m_bInflateToRight			= inflateToRight;
	m_bMultiLine				= multiLine;
	m_leftMouseButtonPressed	= false;
}

CString CInPlaceEditDialog::GetText() const
{
	return m_Text;
}

BOOL CInPlaceEditDialog::PreTranslateMessage(MSG* pMsg) 
{
	// Fix (Adrian Roman): Sometimes if the editor loses capture it is should be setcaptured again
	CWnd* captureCWnd = GetCapture();
	if (captureCWnd ==  NULL || captureCWnd->m_hWnd != m_richWnd->m_hWnd) {
		// Recapture
		m_richWnd->SetCapture();
	}

	return CDialog::PreTranslateMessage(pMsg);
}
