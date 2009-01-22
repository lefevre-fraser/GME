//################################################################################################
//
// PortLabel part class (decorator part)
//	PortLabelPart.h
//
//################################################################################################

#ifndef __PORTLABELPART_H_
#define __PORTLABELPART_H_


#include "StdAfx.h"
#include "LabelPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : PortLabelPart
//
//################################################################################################

class PortLabelPart: public LabelPart
{
protected:
	bool			m_bInsideContainer;
	ELocation		m_eAdjust;

public:
	PortLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents>& eventSink);
	virtual ~PortLabelPart();

	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);
	virtual bool	MouseMoved					(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseLeftButtonDown			(UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MouseRightButtonDown		(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC);
	virtual bool	MenuItemSelected			(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC);

	virtual CPoint	GetTextPosition				(CDC* pDC, Gdiplus::Graphics* gdip) const;
	virtual CRect	GetTextLocation				(CDC* pDC, Gdiplus::Graphics* gdip) const;

	ELocation		GetLocationAdjust			(void) const { return m_eAdjust; };
};

}; // namespace DecoratorSDK

#endif //__PORTLABELPART_H_
