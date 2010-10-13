///////////////////////////////////////////////////////////////////////////
// RawComponent.cpp, the main RAW COM component implementation file
// This is the file (along with its header RawComponent.h)
// that the component implementor is expected to modify in the first place
//
///////////////////////////////////////////////////////////////////////////
#include "stdafx.h"

//#include "ComHelp.h"
//#include "GMECOM.h"
#include "ComponentLib.h"
#include "ComponentConfig.h"
#include "RawComponent.h"
#include "CommonSmart.h"
#include "GMEGraph.h"
#include "DlgAutoLayout.h"

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
	COMTRY 
    {
	  if(interactive) 
      {
		CComBSTR projname;
		CComObjPtr<IMgaTerritory> terr;
		COMTHROW(project->CreateTerritory(NULL, PutOut(terr)));
		COMTHROW(project->BeginTransaction(terr));
		try 
        {
            if(currentobj==NULL)
                throw 0;

            objtype_enum objType;
            COMTHROW(currentobj->get_ObjType(&objType));
            if( objType != OBJTYPE_MODEL )
            {
                AfxMessageBox("AutoLayout can only run on models. Open a model and try again!");
                throw 0;
            }

            CDlgAutoLayout dlg;
            dlg.initialzie( project, (IMgaModel*)currentobj );
            if( dlg.DoModal() != IDOK )
                throw 0;

            COMTHROW( project->CommitTransaction() );
		}	
        catch(...)         
        { 
            project->AbortTransaction(); 
        }		
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
