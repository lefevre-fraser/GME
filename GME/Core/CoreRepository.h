
#ifndef MGA_COREREPOSITORY_H
#define MGA_COREREPOSITORY_H

#include "repapi.h"

#include <hash_map>

// --------------------------- CCoreRepository

class ATL_NO_VTABLE CCoreRepository : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ICoreStorage, &IID_ICoreStorage, &LIBID_CORELib>,
	public ISupportErrorInfoImpl<&IID_ICoreStorage>,
	public CComCoClass<CCoreRepository, &CLSID_CoreRepository>
{
public:
	CCoreRepository();
	~CCoreRepository();

BEGIN_COM_MAP(CCoreRepository)
	COM_INTERFACE_ENTRY(ICoreStorage)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

DECLARE_REGISTRY_RESOURCEID(IDR_COREREPOSITORY)

// ------- MetaProject

public:
	CComObjPtr<ICoreMetaProject> metaproject;
	bindata metaprojectid;

	STDMETHODIMP get_MetaProject(ICoreMetaProject **p);
	STDMETHODIMP put_MetaProject(ICoreMetaProject *p);

	void OpenMetaProject();
	void CloseMetaProject() NOTHROW;

	std::string GetProjectToken();

// ------- MetaObject

public:
	CComObjPtr<ICoreMetaObject> metaobject;

	STDMETHODIMP get_MetaObject(ICoreMetaObject **p);
	STDMETHODIMP put_MetaObject(ICoreMetaObject *p);

	STDMETHODIMP get_MetaID(metaid_type *p);
	STDMETHODIMP put_MetaID(metaid_type p);

	void OpenMetaObject() { };
	void CloseMetaObject() NOTHROW;

	std::string GetObjectToken();
	metaid_type GetMetaID() { metaid_type a; COMTHROW( get_MetaID(&a) ); return a; }

// ------- MetaAttribute

public:
	CComObjPtr<ICoreMetaAttribute> metaattribute;

	STDMETHODIMP get_MetaAttribute(ICoreMetaAttribute **p);
	STDMETHODIMP put_MetaAttribute(ICoreMetaAttribute *p);

	STDMETHODIMP get_AttrID(attrid_type *p);
	STDMETHODIMP put_AttrID(attrid_type p);

	void OpenMetaAttribute() { };
	void CloseMetaAttribute() NOTHROW;

	attrid_type GetAttrID(ICoreMetaAttribute *p = NULL);
	valtype_type GetValType(ICoreMetaAttribute *p = NULL);
	long GetMaxSize(ICoreMetaAttribute *p = NULL);
	attrid_type GetLockAttrID(ICoreMetaAttribute *p = NULL);
	std::string GetToken(ICoreMetaAttribute *p = NULL);

// ------- GUID and OBJID

public:
	GUID GetGUID(short cat, long index) NOTHROW;
	OBJID GetOBJID(long index, long localid) NOTHROW;

	void ReadGUID(const bindata &input, short &cat, long &index);
	void ReadOBJID(const bindata &input, long &index, long &localid);

// ------- Repository 

public:
	template<class T>
	void GetRepObject(const OBJID &objid, CComObjPtr<T> &repobj)
	{
		ASSERT( repobj == NULL );
		CComObjPtr<IRepositoryObject> repobj2;

		ASSERT( repository != NULL );
		COMTHROW( repository->get_Object(PutInVariant(objid), PutOut(repobj2)) );
		ASSERT( repobj2 != NULL );

		COMTHROW( ::QueryInterface(repobj2, repobj) );
		ASSERT( repobj != NULL );
	}

	template<>
	void GetRepObject(const OBJID &objid, CComObjPtr<IRepositoryObject> &repobj)
	{
		ASSERT( repobj == NULL );

		COMTHROW( repository->get_Object(PutInVariant(objid), PutOut(repobj)) );
		ASSERT( repobj != NULL );
	}

	void GetRepInterface(IRepositoryItem *repobj, const GUID &guid, CComObjPtr<IDispatch> &ret);

// ------- TypeLib

public:
	CComObjPtr<IReposTypeLib> reptypelib;
	CComObjPtr<IInterfaceDef> repdispatchdef;

public:
	std::string GetTypeLibName() { return std::string("MGA ") + GetProjectToken() + " Type Information Model"; }
	GUID GetTypeLibGUID() { return GetGUID(0,0); }
	OBJID GetTypeLibOBJID() { return GetOBJID(0,0); }

	void CreateTypeLib();

// ------- ClassDef

public:
	CComObjPtr<IClassDef> repclassdef;
	CComObjPtr<IInterfaceDef> repinterfacedef;

public:
	std::string GetClassName() { return GetObjectToken(); }
	GUID GetClassGUID() { return GetGUID(0, GetMetaID()); }
	OBJID GetClassOBJID() { return GetOBJID(0, GetMetaID()); }

	std::string GetInterfaceName() { return std::string("I") + GetObjectToken(); }
	GUID GetInterfaceGUID() { return GetGUID(1, GetMetaID()); }

	void CreateClassDef();

// ------- PropertyDef

public:
	std::string GetPropertyName() NOTHROW { return GetToken(); }
	void CheckIsEqual(ICoreMetaAttribute *p, ICoreMetaAttribute *q);

	void CreatePropertyDef();

// ------- CollDefs

public:
	typedef struct colldef_type
	{
		attrid_type attrid;
		CComObjPtr<ICoreMetaAttribute> metaattribute;
		CComObjPtr<IInterfaceDef> interfacedef;
	} colldef_type;

	typedef std::list<colldef_type> colldefs_type;//slist
	typedef colldefs_type::iterator colldefs_iterator;

	colldefs_type colldefs;

public:
	std::string GetCollInterfaceName(ICoreMetaAttribute *metaaattribute);
	GUID GetCollInterfaceGUID(ICoreMetaAttribute *metaattribute)
		{ return GetGUID(2, GetAttrID(metaattribute)); }
	std::string GetCollRelationshipName(ICoreMetaAttribute *pointer, ICoreMetaAttribute *collection)
		{ return GetToken(collection) + " - " + GetToken(pointer); }

	colldefs_iterator FindCollDef(attrid_type attrid) NOTHROW;
	IInterfaceDef *GetCollInterfaceDef(ICoreMetaAttribute *metaattribute);
	void CreateCollRelationshipDef(colldef_type &pointer, colldef_type &collection);

// ------- Project

public:
	CComObjPtr<IRepository> repository;
	CComObjPtr<IRepositoryTransaction> reptransaction;

private:
	std::string connstr;
public:
	void GetConnUserPswd(std::string &connection, 
		std::string &conn, std::string &user, std::string &pswd);

	STDMETHODIMP OpenProject(BSTR connection, VARIANT_BOOL *mode);
	STDMETHODIMP CreateProject(BSTR connection);
	STDMETHODIMP CloseProject(VARIANT_BOOL abort = VARIANT_FALSE) NOTHROW;
	STDMETHODIMP SaveProject(BSTR connection, VARIANT_BOOL)  { 
		if(connection && !(CComBSTR(connection) == connstr.c_str())) {
			return E_INVALID_USAGE;
		}
		return S_OK; 
	}
	STDMETHODIMP DeleteProject() { return E_NOTIMPL; }

	STDMETHODIMP BeginTransaction();
	STDMETHODIMP CommitTransaction();
	STDMETHODIMP AbortTransaction();

	STDMETHODIMP get_StorageType(long *p);

// ------- ObjID

public:
	struct objid_gen_type
	{
		objid_gen_type() : next(OBJID_NONE) { }
		objid_gen_type(const objid_gen_type &a) : next(a.next), returned(a.returned) { }

		objid_type next;				// OBJID_NONE if not loaded
		std::vector<objid_type> returned;
	};

	typedef std::hash_map< metaid_type, objid_gen_type, std::hash<metaid_type>,
		std::equal_to<metaid_type> > objid_gens_type;
	typedef objid_gens_type::iterator objid_gens_iterator;

	objid_gens_type start_gens;
	objid_gens_type objid_gens;

	void ObjID_BeginTransaction() NOTHROW;
	void ObjID_CommitTransaction();
	void ObjID_AbortTransaction() NOTHROW { objid_gens = start_gens; }
	void ObjID_CloseProject() NOTHROW { objid_gens.clear(); start_gens.clear(); }

	objid_type ObjID_GetNext(metaid_type metaid);
	void ObjID_Return(metaid_type metaid, objid_type objid);

// ------- Object

public:
	CComObjPtr<IRepositoryObject> repobject;
	CComObjPtr<IDispatch> repobjectitf;
	objid_type opened_objid;

public:
	OBJID GetObjectOBJID(metaid_type metaid, objid_type objid) NOTHROW
		{  ASSERT( metaid != METAID_NONE ); return GetOBJID(metaid, objid); }

	STDMETHODIMP OpenObject(objid_type objid);
	STDMETHODIMP CreateObject(objid_type *objid);
	STDMETHODIMP CloseObject() NOTHROW;

	STDMETHODIMP DeleteObject();
	STDMETHODIMP LockObject();

// ------- Attribute

public:
	void AddIDPair(IObjectCol *objcol, long index, std::vector<metaobjidpair_type> &idpairs);

	STDMETHODIMP get_AttributeValue(VARIANT *p);
	STDMETHODIMP put_AttributeValue(VARIANT p);
};

#endif//MGA_COREREPOSITORY_H
