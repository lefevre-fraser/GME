//################################################################################################
//
// Inheritance vector part decorator class
//	InheritanceVectorPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "InheritanceVectorPart.h"

#include "DecoratorDefs.h"


namespace DecoratorSDK {

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
									  HWND parentWnd, PreferenceMap& preferences)
{
	TriangleVectorPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);

	if (m_inheritanceType == ImplementationInheritance || m_inheritanceType == InterfaceInheritance) {
		//dc.SelectObject(getFacilities().getBrush(m_isActive ? m_color : COLOR_GRAYED_OUT));

		getFacilities().getMetaFCO(pPart, m_spMetaFCO);
		bool bColor = false;
		COLORREF crColor = COLOR_BLACK;
		PreferenceMap::iterator it = preferences.find(PREF_COLOR);
		if (it != preferences.end()) {
			bColor = true;
			crColor = it->second.uValue.crValue;
		} else {
			bColor = getFacilities().getPreference(pFCO, m_spMetaFCO, PREF_COLOR, crColor);
		}
		AbsoluteCoordCommand* colorCmd = new AbsoluteCoordCommand(crColor);
		AbsoluteCoordCommand* grayedCmd = new AbsoluteCoordCommand(COLOR_GRAYED_OUT);
		m_coordCommands.push_back(colorCmd);
		m_coordCommands.push_back(grayedCmd);
		unsigned long size = m_coordCommands.size();
		AddCommand(VectorCommand(colorCmd, grayedCmd, VectorCommand::SelectBrush));

		if (m_inheritanceType == InterfaceInheritance)
			AddCommand(VectorCommand(VectorCommand::SelectNullBrush));

		// Looks awful
//		if (m_inheritanceType == ImplementationInheritance)
//			AddCommand(VectorCommand(VectorCommand::SelectNullPen));

		// Add four coordinates for the inner circle boundaries
		ComplexCoordCommand* ellipseLeft = new ComplexCoordCommand(LeftMost, 0.5 - 0.25 * INHERITANCE_RATIO);
		ellipseLeft->AddCommand(RightMost, 0.5 + 0.25 * INHERITANCE_RATIO, CoordAdd);
		ellipseLeft->AddCommand(OneConstant, 1.0, CoordAdd);	// correction in case of small sizes
		ComplexCoordCommand* ellipseTop = new ComplexCoordCommand(TopMost, 1.0 / 3.0 - 0.25);
		ellipseTop->AddCommand(BottomMost, 2.0 / 3.0 + 0.25, CoordAdd);
		ComplexCoordCommand* ellipseRight = new ComplexCoordCommand(LeftMost, 0.5 + 0.25 * INHERITANCE_RATIO);
		ellipseRight->AddCommand(RightMost, 0.5 - 0.25 * INHERITANCE_RATIO, CoordAdd);
		ComplexCoordCommand* ellipseBottom = new ComplexCoordCommand(TopMost, 1.0 / 3.0 + 0.25);
		ellipseBottom->AddCommand(BottomMost, 2.0 / 3.0 - 0.25, CoordAdd);

		m_coordCommands.push_back(ellipseLeft);
		m_coordCommands.push_back(ellipseTop);
		m_coordCommands.push_back(ellipseRight);
		m_coordCommands.push_back(ellipseBottom);
		size = m_coordCommands.size();
		AddCommand(VectorCommand(m_coordCommands[size - 4],
								 m_coordCommands[size - 3],
								 m_coordCommands[size - 2],
								 m_coordCommands[size - 1],
								 VectorCommand::Ellipse));
	}
}

}; // namespace DecoratorSDK
