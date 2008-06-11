// SvnTester.h : Declaration of the CSvnTester

#pragma once
#include "XmlBackEnd.h"
#include "HiClient.h"
#include "CmdClient.h"
#include "resource.h"       // main symbols
#include <comsvcs.h>

// CSvnTester

class ATL_NO_VTABLE CSvnTester : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSvnTester, &CLSID_SvnTester>,
	public IDispatchImpl<ISvnTester, &IID_ISvnTester, &LIBID_XMLBACKENDLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CSvnTester()
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

DECLARE_REGISTRY_RESOURCEID(IDR_SVNTESTER)

DECLARE_NOT_AGGREGATABLE(CSvnTester)

BEGIN_COM_MAP(CSvnTester)
	COM_INTERFACE_ENTRY(ISvnTester)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


// ISvnTester
public:
	STDMETHOD(info)    (BSTR url, VARIANT_BOOL byApi, VARIANT_BOOL recursive, BSTR* resultMsg);
	STDMETHOD(status)  (BSTR url, VARIANT_BOOL byApi, VARIANT_BOOL onserver, BSTR* resultMsg);
	STDMETHOD(cleanup) (BSTR path, VARIANT_BOOL byApi, BSTR* resultMsg);
	STDMETHOD(resolve) (BSTR path, VARIANT_BOOL byApi, VARIANT_BOOL recursive);
	STDMETHOD(commit)  (BSTR path, VARIANT_BOOL byApi, VARIANT_BOOL recursive);
	STDMETHOD(checkout)(BSTR url, BSTR path, VARIANT_BOOL byApi, VARIANT_BOOL recursive);
	STDMETHOD(add)     (BSTR path, VARIANT_BOOL byApi, VARIANT_BOOL recursive);
	STDMETHOD(propset) (BSTR path, BSTR propname, BSTR propval, VARIANT_BOOL byApi, VARIANT_BOOL recursive);
	STDMETHOD(lock)    (BSTR path, VARIANT_BOOL force, VARIANT_BOOL byAPI);
	STDMETHOD(unlock)  (BSTR path, VARIANT_BOOL force, VARIANT_BOOL byAPI);
	STDMETHOD(update)  (BSTR path, VARIANT_BOOL byApi);
	STDMETHOD(testSubversionSettingsDir) (BSTR* resultMsg);
	STDMETHOD(testSubversionSettingsDlg) ();
protected:
	bool        getLoginData();

	std::string                 m_svnUrl;
	std::string                 m_username;
	std::string                 m_password;

	HiClient                    *m_apiSvn;
	CmdClient                   *m_cmdSvn;
};

OBJECT_ENTRY_AUTO(__uuidof(SvnTester), CSvnTester)
