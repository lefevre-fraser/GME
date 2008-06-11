// InterpreterConfig.h : main header file for the INTERPRETERCONFIG application
//

#if !defined(AFX_INTERPRETERCONFIG_H__DC555F79_043B_4D85_A7E9_4DC73238D41E__INCLUDED_)
#define AFX_INTERPRETERCONFIG_H__DC555F79_043B_4D85_A7E9_4DC73238D41E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CInterpreterConfigApp:
// See InterpreterConfig.cpp for the implementation of this class
//

class CInterpreterConfigApp : public CWinApp
{
public:
	CInterpreterConfigApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterpreterConfigApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CInterpreterConfigApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERPRETERCONFIG_H__DC555F79_043B_4D85_A7E9_4DC73238D41E__INCLUDED_)
