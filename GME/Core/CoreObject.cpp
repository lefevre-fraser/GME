
#include "stdafx.h"

#include "CoreObject.h"
#include "CoreAttribute.h"
#include "CoreProject.h"
#include "CommonCollection.h"
#include "CoreMetaProject.h"

// --------------------------- CCoreObject

CCoreObject::CCoreObject()
{
	status = 0;

#ifdef _DEBUG
	project = NULL;
	objid = OBJID_NONE;

	footprint[0] = '(';
	footprint[1] = 'C';
	footprint[2] = 'O';
	footprint[3] = ')';
#endif
}

CComObjPtr<CCoreObject> CCoreObject::Create(CCoreProject *project, metaid_type metaid, objid_type objid)
{
	ASSERT( project != NULL );
	ASSERT( metaid != METAID_NONE );
	ASSERT( objid != OBJID_NONE );

	CCoreMetaObject *metaobject;
	metaobject = project->GetMetaProject()->GetObject(metaid);
	if( metaobject == NULL )
		HR_THROW(E_NOTFOUND);

	CComObjPtr<CCoreObject> object;
	CreateComObject(object);

	// nothing will throw here
	object->project = project;
	object->objid = objid;
	object->metaobject = metaobject;

	project->RegisterObject(metaid, objid, object);
	// the object is ready for deletion

	object->CreateAttributes();
	object->CreateAggregates();

	return object;
}

CCoreObject::~CCoreObject()
{
	ASSERT( (objid == OBJID_NONE && project == NULL && metaobject == NULL ) ||
		(objid != OBJID_NONE && project != NULL && metaobject != NULL) );

	// If this assertion fails, then we have killed the CCoreObject already.
	// Probably the reference count on this is wrong.

	// first kill the aggregated components
	aggregates.clear();

	// the attribute will remove itself from the list
	while( !attributes.empty() )
		delete attributes.front();

	if( project != NULL )
		project->UnregisterObject(GetMetaID(), objid);

#ifdef _DEBUG
	project = NULL;
	objid = OBJID_NONE;
#endif
}

HRESULT CCoreObject::AggregatedInterfaceLookup(void *pvThis, REFIID riid, LPVOID *ppv, DWORD dw)
{
	ASSERT( ppv != NULL && *ppv == NULL );
	ASSERT( dw == 0 );

	HRESULT hr = E_NOINTERFACE;

	aggregates_type &aggregates = ((CCoreObject*)pvThis)->aggregates;
	ASSERT( aggregates.size() >= 0 );

	aggregates_iterator i = aggregates.begin();
	aggregates_iterator e = aggregates.end();
	while( i != e && hr == E_NOINTERFACE )
	{
		ASSERT( *i != NULL );
		hr = (*i)->QueryInterface(riid, ppv);

		++i;
	}

	return hr;
}

// ------- COM methods

STDMETHODIMP CCoreObject::get_Project(ICoreProject **p)
{
	CHECK_OUT(p);

	if( IsZombie() )
		COMRETURN(E_ZOMBIE);

	ASSERT( project != NULL );
	CopyTo(project, p);
	return S_OK;
}

STDMETHODIMP CCoreObject::get_MetaObject(ICoreMetaObject **p)
{
	CHECK_OUT(p);

	ASSERT( metaobject != NULL );
	CopyTo(metaobject, p);
	return S_OK;
}

STDMETHODIMP CCoreObject::get_ObjID(objid_type *p)
{
	CHECK_OUT(p);

	if( IsZombie() )
		COMRETURN(E_ZOMBIE);

	ASSERT( objid != 0 );
	*p = objid;
	return S_OK;
}

STDMETHODIMP CCoreObject::get_Attribute(attrid_type attrid, ICoreAttribute **p)
{
	CHECK_OUT(p);

	if( attrid == ATTRID_NONE )
		return E_INVALIDARG;

	if( IsZombie() )
		COMRETURN(E_ZOMBIE);

	CCoreAttribute *attribute = FindAttribute(attrid);
	if( attribute == NULL )
		return E_INVALIDARG;

	CopyTo(attribute, p);
	return S_OK;
}

STDMETHODIMP CCoreObject::get_Attributes(ICoreAttributes **p)
{
	CHECK_OUT(p);

	COMTRY
	{
		typedef CCoreCollection<ICoreAttributes, std::vector<ICoreAttribute*>,
			ICoreAttribute, CCoreAttribute> COMTYPE;

		CComObjPtr<COMTYPE> q;
		CreateComObject(q);

		q->Fill(attributes.begin(), attributes.end());
		MoveTo(q,p);
	}
	COMCATCH(;)
}

STDMETHODIMP CCoreObject::get_AttributeValue(attrid_type attrid, VARIANT *p)
{
	CHECK_OUT(p);

	if( IsZombie() )
		COMRETURN(E_ZOMBIE);

	CCoreAttribute *attribute = FindAttribute(attrid);
	if( attribute == NULL )
		return E_INVALIDARG;

	return attribute->get_Value(p);
}

STDMETHODIMP CCoreObject::put_AttributeValue(attrid_type attrid, VARIANT p)
{
	if( IsZombie() )
		COMRETURN(E_ZOMBIE);

	CCoreAttribute *attribute = FindAttribute(attrid);
	if( attribute == NULL )
		return E_INVALIDARG;

	return attribute->put_Value(p);
}

STDMETHODIMP CCoreObject::get_LoadedAttrValue(attrid_type attrid, VARIANT *p)
{
	CHECK_OUT(p);

	if( IsZombie() )
		COMRETURN(E_ZOMBIE);

	CCoreAttribute *attribute = FindAttribute(attrid);
	if( attribute == NULL )
		return E_INVALIDARG;

	return attribute->get_LoadedValue(p);
}

STDMETHODIMP CCoreObject::get_PreviousAttrValue(attrid_type attrid, VARIANT *p)
{
	CHECK_OUT(p);

	if( IsZombie() )
		COMRETURN(E_ZOMBIE);

	CCoreAttribute *attribute = FindAttribute(attrid);
	if( attribute == NULL )
		return E_INVALIDARG;

	return attribute->get_PreviousValue(p);
}

STDMETHODIMP CCoreObject::get_PeerLockValue(attrid_type attrid, locking_type *p)
{
	CHECK_OUT(p);

	if( IsZombie() )
		COMRETURN(E_ZOMBIE);

	CCoreAttribute *attribute = FindAttribute(attrid);
	if( attribute == NULL || attribute->GetValType() != VALTYPE_LOCK )
		return E_INVALIDARG;

	return ((CCoreLockAttribute*)attribute)->get_PeerLockValue(p);
}

STDMETHODIMP CCoreObject::SearchCollection(attrid_type coll_attrid, attrid_type search_attrid,
	VARIANT search_value, ICoreObject **p)
{
	CHECK_OUT(p);

	if( IsZombie() )
		COMRETURN(E_ZOMBIE);

	CCoreAttribute *attribute = FindAttribute(coll_attrid);
	if( attribute == NULL || attribute->GetValType() != VALTYPE_COLLECTION )
		return E_INVALIDARG;

	COMTRY
	{
		CCoreCollectionAttribute *collection = 
			static_cast<CCoreCollectionAttribute*>(attribute);
		
		CComObjPtr<CCoreObject> ret = collection->SearchCollection(search_attrid, search_value);
		MoveTo(ret, p);
	}
	COMCATCH(;)
}

STDMETHODIMP CCoreObject::get_IsDeleted(VARIANT_BOOL *p)
{
	CHECK_OUT(p);

	if( IsZombie() )
		COMRETURN(E_ZOMBIE);

	*p = VARIANT_FALSE;

	COMTRY
	{
		CCoreAttribute *lock = FindAttribute(ATTRID_LOCK);
		ASSERT( lock != NULL && lock->GetValType() == VALTYPE_LOCK );
		
		if( static_cast<CCoreLockAttribute*>(lock)->IsLoaded() &&
			HasEmptyPointers() && 
			(objid != OBJID_ROOT || GetMetaID() != METAID_ROOT) )
		{
			*p = VARIANT_TRUE;
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CCoreObject::Delete()
{
	if( IsZombie() )
		COMRETURN(E_ZOMBIE);

	COMTRY
	{
		CCoreAttribute *lock = FindAttribute(ATTRID_LOCK);
		ASSERT( lock != NULL && lock->GetValType() == VALTYPE_LOCK );

		COMTHROW( lock->put_Value(PutInVariant(locking_type(LOCKING_EXCLUSIVE))) );

		attributes_iterator i = attributes.begin();
		attributes_iterator e = attributes.end();
		while( i != e )
		{
			if( (*i)->GetValType() == VALTYPE_COLLECTION )
			{
				if( !((CCoreCollectionAttribute*)(*i))->IsEmptyFromStorage() )
					HR_THROW(E_NONEMPTY_COLL);
			}

			++i;
		}

		i = attributes.begin();
		while( i != e )
		{
			if( (*i)->GetValType() == VALTYPE_POINTER )
				COMTHROW( (*i)->put_Value(PutInVariant((IDispatch*)NULL)) );

			++i;
		}

		COMTHROW( lock->put_Value(PutInVariant(locking_type(LOCKING_NONE))) );
	}
	COMCATCH(;)
}

STDMETHODIMP CCoreObject::Clone(ICoreObject **p)
{
	return E_NOTIMPL;
}

// ------- Creation 

void CCoreObject::CreateAttributes()
{
	ASSERT( attributes.empty() );

	typedef CCoreMetaObject::attributes_type metaattributes_type;
	
	ASSERT( metaobject != NULL );
	const metaattributes_type &metaattributes = metaobject->GetAttributes();

	metaattributes_type::const_iterator i = metaattributes.begin();
	metaattributes_type::const_iterator e = metaattributes.end();
	while( i != e )
	{
		CCoreAttribute::Create(this, *i);

		++i;
	}
}

void CCoreObject::CreateAggregates()
{
	CComSafeArray p;
	COMTHROW( metaobject->get_ClassIDs(PutOut(p)) );
	ASSERT( p != NULL );

	const std::vector<GUID> &classids = metaobject->GetClassIDs();

	std::vector<GUID>::const_iterator i = classids.begin();
	std::vector<GUID>::const_iterator e = classids.end();
	while( i != e )
	{
		CComObjPtr<IUnknown> aggregated;

		COMTHROW( CoCreateInstance(*i, CastToUnknown(this), CLSCTX_ALL, IID_IUnknown, 
			(void**)PutOut(aggregated)) );
		ASSERT( aggregated != NULL );

		aggregates.push_front();
		MoveTo(aggregated, aggregates.front());

		++i;
	}
}

void CCoreObject::FillAfterCreateObject()
{
	ASSERT( !attributes.empty() );

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		(*i)->FillAfterCreateObject();
		++i;
	}

	RegisterFinalTrItem();
}

// ------- Methods

CCoreAttribute *CCoreObject::FindAttribute(attrid_type attrid) const
{
	attributes_type::const_iterator i = attributes.begin();
	attributes_type::const_iterator e = attributes.end();
	while( i != e )
	{
		if( (*i)->GetAttrID() == attrid )
		{
			ASSERT( attrid != ATTRID_NONE );
			return *i;
		}

		++i;
	}

	return NULL;
}

void CCoreObject::RegisterAttribute(CCoreAttribute *attribute)
{
	ASSERT( attribute != NULL );
#ifdef DEBUG_CONTAINERS
	ASSERT( find(attributes.begin(), attributes.end(), attribute) == attributes.end() );
	ASSERT( FindAttribute(attribute->GetAttrID()) == NULL );
#endif

	attributes.push_front(attribute);
}

void CCoreObject::UnregisterAttribute(CCoreAttribute *attribute)
{
	ASSERT( attribute != NULL );
	ASSERT( FindAttribute(attribute->GetAttrID()) != NULL );

	attributes_iterator i = std::find(attributes.begin(), attributes.end(), attribute);
	ASSERT( i != attributes.end() );

	attributes.erase(i);
}

void CCoreObject::GetAttributes(CCoreLockAttribute *lockattribute, 
	std::list<CCoreAttribute*> &controlled)
{
	ASSERT( lockattribute != NULL );
	ASSERT( controlled.empty() );

#ifdef _DEBUG
	attrid_type attrid = lockattribute->GetAttrID();
#endif

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{

#ifdef _DEBUG
		attrid_type lockattrid = ATTRID_NONE;
		ASSERT( (*i)->GetMetaAttribute()->get_LockAttrID(&lockattrid) == S_OK );
#endif

		if( (*i)->GetLockAttr() == lockattribute )
		{
			ASSERT( lockattrid == attrid );
			controlled.push_back( *i );
		}

		++i;
	}
}

void CCoreObject::LoadAttributes(CCoreLockAttribute *lockattribute)
{
	ASSERT( lockattribute != NULL );


	std::list<CCoreAttribute*> controlled;
	GetAttributes(lockattribute, controlled);

	attributes_iterator i = controlled.begin();
	attributes_iterator e = controlled.end();

	try
	{
		while( i != e )
		{
			(*i)->Load();

			++i;
		}
	}
	catch(hresult_exception &)
	{
		e = i;
		i = controlled.begin();
		while( i != e )
		{
			(*i)->Unload();

			++i;
		}

		throw;
	}
}

void CCoreObject::UnloadAttributes(CCoreLockAttribute *lockattribute)
{
	ASSERT( lockattribute != NULL );

	std::list<CCoreAttribute*> controlled;
	GetAttributes(lockattribute, controlled);

	attributes_iterator i = controlled.begin();
	attributes_iterator e = controlled.end();
	while( i != e )
	{
		(*i)->Unload();

		++i;
	}
}

// ------- Status

bool CCoreObject::InTransaction() const
{
	ASSERT( !IsZombie() );
	ASSERT( project != NULL );

	return project->InTransaction();
}

bool CCoreObject::InWriteTransaction() const
{
	ASSERT( !IsZombie() );
	ASSERT( project != NULL );

	return project->InWriteTransaction();
}

void CCoreObject::SetZombie()
{
	ASSERT( project != NULL );

	// we do not unregister, the object_lookup is cleared

	project = NULL;
	metaobject = NULL;
}

bool CCoreObject::HasEmptyPointers() const
{
	ASSERT( project != NULL );
	
	attributes_type::const_iterator i = attributes.begin();
	attributes_type::const_iterator e = attributes.end();
	while( i != e )
	{
		if( (*i)->GetValType() == VALTYPE_POINTER )
		{
			if( !((CCorePointerAttrBase*)(*i))->IsEmpty() )
				return false;
		}

		++i;
	}

	return true;
}

bool CCoreObject::HasEmptyPointersAndLocks() const
{
	ASSERT( project != NULL );
	
	attributes_type::const_iterator i = attributes.begin();
	attributes_type::const_iterator e = attributes.end();
	while( i != e )
	{
		valtype_type valtype = (*i)->GetValType();

		if( valtype == VALTYPE_LOCK )
		{
			if( !((CCoreLockAttribute*)(*i))->IsEmpty() )
				return false;
		}
		else if( valtype == VALTYPE_POINTER )
		{
			if( !((CCorePointerAttrBase*)(*i))->IsEmpty() )
				return false;
		}

		++i;
	}

	return true;
}

// ------- Debug

#ifdef _DEBUG

void CCoreObject::Dump()
{
	ASSERT( metaobject != NULL );

	CComBstrObj metabstr;
	COMTHROW( metaobject->get_Name(PutOut(metabstr)) );

	std::string metaname;
	CopyTo(metabstr, metaname);

	AtlTrace("object_dump metaid=%d metaname=\"%s\" objid=%d, #attrs: %d\n",
		(int)GetMetaID(), metaname.begin(), (int)objid, attributes.size());

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		(*i)->Dump();

		++i;
	}
}

#endif

// ------- FinalTrItem

void CCoreObject::RegisterFinalTrItem()
{
	ASSERT( project );

	if( !IsDirty() )
	{
		project->RegisterFinalTrItem(this);
		SetDirty();
	}
}

void CCoreObject::AbortFinalTransaction()
{
	ASSERT( IsDirty() );

	// keep this object alive
	CComObjPtr<ICoreObject> self(this);

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		if( (*i)->IsDirty() )
		{
			(*i)->AbortFinalTransaction();
			ASSERT( !(*i)->IsDirty() );
		}

		++i;
	}

	ResetDirty();
}

void CCoreObject::CommitFinalTransaction()
{
	ASSERT( IsDirty() );

	if( HasEmptyPointersAndLocks() && (objid != OBJID_ROOT || GetMetaID() != METAID_ROOT) )
	{
		ASSERT( project != NULL );
		ICoreStorage *storage = project->SetStorageObject(this);
		ASSERT( storage != NULL );

		COMTHROW( storage->DeleteObject() );
	}
	else
	{
		attributes_iterator i = attributes.begin();
		attributes_iterator e = attributes.end();
		while( i != e )
		{
			if( (*i)->IsDirty() )
			{
				(*i)->CommitFinalTransaction();
				ASSERT( (*i)->IsDirty() );
			}

			++i;
		}
	}
}

void CCoreObject::CommitFinalTransactionFinish(bool undo)
{
	ASSERT( IsDirty() );

	// keep this object alive
	CComObjPtr<ICoreObject> self(this);

	attributes_iterator i = attributes.begin();
	attributes_iterator e = attributes.end();
	while( i != e )
	{
		if( (*i)->IsDirty() )
		{
			(*i)->CommitFinalTransactionFinish(undo);
			ASSERT( !(*i)->IsDirty() );
		}

		++i;
	}

	ResetDirty();
}

