// InPlaceEditSingleLineDialog.cpp : implementation file
//

#include "stdafx.h"
#include "InPlaceEditSingleLineDialog.h"


// CInPlaceEditSingleLineDialog dialog

IMPLEMENT_DYNAMIC(CInPlaceEditSingleLineDialog, CInPlaceEditDialog)
CInPlaceEditSingleLineDialog::CInPlaceEditSingleLineDialog(CWnd* pParent /*=NULL*/)
	: CInPlaceEditDialog(CInPlaceEditSingleLineDialog::IDD, pParent)
{
}

CInPlaceEditSingleLineDialog::~CInPlaceEditSingleLineDialog()
{
}
