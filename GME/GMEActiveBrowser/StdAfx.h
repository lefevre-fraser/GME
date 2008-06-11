#if !defined(AFX_STDAFX_H__16AA33FA_B59A_4910_9F60_CAA3FF9A3EF1__INCLUDED_)
#define AFX_STDAFX_H__16AA33FA_B59A_4910_9F60_CAA3FF9A3EF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxctl.h>         // MFC support for ActiveX Controls
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Comon Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// Delete the two includes below if you do not wish to use the MFC
//  database classes
#include <afxdb.h>			// MFC database classes
#include <afxdao.h>			// MFC DAO database classes

#include <atlbase.h>

#define _ATL_APARTMENT_THREADED
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;

#include <atlcom.h>
#include "..\Interfaces\Meta.h"
#include "..\Interfaces\MgaUtil.h"
#include "..\Interfaces\GME.h"
#include "CommonError.h"
#include "CommonMfc.h"
#include "CommonMgaTrukk.h"

// Comment this out if you do not want to see the messages in the debug window
#define DEBUG_EVENTS


#ifdef DEBUG_EVENTS
 #define EVENT_TRACE(x) TRACE(x)
#else
 #define EVENT_TRACE(x)
#endif 



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__16AA33FA_B59A_4910_9F60_CAA3FF9A3EF1__INCLUDED_)
