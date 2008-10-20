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
	for(unsigned long i = 0; i < m_coordCommands.size(); i++) {
		delete m_coordCommands[i];
	}
	m_coordCommands.clear();
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

	m_coordCommands.push_back(new SimpleCoordCommand(LeftMost));
	m_coordCommands.push_back(new SimpleCoordCommand(TopMost));
	m_coordCommands.push_back(new SimpleCoordCommand(RightMost));
	m_coordCommands.push_back(new SimpleCoordCommand(BottomMost));
	ComplexCoordCommand* centerx = new ComplexCoordCommand(LeftMost);
	centerx->AddCommand(RightMost, 0.5, CoordAdd);
	centerx->AddCommand(LeftMost, 0.5, CoordSubstract);
	m_coordCommands.push_back(centerx);
	ComplexCoordCommand* centery = new ComplexCoordCommand(TopMost);
	centery->AddCommand(BottomMost, 0.5, CoordAdd);
	centery->AddCommand(TopMost, 0.5, CoordSubstract);
	m_coordCommands.push_back(centery);

	AddCommand(VectorCommand(VectorCommand::BeginPath));
	AddCommand(VectorCommand(m_coordCommands[0], m_coordCommands[5], VectorCommand::MoveTo));	// Left CenterY
	AddCommand(VectorCommand(m_coordCommands[4], m_coordCommands[3], VectorCommand::LineTo));	// CenterX Bottom
	AddCommand(VectorCommand(m_coordCommands[2], m_coordCommands[5], VectorCommand::LineTo));	// Right CenterY
	AddCommand(VectorCommand(m_coordCommands[4], m_coordCommands[1], VectorCommand::LineTo));	// CenterX Top
	AddCommand(VectorCommand(m_coordCommands[0], m_coordCommands[5], VectorCommand::LineTo));	// Left CenterY
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
