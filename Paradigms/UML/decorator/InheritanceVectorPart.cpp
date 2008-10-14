//################################################################################################
//
// Inheritance vector part decorator class
//	InheritanceVectorPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "DecoratorStd.h"
#include "InheritanceVectorPart.h"


//################################################################################################
//
// CLASS : InheritanceVectorPart
//
//################################################################################################

InheritanceVectorPart::InheritanceVectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	VectorPart(pPart, eventSink)
{
}

InheritanceVectorPart::~InheritanceVectorPart()
{
	for(unsigned long i = 0; i < coordCommands.size(); i++) {
		delete coordCommands[i];
	}
	coordCommands.clear();
}

CSize InheritanceVectorPart::GetPreferredSize(void) const
{
	CSize prefSize = ResizablePart::GetPreferredSize();
	if (prefSize != CSize(0, 0))
		return prefSize;
	return CSize(static_cast<long> (UML_INHERITANCE_WIDTH), static_cast<long> (UML_INHERITANCE_HEIGHT));
}

void InheritanceVectorPart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	VectorPart::Initialize(pProject, pPart, pFCO);

	coordCommands.push_back(new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::LeftMost));
	coordCommands.push_back(new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::BottomMost));
	coordCommands.push_back(new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::RightMost));
	coordCommands.push_back(new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::BottomMost));
	DecoratorSDK::ComplexCoordCommand* triangletip = new DecoratorSDK::ComplexCoordCommand(DecoratorSDK::LeftMost);
	triangletip->AddCommand(DecoratorSDK::RightMost, 0.5, DecoratorSDK::CoordAdd);
	triangletip->AddCommand(DecoratorSDK::LeftMost, 0.5, DecoratorSDK::CoordSubstract);
	coordCommands.push_back(triangletip);
	coordCommands.push_back(new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::TopMost));
	coordCommands.push_back(new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::LeftMost));
	coordCommands.push_back(new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::BottomMost));

	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::BeginPath));
	AddCommand(DecoratorSDK::VectorCommand(coordCommands[0], coordCommands[1], DecoratorSDK::VectorCommand::MoveTo));
	AddCommand(DecoratorSDK::VectorCommand(coordCommands[2], coordCommands[3], DecoratorSDK::VectorCommand::LineTo));
	AddCommand(DecoratorSDK::VectorCommand(coordCommands[4], coordCommands[5], DecoratorSDK::VectorCommand::LineTo));
	AddCommand(DecoratorSDK::VectorCommand(coordCommands[6], coordCommands[7], DecoratorSDK::VectorCommand::LineTo));
	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::EndPath));
	AddCommand(DecoratorSDK::VectorCommand(DecoratorSDK::VectorCommand::StrokeAndFillPath));
}

// New functions
void InheritanceVectorPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
										 HWND parentWnd, DecoratorSDK::PreferenceMap& preferences)
{
	VectorPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

void InheritanceVectorPart::SetBrush(CDC* pDC)
{
	pDC->SelectStockObject(NULL_BRUSH);
}
