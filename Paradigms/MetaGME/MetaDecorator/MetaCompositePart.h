//################################################################################################
//
// New Meta decorator composite part class
//	MetaCompositePart.h
//
//################################################################################################

#ifndef __METACOMPOSITEPART_H_
#define __METACOMPOSITEPART_H_


#include "StdAfx.h"
#include "BitmapAndLabelPart.h"


namespace MetaDecor {

//################################################################################################
//
// CLASS : MetaCompositePart
//
//################################################################################################

	class MetaCompositePart: public DecoratorSDK::BitmapAndLabelPart
{
public:
	MetaCompositePart(DecoratorSDK::PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~MetaCompositePart();

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

}; // namespace MetaDecor

#endif //__METACOMPOSITEPART_H_
