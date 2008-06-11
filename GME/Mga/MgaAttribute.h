// MgaAttribute.h : Declaration of the CMgaAttribute

#ifndef __MGAATTRIBUTE_H_
#define __MGAATTRIBUTE_H_

#include "resource.h"       // main symbols



/////////////////////////////////////////////////////////////////////////////
// CMgaAttribute
class ATL_NO_VTABLE CMgaAttribute : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMgaAttribute, &CLSID_MgaAttribute>,
	public IDispatchImpl<IMgaAttribute, &IID_IMgaAttribute, &LIBID_MGALib>,
	public ISupportErrorInfoImpl<&IID_IMgaAttribute>
{
public:
	CMgaAttribute()	: prevptr(NULL), next(NULL), load_status(ATTSTATUS_INVALID) {	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMgaAttribute)
	COM_INTERFACE_ENTRY(IMgaAttribute)
	COM_INTERFACE_ENTRY_IID(IID_ISupportErrorInfo, IMyErrorInfoBase)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IMgaAttribute
public:
	STDMETHOD(get_Meta)( IMgaMetaAttribute **pVal) {
		COMTRY {
				CHECK_OUTPTRPAR(pVal);
				CComQIPtr<IMgaMetaAttribute> m(mgaproject->FindMetaRef(mref));
				*pVal = m.Detach();
		} COMCATCH(;)
	}
	STDMETHOD(get_Owner)( IMgaFCO **pVal);
	STDMETHOD(get_Status)( long *status);
	STDMETHOD(get_Value)( VARIANT *pVal);
	STDMETHOD(put_Value)( VARIANT newVal);

	STDMETHOD(get_StringValue)(BSTR *pVal);
	STDMETHOD(put_StringValue)( BSTR newVal);
	STDMETHOD(get_OrigValue)( VARIANT *pVal);
	STDMETHOD(get_HasChanged)( VARIANT_BOOL *pVal);

	STDMETHOD(get_IntValue)( long *pVal);
	STDMETHOD(put_IntValue)( long newVal);
	STDMETHOD(get_BoolValue)( VARIANT_BOOL *pVal);
	STDMETHOD(put_BoolValue)( VARIANT_BOOL newVal);
	STDMETHOD(get_FloatValue)( double *pVal);
	STDMETHOD(put_FloatValue)( double newVal);
	STDMETHOD(get_FCOValue)( IMgaFCO **pVal);
	STDMETHOD(put_FCOValue)( IMgaFCO * newVal);

	STDMETHOD(get_RegistryNode)( BSTR path,  IMgaRegNode **pVal); 
	STDMETHOD(GetRegistryNodeDisp)( BSTR path,  IMgaRegNode **pVal) { return get_RegistryNode( path, pVal); }
	STDMETHOD(get_Registry)(VARIANT_BOOL virtuals, IMgaRegNodes **pVal);
	STDMETHOD(GetRegistryDisp)(VARIANT_BOOL virtuals, IMgaRegNodes **pVal) { return get_Registry( virtuals, pVal); }
	STDMETHOD(get_RegistryValue)( BSTR path,  BSTR *pVal);
	STDMETHOD(put_RegistryValue)( BSTR path,  BSTR newval);
	STDMETHOD(GetRegistryValueDisp)( BSTR path,  BSTR *pVal) { return get_RegistryValue( path, pVal); }
	STDMETHOD(SetRegistryValueDisp)( BSTR path,  BSTR newval) { return put_RegistryValue( path, newval); }

	STDMETHOD(Clear)();

	typedef CMgaAttribute *hashobp;
	hashobp *prevptr, next;
	~CMgaAttribute() {						// remove object from hash
		if(next) next->prevptr = prevptr;
		*prevptr = next;
	}
	void Initialize(metaref_type mr, FCO *o, CMgaProject *p);   // Throws!!!
	metaref_type mref;

	long load_status;
	CoreObj valueobj;
	CComQIPtr<IMgaMetaAttribute> mvalueobj;
	FCOPtr fco;
	attval_enum attrtyp, inputtyp;
	CMgaProject *mgaproject;
	CComBSTR(regprefix);
};


#define APOOL_HASHSIZE 8
#define apool_hash(x) ((x)%APOOL_HASHSIZE)


class attrpool {
	CMgaAttribute::hashobp pool[APOOL_HASHSIZE];
public:
	attrpool() { 
		int i; 
		for(i = 0; i < APOOL_HASHSIZE;i++) pool[i] = NULL;
	}

	~attrpool() {
		int i; 
		for(i = 0; i < APOOL_HASHSIZE;i++) ASSERT(pool[i] == NULL);
	}

	// Throws (allocates)!!!!
	CComPtr<IMgaAttribute> getpoolobj(metaref_type mref, FCO *o, CMgaProject *pr) {
		CMgaAttribute::hashobp &k = pool[apool_hash(mref)], *kk;
		for(kk = &k; *kk != NULL; kk = &((*kk)->next)) {
			if((*kk)->mref == mref) {
				return (*kk);
			}
		}
		CComPtr<CMgaAttribute> s;
		CreateComObject(s);
		s->prevptr = &k;				// Insert to the front
		s->next = k;
		if(k) k->prevptr = &(s->next);
		k = s;

		s->Initialize(mref, o, pr);  
		CComPtr<IMgaAttribute> retval = s;
		return retval;
	}
};

void MergeAttrs(const CoreObj &src, CoreObj &dst);


/////////////////////////////////////////////////////////////////////////////
// CMgaRegNode
class ATL_NO_VTABLE CMgaRegNode : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMgaRegNode, &CLSID_MgaRegNode>,
	public IDispatchImpl<IMgaRegNode, &IID_IMgaRegNode, &LIBID_MGALib>,
	public ISupportErrorInfoImpl<&IID_IMgaRegNode>
{
public:

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMgaRegNode)
	COM_INTERFACE_ENTRY(IMgaRegNode)
	COM_INTERFACE_ENTRY_IID(IID_ISupportErrorInfo, IMyErrorInfoBase)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IMgaRegNode
	void markchg();
public:
	STDMETHOD(get_Name)( BSTR *pVal) { 
		COMTRY {
			CHECK_OUTPAR(pVal);
			LPCOLESTR p = wcsrchr(mypath, '/');
			if(p) p += 1; // skip '/'
			else p = mypath;
			CComBSTR rval(p);
			*pVal = rval.Detach();
		} COMCATCH(;); 
	};
	STDMETHOD(get_Path)( BSTR *pVal) { 
		COMTRY {
			CHECK_OUTPAR(pVal);
			*pVal = mypath.Copy();
		} COMCATCH(;); 
	};
	STDMETHOD(get_Object)( IMgaObject **pVal);
	STDMETHOD(get_Value)( BSTR *pVal);
	STDMETHOD(put_Value)( BSTR newVal);
	STDMETHOD(get_FCOValue)( IMgaFCO **pVal);
	STDMETHOD(put_FCOValue)( IMgaFCO *newVal);
	STDMETHOD(get_SubNodes)( VARIANT_BOOL virtuals, IMgaRegNodes **pVal);
	STDMETHOD(GetSubNodesDisp)( VARIANT_BOOL virtuals, IMgaRegNodes **pVal) { return get_SubNodes( virtuals, pVal); }
	STDMETHOD(get_SubNodeByName)(BSTR name, IMgaRegNode **pVal);
	STDMETHOD(GetSubNodeByNameDisp)(BSTR name, IMgaRegNode **pVal) { return get_SubNodeByName( name, pVal); }
	STDMETHOD(get_ParentNode)( IMgaRegNode **pVal);

	STDMETHOD(get_Status)( long *status);
	STDMETHOD(get_Opacity)( VARIANT_BOOL *pVal);
	STDMETHOD(put_Opacity)( VARIANT_BOOL newVal);
	STDMETHOD(Clear)();
	STDMETHOD(RemoveTree)();

	typedef CMgaRegNode *hashobp;
	hashobp *prevptr, next;
	CMgaRegNode()	: prevptr(NULL), next(NULL), load_status(ATTSTATUS_INVALID) {	}
	~CMgaRegNode() {						// remove object from hash
		if(next) next->prevptr = prevptr;
		*prevptr = next;
	}
	void Initialize(BSTR path, FCO *o, CMgaProject *p) {   // Throws!!!
		mypath = path;		
		fco = o;
		mgaproject = p;
	}

	long load_status;
	CoreObj valueobj;
	FCOPtr fco;
	CComBSTR mypath;
	CMgaProject *mgaproject;
};


#define RPOOL_HASHSIZE 8


class regnpool {
	CMgaRegNode::hashobp pool[RPOOL_HASHSIZE];
public:
	regnpool() { 
		int i; 
		for(i = 0; i < RPOOL_HASHSIZE;i++) pool[i] = NULL;
	}

	~regnpool() {
		int i; 
		for(i = 0; i < RPOOL_HASHSIZE;i++) ASSERT(pool[i] == NULL);
	}

	int rpool_hash(BSTR nam) {
		int i = SysStringLen(nam);
		int hash = i;
		while(i) hash ^= nam[--i];
		return hash % RPOOL_HASHSIZE;
	}

	// Throws (allocates)!!!!
	CComPtr<IMgaRegNode>  getpoolobj(BSTR nam, FCO *o, CMgaProject *pr) {
		CMgaRegNode::hashobp &k = pool[rpool_hash(nam)], *kk;
		for(kk = &k; *kk != NULL; kk = &((*kk)->next)) {
			if((*kk)->mypath == nam) {
				return (*kk);
			}
		}
		CComPtr<CMgaRegNode > s;
		CreateComObject(s);
		s->prevptr = &k;				// Insert to the front
		s->next = k;
		if(k) k->prevptr = &(s->next);
		k = s;

		s->Initialize(nam, o, pr);  
		CComPtr<IMgaRegNode> retval = s;
		return retval;
	}
};

void RegistryChildrenRemove(CoreObj &t);
void MergeRegs(const CoreObj &src, CoreObj &dst);



/////////////////////////////////////////////////////////////
// CMgaPart
/////////////////////////////////////////////////////////////

class ATL_NO_VTABLE CMgaPart : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMgaPart, &CLSID_MgaPart>,
	public IDispatchImpl<IMgaPart, &IID_IMgaPart, &LIBID_MGALib>,
	public ISupportErrorInfoImpl<&IID_IMgaPart>
{
public:

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMgaPart)
	COM_INTERFACE_ENTRY(IMgaPart)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY_IID(IID_ISupportErrorInfo, IMyErrorInfoBase)
END_COM_MAP()

// IMgaPart
public:
	STDMETHOD(get_Model)(struct IMgaModel **pVal );
	STDMETHOD(get_Meta)(struct IMgaMetaPart **pVal );
	STDMETHOD(get_MetaAspect)(struct IMgaMetaAspect **pVal );
	STDMETHOD(get_MetaRole)(struct IMgaMetaRole **pVal );
	STDMETHOD(get_FCO)(struct IMgaFCO **pVal);
	STDMETHOD(get_AccessMask)(long *);

	STDMETHOD(GetGmeAttrs)(BSTR *icon,long *x,long *y);
	STDMETHOD(SetGmeAttrs)(BSTR icon,long x,long y);

	STDMETHOD(get_RegistryMode)( VARIANT_BOOL *own);
	STDMETHOD(put_RegistryMode)( VARIANT_BOOL own);

	STDMETHOD(get_RegistryNode)( BSTR path,  IMgaRegNode **pVal);
	STDMETHOD(GetRegistryNodeDisp)( BSTR path,  IMgaRegNode **pVal) { return get_RegistryNode( path, pVal); }
	STDMETHOD(get_Registry)( VARIANT_BOOL virtuals, IMgaRegNodes **pVal);
	STDMETHOD(GetRegistryDisp)( VARIANT_BOOL virtuals, IMgaRegNodes **pVal) { return get_Registry( virtuals, pVal); }
	STDMETHOD(get_RegistryValue)( BSTR path,  BSTR *pVal);
	STDMETHOD(put_RegistryValue)( BSTR path,  BSTR newval);  
	STDMETHOD(GetRegistryValueDisp)( BSTR path,  BSTR *pVal) { return get_RegistryValue( path, pVal); }
	STDMETHOD(SetRegistryValueDisp)( BSTR path,  BSTR newval) { return put_RegistryValue( path, newval); }
	CMgaPart();
	~CMgaPart();
	void Initialize(metaref_type mr, FCO *o, CMgaProject *p);
	typedef CMgaPart *hashobp;
	hashobp *prevptr, next;
	metaref_type mref;

	long load_status;
	FCOPtr fco;
	CMgaProject *mgaproject;  // Holds no reference
	CComBSTR(regprefix);
	CComBSTR(aspname);
};



#define PPOOL_HASHSIZE 4
#define ppool_hash(x) ((x)%PPOOL_HASHSIZE)


class partpool {
	CMgaPart::hashobp pool[PPOOL_HASHSIZE];
public:
	partpool() { 
		int i; 
		for(i = 0; i < PPOOL_HASHSIZE;i++) pool[i] = NULL;
	}

	~partpool() {
		int i; 
		for(i = 0; i < PPOOL_HASHSIZE;i++) ASSERT(pool[i] == NULL);
	}

	// Throws (allocates)!!!!
	CComPtr<IMgaPart> getpoolobj(metaref_type mref, FCO *o, CMgaProject *pr) {
		CMgaPart::hashobp &k = pool[ppool_hash(mref)], *kk;
		for(kk = &k; *kk != NULL; kk = &((*kk)->next)) {
			if((*kk)->mref == mref) {
				return (*kk);
			}
		}
		CComPtr<CMgaPart > s;
		CreateComObject(s);
		s->prevptr = &k;				// Insert to the front
		s->next = k;
		if(k) k->prevptr = &(s->next);
		k = s;

		s->Initialize(mref, o, pr);  
		CComPtr<IMgaPart> retval = s;
		return retval;
	}
};

#endif //__MGAATTRIBUTE_H_
