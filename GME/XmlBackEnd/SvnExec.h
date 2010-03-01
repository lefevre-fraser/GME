// SvnExec.h : Declaration of the CSvnExec

#pragma once
#include "XmlBackEnd.h"
#include "svauto.h"
#include "HiClient.h"
#include "resource.h"       // main symbols
#include <comsvcs.h>


// CSvnExec

class ATL_NO_VTABLE CSvnExec : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSvnExec, &CLSID_SvnExec>,
	public IDispatchImpl<ISvnExec, &IID_ISvnExec, &LIBID_XMLBACKENDLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CSvnExec()
	{
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_SVNEXEC)

DECLARE_NOT_AGGREGATABLE(CSvnExec)

BEGIN_COM_MAP(CSvnExec)
	COM_INTERFACE_ENTRY(ISvnExec)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


// ISvnExec
public:
	STDMETHOD(TryLock)(BSTR path, VARIANT_BOOL* success);
	STDMETHOD(UnLock)(BSTR path, VARIANT_BOOL* success);
	STDMETHOD(AddLockableProperty)(BSTR path);
	STDMETHOD(GetLatest)(BSTR path);
	STDMETHOD(LightCheckOut)(BSTR path, BSTR localDir);
	STDMETHOD(Commit)(BSTR path, BSTR comment, VARIANT_BOOL keepLocked);
	STDMETHOD(Add)(BSTR path, VARIANT_BOOL recursive);
	STDMETHOD(SrvMkDir)(BSTR path);
	STDMETHOD(Resolve)(BSTR path, VARIANT_BOOL recursive);
	STDMETHOD(CleanUp)(BSTR path);
	STDMETHOD(Status)(BSTR path, VARIANT_BOOL provideStatusMessage, BSTR* statusMessage);
	STDMETHOD(Info)(BSTR url, VARIANT_BOOL recursive, VARIANT_BOOL provideInfoMessage, BSTR* infoMsg, BSTR* author, BSTR* lockOwner);
	STDMETHOD(IsVersioned)(BSTR path, VARIANT_BOOL isDir, VARIANT_BOOL suppressErrorMsg, VARIANT_BOOL* isVersioned);
	STDMETHOD(IsLocked)(BSTR path, VARIANT_BOOL* isLocked, BSTR* lockHolder);
	STDMETHOD(Init)(BSTR username, BSTR password);
	STDMETHOD(ReplaceUserName)(BSTR userName);
	STDMETHOD(Logging)(VARIANT_BOOL onoff, BSTR logfile);
	STDMETHOD(IsUpToDate)(BSTR path, VARIANT_BOOL* upToDate);
	STDMETHOD(BulkUnLock)(VARIANT pathVec, VARIANT_BOOL* success);
	STDMETHOD(SpeedLock)(VARIANT targets, VARIANT_BOOL* success, BSTR* succ_msg);

protected:
	VARIANT_BOOL      b2vb( bool val);
	bool              vb2b( VARIANT_BOOL val);

	HiClient    *m_impl;
	
};

OBJECT_ENTRY_AUTO(__uuidof(SvnExec), CSvnExec)
