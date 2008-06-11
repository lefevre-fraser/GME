
#ifndef MGA_MGAMETASET_H
#define MGA_MGAMETASET_H

#ifndef MGA_MGAMETAFCO_H
#include "MgaMetaFCO.h"
#endif

// --------------------------- CMgaMetaSet

class ATL_NO_VTABLE CMgaMetaSet : 
	public CComCoClass<CMgaMetaSet, &CLSID_MgaMetaSet>,
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<IMgaMetaSet, &IID_IMgaMetaSet, &LIBID_METALib>,
	public CMgaMetaFCO
{
public:
	IUnknown *GetUnknown() const { return (IMgaMetaSet*)this; }

DECLARE_REGISTRY_RESOURCEID(IDR_MGAMETASET)
DECLARE_ONLY_AGGREGATABLE(CMgaMetaSet)

BEGIN_COM_MAP(CMgaMetaSet)
	COM_INTERFACE_ENTRY(IMgaMetaSet)
	COM_INTERFACE_ENTRY(IMgaMetaFCO)
	COM_INTERFACE_ENTRY2(IMgaMetaBase, CMgaMetaBase)
	COM_INTERFACE_ENTRY2(IDispatch, IMgaMetaSet)
END_COM_MAP()

DECLARE_MGAMETAFCO()

public:
	STDMETHOD(get_MemberSpec)(IMgaMetaPointerSpec **p)
	{ return ::QueryInterface(GetUnknown(), p); }

	STDMETHOD(CheckPath)(BSTR path, VARIANT_BOOL *p);

// ------- Traverse

public:
	static void Traverse(CMgaMetaProject *metaproject, CCoreObjectPtr &me);

};

#endif//MGA_MGAMETASET_H
