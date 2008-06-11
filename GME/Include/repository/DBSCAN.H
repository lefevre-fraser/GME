/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 3.01.75 */
/* at Fri Sep 11 16:25:16 1998
 */
/* Compiler settings for DBScanner.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )
#include "rpc.h"
#include "rpcndr.h"

#ifndef __DBScan_h__
#define __DBScan_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IRepOLEDBScanner_FWD_DEFINED__
#define __IRepOLEDBScanner_FWD_DEFINED__
typedef interface IRepOLEDBScanner IRepOLEDBScanner;
#endif 	/* __IRepOLEDBScanner_FWD_DEFINED__ */


#ifndef __RepOLEDBScanner_FWD_DEFINED__
#define __RepOLEDBScanner_FWD_DEFINED__

#ifdef __cplusplus
typedef class RepOLEDBScanner RepOLEDBScanner;
#else
typedef struct RepOLEDBScanner RepOLEDBScanner;
#endif /* __cplusplus */

#endif 	/* __RepOLEDBScanner_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __DBSCANNERLib_LIBRARY_DEFINED__
#define __DBSCANNERLib_LIBRARY_DEFINED__

/****************************************
 * Generated header for library: DBSCANNERLib
 * at Fri Sep 11 16:25:16 1998
 * using MIDL 3.01.75
 ****************************************/
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_DBSCANNERLib;

#ifndef __IRepOLEDBScanner_INTERFACE_DEFINED__
#define __IRepOLEDBScanner_INTERFACE_DEFINED__

/****************************************
 * Generated header for interface: IRepOLEDBScanner
 * at Fri Sep 11 16:25:16 1998
 * using MIDL 3.01.75
 ****************************************/
/* [unique][helpstring][uuid][object] */ 



EXTERN_C const IID IID_IRepOLEDBScanner;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    interface DECLSPEC_UUID("985F4C8F-B859-11D1-922C-00C04FB6F948")
    IRepOLEDBScanner : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScanDB( 
            /* [in] */ /* external definition not present */ IRepository __RPC_FAR *pIRepository,
            /* [out][in] */ /* external definition not present */ IRepositoryObject __RPC_FAR *__RPC_FAR *pDbmDataSource,
            /* [in] */ BSTR szProviderName,
            /* [optional][in] */ BSTR szProviderString,
            /* [defaultvalue][optional][in] */ BSTR szDataSource,
            /* [defaultvalue][optional][in] */ BSTR szCatalog,
            /* [defaultvalue][optional][in] */ BSTR szUserName,
            /* [defaultvalue][optional][in] */ BSTR szPassword) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScanConnection( 
            /* [in] */ /* external definition not present */ IRepository __RPC_FAR *pRepository,
            /* [out][in] */ /* external definition not present */ IRepositoryObject __RPC_FAR *__RPC_FAR *pDbmDataSource,
            /* [in] */ IUnknown __RPC_FAR *pSession,
            /* [in] */ BSTR szCatalog) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScanDataLink( 
            /* [in] */ /* external definition not present */ IRepository __RPC_FAR *pRepository,
            /* [out][in] */ /* external definition not present */ IRepositoryObject __RPC_FAR *__RPC_FAR *ppDbmDataSource,
            /* [in] */ BSTR szPath,
            /* [optional][in] */ BSTR szUserName,
            /* [optional][in] */ BSTR szPassword) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IRepOLEDBScannerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IRepOLEDBScanner __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IRepOLEDBScanner __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IRepOLEDBScanner __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IRepOLEDBScanner __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IRepOLEDBScanner __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IRepOLEDBScanner __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IRepOLEDBScanner __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScanDB )( 
            IRepOLEDBScanner __RPC_FAR * This,
            /* [in] */ /* external definition not present */ IRepository __RPC_FAR *pIRepository,
            /* [out][in] */ /* external definition not present */ IRepositoryObject __RPC_FAR *__RPC_FAR *pDbmDataSource,
            /* [in] */ BSTR szProviderName,
            /* [optional][in] */ BSTR szProviderString,
            /* [defaultvalue][optional][in] */ BSTR szDataSource,
            /* [defaultvalue][optional][in] */ BSTR szCatalog,
            /* [defaultvalue][optional][in] */ BSTR szUserName,
            /* [defaultvalue][optional][in] */ BSTR szPassword);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScanConnection )( 
            IRepOLEDBScanner __RPC_FAR * This,
            /* [in] */ /* external definition not present */ IRepository __RPC_FAR *pRepository,
            /* [out][in] */ /* external definition not present */ IRepositoryObject __RPC_FAR *__RPC_FAR *pDbmDataSource,
            /* [in] */ IUnknown __RPC_FAR *pSession,
            /* [in] */ BSTR szCatalog);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ScanDataLink )( 
            IRepOLEDBScanner __RPC_FAR * This,
            /* [in] */ /* external definition not present */ IRepository __RPC_FAR *pRepository,
            /* [out][in] */ /* external definition not present */ IRepositoryObject __RPC_FAR *__RPC_FAR *ppDbmDataSource,
            /* [in] */ BSTR szPath,
            /* [optional][in] */ BSTR szUserName,
            /* [optional][in] */ BSTR szPassword);
        
        END_INTERFACE
    } IRepOLEDBScannerVtbl;

    interface IRepOLEDBScanner
    {
        CONST_VTBL struct IRepOLEDBScannerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IRepOLEDBScanner_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IRepOLEDBScanner_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IRepOLEDBScanner_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IRepOLEDBScanner_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IRepOLEDBScanner_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IRepOLEDBScanner_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IRepOLEDBScanner_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IRepOLEDBScanner_ScanDB(This,pIRepository,pDbmDataSource,szProviderName,szProviderString,szDataSource,szCatalog,szUserName,szPassword)	\
    (This)->lpVtbl -> ScanDB(This,pIRepository,pDbmDataSource,szProviderName,szProviderString,szDataSource,szCatalog,szUserName,szPassword)

#define IRepOLEDBScanner_ScanConnection(This,pRepository,pDbmDataSource,pSession,szCatalog)	\
    (This)->lpVtbl -> ScanConnection(This,pRepository,pDbmDataSource,pSession,szCatalog)

#define IRepOLEDBScanner_ScanDataLink(This,pRepository,ppDbmDataSource,szPath,szUserName,szPassword)	\
    (This)->lpVtbl -> ScanDataLink(This,pRepository,ppDbmDataSource,szPath,szUserName,szPassword)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRepOLEDBScanner_ScanDB_Proxy( 
    IRepOLEDBScanner __RPC_FAR * This,
    /* [in] */ /* external definition not present */ IRepository __RPC_FAR *pIRepository,
    /* [out][in] */ /* external definition not present */ IRepositoryObject __RPC_FAR *__RPC_FAR *pDbmDataSource,
    /* [in] */ BSTR szProviderName,
    /* [optional][in] */ BSTR szProviderString,
    /* [defaultvalue][optional][in] */ BSTR szDataSource,
    /* [defaultvalue][optional][in] */ BSTR szCatalog,
    /* [defaultvalue][optional][in] */ BSTR szUserName,
    /* [defaultvalue][optional][in] */ BSTR szPassword);


void __RPC_STUB IRepOLEDBScanner_ScanDB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRepOLEDBScanner_ScanConnection_Proxy( 
    IRepOLEDBScanner __RPC_FAR * This,
    /* [in] */ /* external definition not present */ IRepository __RPC_FAR *pRepository,
    /* [out][in] */ /* external definition not present */ IRepositoryObject __RPC_FAR *__RPC_FAR *pDbmDataSource,
    /* [in] */ IUnknown __RPC_FAR *pSession,
    /* [in] */ BSTR szCatalog);


void __RPC_STUB IRepOLEDBScanner_ScanConnection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IRepOLEDBScanner_ScanDataLink_Proxy( 
    IRepOLEDBScanner __RPC_FAR * This,
    /* [in] */ /* external definition not present */ IRepository __RPC_FAR *pRepository,
    /* [out][in] */ /* external definition not present */ IRepositoryObject __RPC_FAR *__RPC_FAR *ppDbmDataSource,
    /* [in] */ BSTR szPath,
    /* [optional][in] */ BSTR szUserName,
    /* [optional][in] */ BSTR szPassword);


void __RPC_STUB IRepOLEDBScanner_ScanDataLink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IRepOLEDBScanner_INTERFACE_DEFINED__ */


#ifdef __cplusplus
EXTERN_C const CLSID CLSID_RepOLEDBScanner;

class DECLSPEC_UUID("985F4C90-B859-11D1-922C-00C04FB6F948")
RepOLEDBScanner;
#endif
#endif /* __DBSCANNERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
