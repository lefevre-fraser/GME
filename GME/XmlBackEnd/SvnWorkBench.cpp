// SvnWorkBench.cpp : Implementation of CSvnWorkBench

#include "stdafx.h"
#include ".\SvnWorkBench.h"
#include "..\Common\CommonMFC.h"
#include "SvnBench.h"
#include "SvnTestDlg.h"

// CSvnWorkBench


STDMETHODIMP CSvnWorkBench::ShowWorkBenchDlg(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CSvnBench d;
	CString a_clue;
	CopyTo( m_clue, a_clue);
	d.init( a_clue);

	d.DoModal();

	return S_OK;
}

STDMETHODIMP CSvnWorkBench::SetClues(BSTR p_connString)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_clue = p_connString;

	return S_OK;
}

STDMETHODIMP CSvnWorkBench::ShowResultDlg(BSTR p_result)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CSvnTestDlg d;
	CString res;
	CopyTo( p_result, res);
	d.setContent( res);

	d.DoModal();

	return S_OK;
}
