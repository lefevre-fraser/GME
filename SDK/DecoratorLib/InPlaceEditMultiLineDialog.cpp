// InPlaceEditMultiLineDialog.cpp : implementation file
//

#include "stdafx.h"
#include "InPlaceEditMultiLineDialog.h"


// CInPlaceEditMultiLineDialog dialog

IMPLEMENT_DYNAMIC(CInPlaceEditMultiLineDialog, CInPlaceEditDialog)
CInPlaceEditMultiLineDialog::CInPlaceEditMultiLineDialog(CWnd* pParent /*=NULL*/)
	: CInPlaceEditDialog(CInPlaceEditMultiLineDialog::IDD, pParent)
{
}

CInPlaceEditMultiLineDialog::~CInPlaceEditMultiLineDialog()
{
}
