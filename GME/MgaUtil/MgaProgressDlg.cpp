
#include "stdafx.h"
#include "MgaProgressDlg.h"

// --------------------------- CMgaProgressDlg

CMgaProgressDlg::CMgaProgressDlg() 
{
}

CMgaProgressDlg::~CMgaProgressDlg()
{
	if( dlg.m_hWnd != NULL )
		dlg.DestroyWindow();
}

STDMETHODIMP CMgaProgressDlg::SetTitle(BSTR t)
{
	COMTRY
	{
		CopyTo(t, title);

		if( dlg.m_hWnd != NULL )
			dlg.SetWindowText(title);
	}
	COMCATCH(;)
}

int nIDs[2] = {IDC_STATIC1, IDC_STATIC2};

STDMETHODIMP CMgaProgressDlg::SetLine(int line, BSTR msg)
{
	if( line < 0 || line >= 2 )
		COMRETURN(E_INVALIDARG);

	COMTRY
	{
		CopyTo(msg, lines[line]);

		if( dlg.m_hWnd != NULL )
			dlg.GetDlgItem(nIDs[line])->SetWindowText(lines[line]);
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaProgressDlg::StartProgressDialog(HWND hwndParent)
{
	if( dlg.m_hWnd != NULL )
		COMRETURN(E_INVALID_USAGE);

	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CWnd *win = hwndParent == NULL ? AfxGetMainWnd() : CWnd::FromHandle(hwndParent);
	dlg.Create(IDD_PROGRESSDLG, win);
	ASSERT( dlg.m_hWnd != NULL );

	dlg.SetWindowText(title);
	dlg.GetDlgItem(nIDs[0])->SetWindowText(lines[0]);
	dlg.GetDlgItem(nIDs[1])->SetWindowText(lines[1]);

	dlg.ShowWindow(SW_SHOWNORMAL);

	return S_OK;
}

STDMETHODIMP CMgaProgressDlg::SetProgress(long completed, long total)
{
	if( dlg.m_hWnd == NULL )
		COMRETURN(E_INVALID_USAGE);

	CProgressCtrl *ctrl = (CProgressCtrl*)dlg.GetDlgItem(IDC_PROGRESS1);
	ASSERT( ctrl != NULL );

	ctrl->SetRange32(0, total);
	ctrl->SetPos(completed);

//	dlg.Invalidate();
	dlg.UpdateWindow();

	return S_OK;
}

STDMETHODIMP CMgaProgressDlg::HasUserCancelled(VARIANT_BOOL *p)
{
	if( dlg.m_hWnd == NULL )
		COMRETURN(E_INVALID_USAGE);

//	*p = dlg.cancelPressed ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CMgaProgressDlg::StopProgressDialog()
{
	if( dlg.m_hWnd == NULL )
		COMRETURN(E_INVALID_USAGE);

	dlg.DestroyWindow();
	ASSERT( dlg.m_hWnd == NULL );

	return S_OK;
}
