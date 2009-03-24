//################################################################################################
//
// Ellipse vector part decorator class
//	EllipseVectorPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "EllipseVectorPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : EllipseVectorPart
//
//################################################################################################

EllipseVectorPart::EllipseVectorPart(PartBase* pPart, CComPtr<IMgaCommonDecoratorEvents>& eventSink,
									 long ellipseWidth, long ellipseHeight):
	VectorPart(pPart, eventSink),
	m_ellipseWidth(ellipseWidth),
	m_ellipseHeight(ellipseHeight)
{
}

EllipseVectorPart::~EllipseVectorPart()
{
}

CSize EllipseVectorPart::GetPreferredSize(void) const
{
	CSize prefSize = ResizablePart::GetPreferredSize();
	if (prefSize != CSize(0, 0))
		return prefSize;
	return CSize(m_ellipseWidth, m_ellipseHeight);
}

// New functions
void EllipseVectorPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									 HWND parentWnd, PreferenceMap& preferences)
{
	VectorPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);

	SimpleCoordCommand* leftMost	= new SimpleCoordCommand(LeftMost);
	SimpleCoordCommand* topMost		= new SimpleCoordCommand(TopMost);
	SimpleCoordCommand* rightMost	= new SimpleCoordCommand(RightMost);
	SimpleCoordCommand* bottomMost	= new SimpleCoordCommand(BottomMost);
	m_coordCommands.push_back(leftMost);
	m_coordCommands.push_back(topMost);
	m_coordCommands.push_back(rightMost);
	m_coordCommands.push_back(bottomMost);

	AddCommand(VectorCommand(VectorCommand::BeginPath));
	AddCommand(VectorCommand(leftMost, topMost, rightMost, bottomMost, VectorCommand::AddEllipseToPath));
	AddCommand(VectorCommand(VectorCommand::EndPath));
	AddCommand(VectorCommand(VectorCommand::CopyShadowPath));
	AddCommand(VectorCommand(VectorCommand::CastShadowPath));

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
	AddCommand(VectorCommand(colorCmd, grayedCmd, VectorCommand::StrokeAndFillPath));
}

}; // namespace DecoratorSDK
