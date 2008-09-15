//################################################################################################
//
// Typeable bitmap part class (decorator part)
//	TypeableBitmapPart.h
//
//################################################################################################

#ifndef __TYPEABLEBITMAPPART_H_
#define __TYPEABLEBITMAPPART_H_


#include "../StdAfx.h"
#include "BitmapPart.h"


namespace Decorator {

//################################################################################################
//
// CLASS : TypeableBitmapPart
//
//################################################################################################

class TypeableBitmapPart: public BitmapPart
{
protected:
	bool				m_bTypeIconEnabled;
	int					m_iTypeInfo;

public:
	TypeableBitmapPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~TypeableBitmapPart();

// =============== resembles IMgaNewDecorator
public:
	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);

protected:
	virtual void	DrawIcons					(CDC* pDC);
};

}; // namespace Decorator

#endif //__TYPEABLEBITMAPPART_H_
