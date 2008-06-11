

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Tue May 06 14:02:46 2008
 */
/* Compiler settings for .\PartBrowser.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __PartBrowseridl_h__
#define __PartBrowseridl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DPartBrowser_FWD_DEFINED__
#define ___DPartBrowser_FWD_DEFINED__
typedef interface _DPartBrowser _DPartBrowser;
#endif 	/* ___DPartBrowser_FWD_DEFINED__ */


#ifndef ___DPartBrowserEvents_FWD_DEFINED__
#define ___DPartBrowserEvents_FWD_DEFINED__
typedef interface _DPartBrowserEvents _DPartBrowserEvents;
#endif 	/* ___DPartBrowserEvents_FWD_DEFINED__ */


#ifndef __PartBrowser_FWD_DEFINED__
#define __PartBrowser_FWD_DEFINED__

#ifdef __cplusplus
typedef class PartBrowser PartBrowser;
#else
typedef struct PartBrowser PartBrowser;
#endif /* __cplusplus */

#endif 	/* __PartBrowser_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "Core.h"
#include "Meta.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __PartBrowserLib_LIBRARY_DEFINED__
#define __PartBrowserLib_LIBRARY_DEFINED__

/* library PartBrowserLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_PartBrowserLib;

#ifndef ___DPartBrowser_DISPINTERFACE_DEFINED__
#define ___DPartBrowser_DISPINTERFACE_DEFINED__

/* dispinterface _DPartBrowser */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DPartBrowser;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2D05F0EE-EB81-4D1D-A5C6-43146F38BF81")
    _DPartBrowser : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DPartBrowserVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DPartBrowser * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DPartBrowser * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DPartBrowser * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DPartBrowser * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DPartBrowser * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DPartBrowser * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DPartBrowser * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DPartBrowserVtbl;

    interface _DPartBrowser
    {
        CONST_VTBL struct _DPartBrowserVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DPartBrowser_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DPartBrowser_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DPartBrowser_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DPartBrowser_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DPartBrowser_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DPartBrowser_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DPartBrowser_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DPartBrowser_DISPINTERFACE_DEFINED__ */


#ifndef ___DPartBrowserEvents_DISPINTERFACE_DEFINED__
#define ___DPartBrowserEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DPartBrowserEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DPartBrowserEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("5042C3E4-58A9-4059-A5E4-FD7BFB3AA22B")
    _DPartBrowserEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DPartBrowserEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DPartBrowserEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DPartBrowserEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DPartBrowserEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DPartBrowserEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DPartBrowserEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DPartBrowserEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DPartBrowserEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DPartBrowserEventsVtbl;

    interface _DPartBrowserEvents
    {
        CONST_VTBL struct _DPartBrowserEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DPartBrowserEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DPartBrowserEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DPartBrowserEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DPartBrowserEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DPartBrowserEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DPartBrowserEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DPartBrowserEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DPartBrowserEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PartBrowser;

#ifdef __cplusplus

class DECLSPEC_UUID("1FF57057-D598-4FC2-8F9D-708F59B9C017")
PartBrowser;
#endif
#endif /* __PartBrowserLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


