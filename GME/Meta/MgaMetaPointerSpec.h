
#ifndef MGA_MGAMETAPOINTERSPEC_H
#define MGA_MGAMETAPOINTERSPEC_H

// --------------------------- CMgaMetaPointerSpec

class ATL_NO_VTABLE CMgaMetaPointerSpec : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMgaMetaPointerSpec, &CLSID_MgaMetaPointerSpec>,
	public IDispatchImpl<IMgaMetaPointerSpec, &IID_IMgaMetaPointerSpec, &LIBID_MGAMetaLib>
{
public:
	IUnknown *GetUnknown() const { return (IMgaMetaPointerSpec*)this; }

DECLARE_REGISTRY_RESOURCEID(IDR_MGAMETAPOINTERSPEC)
DECLARE_ONLY_AGGREGATABLE(CMgaMetaPointerSpec)

BEGIN_COM_MAP(CMgaMetaPointerSpec)
	COM_INTERFACE_ENTRY(IMgaMetaPointerSpec)
	COM_INTERFACE_ENTRY2(IDispatch, IMgaMetaPointerSpec)
END_COM_MAP()

public:
	STDMETHOD(get_Parent)(IDispatch **p);

	STDMETHOD(get_Name)(BSTR *p)
	{ return ComGetAttrValue(GetUnknown(), ATTRID_PTRSPECNAME, p); }

	STDMETHOD(get_Items)(IMgaMetaPointerItems **p)
	{ return ComGetCollectionValue<IMgaMetaPointerItem>(
		GetUnknown(), ATTRID_PTRITEMS_COLL, p); }

// ------- Edit

public:
	STDMETHOD(put_Name)(BSTR p)
	{ return ComPutAttrValue(GetUnknown(), ATTRID_PTRSPECNAME, p); }

	STDMETHOD(CreateItem)(IMgaMetaPointerItem **p)
	{ return ComCreateMetaObj(GetUnknown(), METAID_METAPOINTERITEM, ATTRID_PTRITEMS_COLL, p); }

// ------- Methods

public:
	static void Traverse(CMgaMetaProject *metaproject, CCoreObjectPtr &me);
	static bool CheckPath(CCoreObjectPtr &self, pathitems_type &pathitems, bool global);
};

#endif//MGA_MGAMETAPOINTERSPEC_H
