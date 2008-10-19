//################################################################################################
//
// New UML decorator composite part class
//	UMLClassPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "UMLClassPart.h"

#include "Resource.h"
#include "DecoratorStd.h"
#include "TokenEx.h"
#include "ClassLabelPart.h"
#include "UMLStereoLabelPart.h"
#include "UMLAttributePart.h"
#include "BitmapPart.h"


namespace UMLDecor {

//################################################################################################
//
// CLASS : UMLClassPart
//
//################################################################################################

UMLClassPart::UMLClassPart(DecoratorSDK::PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	ClassComplexPart(pPart, eventSink)
{
}

UMLClassPart::~UMLClassPart()
{
}

// New functions
void UMLClassPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
								HWND parentWnd, DecoratorSDK::PreferenceMap& preferences)
{
	try {
		DecoratorSDK::getFacilities().getMetaFCO(pPart, m_spMetaFCO);
		preferences[DecoratorSDK::PREF_LABELFONT]		= DecoratorSDK::PreferenceVariant((long)DecoratorSDK::FONT_PORTNAME);
		preferences[DecoratorSDK::PREF_LABELLENGTH]		= DecoratorSDK::PreferenceVariant((long)-1);
		preferences[DecoratorSDK::PREF_LABELENABLED]	= DecoratorSDK::PreferenceVariant(true);
		preferences[DecoratorSDK::PREF_LABELWRAP]		= DecoratorSDK::PreferenceVariant((long)0);
		preferences[DecoratorSDK::PREF_TEXTOVERRIDE]	= DecoratorSDK::PreferenceVariant(true);

		if (m_spFCO) {
			bool isAbstract = false;
			objtype_enum objtype = OBJTYPE_NULL;
			COMTHROW(m_spFCO->get_ObjType(&objtype));
			if (objtype == OBJTYPE_REFERENCE) {
				CreateCopyBitmapPart(preferences);
				CComPtr<IMgaFCO> mgaFco = m_spFCO;
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
				if (objtype != OBJTYPE_NULL) {
					CString strStereotype;
					if (DecoratorSDK::getFacilities().getAttribute(mgaFco ? mgaFco : m_spFCO, UML_STEREOTYPE_ATTR, strStereotype)) {
						if (!strStereotype.IsEmpty()) {
							m_StereotypePart = new UMLStereoLabelPart(this, m_eventSink, mgaFco ? mgaFco : m_spFCO);
							m_StereotypePart->SetText(strStereotype);
						}
					}

					DecoratorSDK::getFacilities().getAttribute(mgaFco ? mgaFco : m_spFCO, UML_ABSTRACT_ATTR, isAbstract);
					CollectAttributes(mgaFco);
				}
			} else {
				CString strStereotype;
				if (DecoratorSDK::getFacilities().getAttribute(m_spFCO, UML_STEREOTYPE_ATTR, strStereotype)) {
					if (!strStereotype.IsEmpty()) {
						m_StereotypePart = new UMLStereoLabelPart(this, m_eventSink, m_spFCO);
						m_StereotypePart->SetText(strStereotype);
					}
				}

				DecoratorSDK::getFacilities().getAttribute(m_spFCO, UML_ABSTRACT_ATTR, isAbstract);
				CollectAttributes();
			}
			CComBSTR bstr;
			COMTHROW(m_spFCO->get_Name(&bstr));
			m_LabelPart = new DecoratorSDK::ClassLabelPart(this, m_eventSink, isAbstract);
			m_LabelPart->SetText(CString(bstr));
		} else {
			objtype_enum objtype;
			COMTHROW(m_spMetaFCO->get_ObjType(&objtype));
			if (objtype == OBJTYPE_REFERENCE) {
				CreateCopyBitmapPart(preferences);
			}
			CComBSTR bstr;
			COMTHROW(m_spMetaFCO->get_DisplayedName(&bstr));
			if (bstr.Length() == 0) {
				bstr.Empty();
				COMTHROW(m_spMetaFCO->get_Name(&bstr));
			}
			m_LabelPart = new DecoratorSDK::ClassLabelPart(this, m_eventSink, false);
			m_LabelPart->SetText(CString(bstr));
		}

		COLORREF color = GME_BLACK_COLOR;
		DecoratorSDK::getFacilities().getPreference(m_spFCO, m_spMetaFCO, DecoratorSDK::PREF_COLOR, color);
		preferences[DecoratorSDK::PREF_COLOR] = DecoratorSDK::PreferenceVariant(color);

		COLORREF nameColor = GME_BLACK_COLOR;
		DecoratorSDK::getFacilities().getPreference(m_spFCO, m_spMetaFCO, DecoratorSDK::PREF_LABELCOLOR, nameColor);
		preferences[DecoratorSDK::PREF_LABELCOLOR] = DecoratorSDK::PreferenceVariant(nameColor);
	}
	catch(hresult_exception &e)
	{
		ASSERT( FAILED(e.hr) );
		SetErrorInfo(e.hr);
	}

	ClassComplexPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);

	CalcRelPositions();
}

void UMLClassPart::CollectAttributes(CComPtr<IMgaFCO> mgaFco)
{
	if (!mgaFco) {
		mgaFco = m_spFCO;
	}
	CString attrStr;
	if (DecoratorSDK::getFacilities().getAttribute(mgaFco, UML_ATTRIBUTES_ATTR, attrStr)) {
		CStringArray attrPairs;
		CTokenEx tok;
		tok.Split(attrStr, "\n", attrPairs);
		for (int i = 0; i < attrPairs.GetSize(); i++) {
			CStringArray attrPair;
			tok.Split(attrPairs[i], ":", attrPair);
			if (attrPair.GetSize() == 1) {
				attrPair.Add("unknown");
			}
			if (attrPair.GetSize() == 2) {
				attrPair[0].TrimLeft();
				attrPair[0].TrimRight();
				attrPair[1].TrimLeft();
				attrPair[1].TrimRight();
				m_AttributeParts.push_back(new UMLAttributePart(this, m_eventSink, attrPair[0], attrPair[1], mgaFco));
			}
		}
	}
}

void UMLClassPart::ModifyAttributes(CComPtr<IMgaFCO> mgaFco)
{
	CString attrPairs;
	for (std::vector<DecoratorSDK::AttributePart*>::iterator ii = m_AttributeParts.begin(); ii != m_AttributeParts.end(); ++ii) {
		if (!attrPairs.IsEmpty())
			attrPairs += '\n';
		CString attrName = (*ii)->GetName();
		CString attrType = (*ii)->GetType();
		CString attrPair = attrName;
		if (attrType != "unknown") {
			attrPair += ':' + attrType;
		}
		attrPairs += attrPair;
	}
	DecoratorSDK::getFacilities().setAttribute(mgaFco, UML_ATTRIBUTES_ATTR, attrPairs);
}

void UMLClassPart::CreateCopyBitmapPart(DecoratorSDK::PreferenceMap& preferences)
{
	preferences[DecoratorSDK::PREF_ISMASKEDBITMAP]		= DecoratorSDK::PreferenceVariant(true);

	preferences[DecoratorSDK::PREF_ICONDEFAULT]			= DecoratorSDK::PreferenceVariant(DecoratorSDK::createResString(IDB_ATOM));
	preferences[DecoratorSDK::PREF_TILESDEFAULT]		= DecoratorSDK::PreferenceVariant(DecoratorSDK::getFacilities().getTileVector(DecoratorSDK::TILE_ATOMDEFAULT));
	preferences[DecoratorSDK::PREF_TILESUNDEF]			= DecoratorSDK::PreferenceVariant(DecoratorSDK::getFacilities().getTileVector(DecoratorSDK::TILE_ATOMDEFAULT));
	preferences[DecoratorSDK::PREF_TILES]				= DecoratorSDK::PreferenceVariant(DecoratorSDK::getFacilities().getTileVector(DecoratorSDK::TILE_ATOMDEFAULT));

	preferences[DecoratorSDK::PREF_ICON]				= DecoratorSDK::PreferenceVariant((long)IDB_REFERENCE_SIGN);
	preferences[DecoratorSDK::PREF_TRANSPARENTCOLOR]	= DecoratorSDK::PreferenceVariant(DecoratorSDK::COLOR_TRANSPARENT);
	preferences[DecoratorSDK::PREF_GRAYEDOUTCOLOR]		= DecoratorSDK::PreferenceVariant(DecoratorSDK::COLOR_GRAYED_OUT);

	m_copySignPart = new DecoratorSDK::BitmapPart(this, m_eventSink);
}

}; // namespace UMLDecor
