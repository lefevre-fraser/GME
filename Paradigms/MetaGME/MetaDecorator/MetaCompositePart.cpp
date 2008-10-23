//################################################################################################
//
// New Meta decorator composite part class
//	MetaCompositePart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "MetaCompositePart.h"

#include "Resource.h"
#include "MaskedBitmapPart.h"
#include "TypeableLabelPart.h"
#include "EllipseVectorPart.h"
#include "InheritanceVectorPart.h"
#include "DiamondVectorPart.h"
#include "MetaClassPart.h"
#include "DecoratorExceptions.h"
#include "MetaDecoratorUtil.h"


namespace MetaDecor {

//################################################################################################
//
// CLASS : MetaCompositePart
//
//################################################################################################

MetaCompositePart::MetaCompositePart(DecoratorSDK::PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	ObjectAndTextPart(pPart, eventSink)
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
	try {
		if (!DecoratorSDK::getFacilities().getMetaFCO(pPart, m_spMetaFCO))
			throw DecoratorException((DecoratorExceptionCode)E_DECORATOR_INIT_WITH_NULL);
		if (pProject && pPart) {
			m_spFCO = pFCO;		// pFCO == NULL, if we are in the PartBrowser

			CComBSTR bstr;
			COMTHROW(m_spMetaFCO->get_Name(&bstr));
			CString stereotypeName(bstr);

			// Get ShapeCode
			ShapeCode shape = MetaDecor::GetDecorUtils().GetShapeCode(stereotypeName);
			if (shape == NULLSHAPE) {
				throw DecoratorException((DecoratorExceptionCode)E_METADECORATOR_KINDNOTSUPPORTED);
			} else if (shape == CONNECTOR) {
				AddObjectPart(new DecoratorSDK::EllipseVectorPart(this, m_eventSink,
																  static_cast<long> (2 * META_CONNECTOR_RAIDUS),
																  static_cast<long> (2 * META_CONNECTOR_RAIDUS)));
				if (!pFCO)
					AddTextPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
			} else if (shape == CONSTRAINT) {
				AddObjectPart(new DecoratorSDK::MaskedBitmapPart(this, m_eventSink, IDB_BITMAP_CONSTRAINT, DecoratorSDK::COLOR_TRANSPARENT, DecoratorSDK::COLOR_GRAYED_OUT));
				AddTextPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
			} else if (shape == CONSTRAINTFUNC) {
				AddObjectPart(new DecoratorSDK::MaskedBitmapPart(this, m_eventSink, IDB_BITMAP_CONSTRAINTFUNC, DecoratorSDK::COLOR_TRANSPARENT, DecoratorSDK::COLOR_GRAYED_OUT));
				AddTextPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
			} else if (shape == INHERITANCE) {
				AddObjectPart(new InheritanceVectorPart(this, m_eventSink,
														static_cast<long> (META_INHERITANCE_WIDTH),
														static_cast<long> (META_INHERITANCE_HEIGHT),
														NormalInheritance));
				if (!pFCO)
					AddTextPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
			} else if (shape == IMPINHERITANCE) {
				AddObjectPart(new InheritanceVectorPart(this, m_eventSink,
														static_cast<long> (META_INHERITANCE_WIDTH),
														static_cast<long> (META_INHERITANCE_HEIGHT),
														ImplementationInheritance));
				if (!pFCO)
					AddTextPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
			} else if (shape == INTINHERITANCE) {
				AddObjectPart(new InheritanceVectorPart(this, m_eventSink,
														static_cast<long> (META_INHERITANCE_WIDTH),
														static_cast<long> (META_INHERITANCE_HEIGHT),
														InterfaceInheritance));
				if (!pFCO)
					AddTextPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
			} else if (shape == EQUIVALENCE) {
				AddObjectPart(new DecoratorSDK::DiamondVectorPart(this, m_eventSink,
																  static_cast<long> (META_EQUIVALENCE_WIDTH),
																  static_cast<long> (META_EQUIVALENCE_HEIGHT)));
				if (!pFCO)
					AddTextPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
			} else {	// This must be a class
				AddObjectPart(new MetaClassPart(this, m_eventSink, shape, stereotypeName));
				// The MetaClassPart handles the label also
			}
		}
	}
	catch (hresult_exception& e) {
		throw DecoratorException((DecoratorExceptionCode)e.hr);
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
