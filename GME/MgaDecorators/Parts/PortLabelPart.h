//################################################################################################
//
// PortLabel part class (decorator part)
//	PortLabelPart.h
//
//################################################################################################

#ifndef __PORTLABELPART_H_
#define __PORTLABELPART_H_


#include "../StdAfx.h"
#include "LabelPart.h"


namespace Decorator {

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
	bool			m_offsetPositions;

public:
	PortLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink);
	virtual ~PortLabelPart();

	virtual void	InitializeEx				(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart,
												 CComPtr<IMgaFCO>& pFCO, HWND parentWnd, PreferenceMap& preferences);
	virtual bool	MouseMoved					(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);
	virtual bool	MouseLeftButtonDown			(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);
	virtual bool	MouseRightButtonDown		(HMENU hCtxMenu, UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);
	virtual bool	MenuItemSelected			(UINT menuItemId, UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent);

	virtual CPoint	GetTextPosition				(void) const;
	virtual CRect	GetLabelLocation			(void) const;
};

}; // namespace Decorator

#endif //__PORTLABELPART_H_
