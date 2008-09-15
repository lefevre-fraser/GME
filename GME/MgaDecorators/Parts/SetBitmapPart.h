//################################################################################################
//
// Set bitmap part class (decorator part)
//	SetBitmapPart.h
//
//################################################################################################

#ifndef __SETBITMAPPART_H_
#define __SETBITMAPPART_H_


#include "../StdAfx.h"
#include "TypeableBitmapPart.h"


namespace Decorator {

//################################################################################################
//
// CLASS : SetBitmapPart
//
//################################################################################################

class SetBitmapPart: public TypeableBitmapPart
{
public:
	SetBitmapPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~SetBitmapPart();

// =============== resembles IMgaNewDecorator
public:
	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);

	virtual void	DrawBackground				(CDC* pDC);
};

}; // namespace Decorator

#endif //__SETBITMAPPART_H_
