//################################################################################################
//
// Constraint Bitmap part class (decorator part)
//	ConstraintBitmapPart.h
//
//################################################################################################

#ifndef __CONSTRAINTBITMAPPART_H_
#define __CONSTRAINTBITMAPPART_H_


#include "StdAfx.h"
#include "BitmapPart.h"


//################################################################################################
//
// CLASS : ConstraintBitmapPart
//
//################################################################################################

class ConstraintBitmapPart: public DecoratorSDK::BitmapPart
{
protected:
	long		m_lBitmapResID;
	COLORREF	m_crTransparent;
	COLORREF	m_crGrayedOut;

public:
	ConstraintBitmapPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink, long bitmapResID,
						 COLORREF transparentColor, COLORREF grayedOutColor);
	virtual ~ConstraintBitmapPart();

// =============== resembles IMgaNewDecorator
public:
	virtual void			Initialize			(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO);
	virtual feature_code	GetFeatures			(void) const;

	virtual void			InitializeEx		(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, DecoratorSDK::PreferenceMap& preferences);

	virtual void			DrawBackground		(CDC* pDC);
};

#endif //__CONSTRAINTBITMAPPART_H_
