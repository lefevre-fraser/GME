//################################################################################################
//
// New Box decorator composite part class
//	BoxCompositePart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "BoxCompositePart.h"

#include "ModelComplexPart.h"
#include "TypeableLabelPart.h"
#include "ReferenceBitmapPart.h"
#include "PortPart.h"
#include "AtomBitmapPart.h"
#include "SetBitmapPart.h"
#include "../DecoratorExceptions.h"


namespace Decorator {

//################################################################################################
//
// CLASS : BoxCompositePart
//
//################################################################################################

BoxCompositePart::BoxCompositePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	BitmapAndLabelPart(pPart, eventSink)
{
}

BoxCompositePart::~BoxCompositePart()
{
}

CRect BoxCompositePart::GetPortLocation(CComPtr<IMgaFCO>& fco) const
{
	PortPart* pPortPart = NULL;
	ModelComplexPart* modelComplexPart = dynamic_cast<ModelComplexPart*> (GetBitmapPart());
	ReferenceBitmapPart* refrenceBitmapPart = NULL;
	if (modelComplexPart != NULL) {
		pPortPart = modelComplexPart->GetPort(fco);
	} else {
		refrenceBitmapPart = dynamic_cast<ReferenceBitmapPart*> (GetBitmapPart());
		if (refrenceBitmapPart != NULL) {
			ModelComplexPart* referencedModelPart = dynamic_cast<ModelComplexPart*> (refrenceBitmapPart->GetReferenced());
			if (referencedModelPart != NULL)
				pPortPart = referencedModelPart->GetPort(fco);
		}
	}
	if (pPortPart) {
		CRect location = pPortPart->GetLocation();

		// if a reference has an icon specified for itself 
		// then it is not surrounded by a black rectangle.
		// if it doesn't have an icon, then the icon of the
		// referred element is used, and it is surrounded
		// that's why we shift port locations only if
		// the surrounding rectangle is there (borderwidth > 0)
		if (GetBitmapPart()->GetBorderWidth(false) > 0 && refrenceBitmapPart)	// HACK
			location.OffsetRect(2, 2);

		return location;
	}

	throw PortNotFoundException();
}

bool BoxCompositePart::GetPorts(CComPtr<IMgaFCOs>& portFCOs) const
{
	CComPtr<IMgaFCOs> spFCOs;
	COMTHROW(spFCOs.CoCreateInstance(OLESTR("Mga.MgaFCOs")));

	std::vector<PortPart*>	vecPorts;
	PortPart* pPortPart = NULL;
	ModelComplexPart* modelComplexPart = dynamic_cast<ModelComplexPart*> (GetBitmapPart());
	ReferenceBitmapPart* refrenceBitmapPart = NULL;
	bool modelFound = false;
	if (modelComplexPart != NULL) {
		vecPorts = modelComplexPart->GetPorts();
		modelFound = true;
	} else {
		refrenceBitmapPart = dynamic_cast<ReferenceBitmapPart*> (GetBitmapPart());
		if (refrenceBitmapPart != NULL) {
			ModelComplexPart* referencedModelPart = dynamic_cast<ModelComplexPart*> (refrenceBitmapPart->GetReferenced());
			if (referencedModelPart != NULL) {
				vecPorts = referencedModelPart->GetPorts();
				modelFound = true;
			}
		}
	}

	for (unsigned int i = 0; i < vecPorts.size(); i++)
		COMTHROW(spFCOs->Append(vecPorts[i]->GetFCO()));

	portFCOs = spFCOs.Detach();
	return modelFound;
}

CRect BoxCompositePart::GetLabelLocation(void) const
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
void BoxCompositePart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									HWND parentWnd, PreferenceMap& preferences)
{
	HRESULT retVal = S_OK;
	if (pProject && pPart) {
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
					AddBitmapPart(new AtomBitmapPart(this, m_eventSink));
					AddLabelPart(new TypeableLabelPart(this, m_eventSink));
				}
				break;
			case OBJTYPE_SET: {
					AddBitmapPart(new SetBitmapPart(this, m_eventSink));
					AddLabelPart(new TypeableLabelPart(this, m_eventSink));
				}
				break;
			case OBJTYPE_MODEL: {
					AddBitmapPart(new ModelComplexPart(this, m_eventSink));
					AddLabelPart(new TypeableLabelPart(this, m_eventSink));
				}
				break;
			case OBJTYPE_REFERENCE: {
					AddBitmapPart(new ReferenceBitmapPart(this, m_eventSink));
					AddLabelPart(new TypeableLabelPart(this, m_eventSink));
				}
				break;
		}
	}

	CompositePart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

void BoxCompositePart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									HWND parentWnd)
{
	getFacilities().loadPathes(pProject, true);

	PreferenceMap preferencesMap;
	InitializeEx(pProject, pPart, pFCO, parentWnd, preferencesMap);
}

}; // namespace Decorator
