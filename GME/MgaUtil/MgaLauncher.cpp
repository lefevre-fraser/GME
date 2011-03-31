
#include "stdafx.h"
#include "htmlhelp.h"
#include "MgaLauncher.h"

#include "MetaDlg.h"
#include "GmeDlg.h"
#include "CompDlg.h"
#include "RegistryBrowserDlg.h"
#include "AnnotationBrowserDlg.h"
#include "CommonComponent.h"

#include <comutil.h>
#include <comdef.h>

#include "CrashRpt.h"
#ifdef _DEBUG
#pragma comment(lib, "CrashRptd.lib")
#else
#pragma comment(lib, "CrashRpt.lib")
#endif


/* Deprecated Web based help
#define GME_UMAN_HOME				"http://www.isis.vanderbilt.edu/projects/GME/Doc/UsersManual/"
#define GME_UMAN_CONTENTS			"helpcontents1.htm"
#define GME_UMAN_MODEL				"models.htm"
#define GME_UMAN_ATOM				"atoms.htm"
#define GME_UMAN_REFERENCE			"references.htm"
#define GME_UMAN_SET				"sets.htm"
#define GME_UMAN_CONNECTION			"connectionsandlinks.htm"
#pragma bookmark ( change when folders.htm exists for documentation )
#define GME_UMAN_FOLDER				"themodelbrowser.htm"
*/

#define GME_UMAN_HOME				"Doc/GME Manual and User Guide.chm::/"
#define GME_UMAN_CONTENTS			"index.html"
#define GME_UMAN_MODEL				"models.html"
#define GME_UMAN_ATOM				"atoms.html"
#define GME_UMAN_REFERENCE			"references.html"
#define GME_UMAN_SET				"sets.html"
#define GME_UMAN_CONNECTION			"connectionsandlinks.html"
#pragma bookmark ( change when folders.htm exists for documentation )
#define GME_UMAN_FOLDER				"themodelbrowser.html"


// --------------------------- CMgaLauncher

STDMETHODIMP CMgaLauncher::put_ParadigmName(BSTR p)
{
	COMTRY
	{
		paradigmname = p;
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaLauncher::put_Parameter(VARIANT p)
{
	COMTRY
	{
		parameter = p;
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaLauncher::put_ComponentType(componenttype_enum type)
{
	comptype = type;

	return S_OK;
}

STDMETHODIMP CMgaLauncher::get_ParadigmName(BSTR *p)
{
	CHECK_OUT(p);

	COMTRY
	{
            CopyTo(paradigmname, p);
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaLauncher::get_ConnStr(BSTR *p)
{
	CHECK_OUT(p);

	COMTRY
	{
		CopyTo(connstr, p);
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaLauncher::get_ProgID(BSTR *p)
{
	CHECK_OUT(p);

	COMTRY
	{
		CopyTo(progid, p);
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaLauncher::get_Paradigm(IMgaMetaProject **p)
{
	CHECK_OUT(p);

	COMTRY
	{
		CopyTo(paradigm, p);
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaLauncher::MetaDlg(metadlg_enum flags)
{
	COMTRY
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		connstr.Empty();
		paradigm.Release();

		CMetaDlg dlg;

		dlg.name = paradigmname;
		dlg.flags = flags;

		if( dlg.DoModal() != IDOK )
			COMRETURN(S_FALSE);

		paradigmname = dlg.name;
		if( paradigmname.IsEmpty() )
			COMRETURN(S_FALSE);

		connstr = dlg.connstr;
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaLauncher::GmeDlg()
{
	COMTRY
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		CGmeDlg dlg;

		if( dlg.DoModal() != IDOK )
			COMRETURN(S_FALSE);
	} 
	COMCATCH(;)
}

STDMETHODIMP CMgaLauncher::ComponentDlg(componentdlg_enum flags)
{
	COMTRY
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		progid.Empty();

		CCompDlg dlg;

		dlg.paradigm = paradigmname;
		dlg.type = comptype;
		dlg.parameter = parameter;

		if( dlg.DoModal() != IDOK )
			COMRETURN(S_FALSE);

		progid = dlg.progid;
		if( progid.IsEmpty() )
			COMRETURN(S_FALSE);
	}
	COMCATCH(;)
}


STDMETHODIMP CMgaLauncher::PropDlg(IMgaObject * obj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	COMTRY
	{

		CComPtr<IMgaFCO> fco;
		CComPtr<IMgaFolder> folder;

		if ( SUCCEEDED( obj->QueryInterface(&fco) )) {

			objtype_enum obj_type;

			COMTHROW( fco->get_ObjType(&obj_type));

			if (obj_type == OBJTYPE_CONNECTION) {

				CComPtr<IMgaSimpleConnection> imsc;

				if (SUCCEEDED(fco.QueryInterface(&imsc))) {

//					CConnPropertiesDlg dlg(
//						conn->src->name,
//						conn->srcPort ? conn->srcPort->name : "-",
//						conn->dst->name,
//						conn->dstPort ? conn->dstPort->name : "-",
//						conn->roleName,
//						iden,
//						conn->name,
//						isType);

					CString src_name, srcPort_name, dst_name, dstPort_name, roleName, iden, conn_name,
							metaid, kind, aspect;
					bool isType;

					CComPtr<IMgaObject> obj_par_src;
					CComPtr<IMgaObject> obj_par_dst;
					CComPtr<IMgaFCO> fco_tmp;
					CComBSTR bstr_tmp;
					objtype_enum obj_type;
					VARIANT_BOOL equal_pars = VARIANT_FALSE;

					COMTHROW( imsc->get_Name(&bstr_tmp) );
					conn_name = CString(bstr_tmp);
					
					long relid;
					COMTHROW( imsc->get_RelID(&relid) );

					bstr_tmp.Empty();
					fco_tmp = NULL;

					COMTHROW( imsc->get_Src(&fco_tmp) );
					ASSERT(fco_tmp != NULL);
					COMTHROW( fco_tmp->get_Name(&bstr_tmp) );
					COMTHROW( fco_tmp->GetParent(&obj_par_src, &obj_type) );
					ASSERT( obj_par_src != NULL );
					src_name = CString(bstr_tmp);

					bstr_tmp.Empty();
					fco_tmp = NULL;

					COMTHROW( imsc->get_Dst(&fco_tmp) );
					ASSERT(fco_tmp != NULL);
					COMTHROW( fco_tmp->get_Name(&bstr_tmp) );
					COMTHROW( fco_tmp->GetParent(&obj_par_dst, &obj_type) );
					ASSERT( obj_par_dst != NULL );
					dst_name = CString(bstr_tmp);

					bstr_tmp.Empty();
					fco_tmp = NULL;

					COMTHROW( imsc->get_ID(&bstr_tmp) );
					iden = CString(bstr_tmp);

					bstr_tmp.Empty();
					fco_tmp = NULL;

					CComPtr<IMgaMetaRole> immr;
					COMTHROW( imsc->get_MetaRole(&immr) );
					ASSERT(immr != NULL);
					COMTHROW( immr->get_Name(&bstr_tmp) );
					roleName = CString(bstr_tmp);


					VARIANT_BOOL inst;
					COMTHROW(imsc->get_IsInstance(&inst));
					isType = (inst == VARIANT_FALSE);

					COMTHROW( obj_par_src->get_IsEqual(obj_par_dst, &equal_pars) );

					if (equal_pars != VARIANT_FALSE) {

						srcPort_name = CString("-");
						dstPort_name = CString("-");
					} else {

						bstr_tmp.Empty();
						COMTHROW( obj_par_src->get_Name(&bstr_tmp) );
						srcPort_name = CString(bstr_tmp);

						bstr_tmp.Empty();
						COMTHROW( obj_par_dst->get_Name(&bstr_tmp) );
						dstPort_name = CString(bstr_tmp);
					}

					{
						CComPtr<IMgaMetaFCO> metaFco;
						COMTHROW(fco->get_Meta(&metaFco));
						CString txt = "N/A";
						if(metaFco != 0) {
							CComBSTR bstr;
							COMTHROW(metaFco->get_DisplayedName(&bstr));
							CopyTo(bstr,kind);
						}
//						kind.SetWindowText(txt);
						metaref_type mid = 0;
						COMTHROW(metaFco->get_MetaRef(&mid));
						metaid.Format(_T("%ld"),(long)mid);
					}


					{ // aspects: multiple possible and one may be primary

						bool first = true;

						aspect = _T("-");
						CComPtr<IMgaParts> parts;
						COMTHROW(fco->get_Parts(&parts));

						CComPtr<IMgaPart> impart_ix;

						if(parts != NULL) {

							aspect = _T("");

							MGACOLL_ITERATE(IMgaPart,parts) {

								impart_ix = MGACOLL_ITER;

								ASSERT(impart_ix != NULL);

								CComPtr<IMgaMetaAspect> asp;
								CComBSTR aspname;
								COMTHROW( impart_ix->get_MetaAspect(&asp) );
								COMTHROW( asp->get_Name(&aspname) );

								if (!first) { aspect += _T("; "); } 
								else { first = false; }

								aspect += CString(aspname);

#pragma bookmark ( simplify here when IMgaPart::get_AccessMask() is available )

								CComPtr<IMgaMetaPart> mpart;
								COMTHROW( impart_ix->get_Meta(&mpart) );
								ASSERT( mpart != NULL );

								VARIANT_BOOL vb_pri_asp = VARIANT_FALSE;
								COMTHROW( mpart->get_IsPrimary(&vb_pri_asp) );

								if (vb_pri_asp != VARIANT_FALSE) {

									aspect += _T(" (primary)");
								}
							}
							MGACOLL_ITERATE_END;
							
						}
					}

					CConnPropertiesDlg ccpd(	src_name, srcPort_name,
												dst_name, dstPort_name,
												roleName,
												iden,
												conn_name,
												isType,
												metaid,
												kind,
												aspect,
												relid
						);


					if (ccpd.DoModal() == IDOK) {

						// check to see if a name change occurred

						if (ccpd.m_sz_pre_edit_name != ccpd.name) {

							COMTHROW( fco->put_Name( CComBSTR(ccpd.name)) );
						}
						long rl = _tcstol(ccpd.m_relid,NULL,0);
						if(rl != relid) {
							if(rl <= 0) AfxMessageBox(_T("Invalid RelID value, ignored"));
							else if(IDOK ==AfxMessageBox(_T("Setting Relative ID-s") 
													_T(" is a dangerous operation.\nProceed?"),
													MB_OKCANCEL)) {

								COMTHROW( fco->put_RelID( rl) );

							}
						}
					}

				} else {

					AfxMessageBox(_T("Non-simple connections currently unsupported object type for Properties."));
				}

//				AfxMessageBox(_T("Connections currently unsupported object type for Properties."));

			} else {

				CPropertiesDlg cpd(fco);

				if (cpd.DoModal() == IDOK) {

					// check to see if a name change occurred

					if (cpd.m_sz_pre_edit_name != cpd.name) {

						COMTHROW( fco->put_Name( CComBSTR(cpd.name)) );
					}
					long rl = _tcstol(cpd.m_relid,NULL,0);
					if(rl != cpd.relid) {
						if(rl <= 0) AfxMessageBox(_T("Invalid RelID value, ignored"));
						else if(IDOK ==AfxMessageBox(_T("Setting Relative ID-s") 
												_T(" is a dangerous operation.\nProceed?"),
												MB_OKCANCEL)) {
								COMTHROW( fco->put_RelID( rl) );
							}
					}
				}

			}
		}
		else if ( SUCCEEDED( obj->QueryInterface(&folder) )) {

				CFolderPropertiesDlg cpd(folder);

				if (cpd.DoModal() == IDOK) {

					// check to see if a name change occurred

					if (cpd.m_sz_pre_edit_name != cpd.name) {

						COMTHROW( folder->put_Name( CComBSTR(cpd.name)) );
					}
					long rl = _tcstol(cpd.m_relid,NULL,0);
					if(rl != cpd.relid) {
						if(rl <= 0) AfxMessageBox(_T("Invalid RelID value, ignored"));
						else if(IDOK ==AfxMessageBox(_T("Setting Relative ID-s") 
												_T(" is a dangerous operation.\nProceed?"),
												MB_OKCANCEL)) {
								COMTHROW( folder->put_RelID( rl) );
							}
					}
				}

		}
		else {

			AfxMessageBox(_T("Unsupported object type for Properties."));

		}

//		AfxMessageBox(_T("dummy PropDlg() implementation"));

	}
	COMCATCH(;)
}

STDMETHODIMP CMgaLauncher::AttrDlg(IMgaObject * obj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	COMTRY
	{

#ifdef _DEBUG
		AfxMessageBox(_T("dummy AttrDlg() implementation-- only in Debug version"));
#endif

	}
	COMCATCH(;)
}

LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata)
{
	HKEY hKey;
    LONG lResult = RegOpenKeyEx(key, subkey, 0, KEY_QUERY_VALUE, &hKey); 
  
    if( lResult == ERROR_SUCCESS)
	{
         long lDataSize = MAX_PATH;
		TCHAR data[MAX_PATH];
  
		RegQueryValue( hKey, NULL, data, &lDataSize);
		lstrcpy( retdata,data);
		RegCloseKey( hKey);
    }
  
    return lResult;
}
  
HINSTANCE GotoURL(LPCTSTR url, int showcmd)
{
//	HtmlHelp(NULL, url, HH_DISPLAY_TOPIC, 0);
//	return NULL;

	TCHAR key[MAX_PATH + MAX_PATH];
  
    // First try ShellExecute()
    HINSTANCE hResult = ShellExecute( NULL, _T("open"), url, NULL,NULL, showcmd);

    // If it failed, get the .htm regkey and lookup the program
	if( (UINT)hResult <= HINSTANCE_ERROR)
	{
		if( GetRegKey( HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS)
		{
			lstrcat( key, _T("\\shell\\open\\command")); 
  
            if( GetRegKey( HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS)
			{
				TCHAR *pos;
                pos = _tcsstr( key, _T("\"%1\"")); 
  
                if( pos == NULL)
				{
					// No quotes found
                    pos = _tcsstr( key, _T("%1")); // Check for % 1, without quotes
                    if( pos == NULL)    // No  parameter at all...
                        pos = key+lstrlen( key)-1;
                    else
						*pos = '\0';    //  Remove the parameter
                }
                else
					*pos = '\0';
					// Remove the parameter
  
                lstrcat(pos, _T(" "));
                lstrcat(pos, url);
  
				// FIXME: should use CreateProcess
				hResult = (HINSTANCE)WinExec( CStringA(key),showcmd);
			}
		}
	}
  
	return hResult;
}


STDMETHODIMP CMgaLauncher::ShowHelp(IMgaObject* obj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	COMTRY
	{
		CComPtr<IMgaFolder> imf;
		CComPtr<IMgaFCO> imfco;
		CString url;

		if (obj != NULL) {
			if (FAILED(obj->QueryInterface(&imf)) &&
				FAILED(obj->QueryInterface(&imfco)))
			{
				COMTHROW(E_INVALIDARG);
			}

			CComBSTR bstrVal;
			CComBSTR bstr = L"help";
			COMTHROW((imf != NULL) ? 
				imf->get_RegistryValue(bstr,&bstrVal)
				:
				imfco->get_RegistryValue(bstr,&bstrVal)
				);

			CopyTo(bstrVal,url);

			CString name;
			COMTHROW(obj->get_Name(PutOut(name)));
		}

		if (!url.IsEmpty())
		{
			GotoURL(url,SW_SHOWMAXIMIZED);
		}
		else
		{
			if (obj == NULL)
			{
				url = GME_UMAN_CONTENTS;
			} 
			else
			{
				objtype_enum obj_t;
				COMTHROW( obj->get_ObjType(&obj_t) );

				switch (obj_t) {

					case OBJTYPE_MODEL : {
						url = GME_UMAN_MODEL;
						break;
					}
					case OBJTYPE_ATOM : {
						url = GME_UMAN_ATOM;
						break;
					}
					case OBJTYPE_REFERENCE : {
						url = GME_UMAN_REFERENCE;
						break;
					}
					case OBJTYPE_SET : {
						url = GME_UMAN_SET;
						break;
					}
					case OBJTYPE_CONNECTION : {
						url = GME_UMAN_CONNECTION;
						break;
					}
					case OBJTYPE_FOLDER : {
						url = GME_UMAN_FOLDER;
						break;
					}
				}
			}

			if (!url.IsEmpty())
			{
				CString gmeRoot(_T("../"));
				// Use an absolute path based on the GME_ROOT environment variable, instead of a relative path if we can
				TCHAR* gme_root_env = NULL;
				gme_root_env = _tgetenv(_T("GME_ROOT"));
				if (gme_root_env) {
					long len = _tcslen(gme_root_env);
					bool hasSlashAtTheEnd = (gme_root_env[len - 1] == '\\' || gme_root_env[len - 1] == '/');
					gmeRoot = gme_root_env;
					if (!hasSlashAtTheEnd)
						gmeRoot = gmeRoot + "/";
				}
				gmeRoot.Replace(_T("\\"), _T("/"));
				CString fullUrl = CString(_T("ms-its:")) + gmeRoot + GME_UMAN_HOME + url;
				CWnd* mainWnd = AfxGetMainWnd();
				HWND hwndCaller = NULL;
				if (mainWnd != NULL)
					hwndCaller = mainWnd->m_hWnd;
				HWND helpWnd = NULL;
				helpWnd = ::HtmlHelp(hwndCaller, fullUrl, HH_DISPLAY_TOPIC, 0);
				if (helpWnd == NULL && url != GME_UMAN_CONTENTS) {
					fullUrl = CString(_T("ms-its:")) + gmeRoot + GME_UMAN_HOME + GME_UMAN_CONTENTS;
					helpWnd = ::HtmlHelp(hwndCaller, fullUrl, HH_DISPLAY_TOPIC, 0);
				}
				if (helpWnd == NULL)
					AfxMessageBox(_T("Couldn't find help file or help topic: ") + fullUrl, MB_OK | MB_ICONSTOP);
			}
			else
			{
				AfxMessageBox(_T("No default help is available for selection!"), MB_OK | MB_ICONSTOP);
			}
		}
	}
	COMCATCH(;)
}

static int __stdcall nopExceptionFilter(unsigned int code, struct _EXCEPTION_POINTERS* ep) {
	// FIXME: if (ep->ExceptionRecord->ExceptionFlags & EXCEPTION_NONCONTINUABLE)
	return EXCEPTION_EXECUTE_HANDLER;
}

// returns 0 if an exception was caught
bool __stdcall InvokeExWithCrashRpt(IMgaComponentEx* compex, IMgaProject* project, IMgaFCO* focusobj, IMgaFCOs* selectedobjs, long param, HRESULT& hr) {
	__try {
		__try {
			hr = compex->InvokeEx(project, focusobj, selectedobjs, param);
		} __except(crExceptionFilter(GetExceptionCode(), GetExceptionInformation())) {
			return 0;
		}
		// If run outside of GME, CrashRpt will not be set up, and crExceptionFilter will return EXCEPTION_CONTINUE_SEARCH
	} __except(nopExceptionFilter(GetExceptionCode(), GetExceptionInformation())) {
		return 0;
	}
	return 1;
}

STDMETHODIMP CMgaLauncher::RunComponent(BSTR progid, IMgaProject *project, IMgaFCO *focusobj, IMgaFCOs *selectedobjs, long param)
{
	if( project == NULL )
		COMRETURN(E_INVALIDARG);

	COMTRY
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		CComObjPtr<IMgaRegistrar> registrar;
		COMTHROW( registrar.CoCreateInstance(OLESTR("MGA.MgaRegistrar")) );
	
		CComBSTR prgid = progid;
		if(!prgid) {
			CComObjPtr<IMgaMetaProject> paradigm;
			COMTHROW( project->get_RootMeta(PutOut(paradigm)) );
			ASSERT( paradigm != NULL );
	
			CComBstrObj parname;
			COMTHROW( paradigm->get_Name(PutOut(parname)) );


			CComVariant v;
			COMTHROW( registrar->get_AssociatedComponents(parname, 
			COMPONENTTYPE_INTERPRETER, REGACCESS_BOTH, PutOut(v)) );

			CStringArray comps;
			CopyTo(v, comps);

			if( comps.GetSize() == 0 )
			{
				if( AfxMessageBox(_T("There are no registered interpreters for this paradigm. ")
					_T("Do you want to install your interpreter now?"), MB_YESNO) != IDYES )
					COMRETURN(S_FALSE);
			}
		
			if( comps.GetSize() == 1 )
				prgid = comps[0];
			else
			{
				CCompDlg dlg;
				dlg.onOKoper = _T("Interpret...");

				dlg.paradigm = parname;
				dlg.type = COMPONENTTYPE_INTERPRETER;

				if( dlg.DoModal() != IDOK )
					COMRETURN(S_OK);

				prgid = dlg.progid;
			}

			if( !prgid)	COMRETURN(S_FALSE);
		}


		componenttype_enum type;
		COMTHROW(registrar->QueryComponent(prgid, &type, NULL, REGACCESS_PRIORITY)); 
		CComPtr<IMgaComponent> component;
		// Before DispatchProxy: CComObjPtr<IMgaComponent> component;
		CString compname = prgid;
		if(type & COMPONENTTYPE_SCRIPT) {
			CComBSTR engine, scriptfile;
			COMTHROW(registrar->get_ComponentExtraInfo(REGACCESS_PRIORITY, prgid, CComBSTR(L"ExecEngine"), &engine));
			COMTHROW(registrar->get_ComponentExtraInfo(REGACCESS_PRIORITY, prgid, CComBSTR(L"ScriptFile"), &scriptfile));
			if(!engine || !scriptfile) {
				AfxMessageBox(_T("Incomplete registration for script component ")+ compname);
			}
			compname += _T(" (") + CString(engine) + _T(")");
			COMTHROW( component.CoCreateInstance(engine) );
			CComQIPtr<IMgaComponentEx> compex = component;
			if(!compex) {
				AfxMessageBox(_T("Exec.engine is only supported with extended component interface"));
				COMRETURN(E_MGA_NOT_SUPPORTED);
			}
			if(scriptfile) {
				COMTHROW(compex->put_ComponentParameter(CComBSTR(L"script"), CComVariant(scriptfile)));
			}
		}
		else COMTHROW(CreateMgaComponent(component, prgid));  // Before DispatchProxy: COMTHROW(component.CoCreateInstance(prgid));


		if(component == NULL) {
			AfxMessageBox(CString(_T("Could not start component ")) + compname);
		}
		else {
			CComQIPtr<IGMEVersionInfo> vi = component;
			if(!vi) {
					if(AfxMessageBox(	_T("This component does not provide interface version information\n")
										_T("It is probably incompatible with GME\n")
										_T("Do you want to proceed anyway?") , MB_YESNO) !=IDYES) return S_OK;
			}
			else {
				GMEInterfaceVersion vv;
				COMTHROW(vi->get_version(&vv));
				if(vv != INTERFACE_VERSION) {
					CString aa;
					aa.Format(_T("The interface version number of this component (%d.%d) differs from the GME version (%d.%d)\n")
								_T("This will probably result in serious malfunctions\n")
								_T("Do you want to proceed anyway?"), vv/0x10000,vv%0x10000, INTERFACE_VERSION/0x10000, INTERFACE_VERSION%0x10000); 
					if(AfxMessageBox(aa, MB_YESNO) !=IDYES) return S_OK;
				}
			}
			if(parameter.vt != VT_BOOL || parameter.boolVal != VARIANT_TRUE) { 
				CComQIPtr<IMgaComponentEx> compex = component;
				if (compex) {
					CComQIPtr<ISupportErrorInfo> supportErrorInfo = component;
					HRESULT hr = component->Initialize(project);
					// Need to catch SEH exceptions (especially for Win7 x64: see GME-318)
					if (SUCCEEDED(hr) && !InvokeExWithCrashRpt(compex, project, focusobj, selectedobjs, param, hr)) {
						project->AbortTransaction();
						AfxMessageBox(_T("An error has occurred in component ") + compname + _T(".\n")
							_T("GME may not be in a stable state.\n")
							_T("Please save your work and restart GME."));
					} else {
						if (!SUCCEEDED(hr)) {
							_bstr_t desc;
							if (supportErrorInfo && GetErrorInfo(desc.GetAddress())) {
								CString msg = static_cast<const TCHAR*>(desc);
								msg = "Interpreter returned error: " + msg;
								AfxMessageBox(msg, MB_OK | MB_ICONSTOP);
								SysFreeString(desc);
							} else {
								DisplayError(_T("Interpreter returned error"), hr);
							}
							project->AbortTransaction();
						}
					}
				} else {
					try	{
						COMTHROW(component->Initialize(project));
						CComPtr<IMgaTerritory> terr;
						COMTHROW(project->CreateTerritory(NULL, &terr));
						COMTHROW(project->BeginTransaction(terr));
						try	{
							COMTHROW( component->Invoke(project, selectedobjs, param) );
							COMTHROW(project->CommitTransaction());
						}
						catch(...)
						{
							project->AbortTransaction();
							throw;
						}
					}
					catch(hresult_exception &e)	{
						project->AbortTransaction();
						DisplayError(_T("Interpreter returned error"), e.hr);
					}
					catch(...)
					{
						project->AbortTransaction();
						AfxMessageBox(_T("An error has occurred in component ") + compname + _T(".\n")
							_T("GME may not be in a stable state.\n")
							_T("Please save your work and restart GME."));
					} 
				}
			}
			else {		// running unprotected
				try	{
					COMTHROW(component->Initialize(project));
					CComQIPtr<IMgaComponentEx> compex = component;
					if(compex) {
						COMTHROW(compex->InvokeEx(project, focusobj, CComQIPtr<IMgaFCOs>(selectedobjs), param));
					}
					else {
						CComPtr<IMgaTerritory> terr;
						COMTHROW(project->CreateTerritory(NULL, &terr));
						COMTHROW(project->BeginTransaction(terr));
						try	{		
							COMTHROW( component->Invoke(project, selectedobjs, param) );
							COMTHROW(project->CommitTransaction());
						}
						catch(...)
						{
							project->AbortTransaction();
							throw;
						}
					}
				}
				catch(hresult_exception &e)	{
					DisplayError(_T("Interpreter returned error"), e.hr);
				}
			}				
		}
//		component.Release();
//		CoFreeUnusedLibraries();
//	} COMCATCH(CoFreeUnusedLibraries(););
	} COMCATCH(;);
}

// ------ Helper functions

CString CMgaLauncher::PruneConnectionString(const CString &conn)
{
	CString ret;

	int p = 0;
	while( p < conn.GetLength() )
	{
		int q = conn.Find(';', p);
		if( q < 0 )
			q = conn.GetLength();

		CString part((const TCHAR*)conn + p, q-p);

		int r = part.Find('=');
		if( r < 0 )
			r = part.GetLength();

		CString key((const TCHAR*)part, r);

		if( key == _T("UID") ||
			key == _T("PWD") ||
			key == _T("USER") ||
			key == _T("PASSWORD") )
		{
			if( !ret.IsEmpty() )
				ret += _T(";");

			ret += part;
		}

		p = q+1;
	}

	return ret;
}


STDMETHODIMP CMgaLauncher::RegistryBrowser(IMgaObject *obj)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	COMTRY
	{
		
		CRegistryBrowserDlg dlg(obj);
		if (dlg.DoModal() == IDOK) {
			dlg.UpdateRegistry();
		}
	}
	COMCATCH(;)
}

STDMETHODIMP CMgaLauncher::AnnotationBrowser(IMgaObject *obj, IMgaRegNode *focus)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	COMTRY
	{
		CComPtr<IMgaModel> model;
		if ( SUCCEEDED( obj->QueryInterface(&model) )) {
			CComPtr<IMgaRegNode> currAnn(focus);
			CAnnotationBrowserDlg dlg(model, currAnn);

			dlg.m_model = model;
			if (dlg.DoModal() == IDOK) {
				dlg.UpdateAnnotations();
			} else {
				return E_MGA_MUST_ABORT;	// JIRA GME-236: special ret code, indicating that the dialog was cancelled
			}
		}
		else {
			AfxMessageBox(_T("Unsupported object type for Annotation Browser."));
		}
	}
	COMCATCH(;)
}
