//################################################################################################
//
// Bitmap part class (decorator part)
//	BitmapPart.h
//
//################################################################################################

#ifndef __BITMAPPART_H_
#define __BITMAPPART_H_


#include "StdAfx.h"
#include "ResizablePart.h"


namespace DecoratorSDK {

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
	virtual feature_code	GetFeatures			(void) const;
	virtual CSize			GetPreferredSize	(void) const;
	virtual void			Draw				(CDC* pDC, Gdiplus::Graphics* gdip);

	virtual void			InitializeEx		(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);

	virtual void			DrawBorder			(CDC* pDC, Gdiplus::Graphics* gdip);
	virtual void			DrawBackground		(CDC* pDC, Gdiplus::Graphics* gdip);
	virtual void			DrawIcons			(CDC* pDC, Gdiplus::Graphics* gdip);
};

}; // namespace DecoratorSDK

#endif //__BITMAPPART_H_
