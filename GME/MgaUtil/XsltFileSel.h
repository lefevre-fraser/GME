#ifndef XSLTFILESEL_H
#define XSLTFILESEL_H

#include "XSLTDial.h"

// --------------------------- CXsltFileSel
//

class ATL_NO_VTABLE CXsltFileSel 
	: public CComObjectRootEx<CComSingleThreadModel>
	, public CComCoClass<CXsltFileSel, &CLSID_MgaXsltFileSel>
	, public IMgaXsltFileSel
{
public:
	CXsltFileSel() { }
	~CXsltFileSel() { }

DECLARE_REGISTRY_RESOURCEID(IDR_MGAXSLTFILESEL)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CXsltFileSel)
 	COM_INTERFACE_ENTRY(IMgaXsltFileSel)
END_COM_MAP()

// ------- Properties

	STDMETHOD(StartXslt)( BSTR in, BSTR * out);

// ------- Attributes and Methods
public:

};
#endif // XSLTFILESEL_H
