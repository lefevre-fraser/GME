#if !defined(AFX_STDAFX_H__CDB67FB4_2FC8_4014_88C6_9A46A1E63399__INCLUDED_)
#define AFX_STDAFX_H__CDB67FB4_2FC8_4014_88C6_9A46A1E63399__INCLUDED_

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

#include <afxtempl.h>

#include <atlbase.h>

// Delete the two includes below if you do not wish to use the MFC
//  database classes
#include <afxdb.h>			// MFC database classes
#include <afxdao.h>			// MFC DAO database classes


#include "..\Common\CommonError.h"
#include "..\Common\CommonSmart.h"
#include "..\Common\CommonMgaTrukk.h"

#include "..\Mga\MgaLib.h"
#include <afxwin.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__CDB67FB4_2FC8_4014_88C6_9A46A1E63399__INCLUDED_)
