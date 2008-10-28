//################################################################################################
//
// Ellipse vector part decorator class
//	EllipseVectorPart.h
//
//################################################################################################

#ifndef __ELLIPSEVECTORPART_H_
#define __ELLIPSEVECTORPART_H_


#include "StdAfx.h"
#include "VectorPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : EllipseVectorPart
//
//################################################################################################

class EllipseVectorPart: public VectorPart
{
	long						m_ellipseWidth;
	long						m_ellipseHeight;

public:
	EllipseVectorPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink, long ellipseWidth, long ellipseHeight);
	virtual ~EllipseVectorPart();

// =============== resembles IMgaNewDecorator
public:
	virtual void			Initialize			(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO);
	virtual CSize			GetPreferredSize	(void) const;

	virtual void			InitializeEx		(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);
};

}; // namespace DecoratorSDK

#endif //__ELLIPSEVECTORPART_H_
