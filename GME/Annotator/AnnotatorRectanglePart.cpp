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
	VectorPart(pPart, eventSink)
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
	preferences[DecoratorSDK::PREF_ITEMSHADOWCAST] = DecoratorSDK::PreferenceVariant(true);
	VectorPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);

	DecoratorSDK::SimpleCoordCommand* leftMost		= new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::LeftMost);
	DecoratorSDK::SimpleCoordCommand* topMost		= new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::TopMost);
	DecoratorSDK::SimpleCoordCommand* rightMost		= new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::RightMost);
	DecoratorSDK::SimpleCoordCommand* bottomMost	= new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::BottomMost);
	m_coordCommands.push_back(leftMost);
	m_coordCommands.push_back(topMost);
	m_coordCommands.push_back(rightMost);
	m_coordCommands.push_back(bottomMost);

	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::BeginPath));
	AddCommand(DecoratorSDK::VectorCommand(leftMost,		bottomMost,	rightMost,		bottomMost,	DecoratorSDK::VectorCommand::AddLineToPath));
	AddCommand(DecoratorSDK::VectorCommand(rightMost,		bottomMost,	rightMost,		topMost,	DecoratorSDK::VectorCommand::AddLineToPath));
	AddCommand(DecoratorSDK::VectorCommand(rightMost,		topMost,	leftMost,		topMost,	DecoratorSDK::VectorCommand::AddLineToPath));
	AddCommand(DecoratorSDK::VectorCommand(leftMost,		topMost,	leftMost,		bottomMost,	DecoratorSDK::VectorCommand::AddLineToPath));
	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::EndPath));
	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::CopyShadowPath));
	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::CastShadowPath));
	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::FillPath));
}

}; // namespace AnnotatorDecor
