// Validate.cpp: implementation of the CValidate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Validate.h"

#include "RegExp.h"


void AFXAPI DDX_ValidateInp(CDataExchange* pDX, int nIDC, CString &name)
{
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);

	if (pDX->m_bSaveAndValidate)
	{
		DDX_Text(pDX, nIDC, name);

		CRegExp nam(name);

		if(!nam.CompiledOK())
		{
			AfxMessageBox("Incorrect Regular Expression Format");
			pDX->Fail();
		}
	}
}