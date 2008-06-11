
#include "stdafx.h"
#include "MgaMetaBase.h"
#include "MgaMetaProject.h"
#include "MgaMetaFolder.h"

// --------------------------- CMgaMetaBase

CMgaMetaBase::~CMgaMetaBase()
{
	if( metaproject != NULL )
		metaproject->UnregisterMetaBase(metaref, this);

#ifdef _DEBUG
	metaproject = NULL;
	metaref = 0;
#endif
}

HRESULT CMgaMetaBase::PutMetaRef(metaref_type p)
{
	ASSERT( metaproject != NULL );

	if( p == metaref )
		return S_OK;

	metaproject->RegisterMetaBase(p, this);
	metaproject->UnregisterMetaBase(metaref, this);

	metaref = p;
	return S_OK;
}

void CMgaMetaBase::Traverse(CMgaMetaProject *metaproject, CCoreObjectPtr &me)
{
	ASSERT( metaproject != NULL );

	me.Load();
	metaref_type metaref = me.GetLongValue(ATTRID_METAREF);

	CComObjPtr<IMgaMetaBase> ibase;
	COMTHROW( ::QueryInterface(me, ibase) );
	ASSERT( ibase != NULL );

	CMgaMetaBase *base = static_cast<CMgaMetaBase*>((IMgaMetaBase*)ibase);
	ASSERT( base != NULL );

	ASSERT( base->metaproject == NULL );

	metaproject->RegisterMetaBase(metaref, base);

	base->metaproject = metaproject;
	base->metaref = metaref;

	TraverseCollection(metaproject, me, ATTRID_REGNODES_COLL);
	TraverseCollection(metaproject, me, ATTRID_CONSTRAINT_PTR);
}
