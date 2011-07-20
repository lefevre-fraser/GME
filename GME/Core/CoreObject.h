
#ifndef MGA_COREOBJECT_H
#define MGA_COREOBJECT_H

#ifndef MGA_CORETRANSACTIONITEM_H
#include "CoreTransactionItem.h"
#endif

#ifndef MGA_COREMETAOBJECT_H
#include "CoreMetaObject.h"
#endif

#include <list>
//#include <slist>

class CCoreProject;
class CCoreAttribute;
class CCoreLockAttribute;
class CCoreMetaObject;

// --------------------------- CCoreObject

class ATL_NO_VTABLE CCoreObject : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ICoreObject, &IID_ICoreObject, &LIBID_MGACoreLib>,
	public ISupportErrorInfoImpl<&IID_ICoreObject>,
	public CCoreFinalTrItem
{
public:
	CCoreObject();
	virtual ~CCoreObject();

#ifdef DEBUG
	char footprint[4];
#endif

	static CComObjPtr<CCoreObject> Create(CCoreProject *project, metaid_type metaid, objid_type objid);

DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CCoreObject)
	COM_INTERFACE_ENTRY(ICoreObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY_FUNC_BLIND(0, &CCoreObject::AggregatedInterfaceLookup)
END_COM_MAP()

	static HRESULT WINAPI AggregatedInterfaceLookup(void *pvThis, REFIID riid, LPVOID *ppv, DWORD dw);		

// ------- COM methods

public:
	STDMETHODIMP get_Project(ICoreProject **p);
	STDMETHODIMP get_MetaObject(ICoreMetaObject **p);
	STDMETHODIMP get_ObjID(objid_type *p);
	STDMETHODIMP get_Attribute(attrid_type attrid, ICoreAttribute **p);
	STDMETHODIMP GetAttributeDisp(attrid_type attrid, ICoreAttribute **p) { return get_Attribute( attrid, p); }
	STDMETHODIMP get_Attributes(ICoreAttributes **p);
	STDMETHODIMP get_AttributeValue(attrid_type attrid, VARIANT *p);
	STDMETHODIMP GetAttributeValueDisp(attrid_type attrid, VARIANT *p) { return get_AttributeValue( attrid, p); }
	STDMETHODIMP put_AttributeValue(attrid_type attrid, VARIANT p);
	STDMETHODIMP SetAttributeValueDisp(attrid_type attrid, VARIANT p) { return put_AttributeValue( attrid, p); }
	STDMETHODIMP get_LoadedAttrValue(attrid_type attrid, VARIANT *p);
	STDMETHODIMP GetLoadedAttrValueDisp(attrid_type attrid, VARIANT *p) { return get_LoadedAttrValue( attrid, p); }
	STDMETHODIMP get_PreviousAttrValue(attrid_type attrid, VARIANT *p);
	STDMETHODIMP GetPreviousAttrValueDisp(attrid_type attrid, VARIANT *p) { return get_PreviousAttrValue( attrid, p); }
	STDMETHODIMP get_PeerLockValue(attrid_type attrid, locking_type *p);
	STDMETHODIMP GetPeerLockValueDisp(attrid_type attrid, locking_type *p) { return get_PeerLockValue( attrid, p); }
	STDMETHODIMP SearchCollection(attrid_type coll_attrid, attrid_type search_attrid,
		VARIANT search_value, ICoreObject **p);
	STDMETHODIMP get_IsDeleted(VARIANT_BOOL *p);
	STDMETHODIMP Delete();
	STDMETHODIMP Clone(ICoreObject **p);

// ------- Properties
	
protected:
	CComObjPtr<CCoreProject> project;
	CComObjPtr<CCoreMetaObject> metaobject;
	objid_type objid;

	typedef core::list<CCoreAttribute*> attributes_type;
	typedef attributes_type::iterator attributes_iterator;
	attributes_type attributes;

	typedef core::list< CComObjPtr<IUnknown> > aggregates_type;
	typedef aggregates_type::iterator aggregates_iterator;
	aggregates_type aggregates;

	typedef unsigned char status_type;
	status_type status;

// ------- Creation 

public:
	void CreateAttributes();
	void CreateAggregates();
	void FillAfterCreateObject();

// ------- Methods

public:
	objid_type GetObjID() const NOTHROW { return objid; }
	CCoreProject *GetProject() const NOTHROW { ASSERT( project ); return project; }
	CCoreMetaObject *GetMetaObject() const NOTHROW { ASSERT( metaobject ); return metaobject; }
	metaid_type GetMetaID() const NOTHROW { ASSERT( metaobject ); return metaobject->GetMetaID(); }

	CCoreAttribute *FindAttribute(attrid_type attrid) const NOTHROW;

	void RegisterAttribute(CCoreAttribute *attribute) NOTHROW;
	void UnregisterAttribute(CCoreAttribute *attribute) NOTHROW;

	template<class Functor, class UnwindFunctor>
	void GetAttributes(CCoreLockAttribute *lockattribute, Functor& f, UnwindFunctor& uf);

	void LoadAttributes(CCoreLockAttribute *lockattribute);
	void UnloadAttributes(CCoreLockAttribute *lockattribute) NOTHROW;

// ------- Status

#define COREOBJECT_DIRTY				0x0001

public:
	void SetStatusFlag(status_type flags) NOTHROW { status |= flags; }
	void ResetStatusFlag(status_type flags) NOTHROW { status &= ~flags; }
	bool GetStatusFlag(status_type flag) const NOTHROW { return (status & flag) != 0; }

public:
	bool InTransaction() const NOTHROW;
	bool InWriteTransaction() const NOTHROW;
	bool IsZombie() const NOTHROW { return project == NULL; }
	void SetZombie() NOTHROW;

	bool IsDirty() const NOTHROW { return GetStatusFlag(COREOBJECT_DIRTY); }
	void SetDirty() NOTHROW { SetStatusFlag(COREOBJECT_DIRTY); }
	void ResetDirty() NOTHROW { ResetStatusFlag(COREOBJECT_DIRTY); }

	bool HasEmptyPointers() const NOTHROW;
	bool HasEmptyPointersAndLocks() const NOTHROW;

// ------- Debug

#ifdef _DEBUG
public:
	void Dump();
#endif

// ------- FinalTrItem

public:
	void RegisterFinalTrItem() NOTHROW;

	virtual void AbortFinalTransaction() NOTHROW;
	virtual void CommitFinalTransaction();
	virtual void CommitFinalTransactionFinish(bool undo) NOTHROW;
};

inline IUnknown *CastToUnknown(CCoreObject *p) { return (IUnknown*)(ICoreObject*)p; }
inline CCoreObject *CastToObject(IUnknown *p) { return (CCoreObject*)(ICoreObject*)p; }

#endif//MGA_COREOBJECT_H
