#if !defined(AFX_INPLACEEDITSINGLELINEDIALOG_H__AE790659_3E60_4C5E_B46C_FBB880A85429__INCLUDED_)
#define AFX_INPLACEEDITSINGLELINEDIALOG_H__AE790659_3E60_4C5E_B46C_FBB880A85429__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InPlaceEditSingleLineDialog.h : header file
//

#include "stdafx.h"
#include "InPlaceEditDialog.h"

// CInPlaceEditSingleLineDialog dialog

class CInPlaceEditSingleLineDialog : public CInPlaceEditDialog
{
	DECLARE_DYNAMIC(CInPlaceEditSingleLineDialog)

public:
	CInPlaceEditSingleLineDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInPlaceEditSingleLineDialog();

// Dialog Data
	//{{AFX_DATA(CInPlaceEditSingleLineDialog)
	enum { IDD = IDD_INPLACEEDITSLDIALOG };
	//}}AFX_DATA
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPLACEEDITSINGLELINEDIALOG_H__AE790659_3E60_4C5E_B46C_FBB880A85429__INCLUDED_)
