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
	// The second part is the label
	std::vector<PartBase*>::const_iterator ii = m_compositeParts.begin();
	 ++ii;
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
			} else {	// This should be a class
/*				if (pFCO) {
					objtype_enum objtype;
					COMTHROW(pFCO->get_ObjType(&objtype));
					if (objtype == OBJTYPE_REFERENCE) {
						m_copyBitmap = DecoratorSDK::getFacilities().getMaskedBitmap(IDB_BITMAP_COPY, UML_TRANSPARENT_COLOR, GME_GRAYED_OUT_COLOR);
						m_isCopy = true;
						CComPtr<IMgaFCO> mgaFco = pFCO;
						while(objtype == OBJTYPE_REFERENCE) {
							CComPtr<IMgaReference> ref;
							COMTHROW(mgaFco.QueryInterface(&ref));
							mgaFco = NULL;
							COMTHROW(ref->get_Referred(&mgaFco));
							if (mgaFco) {
								COMTHROW(mgaFco->get_ObjType(&objtype));
							} else {
								objtype = OBJTYPE_NULL;
							}
						}
						if (objtype == OBJTYPE_NULL) {
							m_stereotype.Empty();
							m_attrs.RemoveAll();
						} else {
							if (!DecoratorSDK::getFacilities().getAttribute(mgaFco ? mgaFco : m_mgaFco, UML_STEREOTYPE_ATTR, m_stereotype)) {
								m_stereotype.Empty();
							}
							bool isAbstract;
							if (DecoratorSDK::getFacilities().getAttribute(mgaFco ? mgaFco : m_mgaFco, UML_ABSTRACT_ATTR, isAbstract) && isAbstract) {
								m_isAbstract = true;
							}
							CollectAttributes(mgaFco);
						}
					} else {
						m_isCopy = false;
						if (!DecoratorSDK::getFacilities().getAttribute(m_mgaFco, UML_STEREOTYPE_ATTR, m_stereotype)) {
							m_stereotype.Empty();
						}
						bool isAbstract;
						if (DecoratorSDK::getFacilities().getAttribute(m_mgaFco, UML_ABSTRACT_ATTR, isAbstract) && isAbstract) {
							m_isAbstract = true;
						}
						CollectAttributes();
					}
					CComBSTR bstr;
					COMTHROW(m_mgaFco->get_Name(&bstr));
					m_name = bstr;
				} else {
					objtype_enum objtype;
					COMTHROW(m_metaFco->get_ObjType(&objtype));
					if (objtype == OBJTYPE_REFERENCE) {
						m_copyBitmap = DecoratorSDK::getFacilities().getMaskedBitmap(IDB_BITMAP_COPY, UML_TRANSPARENT_COLOR, GME_GRAYED_OUT_COLOR);
						m_isCopy = true;
					} else {
						m_isCopy = false;
					}
					m_stereotype.Empty();
					CComBSTR bstr;
					COMTHROW(m_metaFco->get_DisplayedName(&bstr));
					if (bstr.Length() == 0 ) {
						bstr.Empty();
						COMTHROW(m_metaFco->get_Name(&bstr));
					}
					m_name = bstr;
				}

				if (!DecoratorSDK::getFacilities().getPreference(m_mgaFco, m_metaFco, COLOR_PREF, m_color)) {
					m_color = GME_BLACK_COLOR;
				}
				if (!DecoratorSDK::getFacilities().getPreference(m_mgaFco, m_metaFco, NAME_COLOR_PREF, m_nameColor)) {
					m_nameColor = GME_BLACK_COLOR;
				}
				CalcRelPositions();*/

				AddImagePart(new DecoratorSDK::AtomBitmapPart(this, m_eventSink));
				AddLabelPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
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
