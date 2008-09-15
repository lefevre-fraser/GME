//################################################################################################
//
// New Box decorator composite part class
//	BoxCompositePart.h
//
//################################################################################################

#ifndef __BOXCOMPOSITEPART_H_
#define __BOXCOMPOSITEPART_H_


#include "../StdAfx.h"
#include "BitmapAndLabelPart.h"


namespace Decorator {

//################################################################################################
//
// CLASS : BoxCompositePart
//
//################################################################################################

class BoxCompositePart: public BitmapAndLabelPart
{
public:
	BoxCompositePart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~BoxCompositePart();

// =============== resembles IMgaNewDecorator
public:
	virtual CRect	GetPortLocation				(CComPtr<IMgaFCO>& fco) const;
	virtual bool	GetPorts					(CComPtr<IMgaFCOs>& portFCOs) const;
	virtual CRect	GetLabelLocation			(void) const;

	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);
	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd);
};

}; // namespace Decorator

#endif //__BOXCOMPOSITEPART_H_
