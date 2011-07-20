
#include "stdafx.h"

#include "CoreTerritory.h"
#include "CoreProject.h"
#include "CoreAttribute.h"
#include "CommonCollection.h"

#include <hash_set>

// --------------------------- CCoreTerritory

CCoreTerritory::CCoreTerritory()
{
	status = 0;
	lockmaps.push_front( lockmap_type());
}

CCoreTerritory *CCoreTerritory::Create(CCoreProject *project)
{
	CCoreTerritory *territory = NULL;

	typedef CComObject< CCoreTerritory > COMTYPE;
	COMTHROW( COMTYPE::CreateInstance((COMTYPE **)&territory) );
	ASSERT( territory != NULL );

	territory->project = project;
	project->RegisterTerritory(territory);

	return territory;
}

CCoreTerritory::~CCoreTerritory()
{
	ASSERT( project != NULL );

	ASSERT( lockmaps.size() == 1 );
	ASSERT( lockmaps.front().empty() );

	project->UnregisterTerritory(this);

#ifdef _DEBUG
	project = NULL;
#endif
}

// ------- COM methods

STDMETHODIMP CCoreTerritory::get_Project(ICoreProject **p)
{
	CHECK_OUT(p);

	ASSERT( project != NULL );
	CopyTo(project, p);
	return S_OK;
}

STDMETHODIMP CCoreTerritory::get_Attributes(ICoreAttributes **p)
{
	CHECK_OUT(p);

	ASSERT( project != NULL );

	COMTRY
	{
		typedef CCoreCollection<ICoreAttributes, std::vector<ICoreAttribute*>,
			ICoreAttribute, CCoreLockAttribute> COMTYPE;

		CComObjPtr<COMTYPE> q;
		CreateComObject(q);

		typedef stdext::hash_set< CCoreLockAttribute*
		                        , ptr_compare<CCoreLockAttribute>
		                        > join_type;

		join_type join;

		lockmaps_type::reverse_iterator i = lockmaps.rbegin();
		lockmaps_type::reverse_iterator e = lockmaps.rend();
		while( !(i == e) )
		{
			lockmap_iterator j = (*i).begin();
			lockmap_iterator f = (*i).end();
			while( j != f )
			{
				ASSERT( (*j).first != NULL );
				ASSERT( LOCKING_NONE <= (*j).second && (*j).second <= LOCKING_EXCLUSIVE );

				if( (*j).second <= LOCKING_NONE )
					join.erase( (*j).first );
				else
					join.insert( (*j).first );

				++j;
			}

			++i;
		}

		q->Fill(join.begin(), join.end());
		MoveTo(q, p);
	}
	COMCATCH(;)
}

STDMETHODIMP CCoreTerritory::Clear()
{
	ASSERT( project != NULL );

	COMTRY
	{
		typedef stdext::hash_set< CCoreLockAttribute*
		                        , ptr_compare<CCoreLockAttribute>
		                        > join_type;

		join_type join;

		lockmaps_type::reverse_iterator i = lockmaps.rbegin();
		lockmaps_type::reverse_iterator e = lockmaps.rend();
		while( !(i == e) )
		{
			lockmap_iterator j = (*i).begin();
			lockmap_iterator f = (*i).end();
			while( j != f )
			{
				ASSERT( (*j).first != NULL );
				ASSERT( LOCKING_NONE <= (*j).second && (*j).second <= LOCKING_EXCLUSIVE );

				if( (*j).second <= LOCKING_NONE )
					join.erase( (*j).first );
				else
					join.insert( (*j).first );

				++j;
			}

			++i;
		}

		HRESULT hr = project->BeginTransaction(TRANSTYPE_READANY);
		if (FAILED(hr))
			COMRETURN(hr);

		try
		{
			join_type::iterator i = join.begin();
			join_type::iterator e = join.end();
			while( i != e )
			{
				SetLocking( *i, LOCKING_NONE );

				++i;
			}

			COMTHROW( project->CommitTransaction(TRANSTYPE_READANY) );
		}
		catch(hresult_exception &)
		{
			project->AbortTransaction(TRANSTYPE_READANY);

			throw;
		}
	}
	COMCATCH(;)
}

// ------- Methods

locking_type CCoreTerritory::GetLocking(CCoreLockAttribute *attribute) const
{
	ASSERT( project != NULL );
	ASSERT( attribute != NULL );
	ASSERT( !lockmaps.empty() );

	lockmaps_type::const_iterator i = lockmaps.begin();
	lockmaps_type::const_iterator e = lockmaps.end();
	while( i != e )
	{
		lockmap_type::const_iterator j = (*i).find(attribute);
		if( j != (*i).end() )
		{
			ASSERT( LOCKING_NONE <= (*j).second && (*j).second <= LOCKING_EXCLUSIVE );
			return (*j).second;
		}

		++i;
	}

	return LOCKING_NONE;
}

void CCoreTerritory::SetLockingCore(CCoreLockAttribute *attribute,
	locking_type old_locking, locking_type locking)
{
	ASSERT( old_locking != locking );

	if( !IsDirty() )
	{
		if( !GetStatusFlag(CORETERRITORY_FINAL) )
		{
			ASSERT( lockmaps.size() == 1 );

			project->RegisterFinalTrItem(this);

			if( lockmaps.front().empty() )
				AddRef();

			SetStatusFlag(CORETERRITORY_FINAL);
		}

		lockmaps.push_front(lockmap_type());

		project->RegisterTransactionItem(this);
		SetStatusFlag(CORETERRITORY_DIRTY);
	}

	attribute->RegisterLockTry( old_locking, locking );
	lockmaps.front()[ attribute ] = locking;
}

void CCoreTerritory::SetLocking(CCoreLockAttribute *attribute, locking_type locking)
{
	ASSERT( attribute != NULL );
	ASSERT( LOCKING_NONE <= locking && locking <= LOCKING_EXCLUSIVE );

	ASSERT( project );
	ASSERT( InTransaction() );
	ASSERT( !lockmaps.empty() );

	locking_type old_locking = GetLocking(attribute);
	if( old_locking != locking )
		SetLockingCore(attribute, old_locking, locking);
}

void CCoreTerritory::RaiseLocking(CCoreLockAttribute *attribute, locking_type locking)
{
	ASSERT( attribute != NULL );
	ASSERT( LOCKING_NONE < locking && locking <= LOCKING_EXCLUSIVE );

	ASSERT( project );
	ASSERT( InTransaction() );
	ASSERT( !lockmaps.empty() );

	locking_type old_locking = GetLocking(attribute);
	locking |= old_locking;

	if( old_locking != locking )
		SetLockingCore(attribute, old_locking, locking);
}

// ------- TransactionItem

void CCoreTerritory::AbortNestedTransaction()
{
	ASSERT( lockmaps.size() >= 2 );
	ASSERT( IsDirty() );

	lockmaps_type temp;
	temp.splice(temp.end(), lockmaps, lockmaps.begin());

	lockmap_iterator i = temp.front().begin();
	lockmap_iterator e = temp.front().end();
	while( i != e )
	{
		ASSERT( (*i).first != NULL );
		ASSERT( LOCKING_NONE <= (*i).second && (*i).second <= LOCKING_EXCLUSIVE );

		locking_type old_locking = GetLocking( (*i).first );
		(*i).first->RegisterLockDo( (*i).second, old_locking );

		++i;
	}

	ResetStatusFlag(CORETERRITORY_DIRTY);
}

void CCoreTerritory::DiscardPreviousValue()
{
	ASSERT( lockmaps.size() >= 3 );
	ASSERT( IsDirty() );

	lockmaps_type temp;
	temp.splice(temp.end(), lockmaps, lockmaps.begin(), ++(++lockmaps.begin()));
	ASSERT( temp.size() == 2 );

	lockmap_type &current = temp.front();

	lockmap_iterator i = temp.back().begin();
	lockmap_iterator e = temp.back().end();
	while( i != e )
	{
		ASSERT( (*i).first != NULL );
		ASSERT( LOCKING_NONE <= (*i).second && (*i).second <= LOCKING_EXCLUSIVE );

		if( current.find( (*i).first ) == current.end() )
		{
			locking_type old_locking = GetLocking( (*i).first );
			(*i).first->RegisterLockDo( (*i).second, old_locking );
		}

		++i;
	}

	lockmaps.splice(lockmaps.begin(), temp, temp.begin());
}

// ------- FinalTrItem

void CCoreTerritory::AbortFinalTransaction()
{
	ASSERT( GetStatusFlag(CORETERRITORY_FINAL) );

	if( IsDirty() )
	{
		ASSERT( lockmaps.size() == 2 );

		// we have to update the lock attribute's read and write lock counts
		// the actual lockvalue will be loaded again from the database

		lockmaps_type temp;
		temp.splice(temp.end(), lockmaps, lockmaps.begin());

		lockmap_iterator i = temp.front().begin();
		lockmap_iterator e = temp.front().end();
		while( i != e )
		{
			ASSERT( (*i).first != NULL );
			ASSERT( LOCKING_NONE <= (*i).second && (*i).second <= LOCKING_EXCLUSIVE );

			locking_type old_locking = GetLocking( (*i).first );
			(*i).first->RegisterLockDo( (*i).second, old_locking );

			++i;
		}

		ResetStatusFlag(CORETERRITORY_DIRTY);
	}
	ASSERT( lockmaps.size() == 1 );

	ResetStatusFlag(CORETERRITORY_FINAL);

	if( lockmaps.front().empty() )
		Release();
}

void CCoreTerritory::CommitFinalTransaction()
{
	ASSERT( GetStatusFlag(CORETERRITORY_FINAL) );
	ASSERT( (IsDirty() && lockmaps.size() == 2) || (!IsDirty() && lockmaps.size() == 1) );
}

void CCoreTerritory::CommitFinalTransactionFinish(bool undo)
{
	ASSERT( GetStatusFlag(CORETERRITORY_FINAL) );

	if( IsDirty() )
	{
		ASSERT( lockmaps.size() == 2 );

		lockmap_type &collected = lockmaps.back();

		lockmap_iterator i = lockmaps.front().begin();
		lockmap_iterator e = lockmaps.front().end();
		while( i != e )
		{
			ASSERT( (*i).first != NULL );
			ASSERT( LOCKING_NONE <= (*i).second && (*i).second <= LOCKING_EXCLUSIVE );

			if( (*i).second > LOCKING_NONE )
				collected[ (*i).first ] = (*i).second;
			else
				collected.erase( (*i).first );

			++i;
		}

		ResetStatusFlag(CORETERRITORY_DIRTY);
		lockmaps.pop_front();
	}
	ASSERT( lockmaps.size() == 1 );

	ResetStatusFlag(CORETERRITORY_FINAL);

	if( lockmaps.front().empty() )
		Release();
}

// ------- Status

bool CCoreTerritory::InTransaction() const
{
	ASSERT( project != NULL );

	return project->InTransaction();
}
