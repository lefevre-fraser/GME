
#ifndef MGA_MGAMETAPROJECT_H
#define MGA_MGAMETAPROJECT_H

#include <hash_map>
#include "CommonVersionInfo.h"

class CMgaMetaBase;

// --------------------------- CMgaMetaProject

class ATL_NO_VTABLE CMgaMetaProject : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMgaMetaProject, &CLSID_MgaMetaProject>,
	public IDispatchImpl<IMgaMetaProject, &IID_IMgaMetaProject, &LIBID_MGAMetaLib>,
	public IGMEVersionInfoImpl
{
public:
	CMgaMetaProject();
	~CMgaMetaProject();

	IUnknown *GetUnknown() const { return (IMgaMetaProject*)this; }

DECLARE_REGISTRY_RESOURCEID(IDR_MGAMETAPROJECT)

BEGIN_COM_MAP(CMgaMetaProject)
	COM_INTERFACE_ENTRY(IMgaMetaProject)
	COM_INTERFACE_ENTRY2(IDispatch, IMgaMetaProject)
	COM_INTERFACE_ENTRY_IID(IID_IGMEVersionInfo, IGMEVersionInfoImpl)
END_COM_MAP()

// ------- Methods

public:
	STDMETHOD(Open)(BSTR connection);
	STDMETHOD(Close)();
	STDMETHOD(Create)(BSTR connection);

	STDMETHOD(BeginTransaction)();
	STDMETHOD(CommitTransaction)();
	STDMETHOD(AbortTransaction)();

	STDMETHOD(get_GUID)(VARIANT *p);
	STDMETHOD(put_GUID)(VARIANT p);
	STDMETHOD(get_Name)(BSTR *p);
	STDMETHOD(put_Name)(BSTR p);
	STDMETHOD(get_DisplayedName)(BSTR *p);
	STDMETHOD(put_DisplayedName)(BSTR p);
	STDMETHOD(get_Version)(BSTR *p);
	STDMETHOD(put_Version)(BSTR p);
	STDMETHOD(get_Author)(BSTR *p);
	STDMETHOD(put_Author)(BSTR p);
	STDMETHOD(get_Comment)(BSTR *p);
	STDMETHOD(put_Comment)(BSTR p);
	STDMETHOD(get_CreatedAt)(BSTR *p);
	STDMETHOD(put_CreatedAt)(BSTR p);
	STDMETHOD(get_ModifiedAt)(BSTR *p);
	STDMETHOD(put_ModifiedAt)(BSTR p);

	STDMETHOD(get_RootFolder)(IMgaMetaFolder **p)
	{ return ::QueryInterface(rootobject, p); }

	STDMETHOD(get_FindObject)(metaref_type metaref, IMgaMetaBase **p);
	STDMETHOD(DoFindObjectDisp)(metaref_type metaref, IMgaMetaBase **p) { return get_FindObject( metaref, p); }

	STDMETHOD(SetNmspc)(BSTR p);
	STDMETHOD(GetNmspc)(BSTR *p);

// ------- metaobj_lookup

	// Through the metaobj_lookup we do not keep references (AddRef)
	// to objects, this would result in a dead-lock. So we use our
	// CoreTerritory to keep these objects alive. They will register
	// and unregister themselves.

public:
	typedef stdext::hash_map< metaref_type
	                        , IMgaMetaBase*
	                        , metaid_hashfunc
	                        > metaobj_lookup_type;
	typedef metaobj_lookup_type::iterator metaobj_lookup_iterator;

	metaobj_lookup_type metaobj_lookup;
	metaref_type max_metaref;

public:
	void RegisterMetaBase(metaref_type metaref, IMgaMetaBase *obj);
	void UnregisterMetaBase(metaref_type metaref, IMgaMetaBase *obj) NOTHROW;

// ------- properties

public:
	CComObjPtr<ICoreProject> coreproject;
	CComObjPtr<ICoreTerritory> coreterritory;
	CCoreObjectPtr rootobject;

	CComBSTR m_namespace;

// ------- Edit

public:
	void CreateMetaBase(metaid_type metaid, CCoreObjectPtr &obj);
	void CreateMetaObj(metaid_type metaid, CCoreObjectPtr &obj);

// ------- CheckPath

public:
	void CreatePathItems(bstr_const_iterator i, bstr_const_iterator e, pathitems_type &pathitems);
	void CreateJointPaths(BSTR paths, jointpaths_type &jointpaths);
};

#endif//MGA_MGAMETAPROJECT_H
