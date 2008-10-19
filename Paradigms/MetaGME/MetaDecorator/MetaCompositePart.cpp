//################################################################################################
//
// New Meta decorator composite part class
//	MetaCompositePart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "MetaCompositePart.h"

#include "ModelComplexPart.h"
#include "TypeableLabelPart.h"
#include "ReferenceBitmapPart.h"
#include "PortPart.h"
#include "AtomBitmapPart.h"
#include "SetBitmapPart.h"
#include "DecoratorExceptions.h"


namespace MetaDecor {

//################################################################################################
//
// CLASS : MetaCompositePart
//
//################################################################################################

MetaCompositePart::MetaCompositePart(DecoratorSDK::PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	BitmapAndLabelPart(pPart, eventSink)
{
}

MetaCompositePart::~MetaCompositePart()
{
}

CRect MetaCompositePart::GetPortLocation(CComPtr<IMgaFCO>& fco) const
{
	throw PortNotFoundException();
}

bool MetaCompositePart::GetPorts(CComPtr<IMgaFCOs>& portFCOs) const
{
	CComPtr<IMgaFCOs> spFCOs;
	COMTHROW(spFCOs.CoCreateInstance(OLESTR("Mga.MgaFCOs")));
	portFCOs = spFCOs.Detach();
	return false;
}

CRect MetaCompositePart::GetLabelLocation(void) const
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
void MetaCompositePart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									 HWND parentWnd, DecoratorSDK::PreferenceMap& preferences)
{
	HRESULT retVal = S_OK;
	if (pProject && pPart) {
/*		m_spFCO = obj;		// obj == NULL, if we are in the PartBrowser
		
		if (!DecoratorSDK::getFacilities().getMetaFCO(metaPart, m_metaFco)) {
			return E_DECORATOR_INIT_WITH_NULL;
		} else {
			m_isInitialized = true;
		}	

		// Get ShapeCode
		try {
			CComBSTR bstr;
			COMTHROW(m_metaFco->get_Name(&bstr));
			m_stereotype = bstr;

			m_shape = MetaDecor::GetDecorUtils().GetShapeCode(m_stereotype);
			if (m_shape == NULLSHAPE) {
				m_isInitialized = false;
				return E_METADECORATOR_KINDNOTSUPPORTED;
			}
		}
		catch (hresult_exception &e) {
			m_isInitialized = false;
			return e.hr;
		}*/


		objtype_enum eType;
		if (pFCO) {
			COMTHROW(pFCO->get_ObjType(&eType));
		} else {
			CComPtr<IMgaMetaRole> spRole;
			COMTHROW(pPart->get_Role(&spRole));

			CComPtr<IMgaMetaFCO> spMetaFCO;
			COMTHROW(spRole->get_Kind(&spMetaFCO));

			COMTHROW(spMetaFCO->get_ObjType(&eType));
		}
		switch (eType) {
			case OBJTYPE_ATOM: {
					AddBitmapPart(new DecoratorSDK::AtomBitmapPart(this, m_eventSink));
					AddLabelPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
				}
				break;
			case OBJTYPE_SET: {
					AddBitmapPart(new DecoratorSDK::SetBitmapPart(this, m_eventSink));
					AddLabelPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
				}
				break;
			case OBJTYPE_MODEL: {
					AddBitmapPart(new DecoratorSDK::ModelComplexPart(this, m_eventSink));
					AddLabelPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
				}
				break;
			case OBJTYPE_REFERENCE: {
					AddBitmapPart(new DecoratorSDK::ReferenceBitmapPart(this, m_eventSink));
					AddLabelPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
				}
				break;
		}
	}

	CompositePart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

void MetaCompositePart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									HWND parentWnd)
{
	DecoratorSDK::getFacilities().loadPathes(pProject, true);

	DecoratorSDK::PreferenceMap preferencesMap;
	InitializeEx(pProject, pPart, pFCO, parentWnd, preferencesMap);
}

}; // namespace MetaDecor
