
#include "stdafx.h"
#include <string>
#include "CoreODBC.h"
#include "CommonCollection.h"
#include "CommonMgaTrukk.h"
#include "ODBCss.h"
#include "stdio.h"

#define VISIBLE_POINTERS

#define SQLExecDirect(a, b, c) (AtlTrace((char *)(SQLCHAR *)b),AtlTrace("\n"),SQLExecDirect(a, b, c)) 

#define XDIM(x) (sizeof(x) / sizeof(*(x)))
/*
	examples:

		ODBC=GMEProject1
*/

// --------------------------- DIAGNOSTICS

SQLSMALLINT htype_lastused;
SQLHANDLE hval_lastused; 
#define LastUsedHandle(a, b) { htype_lastused = a, hval_lastused = b; }

void Nop() { ; }

void ErrGet(void) {		
   // Get the status records
		   SQLCHAR sqlstate[6], msg[SQL_MAX_MESSAGE_LENGTH];
		   SQLINTEGER nativeerror;
		   SQLSMALLINT msglen;
		   SQLRETURN rc2;
		   for(int i = 1; (rc2 = SQLGetDiagRec(htype_lastused, hval_lastused, i, sqlstate, &nativeerror,
			    msg, sizeof(msg), &msglen)) != SQL_NO_DATA; i++) {
			  AtlTrace("%s\n",msg);
		   }
}


void SQLTHROW(SQLRETURN sqlcall) { 
	if((sqlcall) != SQL_SUCCESS) {
		if((sqlcall) != SQL_SUCCESS_WITH_INFO) {
			ErrGet();
			ASSERT(false);
			HR_THROW(E_ODBC); 
		}
		else {
			AtlTrace("SQL_WITH_INFO \n");
			ErrGet();
		}	
	}
}

bool SQLTHROW_NODATA(SQLRETURN sqlcall) { 
		if(sqlcall == SQL_NO_DATA) return true;
		SQLTHROW(sqlcall);
		return false;
}


std::sqlstring tablename(ICoreMetaObject *m) {
	CComBSTR bb;
	COMTHROW(m->get_Token(&bb));
	return bb.m_str;
}

std::sqlstring colname(ICoreMetaAttribute *m) {
	CComBSTR bb;
	COMTHROW(m->get_Token(&bb));
	return bb.m_str;
}

// --------------------------- ODBCEnv


class ODBCenv {
    SQLHENV     m_henv;
public: 	
	ODBCenv() {
	    if(SQLAllocHandle(SQL_HANDLE_ENV, NULL, &m_henv) == SQL_SUCCESS) {
		    SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (void*) SQL_OV_ODBC3,
				SQL_IS_INTEGER);
        }
	}
    
	~ODBCenv() { if(*this) { SQLFreeHandle(SQL_HANDLE_ENV, m_henv); } }
	
	operator bool() const { return m_henv != SQL_NULL_HENV; }
	operator const SQLHENV&() const { return m_henv; } 
}; 
	
	
static ODBCenv env;




// --------------------------- CCoreODBC

CCoreODBC::CCoreODBC()
{
	metaid = METAID_NONE;
	attrid = ATTRID_NONE;
	opened_object = OBJID_NONE;
	intrans = false;
	modified = false;	
	hstmt = SQL_NULL_HSTMT;
	hdbc = SQL_NULL_HDBC;
}

CCoreODBC::~CCoreODBC()
{
	ASSERT(!IsOpened());
	CancelProject();
}

// ------- MetaProject

STDMETHODIMP CCoreODBC::get_MetaProject(ICoreMetaProject **p)
{
	CHECK_OUT(p);

	CopyTo(metaproject, p);

	return S_OK;
}

STDMETHODIMP CCoreODBC::put_MetaProject(ICoreMetaProject *p)
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

void CCoreODBC::OpenMetaProject()
{
	ASSERT( metaprojectid.empty() );
	ASSERT( metaproject != NULL );

	CComVariant tmp;
	metaproject->get_GUID(PutOut(tmp));
	CopyTo(tmp, metaprojectid);
}

void CCoreODBC::CloseMetaProject()
{
	CloseProject();

	CloseMetaObject();

	metaproject = NULL;
	metaprojectid.clear();
}

// ------- MetaObject

STDMETHODIMP CCoreODBC::get_MetaObject(ICoreMetaObject **p)
{
	CHECK_OUT(p);

	CopyTo(metaobject, p);

	return S_OK;
}

STDMETHODIMP CCoreODBC::put_MetaObject(ICoreMetaObject *p)
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

STDMETHODIMP CCoreODBC::get_MetaID(metaid_type *p)
{
	CHECK_OUT(p);

	*p = metaid;

	return S_OK;
}

STDMETHODIMP CCoreODBC::put_MetaID(metaid_type metaid)
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

void CCoreODBC::OpenMetaObject()
{
	ASSERT( metaobject != NULL );

	COMTHROW( metaobject->get_MetaID(&metaid) );
}

void CCoreODBC::CloseMetaObject()
{
	CloseObject();
	CloseMetaAttribute();
	metaobject = NULL;
	metaid = METAID_NONE;
}

// ------- MetaAttribute

STDMETHODIMP CCoreODBC::get_MetaAttribute(ICoreMetaAttribute **p)
{
	CHECK_OUT(p);

	CopyTo(metaattribute, p);

	return S_OK;
}

STDMETHODIMP CCoreODBC::put_MetaAttribute(ICoreMetaAttribute *p)
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

STDMETHODIMP CCoreODBC::get_AttrID(attrid_type *p)
{
	CHECK_OUT(p);

	if( metaattribute )
		return metaattribute->get_AttrID(p);

	*p = 0;
	return S_OK;
}

STDMETHODIMP CCoreODBC::put_AttrID(attrid_type attrid)
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

void CCoreODBC::OpenMetaAttribute()
{
	ASSERT( metaattribute != NULL );

	COMTHROW( metaattribute->get_AttrID(&attrid) );

	if( attrid == ATTRID_NONE )
		HR_THROW(E_METAPROJECT);
}

void CCoreODBC::CloseMetaAttribute()
{
	metaattribute = NULL;
	attrid = ATTRID_NONE;
}

// ------- Attribute

STDMETHODIMP CCoreODBC::get_AttributeValue(VARIANT *p)
{
	CHECK_OUT(p);

	if( metaattribute == NULL || opened_object == OBJID_NONE || !InTransaction() )
		COMRETURN(E_INVALID_USAGE);
	
	COMTRY {
	  valtype_type vt;
	  COMTHROW(metaattribute->get_ValueType(&vt));
	  if(vt == VALTYPE_COLLECTION) {
		attrid_type mi;
		COMTHROW(metaattribute->get_AttrID(&mi));
		praiterator pp = ptrrevattrs.find(mi-ATTRID_COLLECTION);
		ASSERT(pp != ptrrevattrs.end());
		metaobjidpair_type kk;
		metaid_type m;
		COMTHROW(metaobject->get_MetaID(&m));
		kk.metaid = m;
		kk.objid = opened_object;
#ifdef VISIBLE_POINTERS
		kk.metaid = kk.objid + kk.metaid * 10000;
		kk.objid = 0;
#endif
		SQLTHROW(SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_UBIGINT, SQL_BIGINT, 20, 0,
                 &kk, 0, 0));
		std::vector<metaobjidpair_type> idpairs;
		for(attrlist::iterator vv = pp->second.begin(); vv != pp->second.end(); vv++) {
			CComPtr<ICoreMetaObject> mo;
			COMTHROW((*vv)->get_Object(&mo));
			std::sqlstring oblister;
			oblister.format("SELECT objid FROM \"%s\" WHERE \"%s\" = ?", tablename(mo), colname(*vv));
			SQLTHROW(SQLExecDirect(hstmt, oblister, SQL_NTS));

			metaobjidpair_type pp;
			SQLTHROW(SQLBindCol(hstmt, 1, SQL_C_ULONG, &pp.objid, 0, 0));
			while(!SQLTHROW_NODATA(SQLFetch(hstmt))) {
				metaid_type m;
				COMTHROW(mo->get_MetaID(&m));
				pp.metaid = m;
				idpairs.push_back(pp);
			}
			SQLTHROW(SQLFreeStmt(hstmt, SQL_CLOSE));
			SQLTHROW(SQLFreeStmt(hstmt, SQL_UNBIND));
		}
		CopyTo(idpairs, p);
	  }
	  else {
	    CComVariant res;
		SQLTHROW(SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 10, 0,
                  &opened_object, 0, 0));
		std::sqlstring oblocate;
		oblocate.format("SELECT \"%s\" FROM \"%s\" WITH (UPDLOCK) WHERE objid = ?", colname(metaattribute), tablename(metaobject));
		SQLTHROW(SQLExecDirect(hstmt, oblocate, SQL_NTS));

		if(SQLTHROW_NODATA(SQLFetch(hstmt)) ) {
				HR_THROW(E_NOTFOUND);   // not found
		}
		switch(vt) {
			case VALTYPE_LOCK:
				res.vt = VT_I2;
				SQLTHROW(SQLGetData(hstmt, 1, SQL_C_SSHORT, &res.iVal, 0, 0));
				break;
			case VALTYPE_LONG:
				res.vt = VT_I4;
				SQLTHROW(SQLGetData(hstmt, 1, SQL_C_SLONG, &res.lVal, 0, 0));
				break;
			case VALTYPE_REAL:
				res.vt = VT_R8;
				SQLTHROW(SQLGetData(hstmt, 1, SQL_C_DOUBLE, &res.dblVal, 0, 0));
				break;
			case VALTYPE_STRING:
				{
					SQLCHAR stringv[1000];
					SQLINTEGER stringlen;
					SQLTHROW(SQLGetData(hstmt, 1, SQL_C_CHAR, stringv, sizeof(stringv), &stringlen));
					stringv[stringlen] = '\0';
					CComBSTR nn((char *)stringv);
					res.vt = VT_BSTR;
					res.bstrVal = nn.Detach();
				}
				break;
			case VALTYPE_BINARY:
				{
					SQLCHAR stringv[1000];
					SQLINTEGER stringlen;
					SQLTHROW(SQLGetData(hstmt, 1, SQL_C_BINARY, stringv, sizeof(stringv), &stringlen));
					if(stringlen == -1) stringlen = 0;
					CopyTo(stringv, stringv+stringlen, res);
				}
				break;
			case VALTYPE_POINTER:
				metaobjidpair_type idpair;

				SQLTHROW(SQLGetData(hstmt, 1, SQL_C_UBIGINT, &idpair, 0, 0));
#ifdef VISIBLE_POINTERS
		idpair.objid = idpair.metaid % 10000;
		idpair.metaid /= 10000;
#endif
				CopyTo(idpair,res);
				break;
		}
		if(!SQLTHROW_NODATA(SQLFetch(hstmt)) ) {
				HR_THROW(E_ODBC);   // multiple values
		}
		SQLTHROW(SQLFreeStmt(hstmt, SQL_CLOSE));
		res.Detach(p);
	  }
	}
	COMCATCH(ErrGet();)
}

STDMETHODIMP CCoreODBC::put_AttributeValue(VARIANT p) {
	if( metaattribute == NULL || opened_object == OBJID_NONE || !InTransaction() )
		COMRETURN(E_INVALID_USAGE);
	
	COMTRY {
	    valtype_type vvt;
		COMTHROW(metaattribute->get_ValueType(&vvt));
	
		if(vvt != VALTYPE_POINTER) {
			VARTYPE targettypes[] = { VT_EMPTY, VT_EMPTY, VT_EMPTY, VT_I2, VT_I4, VT_BSTR, VT_UI1|VT_ARRAY, VT_R8};
			ASSERT(vvt < XDIM(targettypes) && targettypes[vvt] != VT_EMPTY);
			CComVariant buf;
			if(p.vt == VT_EMPTY && p.vt != targettypes[vvt]) {
				ASSERT(p.vt != VT_EMPTY && p.vt != VT_NULL);
				COMTHROW(::VariantChangeType(&buf, &p, 0, targettypes[vvt]));
				p = buf;
			}
	    }
		SQLINTEGER slen;
		unsigned char buf[1000];
		metaobjidpair_type idpair;
		switch(vvt) {
			case VALTYPE_LOCK:
				SQLTHROW(SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_SMALLINT, 5, 0,
	                 &p.iVal, 0, 0));
				break;
			case VALTYPE_LONG:
				SQLTHROW(SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 10, 0,
	                 &p.lVal, 0, 0));
				break;
			case VALTYPE_REAL:
				SQLTHROW(SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_DOUBLE, SQL_FLOAT, 15, 0,
	                 &p.dblVal, 0, 0));
				break;
			case VALTYPE_STRING:
				{
					slen = ::SysStringLen(p.bstrVal);
					CopyTo(p.bstrVal, slen, (char *)buf, slen);
					SQLTHROW(SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 256, 0,
						 buf, 0, &slen));
				}
				break;
			case VALTYPE_BINARY:
				{
				slen = GetArrayLength(p);
				CopyTo(p, buf, buf+slen);
				SQLTHROW(SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, 256, 0,
	                 buf, 0, &slen));
				}
				break;
			case VALTYPE_POINTER:
				CopyTo(p, idpair);
#ifdef VISIBLE_POINTERS
		idpair.metaid = idpair.objid + idpair.metaid * 10000;
		idpair.objid = 0;
#endif
				SQLTHROW(SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_UBIGINT, SQL_BIGINT, 20, 0,
	                 &idpair, 0, 0));
				break;
		}
		
		
		SQLTHROW(SQLBindParameter(hstmt, 2, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 10, 0,
	                 &opened_object, 0, 0));
		std::sqlstring oblocate;
		oblocate.format("UPDATE \"%s\" SET \"%s\"=? WHERE objid = ?", tablename(metaobject), colname(metaattribute));
		SQLTHROW(SQLExecDirect(hstmt, oblocate, SQL_NTS));
		SQLINTEGER rc;
		SQLTHROW(SQLRowCount(hstmt, &rc));
		if(rc != 1) COMTHROW(E_NOTFOUND);
	}
	COMCATCH(ErrGet();)
}

//1. At Open: select *, for update......
//2. At Open: nothing, attr access: select


STDMETHODIMP CCoreODBC::OpenObject(objid_type objid)
{

	if( metaobject == NULL || !InTransaction() ) COMRETURN(E_INVALID_USAGE);
	COMTRY	{
		SQLTHROW(SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 10, 0,
                  &objid, 0, 0));
		std::sqlstring oblocate;
		oblocate.format("SELECT objid FROM \"%s\" WITH (UPDLOCK) WHERE objid = ?", tablename(metaobject));
		SQLTHROW(SQLExecDirect(hstmt, oblocate, SQL_NTS));

		if(SQLTHROW_NODATA(SQLFetch(hstmt)) ) {
				HR_THROW(E_NOTFOUND); // not found
		}
		if(!SQLTHROW_NODATA(SQLFetch(hstmt)) ) {
				HR_THROW(E_ODBC);   // multiple values
		}
		SQLTHROW(SQLFreeStmt(hstmt, SQL_CLOSE));
		opened_object = objid;
	}
	COMCATCH(ErrGet();)
}

STDMETHODIMP CCoreODBC::CreateObject(objid_type *objid)
{
	CHECK_OUT(objid);

	if( metaobject == NULL || !InTransaction() )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{
		modified = true;

		opened_object = OBJID_NONE;

		std::sqlstring obcreate;
		obcreate.format("INSERT INTO \"%s\" DEFAULT VALUES", tablename(metaobject));
		SQLTHROW(SQLExecDirect(hstmt, obcreate, SQL_NTS));

		std::sqlstring obgetid = "SELECT SCOPE_IDENTITY() AS [_SCI]";
		SQLTHROW(SQLExecDirect(hstmt, obgetid, SQL_NTS));
		
		SQLINTEGER obi;
		SQLTHROW(SQLFetch(hstmt));
		SQLTHROW(SQLGetData(hstmt, 1, SQL_C_SLONG, &obi, 0, NULL));
		*objid = obi;
		SQLTHROW(SQLFreeStmt(hstmt, SQL_CLOSE));

		opened_object = obi;
	} COMCATCH(ErrGet();)
}

STDMETHODIMP CCoreODBC::CloseObject()
{
	COMTRY {
		opened_object = OBJID_NONE;
	} COMCATCH(;)
	return S_OK;
}

STDMETHODIMP CCoreODBC::LockObject()
{
	if( opened_object == OBJID_NONE ||
		metaobject == NULL || 
		!InTransaction() ) COMRETURN(E_INVALID_USAGE);
	COMTRY	{
		SQLTHROW(SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 10, 0,
                  &opened_object, 0, 0));
		std::sqlstring oblocate;
		oblocate.format("SELECT objid FROM \"%s\" WITH (HOLDLOCK) WHERE objid = ?", tablename(metaobject));
		SQLTHROW(SQLExecDirect(hstmt, oblocate, SQL_NTS));

		if(SQLTHROW_NODATA(SQLFetch(hstmt)) ) {
				HR_THROW(E_NOTFOUND); // not found
		}
		if(!SQLTHROW_NODATA(SQLFetch(hstmt)) ) {
				HR_THROW(E_ODBC);   // multiple values
		}
		SQLTHROW(SQLFreeStmt(hstmt, SQL_CLOSE));
	}
	COMCATCH(ErrGet();)
	return S_OK;
}

STDMETHODIMP CCoreODBC::DeleteObject() {
	COMTRY	{
		SQLTHROW(SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 10, 0,
                  &opened_object, 0, 0));
		std::sqlstring obdelete;
		obdelete.format("DELETE \"%s\" WHERE objid = ?", tablename(metaobject));
		SQLTHROW(SQLExecDirect(hstmt, obdelete, SQL_NTS));
		opened_object = OBJID_NONE;
	} COMCATCH(ErrGet();)
	return S_OK;
}

// ------- Project

void CCoreODBC::CancelProject()
{
	CloseMetaObject();

	intrans = false;
	modified = false;

	connstr.clear();
	opened_object = OBJID_NONE;

	if(hstmt != SQL_NULL_HSTMT) {
		SQLFreeHandle(SQL_HANDLE_STMT, hstmt);
		hstmt = SQL_NULL_HSTMT;
	}
    if(hdbc != SQL_NULL_HDBC) {
            SQLDisconnect(hdbc);
            SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
			hdbc = SQL_NULL_HDBC;
	}
}



void CCoreODBC::OpenODBC(BSTR connection, bool create) {
		ASSERT(("Nothing at all",false));
		CopyTo(connection, connstr);
#define ODBCKEYWORDLEN 5   // "ODBC;"
		if( !(std::string(connstr, 0, ODBCKEYWORDLEN) == "ODBC;") )
			HR_THROW(E_INVALID_USAGE);
		
		connstr.erase(0,ODBCKEYWORDLEN);

	    SQLTHROW(SQLAllocHandle(SQL_HANDLE_DBC, env, &hdbc));

		LastUsedHandle(SQL_HANDLE_DBC, hdbc);
        SQLTHROW(SQLSetConnectAttr(hdbc, SQL_LOGIN_TIMEOUT, (void *)5, 0));
        SQLTHROW(SQLSetConnectAttr(hdbc, SQL_INTEGRATED_SECURITY, (void *)SQL_IS_ON, 0));

         /* Connect to data source */
		SQLCHAR ous[500];
        SQLTHROW(SQLDriverConnect(hdbc, NULL, connstr, SQL_NTS, ous, sizeof(ous), NULL, SQL_DRIVER_NOPROMPT));
//        SQLTHROW(SQLBrowseConnect(hdbc, connstr, SQL_NTS, ous, sizeof(ous), NULL));

        SQLTHROW(SQLSetConnectAttr(hdbc, SQL_ATTR_AUTOCOMMIT, SQL_AUTOCOMMIT_OFF, 0));


		SQLTHROW(SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt)); 
		LastUsedHandle(SQL_HANDLE_STMT, hstmt);



		CComPtr<ICoreMetaObjects> mobs;
		COMTHROW(metaproject->get_Objects(&mobs));
		MGACOLL_ITERATE(ICoreMetaObject, mobs) {
			std::sqlstring tname = tablename(MGACOLL_ITER);
std::sqlstring drop;
drop.format("DROP TABLE \"%s\"", tname);
if(create) SQLExecDirect(hstmt, drop, SQL_NTS);

			SQLTHROW(SQLTables(hstmt, NULL, SQL_NTS, NULL, SQL_NTS, 
								tname, SQL_NTS, NULL, SQL_NTS));
			SQLRETURN pp = SQLFetch(hstmt);
			bool tableexists = pp == SQL_SUCCESS;
			if(pp  != SQL_SUCCESS && pp != SQL_NO_DATA) SQLTHROW(pp);
			SQLTHROW(SQLFreeStmt(hstmt, SQL_CLOSE));


			std::sqlstring creacmd("CREATE TABLE ");
			if(!tableexists) {
				if(!create) HR_THROW(E_ODBC);
				creacmd.format("CREATE TABLE \"%s\"  (objid INTEGER IDENTITY NOT FOR REPLICATION PRIMARY KEY", tname);
			}
			CComPtr<ICoreMetaAttributes> attrs;
			COMTHROW(MGACOLL_ITER->get_Attributes(&attrs));

			SQLSMALLINT datatype;
			SQLTHROW(SQLBindCol(hstmt, 5, SQL_C_SSHORT, &datatype, 0, 0));
			MGACOLL_ITERATE(ICoreMetaAttribute, attrs) {
				valtype_type vt;
				COMTHROW(MGACOLL_ITER->get_ValueType(&vt));
				static struct vvx {
					SQLSMALLINT vtcode;
					char *vtname;
				} valtypes_tab[] = { {SQL_INTEGER, ""}, {SQL_INTEGER, ""}, {SQL_BIGINT, "BIGINT DEFAULT 0"},
									{SQL_SMALLINT, "SMALLINT DEFAULT 0"}, {SQL_INTEGER, "INTEGER DEFAULT 0"},
									{SQL_VARCHAR, "VARCHAR(256) DEFAULT ''"}, {SQL_VARBINARY, "VARBINARY(100)"},
									{SQL_FLOAT,  "DOUBLE PRECISION DEFAULT 0.0"}}; 
				if(vt !=  VALTYPE_COLLECTION) {
					std::sqlstring cname = colname(MGACOLL_ITER);

					if(tableexists) {
						SQLTHROW(SQLColumns(hstmt, NULL, SQL_NTS, NULL, SQL_NTS, tname, SQL_NTS, 
											cname, SQL_NTS));
						SQLTHROW(SQLFetch(hstmt));
						if(datatype != valtypes_tab[vt].vtcode) {
							ASSERT(("SABC", false));
							COMTHROW(E_ODBC);
						}
						SQLTHROW(SQLFreeStmt(hstmt, SQL_CLOSE));
					}
					else {
						creacmd.append(", ");						
						creacmd.append(cname);						
						creacmd.append(" ");						
						creacmd.append(valtypes_tab[vt].vtname);						
					}
					if(vt == VALTYPE_POINTER) {
						attrid_type mi;
						COMTHROW(MGACOLL_ITER->get_AttrID(&mi));
						pratype::iterator pp = ptrrevattrs.find(mi);
						if(pp == ptrrevattrs.end()) {
							pp = ptrrevattrs.insert(ptrrevattrs.begin(), pratype::value_type(mi, attrlist()));
						} 
						pp->second.push_front((ICoreMetaAttribute *)MGACOLL_ITER);
					}
				}
			} MGACOLL_ITERATE_END;
			SQLTHROW(SQLFreeStmt(hstmt, SQL_UNBIND));
			if(!tableexists) {
				creacmd.append(")");
				SQLTHROW(SQLExecDirect(hstmt, creacmd, SQL_NTS));
			}
		} MGACOLL_ITERATE_END;
}


STDMETHODIMP CCoreODBC::OpenProject(BSTR connection, VARIANT_BOOL *ro_mode) {
	if( IsOpened() || metaproject == NULL )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{
		OpenODBC(connection, false);


		modified = false;
		if(ro_mode) *ro_mode = VARIANT_FALSE;

		ASSERT( IsOpened() );
	}
	COMCATCH( CancelProject())
}

STDMETHODIMP CCoreODBC::CreateProject(BSTR connection)
{
	if( IsOpened() || metaproject == NULL )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{

		OpenODBC(connection, true);


		SQLUINTEGER rootobjid = OBJID_ROOT;

		SQLTHROW(SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_ULONG, SQL_INTEGER, 10, 0,
                  &rootobjid, 0, 0));

		CComPtr<ICoreMetaObject> mo;
		COMTHROW(metaproject->get_Object(METAID_ROOT, &mo));

		std::sqlstring rootcreate;
		rootcreate.format("SET IDENTITY_INSERT \"%s\" ON", tablename(mo));
		SQLTHROW(SQLExecDirect(hstmt, rootcreate, SQL_NTS));

		rootcreate.format("INSERT INTO \"%s\" (objid) VALUES (?)", tablename(mo));
		SQLTHROW(SQLExecDirect(hstmt, rootcreate, SQL_NTS));

		rootcreate.format("SET IDENTITY_INSERT \"%s\" OFF", tablename(mo));
		SQLTHROW(SQLExecDirect(hstmt, rootcreate, SQL_NTS));
/*
		SQLRETURN retcode = SQLExecDirect(hstmt, rootcreate, SQL_NTS);

	    while (retcode == SQL_NEED_DATA) {
		  retcode = SQLParamData(hstmt, &pToken);
		  if (retcode == SQL_NEED_DATA) {
            SQLPutData(hstmt, Data, cbData);
		  }
		}
*/


		modified = false;

		ASSERT( IsOpened() );
	}
	COMCATCH( CancelProject(); ErrGet())
}


STDMETHODIMP CCoreODBC::CloseProject( VARIANT_BOOL abort) {
	if( abort || !IsOpened() || metaproject == NULL )
		COMRETURN(E_INVALID_USAGE);

	COMTRY
	{
		CancelProject();
	}
	COMCATCH(;)
}

STDMETHODIMP CCoreODBC::BeginTransaction()
{
	if( !IsOpened() || InTransaction() )
		COMRETURN(E_INVALID_USAGE);

	intrans = true;


	return S_OK;
}

STDMETHODIMP CCoreODBC::CommitTransaction()
{
	if( !InTransaction() )
		COMRETURN(E_INVALID_USAGE);

	ASSERT( IsOpened() );

	CloseObject();

	if(SQLEndTran(SQL_HANDLE_DBC, hdbc, SQL_COMMIT) != SQL_SUCCESS) {
		return E_ODBC;
	}
	intrans = false;

	return S_OK;
}

STDMETHODIMP CCoreODBC::AbortTransaction()
{
	if( !InTransaction() )
		COMRETURN(E_INVALID_USAGE);

	ASSERT( IsOpened() );

	CloseObject();

	intrans = false;
	if(SQLEndTran(SQL_HANDLE_DBC, hdbc, SQL_ROLLBACK) != SQL_SUCCESS) {
		return E_ODBC;
	}

	return S_OK;
}

STDMETHODIMP CCoreODBC::get_StorageType(long *p)
{
	CHECK_OUT(p);

	*p = 0;
	return S_OK;
}

namespace std
{
sqlstring::sqlstring(const BSTR a) {
	resize(SysStringLen(a),'x');
	CopyTo(a, (char *)c_str(), size());
}

const sqlstring &sqlstring::format(char *templ, const sqlstring &p1) {
   erase();
   resize(strlen(templ) + 200);
   sprintf((char *)c_str(), templ, (const SQLCHAR *)p1);
   resize(strlen(c_str()));
   ASSERT(size() > strlen(templ));  // may remove it later
   return *this;
}

const sqlstring &sqlstring::format(char *templ, const sqlstring &p1,  const sqlstring &p2) {
   erase();
   resize(strlen(templ) + 200);
   sprintf((char *)c_str(), templ, (const SQLCHAR *)p1, (const SQLCHAR *)p2);
   resize(strlen(c_str()));
   ASSERT(size() > strlen(templ));  // may remove it later
   return *this;
}
};