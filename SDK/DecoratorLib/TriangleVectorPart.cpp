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

	SimpleCoordCommand* leftMost		= new SimpleCoordCommand(LeftMost);
	SimpleCoordCommand* topMost			= new SimpleCoordCommand(TopMost);
	SimpleCoordCommand* rightMost		= new SimpleCoordCommand(RightMost);
	SimpleCoordCommand* bottomMost		= new SimpleCoordCommand(BottomMost);
	ComplexCoordCommand* triangletip	= new ComplexCoordCommand(LeftMost);
	triangletip->AddCommand(RightMost, 0.5, CoordAdd);
	triangletip->AddCommand(LeftMost, 0.5, CoordSubstract);
	m_coordCommands.push_back(leftMost);
	m_coordCommands.push_back(topMost);
	m_coordCommands.push_back(rightMost);
	m_coordCommands.push_back(bottomMost);
	m_coordCommands.push_back(triangletip);

	AddCommand(VectorCommand(VectorCommand::BeginPath));
	AddCommand(VectorCommand(leftMost,		bottomMost,	VectorCommand::MoveTo));
	AddCommand(VectorCommand(rightMost,		bottomMost,	VectorCommand::LineTo));
	AddCommand(VectorCommand(triangletip,	topMost,	VectorCommand::LineTo));
	AddCommand(VectorCommand(leftMost,		bottomMost,	VectorCommand::LineTo));
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
