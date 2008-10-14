//################################################################################################
//
// New UML decorator composite part class
//	UMLCompositePart.h
//
//################################################################################################

#ifndef __UMLCOMPOSITEPART_H_
#define __UMLCOMPOSITEPART_H_


#include "StdAfx.h"
#include "ImageAndLabelPart.h"


namespace UMLDecor {

//################################################################################################
//
// CLASS : UMLCompositePart
//
//################################################################################################

	class UMLCompositePart: public DecoratorSDK::ImageAndLabelPart
{
public:
	UMLCompositePart(DecoratorSDK::PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~UMLCompositePart();

// =============== resembles IMgaNewDecorator
public:
	virtual CRect	GetPortLocation				(CComPtr<IMgaFCO>& fco) const;
	virtual bool	GetPorts					(CComPtr<IMgaFCOs>& portFCOs) const;
	virtual CRect	GetLabelLocation			(void) const;

	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, DecoratorSDK::PreferenceMap& preferences);
	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd);
};

}; // namespace UMLDecor

#endif //__UMLCOMPOSITEPART_H_
