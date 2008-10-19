//################################################################################################
//
// New UML decorator composite part class
//	UMLCompositePart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "UMLCompositePart.h"

#include "Resource.h"
#include "DecoratorStd.h"
#include "InheritanceVectorPart.h"
#include "ConnectorVectorPart.h"
#include "ConstraintBitmapPart.h"
#include "UMLClassPart.h"

#include "ModelComplexPart.h"
#include "TypeableLabelPart.h"
#include "ReferenceBitmapPart.h"
#include "PortPart.h"
#include "AtomBitmapPart.h"
#include "SetBitmapPart.h"
#include "DecoratorExceptions.h"


namespace UMLDecor {

//################################################################################################
//
// CLASS : UMLCompositePart
//
//################################################################################################

UMLCompositePart::UMLCompositePart(DecoratorSDK::PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	ImageAndLabelPart(pPart, eventSink)
{
}

UMLCompositePart::~UMLCompositePart()
{
}

CRect UMLCompositePart::GetPortLocation(CComPtr<IMgaFCO>& fco) const
{
	throw PortNotFoundException();
}

bool UMLCompositePart::GetPorts(CComPtr<IMgaFCOs>& portFCOs) const
{
	CComPtr<IMgaFCOs> spFCOs;
	COMTHROW(spFCOs.CoCreateInstance(OLESTR("Mga.MgaFCOs")));
	portFCOs = spFCOs.Detach();
	return false;
}

CRect UMLCompositePart::GetLabelLocation(void) const
{
	HRESULT retVal = S_OK;
	std::vector<PartBase*>::const_iterator ii = m_compositeParts.begin();
	if (m_compositeParts.size() > 1)
		++ii;	// we expect that the second part is the label if there's more than one part
	if (ii != m_compositeParts.end()) {
		try {
			return (*ii)->GetLabelLocation();
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}

	throw DecoratorException((DecoratorExceptionCode)retVal);
}

// New functions
void UMLCompositePart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									HWND parentWnd, DecoratorSDK::PreferenceMap& preferences)
{
	DecoratorSDK::getFacilities().getMetaFCO(pPart, m_spMetaFCO);
	HRESULT retVal = S_OK;
	try {
		if (pProject && pPart) {
			ASSERT(m_spMetaFCO);
			CComBSTR bstr;
			COMTHROW(m_spMetaFCO->get_Name(&bstr));
			CString name(bstr);
			if (name == UML_INHERITANCE_NAME) {
				AddImagePart(new InheritanceVectorPart(this, m_eventSink));
				if (!pFCO)
					AddLabelPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
			} else if (name == UML_CONNECTOR_NAME) {
				AddImagePart(new ConnectorVectorPart(this, m_eventSink));
				if (!pFCO)
					AddLabelPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
			} else if (name == UML_CONSTRAINT_NAME) {
				AddImagePart(new ConstraintBitmapPart(this, m_eventSink, IDB_BITMAP_CONSTRAINT, DecoratorSDK::COLOR_BKGND, DecoratorSDK::COLOR_GRAYED_OUT));
				AddLabelPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
			} else if (name == UML_CONSTRAINT_DEFINITION_NAME) {
				AddImagePart(new ConstraintBitmapPart(this, m_eventSink, IDB_BITMAP_CDEFINITION, DecoratorSDK::COLOR_BKGND, DecoratorSDK::COLOR_GRAYED_OUT));
				AddLabelPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
			} else {	// This must be a class
				AddImagePart(new UMLClassPart(this, m_eventSink));
				// The UMLClassPart handles the label also
			}
		}
	}
	catch (hresult_exception &) {
		retVal = E_UNEXPECTED;
	}

	CompositePart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

void UMLCompositePart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									HWND parentWnd)
{
	DecoratorSDK::getFacilities().loadPathes(pProject, true);

	DecoratorSDK::PreferenceMap preferencesMap;
	InitializeEx(pProject, pPart, pFCO, parentWnd, preferencesMap);
}

}; // namespace UMLDecor
