//################################################################################################
//
// Annotator rectangle part decorator class
//	AnnotatorRectanglePart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "AnnotatorRectanglePart.h"


namespace AnnotatorDecor {

//################################################################################################
//
// CLASS : AnnotatorRectanglePart
//
//################################################################################################

AnnotatorRectanglePart::AnnotatorRectanglePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents>& eventSink):
	VectorPart(pPart, eventSink),
	m_bRoundCornerRect		(false),
	m_bRoundCornerRadius	(9)
{
	brushColorVariableName	= DecoratorSDK::PREF_FILLCOLOR;
}

AnnotatorRectanglePart::~AnnotatorRectanglePart()
{
}

void AnnotatorRectanglePart::Draw(CDC* pDC, Gdiplus::Graphics* gdip)
{
	VectorPart::Draw(pDC, gdip);
}

// New functions
void AnnotatorRectanglePart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
										  HWND parentWnd, DecoratorSDK::PreferenceMap& preferences)
{
	VectorPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);

	m_bRoundCornerRect = false;
	DecoratorSDK::PreferenceMap::iterator it = preferences.find(DecoratorSDK::PREF_ROUNDCORNERRECT);
	if (it != preferences.end()) {
		m_bRoundCornerRect = it->second.uValue.bValue;
	} else {
		DecoratorSDK::getFacilities().getPreference(m_spFCO, m_spMetaFCO, DecoratorSDK::PREF_ROUNDCORNERRECT, m_bRoundCornerRect);
	}

	m_bRoundCornerRadius = 9;
	it = preferences.find(DecoratorSDK::PREF_ROUNDCORNERRADIUS);
	if (it != preferences.end()) {
		m_bRoundCornerRadius = it->second.uValue.bValue;
	} else {
		DecoratorSDK::getFacilities().getPreference(m_spFCO, m_spMetaFCO, DecoratorSDK::PREF_ROUNDCORNERRADIUS, m_bRoundCornerRadius, false);
	}

	DecoratorSDK::SimpleCoordCommand* leftMost			= new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::LeftMost);
	DecoratorSDK::SimpleCoordCommand* topMost			= new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::TopMost);
	DecoratorSDK::SimpleCoordCommand* rightMost			= new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::RightMost);
	DecoratorSDK::SimpleCoordCommand* bottomMost		= new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::BottomMost);
	DecoratorSDK::AbsoluteCoordCommand* radiusCommand	= new DecoratorSDK::AbsoluteCoordCommand(m_bRoundCornerRect ? m_bRoundCornerRadius : 0);
	m_coordCommands.push_back(leftMost);
	m_coordCommands.push_back(topMost);
	m_coordCommands.push_back(rightMost);
	m_coordCommands.push_back(bottomMost);
	m_coordCommands.push_back(radiusCommand);

	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::BeginPath));
	std::vector<const DecoratorSDK::CoordCommand*> m_roundRectangleParams;
	m_roundRectangleParams.push_back(leftMost);
	m_roundRectangleParams.push_back(topMost);
	m_roundRectangleParams.push_back(rightMost);
	m_roundRectangleParams.push_back(bottomMost);
	m_roundRectangleParams.push_back(radiusCommand);
	AddCommand(DecoratorSDK::VectorCommand(m_roundRectangleParams, DecoratorSDK::VectorCommand::AddRoundRectangleToPath));
	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::EndPath));
	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::CopyShadowPath));
	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::CastShadowPath));
	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::FillPath));
}

}; // namespace AnnotatorDecor
