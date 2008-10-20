//################################################################################################
//
// Triangle vector part decorator class
//	TriangleVectorPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "TriangleVectorPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : TriangleVectorPart
//
//################################################################################################

TriangleVectorPart::TriangleVectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink,
									   long triangleWidth, long triangleHeight):
	VectorPart(pPart, eventSink),
	m_triangleWidth(triangleWidth),
	m_triangleHeight(triangleHeight)
{
}

TriangleVectorPart::~TriangleVectorPart()
{
	for(unsigned long i = 0; i < m_coordCommands.size(); i++) {
		delete m_coordCommands[i];
	}
	m_coordCommands.clear();
}

CSize TriangleVectorPart::GetPreferredSize(void) const
{
	CSize prefSize = ResizablePart::GetPreferredSize();
	if (prefSize != CSize(0, 0))
		return prefSize;
	return CSize(m_triangleWidth, m_triangleHeight);
}

void TriangleVectorPart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	VectorPart::Initialize(pProject, pPart, pFCO);

	m_coordCommands.push_back(new SimpleCoordCommand(LeftMost));
	m_coordCommands.push_back(new SimpleCoordCommand(TopMost));
	m_coordCommands.push_back(new SimpleCoordCommand(RightMost));
	m_coordCommands.push_back(new SimpleCoordCommand(BottomMost));
	ComplexCoordCommand* triangletip = new ComplexCoordCommand(LeftMost);
	triangletip->AddCommand(RightMost, 0.5, CoordAdd);
	triangletip->AddCommand(LeftMost, 0.5, CoordSubstract);
	m_coordCommands.push_back(triangletip);

	AddCommand(VectorCommand(VectorCommand::BeginPath));
	AddCommand(VectorCommand(m_coordCommands[0], m_coordCommands[3], VectorCommand::MoveTo));	// Left Bottom
	AddCommand(VectorCommand(m_coordCommands[2], m_coordCommands[3], VectorCommand::LineTo));	// Right Bottom
	AddCommand(VectorCommand(m_coordCommands[4], m_coordCommands[1], VectorCommand::LineTo));	// CenterX Top
	AddCommand(VectorCommand(m_coordCommands[0], m_coordCommands[3], VectorCommand::LineTo));	// Left Bottom
	AddCommand(VectorCommand(VectorCommand::EndPath));
	AddCommand(VectorCommand(VectorCommand::StrokeAndFillPath));
}

// New functions
void TriangleVectorPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									  HWND parentWnd, PreferenceMap& preferences)
{
	VectorPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

void TriangleVectorPart::SetBrush(CDC* pDC)
{
	pDC->SelectStockObject(NULL_BRUSH);
}

}; // namespace DecoratorSDK
