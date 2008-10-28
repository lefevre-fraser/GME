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

EllipseVectorPart::EllipseVectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink,
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

void EllipseVectorPart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	VectorPart::Initialize(pProject, pPart, pFCO);

	SimpleCoordCommand* leftMost	= new SimpleCoordCommand(LeftMost);
	SimpleCoordCommand* topMost		= new SimpleCoordCommand(TopMost);
	SimpleCoordCommand* rightMost	= new SimpleCoordCommand(RightMost);
	SimpleCoordCommand* bottomMost	= new SimpleCoordCommand(BottomMost);
	m_coordCommands.push_back(leftMost);
	m_coordCommands.push_back(topMost);
	m_coordCommands.push_back(rightMost);
	m_coordCommands.push_back(bottomMost);

	AddCommand(VectorCommand(leftMost, topMost, rightMost, bottomMost, VectorCommand::Ellipse));
}

// New functions
void EllipseVectorPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									 HWND parentWnd, PreferenceMap& preferences)
{
	VectorPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

}; // namespace DecoratorSDK
