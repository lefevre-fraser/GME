// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#if !defined(AFX_STDAFX_H__70C41B18_E3CE_11D3_B37A_005004D38590__INCLUDED_)
#define AFX_STDAFX_H__70C41B18_E3CE_11D3_B37A_005004D38590__INCLUDED_

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _CRT_SECURE_NO_WARNINGS

#define _ATL_APARTMENT_THREADED

#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>


#define ASSERT ATLASSERT

#include "ParserLib.h"
#include "CommonSmart.h"
#include "CommonStl.h"
#define GLOBAL_ID_STR   "guid"
#define GLOBAL_ID_LEN   38
#define PREV_GLOBAL_ID_STR   "guid/prev"
#define PREV_ID_STR     "prev"
typedef IMgaConstraint IMgaMetaConstraint;
typedef IMgaConstraints IMgaMetaConstraints;

#include <string>
namespace std {
#ifdef UNICODE
	typedef wstring tstring;
#else
	typedef string tstring;
#endif
}
static void CopyTo(const BSTR from, std::wstring& to)
{
	if (from != NULL) {
		to = from;
	} else {
		to = L"";
	}
}
#include "comutil.h"
#include "comdef.h"
static _bstr_t PutInBstr(const std::wstring& str)
{
	return _bstr_t(str.c_str());
}
static _bstr_t PutInBstr(const std::string& str)
{
	return _bstr_t(str.c_str());
}

#include <xercesc/util/PlatformUtils.hpp>
class XMLPlatformUtilsTerminate_RAII {
public:
	~XMLPlatformUtilsTerminate_RAII() { xercesc_3_1::XMLPlatformUtils::Terminate(); }
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__70C41B18_E3CE_11D3_B37A_005004D38590__INCLUDED)
