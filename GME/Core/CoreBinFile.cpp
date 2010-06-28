
#include "stdafx.h"
#include "CoreBinFile.h"
#include "CommonCollection.h"
#include "..\Mga\MgaGeneric.h"


/*
	examples:

		MGA=D:\Data\metamodel.mga
*/

// --------------------------- BinAttr

BinAttrBase *BinAttrBase::Create(valtype_type valtype)
{
	ASSERT( valtype != VALTYPE_NONE );

	BinAttrBase *binattr = NULL;

	switch(valtype)
	{
	case VALTYPE_LONG:
		binattr = new BinAttr<VALTYPE_LONG>;
		break;

	case VALTYPE_STRING:
		binattr = new BinAttr<VALTYPE_STRING>;
		break;

	case VALTYPE_BINARY:
		binattr = new BinAttr<VALTYPE_BINARY>;
		break;

	case VALTYPE_LOCK:
		binattr = new BinAttr<VALTYPE_LOCK>;
		break;

	case VALTYPE_POINTER:
		binattr = new BinAttr<VALTYPE_POINTER>;
		break;

	case VALTYPE_COLLECTION:
		binattr = new BinAttr<VALTYPE_COLLECTION>;
		break;

	case VALTYPE_REAL:
		binattr = new BinAttr<VALTYPE_REAL>;
		break;

	default:
		HR_THROW(E_METAPROJECT);
	}

	if( binattr == NULL )
		HR_THROW(E_OUTOFMEMORY);

	return binattr;
};

// --------------------------- BinObject
void getMeAGuid( long *p_l1, long *p_l2, long *p_l3, long *p_l4)
{
	GUID t_guid = GUID_NULL;
	COMTHROW(CoCreateGuid(&t_guid));
		
	ASSERT(t_guid != GUID_NULL);
	//char buff[39];
	//sprintf( buff, "{%08lX-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X}",
	//	t_guid.Data1, t_guid.Data2, t_guid.Data3,
	//	t_guid.Data4[0], t_guid.Data4[1], t_guid.Data4[2], t_guid.Data4[3],
	//	t_guid.Data4[4], t_guid.Data4[5], t_guid.Data4[6], t_guid.Data4[7]);

	// thus replace the old guid with a new one
	*p_l1 = t_guid.Data1; // Data1: 32 b, Data2, Data 3: 16 b, Data4: 64 bit
	*p_l2 = (t_guid.Data2 << 16) + t_guid.Data3;
	*p_l3 = (((((t_guid.Data4[0] << 8) + t_guid.Data4[1]) << 8) + t_guid.Data4[2]) << 8) + t_guid.Data4[3];
	*p_l4 = (((((t_guid.Data4[4] << 8) + t_guid.Data4[5]) << 8) + t_guid.Data4[6]) << 8) + t_guid.Data4[7];
}

bool BinObject::HasGuidAndStatAttributes( bool* p_guidFound, bool* p_statusFound)
{
	int a1( 0), a2( 0), a3( 0), a4( 0);

	binattrs_iterator i = binattrs.begin();
	binattrs_iterator e = binattrs.end();
	while( i != e)
	{
		switch( (*i)->attrid)
		{
			case ATTRID_GUID1: ++a1;break;
			case ATTRID_GUID2: ++a2;break;
			case ATTRID_GUID3: ++a3;break;
			case ATTRID_GUID4: ++a4;break;
			case ATTRID_FILESTATUS: *p_statusFound = true; break;
		};

		++i;
	}

	// a1, a2, a3, a4 should be equal & have the 0 or 1 value
	ASSERT( (a1 == 0 || a1 == 1) && a1 == a2 && a1 == a3 && a1 == a4);

	*p_guidFound = a1 && a2 && a3 && a4;
	return *p_guidFound;
}

// this method will create Guid attributes for mga objects
// loaded from MGA files saved with a previous version of gme
void BinObject::CreateGuidAttributes( CCoreBinFile* p_bf)
{
	// create a new guid
	CComVariant l1, l2, l3, l4;
	l4.vt = l3.vt = l2.vt = l1.vt = VT_I4;
	getMeAGuid( &l1.lVal, &l2.lVal, &l3.lVal, &l4.lVal);

	// create BinAttrs of LONG type
	BinAttrBase *binattr1 = BinAttrBase::Create( VALTYPE_LONG);
	BinAttrBase *binattr2 = BinAttrBase::Create( VALTYPE_LONG);
	BinAttrBase *binattr3 = BinAttrBase::Create( VALTYPE_LONG);
	BinAttrBase *binattr4 = BinAttrBase::Create( VALTYPE_LONG);

	// fill the only public field
	binattr1->attrid = ATTRID_GUID1;
	binattr2->attrid = ATTRID_GUID2;
	binattr3->attrid = ATTRID_GUID3;
	binattr4->attrid = ATTRID_GUID4;

	// set the values
	binattr1->Set( p_bf, l1);
	binattr2->Set( p_bf, l2);
	binattr3->Set( p_bf, l3);
	binattr4->Set( p_bf, l4);

	// insert the objects into the container
	// these objects will be destructed later 
	// by BinObject::DestroyAttributes
	binattrs.push_back( binattr1);
	binattrs.push_back( binattr2);
	binattrs.push_back( binattr3);
	binattrs.push_back( binattr4);
}

// this method will create a status attribute for mga objects
// loaded from MGA files saved with a previous version of gme
void BinObject::CreateStatusAttribute( CCoreBinFile* p_bf)
{
	// create BinAttr of LONG type
	BinAttrBase *binattr = BinAttrBase::Create( VALTYPE_LONG);

	// fill the only public field
	binattr->attrid = ATTRID_FILESTATUS;

	// set the value
	binattr->Set( p_bf, CComVariant( 0L));

	// insert the objects into the container
	// these objects will be destructed later 
	// by BinObject::DestroyAttributes
	binattrs.push_back( binattr);
}

void BinObject::CreateAttributes(ICoreMetaObject *metaobject)
{
	ASSERT( metaobject != NULL );
	ASSERT( binattrs.empty() );

	CComObjPtr<ICoreMetaAttributes> metaattributes;
	COMTHROW( metaobject->get_Attributes(PutOut(metaattributes)) );
	ASSERT( metaattributes != NULL );

	typedef std::vector< CComObjPtr<ICoreMetaAttribute> > metaattributelist_type;
	metaattributelist_type metaattributelist;
	GetAll<ICoreMetaAttributes, ICoreMetaAttribute>(metaattributes, metaattributelist);

	metaattributelist_type::iterator i = metaattributelist.begin();
	metaattributelist_type::iterator e = metaattributelist.end();
	while( i != e )
	{
		valtype_type valtype;
		COMTHROW( (*i)->get_ValueType(&valtype) );

		attrid_type attrid = ATTRID_NONE;
		COMTHROW( (*i)->get_AttrID(&attrid) );

		BinAttrBase *binattr = BinAttrBase::Create(valtype);
		ASSERT( binattr != NULL );

		ASSERT( attrid != ATTRID_NONE );
		binattr->attrid = attrid;

		binattrs.push_front(binattr);

		++i;
	}
}

void BinObject::DestroyAttributes()
{
	binattrs_iterator i = binattrs.begin();
	binattrs_iterator e = binattrs.end();
	while( i != e )
	{
		delete *i;
		++i;
	}

	binattrs.clear();
}

void BinObject::Read(CCoreBinFile *binfile)
{
	ASSERT( binfile != NULL );
	ASSERT( binattrs.empty() );

	valtype_type valtype;
	for(;;)
	{
		binfile->read(valtype);
		if( valtype == VALTYPE_NONE )
			break;

		BinAttrBase *binattr = BinAttrBase::Create(valtype);
		ASSERT( binattr != NULL );

		attrid_type attrid;
		binfile->read(attrid);
		ASSERT( attrid != ATTRID_NONE );

		binattr->attrid = attrid;

		binattr->Read(binfile);

		binattrs.push_front(binattr);
	}
};

void BinObject::Write(CCoreBinFile *binfile)
{
	ASSERT( binfile != NULL );
	ASSERT( !deleted );

	binattrs_iterator i = binattrs.begin();
	binattrs_iterator e = binattrs.end();
	while( i != e )
	{
		ASSERT( (*i)->GetValType() != VALTYPE_NONE );
		ASSERT( (*i)->attrid != ATTRID_NONE );

		binfile->write( (*i)->GetValType() );
		binfile->write( (*i)->attrid );
		(*i)->Write(binfile);

		++i;
	}

	binfile->write((valtype_type)VALTYPE_NONE);
}

bool BinObject::HasEmptyPointers() const
{
	if( deleted )
		return true;

	binattrs_type::const_iterator i = binattrs.begin();
	binattrs_type::const_iterator e = binattrs.end();
	while( i != e )
	{
		if( (*i)->GetValType() == VALTYPE_POINTER )
		{
			if( !( ( ( BinAttr<VALTYPE_POINTER>*)(*i))->isEmpty))
				return false;
		}
		++i;
	}

	return true;
}

objects_iterator no_object = objects_iterator(); // was: no_object(NULL, NULL);

// --------------------------- CCoreBinFile

CCoreBinFile::CCoreBinFile()
{
	metaid = METAID_NONE;
	attrid = ATTRID_NONE;
	opened_object = no_object;
	intrans = false;
	modified = false;
	isEmpty = true;
}

CCoreBinFile::~CCoreBinFile()
{
}

// ------- MetaProject

STDMETHODIMP CCoreBinFile::get_MetaProject(ICoreMetaProject **p)
{
	CHECK_OUT(p);

	CopyTo(metaproject, p);

	return S_OK;
}

STDMETHODIMP CCoreBinFile::put_MetaProject(ICoreMetaProject *p)
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

void CCoreBinFile::OpenMetaProject()
{
	ASSERT( metaprojectid.empty() );
	ASSERT( metaproject != NULL );

	CComVariant tmp;
	metaproject->get_GUID(PutOut(tmp));
	CopyTo(tmp, metaprojectid);
}

void CCoreBinFile::CloseMetaProject()
{
	if( IsOpened() && metaproject != NULL )
		CloseProject();

	CloseMetaObject();

	metaproject = NULL;
	metaprojectid.clear();
}

// ------- MetaObject

STDMETHODIMP CCoreBinFile::get_MetaObject(ICoreMetaObject **p)
{
	CHECK_OUT(p);

	CopyTo(metaobject, p);

	return S_OK;
}

STDMETHODIMP CCoreBinFile::put_MetaObject(ICoreMetaObject *p)
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

STDMETHODIMP CCoreBinFile::get_MetaID(metaid_type *p)
{
	CHECK_OUT(p);

	*p = metaid;

	return S_OK;
}

STDMETHODIMP CCoreBinFile::put_MetaID(metaid_type metaid)
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

void CCoreBinFile::OpenMetaObject()
{
	ASSERT( metaobject != NULL );

	COMTHROW( metaobject->get_MetaID(&metaid) );
}

void CCoreBinFile::CloseMetaObject()
{
	CloseObject();
	CloseMetaAttribute();
	metaobject = NULL;
	metaid = METAID_NONE;
}

// ------- MetaAttribute

STDMETHODIMP CCoreBinFile::get_MetaAttribute(ICoreMetaAttribute **p)
{
	CHECK_OUT(p);

	CopyTo(metaattribute, p);

	return S_OK;
}

STDMETHODIMP CCoreBinFile::put_MetaAttribute(ICoreMetaAttribute *p)
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
			COMTHROW( metaattribute->get_Object(PutOut(t)) );
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

STDMETHODIMP CCoreBinFile::get_AttrID(attrid_type *p)
{
	CHECK_OUT(p);

	if( metaattribute )
		return metaattribute->get_AttrID(p);

	*p = 0;
	return S_OK;
}

STDMETHODIMP CCoreBinFile::put_AttrID(attrid_type attrid)
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

void CCoreBinFile::OpenMetaAttribute()
{
	ASSERT( metaattribute != NULL );

	COMTHROW( metaattribute->get_AttrID(&attrid) );

	if( attrid == ATTRID_NONE )
		HR_THROW(E_METAPROJECT);
}

void CCoreBinFile::CloseMetaAttribute()
{
	metaattribute = NULL;
	attrid = ATTRID_NONE;
}

// ------- Ios

void CCoreBinFile::read(bindata &b)
{
	ASSERT( ifs.is_open() );

	int len;
	
	read(len);
	if(ifs.eof()) COMTHROW(E_FILEOPEN);
	ASSERT( len >= 0 );

	b.resize(len);
	if( len > 0 )
		ifs.read( (char *) &b[0], len);
}

void CCoreBinFile::read(CComBstrObj &ss)
{
	ASSERT( ifs.is_open() );

	std::string s;

	int len;

	read(len);
	ASSERT( len >= 0 );

	s.resize(len);
	if( len > 0 )
		ifs.read( (char *) &s[0], len);

	CopyTo(s, ss);
}

void CCoreBinFile::write(const bindata &b)
{
	ASSERT( ofs.is_open() );

	int len = b.size();
	ASSERT( len >= 0 );
	
	write(len);

	if( len > 0 )
		ofs.write( (const char *) &b[0], len);
}

void CCoreBinFile::write(const CComBstrObj &ss)
{
	ASSERT( ofs.is_open() );

	std::string s;
	CopyTo(ss, s);

	int len = s.size();
	ASSERT( len >= 0 );
	
	write(len);

	if( len > 0 )
		ofs.write( (const char *) &s[0], len);
}

// ------- Attribute

STDMETHODIMP CCoreBinFile::get_AttributeValue(VARIANT *p)
{
	CHECK_OUT(p);

	if( isEmpty || !InTransaction())
		COMRETURN(E_INVALID_USAGE);
	
	COMTRY
	{
		BinAttrBase *attr = opened_object->second.Find(attrid);
		ASSERT( attr != NULL );

		attr->Get(this, p);
	}
	COMCATCH(;)
}

STDMETHODIMP CCoreBinFile::put_AttributeValue(VARIANT p)
{
	if( isEmpty || !InTransaction())
		COMRETURN(E_INVALID_USAGE);
	
	COMTRY
	{
		BinAttrBase *attr = opened_object->second.Find(attrid);

		std::pair<BinAttrBase *const, CComVariant> r(attr, CComVariant());
		std::pair<undos_iterator, bool> t = undos.insert(r);

		if( t.second )
			attr->Get(this, PutOut(t.first->second));

		attr->Set(this, p);
	}
	COMCATCH(;)
}

// ------- Object

void CCoreBinFile::InitMaxObjIDs()
{
	ASSERT( metaproject != NULL );

	maxobjids.clear();

	CComObjPtr<ICoreMetaObjects> metaobjects;
	COMTHROW( metaproject->get_Objects(PutOut(metaobjects)) );
	ASSERT( metaobjects != NULL );

	typedef std::vector< CComObjPtr<ICoreMetaObject> > metaobjectlist_type;
	metaobjectlist_type metaobjectlist;
	GetAll<ICoreMetaObjects, ICoreMetaObject>(metaobjects, metaobjectlist);

	metaobjectlist_type::iterator i = metaobjectlist.begin();
	metaobjectlist_type::iterator e = metaobjectlist.end();
	while( i != e )
	{
		ASSERT( *i != NULL );

		metaid_type metaid = METAID_NONE;
		COMTHROW( (*i)->get_MetaID(&metaid) );
		ASSERT( metaid != METAID_NONE );

		ASSERT( maxobjids.find(metaid) == maxobjids.end() );
		maxobjids.insert( std::pair<const metaid_type, objid_type>(metaid, OBJID_NONE) );

		++i;
	}
}

STDMETHODIMP CCoreBinFile::OpenObject(objid_type objid)
{
	if( metaobject == NULL || !InTransaction() )
		COMRETURN(E_INVALID_USAGE);

	ASSERT( metaid != METAID_NONE );

	metaobjidpair_type idpair;
	idpair.metaid = metaid;
	idpair.objid = objid;

	if( !isEmpty &&
		metaobjidpair_equalkey()(opened_object->first, idpair) )
		return S_OK;

	COMTRY
	{
		opened_object = objects.find(idpair);
		isEmpty = false;
		if( (opened_object == objects.end()) ||
			opened_object->second.deleted )
		{
			opened_object = no_object;
			isEmpty = true;
			HR_THROW(E_NOTFOUND);
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CCoreBinFile::CreateObject(objid_type *objid)
{
	CHECK_OUT(objid);

	if( metaobject == NULL || !InTransaction() )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{
		modified = true;

		opened_object = no_object;
		isEmpty = true;

		ASSERT( metaid != METAID_NONE );

		maxobjids_iterator i = maxobjids.find(metaid);
		ASSERT( i != maxobjids.end() );
		
		metaobjidpair_type idpair;
		idpair.metaid = metaid;
		idpair.objid = ++(i->second);

		ASSERT( metaobject != NULL );

		std::pair<objects_iterator, bool> t = objects.insert(
			objects_type::value_type(idpair,BinObject()));
		ASSERT( t.second );

		t.first->second.deleted = false;
		t.first->second.CreateAttributes(metaobject);

		created_objects.push_front(t.first);

		opened_object = t.first;
		isEmpty = false;
		*objid = idpair.objid;
	}
	COMCATCH(;)
}

STDMETHODIMP CCoreBinFile::CloseObject()
{
	opened_object = no_object;
	isEmpty =  true;
	return S_OK;
}

STDMETHODIMP CCoreBinFile::LockObject()
{
	if( isEmpty || !InTransaction())
		COMRETURN(E_INVALID_USAGE);

	return S_OK;
}

STDMETHODIMP CCoreBinFile::DeleteObject()
{
	if( isEmpty || !InTransaction())
		COMRETURN(E_INVALID_USAGE);

	ASSERT( metaobject != NULL );

	ASSERT( opened_object->second.deleted == false );

	modified = true;

	deleted_objects.push_front(opened_object);

	opened_object->second.deleted = true;
	opened_object = no_object;
	isEmpty = true;

	return S_OK;
}

// ------- Project

void CCoreBinFile::CancelProject()
{
	CloseMetaObject();

	if( ifs.is_open() )
		ifs.close();

	if( ofs.is_open() )
		ofs.close();

	filename.clear();
	intrans = false;
	modified = false;

	opened_object = no_object;
	isEmpty = true;
	deleted_objects.clear();
	created_objects.clear();
	maxobjids.clear();
	resolvelist.clear();
	objects.clear();
}

void CCoreBinFile::SaveProject()
{
	ASSERT( !ofs.is_open() );
	ASSERT( metaprojectid.size() == 16 );

	ofs.clear();
	ofs.open(filename.c_str(), std::ios::out | std::ios::binary);
	if( ofs.fail() || !ofs.is_open() ) {
		ofs.close();
		ofs.clear();
		HR_THROW(E_FILEOPEN);
	}

	write(metaprojectid);

	objects_iterator i = objects.begin();
	objects_iterator e = objects.end();
	while( i != e )
	{
		ASSERT( (*i).first.metaid != METAID_NONE );
		ASSERT( (*i).first.objid != OBJID_NONE );

		if( ((*i).first.metaid == METAID_ROOT && (*i).first.objid == OBJID_ROOT)
			|| !(*i).second.HasEmptyPointers() )
		{
			write( (metaid_type)(*i).first.metaid );
			write( (objid_type)(*i).first.objid );

			(*i).second.Write(this);
		}

		++i;
	}

	write((metaid_type)METAID_NONE);

	if( ofs.fail() )
		HR_THROW(E_FILEOPEN);

	ofs.close();
}

void CCoreBinFile::LoadProject()
{
	InitMaxObjIDs();

	ifs.open(filename.c_str(), std::ios::in | std::ios::binary);//previously ios::nocreate had been used but no file is created if opened for read only
	if( ifs.fail() )
		HR_THROW(E_FILEOPEN);

	bindata guid;
	read(guid);

	if( !(guid == metaprojectid) )
		HR_THROW(E_PROJECT_MISMATCH);

	ASSERT( resolvelist.empty() );

	for(;;)
	{
		metaid_type metaid;
		read(metaid);
		if( metaid == METAID_NONE )
			break;

		objid_type objid;
		read(objid);
		ASSERT( objid != OBJID_NONE );

		maxobjids_iterator i = maxobjids.find(metaid);
		ASSERT( i != maxobjids.end() );

		if( i->second < objid )
			i->second = objid;

		metaobjidpair_type idpair;
		idpair.metaid = metaid;
		idpair.objid = objid;

		std::pair<objects_iterator, bool> t = objects.insert(
			objects_type::value_type(idpair,BinObject()));
		ASSERT( t.second );

		opened_object = t.first;
		isEmpty = false;
		opened_object->second.deleted = false;
		opened_object->second.Read(this);
		
		// if the object read is folder or fco and it does NOT have guid attributes (old version mga file)
		if( metaid >= DTID_MODEL && metaid <= DTID_FOLDER)	// 101 .. 106
		{
			bool stat_found( false), guid_found( false);

			opened_object->second.HasGuidAndStatAttributes( &guid_found, &stat_found);

			if( !guid_found) // we will create guid attributes for it
				opened_object->second.CreateGuidAttributes( this);

			if( !stat_found && ( metaid == DTID_MODEL || metaid == DTID_FOLDER)) // we will create status attribute for M and F
				opened_object->second.CreateStatusAttribute( this);
		}
	}

	resolvelist_type::iterator i = resolvelist.begin();
	resolvelist_type::iterator e = resolvelist.end();
	while( i != e )
	{
		opened_object = i->obj;
		isEmpty = false;
		
		// ASSERT( !isEmpty ); 

		BinAttrBase *base = opened_object->second.Find(i->attrid);
		ASSERT( base != NULL );

		ASSERT( base->GetValType() == VALTYPE_POINTER );

		objects_iterator j = objects.find( i->idpair );
		if( j == objects.end() )
			HR_THROW(E_BINFILE);

		((BinAttr<VALTYPE_POINTER>*)base)->Set(this, j);

		++i;
	}

	opened_object = no_object;
	isEmpty = true;
	resolvelist.clear();

	ifs.close();
	ofs.clear();
	ofs.open(filename.c_str(), std::ios::app | std::ios::binary);
	read_only = false;
	if( ofs.fail() || !ofs.is_open() )	read_only = true;
	else ofs.close();
}

STDMETHODIMP CCoreBinFile::OpenProject(BSTR connection, VARIANT_BOOL *ro_mode) {
	if( IsOpened() || metaproject == NULL )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{
		CopyTo(connection, filename);
		if( !(std::string(filename, 0, 4) == "MGA=") )
			HR_THROW(E_INVALID_USAGE);

		filename.erase(0, 4);

		LoadProject();


		modified = false;
		if(ro_mode) *ro_mode = read_only ? VARIANT_TRUE : VARIANT_FALSE;

		ASSERT( IsOpened() );
	}
	COMCATCH( CancelProject(); )
}

STDMETHODIMP CCoreBinFile::CreateProject(BSTR connection)
{
	if( IsOpened() || metaproject == NULL )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{
		CopyTo(connection, filename);
		if( !(std::string(filename, 0, 4) == "MGA=") )
			HR_THROW(E_INVALID_USAGE);

		filename.erase(0, 4);

		InitMaxObjIDs();

		CComObjPtr<ICoreMetaObject> mo;
		COMTHROW( metaproject->get_Object(METAID_ROOT, PutOut(mo)) );
		ASSERT( mo != NULL );

		maxobjids_iterator i = maxobjids.find(METAID_ROOT);
		i->second = OBJID_ROOT;
		
		metaobjidpair_type idpair;
		idpair.metaid = METAID_ROOT;
		idpair.objid = OBJID_ROOT;

		std::pair<objects_iterator, bool> t = objects.insert(
			objects_type::value_type(idpair,BinObject()));
		ASSERT( t.second );

		t.first->second.deleted = false;
		t.first->second.CreateAttributes(mo);

		if(filename.empty()) filename = ".";
		else SaveProject();

		modified = false;

		ASSERT( IsOpened() );
	}
	COMCATCH( CancelProject(); )
}

STDMETHODIMP CCoreBinFile::SaveProject(BSTR connection, VARIANT_BOOL keepoldname = VARIANT_TRUE) 
{
	std::string origfname = filename;
	COMTRY
	{
		std::string fn;
		CopyTo(connection, fn);

		if( !fn.empty() ) 
		{
			if( !(std::string(fn, 0, 4) == "MGA=") )
				HR_THROW(E_INVALID_USAGE);

			fn.erase(0, 4);
			filename = fn;
			if(filename.empty()) filename = ".";
		}
		if(filename == ".") COMTHROW(E_NAMEMISSING);
		SaveProject();
		if(keepoldname == VARIANT_TRUE) filename = origfname;
	}
	COMCATCH( filename = origfname;)
}

STDMETHODIMP CCoreBinFile::CloseProject( VARIANT_BOOL abort) {
	if( !IsOpened() || metaproject == NULL )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{
		if( abort == VARIANT_FALSE && modified && !(filename == ".")) 
			SaveProject(NULL);

		ASSERT( IsOpened() );

		CancelProject();
	}
	COMCATCH(;)
}

STDMETHODIMP CCoreBinFile::BeginTransaction()
{
	if( !IsOpened() || InTransaction() )
		COMRETURN(E_INVALID_USAGE);

	ASSERT( deleted_objects.empty() );
	ASSERT( created_objects.empty() );

	intrans = true;

	return S_OK;
}

STDMETHODIMP CCoreBinFile::CommitTransaction()
{
	if( !InTransaction() )
		COMRETURN(E_INVALID_USAGE);

	ASSERT( IsOpened() );

	CloseObject();

	std::list<objects_iterator>::iterator i = deleted_objects.begin();//slist
	std::list<objects_iterator>::iterator e = deleted_objects.end();//slist
	while( i != e )
	{
		ASSERT( (*i)->second.deleted );

		objects.erase(*i);

		++i;
	}

	undos.clear();
	deleted_objects.clear();
	created_objects.clear();

	intrans = false;

	return S_OK;
}

STDMETHODIMP CCoreBinFile::AbortTransaction()
{
	if( !InTransaction() )
		COMRETURN(E_INVALID_USAGE);

	ASSERT( IsOpened() );

	CloseObject();

	undos_iterator j = undos.begin();
	undos_iterator f = undos.end();
	while( j != f )
	{
		j->first->Set(this, j->second);

		++j;
	}

	std::list<objects_iterator>::iterator i = deleted_objects.begin();//slist
	std::list<objects_iterator>::iterator e = deleted_objects.end();//slist
	while( i != e )
	{
		ASSERT( (*i)->second.deleted );

		(*i)->second.deleted = false;

		++i;
	}

	i = created_objects.begin();
	e = created_objects.end();
	while( i != e )
	{
		ASSERT( !(*i)->second.deleted );

		objects.erase(*i);

		++i;
	}

	undos.clear();
	deleted_objects.clear();
	created_objects.clear();

	intrans = false;

	return S_OK;
}

STDMETHODIMP CCoreBinFile::get_StorageType(long *p)
{
	CHECK_OUT(p);

	*p = 0;
	return S_OK;
}

// --------------------------- BinAttr<VALTYPE_POINTER>
//moved to the header file
//template<> 
//void BinAttr<VALTYPE_POINTER>::Get(CCoreBinFile *binfile, VARIANT *p) const
//{
//	if( a == no_object )
//	{
//		metaobjidpair_type idpair;
//		idpair.metaid = METAID_NONE;
//		idpair.objid = OBJID_NONE;
//		CopyTo(idpair, p);
//	}
//	else
//		CopyTo(a->first, p);
//}
//
//template<>
//void BinAttr<VALTYPE_POINTER>::Set(CCoreBinFile *binfile, objects_iterator b)
//{
//	ASSERT( binfile != NULL );
//	ASSERT( a == no_object );
//	ASSERT( b != no_object && b != binfile->objects.end() );
//
//	binfile->modified = true;
//
//	a = b;
//
//	ASSERT( binfile->opened_object->second.Find(attrid) == this );
//
//	BinAttrBase *base = a->second.Find(attrid + ATTRID_COLLECTION);
//	ASSERT( base != NULL );
//	
//	ASSERT( base->GetValType() == VALTYPE_COLLECTION );
//	std::vector<objects_iterator> &objs = ((BinAttr<VALTYPE_COLLECTION>*)base)->a;
//
//#ifdef DEBUG_CONTAINERS
//	std::vector<objects_iterator>::iterator i = find(objs.begin(), objs.end(), a);
//	ASSERT( i == objs.end() );
//#endif
//
//	objs.push_back(binfile->opened_object);
//}
//
//template<>
//void BinAttr<VALTYPE_POINTER>::Set(CCoreBinFile *binfile, VARIANT p)
//{
//	if( a != no_object )
//	{
//		BinAttrBase *base = a->second.Find(attrid + ATTRID_COLLECTION);
//		ASSERT( base != NULL );
//		
//		ASSERT( base->GetValType() == VALTYPE_COLLECTION );
//		std::vector<objects_iterator> &objs = ((BinAttr<VALTYPE_COLLECTION>*)base)->a;
//
//		ASSERT( binfile->opened_object->second.Find(attrid) == this );
//
//		std::vector<objects_iterator>::iterator i = std::find(objs.begin(), objs.end(), binfile->opened_object);
//		ASSERT( i != objs.end() );
//
//		objs.erase(i);
//	}
//
//	a = no_object;
//
//	metaobjidpair_type idpair;
//	CopyTo(p, idpair);
//
//	if( idpair.metaid == METAID_NONE )
//	{
//		ASSERT( idpair.objid == OBJID_NONE );
//	}
//	else
//	{
//		ASSERT( idpair.objid != OBJID_NONE );
//
//		Set(binfile, binfile->objects.find(idpair));
//	}
//}
//
//template<>
//void BinAttr<VALTYPE_POINTER>::Write(CCoreBinFile *binfile) const
//{
//	if( a == no_object )
//	{
//		binfile->write((metaid_type)METAID_NONE);
//	}
//	else
//	{
//		ASSERT( a->first.metaid != METAID_NONE );
//		ASSERT( a->first.objid != OBJID_NONE );
//
//		binfile->write((metaid_type)a->first.metaid);
//		binfile->write((objid_type)a->first.objid);
//	}
//}
//
//template<>
//void BinAttr<VALTYPE_POINTER>::Read(CCoreBinFile *binfile)
//{
//	ASSERT( a == no_object );
//
//	metaid_type metaid;
//	binfile->read(metaid);
//
//	if( metaid != METAID_NONE )
//	{
//		objid_type objid;
//		binfile->read(objid);
//
//		ASSERT( objid != OBJID_NONE );
//
//		binfile->resolvelist.push_front();
//		CCoreBinFile::resolve_type &b = binfile->resolvelist.front();
//
//		ASSERT( binfile->opened_object != no_object );
//
//		b.obj = binfile->opened_object;
//		b.attrid = attrid;
//		b.idpair.metaid = metaid;
//		b.idpair.objid = objid;
//	}
//}

// --------------------------- BinAttr<VALTYPE_COLLECTION>

//template<>
//void BinAttr<VALTYPE_COLLECTION>::Get(CCoreBinFile *binfile, VARIANT *p) const
//{
//	ASSERT( p != NULL && p->vt == VT_EMPTY );
//
//	std::vector<metaobjidpair_type> idpairs;
//
//	std::vector<objects_iterator>::const_iterator i = a.begin();
//	std::vector<objects_iterator>::const_iterator e = a.end();
//	while( i != e )
//	{
//		idpairs.push_back( (*i)->first );
//
//		++i;
//	}
//
//	CopyTo(idpairs, p);
//}
