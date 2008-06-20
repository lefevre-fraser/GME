

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Fri Jun 20 10:24:42 2008
 */
/* Compiler settings for .\PanningView.idl:
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


#ifndef __PanningViewidl_h__
#define __PanningViewidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DPanningView_FWD_DEFINED__
#define ___DPanningView_FWD_DEFINED__
typedef interface _DPanningView _DPanningView;
#endif 	/* ___DPanningView_FWD_DEFINED__ */


#ifndef ___DPanningViewEvents_FWD_DEFINED__
#define ___DPanningViewEvents_FWD_DEFINED__
typedef interface _DPanningViewEvents _DPanningViewEvents;
#endif 	/* ___DPanningViewEvents_FWD_DEFINED__ */


#ifndef __PanningView_FWD_DEFINED__
#define __PanningView_FWD_DEFINED__

#ifdef __cplusplus
typedef class PanningView PanningView;
#else
typedef struct PanningView PanningView;
#endif /* __cplusplus */

#endif 	/* __PanningView_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __PanningViewLib_LIBRARY_DEFINED__
#define __PanningViewLib_LIBRARY_DEFINED__

/* library PanningViewLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_PanningViewLib;

#ifndef ___DPanningView_DISPINTERFACE_DEFINED__
#define ___DPanningView_DISPINTERFACE_DEFINED__

/* dispinterface _DPanningView */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DPanningView;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("3055658C-DEFE-4B68-9BC3-21B136BDBBDB")
    _DPanningView : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DPanningViewVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DPanningView * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DPanningView * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DPanningView * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DPanningView * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DPanningView * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DPanningView * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DPanningView * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DPanningViewVtbl;

    interface _DPanningView
    {
        CONST_VTBL struct _DPanningViewVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DPanningView_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DPanningView_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DPanningView_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DPanningView_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DPanningView_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DPanningView_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DPanningView_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DPanningView_DISPINTERFACE_DEFINED__ */


#ifndef ___DPanningViewEvents_DISPINTERFACE_DEFINED__
#define ___DPanningViewEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DPanningViewEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DPanningViewEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("BD4F784C-A79F-48F6-818D-0B829A061CC0")
    _DPanningViewEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DPanningViewEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DPanningViewEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DPanningViewEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DPanningViewEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DPanningViewEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DPanningViewEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DPanningViewEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DPanningViewEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DPanningViewEventsVtbl;

    interface _DPanningViewEvents
    {
        CONST_VTBL struct _DPanningViewEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DPanningViewEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DPanningViewEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DPanningViewEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DPanningViewEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DPanningViewEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DPanningViewEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DPanningViewEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DPanningViewEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_PanningView;

#ifdef __cplusplus

class DECLSPEC_UUID("B0C28BAA-7E44-404C-BEAD-83735356F1D2")
PanningView;
#endif
#endif /* __PanningViewLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


