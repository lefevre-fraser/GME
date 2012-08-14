// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently


#if !defined(AFX_STDAFX_H__270B4F89_B17C_11D3_9AD1_00AA00B6FE26__INCLUDED_)
#define AFX_STDAFX_H__270B4F89_B17C_11D3_9AD1_00AA00B6FE26__INCLUDED_

#pragma once

//#define _SECURE_SCL 0
//#define _HAS_ITERATOR_DEBUGGING 0

//#define _ATL_DEBUG_INTERFACES
// If you find a leak, put this in DllMain to DebugBreak on every AddRef/Release on that interface pointer
// _AtlDebugInterfacesModule.m_nIndexBreakAt = 42;

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
#pragma warning(push,3)


#include <list>//slist
#include <string>
#include <set>
#include <queue>
#include <vector>
#include <hash_set>
#include <hash_map>
#pragma warning(pop)

#ifdef _DEBUG
#define MGA_TRACE AtlTrace
#else
inline void NOOP_TRACE2(LPCSTR, ...) { }
#define MGA_TRACE 1 ? void(0) : NOOP_TRACE2
#endif

// Imports
#import "CoreLib.tlb" no_implementation no_namespace raw_method_prefix("") high_method_prefix("__") no_registry
#import "MetaLib.tlb" no_implementation no_namespace raw_method_prefix("") high_method_prefix("__") no_registry
#import "MgaLib.tlb" no_implementation no_namespace raw_method_prefix("") high_method_prefix("__") no_registry

#include "CommonImport.h"

#define cpp_quote(x) 
#include "Interfaceversion.h"
#undef cpp_quote

typedef GMEInterfaceVersion_enum GMEInterfaceVersion;
typedef long metaref_type;
#define ATTVAL_ENUM _attval_enum
const attrid_type ATTRID_NONE = 0;
const attrid_type ATTRID_LOCK = 1;
const attrid_type ATTRID_NAME = 2;
const attrid_type ATTRID_FATHER = 3;
const attrid_type ATTRID_COLLECTION = 10000;
const metaid_type METAID_NONE = 0;
const metaid_type METAID_ROOT = 1;

const objid_type OBJID_NONE = 0;
const objid_type OBJID_ROOT = 1;
const long RELID_BASE_MAX  = 0x7FFFFFF;	//assigned to non-derived ojects
const long RELID_VALUE_MAX = 0x7FFFFFFF;   // automatically assigned to deriveds


// Don't load the MIDL-generated headers
#define __Core_h__
#define __Meta_h__
#define __Mga_h__
#define INTERFACECOLL_INCLUDED
// End Imports

#define ASSERT ATLASSERT
#include "CommonSmart.h"
#include "CommonStl.h"
#include "CommonError.h"
#include "CommonCollection.h"
#include "MgaGeneric.h"
#include "MgaCoreObj.h"
#include "MgaTrukk.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__270B4F89_B17C_11D3_9AD1_00AA00B6FE26__INCLUDED)
