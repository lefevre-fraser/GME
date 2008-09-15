//################################################################################################
//
// Bitmap part class (decorator part)
//	BitmapPart.h
//
//################################################################################################

#ifndef __BITMAPPART_H_
#define __BITMAPPART_H_


#include "../StdAfx.h"
#include "ResizablePart.h"


namespace Decorator {

//################################################################################################
//
// CLASS : BitmapPart
//
//################################################################################################

class BitmapPart: public ResizablePart
{
protected:
	BitmapBase*		m_pBitmap;
	TileVector*		m_pTileVector;
	COLORREF		m_crOverlay;
	bool			m_bOverlay;
	COLORREF		m_crBorder;

public:
	BitmapPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~BitmapPart();

// =============== resembles IMgaNewDecorator
public:
	virtual void			Initialize			(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO);
	virtual feature_code	GetFeatures			(void) const;
	virtual CSize			GetPreferredSize	(void) const;
	virtual void			Draw				(CDC* pDC);

	virtual void			InitializeEx		(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);

	virtual void			DrawBorder			(CDC* pDC);
	virtual void			DrawBackground		(CDC* pDC);
	virtual void			DrawIcons			(CDC* pDC);
};

}; // namespace Decorator

#endif //__BITMAPPART_H_
