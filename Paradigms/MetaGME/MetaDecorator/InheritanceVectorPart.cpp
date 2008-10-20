//################################################################################################
//
// Inheritance vector part decorator class
//	InheritanceVectorPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "InheritanceVectorPart.h"

#include "DecoratorStd.h"


namespace MetaDecor {

//################################################################################################
//
// CLASS : InheritanceVectorPart
//
//################################################################################################

InheritanceVectorPart::InheritanceVectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink,
											 long inheritanceWidth, long inheritanceHeight, InheritanceType inheritanceType):
	TriangleVectorPart(pPart, eventSink, inheritanceWidth, inheritanceHeight),
	m_inheritanceType(inheritanceType)
{
}

InheritanceVectorPart::~InheritanceVectorPart()
{
}

void InheritanceVectorPart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	TriangleVectorPart::Initialize(pProject, pPart, pFCO);
}

// New functions
void InheritanceVectorPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									  HWND parentWnd, DecoratorSDK::PreferenceMap& preferences)
{
	TriangleVectorPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);

	if (m_inheritanceType == ImplementationInheritance || m_inheritanceType == InterfaceInheritance) {
		//dc.SelectObject(DecoratorSDK::getFacilities().getBrush(m_isActive ? m_color : DecoratorSDK::COLOR_GRAYED_OUT));

		DecoratorSDK::getFacilities().getMetaFCO(pPart, m_spMetaFCO);
		bool bColor = false;
		COLORREF crColor = DecoratorSDK::COLOR_BLACK;
		DecoratorSDK::PreferenceMap::iterator it = preferences.find(DecoratorSDK::PREF_COLOR);
		if (it != preferences.end()) {
			bColor = true;
			crColor = it->second.uValue.crValue;
		} else {
			bColor = DecoratorSDK::getFacilities().getPreference(pFCO, m_spMetaFCO, DecoratorSDK::PREF_COLOR, crColor);
		}
		m_coordCommands.push_back(new DecoratorSDK::AbsoluteCoordCommand((long)crColor));
		m_coordCommands.push_back(new DecoratorSDK::AbsoluteCoordCommand((long)DecoratorSDK::COLOR_GRAYED_OUT));
		unsigned long size = m_coordCommands.size();
		AddCommand(DecoratorSDK::VectorCommand(m_coordCommands[size - 2], m_coordCommands[size - 1], DecoratorSDK::VectorCommand::SelectBrush));

		if (m_inheritanceType == InterfaceInheritance) {
			AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::SelectNullBrush));
		}

		// Add four coordinates for the inner circle boundaries
		DecoratorSDK::ComplexCoordCommand* ellipseLeft = new DecoratorSDK::ComplexCoordCommand(DecoratorSDK::LeftMost);
		ellipseLeft->AddCommand(DecoratorSDK::RightMost, 0.5 + 0.25 * META_INHERITANCE_RATIO, DecoratorSDK::CoordAdd);
		ellipseLeft->AddCommand(DecoratorSDK::LeftMost, 0.5 + 0.25 * META_INHERITANCE_RATIO, DecoratorSDK::CoordSubstract);
		m_coordCommands.push_back(ellipseLeft);
		DecoratorSDK::ComplexCoordCommand* ellipseTop = new DecoratorSDK::ComplexCoordCommand(DecoratorSDK::TopMost);
		ellipseTop->AddCommand(DecoratorSDK::BottomMost, 2.0 / 3.0 + 0.25, DecoratorSDK::CoordAdd);
		ellipseTop->AddCommand(DecoratorSDK::TopMost, 2.0 / 3.0 + 0.25, DecoratorSDK::CoordSubstract);
		m_coordCommands.push_back(ellipseTop);
		DecoratorSDK::ComplexCoordCommand* ellipseRight = new DecoratorSDK::ComplexCoordCommand(DecoratorSDK::LeftMost);
		ellipseRight->AddCommand(DecoratorSDK::RightMost, 0.5 - 0.25 * META_INHERITANCE_RATIO, DecoratorSDK::CoordAdd);
		ellipseRight->AddCommand(DecoratorSDK::LeftMost, 0.5 - 0.25 * META_INHERITANCE_RATIO, DecoratorSDK::CoordSubstract);
		m_coordCommands.push_back(ellipseRight);
		DecoratorSDK::ComplexCoordCommand* ellipseBottom = new DecoratorSDK::ComplexCoordCommand(DecoratorSDK::TopMost);
		ellipseBottom->AddCommand(DecoratorSDK::BottomMost, 2.0 / 3.0 - 0.25, DecoratorSDK::CoordAdd);
		ellipseBottom->AddCommand(DecoratorSDK::TopMost, 2.0 / 3.0 - 0.25, DecoratorSDK::CoordSubstract);
		m_coordCommands.push_back(ellipseBottom);

		size = m_coordCommands.size();
		AddCommand(DecoratorSDK::VectorCommand(m_coordCommands[size - 4],
											   m_coordCommands[size - 3],
											   m_coordCommands[size - 2],
											   m_coordCommands[size - 1],
											   DecoratorSDK::VectorCommand::Ellipse));
	}
}

}; // namespace MetaDecor
