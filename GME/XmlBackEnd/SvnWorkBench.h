// SvnWorkBench.h : Declaration of the CSvnWorkBench

#pragma once
#include "XmlBackEnd.h"
#include "resource.h"       // main symbols
#include <comsvcs.h>


// CSvnWorkBench

class ATL_NO_VTABLE CSvnWorkBench : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSvnWorkBench, &CLSID_SvnWorkBench>,
	public IDispatchImpl<ISvnWorkBench, &IID_ISvnWorkBench, &LIBID_XMLBACKENDLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CSvnWorkBench()
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

DECLARE_REGISTRY_RESOURCEID(IDR_SVNWORKBENCH)

DECLARE_NOT_AGGREGATABLE(CSvnWorkBench)

BEGIN_COM_MAP(CSvnWorkBench)
	COM_INTERFACE_ENTRY(ISvnWorkBench)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


protected:
	CComBSTR m_clue;

// ISvnWorkBench
public:
	STDMETHOD(ShowWorkBenchDlg)(void);
	STDMETHOD(SetClues)(BSTR connString);
	STDMETHOD(ShowResultDlg)(BSTR result);

};

OBJECT_ENTRY_AUTO(__uuidof(SvnWorkBench), CSvnWorkBench)
