
#ifndef MGA_MGAMETABASE_H
#define MGA_MGAMETABASE_H

#ifndef MGA_MGAMETAPROJECT_h
#include "MgaMetaProject.h"
#endif

#ifndef MGA_MGAMETAREGNODE_H
#include "MgaMetaRegNode.h"
#endif

// --------------------------- CMgaMetaBase

class ATL_NO_VTABLE CMgaMetaBase :
	public IDispatchImpl<IMgaMetaBase, &IID_IMgaMetaBase, &LIBID_METALib>,
	public CMgaMetaRegNodes
{
public:
	CMgaMetaBase() : metaproject(NULL) { }
	~CMgaMetaBase();

public:
	HRESULT PutMetaRef(metaref_type p);

	static void Traverse(CMgaMetaProject *metaproject, CCoreObjectPtr &me);

	CMgaMetaProject *metaproject;
	metaref_type metaref;
};

// --------------------------- DECLARE

#define DECLARE_MGAMETABASE() \
DECLARE_PROTECT_FINAL_CONSTRUCT() \
DECLARE_MGAMETAREGNODES() \
\
public: \
	STDMETHOD(get_MetaRef)(metaref_type *p) \
	{  \
		CHECK_OUT(p); \
		*p = metaref; \
		return S_OK; \
	} \
	STDMETHOD(put_MetaRef)(metaref_type p) \
	{ HRESULT hr = PutMetaRef(p); \
		if(hr == S_OK) hr = ComPutAttrValue(GetUnknown(), ATTRID_METAREF, p); \
		return hr; \
	} \
\
	STDMETHOD(get_MetaProject)(IMgaMetaProject **p) \
	{ \
		CHECK_OUT(p); \
		CopyTo(metaproject, p); \
		return S_OK; \
	} \
\
	STDMETHOD(get_Name)(BSTR *p) \
	{ \
		COMTRY { \
			CComBSTR pn; \
			COMTHROW( ComGetAttrValue(GetUnknown(), ATTRID_NAME, &pn)); \
			CComBSTR tn = truncateName( GetUnknown(), pn); \
			*p = tn.Detach(); \
		} COMCATCH(;) \
	} \
\
	STDMETHOD(put_Name)(BSTR p) \
	{ return ComPutAttrValue(GetUnknown(), ATTRID_NAME, p); } \
\
	STDMETHOD(get_DisplayedName)(BSTR *p) \
	{ \
		COMTRY { \
			CComBSTR pn; \
			COMTHROW( ComGetDisplayedName( GetUnknown(), ATTRID_DISPNAME, ATTRID_NAME, &pn)); \
			CComBSTR tn = truncateName( GetUnknown(), pn); \
			*p = tn.Detach(); \
		} COMCATCH(;) \
	} \
\
	STDMETHOD(put_DisplayedName)(BSTR p) \
	{ return ComPutAttrValue(GetUnknown(), ATTRID_DISPNAME, p); } \
\
	STDMETHOD(get_ObjType)(objtype_enum *p) \
	{ return ComGetObjType(GetUnknown(), p); } \
\
	STDMETHOD(get_Constraints)(IMgaMetaConstraints **p)  \
	{ return ComGetCollectionValue<IMgaMetaConstraint>( \
		GetUnknown(), ATTRID_CONSTRAINT_PTR, p); } \
\
	STDMETHOD(CreateConstraint)(IMgaMetaConstraint **p) \
	{ return ComCreateMetaObj(GetUnknown(), METAID_METACONSTRAINT, ATTRID_CONSTRAINT_PTR, p); } \
\
	STDMETHOD(Delete)() \
	{ return ComDeleteObject(GetUnknown()); }

#endif//MGA_MGAMETABASE_H
