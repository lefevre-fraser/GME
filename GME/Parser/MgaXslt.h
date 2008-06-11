#ifndef MGAXSLT_H_10983845732874589762348ajhdfkjasdhfbj
#define MGAXSLT_H_10983845732874589762348ajhdfkjasdhfbj

#include "resource.h"
#include "CommonVersionInfo.h"

// --------------------------- CMgaXslt


class ATL_NO_VTABLE CMgaXslt 
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CMgaXslt, &CLSID_MgaXslt>
	, public ISupportErrorInfoImpl<&IID_IMgaXslt>
	, public IDispatchImpl<IMgaXslt, &IID_IMgaXslt, &LIBID_PARSERLib>
	, public IMgaVersionInfoImpl
{
public:
	CMgaXslt() { }
	~CMgaXslt() { }

DECLARE_REGISTRY_RESOURCEID(IDR_MGAXSLT)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMgaXslt)
	COM_INTERFACE_ENTRY(IMgaXslt)
END_COM_MAP()

// ------- Properties

	STDMETHOD(ApplyXslt)( BSTR in1, BSTR in2, BSTR in3, BSTR * error);

// ------- Attributes and Methods
private:
	std::string getMgaDTDFromResource();
};

#endif // MGAXSLT_H_10983845732874589762348ajhdfkjasdhfbj
