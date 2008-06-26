
#ifndef MGA_COREATTRIBUTE_H
#define MGA_COREATTRIBUTE_H

#ifndef MGA_CORETRANSACTIONITEM_H
#include "CoreTransactionItem.h"
#endif

#ifndef MGA_COREMETAATTRIBUTE_H
#include "CoreMetaAttribute.h"
#endif

#ifndef MGA_COREOBJECT_H
#include "CoreObject.h"
#endif

#include <list>
#include <set>

// comparison of an invalid (null or simply default constructed) iterator 
// with a valid iterator in MS STL is cumbersome. See EQUAL_WITH_NO_OBJECT in CoreBinFile.h 
// for explanation for a macro similar to this
#define INVALID_ITERATOR( x) ( x._Mycont == 0)

class CCoreProject;
class CCoreLockAttribute;
class CCoreCollectionAttribute;
class CCoreTerritory;
class CCoreMetaAttribute;

// --------------------------- CCoreAttribute

class ATL_NO_VTABLE CCoreAttribute : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ICoreAttribute, &IID_ICoreAttribute, &LIBID_CORELib>,
	public ISupportErrorInfoImpl<&IID_ICoreAttribute>
{
public:
	CCoreAttribute();
	virtual ~CCoreAttribute();

#ifdef DEBUG
	char footprint[4];
#endif

	static void Create(CCoreObject *object, CCoreMetaAttribute *metaattribute);

DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CCoreAttribute)
	COM_INTERFACE_ENTRY(ICoreAttribute)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ------- COM methods

public:
	STDMETHOD(get_Object)(ICoreObject **p);
	STDMETHOD(get_MetaAttribute)(ICoreMetaAttribute **p);

// ------- Properties

protected:
	CComObjPtr<CCoreMetaAttribute> metaattribute;

	typedef unsigned char status_type;
	status_type status;

// ------- Methods

public:
	// CCoreAttributes are always used as CComPartObjects
	// where the m_pOuterUnknown points the owner
	CCoreObject *GetObject() const NOTHROW 
	{
		ASSERT( m_pOuterUnknown ); 
		return CastToObject(m_pOuterUnknown); 
	}

	CCoreMetaAttribute *GetMetaAttribute() const NOTHROW { ASSERT( metaattribute ); return metaattribute; }
	attrid_type GetAttrID() const NOTHROW { ASSERT( metaattribute ); return metaattribute->attrid; }
	
	virtual valtype_type GetValType() const NOTHROW = 0;
	virtual CCoreLockAttribute *GetLockAttr() const;

	ICoreStorage *SetStorageThisAttribute();

	// if type mismatch then returns false
	virtual bool DoesMatch(bool do_load, const VARIANT &v) { return false; }

// ------- Inline

public:
	CCoreProject *GetProject() const NOTHROW;
	CCoreTerritory *GetTerritory() const NOTHROW;

// ------- Status

#define COREATTRIBUTE_DIRTY				0x0001
#define COREATTRIBUTE_LOCKGROUP_LOADED	0x0002
#define COREATTRIBUTE_COLL_UPTODATE		0x0004

public:
	void SetStatusFlag(status_type flags) NOTHROW { status |= flags; }
	void ResetStatusFlag(status_type flags) NOTHROW { status &= ~flags; }

	void ChangeStatusFlag(status_type flag, bool set) NOTHROW { if(set) status |= flag; else status &= ~flag; }
	bool GetStatusFlag(status_type flag) const NOTHROW { return (status & flag) != 0; }

public:
	bool InTransaction() const NOTHROW;
	bool InWriteTransaction() const NOTHROW;
	bool IsZombie() const NOTHROW;

	bool IsDirty() const NOTHROW { return GetStatusFlag(COREATTRIBUTE_DIRTY); }
	void SetDirty() NOTHROW { SetStatusFlag(COREATTRIBUTE_DIRTY); }
	void ResetDirty() NOTHROW { ResetStatusFlag(COREATTRIBUTE_DIRTY); }
	void ChangeDirty(bool dirty) { ChangeStatusFlag(COREATTRIBUTE_DIRTY, dirty); }

// ------- FinalTrItem

public:
	virtual void AbortFinalTransaction() NOTHROW { }
	virtual void CommitFinalTransaction() { }
	virtual void CommitFinalTransactionFinish(bool undo) NOTHROW { }

// ------- Storage

public:
	virtual void Load() { }
	virtual void Unload() NOTHROW { }

	virtual void FillAfterCreateObject() NOTHROW { }

// ------- Debug

#ifdef _DEBUG

public:
	virtual void Dump();
#endif
};

// --------------------------- CCoreLockAttribute

class ATL_NO_VTABLE CCoreLockAttribute :
	public CCoreAttribute
{
public:
	CCoreLockAttribute();
#ifdef _DEBUG
	virtual ~CCoreLockAttribute();
#endif

protected:
	typedef unsigned short lock_count_type;

	lock_count_type read_count;
	lock_count_type write_count;

	locking_type original_locking;	// local locking when enterging dirty state
	lockval_type others_lockval;	// original lockval minus local locking

public:
	STDMETHOD(get_Value)(VARIANT *p);
	STDMETHOD(put_Value)(VARIANT p);
	STDMETHOD(get_LoadedValue)(VARIANT *p) { return E_NOTIMPL; }
	STDMETHOD(get_PreviousValue)(VARIANT *p) { return E_NOTIMPL; }
	STDMETHOD(get_PeerLockValue)(locking_type *p);

	virtual valtype_type GetValType() const NOTHROW { return VALTYPE_LOCK; }
	virtual CCoreLockAttribute *GetLockAttr() const NOTHROW { return NULL; }

	void RegisterLockTry(locking_type unreg, locking_type reg);
	void RegisterLockDo(locking_type unreg, locking_type reg) NOTHROW;

	bool IsLoaded() const NOTHROW { return IsDirty() || read_count > 0 || write_count > 0; }
	bool IsEmpty() const NOTHROW { return read_count == 0 && write_count == 0; }

	void ControlLockGroup();
	void ControlLockGroupDo() NOTHROW;

	virtual void Load();
	virtual void Unload() NOTHROW;
	void Save();

	virtual void FillAfterCreateObject() NOTHROW;

// ------- FinalTrItem

public:
	virtual void AbortFinalTransaction() NOTHROW { Unload(); }
	virtual void CommitFinalTransaction();
	virtual void CommitFinalTransactionFinish(bool undo) NOTHROW { Unload(); }

// ------- Locking

public:
#ifdef _DEBUG
	lockval_type CalcLock(locking_type locking, lockval_type lockval);
	lockval_type CalcUnlock(locking_type locking, lockval_type lockval);
#else
	static lockval_type CalcLock(locking_type locking, lockval_type lockval);
	static lockval_type CalcUnlock(locking_type locking, lockval_type lockval);
#endif
	static locking_type CalcLocking(lockval_type lockval);
	static locking_type CombineLock(lock_count_type read_count,
		lock_count_type write_count) NOTHROW;

// ------- Debug

#ifdef _DEBUG

public:
	virtual void Dump();

#endif
};

// --------------------------- CCoreDataAttrBase

template<class DATA>
class ATL_NO_VTABLE CCoreDataAttrBase :
	public CCoreAttribute
{
// ------- Properties

public:
	typedef DATA value_type;

	typedef std::list<value_type> values_type;
	typedef typename values_type::iterator values_iterator;

protected:
	values_type values;

// ------- CopyTo

public:
	void UserCopyTo(const DATA &a, VARIANT *v) { ::CopyTo(a, v); }
	void StorageCopyTo(const DATA &a, VARIANT *v) { ::CopyTo(a, v); }

// ------- Low level

public:
	void LockSelfTry();
	void LockSelfCancel() NOTHROW;
	void UnlockSelfTry();
	void UnlockSelfCancel() NOTHROW;
	void UnlockSelfDo() NOTHROW;

// ------- Medium level

public:
	void ChangeFrontValue(VARIANT &v);
	void InsertFrontValue(VARIANT &v);

	void SpliceValue(values_iterator before, values_iterator pos) NOTHROW;

	void RemoveValueTry(values_iterator pos);
	void RemoveValueCancel(values_iterator pos) NOTHROW;
	void RemoveValueFinish(values_iterator pos) NOTHROW;
	void RemoveValue(values_iterator pos);
	void RemoveValueDo(values_iterator pos) NOTHROW;

// ------- Methods

public:
	bool IsLoaded() const NOTHROW { return !values.empty(); }

	// does not load, only compares
	static bool DoesMatchBase(const value_type &a, const VARIANT &v) NOTHROW;

// ------- Debug

#ifdef _DEBUG

public:
	virtual void Dump() { }

#endif
};

// --------------------------- CCorePointerAttrBase

class ATL_NO_VTABLE CCorePointerAttrBase :
	public CCoreAttribute
{
public:
	CCorePointerAttrBase();
#ifdef _DEBUG
	virtual ~CCorePointerAttrBase();
#endif

// ------- Properties

public:
	typedef CComObjPtr<CCoreCollectionAttribute> value_type;

	typedef std::list<value_type> values_type;
	typedef values_type::iterator values_iterator;

	typedef std::set< CCoreObject*, ptr_compare<CCoreObject> > objects_type;
	typedef objects_type::iterator objects_iterator;

protected:
	values_type values;
	objects_iterator backref;

// ------- CopyTo

public:
	void UserCopyTo(CCoreCollectionAttribute* const p, VARIANT *v);
	void UserCopyTo(const VARIANT &v, CComObjPtr<CCoreCollectionAttribute> &p);

	void StorageCopyTo(CCoreCollectionAttribute* const p, VARIANT *v);
	void StorageCopyTo(const VARIANT &v, CComObjPtr<CCoreCollectionAttribute> &p);

// ------- Low level

public:
	void InsertIntoCollection() NOTHROW;
	void RemoveFromCollection() NOTHROW;
	void CollectionNotUpToDate() NOTHROW;

	void LockCollectionTry(CCoreCollectionAttribute *p);
	void LockCollectionCancel(CCoreCollectionAttribute *p) NOTHROW;
	void UnlockCollectionTry(CCoreCollectionAttribute *p);
	void UnlockCollectionCancel(CCoreCollectionAttribute *p) NOTHROW;
	void UnlockCollectionDo(CCoreCollectionAttribute *p) NOTHROW;

	void LockSelfTry();
	void LockSelfCancel() NOTHROW;
	void UnlockSelfTry();
	void UnlockSelfCancel() NOTHROW;
	void UnlockSelfDo() NOTHROW;

// ------- Medium level

public:
	void ChangeFrontValue(VARIANT &v);
	void InsertFrontValue(VARIANT &v);

	void SpliceValue(values_iterator before, values_iterator pos) NOTHROW;

	void RemoveValueTry(values_iterator pos);
	void RemoveValueCancel(values_iterator pos) NOTHROW;
	void RemoveValueFinish(values_iterator pos) NOTHROW;
	void RemoveValue(values_iterator pos);
	void RemoveValueDo(values_iterator pos) NOTHROW;

// ------- Methods

public:
	bool IsEmpty() const NOTHROW { return INVALID_ITERATOR(backref); } // used to be: return backref == objects_iterator(NULL);
	bool IsLoaded() const NOTHROW { return !values.empty(); }

	// does not load, only compares
	static bool DoesMatchBase(const value_type &a, const VARIANT &v) NOTHROW;
};

// --------------------------- CCoreDataAttribute

template<class BASE, const int VALTYPE>
class ATL_NO_VTABLE CCoreDataAttribute : 
	public /*typename*/ BASE,//z!
	public CCoreTransactionItem,
	public CCoreUndoItem
{
public:
	typedef typename BASE::value_type value_type;

// ------- Methods

public:
	virtual valtype_type GetValType() const NOTHROW { return VALTYPE; }

	STDMETHODIMP get_Value(VARIANT *p);
	STDMETHODIMP put_Value(VARIANT p);
	STDMETHODIMP get_LoadedValue(VARIANT *p);
	STDMETHODIMP get_PreviousValue(VARIANT *p);

	const value_type &GetValue() const { ASSERT( !values.empty() ); return values.front(); }

	// if type mismatch then returns false
	virtual bool DoesMatch(bool do_load, const VARIANT &v);

// ------- Storage

public:
	virtual void Load();
	virtual void Unload() NOTHROW;
	void Save(value_type &value);

	virtual void FillAfterCreateObject() NOTHROW;

// ------- NestedTrItem

public:
	virtual bool IsDirty() const NOTHROW { return CCoreAttribute::IsDirty(); }
	virtual void ChangeDirty(bool dirty) NOTHROW { CCoreAttribute::ChangeDirty(dirty); }

	virtual void AbortNestedTransaction() NOTHROW;
	virtual void DiscardPreviousValue() NOTHROW;

// ------- FinalTrItem

public:
	virtual void AbortFinalTransaction() NOTHROW;
	virtual void CommitFinalTransaction();
	virtual void CommitFinalTransactionFinish(bool undo) NOTHROW;

// ------- UndoItem

public:
	virtual void UndoTransaction();
	virtual void UndoTransactionFinish() NOTHROW;

	virtual void RedoTransaction();
	virtual void RedoTransactionFinish() NOTHROW;

	virtual void DiscardLastItem();
	virtual void DiscardLastItemFinish() NOTHROW;
	virtual void DiscardLastItemCancel() NOTHROW;
};

// --------------------------- CCoreCollectionAttribute

class ATL_NO_VTABLE CCoreCollectionAttribute :
	public CCoreAttribute
{
#ifdef _DEBUG
public:
	~CCoreCollectionAttribute();
#endif

public:
	typedef std::set< CCoreObject*, ptr_compare<CCoreObject> > objects_type;
	typedef objects_type::iterator objects_iterator;

public:
	objects_type collection;

	objects_type &GetCollection() NOTHROW { return collection; }

	virtual valtype_type GetValType() const NOTHROW { return VALTYPE_COLLECTION; }

public:
	STDMETHOD(get_Value)(VARIANT *p);
	STDMETHOD(put_Value)(VARIANT p);
	STDMETHOD(get_LoadedValue)(VARIANT *p);
	STDMETHOD(get_PreviousValue)(VARIANT *p) { return E_NOTIMPL; }

// ------ Low level

public:
	void CopyCollectionFromMemory(VARIANT &v);
	void CopyCollectionFromStorage(VARIANT &v);
	CComObjPtr<CCoreObject> SearchCollection(attrid_type attrid, const VARIANT &value);
	bool IsEmptyFromStorage();

	inline void NotUpToDate() NOTHROW { ResetStatusFlag(COREATTRIBUTE_COLL_UPTODATE); }
};

#endif//MGA_COREATTRIBUTE_H
