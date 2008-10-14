//################################################################################################
//
// Connector vector part decorator class
//	ConnectorVectorPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "DecoratorStd.h"
#include "ConnectorVectorPart.h"


//################################################################################################
//
// CLASS : ConnectorVectorPart
//
//################################################################################################

ConnectorVectorPart::ConnectorVectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	VectorPart(pPart, eventSink)
{
}

ConnectorVectorPart::~ConnectorVectorPart()
{
	for(unsigned long i = 0; i < coordCommands.size(); i++) {
		delete coordCommands[i];
	}
	coordCommands.clear();
}

CSize ConnectorVectorPart::GetPreferredSize(void) const
{
	CSize prefSize = ResizablePart::GetPreferredSize();
	if (prefSize != CSize(0, 0))
		return prefSize;
	return CSize(static_cast<long> (UML_CONNECTOR_WIDTH), static_cast<long> (UML_CONNECTOR_HEIGHT));
}

void ConnectorVectorPart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	VectorPart::Initialize(pProject, pPart, pFCO);

	coordCommands.push_back(new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::LeftMost));
	coordCommands.push_back(new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::TopMost));
	coordCommands.push_back(new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::RightMost));
	coordCommands.push_back(new DecoratorSDK::SimpleCoordCommand(DecoratorSDK::BottomMost));

	AddCommand(DecoratorSDK::VectorCommand(coordCommands[0], coordCommands[1], coordCommands[2], coordCommands[3], DecoratorSDK::VectorCommand::Ellipse));
}

// New functions
void ConnectorVectorPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
										 HWND parentWnd, DecoratorSDK::PreferenceMap& preferences)
{
	VectorPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}
