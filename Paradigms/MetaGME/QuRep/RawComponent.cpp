///////////////////////////////////////////////////////////////////////////
// RawComponent.cpp, the main RAW COM component implementation file
// This is the file (along with its header RawComponent.h)
// that the component implementor is expected to modify in the first place
//
///////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include "ComHelp.h"
#include "GMECOM.h"
#include <ComponentConfig.h>
#include "RawComponent.h"
#include "SearchRepl.h"
#include "KindSelDlg.h"

void CopyTo(const OLECHAR *p, int olelen, char *s, int charlen)
{
	ASSERT( olelen >= -1 && charlen >= 0 );
	ASSERT( charlen == 0 || p != NULL );

	if( charlen <= 0 )
		return;

	UINT acp = GetACP();

	int len = WideCharToMultiByte(acp, 0, p, olelen, 
		s, charlen, NULL, NULL);

	// zero if failed
	ASSERT( len > 0 );

	ASSERT( len == charlen );
}

void CopyTo(const CComBSTR p, CString& res)
{
	unsigned int len = p.Length();
	if( !len) return;

	char *buff = new char[ len + 1];
	//char buff[1024];

	CopyTo( p, len, buff, len);
	int l1 = strlen( buff);
	buff[ len] = '\0';
	int l2 = strlen( buff);
	++l1;++l2;
	res = buff;
	int l3 = strlen( buff);
	++l3;
	delete [] buff;
}

// this method is called after all the generic initialization is done
// this should be empty, unless application-specific initialization is needed
STDMETHODIMP RawComponent::Initialize(struct IMgaProject *) {
	return S_OK;
}

// this is the obsolete component interface
// this present implementation either tries to call InvokeEx, or returns an error;
STDMETHODIMP RawComponent::Invoke(IMgaProject* gme, IMgaFCOs *models, long param) {
#ifdef SUPPORT_OLD_INVOKE
	CComPtr<IMgaFCO> focus;
	CComVariant parval = param;
	return InvokeEx(gme, focus, selected, parvar);
#else
	if(interactive) {
		AfxMessageBox("This component does not support the obsolete invoke mechanism");
	}
	return E_MGA_NOT_SUPPORTED;
#endif
}


// This is the main component method for interpereters and plugins. 
// May als be used in case of invokeable addons
STDMETHODIMP RawComponent::InvokeEx( IMgaProject *project,  IMgaFCO *currentobj,  
									IMgaFCOs *selectedobjs,  long param) {
	COMTRY {
	  if(interactive) {
		CComBSTR projname;
		CComBSTR focusname = "<nothing>";
		CComPtr<IMgaTerritory> terr;
		COMTHROW(project->CreateTerritory(NULL, &terr));
		COMTHROW(project->BeginTransaction(terr));
		try {
			//COMTHROW(project->get_Name(&projname));
			//if(currentobj) COMTHROW(currentobj->get_Name(&focusname));
			long c = 0;
			if( selectedobjs) COMTHROW( selectedobjs->get_Count( &c));
			if( c > 0)
			{
				SearchRepl sr( project);
				KindSelDlg d;
				//d.setup();

				for( long i = 1; i <= c; ++i)
				{
					CComPtr<IMgaFCO> i_tem;
					CComPtr<IMgaFCO> item;
					CComPtr<IMgaFCO> jtem;
					COMTHROW( selectedobjs->get_Item( i, &i_tem));
					if( i_tem)
					{
						COMTHROW( terr->OpenFCO( i_tem, &item));

						long stat;
						COMTHROW( item->get_Status( &stat));
						// if two elements from the same equiv class were included in the initial selection
						// no need to execute the search and repl on them
						if( stat != OBJECT_EXISTS)
							continue; 

						CComQIPtr<IMgaReference> rf_item( item);
						if( rf_item)
						{
							// never invoke SRepl with a proxy, use the real class instead
							COMTHROW( rf_item->get_Referred( &jtem));
						}
						else jtem = item;

						if( sr.qualifies( jtem))
						{
							if( d.shouldApplyForAll())
							{
								sr.exec( jtem, (LPCTSTR) d.selection());
							}
							else
							{
								// the object name
								CComBSTR nm;
								COMTHROW( jtem->get_Name( &nm));
								CString nms;
								CopyTo( nm, nms);
								
								// the current kind
								CComPtr<IMgaMetaRole> mr;
								COMTHROW( jtem->get_MetaRole( &mr));
								CComBSTR mrn;
								COMTHROW( mr->get_Name( &mrn));
								CString mrns;
								CopyTo( mrn, mrns);
								
								d.init( nms, mrns);

								if( IDOK == d.DoModal() && d.selection() != mrns) // something has to be done
									sr.exec( jtem, (LPCTSTR) d.selection()); 
								else if( d.shouldFinish())
									break;
							}
						}
					}
				}
			}
			COMTHROW(project->CommitTransaction());
		}	catch(...) { project->AbortTransaction(); throw; }
		
	  } 
	} COMCATCH(;);
}

// GME currently does not use this function
// you only need to implement it if other invokation mechanisms are used
STDMETHODIMP RawComponent::ObjectsInvokeEx( IMgaProject *project,  IMgaObject *currentobj,  IMgaObjects *selectedobjs,  long param) {
	if(interactive) {
		AfxMessageBox("Tho ObjectsInvoke method is not implemented");
	}
	return E_MGA_NOT_SUPPORTED;
}


// implement application specific parameter-mechanism in these functions:
STDMETHODIMP RawComponent::get_ComponentParameter(BSTR name, VARIANT *pVal) {
	return S_OK;
}

STDMETHODIMP RawComponent::put_ComponentParameter(BSTR name, VARIANT newVal) {
	return S_OK;
}


#ifdef GME_ADDON

// these two functions are the main 
STDMETHODIMP RawComponent::GlobalEvent(globalevent_enum event) { 
	if(event == GLOBALEVENT_UNDO) {
		AfxMessageBox("UNDO!!");
	}
	return S_OK; 
}

STDMETHODIMP RawComponent::ObjectEvent(IMgaObject * obj, unsigned long eventmask, VARIANT v) {
	if(eventmask & OBJEVENT_CREATED) {
		CComBSTR objID;
		COMTHROW(obj->get_ID(&objID));
		AfxMessageBox( "Object created! ObjID: " + CString(objID)); 
	}		
	return S_OK;
}

#endif
