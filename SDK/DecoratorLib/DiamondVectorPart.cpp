//################################################################################################
//
// Diamond vector part decorator class
//	DiamondVectorPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "DiamondVectorPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : DiamondVectorPart
//
//################################################################################################

DiamondVectorPart::DiamondVectorPart(PartBase* pPart, CComPtr<IMgaElementDecoratorEvents>& eventSink,
									 long diamondWidth, long diamondHeight):
	VectorPart(pPart, eventSink),
	m_diamondWidth(diamondWidth),
	m_diamondHeight(diamondHeight)
{
}

DiamondVectorPart::~DiamondVectorPart()
{
}

CSize DiamondVectorPart::GetPreferredSize(void) const
{
	CSize prefSize = ResizablePart::GetPreferredSize();
	if (prefSize != CSize(0, 0))
		return prefSize;
	return CSize(m_diamondWidth, m_diamondHeight);
}

// New functions
void DiamondVectorPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									  HWND parentWnd, PreferenceMap& preferences)
{
	VectorPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);

	SimpleCoordCommand* leftMost	= new SimpleCoordCommand(LeftMost);
	SimpleCoordCommand* topMost		= new SimpleCoordCommand(TopMost);
	SimpleCoordCommand* rightMost	= new SimpleCoordCommand(RightMost);
	SimpleCoordCommand* bottomMost	= new SimpleCoordCommand(BottomMost);
	ComplexCoordCommand* centerx	= new ComplexCoordCommand(LeftMost, 0.5);
	centerx->AddCommand(RightMost, 0.5, CoordAdd);
	ComplexCoordCommand* centery	= new ComplexCoordCommand(TopMost, 0.5);
	centery->AddCommand(BottomMost, 0.5, CoordAdd);

	m_coordCommands.push_back(leftMost);
	m_coordCommands.push_back(topMost);
	m_coordCommands.push_back(rightMost);
	m_coordCommands.push_back(bottomMost);
	m_coordCommands.push_back(centerx);
	m_coordCommands.push_back(centery);

	AddCommand(VectorCommand(VectorCommand::BeginPath));
	AddCommand(VectorCommand(leftMost,	centery,	centerx,	bottomMost,	VectorCommand::AddLineToPath));
	AddCommand(VectorCommand(centerx,	bottomMost,	rightMost,	centery,	VectorCommand::AddLineToPath));
	AddCommand(VectorCommand(rightMost,	centery,	centerx,	topMost,	VectorCommand::AddLineToPath));
	AddCommand(VectorCommand(centerx,	topMost,	leftMost,	centery,	VectorCommand::AddLineToPath));
	AddCommand(VectorCommand(VectorCommand::EndPath));
	AddCommand(VectorCommand(VectorCommand::CopyShadowPath));
	AddCommand(VectorCommand(VectorCommand::CastShadowPath));
	AddCommand(VectorCommand(VectorCommand::StrokeAndFillPath));
}

}; // namespace DecoratorSDK
