// CInPlaceNativeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "InPlaceNativeDialog.h"
#include "DecoratorDefs.h"


// CInPlaceNativeDialog dialog

CInPlaceNativeDialog::CInPlaceNativeDialog(CWnd* pParent)
{
}

CInPlaceNativeDialog::~CInPlaceNativeDialog()
{
}

//-----------------------------------------------------------------------------
// Name: InPlaceEditDlgProc()
// Desc: The dialog window proc
//-----------------------------------------------------------------------------
LRESULT CALLBACK InPlaceEditDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static CInPlaceNativeDialog* thisPtr = NULL;
	switch (uMsg)
	{
		case WM_INITDIALOG:
			{
				thisPtr = (CInPlaceNativeDialog*) lParam;
				CRect rectInResource = thisPtr->GetWindowSizeFromResource();
				long width = (long)(thisPtr->m_initialRect.Width() * 1.50) + 4;
				long height = (long)(thisPtr->m_initialRect.Height()) + 4;
//				CRect parentWindowRect;
//				::GetWindowRect(thisPtr->m_parentHWnd, &parentWindowRect);
//				thisPtr->m_initialRect.OffsetRect(parentWindowRect.TopLeft());

				MoveWindow(hDlg, thisPtr->m_initialRect.left, thisPtr->m_initialRect.top, width, height, TRUE);

				HWND editWnd = GetDlgItem(hDlg, IDC_TEXTEDIT);
				SendMessage(editWnd, WM_SETFONT, (WPARAM)(HFONT)(*(thisPtr->m_font)), TRUE);
				long dWidth = width - rectInResource.Width();
				long dHeight = height - rectInResource.Height();
				if (dWidth != 0 || dHeight != 0) {
					RECT editRect;
					GetWindowRect(editWnd, &editRect);
					MoveWindow(editWnd, 0, 0, editRect.right - editRect.left + dWidth, editRect.bottom - editRect.top + dHeight, TRUE);
				}

				SetDlgItemText(hDlg, IDC_TEXTEDIT, thisPtr->m_Text);

				// Capture the mouse, this allows the dialog to close when the user clicks outside.
				// The dialog has no "close" button.
//				SetCapture();
			}
			return TRUE;
		case WM_COMMAND:
			switch (HIWORD(wParam))
			{
				case BN_CLICKED:
					switch (LOWORD(wParam))
					{
						case IDOK:
							{
//								INT i = SendDlgItemMessage(hDlg, IDC_COMBOMODES, CB_GETCURSEL, 0, 0 );
								EndDialog(hDlg, TRUE);
								return TRUE;
							}
						case IDCANCEL:
							EndDialog(hDlg, FALSE);
							return TRUE;
					}
					break;
			}
			break;
	}

	return FALSE;
}

int CInPlaceNativeDialog::DoModal(void)
{
	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(IDD_INPLACEEDITSLDIALOG), RT_DIALOG);
	ASSERT(hInst != NULL);
	int retVal = DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_INPLACEEDITSLDIALOG), m_parentHWnd, (DLGPROC) InPlaceEditDlgProc, (LPARAM)this);
	if (retVal == 0 || retVal == -1) {
		DWORD errCode = GetLastError();
		char szBuffer[512] = { 0 };
		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			errCode,
			0,
			szBuffer,
			sizeof(szBuffer),
			0
		);
		OutputDebugString(szBuffer);
	}

	return retVal;
}

// CodeGuru: Finding Display Size of Dialog From Resource
//		by Shridhar Guravannavar
CRect CInPlaceNativeDialog::GetWindowSizeFromResource(void) const
{
	CRect rectSize;

	// if the dialog resource resides in a DLL ...
	//

	HINSTANCE hInst = AfxFindResourceHandle(MAKEINTRESOURCE(IDD_INPLACEEDITSLDIALOG), RT_DIALOG);

	ASSERT(hInst != NULL);

	HRSRC hRsrc = ::FindResource(hInst, MAKEINTRESOURCE(IDD_INPLACEEDITSLDIALOG), RT_DIALOG);
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

	HRSRC hsDlgInit = ::FindResource(hInst, MAKEINTRESOURCE(IDD_INPLACEEDITSLDIALOG), RT_DLGINIT);
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

	return rectSize;
}
