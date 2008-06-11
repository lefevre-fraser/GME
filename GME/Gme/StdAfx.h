// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__BD235B4D_BD3F_11D3_91E2_00104B98EAD9__INCLUDED_)
#define AFX_STDAFX_H__BD235B4D_BD3F_11D3_91E2_00104B98EAD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#if defined(_DEBUG)
#define ADDCRASHTESTMENU
#endif

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#include <afxctl.h>			// Pick up the definition of AfxOleRegisterTypeLib
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "mfcdual.h"

#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>

#include <stl_user_config.h>

#include "..\Mga\MgaLib.h"

#include "CommonError.h"
#include "CommonSmart.h"
#include "CommonMfc.h"
#include "CommonMgaTrukk.h"

#define WM_USER_ZOOM			(WM_USER+111)
#define WM_PANN_SCROLL			(WM_USER+112)
#define WM_USER_PANNREFRESH		(WM_USER+113)
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__BD235B4D_BD3F_11D3_91E2_00104B98EAD9__INCLUDED_)
