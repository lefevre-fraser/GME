// InPlaceEditDialog.cpp : implementation file
//

#include "stdafx.h"
#include "InPlaceEditDialog.h"


// CInPlaceEditDialog dialog

IMPLEMENT_DYNAMIC(CInPlaceEditDialog, CDialog)
CInPlaceEditDialog::CInPlaceEditDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CInPlaceEditDialog::IDD, pParent)
{
}

CInPlaceEditDialog::~CInPlaceEditDialog()
{
}

void CInPlaceEditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInPlaceEditDialog)
	DDX_Text(pDX, IDC_TEXTEDIT, m_Text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInPlaceEditDialog, CDialog)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_EN_CHANGE(IDC_TEXTEDIT, OnEnChangeTextedit)
END_MESSAGE_MAP()


// CInPlaceEditDialog message handlers

BOOL CInPlaceEditDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

/*	m_hOKIcon = LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_OK));
	CButton* okButton = (CButton*)GetDlgItem(IDOK);
	okButton->SetIcon(m_hOKIcon);
	m_hCancelIcon = LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_CANCEL));
	CButton* cancelButton = (CButton*)GetDlgItem(IDCANCEL);
	cancelButton->SetIcon(m_hCancelIcon);*/

	CRect rectInResource = GetWindowSizeFromResource();
	long width = (long)(m_initialRect.Width() * 1.50) + 4;
	long height = (long)(m_initialRect.Height()) + 4;
	CRect parentWindowRect;
	::GetWindowRect(m_parentHWnd, &parentWindowRect);
	m_initialRect.OffsetRect(parentWindowRect.TopLeft());

	MoveWindow(m_initialRect.left, m_initialRect.top, width, height);

	CWnd* editWnd = GetDlgItem(IDC_TEXTEDIT);
	editWnd->SetFont(m_font);
	long dWidth = width - rectInResource.Width();
	long dHeight = height - rectInResource.Height();
	if (dWidth != 0 || dHeight != 0) {
		CRect editRect;
		editWnd->GetWindowRect(&editRect);
		editWnd->MoveWindow(0, 0, editRect.Width() + dWidth, editRect.Height() + dHeight);
	}

	// Capture the mouse, this allows the dialog to close when the user clicks outside.
	// The dialog has no "close" button.
	SetCapture();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CInPlaceEditDialog::OnDestroy()
{
	ReleaseCapture();

	CDialog::OnDestroy();

	// destroy icons if they were loaded
/*	if (m_hOKIcon != NULL)
		DestroyIcon(m_hOKIcon);
	if (m_hCancelIcon != NULL)
		DestroyIcon(m_hCancelIcon);*/
}

void CInPlaceEditDialog::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CInPlaceEditDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
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
		// If the user clicked outside of the dialog, close.
		EndDialog(IDCANCEL);
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

		CWnd *child = ChildWindowFromPoint(point);

		if (child && child != this)
			child->SendMessage(WM_LBUTTONDOWN, nFlags, MAKELPARAM(point.x, point.y));
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CInPlaceEditDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	// See notes for OnLButtonDown.
	CWnd *child = ChildWindowFromPoint(point, CWP_ALL);

	if (child && child != this)
		child->SendMessage(WM_LBUTTONUP, nFlags, MAKELPARAM(point.x, point.y));

	CDialog::OnLButtonUp(nFlags, point);
}

void CInPlaceEditDialog::OnEnChangeTextedit()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

void CInPlaceEditDialog::EndDialog(int nResult)
{
	ReleaseCapture();

	CDialog::EndDialog(nResult);
}

BOOL CInPlaceEditDialog::PreTranslateMessage(MSG* pMsg) 
{
	// Fix (Adrian Roman): Sometimes if the picker loses focus it is never destroyed
	if (GetCapture()->GetSafeHwnd() != m_hWnd)
		SetCapture();

	return CDialog::PreTranslateMessage(pMsg);
}

// CodeGuru: Finding Display Size of Dialog From Resource
//		by Shridhar Guravannavar
CRect CInPlaceEditDialog::GetWindowSizeFromResource(void) const
{
	CRect rectSize;

	// if the dialog resource resides in a DLL ...
	//
/*	HINSTANCE hExeResourceHandle;
	HINSTANCE hModule;

	if (strDllName != NULL) {
		hExeResourceHandle = AfxGetResourceHandle();

		hModule= ::LoadLibrary(strDllName);
		ASSERT(hModule);

		AfxSetResourceHandle(hModule);
	}*/

	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(IDD_INPLACEEDITDIALOG),
											RT_DIALOG);

	ASSERT(hInst != NULL);

	HRSRC hRsrc = ::FindResource(hInst,
								 MAKEINTRESOURCE(IDD_INPLACEEDITDIALOG),
								 RT_DIALOG);
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

	HRSRC hsDlgInit = ::FindResource(hInst,
									 MAKEINTRESOURCE(IDD_INPLACEEDITDIALOG),
									 RT_DLGINIT);
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
//	dlg.GetClientRect(rectSize);
	dlg.GetWindowRect(rectSize);

	dlg.DestroyWindow();

	::UnlockResource(hTemplate);
	::FreeResource(hTemplate);
	if (hDlgInit) {
		::UnlockResource(hDlgInit);
		::FreeResource(hDlgInit);
	}

/*	if(strDllName != NULL) {
		AfxSetResourceHandle(hExeResourceHandle);
		::FreeLibrary(hModule);
	}*/

	return rectSize;
}
