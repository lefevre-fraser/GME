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

AnnotatorRectanglePart::AnnotatorRectanglePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	VectorPart(pPart, eventSink),
	m_bRoundEdgeRect		(false),
	m_bRoundEdgeRadius		(9)
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

	m_bRoundEdgeRect = false;
	DecoratorSDK::PreferenceMap::iterator it = preferences.find(DecoratorSDK::PREF_ROUNDEDGERECT);
	if (it != preferences.end()) {
		m_bRoundEdgeRect = it->second.uValue.bValue;
	} else {
		DecoratorSDK::getFacilities().getPreference(m_spFCO, m_spMetaFCO, DecoratorSDK::PREF_ROUNDEDGERECT, m_bRoundEdgeRect);
	}

	m_bRoundEdgeRadius = 9;
	it = preferences.find(DecoratorSDK::PREF_ROUNDEDGERADIUS);
	if (it != preferences.end()) {
		m_bRoundEdgeRadius = it->second.uValue.bValue;
	} else {
		DecoratorSDK::getFacilities().getPreference(m_spFCO, m_spMetaFCO, DecoratorSDK::PREF_ROUNDEDGERADIUS, m_bRoundEdgeRadius, false);
	}

	DecoratorSDK::SimpleCoordCommand* leftMost		= new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::LeftMost);
	DecoratorSDK::SimpleCoordCommand* topMost		= new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::TopMost);
	DecoratorSDK::SimpleCoordCommand* rightMost		= new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::RightMost);
	DecoratorSDK::SimpleCoordCommand* bottomMost	= new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::BottomMost);
	m_coordCommands.push_back(leftMost);
	m_coordCommands.push_back(topMost);
	m_coordCommands.push_back(rightMost);
	m_coordCommands.push_back(bottomMost);

	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::BeginPath));

	if (m_bRoundEdgeRect) {
		DecoratorSDK::ComplexCoordCommand* leftoRadius = new DecoratorSDK::ComplexCoordCommand(DecoratorSDK::LeftMost);
		leftoRadius->AddCommand(DecoratorSDK::OneConstant, m_bRoundEdgeRadius, DecoratorSDK::CoordAdd);
		DecoratorSDK::ComplexCoordCommand* topoRadius = new DecoratorSDK::ComplexCoordCommand(DecoratorSDK::TopMost);
		topoRadius->AddCommand(DecoratorSDK::OneConstant, m_bRoundEdgeRadius, DecoratorSDK::CoordAdd);
		DecoratorSDK::ComplexCoordCommand* rightoRadius = new DecoratorSDK::ComplexCoordCommand(DecoratorSDK::RightMost);
		rightoRadius->AddCommand(DecoratorSDK::OneConstant, m_bRoundEdgeRadius, DecoratorSDK::CoordSubstract);
		DecoratorSDK::ComplexCoordCommand* bottomoRadius = new DecoratorSDK::ComplexCoordCommand(DecoratorSDK::BottomMost);
		bottomoRadius->AddCommand(DecoratorSDK::OneConstant, m_bRoundEdgeRadius, DecoratorSDK::CoordSubstract);

		DecoratorSDK::ComplexCoordCommand* lefto2Radius = new DecoratorSDK::ComplexCoordCommand(DecoratorSDK::LeftMost);
		lefto2Radius->AddCommand(DecoratorSDK::OneConstant, 2 * m_bRoundEdgeRadius, DecoratorSDK::CoordAdd);
		DecoratorSDK::ComplexCoordCommand* topo2Radius = new DecoratorSDK::ComplexCoordCommand(DecoratorSDK::TopMost);
		topo2Radius->AddCommand(DecoratorSDK::OneConstant, 2 * m_bRoundEdgeRadius, DecoratorSDK::CoordAdd);
		DecoratorSDK::ComplexCoordCommand* righto2Radius = new DecoratorSDK::ComplexCoordCommand(DecoratorSDK::RightMost);
		righto2Radius->AddCommand(DecoratorSDK::OneConstant, 2 * m_bRoundEdgeRadius, DecoratorSDK::CoordSubstract);
		DecoratorSDK::ComplexCoordCommand* bottomo2Radius = new DecoratorSDK::ComplexCoordCommand(DecoratorSDK::BottomMost);
		bottomo2Radius->AddCommand(DecoratorSDK::OneConstant, 2 * m_bRoundEdgeRadius, DecoratorSDK::CoordSubstract);

		DecoratorSDK::AbsoluteCoordCommand* radiusCommand = new DecoratorSDK::AbsoluteCoordCommand(m_bRoundEdgeRadius);
		DecoratorSDK::AbsoluteCoordCommand* diameterCommand = new DecoratorSDK::AbsoluteCoordCommand(2 * m_bRoundEdgeRadius);
		DecoratorSDK::SimpleCoordCommand* angle0Command = new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::ZeroConstant);
		DecoratorSDK::AbsoluteCoordCommand* angle90Command = new DecoratorSDK::AbsoluteCoordCommand(90);
		DecoratorSDK::AbsoluteCoordCommand* angle180Command = new DecoratorSDK::AbsoluteCoordCommand(180);
		DecoratorSDK::AbsoluteCoordCommand* angle270Command = new DecoratorSDK::AbsoluteCoordCommand(270);

		m_coordCommands.push_back(leftoRadius);
		m_coordCommands.push_back(topoRadius);
		m_coordCommands.push_back(rightoRadius);
		m_coordCommands.push_back(bottomoRadius);
		m_coordCommands.push_back(lefto2Radius);
		m_coordCommands.push_back(topo2Radius);
		m_coordCommands.push_back(righto2Radius);
		m_coordCommands.push_back(bottomo2Radius);
		m_coordCommands.push_back(radiusCommand);
		m_coordCommands.push_back(diameterCommand);
		m_coordCommands.push_back(angle0Command);
		m_coordCommands.push_back(angle90Command);
		m_coordCommands.push_back(angle180Command);
		m_coordCommands.push_back(angle270Command);

		std::vector<const DecoratorSDK::CoordCommand*> m_arcParams;
		m_arcParams.push_back(leftMost);
		m_arcParams.push_back(topMost);
		m_arcParams.push_back(diameterCommand);
		m_arcParams.push_back(diameterCommand);
		m_arcParams.push_back(angle180Command);
		m_arcParams.push_back(angle90Command);
		AddCommand(DecoratorSDK::VectorCommand(m_arcParams, DecoratorSDK::VectorCommand::AddArcToPath));
		AddCommand(DecoratorSDK::VectorCommand(leftoRadius, topMost, rightoRadius, topMost, DecoratorSDK::VectorCommand::AddLineToPath));
		m_arcParams[0] = righto2Radius;
		m_arcParams[1] = topMost;
		m_arcParams[2] = diameterCommand;
		m_arcParams[3] = diameterCommand;
		m_arcParams[4] = angle270Command;
		m_arcParams[5] = angle90Command;
		AddCommand(DecoratorSDK::VectorCommand(m_arcParams, DecoratorSDK::VectorCommand::AddArcToPath));
		AddCommand(DecoratorSDK::VectorCommand(rightMost, topoRadius, rightMost, bottomoRadius, DecoratorSDK::VectorCommand::AddLineToPath));
		m_arcParams[0] = righto2Radius;
		m_arcParams[1] = bottomo2Radius;
		m_arcParams[2] = diameterCommand;
		m_arcParams[3] = diameterCommand;
		m_arcParams[4] = angle0Command;
		m_arcParams[5] = angle90Command;
		AddCommand(DecoratorSDK::VectorCommand(m_arcParams, DecoratorSDK::VectorCommand::AddArcToPath));
		AddCommand(DecoratorSDK::VectorCommand(rightoRadius, bottomMost, leftoRadius, bottomMost, DecoratorSDK::VectorCommand::AddLineToPath));
		m_arcParams[0] = leftMost;
		m_arcParams[1] = bottomo2Radius;
		m_arcParams[2] = diameterCommand;
		m_arcParams[3] = diameterCommand;
		m_arcParams[4] = angle90Command;
		m_arcParams[5] = angle90Command;
		AddCommand(DecoratorSDK::VectorCommand(m_arcParams, DecoratorSDK::VectorCommand::AddArcToPath));
		AddCommand(DecoratorSDK::VectorCommand(leftMost, bottomoRadius, leftMost, topoRadius, DecoratorSDK::VectorCommand::AddLineToPath));
	} else {
		AddCommand(DecoratorSDK::VectorCommand(leftMost,		bottomMost,	rightMost,		bottomMost,	DecoratorSDK::VectorCommand::AddLineToPath));
		AddCommand(DecoratorSDK::VectorCommand(rightMost,		bottomMost,	rightMost,		topMost,	DecoratorSDK::VectorCommand::AddLineToPath));
		AddCommand(DecoratorSDK::VectorCommand(rightMost,		topMost,	leftMost,		topMost,	DecoratorSDK::VectorCommand::AddLineToPath));
		AddCommand(DecoratorSDK::VectorCommand(leftMost,		topMost,	leftMost,		bottomMost,	DecoratorSDK::VectorCommand::AddLineToPath));
	}

	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::EndPath));
	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::CopyShadowPath));
	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::CastShadowPath));
	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::FillPath));
}

}; // namespace AnnotatorDecor
