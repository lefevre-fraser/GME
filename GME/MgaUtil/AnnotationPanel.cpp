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

/*	ctrl = prnt->GetDlgItem(IDC_STATIC_BORDERCOLOR);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(13,138+16,13+19,138+8+16);
		prnt->MapDialogRect(&origRect);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}*/

	ctrl = prnt->GetDlgItem(IDC_STATIC_GRADIENTCOLOR);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(13,156+16,13+40,156+8+16);
		prnt->MapDialogRect(&origRect);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_STATIC_FONT);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(13,199+16,13+17,199+8+16);
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

/*	ctrl = prnt->GetDlgItem(IDC_COMBO_BORDERCOLOR);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(58,135+16,38+135,135+14+16);
		CRect origRect2(192,135+16,200,135+14+16);
		prnt->MapDialogRect(&origRect);
		prnt->MapDialogRect(&origRect2);
		origRect.right = cx - (origRect2.right - origRect2.left);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}*/

	ctrl = prnt->GetDlgItem(IDC_COMBO_GRADIENTCOLOR);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(58,153+16,38+135,153+14+16);
		CRect origRect2(192,153+16,200,153+14+16);
		prnt->MapDialogRect(&origRect);
		prnt->MapDialogRect(&origRect2);
		origRect.right = cx - (origRect2.right - origRect2.left);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_CHECK_GRADIENTFILL);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(13,170+16,13+53,170+10+16);
		prnt->MapDialogRect(&origRect);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_CHECK_CASTSHADOW);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(13,183+16,13+55,183+10+16);
		prnt->MapDialogRect(&origRect);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

/*	ctrl = prnt->GetDlgItem(IDC_RADIO_VERTICAL);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(68,170+16,68+53,170+10+16);
		prnt->MapDialogRect(&origRect);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_RADIO_HORIZONTAL);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(136,170+16,136+55,170+10+16);
		prnt->MapDialogRect(&origRect);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}*/

	ctrl = prnt->GetDlgItem(IDC_STATIC_SHADOWDEPTH);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(75,184+16,75+51,184+8+16);
		prnt->MapDialogRect(&origRect);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_EDIT_SHADOWDEPTH);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(135,180+16,135+55,180+14+16);
		prnt->MapDialogRect(&origRect);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_EDIT_FONT);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(58,196+16,58+115,196+14+16);
		CRect origRect2(167,196+16,200,196+14+16);
		prnt->MapDialogRect(&origRect);
		prnt->MapDialogRect(&origRect2);
		origRect.right = cx - (origRect2.right - origRect2.left);
		ClientToScreen(&origRect);
		prnt->ScreenToClient(&origRect);
		ctrl->MoveWindow(&origRect);
	}

	ctrl = prnt->GetDlgItem(IDC_BUTTON_FONT);
	if (ctrl->GetSafeHwnd()) {
		CRect origRect(173,196+16,173+20,196+14+16);
		CRect origRect2(192,196+16,200,196+14+16);
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
		CRect origRect(3,212+16,3+190,212+70+16);
		CRect origRect2(197,212+16,200,212+70+16);
		CRect origRect3(3,295+16,3+190, 295+3+16);
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
		CRect origRect(7,221+16,7+120,221+55+16);
		CRect origRect2(130,221+16,200,221+55+16);
		CRect origRect3(7,276+16,7+120, 276+7+16);
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
		CRect origRect(141,229+16,141+8,229+8+16);
		CRect origRect2(148,229+16,200,229+8+16);
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
		CRect origRect(141,251+16,141+8,251+8+16);
		CRect origRect2(148,251+16,200,251+8+16);
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
		CRect origRect(151,225+16,151+40,225+14+16);
		CRect origRect2(190,225+16,200,225+14+16);
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
		CRect origRect(151,246+16,151+40,246+14+16);
		CRect origRect2(190,246+16,200,246+14+16);
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
		CRect origRect(141,266+16,141+53,266+10+16);
		CRect origRect2(193,266+16,200,266+10+16);
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

