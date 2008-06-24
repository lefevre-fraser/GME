
#include "stdafx.h"
#define INITGUID
#include <initguid.h>
#include <list>//slist
#include "CoreRepository.h"
#define	CIfacePtr CComObjPtr
#include <rephelp.h>
#include <reperr.h>
#include "CommonCollection.h"
#include <sqlext.h>

/*
	connection string keywords:

		DBQ=filename
		SERVER=servername
		DATABASE=databasename
		USER=username			(also USR)
		PASSWORD=password		(also PWD)
		DSN=datasourcename

	examples:

		DBQ=D:\Data\metamodel.mdb
		SERVER=xxx;DATABASE=metamodel;USER=user;PASSWORD=password
		DSN=xxx;USER=user;PASSWORD=password

	GUIDs and OBJIDs:

							OBJID					GUID

		TypeLib:			base, 0					base
		ClassDef:			base, metaid			base(0, metaid)
		InterfaceDef:								base(1, metaid)
		CollItfDef:									base(2, attrid)

*/

// --------------------------- CCoreRepository

CCoreRepository::CCoreRepository()
{
	opened_objid = OBJID_NONE;
}

CCoreRepository::~CCoreRepository()
{
	CloseProject();
}

// ------- MetaProject

STDMETHODIMP CCoreRepository::get_MetaProject(ICoreMetaProject **p)
{
	CHECK_OUT(p);

	CopyTo(metaproject, p);

	return S_OK;
}

STDMETHODIMP CCoreRepository::put_MetaProject(ICoreMetaProject *p)
{
	COMTRY
	{
		CloseMetaProject();

		metaproject = p;

		if( metaproject != NULL )
			OpenMetaProject();
	}
	COMCATCH( CloseMetaProject() )
}

void CCoreRepository::OpenMetaProject()
{
	ASSERT( metaprojectid.empty() );
	ASSERT( metaproject != NULL );

	CComVariant tmp;
	metaproject->get_GUID(PutOut(tmp));
	CopyTo(tmp, metaprojectid);
}

void CCoreRepository::CloseMetaProject()
{
	CloseProject();

	CloseMetaObject();

	metaproject = NULL;
	metaprojectid.clear();
}

std::string CCoreRepository::GetProjectToken()
{
	ASSERT( metaproject != NULL );

	CComBstrObj name;
	COMTHROW( metaproject->get_Token(PutOut(name)) );
	if( name.Length() <= 0 )
		HR_THROW(E_METAPROJECT);

	std::string tmp;
	CopyTo(name, tmp);

	return tmp;
}

// ------- MetaObject

STDMETHODIMP CCoreRepository::get_MetaObject(ICoreMetaObject **p)
{
	CHECK_OUT(p);

	CopyTo(metaobject, p);

	return S_OK;
}

STDMETHODIMP CCoreRepository::put_MetaObject(ICoreMetaObject *p)
{
	if( metaproject == NULL )
		COMRETURN(E_INVALID_USAGE);

	if( metaobject == p )
		return S_OK;

	COMTRY
	{
		if( p != NULL )
		{
			CComObjPtr<ICoreMetaProject> t;
			COMTHROW( p->get_Project(PutOut(t)) );
			if( !IsEqualObject(metaproject, t) )
				HR_THROW(E_SAMEPROJECT);
		}

		CloseMetaObject();
		metaobject = p;
		if( metaobject != NULL )
			OpenMetaObject();
	}
	COMCATCH( CloseMetaObject() )
}

STDMETHODIMP CCoreRepository::get_MetaID(metaid_type *p)
{
	CHECK_OUT(p);

	if( metaobject )
		return metaobject->get_MetaID(p);

	*p = 0;
	return S_OK;
}

STDMETHODIMP CCoreRepository::put_MetaID(metaid_type metaid)
{
	if( metaproject == NULL )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{
		if( metaid != METAID_NONE )
		{
			CComObjPtr<ICoreMetaObject> p;
			COMTHROW( metaproject->get_Object(metaid, PutOut(p)) );
			ASSERT( p != NULL );

			if( metaobject != p )
			{
				CloseMetaObject();
				MoveTo(p, metaobject);
				OpenMetaObject();
			}
		}
		else
			CloseMetaObject();
	}
	COMCATCH( CloseMetaObject() )
}

void CCoreRepository::CloseMetaObject()
{
	CloseObject();
	CloseMetaAttribute();
	metaobject = NULL;
}

std::string CCoreRepository::GetObjectToken()
{
	ASSERT( metaobject != NULL );

	CComBstrObj name;
	COMTHROW( metaobject->get_Token(PutOut(name)) );
	if( name.Length() <= 0 )
		HR_THROW(E_METAPROJECT);

	std::string tmp;
	CopyTo(name, tmp);

	return tmp;
}

// ------- MetaAttribute

STDMETHODIMP CCoreRepository::get_MetaAttribute(ICoreMetaAttribute **p)
{
	CHECK_OUT(p);

	CopyTo(metaattribute, p);

	return S_OK;
}

STDMETHODIMP CCoreRepository::put_MetaAttribute(ICoreMetaAttribute *p)
{
	if( metaobject == NULL )
		COMRETURN(E_INVALID_USAGE);
	ASSERT( metaproject != NULL );

	if( metaattribute == p )
		return S_OK;

	COMTRY
	{
		if( metaattribute != NULL )
		{
			CComObjPtr<ICoreMetaObject> t;
			metaattribute->get_Object(PutOut(t));
			if( !IsEqualObject(metaobject, t) )
			{
				metaattribute = NULL;
				return E_INVALIDARG;
			}
		}

		CloseMetaAttribute();
		metaattribute = p;
		if( metaattribute != NULL )
			OpenMetaAttribute();
	}
	COMCATCH( CloseMetaAttribute() )
}

STDMETHODIMP CCoreRepository::get_AttrID(attrid_type *p)
{
	CHECK_OUT(p);

	if( metaattribute )
		return metaattribute->get_AttrID(p);

	*p = 0;
	return S_OK;
}

STDMETHODIMP CCoreRepository::put_AttrID(attrid_type attrid)
{
	if( metaobject == NULL )
		COMRETURN(E_INVALID_USAGE);
	ASSERT( metaproject != NULL );

	COMTRY
	{
		if( attrid != ATTRID_NONE )
		{
			CComObjPtr<ICoreMetaAttribute> p;
			COMTHROW( metaobject->get_Attribute(attrid, PutOut(p)) );
			ASSERT( p != NULL );

			if( metaattribute != p )
			{
				CloseMetaAttribute();
				metaattribute = p;
				OpenMetaAttribute();
			}
		}
		else
			CloseMetaAttribute();
	}
	COMCATCH( CloseMetaAttribute() )
}

void CCoreRepository::CloseMetaAttribute()
{
	metaattribute = NULL;
}

attrid_type CCoreRepository::GetAttrID(ICoreMetaAttribute *p)
{
	if( p == NULL )
		p = metaattribute;
	ASSERT( p != NULL );

	attrid_type attrid;
	COMTHROW( p->get_AttrID(&attrid) );
	if( attrid <= 0 )
		HR_THROW(E_METAPROJECT);

	return attrid;
}

valtype_type CCoreRepository::GetValType(ICoreMetaAttribute *p)
{
	if( p == NULL )
		p = metaattribute;
	ASSERT( p != NULL );

	valtype_type valtype;
	COMTHROW( p->get_ValueType(&valtype) );
	
	if( valtype <= 0 || valtype > VALTYPE_MAX )
		HR_THROW(E_METAPROJECT);

	return valtype;
}

long CCoreRepository::GetMaxSize(ICoreMetaAttribute *p)
{
	if( p == NULL )
		p = metaattribute;
	ASSERT( p != NULL );

	long maxsize = 0;
	COMTHROW( p->get_MaxSize(&maxsize) );

	if( maxsize < 0 )
		HR_THROW(E_METAPROJECT);

	return maxsize;
}

attrid_type CCoreRepository::GetLockAttrID(ICoreMetaAttribute *p)
{
	if( p == NULL )
		p = metaattribute;
	ASSERT( p != NULL );

	attrid_type attrid;
	COMTHROW( p->get_LockAttrID(&attrid) );

	if( attrid < 0 )
		HR_THROW(E_METAPROJECT);

	return attrid;
}

std::string CCoreRepository::GetToken(ICoreMetaAttribute *p)
{
	if( p == NULL )
		p = metaattribute;
	ASSERT( p != NULL );

	CComBstrObj name;
	COMTHROW( p->get_Token(PutOut(name)) );
	if( name.Length() <= 0 )
		HR_THROW(E_METAPROJECT);

	std::string tmp;
	CopyTo(name, tmp);

	return tmp;
}

// ------- GUID and OBJID

inline GUID CCoreRepository::GetGUID(short cat, long index)
{
	ASSERT( metaprojectid.size() == sizeof(GUID) );
	GUID ret = *(GUID*)&metaprojectid[0];

	ret.Data1 += index;
	ret.Data2 += cat;

	return ret;
}

inline OBJID CCoreRepository::GetOBJID(long index, long localid)
{
	ASSERT( metaprojectid.size() == sizeof(GUID) );

	OBJID ret;
	ret.Lineage = *(GUID*)&metaprojectid[0];

	ret.Lineage.Data1 += index;
	ret.Uniquifier = localid;

	return ret;
}

inline void CCoreRepository::ReadGUID(const bindata &input, short &cat, long &index)
{
	ASSERT( metaprojectid.size() == 16 );
	ASSERT( input.size() == 16 );

	GUID &base = *(GUID*)&metaprojectid[0];
	GUID &guid = *(GUID*)&input[0];

	if( memcmp(&base.Data3, &guid.Data3, sizeof(base.Data3) + sizeof(guid.Data4)) != 0 )
		HR_THROW(E_REPOSITORY_DATA);

	cat = guid.Data2 - base.Data2;
	index = guid.Data1 - base.Data1;
}

inline void CCoreRepository::ReadOBJID(const bindata &input, long &index, long &localid)
{
	ASSERT( metaprojectid.size() == 16 );
	ASSERT( input.size() == 20 );

	GUID &base = *(GUID*)&metaprojectid[0];
	OBJID &objid = *(OBJID*)&input[0];

	if( memcmp(&base.Data2, &objid.Lineage.Data2, 
		sizeof(base.Data2) + sizeof(base.Data3) + sizeof(base.Data4)) != 0 )
		HR_THROW(E_REPOSITORY_DATA);

	index = objid.Lineage.Data1 - base.Data1;
	localid = objid.Uniquifier;
}

// ------- Repository 

inline void CCoreRepository::GetRepInterface(IRepositoryItem *repobj, const GUID &guid, CComObjPtr<IDispatch> &ret)
{
	ASSERT( ret == NULL );
	ASSERT( repobj != NULL );

	COMTHROW( repobj->QueryInterface(guid, (void**)PutOut(ret)) );
	ASSERT( ret != NULL );
}

// ------- TypeLib

void CCoreRepository::CreateTypeLib()
{
	ASSERT( metaproject != NULL );
	ASSERT( repository != NULL );

	ASSERT( reptransaction == NULL );
	ASSERT( reptypelib == NULL );
	ASSERT( repdispatchdef == NULL );

	COMTHROW( repository->get_Transaction(PutOut(reptransaction)) );
	ASSERT( reptransaction != NULL );

	COMTHROW( reptransaction->Begin() );

	try
	{
		CComObjPtr<IManageReposTypeLib> managetypelib;
		GetRepObject(OBJID_ReposRootObj, managetypelib);

		COMTHROW( managetypelib->CreateTypeLib(PutInVariant(GetTypeLibOBJID()),
			PutInBstr(GetTypeLibName()), PutInVariant(GetTypeLibGUID()),
			PutOut(reptypelib)) );
		ASSERT( reptypelib != NULL );

		GetRepObject(OBJID_IReposDispatch, repdispatchdef);

		CComObjPtr<ICoreMetaObjects> metaobjects;
		COMTHROW( metaproject->get_Objects(PutOut(metaobjects)) );
		ASSERT( metaobjects != NULL );

		typedef std::vector< CComObjPtr<ICoreMetaObject> > metaobjectlist_type;
		metaobjectlist_type metaobjectlist;
		GetAll<ICoreMetaObjects, ICoreMetaObject>(metaobjects, metaobjectlist);

		ASSERT( colldefs.empty() );

		metaobjectlist_type::iterator i = metaobjectlist.begin();
		metaobjectlist_type::iterator e = metaobjectlist.end();
		while( i != e )
		{
			metaobject = *i;
			ASSERT( metaobject != NULL );

			CreateClassDef();
			++i;
		}

		{
			colldefs_iterator i = colldefs.begin();
			colldefs_iterator e = colldefs.end();
			while( i != e )
			{
				if( GetValType((*i).metaattribute) == VALTYPE_POINTER )
				{
					colldefs_iterator j = FindCollDef( (*i).attrid + ATTRID_COLLECTION );
					if( j == e )
						HR_THROW(E_METAPROJECT);

					CreateCollRelationshipDef(*i, *j);
				}
				else
				{
					ASSERT( GetValType((*i).metaattribute) == VALTYPE_COLLECTION );

					if( FindCollDef( (*i).attrid - ATTRID_COLLECTION ) == e )
						HR_THROW(E_METAPROJECT);
				}

				++i;
			}
		}
		colldefs.clear();

		CComObjPtr<IClassDef> reprootclassdef;
		GetRepObject(OBJID_ReposRoot, reprootclassdef);

		CComObjPtr<IInterfaceDef> reprootinterfacedef;
		COMTHROW( reprootclassdef->CreateInterfaceDef(PutInVariant(OBJID_NULL),
			PutInBstr(std::string("I") + GetProjectToken()),
			PutInVariant(GetGUID(1, ATTRID_NONE + ATTRID_COLLECTION)),
			repdispatchdef, NULL, PutOut(reprootinterfacedef)) );
		ASSERT( reprootinterfacedef );

		CComObjPtr<IClassDef> corerootclassdef;
		GetRepObject(GetOBJID(0, METAID_ROOT), corerootclassdef);

		CComObjPtr<IInterfaceDef> corerootinterfacedef;
		COMTHROW( corerootclassdef->CreateInterfaceDef(PutInVariant(OBJID_NULL),
			PutInBstr("IRepositoryRoot"),
			PutInVariant(GetGUID(1, ATTRID_NONE)),
			repdispatchdef, NULL, PutOut(corerootinterfacedef)) );

		CComObjPtr<IReposTypeInfo> relshipdef;
		COMTHROW( reptypelib->CreateRelationshipDef(
			PutInVariant(OBJID_NULL),
			PutInBstr(GetProjectToken() + " - RepositoryRoot"), 
			PutOut(relshipdef)) );
		ASSERT( relshipdef != NULL );

		CComObjPtr<ICollectionDef> coldef;
		ASSERT( reprootinterfacedef != NULL );
		COMTHROW( reprootinterfacedef->CreateRelationshipColDef(
			PutInVariant(OBJID_NULL),
			PutInBstr(GetProjectToken()),
			ATTRID_NONE, true, 0,
			relshipdef, PutOut(coldef)) );
		ASSERT( coldef != NULL );

		coldef = NULL;
		COMTHROW( corerootinterfacedef->CreateRelationshipColDef(
			PutInVariant(OBJID_NULL),
			PutInBstr("ReporitoryRoot"),
			ATTRID_NONE, false, 0, 
			relshipdef, PutOut(coldef)) );
		ASSERT( coldef != NULL );

		COMTHROW( put_RepProp(coldef, DISPID_MaxCount, 1) );

		i = metaobjectlist.begin();
		ASSERT( e == metaobjectlist.end() );
		while( i != e )
		{
			metaobject = *i;

			CComObjPtr<IPropertyDef> propertydef;
			COMTHROW( reprootinterfacedef->CreatePropertyDef(
				PutInVariant(OBJID_NULL),
				PutInBstr(std::string("ObjID_") + GetObjectToken()),
				GetMetaID(), SQL_C_LONG,
				PutOut(propertydef)) );

			++i;
		}

		ASSERT( reptransaction != NULL );
		COMTHROW( reptransaction->Commit() );
		COMTHROW( reptransaction->Begin() );

		CComObjPtr<IRepositoryObject> corerootobj;
		COMTHROW( repository->CreateObject(
			PutInVariant(GetOBJID(0, METAID_ROOT)),
			PutInVariant(GetOBJID(METAID_ROOT, OBJID_ROOT)),
			PutOut(corerootobj)) );
		ASSERT( corerootobj != NULL );

		COMTHROW( corerootobj->put_Name(
			PutInBstr(std::string("MGA ") + GetProjectToken() + " Root Object")) );

		CComObjPtr<IRepositoryObject> reprootobj;
		GetRepObject(OBJID_ReposRootObj, reprootobj);

		CComObjPtr<IDispatch> reprootitf;
		GetRepInterface(reprootobj, GetGUID(1, ATTRID_NONE + ATTRID_COLLECTION), reprootitf);

		CComObjPtr<ITargetObjectCol> objcol;
		COMTHROW( get_RepTargetObjCol(reprootitf,
			ATTRID_NONE, PutOut(objcol)) );
		ASSERT( objcol != NULL );

		CComObjPtr<IRelationship> relship;
		COMTHROW( objcol->Add(corerootobj,
			NULL, PutOut(relship)) );
		ASSERT( relship != NULL );

		i = metaobjectlist.begin();
		ASSERT( e == metaobjectlist.end() );
		while( i != e )
		{
			metaobject = *i;
			metaid_type metaid = GetMetaID();

			COMTHROW( put_RepProp(reprootitf, metaid, metaid == METAID_ROOT ? 2 : 1) );

			++i;
		}

		metaobject = NULL;

		ASSERT( reptransaction != NULL );
		COMTHROW( reptransaction->Commit() );

		ASSERT( colldefs.empty() );
		ASSERT( metaobject == NULL );
		ASSERT( metaattribute == NULL );

		reptransaction = NULL;
		reptypelib = NULL;
		repdispatchdef = NULL;
	}
	catch(hresult_exception &)
	{
		try {
			CComPtr<IReposErrorQueueHandler> errh;
			COMTHROW(repository->QueryInterface(IID_IReposErrorQueueHandler, (void**)&errh));

			CComPtr<IRepositoryErrorQueue> errq;

			COMTHROW(errh->GetErrorQueue(&errq));
			unsigned long errqcnt = errq->Count();
			for(unsigned long i = 0; i < errqcnt; i++) {
				REPOSERROR rerr;
				COMTHROW(errq->Item(i+1, &rerr));
			unsigned long cerrqcnt = errq->Count();
			}
		}
		catch(hresult_exception &) {
			;
		}

		if( reptransaction != NULL )
			reptransaction->Abort();

		colldefs.clear();

		reptransaction = NULL;
		reptypelib = NULL;
		repdispatchdef = NULL;

		throw;
	}
}

// ------- ClassDef

void CCoreRepository::CreateClassDef()
{
	ASSERT( repository != NULL );
	ASSERT( metaobject != NULL );

	ASSERT( reptypelib != NULL );
	ASSERT( repdispatchdef != NULL );

	try
	{
		ASSERT( repclassdef == NULL );
		COMTHROW( reptypelib->CreateClassDef(PutInVariant(GetClassOBJID()),
			PutInBstr(GetClassName()), PutInVariant(GetClassGUID()),
			PutOut(repclassdef)) );
		ASSERT( repclassdef != NULL );

		ASSERT( repinterfacedef == NULL );
		COMTHROW( repclassdef->CreateInterfaceDef(PutInVariant(OBJID_NULL),
			PutInBstr(GetInterfaceName()), PutInVariant(GetInterfaceGUID()),
			repdispatchdef, PutInBstr("Default"), PutOut(repinterfacedef)) );
		ASSERT( repinterfacedef != NULL );

		CComObjPtr<ICoreMetaAttributes> metaattrs;
		COMTHROW( metaobject->get_Attributes(PutOut(metaattrs)) );
		ASSERT( metaattrs != NULL );

		typedef std::vector< CComObjPtr<ICoreMetaAttribute> > metaattrlist_type;
		metaattrlist_type metaattrlist;
		GetAll<ICoreMetaAttributes,ICoreMetaAttribute>(metaattrs, metaattrlist);

		metaattrlist_type::iterator i = metaattrlist.begin();
		metaattrlist_type::iterator e = metaattrlist.end();

		while( i != e )
		{
			metaattribute = *i;
			ASSERT( metaattribute != NULL );

			CreatePropertyDef();
			++i;
		}

		metaattribute = NULL;
		repclassdef = NULL;
		repinterfacedef = NULL;
	}
	catch(hresult_exception &)
	{
		metaattribute = NULL;
		repclassdef = NULL;
		repinterfacedef = NULL;

		throw;
	}
}

// ------- PropertyDef

inline void CCoreRepository::CheckIsEqual(ICoreMetaAttribute *p, ICoreMetaAttribute *q)
{
	ASSERT( p != NULL );
	ASSERT( q != NULL );

	if( GetAttrID(p) != GetAttrID(q) ||
//		!(GetName(p) == GetName(q)) ||
		!(GetToken(p) == GetToken(q)) ||
		GetValType(p) != GetValType(q) ||
		GetMaxSize(p) != GetMaxSize(q) )
	{
		HR_THROW(E_METAPROJECT);
	}
}

void CCoreRepository::CreatePropertyDef()
{
	ASSERT( repclassdef != NULL );
	ASSERT( repinterfacedef != NULL );
	ASSERT( metaattribute != NULL );

	attrid_type attrid = GetAttrID(metaattribute);
	valtype_type valtype = GetValType(metaattribute);

	if( attrid == ATTRID_NAME )
	{
		if( valtype != VALTYPE_STRING )
			HR_THROW(E_METAPROJECT);

		CComObjPtr<IInterfaceDef> nameditfdef;
		GetRepObject(OBJID_INamedObject, nameditfdef);

		COMTHROW( repclassdef->AddInterface(nameditfdef, NULL) );

		return;
	}

	if( valtype == VALTYPE_COLLECTION || valtype == VALTYPE_POINTER )
	{
		IInterfaceDef *collinterfacedef = GetCollInterfaceDef(metaattribute);
		ASSERT( collinterfacedef != NULL );

		COMTHROW( repclassdef->AddInterface((collinterfacedef), NULL) );

		return;
	}

	std::string name(GetPropertyName());
	DISPID dispid(attrid);

	short ctype = 0;
	short sqltype = 0;
	long sqlsize = 0;

	if( valtype == VALTYPE_LONG )
		ctype = SQL_C_LONG;
	else if( valtype == VALTYPE_BINARY )
	{
		ctype = SQL_C_BINARY;

		sqlsize = GetMaxSize(metaattribute);

		if( sqlsize < 255 )
			sqltype = SQL_VARBINARY;
		else
			sqltype = SQL_LONGVARBINARY;
	}
	else if( valtype == VALTYPE_LOCK )
		ctype = SQL_C_SHORT;
	else if( valtype == VALTYPE_REAL )
	{
		ctype = SQL_C_DOUBLE;
		sqltype = SQL_DOUBLE;
	}
	else if( valtype == VALTYPE_STRING )
	{
		ctype = SQL_C_CHAR;

		sqlsize = GetMaxSize(metaattribute);

		if( sqlsize < 255 )
			sqltype = SQL_VARCHAR;
		else
			sqltype = SQL_LONGVARCHAR;
	}
	else
		HR_THROW(E_METAPROJECT);

	if( sqlsize < 0 )
		sqlsize = 0;
	else if( sqlsize > 32767 )
		sqlsize = 32767;

	CComObjPtr<IPropertyDef> propertydef;
	COMTHROW( repinterfacedef->CreatePropertyDef(PutInVariant(OBJID_NULL),
		PutInBstr(name), dispid, ctype, PutOut(propertydef)) );
	ASSERT( propertydef != NULL );

	if( sqltype != 0 )
		COMTHROW( put_RepProp(propertydef, DISPID_SQLType, sqltype) );

	if( sqlsize != 0 )
		COMTHROW( put_RepProp(propertydef, DISPID_SQLSize, (short)sqlsize) );
}

// ------- CollDefs

inline std::string CCoreRepository::GetCollInterfaceName(ICoreMetaAttribute *metaaattribute)
{
	return std::string("I") + GetToken(metaattribute);
}

CCoreRepository::colldefs_iterator CCoreRepository::FindCollDef(attrid_type attrid)
{
	colldefs_iterator i = colldefs.begin();
	colldefs_iterator e = colldefs.end();
	while( i != e && (*i).attrid != attrid )
		++i;

	return i;
}

IInterfaceDef *CCoreRepository::GetCollInterfaceDef(ICoreMetaAttribute *metaattribute)
{
	ASSERT( metaattribute != NULL );
	ASSERT( GetValType(metaattribute) == VALTYPE_POINTER ||
		GetValType(metaattribute) == VALTYPE_COLLECTION );

	attrid_type attrid = GetAttrID(metaattribute);

	colldefs_iterator i = FindCollDef(attrid);
	if( i == colldefs.end() )
	{
		colldefs.push_front(colldef_type());

		colldefs.front().attrid = attrid;
		colldefs.front().metaattribute = metaattribute;

		ASSERT( reptypelib != NULL );
		ASSERT( repdispatchdef );

		COMTHROW( reptypelib->CreateInterfaceDef(PutInVariant(OBJID_NULL),
			PutInBstr(GetCollInterfaceName(metaattribute)),
			PutInVariant(GetCollInterfaceGUID(metaattribute)),
			repdispatchdef, PutOut(colldefs.front().interfacedef)) );

		return colldefs.front().interfacedef;
	}

	CheckIsEqual(metaattribute, (*i).metaattribute);
	return (*i).interfacedef;
}

void CCoreRepository::CreateCollRelationshipDef(colldef_type &pointer, colldef_type &collection)
{
	ASSERT( GetValType(pointer.metaattribute) == VALTYPE_POINTER );
	ASSERT( GetValType(collection.metaattribute) == VALTYPE_COLLECTION );
	ASSERT( pointer.attrid + ATTRID_COLLECTION == collection.attrid );

	CComObjPtr<IReposTypeInfo> relshipdef;
	ASSERT( reptypelib != NULL );
	COMTHROW( reptypelib->CreateRelationshipDef(
		PutInVariant(OBJID_NULL),
		PutInBstr(GetCollRelationshipName(pointer.metaattribute, collection.metaattribute)), 
		PutOut(relshipdef)) );
	ASSERT( relshipdef != NULL );

	CComObjPtr<ICollectionDef> coldef;
	ASSERT( collection.interfacedef != NULL );
	COMTHROW( collection.interfacedef->CreateRelationshipColDef(
		PutInVariant(OBJID_NULL),
		PutInBstr(GetToken(collection.metaattribute)),
		collection.attrid, true, 0,
		relshipdef, PutOut(coldef)) );
	ASSERT( coldef != NULL );

	coldef = NULL;
	ASSERT( pointer.interfacedef != NULL );
	COMTHROW( pointer.interfacedef->CreateRelationshipColDef(
		PutInVariant(OBJID_NULL),
		PutInBstr(GetToken(pointer.metaattribute)),
		pointer.attrid,	false, 0, 
		relshipdef, PutOut(coldef)) );
	ASSERT( coldef != NULL );

	COMTHROW( put_RepProp(coldef, DISPID_MaxCount, 1) );
}

// ------- Project

void CCoreRepository::GetConnUserPswd(std::string &connection, 
	std::string &conn, std::string &user, std::string &pswd)
{
	conn.erase();
	user.erase();
	pswd.erase();

	unsigned int pos = 0;
	while( pos < connection.size() )
	{
		unsigned int end = connection.find(";", pos);
		if( end == connection.npos )
			end = connection.size();

		std::string keyval(connection, pos, end-pos);
		pos = end+1;

		if( keyval.empty() )
			continue;

		unsigned int mid = keyval.find("=", 0);
		if( mid != keyval.npos )
		{
			std::string key(keyval, 0, mid);
			std::string val(keyval, mid+1);

			if( key == "USER" )
			{
				user = val;
				continue;
			}
			if( key == "PASSWORD" )
			{
				pswd = val;
				continue;
			}
		}

		if( !keyval.empty() )
		{
			if( !conn.empty() )
				conn += ";";

			conn += keyval;
		}
	}
}

STDMETHODIMP CCoreRepository::CreateProject(BSTR connection)
{
	if( metaproject == NULL || repository != NULL )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{
#ifdef TRACE_REPOSITORY
		AtlTrace("Repository: CreateProject\n");
#endif

		COMTHROW( CloseProject() );

		ASSERT( repository == NULL );
		COMTHROW( CoCreateInstance(CLSID_Repository, NULL, CLSCTX_INPROC_SERVER,
			__uuidof(repository), (void**)PutOut(repository)) );
		ASSERT( repository != NULL );

		std::string connall;
		CopyTo(connection, connall);

		std::string conn, user, pswd;
		GetConnUserPswd(connall, conn, user, pswd);

		CComObjPtr<IRepositoryObject> reprootobj;
		COMTHROW( repository->Create(PutInBstr(conn), PutInBstr(user), 
			PutInBstr(pswd), 0, PutOut(reprootobj)) );
		ASSERT( reprootobj != NULL );

		CreateTypeLib();

		ASSERT( reptypelib == NULL );
		CopyTo(connection, connstr);
	}
	COMCATCH( repository = NULL; )
}

STDMETHODIMP CCoreRepository::OpenProject(BSTR connection, VARIANT_BOOL *ro_mode) {
	if( metaproject == NULL || repository != NULL )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{
#ifdef TRACE_REPOSITORY
		AtlTrace("Repository: OpenProject\n");
#endif;

		COMTHROW( CloseProject() );

		ASSERT( repository == NULL );
		COMTHROW( CoCreateInstance(CLSID_Repository, NULL, CLSCTX_INPROC_SERVER,
			__uuidof(repository), (void**)PutOut(repository)) );
		ASSERT( repository != NULL );

		std::string connall;
		CopyTo(connection, connall);

		std::string conn, user, pswd;
		GetConnUserPswd(connall, conn, user, pswd);

		CComObjPtr<IRepositoryObject> reprootobj;
		COMTHROW( repository->Open(PutInBstr(conn), PutInBstr(user), 
			PutInBstr(pswd), 0, PutOut(reprootobj)) );
		ASSERT( reprootobj != NULL );

		CComObjPtr<IDispatch> reprootitf;
		GetRepInterface(reprootobj, GetGUID(1, ATTRID_NONE + ATTRID_COLLECTION), reprootitf);
		ASSERT( reprootitf != NULL );

		ASSERT( reptypelib == NULL );
		if(ro_mode) *ro_mode = VARIANT_FALSE;
		CopyTo(connection, connstr);
	}
	COMCATCH( repository = NULL; )
}

STDMETHODIMP CCoreRepository::CloseProject(VARIANT_BOOL abort)
{
#ifdef TRACE_REPOSITORY
	AtlTrace("Repository: CloseProject\n");
#endif;

	if(abort != VARIANT_FALSE) return E_INVALID_USAGE;

	CloseObject();

	if( reptransaction )
		AbortTransaction();

	ObjID_CloseProject();

	ASSERT( reptypelib == NULL );
	ASSERT( repdispatchdef == NULL );

	reptransaction = NULL;
	repository = NULL;
	
	return S_OK;
}

STDMETHODIMP CCoreRepository::BeginTransaction()
{
	if( repository == NULL || reptransaction != NULL )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{
#ifdef TRACE_REPOSITORY
		AtlTrace("Repository: BeginTransaction\n");
#endif;
		
		COMTHROW( repository->Refresh(0) );

		COMTHROW( repository->get_Transaction(PutOut(reptransaction)) );
		ASSERT( reptransaction != NULL );

		COMTHROW( reptransaction->Begin() );

		ObjID_BeginTransaction();
	}
	COMCATCH( reptransaction = NULL );
}

STDMETHODIMP CCoreRepository::CommitTransaction()
{
	if( repository == NULL || reptransaction == NULL )
		COMRETURN(E_INVALID_USAGE);

#ifdef TRACE_REPOSITORY
	AtlTrace("Repository: CommitTransaction\n");
#endif;

	COMTRY
	{
		ObjID_CommitTransaction();

		COMTHROW( reptransaction->Commit() );

		reptransaction = NULL;
	}
	COMCATCH(;)
}

STDMETHODIMP CCoreRepository::AbortTransaction()
{
	if( repository == NULL || reptransaction == NULL )
		COMRETURN(E_INVALID_USAGE);

#ifdef TRACE_REPOSITORY
	AtlTrace("Repository: AbortTransaction\n");
#endif;

	ObjID_AbortTransaction();
	
	HRESULT hr = reptransaction->Abort();

	reptransaction = NULL;

	COMRETURN(hr);
}

STDMETHODIMP CCoreRepository::get_StorageType(long *p)
{
	CHECK_OUT(p);

	if( repository == NULL )
		COMRETURN(E_INVALID_USAGE);

	*p = 1;
	return S_OK;
}

// ------- ObjID

void CCoreRepository::ObjID_BeginTransaction()
{
	start_gens = objid_gens;

	objid_gens_iterator i = objid_gens.begin();
	objid_gens_iterator e = objid_gens.end();
	while( i != e )
	{
		(*i).second.next = OBJID_NONE;

		++i;
	}
}

void CCoreRepository::ObjID_CommitTransaction()
{
	ASSERT( reptransaction != NULL );

	CComObjPtr<IRepositoryObject> reprootobj;
	GetRepObject(OBJID_ReposRootObj, reprootobj);

	CComObjPtr<IDispatch> reprootitf;
	GetRepInterface(reprootobj, GetGUID(1, ATTRID_NONE + ATTRID_COLLECTION), reprootitf);

	objid_gens_iterator i = objid_gens.begin();
	objid_gens_iterator e = objid_gens.end();
	while( i != e )
	{
		if( (*i).second.next != OBJID_NONE )
		{
			COMTHROW( put_RepProp(reprootitf, (*i).first, (*i).second.next) );
		}

		++i;
	}
}

objid_type CCoreRepository::ObjID_GetNext(metaid_type metaid)
{
	ASSERT( metaid != METAID_NONE );

	objid_type objid = OBJID_NONE;

	objid_gen_type &gen = objid_gens[metaid];
	if( !gen.returned.empty() )
	{
		objid = gen.returned.back();
		gen.returned.pop_back();
	}
	else if( gen.next == OBJID_NONE )
	{
		CComObjPtr<IRepositoryObject> reprootobj;
		GetRepObject(OBJID_ReposRootObj, reprootobj);

		CComObjPtr<IDispatch> reprootitf;
		GetRepInterface(reprootobj, GetGUID(1, ATTRID_NONE + ATTRID_COLLECTION), reprootitf);

		CComVariant result;
		COMTHROW( get_RepProp(reprootitf, metaid, &result) );

		CopyTo(result, gen.next);
		if( gen.next == OBJID_NONE )
			HR_THROW(E_REPOSITORY);

		objid = gen.next++;
		ASSERT( gen.next != OBJID_NONE );
	}
	else
	{
		objid = gen.next++;
		ASSERT( gen.next != OBJID_NONE );
	}

	ASSERT( objid != OBJID_NONE );
	return objid;
}

void CCoreRepository::ObjID_Return(metaid_type metaid, objid_type objid)
{
	ASSERT( metaid != METAID_NONE );
	ASSERT( objid != OBJID_NONE );

//	objid_gen_type &gen = objid_gens[metaid];
//	gen.returned.push_back(objid);
}

// ------- Object

STDMETHODIMP CCoreRepository::OpenObject(objid_type objid)
{
	if( repository == NULL || metaobject == NULL )
		COMRETURN(E_INVALID_USAGE);

	if( objid == OBJID_NONE )
		return E_INVALIDARG;

	if( objid == opened_objid )
		return S_OK;

	COMTRY
	{
#ifdef TRACE_REPOSITORY
		AtlTrace("Repository: OpenObject metaid=%d, objid=%d\n", (int)GetMetaID(), (int)objid);
#endif

		CloseObject();
		COMTHROW( repository->get_Object(
			PutInVariant(GetObjectOBJID(GetMetaID(), objid)),
			PutOut(repobject)) );
		ASSERT( repobject != NULL );

		opened_objid = objid;
	}
	COMCATCH( CloseObject() )
}

STDMETHODIMP CCoreRepository::CreateObject(objid_type *objid)
{
	CHECK_OUT(objid);

	if( repository == NULL || metaobject == NULL )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{
		CloseObject();

		*objid = ObjID_GetNext(GetMetaID());
		ASSERT( *objid != OBJID_NONE );

#ifdef TRACE_REPOSITORY
		AtlTrace("Repository: CreateObject metaid=%d, objid=%d\n", (int)GetMetaID(), (int)*objid);
#endif
	
		COMTHROW( repository->CreateObject(
			PutInVariant(GetClassOBJID()),
			PutInVariant(GetObjectOBJID(GetMetaID(), *objid)),
			PutOut(repobject)) );
		ASSERT( repobject != NULL );

		opened_objid = *objid;
	}
	COMCATCH( CloseObject() )
}

STDMETHODIMP CCoreRepository::CloseObject()
{
	repobject = NULL;
	repobjectitf = NULL;
	opened_objid = OBJID_NONE;

	return S_OK;
}

STDMETHODIMP CCoreRepository::LockObject()
{
	if( repobject == NULL )
		COMRETURN(E_INVALID_USAGE);

#ifdef TRACE_REPOSITORY
	AtlTrace("Repository: LockObject\n");
#endif;

	return repobject->Lock();
}

STDMETHODIMP CCoreRepository::DeleteObject()
{
	if( repobject == NULL )
		COMRETURN(E_INVALID_USAGE);

#ifdef TRACE_REPOSITORY
	AtlTrace("Repository: DeleteObject\n");
#endif;

	HRESULT hr = repobject->Delete();

	if( SUCCEEDED(hr) )
		ObjID_Return(GetMetaID(), opened_objid);

	return hr;
}

// ------- Attribute

STDMETHODIMP CCoreRepository::get_AttributeValue(VARIANT *p)
{
	CHECK_OUT(p);
	
	if( metaattribute == NULL || repobject == NULL || reptransaction == NULL )
		COMRETURN(E_INVALID_USAGE);

	ASSERT( repository != NULL );
	ASSERT( reptransaction != NULL );

	COMTRY
	{
#ifdef TRACE_REPOSITORY
		AtlTrace("Repository: get_AttributeValue attrid=%d\n", (int)GetAttrID());
#endif

		valtype_type valtype = GetValType(metaattribute);

		if( valtype <= VALTYPE_NONE || valtype > VALTYPE_MAX )
			HR_THROW(E_METAPROJECT);

		if( valtype == VALTYPE_COLLECTION )
		{
			CComObjPtr<IDispatch> repcollitf;
			GetRepInterface(repobject, GetCollInterfaceGUID(metaattribute), repcollitf);

			CComObjPtr<ITargetObjectCol> objcol;
			COMTHROW( get_RepTargetObjCol(repcollitf,
				GetAttrID(), PutOut(objcol)) );
			ASSERT( objcol != NULL );

			long c = 0;
			COMTHROW( objcol->get_Count(&c) );

			std::vector<metaobjidpair_type> idpairs;

			for(long i = 1; i <= c; i++)
				AddIDPair(objcol, i, idpairs);

			CopyTo(idpairs, p);
		}
		else if( valtype == VALTYPE_POINTER )
		{
			CComObjPtr<IDispatch> repcollitf;
			GetRepInterface(repobject, GetCollInterfaceGUID(metaattribute), repcollitf);

			CComObjPtr<ITargetObjectCol> objcol;
			COMTHROW( get_RepTargetObjCol(repcollitf,
				GetAttrID(), PutOut(objcol)) );
			ASSERT( objcol != NULL );

			long c = 0;
			COMTHROW( objcol->get_Count(&c) );
			ASSERT( c == 0 || c == 1 );

			std::vector<metaobjidpair_type> idpairs;

			if( c != 0 )
				AddIDPair(objcol, 1, idpairs);
			else
			{
				idpairs.push_back( metaobjidpair_type());
				idpairs.back().metaid = METAID_NONE;
				idpairs.back().objid = OBJID_NONE;
			}

			CopyTo(idpairs, p);
		}
		else
		{
			attrid_type attrid = GetAttrID();

			CComVariant result;

			if( attrid == ATTRID_NAME )
			{
				ASSERT( result.vt == VT_EMPTY );
				result.vt = VT_BSTR;
				result.bstrVal = NULL;

				ASSERT( repobject != NULL );
				COMTHROW( repobject->get_Name(&result.bstrVal) );
			}
			else
			{
				if( repobjectitf == NULL )
					GetRepInterface(repobject, GetInterfaceGUID(), repobjectitf);

				ASSERT( repobjectitf != NULL );
				COMTHROW( get_RepProp(repobjectitf, attrid, &result) );

				if( result.vt == VT_NULL )
				{
					switch( valtype )
					{
					case VALTYPE_LOCK:
						result = (short)LOCKING_NONE;
						break;

					case VALTYPE_LONG:
						result = (long)0;
						break;

					case VALTYPE_STRING:
						result = (BSTR)NULL;
						break;

					case VALTYPE_REAL:
						result = (double)0.0;
						break;

					case VALTYPE_BINARY:
						CopyTo((unsigned char*)NULL, (unsigned char*)NULL, result);
						break;

					default:
						HR_THROW(E_REPOSITORY);
					}
				}
				else
				{
					switch( valtype )
					{
					case VALTYPE_LOCK:
						COMTHROW( result.ChangeType(VT_I2) );
						break;

					case VALTYPE_LONG:
						COMTHROW( result.ChangeType(VT_I4) );
						break;

					case VALTYPE_STRING:
						COMTHROW( result.ChangeType(VT_BSTR) );
						break;

					case VALTYPE_REAL:
						COMTHROW( result.ChangeType(VT_R8) );
						break;

					case VALTYPE_BINARY:
						COMTHROW( result.ChangeType(VT_UI1 | VT_ARRAY) );
						break;

					default:
						HR_THROW(E_REPOSITORY);
					}
				}
			}

			result.Detach(p);
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CCoreRepository::put_AttributeValue(VARIANT p)
{
	if( metaattribute == NULL || repobject == NULL || reptransaction == NULL )
		COMRETURN(E_INVALID_USAGE);

	ASSERT( repository != NULL );
	ASSERT( reptransaction != NULL );

	COMTRY
	{
#ifdef TRACE_REPOSITORY
		AtlTrace("Repository: put_AttributeValue attrid=%d\n", (int)GetAttrID());
#endif

		valtype_type valtype = GetValType(metaattribute);

		if( valtype <= VALTYPE_NONE || valtype > VALTYPE_MAX )
			HR_THROW(E_METAPROJECT);

		if( valtype == VALTYPE_COLLECTION )
			HR_THROW(E_INVALID_USAGE);
		else if( valtype == VALTYPE_POINTER )
		{
			metaobjidpair_type idpair;
			CopyTo(p, idpair);

			attrid_type attrid = GetAttrID();

			CComObjPtr<IDispatch> repcollitf;
			GetRepInterface(repobject, GetCollInterfaceGUID(metaattribute), repcollitf);

			CComObjPtr<ITargetObjectCol> objcol;
			COMTHROW( get_RepTargetObjCol(repcollitf,
				attrid, PutOut(objcol)) );
			ASSERT( objcol != NULL );

#ifdef _DEBUG
			long c = 0;
			COMTHROW( objcol->get_Count(&c) );
			ASSERT( c == 0 || c == 1 );
#endif

			HRESULT hr = objcol->Remove(PutInVariant(1));
			if( hr != S_OK && hr != DISP_E_BADINDEX )
				HR_THROW(hr);

			if( idpair.metaid != METAID_NONE )
			{
				CComObjPtr<IRepositoryObject> repobj;
#pragma warning( disable: 4244) // conversion from 'long' to 'short', possible loss of data
				COMTHROW( repository->get_Object(
					PutInVariant(GetObjectOBJID(idpair.metaid, idpair.objid)),
					PutOut(repobj)) );
#pragma warning( default: 4244) // conversion from 'long' to 'short', possible loss of data
				ASSERT( repobj != NULL );
				
				CComObjPtr<IRelationship> reprel;
				COMTHROW( objcol->Add(repobj, NULL, PutOut(reprel)) );
				ASSERT( reprel != NULL );
			}

#ifdef _DEBUG
			c = 0;
			COMTHROW( objcol->get_Count(&c) );
			ASSERT( c == 0 || c == 1 );
#endif
		}
		else
		{
			CComVariant var(p);

			switch( valtype )
			{
			case VALTYPE_LOCK:
				COMTHROW( var.ChangeType(VT_I2) );
				break;

			case VALTYPE_LONG:
				COMTHROW( var.ChangeType(VT_I4) );
				break;

			case VALTYPE_STRING:
				COMTHROW( var.ChangeType(VT_BSTR) );
				break;

			case VALTYPE_BINARY:
				COMTHROW( var.ChangeType(VT_UI1 | VT_ARRAY) );
				break;

			case VALTYPE_REAL:
				COMTHROW( var.ChangeType(VT_R8) );
				break;

			default:
				ASSERT(false);
			}

			attrid_type attrid = GetAttrID();

			if( attrid == ATTRID_NAME )
			{
				ASSERT( repobject != NULL );
				ASSERT( var.vt == VT_BSTR );
				COMTHROW( repobject->put_Name(var.bstrVal) );
			}
			else
			{
				if( repobjectitf == NULL )
					GetRepInterface(repobject, GetInterfaceGUID(), repobjectitf);

				ASSERT( repobjectitf != NULL );
				COMTHROW( put_RepProp(repobjectitf, GetAttrID(), var) );
			}
		}
	}
	COMCATCH(;)
}

void CCoreRepository::AddIDPair(IObjectCol *objcol, long i, std::vector<metaobjidpair_type> &idpairs)
{
	ASSERT( objcol != NULL );

	CComObjPtr<IRepositoryObject> repobj;
	COMTHROW( objcol->get_Item(PutInVariant(i), PutOut(repobj)) );
	ASSERT( repobj != NULL );

	CComVariant repobjid;
	COMTHROW( repobj->get_ObjectID(PutOut(repobjid)) );

	bindata repobjid2;
	CopyTo(repobjid, repobjid2);

	ASSERT( repobjid2.size() == 20 );

	long index, localid;
	ReadOBJID(repobjid2, index, localid);

	idpairs.push_back(metaobjidpair_type());
	idpairs.back().metaid = index;
	idpairs.back().objid = localid;
}
