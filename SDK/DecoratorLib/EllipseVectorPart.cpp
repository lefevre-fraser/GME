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
	for(unsigned long i = 0; i < m_coordCommands.size(); i++) {
		delete m_coordCommands[i];
	}
	m_coordCommands.clear();
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

	m_coordCommands.push_back(new SimpleCoordCommand(LeftMost));
	m_coordCommands.push_back(new SimpleCoordCommand(TopMost));
	m_coordCommands.push_back(new SimpleCoordCommand(RightMost));
	m_coordCommands.push_back(new SimpleCoordCommand(BottomMost));

	AddCommand(VectorCommand(m_coordCommands[0], m_coordCommands[1], m_coordCommands[2], m_coordCommands[3], VectorCommand::Ellipse));
}

// New functions
void EllipseVectorPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									 HWND parentWnd, PreferenceMap& preferences)
{
	VectorPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

}; // namespace DecoratorSDK
