
#include "stdafx.h"
#include "MgaMetaProject.h"
#include "MgaMetaFolder.h"
#include <time.h>

// ------- CurrentTime

CComVariant CurrentTime(void) 
{
	time_t t;
	time(&t);
	char *p = ctime(&t);
	ASSERT( p != NULL );

	p[strlen(p)-1] = 0;
	return p;
}

// --------------------------- CMgaMetaProject

CMgaMetaProject::CMgaMetaProject()
{
	max_metaref = 1000;
}

CMgaMetaProject::~CMgaMetaProject()
{
	if( coreproject != NULL )
	{
		ASSERT( coreterritory != NULL );

		// If this assertion fails then we have killed the CMgaMetaProject
		// while working in the Close method. Probably the reference
		// count on this object is wrong.

		ASSERT( rootobject != NULL );
		ASSERT( !metaobj_lookup.empty() );

		Close();
	}

	ASSERT( coreproject == NULL );
	ASSERT( coreterritory == NULL );
	ASSERT( rootobject == NULL );
	ASSERT( metaobj_lookup.empty() );
}
	
// ------- Methods

STDMETHODIMP CMgaMetaProject::Open(BSTR connection)
{
	COMTRY
	{
		if( coreproject != NULL )
			COMTHROW( Close() );

		CComPtr<ICoreMetaProject> coremetaproject;
		CreateCoreMetaProject(coremetaproject);

		COMTHROW( coreproject.CoCreateInstance(OLESTR("MGA.CoreProject")) );
		ASSERT( coreproject != NULL );

		COMTHROW( coreproject->OpenProject(connection, coremetaproject) );

		COMTHROW( coreproject->CreateTerritory(PutOut(coreterritory)) );
		ASSERT( coreterritory != NULL );

		COMTHROW( coreproject->BeginTransaction(TRANSTYPE_READFIRST) );
		COMTHROW( coreproject->PushTerritory(coreterritory) );

		COMTHROW( coreproject->get_RootObject(PutOut(rootobject)) );

		CMgaMetaFolder::Traverse(this, rootobject);

		COMTHROW( coreproject->CommitTransaction(TRANSTYPE_READFIRST) );
	}
	COMCATCH(
		metaobj_lookup.clear();
		rootobject = NULL;
		coreterritory = NULL;
		coreproject = NULL;
	)
}

STDMETHODIMP CMgaMetaProject::Create(BSTR connection)
{
	COMTRY
	{
		if( coreproject != NULL )
			COMTHROW( Close() );

		CComPtr<ICoreMetaProject> coremetaproject;
		CreateCoreMetaProject(coremetaproject);

		COMTHROW( coreproject.CoCreateInstance(OLESTR("MGA.CoreProject")) );
		ASSERT( coreproject != NULL );

		COMTHROW( coreproject->CreateProject(connection, coremetaproject) );

		COMTHROW( coreproject->CreateTerritory(PutOut(coreterritory)) );
		ASSERT( coreterritory != NULL );

		COMTHROW( coreproject->BeginTransaction(TRANSTYPE_FIRST) );
		COMTHROW( coreproject->PushTerritory(coreterritory) );

		COMTHROW( coreproject->get_RootObject(PutOut(rootobject)) );
		COMTHROW( rootobject->put_AttributeValue(ATTRID_CDATE, CurrentTime()) );
		COMTHROW( rootobject->put_AttributeValue(ATTRID_MDATE, CurrentTime()) );
		COMTHROW( rootobject->put_AttributeValue(ATTRID_NAME, CComVariant()) );
		COMTHROW( rootobject->put_AttributeValue(ATTRID_METAREF, PutInVariant(max_metaref)) );

		COMTHROW( coreterritory->Clear() );

		CMgaMetaFolder::Traverse(this, rootobject);

		COMTHROW( coreproject->CommitTransaction(TRANSTYPE_FIRST) );
	}
	COMCATCH(
		metaobj_lookup.clear();
		rootobject = NULL;
		coreterritory = NULL;
		coreproject = NULL;
	)
}

STDMETHODIMP CMgaMetaProject::BeginTransaction()
{
	if( coreproject == NULL )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{
		COMTHROW( coreproject->BeginTransaction(TRANSTYPE_FIRST) );

		ASSERT( coreterritory != NULL );
		COMTHROW( coreproject->PushTerritory(coreterritory) );
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaMetaProject::CommitTransaction()
{
	if( coreproject == NULL )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{
		COMTHROW( rootobject->put_AttributeValue(ATTRID_MDATE, CurrentTime()) );
		COMTHROW( coreproject->CommitTransaction(TRANSTYPE_FIRST) );
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaMetaProject::AbortTransaction()
{
	if( coreproject == NULL )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{
		COMTHROW( coreproject->AbortTransaction(TRANSTYPE_FIRST) );
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaMetaProject::Close()
{
	COMTRY
	{
		if( coreproject != NULL )
		{
			rootobject = NULL;

			short count = 0;
			COMTHROW( coreproject->get_NestedTransactionCount(&count) );

			if( count == 1 )
				COMTHROW( coreproject->AbortTransaction(TRANSTYPE_ANY) );

			if( coreterritory != NULL )
			{
				COMTHROW( coreterritory->Clear() );
				coreterritory = NULL;
			}

			COMTHROW( coreproject->CloseProject() );
			coreproject = NULL;

			metaobj_lookup.clear();
			max_metaref = 1000;
		}

		ASSERT( coreproject == NULL );
		ASSERT( coreterritory == NULL );
		ASSERT( rootobject == NULL );
		ASSERT( metaobj_lookup.empty() );
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaMetaProject::get_GUID(VARIANT *p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	CHECK_OUT(p);

	COMTRY
	{
		CCoreObjectPtr me(rootobject);
		me.GetVariantValue(ATTRID_GUID, p);

		if( p->vt != (VT_UI1 | VT_ARRAY) || GetArrayLength(*p) != sizeof(GUID) )
		{
			GUID guid;
			memset(&guid, 0, sizeof(GUID));

			CopyTo(guid, p);
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaMetaProject::put_GUID(VARIANT p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	if( p.vt != (VT_UI1 | VT_ARRAY) || GetArrayLength(p) != sizeof(GUID) )
		COMRETURN(E_INVALIDARG);

	return ComPutAttrValue(rootobject, ATTRID_GUID, p);
}

STDMETHODIMP CMgaMetaProject::get_Name(BSTR *p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	return ComGetAttrValue(rootobject, ATTRID_PARNAME, p);
}

STDMETHODIMP CMgaMetaProject::put_Name(BSTR p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	return ComPutAttrValue(rootobject, ATTRID_PARNAME, p);
}

STDMETHODIMP CMgaMetaProject::get_DisplayedName(BSTR *p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	return ComGetDisplayedName(rootobject, ATTRID_PARDISPNAME, ATTRID_PARNAME, p);
}

STDMETHODIMP CMgaMetaProject::put_DisplayedName(BSTR p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	return ComPutAttrValue(rootobject, ATTRID_PARDISPNAME, p);
}

STDMETHODIMP CMgaMetaProject::get_Version(BSTR *p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	return ComGetAttrValue(rootobject, ATTRID_VERSION, p);
}

STDMETHODIMP CMgaMetaProject::put_Version(BSTR p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	return ComPutAttrValue(rootobject, ATTRID_VERSION, p);
}

STDMETHODIMP CMgaMetaProject::get_Author(BSTR *p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	return ComGetAttrValue(rootobject, ATTRID_AUTHOR, p);
}

STDMETHODIMP CMgaMetaProject::put_Author(BSTR p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	return ComPutAttrValue(rootobject, ATTRID_AUTHOR, p);
}

STDMETHODIMP CMgaMetaProject::get_Comment(BSTR *p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	return ComGetAttrValue(rootobject, ATTRID_COMMENT, p);
}

STDMETHODIMP CMgaMetaProject::put_Comment(BSTR p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	return ComPutAttrValue(rootobject, ATTRID_COMMENT, p);
}

STDMETHODIMP CMgaMetaProject::get_CreatedAt(BSTR *p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	return ComGetAttrValue(rootobject, ATTRID_CDATE, p);
}

STDMETHODIMP CMgaMetaProject::put_CreatedAt(BSTR p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	return ComPutAttrValue(rootobject, ATTRID_CDATE, p);
}

STDMETHODIMP CMgaMetaProject::get_ModifiedAt(BSTR *p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	return ComGetAttrValue(rootobject, ATTRID_MDATE, p);
}

STDMETHODIMP CMgaMetaProject::put_ModifiedAt(BSTR p)
{
	if( rootobject == NULL )
		COMRETURN(E_META_NOTOPEN);

	return ComPutAttrValue(rootobject, ATTRID_MDATE, p);
}

STDMETHODIMP CMgaMetaProject::get_FindObject(metaref_type metaref, IMgaMetaBase **p)
{
	metaobj_lookup_iterator i = metaobj_lookup.find(metaref);
	if( i == metaobj_lookup.end() )
		COMRETURN(E_NOTFOUND);

	CopyTo((*i).second, p);
	return S_OK;
}

STDMETHODIMP CMgaMetaProject::SetNmspc(BSTR p)
{
	m_namespace = p;
	return S_OK;
}

STDMETHODIMP CMgaMetaProject::GetNmspc(BSTR *p)
{
	CComBSTR nms = m_namespace;
	*p = nms.Detach();

	return S_OK;
}

// ------- metaobj_lookup

void CMgaMetaProject::RegisterMetaBase(metaref_type metaref, IMgaMetaBase *obj)
{
	ASSERT( obj != NULL );

	if( metaobj_lookup.find(metaref) != metaobj_lookup.end() )
		HR_THROW(E_METAREF);

	if( metaref > max_metaref )
		max_metaref = metaref;

	metaobj_lookup[metaref] = obj;
}

void CMgaMetaProject::UnregisterMetaBase(metaref_type metaref, IMgaMetaBase *obj)
{
	ASSERT( obj != NULL );
	ASSERT( metaobj_lookup.find(metaref) != metaobj_lookup.end() );
	ASSERT( metaobj_lookup[metaref] == obj );

	metaobj_lookup.erase(metaref);
}

//  ------- Edit

void CMgaMetaProject::CreateMetaBase(metaid_type metaid, CCoreObjectPtr &obj)
{
	ASSERT( obj == NULL );
	ASSERT( coreproject != NULL );

	COMTHROW( coreproject->CreateObject(metaid, PutOut(obj)) );
	COMTHROW( obj->put_AttributeValue(ATTRID_METAREF, PutInVariant(max_metaref + 1)) );
	CMgaMetaBase::Traverse(this, obj);
	
	++max_metaref;
}

void CMgaMetaProject::CreateMetaObj(metaid_type metaid, CCoreObjectPtr &obj)
{
	ASSERT( obj == NULL );
	ASSERT( coreproject != NULL );

	COMTHROW( coreproject->CreateObject(metaid, PutOut(obj)) );
}

// ------- CheckPath

void CMgaMetaProject::CreatePathItems(bstr_const_iterator i, bstr_const_iterator e, pathitems_type &pathitems)
{
	ASSERT( pathitems.empty() );

	while( i != e && *(e-1) == L' ' )
		--e;

	while( i < e )
	{
		wchar_t *j = 0;
		long metaref = wcstol(i, &j, 10);

		if( i == j || j == 0 )
			COMTHROW(E_INVALID_PATH);

		metaobj_lookup_iterator k = metaobj_lookup.find(metaref);
		if( k == metaobj_lookup.end() )
			COMTHROW(E_INVALID_PATH);

		pathitems.push_back(pathitem_type());
		
		COMTHROW( k->second->get_Name(PutOut(pathitems.back().continual_name)) );

		CComObjPtr<IMgaMetaRole> role;
		if( SUCCEEDED( ::QueryInterface(k->second, role)) )
		{
			CComObjPtr<IMgaMetaFCO> fco;
			COMTHROW( role->get_Kind(PutOut(fco)) );
			COMTHROW( fco->get_Name(PutOut(pathitems.back().terminal_name)) );
		}
		else
		{
			pathitems.back().terminal_name = pathitems.back().continual_name;
		}

		i = j;
	}
}

void CMgaMetaProject::CreateJointPaths(BSTR paths, jointpaths_type &jointpaths)
{
	ASSERT( jointpaths.empty() );

	bstr_const_iterator i = begin(paths);
	bstr_const_iterator e = end(paths);
	while( i != e )
	{
		i = std::find_if(i, e, std::bind2nd( std::not_equal_to<wchar_t>(), L' '));
		if( i == e )
			break;
		
		bstr_const_iterator j = std::find(i, e, L' ');
		bstr_const_iterator k = std::find(j, e, L',');

		jointpaths.push_back(jointpath_type());
		CopyTo(i, j, jointpaths.back().ptrspec_name);

		CreatePathItems(j, k, jointpaths.back().pathitems);

		i = k;
		if( i != e )
		{
			ASSERT( *i == L',' );
			++i;
		}
	}
}