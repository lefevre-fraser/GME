
#ifndef MGA_CORETERRITORY_H
#define MGA_CORETERRITORY_H

#ifndef MGA_CORETRANSACTIONITEM_H
#include "CoreTransactionItem.h"
#endif

#include <list>
#include <hash_map>

class CCoreProject;
class CCoreLockAttribute;

// --------------------------- typedefs

typedef stdext::hash_map< CComObjPtr<CCoreLockAttribute>
                        , locking_type
                        , ptr_compare<CCoreLockAttribute> 
                        > lockmap_type;
typedef lockmap_type::iterator lockmap_iterator;

typedef std::list<lockmap_type> lockmaps_type;
typedef lockmaps_type::iterator lockmaps_iterator;

// --------------------------- CCoreTerritory

class ATL_NO_VTABLE CCoreTerritory : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ICoreTerritory, &IID_ICoreTerritory, &LIBID_MGACoreLib>,
	public ISupportErrorInfoImpl<&IID_ICoreTerritory>,
	public CCoreTransactionItem,
	public CCoreFinalTrItem
{
public:
	CCoreTerritory();
	virtual ~CCoreTerritory();

	static CCoreTerritory *Create(CCoreProject *project);

BEGIN_COM_MAP(CCoreTerritory)
	COM_INTERFACE_ENTRY(ICoreTerritory)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// ------- Attributes

protected:
	CComObjPtr<CCoreProject> project;
	lockmaps_type lockmaps;

	typedef unsigned char status_type;
	status_type status;

// ------- COM methods

public:
	STDMETHODIMP get_Project(ICoreProject **p);
	STDMETHODIMP get_Attributes(ICoreAttributes **p);
	STDMETHODIMP Clear();

// ------- Methods

public:
	CCoreProject *GetProject() const { return project; }

	locking_type GetLocking(CCoreLockAttribute *attribute) const NOTHROW;
	void SetLockingCore(CCoreLockAttribute *attribute, locking_type old_locking, locking_type locking);
	void SetLocking(CCoreLockAttribute *attribute, locking_type locking);
	void RaiseLocking(CCoreLockAttribute *attribute, locking_type locking);

// ------- Status

#define CORETERRITORY_DIRTY				0x0001
#define CORETERRITORY_FINAL				0x0002

public:
	void SetStatusFlag(status_type flags) { status |= flags; }
	void ResetStatusFlag(status_type flags) { status &= ~flags; }

	void ChangeStatusFlag(status_type flag, bool set) { if(set) status |= flag; else status &= ~flag; }
	bool GetStatusFlag(status_type flag) const { return (status & flag) != 0; }

public:
	bool InTransaction() const;

// ------- NestedTrItem

public:
	virtual bool IsDirty() const NOTHROW { return GetStatusFlag(CORETERRITORY_DIRTY); }
	virtual void ChangeDirty(bool dirty) NOTHROW { ChangeStatusFlag(CORETERRITORY_DIRTY, dirty); }

	virtual void AbortNestedTransaction() NOTHROW;
	virtual void DiscardPreviousValue() NOTHROW;

// ------- FinalTrItem

public:
	virtual void AbortFinalTransaction() NOTHROW;
	virtual void CommitFinalTransaction();
	virtual void CommitFinalTransactionFinish(bool undo) NOTHROW;
};

inline IUnknown *CastToUnknown(CCoreTerritory *p) { return (IUnknown*)(ICoreTerritory*)p; }
inline CCoreTerritory *CastToTerritory(IUnknown *p) { return (CCoreTerritory*)(ICoreTerritory*)p; }

#endif//MGA_CORETERRITORY_H

