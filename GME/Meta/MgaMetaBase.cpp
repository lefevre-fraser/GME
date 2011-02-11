
#include "stdafx.h"
#include "MgaMetaBase.h"
#include "MgaMetaProject.h"
#include "MgaMetaFolder.h"

// --------------------------- CMgaMetaBase

CMgaMetaBase::~CMgaMetaBase()
{
	if (metaprojectref != NULL)
		metaproject->UnregisterMetaBase(metaref, this);

#ifdef _DEBUG
	metaref = 0;
#endif
}

HRESULT CMgaMetaBase::PutMetaRef(metaref_type p)
{
	ASSERT( metaprojectref != NULL );

	if( p == metaref )
		return S_OK;

	metaproject->RegisterMetaBase(p, this);
	metaproject->UnregisterMetaBase(metaref, this);

	metaref = p;
	return S_OK;
}

void CMgaMetaBase::Traverse(CMgaMetaProject *metaproject, CCoreObjectPtr &me)
{
	ASSERT( metaprojectref != NULL );

	me.Load();
	metaref_type metaref = me.GetLongValue(ATTRID_METAREF);

	CComObjPtr<IMgaMetaBase> ibase;
	COMTHROW( ::QueryInterface(me, ibase) );
	ASSERT( ibase != NULL );

	CMgaMetaBase *base = static_cast<CMgaMetaBase*>((IMgaMetaBase*)ibase);
	ASSERT( base != NULL );

	ASSERT( base->metaproject == NULL );

	metaproject->RegisterMetaBase(metaref, base);

	base->metaprojectref = metaproject;
	base->metaref = metaref;

	TraverseCollection(metaproject, me, ATTRID_REGNODES_COLL);
	TraverseCollection(metaproject, me, ATTRID_CONSTRAINT_PTR);
}
