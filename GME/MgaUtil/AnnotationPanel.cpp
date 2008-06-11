// AnnotationPanel.cpp : implementation file
//

#include "stdafx.h"
#include "mgautil.h"
#include "AnnotationPanel.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnnotationPanel

CAnnotationPanel::CAnnotationPanel()
{
}

CAnnotationPanel::~CAnnotationPanel()
{
}


BEGIN_MESSAGE_MAP(CAnnotationPanel, CButton)
	//{{AFX_MSG_MAP(CAnnotationPanel)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnnotationPanel message handlers

void CAnnotationPanel::OnSize(UINT nType, int cx, int cy) 
{
	CButton::OnSize(nType, cx, cy);
	
	CDialog *prnt = (CDialog*)(GetParent());

	CWnd *ctrl;

	// Labels 
	ctrl = prnt->GetDlgItem(IDC_STATIC_NAME);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(13,18,13+22,18+8);
		prnt->MapDialogRect(&origRect);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_STATIC_TEXT);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(13,34,13+17,34+8);
		prnt->MapDialogRect(&origRect);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_STATIC_COLOR);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(13,101+16,13+19,101+8+16);
		prnt->MapDialogRect(&origRect);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_STATIC_BGCOLOR);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(13,119+16,13+40,119+8+16);
		prnt->MapDialogRect(&origRect);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_STATIC_FONT);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(13,138+16,13+17,138+8+16);
		prnt->MapDialogRect(&origRect);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	// Edit Fields
	ctrl = prnt->GetDlgItem(IDC_EDIT_NAME);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(38,15,38+155,15+14);
		CRect origRect2(192,15,200,15+14);
		prnt->MapDialogRect(&origRect);
		prnt->MapDialogRect(&origRect2);
		origRect.right = cx - (origRect2.right - origRect2.left);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}
	
	ctrl = prnt->GetDlgItem(IDC_EDIT_TEXT);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(38,34,38+155,34+60);
		CRect origRect2(192,34,200,34+60);
		prnt->MapDialogRect(&origRect);
		prnt->MapDialogRect(&origRect2);
		origRect.right = cx - (origRect2.right - origRect2.left);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	// inheritable checkbox
	ctrl = prnt->GetDlgItem(IDC_CHECK1);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(13,98,13+55,98+14);
		//CRect origRect2(192,98,200,98+14);
		prnt->MapDialogRect(&origRect);
		//prnt->MapDialogRect(&origRect2);
		//origRect.right = cx - (origRect2.right - origRect2.left);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	// reDerive 
	ctrl = prnt->GetDlgItem(IDC_REDERIVEBUTTON);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(13+55+10,98,13+55+10+54,98+14);
		//CRect origRect2(192,98,200,98+14);
		prnt->MapDialogRect(&origRect);
		//prnt->MapDialogRect(&origRect2);
		//origRect.right = cx - (origRect2.right - origRect2.left);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	// showHide
	ctrl = prnt->GetDlgItem(IDC_SHOWHIDEBUTTON);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(13+55+10+54+10,98,13+55+10+54+10+54,98+14);
		CRect origRect2(192,98,200,98+14);
		prnt->MapDialogRect(&origRect);
		prnt->MapDialogRect(&origRect2);
		origRect.right = cx - (origRect2.right - origRect2.left);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_COMBO_COLOR);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(58,98+16,38+135,98+14+16);
		CRect origRect2(192,98+16,200,98+14+16);
		prnt->MapDialogRect(&origRect);
		prnt->MapDialogRect(&origRect2);
		origRect.right = cx - (origRect2.right - origRect2.left);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_COMBO_BGCOLOR);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(58,116+16,38+135,116+14+16);
		CRect origRect2(192,116+16,200,116+14+16);
		prnt->MapDialogRect(&origRect);
		prnt->MapDialogRect(&origRect2);
		origRect.right = cx - (origRect2.right - origRect2.left);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_EDIT_FONT);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(58,135+16,58+115,135+14+16);
		CRect origRect2(167,135+16,200,135+14+16);
		prnt->MapDialogRect(&origRect);
		prnt->MapDialogRect(&origRect2);
		origRect.right = cx - (origRect2.right - origRect2.left);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_BUTTON_FONT);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(173,135+16,173+20,135+14+16);
		CRect origRect2(192,135+16,200,135+14+16);
		prnt->MapDialogRect(&origRect);
		int sx = origRect.right - origRect.left;
		prnt->MapDialogRect(&origRect2);
		origRect.right = cx - (origRect2.right - origRect2.left);
		origRect.left = origRect.right - sx;
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_STATIC_VISIBILITY);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(3,151+16,3+190,151+70+16);
		CRect origRect2(197,151+16,200,151+70+16);
		CRect origRect3(3,234+16,3+190, 234+3+16);
		prnt->MapDialogRect(&origRect);
		prnt->MapDialogRect(&origRect2);
		prnt->MapDialogRect(&origRect3);
		origRect.right = cx - (origRect2.right - origRect2.left);
		origRect.bottom = cy - (origRect3.bottom - origRect3.top);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_LIST_ASPECT);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(7,160+16,7+120,160+55+16);
		CRect origRect2(130,160+16,200,160+55+16);
		CRect origRect3(7,215+16,7+120, 215+7+16);
		prnt->MapDialogRect(&origRect);
		prnt->MapDialogRect(&origRect2);
		prnt->MapDialogRect(&origRect3);
		origRect.right = cx - (origRect2.right - origRect2.left);
		origRect.bottom = cy - (origRect3.bottom - origRect3.top);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_STATIC_XCOORD);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(141,168+16,141+8,168+8+16);
		CRect origRect2(148,168+16,200,168+8+16);
		prnt->MapDialogRect(&origRect);
		int sx = origRect.right - origRect.left;
		prnt->MapDialogRect(&origRect2);
		origRect.right = cx - (origRect2.right - origRect2.left);
		origRect.left = origRect.right - sx;
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_STATIC_YCOORD);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(141,190+16,141+8,190+8+16);
		CRect origRect2(148,190+16,200,190+8+16);
		prnt->MapDialogRect(&origRect);
		int sx = origRect.right - origRect.left;
		prnt->MapDialogRect(&origRect2);
		origRect.right = cx - (origRect2.right - origRect2.left);
		origRect.left = origRect.right - sx;
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_EDIT_XCOORD);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(151,164+16,151+40,164+14+16);
		CRect origRect2(190,164+16,200,164+14+16);
		prnt->MapDialogRect(&origRect);
		int sx = origRect.right - origRect.left;
		prnt->MapDialogRect(&origRect2);
		origRect.right = cx - (origRect2.right - origRect2.left);
		origRect.left = origRect.right - sx;
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_EDIT_YCOORD);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(151,185+16,151+40,185+14+16);
		CRect origRect2(190,185+16,200,185+14+16);
		prnt->MapDialogRect(&origRect);
		int sx = origRect.right - origRect.left;
		prnt->MapDialogRect(&origRect2);
		origRect.right = cx - (origRect2.right - origRect2.left);
		origRect.left = origRect.right - sx;
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_CHECK_DEFPOS);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(141,205+16,141+53,205+10+16);
		CRect origRect2(193,205+16,200,205+10+16);
		prnt->MapDialogRect(&origRect);
		int sx = origRect.right - origRect.left;
		prnt->MapDialogRect(&origRect2);
		origRect.right = cx - (origRect2.right - origRect2.left);
		origRect.left = origRect.right - sx;
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}
}

