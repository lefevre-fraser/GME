// InPlaceEditDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TextPart.h"
#include "InPlaceEditDialog.h"

// CInPlaceEditDialog dialog

IMPLEMENT_DYNAMIC(CInPlaceEditDialog, CDialog)
CInPlaceEditDialog::CInPlaceEditDialog() :
	CDialog(),
	editWnd(NULL),
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
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_USER_INPLACEEDITING, OnInPlaceEditing)
END_MESSAGE_MAP()


// CInPlaceEditDialog message handlers

BOOL CInPlaceEditDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	editWnd = (CEdit*)GetDlgItem(IDC_INPLACETEXTEDIT);
	editWnd->SetWindowText(m_Text);

	CRect rectInResource(0, 0, 76, 19);
	double widthDeltaRatio = 0.5;
	long widthBoost = (long)(m_initialRect.Width() * widthDeltaRatio);
	widthBoost = min(max(widthBoost, 40), 200);	// Limiting minimum & maximum
	long width = m_initialRect.Width() + widthBoost;
	double heightDeltaRatio = 0.0;
	if (m_bMultiLine)
		heightDeltaRatio = 0.5;
	long heightBoost = (long)(m_initialRect.Height() * heightDeltaRatio) + 4;
	heightBoost = min(heightBoost, 80);	// Limiting maximum
	long height = m_initialRect.Height() + heightBoost;
	height = max(height, 16);	// Limiting minimum
	// Inflate to the left in case of right port
	long left = m_initialRect.left - (m_bInflateToRight ? 0 : widthBoost);

	MoveWindow(left, m_initialRect.top, width, height);

	editWnd->SetFont(m_font);
	long dWidth = width - rectInResource.Width();
	long dHeight = height - rectInResource.Height();
	if (dWidth != 0 || dHeight != 0) {
		CRect editRect;
		editWnd->GetWindowRect(&editRect);
		editWnd->MoveWindow(0, 0, editRect.Width() + dWidth, editRect.Height() + dHeight);
	}

	// Smart positioning of the caret
	editWnd->ScreenToClient(&m_mouseClick);
	int n = editWnd->CharFromPos(m_mouseClick);
	int nLineIndex = HIWORD(n);
	int nCharIndex = LOWORD(n);
	TRACE("nLineIndex = %d, nCharIndex = %d\n", nCharIndex, nCharIndex);
	editWnd->SetSel(nCharIndex, nCharIndex);

	m_parentPart->LabelEditingStarted(m_initialRect);

	m_editState = Initial;

	// Capture the mouse, this allows the dialog to close when the user clicks outside.
	// The dialog has no "close" button.
	editWnd->SetCapture();
	editWnd->SetFocus();

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
	editWnd->GetWindowText(m_Text);
	ReleaseCapture();
	m_bDlgResult = false;

	DestroyWindow();
//	OnCancel();	-> calls EndDialog, which is for Modal dialogs, avoid it!
}

void CInPlaceEditDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	editWnd->GetWindowText(m_Text);
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
		editWnd->SetSel(0, -1);
	} else if (wParam == ID_EDIT_UNDO) {
		editWnd->Undo();
	} else if (wParam == ID_EDIT_REDO) {
//		editWnd->Redo();	// There's no Redo on CEdit interface! :P
	}
	return 0;
}

void CInPlaceEditDialog::SetProperties(const CString& text, DecoratorSDK::TextPart* parentPart,
									   const CRect& initialRect, const CPoint& mouseClick, HWND parentWnd,
									   CWnd* parentCWnd, CFont* font, bool isPermanentCWnd, bool inflateToRight,
									   bool multiLine)
{
	m_Text						= text;
	m_parentPart				= parentPart;
	m_initialRect				= initialRect;
	m_mouseClick				= mouseClick;
	m_parentHWnd				= parentWnd;
	m_parentCWnd				= parentCWnd;
	m_font						= font;
	m_bPermanentCWnd			= isPermanentCWnd;
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
	if (captureCWnd ==  NULL || captureCWnd->m_hWnd != editWnd->m_hWnd) {
		// Recapture
		editWnd->SetCapture();
	}

	return CDialog::PreTranslateMessage(pMsg);
}
