//################################################################################################
//
// Connector vector part decorator class
//	VectorPart.h
//
//################################################################################################

#ifndef __CONNECTORVECTORPART_H_
#define __CONNECTORVECTORPART_H_


#include "StdAfx.h"
#include "VectorPart.h"
#include "ConnectorVectorPart.h"


//################################################################################################
//
// CLASS : ConnectorVectorPart
//
//################################################################################################

class ConnectorVectorPart: public DecoratorSDK::VectorPart
{
	std::vector<DecoratorSDK::CoordCommand*>	coordCommands;

public:
	ConnectorVectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~ConnectorVectorPart();

// =============== resembles IMgaNewDecorator
public:
	virtual void			Initialize			(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO);
	virtual CSize			GetPreferredSize	(void) const;

	virtual void			InitializeEx		(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, DecoratorSDK::PreferenceMap& preferences);
};

#endif //__CONNECTORVECTORPART_H_
