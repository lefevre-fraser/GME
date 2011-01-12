#include "stdafx.h"
#include "MgaRegistrar.h"
#include "atlconv.h"
#include "CommonComponent.h"
#include "Parser.h"

#import "mscorlib.tlb"
#ifdef _DEBUG
#import "../Debug/MgaDotNetServices.tlb"
#else
#import "../Release/MgaDotNetServices.tlb"
#endif

#include "atlsafe.h"

#ifdef _DEBUG
void ERRTHROW(LONG err)
{
	VERIFYTHROW( err == ERROR_SUCCESS );
}
#else
#define ERRTHROW(FUNC) \
{ \
	VERIFYTHROW( (FUNC) == ERROR_SUCCESS ); \
}
#endif

const CString rootreg(_T("SOFTWARE\\GME"));


CString QueryValue(CRegKey &key, const char *name)
{
	CString buffer;
	TCHAR *bufp = buffer.GetBuffer(4096);
	ULONG buflen = 4095;
	LONG err = key.QueryStringValue( name, bufp, &buflen);
	if( err != ERROR_SUCCESS ) {
		buflen = 0;
		if(err != ERROR_FILE_NOT_FOUND) ERRTHROW(err);
	}
	ASSERT( 0 <= buflen && buflen < 4096 );
	bufp[buflen] = _T('\0');
	buffer.ReleaseBuffer();

	return buffer;
}

// --------------------------- CMgaRegistrar

#define RM_USER 1 
#define RM_SYS  2
#define RM_SYS2 4
#define RM_BOTH 3
#define RM_TEST 8
#define RM_PRIO		 (RM_SYS2 | RM_USER)
#define RM_SYSDOREAD (RM_SYS2 | RM_SYS)

// For read operations: USER, SYS, PRIO
// For multi-return read operations: USER, SYS, BOTH, PRIO
// For write operations: USER, SYS, BOTH, TEST

void REVOKE_SYS2(regaccessmode_enum &mode) { *(int *)&mode &= ~RM_SYS2; }

STDMETHODIMP CMgaRegistrar::get_IconPath(regaccessmode_enum mode, BSTR *path)
{
	CHECK_OUT(path);

	COMTRY
	{
		LONG res;
		CString str;
		if(mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "IconPath");
				str.TrimRight(" ;,\t");
				if(!str.IsEmpty()) REVOKE_SYS2(mode);
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				CString str2 = QueryValue(mga, "IconPath");
				str2.TrimLeft(" ;,\t");
				if(!str.IsEmpty() && !str2.IsEmpty()) str += ";";
				str	+= str2;
			}
		}
		CopyTo(str, path);
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::put_IconPath(regaccessmode_enum mode, BSTR path)
{
	COMTRY
	{
		CString str;
		CopyTo(path, str);
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "IconPath", str ));
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(mode & RM_SYS) ERRTHROW( mga.SetStringValue( "IconPath", str));
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::get_ShowMultipleView(regaccessmode_enum mode, VARIANT_BOOL *enabled)
{
	COMTRY
	{
		LONG res;
		CString str;
		if(mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "ShowMultipleView");
				if(!str.IsEmpty()) {
					REVOKE_SYS2(mode);
				}
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "ShowMultipleView");
			}
		}
		*enabled = (str == "1") ? VARIANT_TRUE : VARIANT_FALSE; // Default value: false
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::put_ShowMultipleView(regaccessmode_enum mode, VARIANT_BOOL enabled)
{
	COMTRY
	{
		CString str = (enabled == VARIANT_FALSE) ? "0" : "1";
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "ShowMultipleView", str));
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(mode & RM_SYS) ERRTHROW( mga.SetStringValue( "ShowMultipleView", str));
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::get_EventLoggingEnabled(regaccessmode_enum mode, VARIANT_BOOL *enabled)
{
	COMTRY
	{
		LONG res;
		CString str;
		if(mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "EventLoggingEnabled");
				if(!str.IsEmpty()) {
					REVOKE_SYS2(mode);
				}
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "EventLoggingEnabled");
			}
		}
		*enabled = (str == "1") ? VARIANT_TRUE : VARIANT_FALSE; // Default value: false
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::put_EventLoggingEnabled(regaccessmode_enum mode, VARIANT_BOOL enabled)
{
	COMTRY
	{
		CString str = (enabled == VARIANT_FALSE) ? "0" : "1";
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "EventLoggingEnabled", str));
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(mode & RM_SYS) ERRTHROW( mga.SetStringValue( "EventLoggingEnabled", str));
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::get_AutosaveEnabled(regaccessmode_enum mode, VARIANT_BOOL *enabled)
{
	COMTRY
	{
		LONG res;
		CString str;
		if(mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "AutosaveEnabled");
				if(!str.IsEmpty()) {
					REVOKE_SYS2(mode);
				}
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "AutosaveEnabled");
			}
		}
		*enabled = (str == "1") ? VARIANT_TRUE : VARIANT_FALSE; // Default value: false
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::put_AutosaveEnabled(regaccessmode_enum mode, VARIANT_BOOL enabled)
{
	COMTRY
	{
		CString str = (enabled == VARIANT_FALSE) ? "0" : "1";
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "AutosaveEnabled", str));
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(mode & RM_SYS) ERRTHROW( mga.SetStringValue( "AutosaveEnabled", str));
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::get_AutosaveFreq(regaccessmode_enum mode, long *secs)
{
	COMTRY
	{
		LONG res;
		CString str;
		if(mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "AutosaveFreq");
				if(!str.IsEmpty()) {
					REVOKE_SYS2(mode);
				}
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "AutosaveFreq");
			}
		}
		if (_stscanf((LPCTSTR)str, "%ld", secs) != 1) {
			*secs = 60;	// Default value: 1 minute
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::put_AutosaveFreq(regaccessmode_enum mode, long secs)
{
	COMTRY
	{
		CString str;
		str.Format("%ld", secs);
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "AutosaveFreq", str));
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(mode & RM_SYS) ERRTHROW( mga.SetStringValue( "AutosaveFreq", str));
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::get_AutosaveUseDir(regaccessmode_enum mode, VARIANT_BOOL *enabled)
{
	COMTRY
	{
		LONG res;
		CString str;
		if(mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "AutosaveUseDir");
				if(!str.IsEmpty()) {
					REVOKE_SYS2(mode);
				}
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "AutosaveUseDir");
			}
		}
		*enabled = (str == "1") ? VARIANT_TRUE : VARIANT_FALSE; // Default value: false
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::put_AutosaveUseDir(regaccessmode_enum mode, VARIANT_BOOL enabled)
{
	COMTRY
	{
		CString str = (enabled == VARIANT_FALSE) ? "0" : "1";
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "AutosaveUseDir", str));
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(mode & RM_SYS) ERRTHROW( mga.SetStringValue( "AutosaveUseDir", str));
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::get_AutosaveDir(regaccessmode_enum mode, BSTR *dir)
{
	CHECK_OUT(dir);

	COMTRY
	{
		LONG res;
		CString str;
		if(mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "AutosaveDir");
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "AutosaveDir");
			}
		}
		CopyTo(str, dir);
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::put_AutosaveDir(regaccessmode_enum mode, BSTR dir)
{
	COMTRY
	{
		CString str;
		CopyTo(dir, str);
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "AutosaveDir", str));
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(mode & RM_SYS) ERRTHROW( mga.SetStringValue( "AutosaveDir", str));
		}
	}
	COMCATCH(;)
}


STDMETHODIMP CMgaRegistrar::get_ExternalEditorEnabled(regaccessmode_enum mode, VARIANT_BOOL *enabled)
{
	COMTRY
	{
		LONG res;
		CString str;
		if(mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "ExternalEditorEnabled");
				if(!str.IsEmpty()) {
					REVOKE_SYS2(mode);
				}
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "ExternalEditorEnabled");
			}
		}
		*enabled = (str == "1") ? VARIANT_TRUE : VARIANT_FALSE; // Default value: false
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::put_ExternalEditorEnabled(regaccessmode_enum mode, VARIANT_BOOL enabled)
{
	COMTRY
	{
		CString str = (enabled == VARIANT_FALSE) ? "0" : "1";
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "ExternalEditorEnabled", str));
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(mode & RM_SYS) ERRTHROW( mga.SetStringValue( "ExternalEditorEnabled", str));
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::get_ExternalEditor(regaccessmode_enum mode, BSTR *path)
{
	CHECK_OUT(path);

	COMTRY
	{
		LONG res;
		CString str;
		if(mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "ExternalEditor");
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "ExternalEditor");
			}
		}
		CopyTo(str, path);
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::put_ExternalEditor(regaccessmode_enum mode, BSTR path)
{
	COMTRY
	{
		CString str;
		CopyTo(path, str);
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "ExternalEditor", str));
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(mode & RM_SYS) ERRTHROW( mga.SetStringValue( "ExternalEditor", str));
		}
	}
	COMCATCH(;)
}


STDMETHODIMP CMgaRegistrar::get_UseAutoRouting(regaccessmode_enum mode, VARIANT_BOOL *enabled)
{
	COMTRY
	{
		LONG res;
		CString str;
		if(mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "UseAutoRouting");
				if(!str.IsEmpty()) {
					REVOKE_SYS2(mode);
				}
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "UseAutoRouting");
			}
		}
		*enabled = (str == "0") ? VARIANT_FALSE : VARIANT_TRUE; // Default value: true
	}
	COMCATCH(;)
}


STDMETHODIMP CMgaRegistrar::put_UseAutoRouting(regaccessmode_enum mode, VARIANT_BOOL enabled)
{
	COMTRY
	{
		CString str = (enabled == VARIANT_FALSE) ? "0" : "1";
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "UseAutoRouting", str));
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(mode & RM_SYS) ERRTHROW( mga.SetStringValue( "UseAutoRouting", str));
		}
	}
	COMCATCH(;)
}


STDMETHODIMP CMgaRegistrar::get_LabelAvoidance(regaccessmode_enum mode, VARIANT_BOOL *enabled)
{
	COMTRY
	{
		LONG res;
		CString str;
		if(mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "LabelAvoidance");
				if(!str.IsEmpty()) {
					REVOKE_SYS2(mode);
				}
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "LabelAvoidance");
			}
		}
		*enabled = (str == "1") ? VARIANT_TRUE : VARIANT_FALSE; // Default value: false
	}
	COMCATCH(;)
}


STDMETHODIMP CMgaRegistrar::put_LabelAvoidance(regaccessmode_enum mode, VARIANT_BOOL enabled)
{
	COMTRY
	{
		CString str = (enabled == VARIANT_FALSE) ? "0" : "1";
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "LabelAvoidance", str));
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(mode & RM_SYS) ERRTHROW( mga.SetStringValue( "LabelAvoidance", str));
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::get_ScriptEngine(regaccessmode_enum mode, BSTR *path) {
	CHECK_OUT(path);

	COMTRY
	{
		LONG res;
		CString str;
		if(mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "ScriptEngine");
				str.TrimRight(" ;,\t");
				if(!str.IsEmpty()) REVOKE_SYS2(mode);
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				CString str2 = QueryValue(mga, "ScriptEngine");
				str2.TrimLeft(" ;,\t");
				if(!str.IsEmpty() && !str2.IsEmpty()) str += ";";
				str	+= str2;
			}
		}
		CopyTo(str, path);
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::put_ScriptEngine(regaccessmode_enum mode, BSTR path) {
	COMTRY
	{
		CString str;
		CopyTo(path, str);
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue("ScriptEngine", str) );//z7
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(mode & RM_SYS) ERRTHROW( mga.SetStringValue("ScriptEngine", str) );//z7
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::GetDefZoomLevel(regaccessmode_enum p_mode, BSTR *p_zlev)
{
	CHECK_OUT(p_zlev);
	COMTRY
	{
		LONG res;
		CString str;
		if(p_mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "DefaultZoomLevel");
				if(!str.IsEmpty()) REVOKE_SYS2(p_mode);
			}
		}
		if(p_mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "DefaultZoomLevel");
			}
		}
		CopyTo(str, p_zlev);
	}
	COMCATCH(;)

}

STDMETHODIMP CMgaRegistrar::SetDefZoomLevel(regaccessmode_enum p_mode, BSTR p_zlev)
{
	COMTRY
	{
		CString str;
		CopyTo(p_zlev, str);
		if(p_mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "DefaultZoomLevel", str));
		}
		if(p_mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(p_mode & RM_SYS) ERRTHROW( mga.SetStringValue( "DefaultZoomLevel", str));
		}
	}
	COMCATCH(;)
}


STDMETHODIMP CMgaRegistrar::GetMouseOverNotify(regaccessmode_enum mode, VARIANT_BOOL *enabled)
{
	COMTRY
	{
		LONG res;
		CString str;
		if(mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "MouseOverNotify");
				if(!str.IsEmpty()) {
					REVOKE_SYS2(mode);
				}
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "MouseOverNotify");
			}
		}
		*enabled = (str == "1") ? VARIANT_TRUE : VARIANT_FALSE; // Default value: false
	}
	COMCATCH(;)
}


STDMETHODIMP CMgaRegistrar::SetMouseOverNotify(regaccessmode_enum mode, VARIANT_BOOL enabled)
{
	COMTRY
	{
		CString str = (enabled == VARIANT_FALSE) ? "0" : "1";
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "MouseOverNotify", str));
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(mode & RM_SYS) ERRTHROW( mga.SetStringValue( "MouseOverNotify", str));
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::GetRealNmbFmtStr(regaccessmode_enum p_mode, BSTR *p_fmtStr)
{
	CHECK_OUT(p_fmtStr);
	COMTRY
	{
		LONG res;
		CString str;
		if(p_mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "RealNmbFmtStr");
				if(!str.IsEmpty()) REVOKE_SYS2(p_mode);
			}
		}
		if(p_mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "RealNmbFmtStr");
			}
		}
		CopyTo(str, p_fmtStr);
	}
	COMCATCH(;)

}

STDMETHODIMP CMgaRegistrar::SetRealNmbFmtStr(regaccessmode_enum p_mode, BSTR p_fmtStr)
{
	COMTRY
	{
		CString str;
		CopyTo(p_fmtStr, str);
		if(p_mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "RealNmbFmtStr", str));
		}
		if(p_mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(p_mode & RM_SYS) ERRTHROW( mga.SetStringValue( "RealNmbFmtStr", str));
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::GetTimeStamping(regaccessmode_enum p_mode, VARIANT_BOOL *p_enabled)
{
	COMTRY
	{
		LONG res;
		CString str;
		if(p_mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "TimeStamping");
				if(!str.IsEmpty()) {
					REVOKE_SYS2(p_mode);
				}
			}
		}
		if(p_mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "TimeStamping");
			}
		}
		*p_enabled = (str == "1") ? VARIANT_TRUE : VARIANT_FALSE; // Default value: false
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::SetTimeStamping(regaccessmode_enum p_mode, VARIANT_BOOL p_enabled)
{
	COMTRY
	{
		CString str = (p_enabled == VARIANT_FALSE) ? "0" : "1";
		if(p_mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "TimeStamping", str));
		}
		if(p_mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(p_mode & RM_SYS) ERRTHROW( mga.SetStringValue( "TimeStamping", str));
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::GetNavigation(regaccessmode_enum p_mode, VARIANT_BOOL *p_enabled)
{
	COMTRY
	{
		LONG res;
		CString str;
		if(p_mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "Navigation");
				if(!str.IsEmpty()) {
					REVOKE_SYS2(p_mode);
				}
			}
		}
		if(p_mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "Navigation");
			}
		}
		*p_enabled = (str == "0") ? VARIANT_FALSE : VARIANT_TRUE; // Default value: true
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::SetNavigation(regaccessmode_enum p_mode, VARIANT_BOOL p_enabled)
{
	COMTRY
	{
		CString str = (p_enabled == VARIANT_FALSE) ? "0" : "1";
		if(p_mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "Navigation", str));
		}
		if(p_mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(p_mode & RM_SYS) ERRTHROW( mga.SetStringValue( "Navigation", str));
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::GetUndoQueueSize(regaccessmode_enum p_mode, BSTR *p_qusz)
{
	CHECK_OUT(p_qusz);
	COMTRY
	{
		LONG res;
		CString str;
		if(p_mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "UndoQueueSize");
				if(!str.IsEmpty()) REVOKE_SYS2(p_mode);
			}
		}
		if(p_mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "UndoQueueSize");
			}
		}
		CopyTo(str, p_qusz);
	}
	COMCATCH(;)

}

STDMETHODIMP CMgaRegistrar::SetUndoQueueSize(regaccessmode_enum p_mode, BSTR p_qusz)
{
	COMTRY
	{
		CString str;
		CopyTo(p_qusz, str);
		if(p_mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "UndoQueueSize", str));
		}
		if(p_mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(p_mode & RM_SYS) ERRTHROW( mga.SetStringValue( "UndoQueueSize", str));
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::get_EdgeSmoothMode(regaccessmode_enum mode, edgesmoothmode_enum* smoothMode)
{
	COMTRY
	{
		LONG res;
		CString str;
		if(mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "EdgeSmoothMode");
				if(!str.IsEmpty()) {
					REVOKE_SYS2(mode);
				}
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "EdgeSmoothMode");
			}
		}
		*smoothMode = (edgesmoothmode_enum)(str.IsEmpty() ? 2 : strtol(str, NULL, 10));
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::put_EdgeSmoothMode(regaccessmode_enum mode, edgesmoothmode_enum smoothMode)
{
	COMTRY
	{
		CString str;
		str.Format("%d", smoothMode);
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "EdgeSmoothMode", str));
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(mode & RM_SYS) ERRTHROW( mga.SetStringValue( "EdgeSmoothMode", str));
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::get_FontSmoothMode(regaccessmode_enum mode, fontsmoothmode_enum* smoothMode)
{
	COMTRY
	{
		LONG res;
		CString str;
		if(mode & RM_USER) {
			CRegKey mga;
			res = mga.Open(HKEY_CURRENT_USER, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str	= QueryValue(mga, "FontSmoothMode");
				if(!str.IsEmpty()) {
					REVOKE_SYS2(mode);
				}
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey mga;
			res = mga.Open(HKEY_LOCAL_MACHINE, rootreg, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				str = QueryValue(mga, "FontSmoothMode");
			}
		}
		*smoothMode = (fontsmoothmode_enum)(str.IsEmpty() ? 4 : strtol(str, NULL, 10));
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::put_FontSmoothMode(regaccessmode_enum mode, fontsmoothmode_enum smoothMode)
{
	COMTRY
	{
		CString str;
		str.Format("%d", smoothMode);
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			ERRTHROW( mga.SetStringValue( "FontSmoothMode", str));
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			if(mode & RM_SYS) ERRTHROW( mga.SetStringValue( "FontSmoothMode", str));
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::get_Paradigms(regaccessmode_enum mode, VARIANT *names)
{
	CHECK_OUT(names);

	COMTRY
	{
		CStringArray ret;
		if(mode & RM_USER) {
			CRegKey pars;
			LONG res = pars.Open(HKEY_CURRENT_USER, rootreg+"\\Paradigms", KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				for(int index = 0;; ++index) {
					TCHAR name[1024];
					LONG err = RegEnumKey(pars, index, name, 1024);
					if( err == ERROR_NO_MORE_ITEMS )
						break;
					ERRTHROW( err );

					REVOKE_SYS2(mode);
					ret.Add(name);
				}

			}
		}
		int retlen = ret.GetSize();

		if(mode & RM_SYSDOREAD) {
			CRegKey pars;
			LONG res = pars.Open(HKEY_LOCAL_MACHINE, rootreg+"\\Paradigms", KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				for(int index = 0;; ++index) {
					TCHAR name[1024];
					LONG err = RegEnumKey(pars, index, name, 1024);
					if( err == ERROR_NO_MORE_ITEMS )
						break;
					ERRTHROW( err );
					int j;
					for(j = 0; j < retlen; j++) {		// Make sure, name is not present already, if yes, system copy is ignored
						if(!ret[j].CompareNoCase(name)) break;
					}
					if(j != retlen) continue;
					ret.Add(name);
				}

			}
		}


		CopyTo(ret, names);
	}
	COMCATCH(;)
}


HRESULT GetMtaInfo(BSTR conn, BSTR *parname, BSTR *version, VARIANT *guid) {
	COMTRY {
		CComObjPtr<IMgaMetaProject> paradigm;
		COMTHROW( paradigm.CoCreateInstance(OLESTR("MGA.MgaMetaProject")) );
		ASSERT( paradigm != NULL );

		COMTHROW( paradigm->Open(conn) );

		COMTHROW( paradigm->get_Name(parname) );

		COMTHROW( paradigm->get_Version(version) );

		COMTHROW( paradigm->get_GUID(guid) );

		COMTHROW( paradigm->Close() );
	} COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::RegisterParadigmFromDataDisp(BSTR connstr, regaccessmode_enum mode, BSTR *newname)
{
	return RegisterParadigmFromData( connstr, newname, mode);
}

STDMETHODIMP CMgaRegistrar::RegisterParadigmFromData(BSTR connstr, BSTR *newname, regaccessmode_enum mode)
{
	CHECK_IN(connstr);
 	if(newname) CHECK_OUT(newname);
	COMTRY {
		CString conn = connstr;
		CString connrecent;
		// we have to parse it
		if( conn.Left(4) == "XML=" )
		{
			CString file = conn.Mid(4);

			conn = "MGA=";
			conn += file;

			if( conn.Right(4).CompareNoCase(".xml") == 0 || 
				conn.Right(4).CompareNoCase(".xmp") == 0 ) {
				conn.Delete(conn.GetLength() - 4, 4);
			}
			conn += ".mta";
#define FILEPART(x) (((LPCTSTR)x)+4)
			DWORD info = GetFileAttributes(FILEPART(conn));
			if(info != 0xFFFFFFFF ) {	// save old version of paradigm under another name
			  if(info & FILE_ATTRIBUTE_DIRECTORY) COMTHROW(E_FILEOPEN);
			  try {
				CComBstrObj name;	// Format: name-<GUID>
				CComVariant prevguid;
				CComBstrObj prevversion;
				COMTHROW(GetMtaInfo(PutInBstr(conn), PutOut(name), PutOut(prevversion), PutOut(prevguid)));
				CComBstrObj conn1;
				if(QueryParadigm(name, PutOut(conn1), &prevguid, REGACCESS_PRIORITY) == S_OK &&
					conn1 == CComBSTR(conn)) {  // if it was correctly registered under the previous nonextended name
					GUID  gg;
					CopyTo(prevguid,gg);
					CComBstrObj guidstr;
					CopyTo(gg, guidstr);
					connrecent = conn.Left(conn.GetLength()-4)+"-"+CString(PutInCString(guidstr))+".mta";

					bool sysmove = false, usermove = false;
					conn1.Empty();
					if(QueryParadigm(name, PutOut(conn1), &prevguid, REGACCESS_SYSTEM) == S_OK &&
						conn1 == CComBSTR(conn)) {  // if it was correctly registered in system
						if(RegisterParadigm(name, PutInBstr(connrecent), prevversion, prevguid, REGACCESS_TEST) != S_OK) {
							AfxMessageBox("Cannot register this paradigm file\n"
										  "an existing '.mta' file with the same name\n"
										  "is registered in the system registry\n"
										  "which you are not permitted to change.\n"
										  "You need to change the name or location\n"
										  "of the new paradigm file");
							return E_INVALID_USAGE;
						}
						sysmove = true;;
					}
					conn1.Empty();
					if(QueryParadigm(name, PutOut(conn1), &prevguid, REGACCESS_USER) == S_OK &&
						conn1 == CComBSTR(conn)) {  // if it was correctly registered in user
						usermove = true;;
					}

					if(!MoveFileEx(FILEPART(conn), FILEPART(connrecent), MOVEFILE_REPLACE_EXISTING)) {
						COMTHROW(E_FILEOPEN);
					}
 
					if(sysmove) {
						COMTHROW( RegisterParadigm( name, PutInBstr(connrecent), prevversion, prevguid, REGACCESS_SYSTEM) );
					}
					if(usermove) {
						COMTHROW( RegisterParadigm( name, PutInBstr(connrecent), prevversion, prevguid, REGACCESS_USER) );
					}
				}
			  } catch(hresult_exception(&e)) {
					AfxMessageBox(CString("Failure saving previous version of paradigm\n") + 
									e.what() + 
									(e.hr == E_BINFILE?" [Binary paradigm file (.mta) incompatibility]\nPossible reason: GME version 6 changed the binary format of paradigms.":"") +
									"\nOld version will be overwritten");
					connrecent.Empty();
			  }
			}

			CComObjPtr<IMgaMetaParser> parser;
			COMTHROW( parser.CoCreateInstance(OLESTR("MGA.MgaMetaParser")) );
			ASSERT( parser != NULL );

			COMTHROW( parser->Parse(PutInBstr(file), PutInBstr(conn)) );
		}

		CComBstrObj name;
		CComVariant guid;
		CComBstrObj version;
		COMTHROW(GetMtaInfo(PutInBstr(conn), PutOut(name), PutOut(version), PutOut(guid)));
		if(!connrecent.IsEmpty()) {
			CComBstrObj namer;
			CComVariant guidr;
			CComBstrObj versionr;
			COMTHROW(GetMtaInfo(PutInBstr(connrecent), PutOut(namer), PutOut(versionr), PutOut(guidr)));
			// We should change existing registration only here, if the new GUID != the old
		}

		COMTHROW(RegisterParadigm( name, PutInBstr(conn), PutInBstr(version), guid, mode) );
		if(newname) MoveTo(name, newname);
	} COMCATCH(;)
}



/*
bool CheckHasConstraints(IMgaMetaBase *o) {
	{
		CComPtr<IMgaConstraints> consts;
		long l;
		COMTHROW(f->get_Constraints(&consts));
		COMTHROW(consts->get_Count(&l));
		if(l > 0) return true;
	}
	CComQIPtr<IMgaMetaFolder> f = o;
	if(f) {
		CComPtr<IMgaMetaFolders> fs;
		COMTHROW(f->get_DefinedFolders(&fs));
		MGACOLL_ITERATE(IMgaMetaFolder, fs) {
			if(CheckHasConstraints(MGACOLL_ITER)) return true;
		} MGACOLL_ITERATE_END;
		CComPtr<IMgaMetaFCOs> fcs;
		COMTHROW(f->get_DefinedFCOs(&fcs));
		MGACOLL_ITERATE(IMgaMetaFCO, fcs) {
			if(CheckHasConstraints(MGACOLL_ITER)) return true;
		} MGACOLL_ITERATE_END;
	}
	else {
		CComQIPtr<IMgaMetaModel> m = o;
		if(m) {
			CComPtr<IMgaMetaFCOs> fcs;
			COMTHROW(m->get_DefinedFCOs(&fcs));
			MGACOLL_ITERATE(IMgaMetaFCO, fcs) {
				if(CheckHasConstraints(MGACOLL_ITER)) return true;
			} MGACOLL_ITERATE_END;
		}		
	}
}


bool ParadigmHasConstraints(BSTR connstr) {
	bool hasconstraints = false;
	int openstate = 0;
	COMTRY {
		CComPtr<IMgaMetaProject> pp;
		COMTHROW(pp.CoCreateInstance("Mga.MgaMetaProject"));
		COMTHROW(pp->Open(connstr));
		openstate = 1;
		CComPtr<IMgaMetaFolder> f;
		COMTHROW(pp->get_RootFolder(&f));
	
		hasconstraints = CheckHasConstraints(f);

	} 	catch(hresult_exception &) { ; }
	if(openstate) {
		COMTHROW(pp->Close());
	}
	return hasconstraints;
}
*/


STDMETHODIMP CMgaRegistrar::RegisterParadigm(BSTR name, BSTR connstr, BSTR version, VARIANT guid, regaccessmode_enum mode)
{
	COLE2CT version2(version);
	CString cver(version2); 

	if( guid.vt != (VT_UI1 | VT_ARRAY) || GetArrayLength(guid) != sizeof(GUID) )
	COMRETURN(E_INVALIDARG);

	COMTRY
	{
		
		GUID guid2;
		CopyTo(guid, guid2);
		CComBstrObj guid3;
		CopyTo(guid2, guid3);
	
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW(mga.Create(HKEY_CURRENT_USER, rootreg) );

			CRegKey pars;
			ERRTHROW( pars.Create(mga, "Paradigms") );

			CRegKey par;
			ERRTHROW( par.Create(pars, PutInCString(name)) );


			ERRTHROW( par.SetStringValue( "CurrentVersion", PutInCString(guid3)));
			if (!cver.IsEmpty()) {
				ERRTHROW( par.SetStringValue( cver, PutInCString(guid3)));
			}
			CRegKey parg;
			ERRTHROW( parg.Create(par, PutInCString(guid3)) );

			ERRTHROW( parg.SetStringValue( "ConnStr", PutInCString(connstr)));
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW(mga.Create(HKEY_LOCAL_MACHINE, rootreg) );

			CRegKey pars;
			ERRTHROW( pars.Create(mga, "Paradigms") );

			CRegKey par;

			if(mode & RM_SYS) {
				ERRTHROW( par.Create(pars, PutInCString(name)) );
				CString gg	= QueryValue(par, "GUID");
				CString gc	= QueryValue(par, "ConnStr");
				par.DeleteValue("GUID");
				par.DeleteValue("ConnStr");
				if(!gc.IsEmpty() && !gg.IsEmpty()) {
					CRegKey parg2;
					ERRTHROW( parg2.Create(par, gg) );
					ERRTHROW( parg2.SetStringValue( "ConnStr", gc) );
				}

				ERRTHROW( par.SetStringValue( "CurrentVersion", PutInCString(guid3)));
				if (!cver.IsEmpty()) {
					ERRTHROW( par.SetStringValue( cver, PutInCString(guid3)));
				}
				CRegKey parg;
				ERRTHROW( parg.Create(par, PutInCString(guid3)) );
	
				ERRTHROW( parg.SetStringValue( "ConnStr", PutInCString(connstr)));
			}
			else {
				LONG res = par.Open(pars, PutInCString(name));
				if(res != ERROR_SUCCESS && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			}
		}
		
		Associate(CComBSTR(L"Mga.AddOn.ConstraintManager"), name, mode);     // no error checking
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::QueryParadigmAllGUIDs(BSTR parname, VARIANT *guidstrs, regaccessmode_enum mode) {
	CHECK_OUT(guidstrs);
	COLE2CT parname2(parname);
	CString pname(parname2); 

	COMTRY
	{
		CStringArray ret;
		if(mode & RM_USER) {
			CRegKey par;
			LONG res = par.Open(HKEY_CURRENT_USER, rootreg+"\\Paradigms\\" + pname, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				for(int index = 0;; ++index) {
					TCHAR name[1024];
					LONG err = RegEnumKey(par, index, name, 1024);
					if( err == ERROR_NO_MORE_ITEMS )
						break;
					ERRTHROW( err );

					REVOKE_SYS2(mode);
					ret.Add(name);
				}

			}
		}
		int retlen = ret.GetSize();

		if(mode & RM_SYSDOREAD) {
			CRegKey par;
			LONG res = par.Open(HKEY_LOCAL_MACHINE, rootreg+"\\Paradigms\\" + pname, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				CString cur = QueryValue(par, "CurrentVersion");
				if(!cur.IsEmpty()) {  // New style: Connection strings are stored under GUID subkeys
				  for(int index = 0;; ++index) {
					TCHAR name[1024];
					LONG err = RegEnumKey(par, index, name, 1024);
					if( err == ERROR_NO_MORE_ITEMS )
						break;
					ERRTHROW( err );
					int j;
					for(j = 0; j < retlen; j++) {		// Make sure, name is not present already, if yes system copy is ignored
						if(!ret[j].CompareNoCase(name)) break;
					}
					if(j != retlen) continue;
					ret.Add(name);
				  }
				}
				else {
					CString name = QueryValue(par, "GUID");
					int j;
					for(j = 0; j < retlen; j++) {		// Make sure, name is not present already, if yes system copy is ignored
						if(!ret[j].CompareNoCase(name)) break;
					}
					if(j == retlen) ret.Add(name);
				}
			}
		}


		CopyTo(ret, guidstrs);
	}
	COMCATCH(;)
}


STDMETHODIMP CMgaRegistrar::QueryParadigm(BSTR parname, BSTR *connstr, VARIANT *guid, regaccessmode_enum mode)
{
	CHECK_OUT(connstr);
//	CHECK_OUT(guid);

	COMTRY
	{
		CString pname = PutInCString(parname);

		CRegKey subk;
		CString guidact;

		CComBstrObj inguidstr;
		if(guid->vt != VT_EMPTY) {
			GUID g;
			CopyTo(*guid, g);
			CopyTo(g, inguidstr);
//			if(inguidstr == L"{00000000-0000-0000-0000-000000000000}") inguidstr = NULL;
		}

		LONG res;

		if(mode & RM_USER) {
			CRegKey par;
			res = par.Open(HKEY_CURRENT_USER, rootreg + "\\Paradigms\\" + pname, KEY_READ);
			if(res == ERROR_SUCCESS) {
				// REVOKE_SYS2(mode);						// paradigm found, ignore system settings
				if(inguidstr == NULL) {
					guidact = QueryValue(par, "CurrentVersion");
					if(guidact.IsEmpty()) res = ERROR_FILE_NOT_FOUND;
				}
				else	guidact = inguidstr;
			}
			if(res == ERROR_SUCCESS) res = subk.Open(par, guidact, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS)   mode = REGACCESS_USER;
		}

		if(mode & RM_SYSDOREAD) {
			CRegKey par;
			res = par.Open(HKEY_LOCAL_MACHINE, rootreg + "\\Paradigms\\" + pname, KEY_READ);
			if(res == ERROR_SUCCESS) {
				CString cur = QueryValue(par, "CurrentVersion");
				if(cur.IsEmpty()) {
					guidact = QueryValue(par, "GUID");
					if(inguidstr != NULL && inguidstr != CComBSTR(guidact)) COMTHROW(E_NOTFOUND);
					subk.Attach(par.Detach());
				}
				else {
					if(inguidstr == NULL) guidact = cur;
					else	guidact = inguidstr;
					res = subk.Open(par, guidact, KEY_READ);
					if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
				}
			}
		}
		if(subk == NULL) return(E_NOTFOUND);  // !!!!!!!


		CopyTo(QueryValue(subk, "ConnStr"), connstr);

		if(inguidstr == NULL) {
			GUID g;
			CopyTo(CComBSTR(guidact),g); 
			CopyTo(g, guid);
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::get_ParadigmGUIDString(regaccessmode_enum mode, BSTR parname, BSTR *guidstr)
{
	CHECK_OUT(guidstr);
	COMTRY
	{
		CComBSTR connstr;
		CComVariant guid;
		COMTHROW(QueryParadigm(parname, &connstr, &guid, mode));
		GUID g;
		CopyTo(guid, g);
		CopyTo(g, guidstr);
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::VersionFromGUID(BSTR name, VARIANT guid, BSTR *ver, regaccessmode_enum mode)
{
	CHECK_OUT(ver);

	bool found = false;
	COMTRY
	{
		GUID gg;
		CopyTo(guid,gg);
		CComBstrObj guidbstr;
		CopyTo(gg, guidbstr);

		LONG res;

		if(mode & RM_USER) {
			CRegKey par;
			res = par.Open(HKEY_CURRENT_USER, rootreg + "\\Paradigms\\"+name, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				mode = REGACCESS_USER;
				for(int index = 0;; ++index) {
					TCHAR name[512];
					DWORD namesize = sizeof(name);
					BYTE value[512];
					DWORD valuesize = sizeof(value);
					DWORD valtype;

					LONG err = RegEnumValue(par, index, name, &namesize, NULL, &valtype, value, &valuesize);
					if( err == ERROR_NO_MORE_ITEMS )
						break;
					ERRTHROW( err );
					if (valtype == REG_SZ) {
						CString cver(value);
						if (cver.Compare(PutInCString(guidbstr)) == 0) {
							CString namestr(name);
							if (namestr.CompareNoCase("CurrentVersion") != 0) {
								found = true;
								CopyTo(namestr, ver);
							}
						}
					}
				}
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey par;
			res = par.Open(HKEY_LOCAL_MACHINE, rootreg + "\\Paradigms\\"+name, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				for(int index = 0;; ++index) {
					TCHAR name[512];
					DWORD namesize = sizeof(name);
					BYTE value[512];
					DWORD valuesize = sizeof(value);
					DWORD valtype;

					LONG err = RegEnumValue(par, index, name, &namesize, NULL, &valtype, value, &valuesize);
					if( err == ERROR_NO_MORE_ITEMS )
						break;
					ERRTHROW( err );
					if (valtype == REG_SZ) {
						CString cver(value);
						if (cver.Compare(PutInCString(guidbstr)) == 0) {
							CString namestr(name);
							if (namestr.CompareNoCase("CurrentVersion") != 0) {
								found = true;
								CopyTo(namestr, ver);
							}
						}
					}
				}
			}
		}
		if(!found) return(E_NOTFOUND);
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::GUIDFromVersion(BSTR name, BSTR ver, VARIANT* guid, regaccessmode_enum mode)
{
	CHECK_OUT(guid);

	CString verstr = PutInCString(ver);
	CString gstr;

	COMTRY
	{
		LONG res;

		if(mode & RM_USER) {
			CRegKey par;
			res = par.Open(HKEY_CURRENT_USER, rootreg + "\\Paradigms\\"+name, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) { 
				gstr = QueryValue(par, verstr);
				if (!gstr.IsEmpty()) {
					mode = REGACCESS_USER;
				}
			}
		}
		if(mode & (RM_SYSDOREAD)) {
			CRegKey par;
			res = par.Open(HKEY_LOCAL_MACHINE, rootreg + "\\Paradigms\\"+name, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) { 
				gstr = QueryValue(par, verstr);
			}
		}

		if (gstr.IsEmpty()) {
			ERRTHROW(E_NOTFOUND);
		}

		GUID g;
		CopyTo(CComBSTR(gstr),g); 
		CopyTo(g, guid);
	}
	COMCATCH(;)
}


STDMETHODIMP CMgaRegistrar::UnregisterParadigmGUID(BSTR name, VARIANT v, regaccessmode_enum mode)
{				// it cannot be unregistered if it is the current version
	COMTRY
	{
		GUID gg;
		CopyTo(v,gg);
		CComBstrObj guidbstr;
		CopyTo(gg, guidbstr);

		if(mode & RM_USER) {
			CRegKey par;
			ERRTHROW( par.Open(HKEY_CURRENT_USER, rootreg + "\\Paradigms\\"+name) );
			CString cur = QueryValue(par, "CurrentVersion");
			if(cur.Compare(PutInCString(guidbstr)) == 0) {
				COMTHROW(E_INVALID_USAGE);
			}
			
			for(int index = 0;; ++index) {
				TCHAR name[512];
				DWORD namesize = sizeof(name);
				BYTE value[512];
				DWORD valuesize = sizeof(value);
				DWORD valtype;

				LONG err = RegEnumValue(par, index, name, &namesize, NULL, &valtype, value, &valuesize);
				if( err == ERROR_NO_MORE_ITEMS )
					break;
				ERRTHROW( err );
				if (valtype == REG_SZ) {
					CString cver(value);
					if (cver.Compare(PutInCString(guidbstr)) == 0) {
						RegDeleteValue(par, name);
					}
				}
			}

			ERRTHROW( par.RecurseDeleteKey(PutInCString(guidbstr)) );
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey par;
			ERRTHROW( par.Open(HKEY_LOCAL_MACHINE, rootreg + "\\Paradigms\\"+name) );
			CString cur = QueryValue(par, "CurrentVersion");
			if(cur.Compare(PutInCString(guidbstr)) == 0) {
				COMTHROW(E_INVALID_USAGE);
			}
			if(mode & RM_SYS) {
				ERRTHROW( par.RecurseDeleteKey(PutInCString(guidbstr)) );
				for(int index = 0;; ++index) {
					TCHAR name[512];
					DWORD namesize = sizeof(name);
					BYTE value[512];
					DWORD valuesize = sizeof(value);
					DWORD valtype;

					LONG err = RegEnumValue(par, index, name, &namesize, NULL, &valtype, value, &valuesize);
					if( err == ERROR_NO_MORE_ITEMS )
						break;
					ERRTHROW( err );
					if (valtype == REG_SZ) {
						CString cver(value);
						if (cver.Compare(PutInCString(guidbstr)) == 0) {
							RegDeleteValue(par, name);
						}
					}
				}
			}
			if(mode & RM_TEST) ERRTHROW( par.Open(par, PutInCString(guidbstr)) );
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::UnregisterParadigm(BSTR name, regaccessmode_enum mode)
{
	COMTRY
	{
		if(mode & RM_USER) {
			CRegKey pars;
			LONG res = pars.Open(HKEY_CURRENT_USER, rootreg + "\\Paradigms");
			if(!res) res = pars.RecurseDeleteKey(PutInCString(name));
			if(res == ERROR_FILE_NOT_FOUND) res = ERROR_SUCCESS;
			ERRTHROW(res);
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey pars;
			LONG res = pars.Open(HKEY_LOCAL_MACHINE, rootreg + "\\Paradigms");
			if(!res) {
				if(mode & RM_SYS) res = pars.RecurseDeleteKey(PutInCString(name));
				if(mode & RM_TEST) res = pars.Open(pars, PutInCString(name));
			}
			if(res == ERROR_FILE_NOT_FOUND) res = ERROR_SUCCESS;
			ERRTHROW(res);
		}
	}
	COMCATCH(;)
}

// throws hresult_exception
void GetComponents(HKEY hive, CStringArray& ret) {
	CRegKey comps;
	LONG res = comps.Open(hive, rootreg + "\\Components", KEY_READ);
	if (res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND)
		COMTHROW(HRESULT_FROM_WIN32(res));
	if (res == ERROR_SUCCESS) {
		for (int index = 0;; ++index) {
			TCHAR name[1024];
			LONG err = RegEnumKey(comps, index, name, 1024);
			if (err == ERROR_NO_MORE_ITEMS)
				break;
			ERRTHROW(err);

			CRegKey comp;
			err = comp.Open(comps, name, KEY_READ);
			DWORD type2;
			if (err == ERROR_SUCCESS)
				err = comp.QueryDWORDValue("Type", type2);
			if (err != ERROR_SUCCESS)
				continue;
			if((type2 & COMPONENTTYPE_SYSREGREF) != 0) { 
				continue;
			}
			// Make sure name is not present already
			int j;
			for (j = 0; j < ret.GetSize(); j++) {
				if (!ret[j].CompareNoCase(name))
					break;
			}
			if (j != ret.GetSize())
				continue;
			ret.Add(name);
		}
	}
}

STDMETHODIMP CMgaRegistrar::get_Components(regaccessmode_enum mode, VARIANT *progids)
{
	CHECK_OUT(progids);

	COMTRY
	{
		CStringArray ret;
		if (mode & REGACCESS_USER)
			GetComponents(HKEY_CURRENT_USER, ret);
		if (mode & REGACCESS_SYSTEM)
			GetComponents(HKEY_LOCAL_MACHINE, ret);
		CopyTo(ret, progids);
	}
	COMCATCH(;)
}

template<typename Functor>
void TokenizeParadigmString(const CString& paradigms, Functor x) {
	CStringList ret;
	int curPos = 0;
	CString token = paradigms.Tokenize(" ;,\n\t", curPos);
	while (token != "") {
		x(token);
		token = paradigms.Tokenize(" ;,\n\t", curPos);
	}
}

STDMETHODIMP CMgaRegistrar::RegisterComponent(BSTR progid, componenttype_enum type, BSTR desc, regaccessmode_enum mode)
{
	COMTRY
	{
		CComBstrObj paradigms(OLESTR("*"));
		if(!(type & COMPONENTTYPE_PARADIGM_INDEPENDENT)) {
			paradigms.Empty();
			CComPtr<IMgaComponent> comp;
			CreateMgaComponent(comp, progid);
			if(!comp) COMTHROW(E_MGA_COMPONENT_ERROR);
			COMTHROW(comp->get_Paradigm(PutOut(paradigms)));
		}
		if(mode & RM_USER) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_CURRENT_USER, rootreg) );
			CRegKey comps;
			ERRTHROW( comps.Create(mga, "Components") );
			CRegKey comp;
			ERRTHROW( comp.Create(comps, PutInCString(progid)) );

			ERRTHROW( comp.SetDWORDValue( "Type", (DWORD)type));

			ERRTHROW( comp.SetStringValue( "Description", PutInCString(desc)));
			if(paradigms.Length()) {
				TokenizeParadigmString(PutInCString(paradigms), [&comp](const CString& par) {
					ERRTHROW(comp.SetStringValue("Paradigm", par));
				});
			}
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey mga;
			ERRTHROW( mga.Create(HKEY_LOCAL_MACHINE, rootreg) );
			CRegKey comps;
			ERRTHROW( comps.Create(mga, "Components") );
			if(mode & RM_SYS) {
				CRegKey comp;
				ERRTHROW( comp.Create(comps, PutInCString(progid)) );
	
				ERRTHROW( comp.SetDWORDValue( "Type", (DWORD)type));

				ERRTHROW( comp.SetStringValue( "Description", PutInCString(desc)));
				TokenizeParadigmString(PutInCString(paradigms), [&comp](const CString& par) {
					ERRTHROW(comp.SetStringValue("Paradigm", par));
				});
			}
			else {
				CRegKey comp;
				LONG res = comp.Open(comps, PutInCString(progid));
				if(res != ERROR_SUCCESS && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			}
		}
	}
	COMCATCH(;)
}

// FIXME: mode is ignored. It should be removed next interface-breaking change
STDMETHODIMP CMgaRegistrar::QueryComponent(BSTR progid, componenttype_enum *type, BSTR *desc, regaccessmode_enum mode)
{
	CHECK_OUT(type);
	if(desc) CHECK_OUT(desc);
	CString progidstr = PutInCString(progid);

	COMTRY
	{
		DWORD dwType = -1;
		CString strDesc;
		HKEY hives[] = { HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE };
		for (int i = 0; i < 2; i++) {
			CRegKey comp;
			LONG res = comp.Open(hives[i], rootreg+"\\Components\\"+progidstr, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				comp.QueryDWORDValue("Type", dwType);
				ULONG count;
				res = comp.QueryStringValue("Description", NULL, &count);
				if (strDesc == "" && res == ERROR_SUCCESS) {
					CString ret;
					if (comp.QueryStringValue("Description", ret.GetBufferSetLength(count), &count) == ERROR_SUCCESS)
						strDesc = ret;
				}
			}
		}
		if (dwType == -1 || !(dwType & COMPONENTTYPE_ALL))
			COMTHROW(E_NOTFOUND);
		
		if (type)
			*type = (componenttype_enum)dwType;
		if (desc && strDesc != "")
			CopyTo(strDesc, desc);
		return S_OK;
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::UnregisterComponent(BSTR progid, regaccessmode_enum mode)
{
	COMTRY
	{
//		if(mode & RM_USER) {
		if(mode & (RM_USER | RM_SYS) ){
			CRegKey comps;
			LONG res = comps.Open(HKEY_CURRENT_USER, rootreg + "\\Components");

			DWORD type2 = 0;
			if(!res) {
				CRegKey comp;
				res =  comp.Open(comps, PutInCString(progid), KEY_READ);
				if(!res) comp.QueryDWORDValue( "Type", type2);
			}

			if((mode & RM_USER) || (type2 & COMPONENTTYPE_SYSREGREF) != 0 ) {
				if (!res) res = comps.RecurseDeleteKey(PutInCString(progid));
				if (res == ERROR_FILE_NOT_FOUND) res = ERROR_SUCCESS;
				ERRTHROW(res);
			}
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey comps;
			LONG res = comps.Open(HKEY_LOCAL_MACHINE, rootreg + "\\Components");
			if(!res) {
				if(mode & RM_SYS) res = comps.RecurseDeleteKey(PutInCString(progid));
				if(mode & RM_TEST) res = comps.Open(comps, PutInCString(progid));
			}
			if(res == ERROR_FILE_NOT_FOUND) res = ERROR_SUCCESS;
			ERRTHROW(res);
		}
	}
	COMCATCH(;)
}


STDMETHODIMP CMgaRegistrar::put_ComponentExtraInfo(regaccessmode_enum mode, 
												   BSTR progid, BSTR name, BSTR newVal) {
	CString progidstr = PutInCString(progid);

	COMTRY
	{
		if(mode & RM_USER) {
			CRegKey comp;
			LONG res = comp.Open(HKEY_CURRENT_USER, rootreg+"\\Components\\"+progidstr);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				DWORD type2;
				ERRTHROW( comp.QueryDWORDValue( "Type", type2));

				if((type2 & COMPONENTTYPE_ALL)) { 
					if(!newVal) { ERRTHROW( comp.DeleteValue(PutInCString(name)) );  }
					else		{ ERRTHROW( comp.SetStringValue( PutInCString(name), PutInCString(newVal))); }
				}
			}
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey comp;
			LONG res = comp.Open(HKEY_LOCAL_MACHINE, rootreg+"\\Components\\"+progidstr);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				DWORD type2;
				ERRTHROW( comp.QueryDWORDValue( "Type", type2));

				if((mode & RM_SYS) && (type2 & COMPONENTTYPE_ALL)) { 
					if(!newVal) { ERRTHROW( comp.DeleteValue(PutInCString(name)) );  }
					else		{ ERRTHROW( comp.SetStringValue( PutInCString(name), PutInCString(newVal))); }
				}
			}
		}
	
	} COMCATCH(;)
}

// FIXME: mode is ignored. It should be removed next interface-breaking change
STDMETHODIMP CMgaRegistrar::get_ComponentExtraInfo(regaccessmode_enum mode, 
												   BSTR progid, BSTR name, BSTR* pVal) {
	CHECK_OUT(pVal);
	CString progidstr = PutInCString(progid);

	COMTRY
	{
		HKEY hives[] = { HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE };
		for (int i = 0; i < 2; i++) {
			CRegKey comp;
			LONG res = comp.Open(hives[i], rootreg+"\\Components\\"+progidstr, KEY_READ);
			if(res != ERROR_SUCCESS && res != ERROR_ACCESS_DENIED && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			if(res == ERROR_SUCCESS) {
				ULONG count;
				res = comp.QueryStringValue(PutInCString(name), NULL, &count);
				if (res == ERROR_SUCCESS) {
					CString ret;
					if (comp.QueryStringValue(PutInCString(name), ret.GetBufferSetLength(count), &count) == ERROR_SUCCESS) {
						CopyTo(ret, pVal);
						return S_OK;
					}
				}
			}
		}
		return E_NOTFOUND;
	}
	COMCATCH(;)
}


STDMETHODIMP CMgaRegistrar::get_LocalDllPath(BSTR progid, BSTR* pVal) {
	CHECK_OUT(pVal);
	COMTRY
	{
		CString m_strProgId = PutInCString(progid);
		CRegKey comp;
		CString m_strClassId;
		for(int i = 0; i < 10; i++) {
			LONG res = comp.Open(HKEY_CLASSES_ROOT, m_strProgId + "\\CLSID", KEY_READ);
			if(res == ERROR_SUCCESS) {
				m_strClassId = QueryValue(comp,"" );
				break;
			}
			else {
				res = comp.Open(HKEY_CLASSES_ROOT, m_strProgId + "\\CurVer", KEY_READ);
				if(res != ERROR_SUCCESS) COMTHROW(E_NOTFOUND);
				m_strProgId = QueryValue(comp, "" );
				comp.Close();
			}
		}
		if(m_strClassId.IsEmpty()) COMTHROW(E_NOTFOUND);

		LONG res = comp.Open(HKEY_CLASSES_ROOT, "CLSID\\" + m_strClassId + "\\InprocServer32", KEY_READ);
		CString m_strPath;
		if(res == ERROR_SUCCESS) {
			m_strPath = QueryValue(comp, "" );
			if (m_strPath == "mscoree.dll") {
				char data[MAX_PATH];
				ULONG num_bytes = sizeof(data) / sizeof(data[0]);
				if (comp.QueryValue("CodeBase", 0, data, &num_bytes) == ERROR_SUCCESS) {
					m_strPath = data;
					m_strPath = m_strPath.Right(m_strPath.GetLength() - 8);
					m_strPath.Replace('/', '\\');
				} else {
					if (comp.QueryValue("Assembly", 0, data, &num_bytes) == ERROR_SUCCESS) {
						m_strPath = "GAC: ";
						m_strPath += data;
					}
				}
			}
		}
		CopyTo(m_strPath, pVal);

	}
	COMCATCH(;)
}

enum Tristate_t {
	Tristate_Enabled,
	Tristate_Disabled,
	Tristate_Not_Specified,
};

bool Combine_Tristate(Tristate_t user, Tristate_t system, bool default_ = false) {
	if (user != Tristate_Not_Specified) {
		return user == Tristate_Enabled;
	}
	if (system != Tristate_Not_Specified) {
		return system == Tristate_Enabled;
	}
	return default_;
}

Tristate_t IsAssociated_hive(const CString& progidstr, const CString& paradigmstr, HKEY hive) {
	CRegKey acomp;

	if (acomp.Open(hive, rootreg + "\\Components\\" + progidstr + "\\Associated", KEY_READ) != ERROR_SUCCESS) {
		return Tristate_Not_Specified;
	}
	ULONG count;
	DWORD res = acomp.QueryValue(paradigmstr, NULL, NULL, &count);
	if (res != ERROR_SUCCESS) {
		return Tristate_Not_Specified;
	}
	CString val;
	if (acomp.QueryStringValue(paradigmstr, val.GetBufferSetLength(count), &count) == ERROR_SUCCESS) {
		val.ReleaseBuffer();
		if (val == "Disabled") {
			return Tristate_Disabled;
		}
	}
	return Tristate_Enabled;
}

bool IsAssociated_regaccess(const CString& progidstr, const CString& paradigmstr, regaccessmode_enum mode) {
	if (mode & REGACCESS_BOTH) {
		return  Combine_Tristate(
				IsAssociated_hive(progidstr, paradigmstr, HKEY_CURRENT_USER),
				IsAssociated_hive(progidstr, paradigmstr, HKEY_LOCAL_MACHINE));
	} else if (mode & REGACCESS_USER) {
		return IsAssociated_hive(progidstr, paradigmstr, HKEY_CURRENT_USER) == Tristate_Enabled;
	} else if (mode & REGACCESS_SYSTEM) {
		return IsAssociated_hive(progidstr, paradigmstr, HKEY_LOCAL_MACHINE) == Tristate_Enabled;
	}
	return false;
}

STDMETHODIMP CMgaRegistrar::get_AssociatedComponents(BSTR paradigm, 
	componenttype_enum type, regaccessmode_enum mode, VARIANT *progids)
{
	CHECK_OUT(progids);
	type = (componenttype_enum)(type & COMPONENTTYPE_ALL);

	COMTRY
	{
		CStringArray ret;

		CString paradigmstr;
		CopyTo(paradigm, paradigmstr);

		CStringArray components;
		if (mode & REGACCESS_USER)
			GetComponents(HKEY_CURRENT_USER, components);
		if (mode & REGACCESS_SYSTEM)
			GetComponents(HKEY_LOCAL_MACHINE, components);
		for (int i = 0; i < components.GetSize(); i++) {
			componenttype_enum comptype = COMPONENTTYPE_NONE;
			PutInBstr progid(components.GetAt(i));
			CComBSTR desc;
			COMTHROW(QueryComponent(progid, &comptype, &desc, REGACCESS_BOTH));
			if ((comptype & type) && IsAssociated_regaccess(components.GetAt(i), paradigmstr, mode)) {
				ret.Add(components.GetAt(i));
			}
		}
		CopyTo(ret, progids);
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::get_AssociatedParadigms(BSTR progid, regaccessmode_enum mode, VARIANT *paradigms)
{
	CHECK_OUT(paradigms);

	COMTRY
	{

		CStringArray ret;
		CString progidstr = PutInCString(progid);

		VARIANT all_paradigms_;
		COMTHROW(get_Paradigms(REGACCESS_BOTH, &all_paradigms_));
		ATL::CComSafeArray<BSTR> all_paradigms;
		all_paradigms.Attach(all_paradigms_.parray);
		for (ULONG i = 0; i < all_paradigms.GetCount(); i++) {
			BSTR paradigm = all_paradigms.GetAt(i);
			if (IsAssociated_regaccess(progidstr, PutInCString(paradigm), mode)) {
				ret.Add(static_cast<const CString&>(PutInCString(paradigm)));
			}
		}

		CopyTo(ret, paradigms);
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::Associate(BSTR progid, BSTR paradigm, regaccessmode_enum mode)
{
	COLE2CT progid2(progid);
	CString pname(progid2);
	COMTRY
	{
		bool somethingdone = false;
		if(mode & RM_USER) {		
			CRegKey comp;
			LONG res = comp.Open(HKEY_CURRENT_USER, rootreg + "\\Components\\" + pname);
			CRegKey assocs;
			if(res == ERROR_FILE_NOT_FOUND) {   // try to create a shadow registry
				CRegKey comp1, mga;
				res = comp1.Open(HKEY_LOCAL_MACHINE, rootreg + "\\Components\\" + pname, KEY_READ);
				if(!res) res = mga.Create(HKEY_CURRENT_USER, rootreg);
				CRegKey comps;
				if(!res) res = ( comps.Create(mga, "Components") );
				if(!res) res = ( comp.Create(comps, pname) );
			}
			if(!res) res = assocs.Create(comp, "Associated");
			if(!res) assocs.SetStringValue( PutInCString(paradigm), "");
			if(!res) somethingdone = true;
			if(res == ERROR_FILE_NOT_FOUND) res = ERROR_SUCCESS;
			ERRTHROW(res);
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey comp;
			LONG res = comp.Open(HKEY_LOCAL_MACHINE, rootreg + "\\Components\\" + pname);
			if(mode & RM_SYS) {
				CRegKey assocs;
				if(!res) res = assocs.Create(comp, "Associated");
				if(!res) res = assocs.SetStringValue( PutInCString(paradigm), "");
			}
			else {
				CRegKey assocs;
				LONG res = assocs.Open(comp, "Associated");
				if(res != ERROR_SUCCESS && res != ERROR_FILE_NOT_FOUND) ERRTHROW(res);
			}
			if(!res) somethingdone = true;
		}
		if(!somethingdone) COMTHROW(E_NOTFOUND);
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::Disassociate(BSTR progid, BSTR paradigm, regaccessmode_enum mode)
{
	COLE2CT progid2(progid);
	CString pname(progid2);
	COMTRY
	{
		if(mode & RM_USER) {		
			CRegKey comp;
			LONG res = comp.Open(HKEY_CURRENT_USER, rootreg + "\\Components\\" + pname);
			CRegKey assocs;
			if(!res) res = assocs.Open(comp, "Associated");
			if (res == ERROR_FILE_NOT_FOUND) 
				res = assocs.Create(comp, "Associated");
			if (!res)
				res = assocs.SetStringValue(PutInCString(paradigm), "Disabled");
			if(res == ERROR_FILE_NOT_FOUND) res = ERROR_SUCCESS;
			ERRTHROW(res);
		}
		if(mode & (RM_SYS | RM_TEST)) {
			CRegKey comp;
			LONG res = comp.Open(HKEY_LOCAL_MACHINE, rootreg + "\\Components\\" + pname);
			CRegKey assocs;
			if(!res) res = assocs.Open(comp, "Associated");
			if(mode & RM_SYS) {
				if(!res) res = assocs.DeleteValue(PutInCString(paradigm));
			}
			if(res == ERROR_FILE_NOT_FOUND) res = ERROR_SUCCESS;
			ERRTHROW(res);
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::IsAssociated(BSTR progid, BSTR paradigm, 
										VARIANT_BOOL *is_ass, VARIANT_BOOL *can_ass, regaccessmode_enum mode){
	CHECK_IN(progid);
	CHECK_OUT(paradigm);
	CString progidstr = PutInCString(progid);
	CString parc = PutInCString(paradigm);

	COMTRY
	{
		componenttype_enum type;

		COMTHROW(QueryComponent(progid, &type, NULL, REGACCESS_PRIORITY));

		if (is_ass) *is_ass = IsAssociated_regaccess(progidstr, parc, mode) ? VARIANT_TRUE : VARIANT_FALSE;

		if (can_ass) *can_ass = VARIANT_FALSE;
		VARIANT_BOOL can = VARIANT_FALSE;
		CComBSTR pars;
		get_ComponentExtraInfo(mode,progid,CComBSTR("Paradigm"), &pars);
		if(!pars && !(type & COMPONENTTYPE_SCRIPT)) {
			CComPtr<IMgaComponent> comp;
			CreateMgaComponent(comp, progid);
			if(!comp) COMTHROW(E_NOTFOUND);
			COMTHROW(comp->get_Paradigm(&pars));
			put_ComponentExtraInfo(REGACCESS_BOTH, progid, CComBSTR("Paradigm"), pars);  // just try
		}
		if(!pars) {
			can = type & COMPONENTTYPE_PARADIGM_INDEPENDENT ? VARIANT_TRUE : VARIANT_FALSE;
		}
		else if(!wcscmp(pars, L"*")) {
			can = VARIANT_TRUE;
		}
		else {
			can = VARIANT_FALSE;
			TokenizeParadigmString(PutInCString(pars), [&paradigm, &can](const CString& paradigm2) {
				if (static_cast<const CString &>(PutInCString(paradigm)) == paradigm2)
					can = VARIANT_TRUE;
			});
		}	
		if(can_ass) *can_ass = can;
		
	}
	COMCATCH(;)
}


// --- Actions
typedef HRESULT (STDAPICALLTYPE *CTLREGPROC)();

STDMETHODIMP CMgaRegistrar::RegisterComponentLibrary(BSTR path, regaccessmode_enum mode)
{
	COMTRY
	{
		HMODULE hModule = LoadLibrary(CString(path));
		if( hModule == 0 )
			HR_THROW(E_FAIL);

		CTLREGPROC DLLRegisterServer =
			(CTLREGPROC)::GetProcAddress(hModule,"DllRegisterServer" );
		
		if( DLLRegisterServer == NULL )
		{
			FreeLibrary(hModule);
			//CLR dll:
			using namespace MgaDotNetServices;
			CComPtr<_Registrar> reg;
			COMTHROW(reg.CoCreateInstance(L"MGA.DotNetRegistrar"));
			try {
				reg->Register(_bstr_t(path));
			} catch (_com_error& e) {
				SetErrorInfo(e.Error(), e.Description());
				return e.Error();
			}

			return S_OK;
		}
		else
		{
			//c++ dll:
			COMTHROW( DLLRegisterServer() );
			FreeLibrary(hModule);
		}


		CComObjPtr<ITypeLib> typelib;
		COMTHROW( LoadTypeLibEx(path, REGKIND_REGISTER, PutOut(typelib)) );

		UINT index = typelib->GetTypeInfoCount();
		while( index-- > 0 )
		{
			CComObjPtr<ITypeInfo> typeinfo;
			COMTHROW( typelib->GetTypeInfo(index, PutOut(typeinfo)) );

			TYPEATTR *typeattr = NULL;
			COMTHROW( typeinfo->GetTypeAttr(&typeattr) );
			ASSERT( typeattr != NULL );

			try
			{
				if( typeattr->typekind == TKIND_COCLASS )
				{
					CComPtr<IMgaComponent> component;
					// if( SUCCEEDED(typeinfo->CreateInstance(NULL, 
					//	__uuidof(IMgaComponent), (void**)PutOut(component))) )
					if (SUCCEEDED(CreateMgaComponent(component, typeattr->guid)))
					{
						CComBstrObj desc;
						COMTHROW( component->get_ComponentName(PutOut(desc)) );

						componenttype_enum type;
						COMTHROW( component->get_ComponentType(&type) );

						LPOLESTR olestr;
						COMTHROW( ProgIDFromCLSID(typeattr->guid, &olestr) );
						CComBstrObj progid(olestr);
						{
							LPOLESTR pp = olestr + wcslen(olestr) - 2;
							if(wcslen(olestr) > 2 && 
								pp[0] == '.' &&
								isdigit(pp[1]) ) {
								pp[0] = 0;
								CLSID tempGUID;
								HRESULT hr = CLSIDFromProgID(olestr, &tempGUID);
								if(hr == S_OK && tempGUID == typeattr->guid) {
									progid = olestr;
								}
							}
						}

						COMTHROW( RegisterComponent(progid, type, desc, mode) );
						CoTaskMemFree(olestr);

						CString paradigms;
						COMTHROW( component->get_Paradigm(PutOut(paradigms)) );

						TokenizeParadigmString(paradigms, [this,&mode,&progid](const CString& par){
							COMTHROW(Associate(progid, PutInBstr(par), mode));
						});
					}
				}

				typeinfo->ReleaseTypeAttr(typeattr);
			}
			catch(hresult_exception &)
			{
				typeinfo->ReleaseTypeAttr(typeattr);
				throw;
			}
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaRegistrar::UnregisterComponentLibrary(BSTR path, regaccessmode_enum mode)
{
	COMTRY
	{
		CComObjPtr<ITypeLib> typelib;
		COMTHROW( LoadTypeLibEx(path, REGKIND_NONE, PutOut(typelib)) );

		UINT index = typelib->GetTypeInfoCount();
		while( index) //WAS: while( --index >= 0 ) // was an infinite loop with UINT
		{
			--index;
			CComObjPtr<ITypeInfo> typeinfo;
			COMTHROW( typelib->GetTypeInfo(index, PutOut(typeinfo)) );// index parameter with the range of 0 to GetTypeInfoCount() –1.

			TYPEATTR *typeattr = NULL;
			COMTHROW( typeinfo->GetTypeAttr(&typeattr) );
			ASSERT( typeattr != NULL );

			try
			{
				if( typeattr->typekind == TKIND_COCLASS )
				{
					LPOLESTR olestr;
					if( SUCCEEDED(ProgIDFromCLSID(typeattr->guid, &olestr)) )
					{
						CComBstrObj progid(olestr);
						COMTHROW( UnregisterComponent(progid, mode) );
					}
				}

				typeinfo->ReleaseTypeAttr(typeattr);
			}
			catch(hresult_exception &)
			{
				typeinfo->ReleaseTypeAttr(typeattr);
				throw;
			}
		}

		// TODO: unregister the type library
	}
	COMCATCH(;)
}
