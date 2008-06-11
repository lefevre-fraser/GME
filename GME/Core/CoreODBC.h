
#ifndef MGA_COREODBC_H
#define MGA_COREODBC_H

#include <fstream>//fstream.h
#include <list>//slist
#include <hash_map>
#include <map>

#include "sql.h"
#include "sqlext.h"


#define E_ODBC E_BINFILE   // should be moved to commonerror or rather to core.idl


// sqlstring
namespace std
{
class sqlstring : public string {
public:
	sqlstring() { ; }
	sqlstring(const string a) : string(a) {; } 
	sqlstring(const sqlstring &a): string(a) {; }
	sqlstring(const BSTR a);
	sqlstring(const char *a): string(a) {; }
	sqlstring(const SQLCHAR *a): string((char *)a) {; };
	const sqlstring &format(char *templ, const sqlstring &p1);
	const sqlstring &format(char *templ, const sqlstring &p1, const sqlstring &p2);
		operator SQLCHAR *() const { return (SQLCHAR *)c_str(); }  // const override
	operator string() { return *(string *)this; }
};
};


// --------------------------- CCoreODBC

class ATL_NO_VTABLE CCoreODBC : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ICoreStorage, &IID_ICoreStorage, &LIBID_CORELib>,
	public ISupportErrorInfoImpl<&IID_ICoreStorage>,
	public CComCoClass<CCoreODBC, &CLSID_CoreODBC>
{
	SQLHDBC hdbc;
	SQLHSTMT hstmt;

public:
	CCoreODBC();
	~CCoreODBC();

BEGIN_COM_MAP(CCoreODBC)
	COM_INTERFACE_ENTRY(ICoreStorage)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

DECLARE_REGISTRY_RESOURCEID(IDR_COREODBC)

// ------- MetaProject

public:
	typedef std::list< CComObjPtr<ICoreMetaAttribute> > attrlist;//slist
	typedef std::map<attrid_type, attrlist > pratype;
	typedef std::map<attrid_type, attrlist >::iterator praiterator;
	pratype ptrrevattrs;
	CComObjPtr<ICoreMetaProject> metaproject;
	bindata metaprojectid;

	STDMETHODIMP get_MetaProject(ICoreMetaProject **p);
	STDMETHODIMP put_MetaProject(ICoreMetaProject *p);

	void OpenMetaProject();
	void CloseMetaProject() NOTHROW;

// ------- MetaObject

public:
	CComObjPtr<ICoreMetaObject> metaobject;
	metaid_type metaid;

	STDMETHODIMP get_MetaObject(ICoreMetaObject **p);
	STDMETHODIMP put_MetaObject(ICoreMetaObject *p);

	STDMETHODIMP get_MetaID(metaid_type *p);
	STDMETHODIMP put_MetaID(metaid_type p);

	void OpenMetaObject();
	void CloseMetaObject() NOTHROW;

// ------- MetaAttribute

public:
	CComObjPtr<ICoreMetaAttribute> metaattribute;
	attrid_type attrid;

	STDMETHODIMP get_MetaAttribute(ICoreMetaAttribute **p);
	STDMETHODIMP put_MetaAttribute(ICoreMetaAttribute *p);

	STDMETHODIMP get_AttrID(attrid_type *p);
	STDMETHODIMP put_AttrID(attrid_type p);

	void OpenMetaAttribute();
	void CloseMetaAttribute() NOTHROW;

// ------- Attribute

public:
	STDMETHODIMP get_AttributeValue(VARIANT *p);
	STDMETHODIMP put_AttributeValue(VARIANT p);

// ------- Object

public:
	SQLINTEGER opened_object;

public:
	STDMETHODIMP OpenObject(objid_type objid);
	STDMETHODIMP CreateObject(objid_type *objid);
	STDMETHODIMP CloseObject() NOTHROW;

	STDMETHODIMP DeleteObject();
	STDMETHODIMP LockObject();

// ------- Project

public:
	std::sqlstring connstr;
	bool read_only;
	bool intrans;
	bool modified;

	bool IsOpened() const { return !connstr.empty(); }
	bool InTransaction() const { return intrans; }

	void CancelProject() NOTHROW;
	void OpenODBC(BSTR conn, bool);

public:
	STDMETHODIMP OpenProject(BSTR connection, VARIANT_BOOL *ro_mode);
	STDMETHODIMP CreateProject(BSTR connection);
	STDMETHODIMP CloseProject( VARIANT_BOOL abort = VARIANT_FALSE) NOTHROW;
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
};

#endif//MGA_COREODBC_H
