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

DiamondVectorPart::DiamondVectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink,
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

void DiamondVectorPart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	VectorPart::Initialize(pProject, pPart, pFCO);

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
	AddCommand(VectorCommand(leftMost,	centery,	VectorCommand::MoveTo));
	AddCommand(VectorCommand(centerx,	bottomMost,	VectorCommand::LineTo));
	AddCommand(VectorCommand(rightMost,	centery,	VectorCommand::LineTo));
	AddCommand(VectorCommand(centerx,	topMost,	VectorCommand::LineTo));
	AddCommand(VectorCommand(leftMost,	centery,	VectorCommand::LineTo));
	AddCommand(VectorCommand(VectorCommand::EndPath));
	AddCommand(VectorCommand(VectorCommand::StrokeAndFillPath));
}

// New functions
void DiamondVectorPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									  HWND parentWnd, PreferenceMap& preferences)
{
	VectorPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

void DiamondVectorPart::SetBrush(CDC* pDC)
{
	pDC->SelectStockObject(NULL_BRUSH);
}

}; // namespace DecoratorSDK
