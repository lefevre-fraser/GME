//################################################################################################
//
// PortLabel part class (decorator part)
//	PortLabelPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "PortLabelPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : PortLabelPart
//
//################################################################################################

PortLabelPart::PortLabelPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	LabelPart(pPart, eventSink)
{
	m_bInsideContainer	= true;
	m_eAdjust			= L_WEST;
}

PortLabelPart::~PortLabelPart()
{
}

// New functions
void PortLabelPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
								 HWND parentWnd, PreferenceMap& preferences)
{
	// Determines if port label displayed inside or outside container?
	m_bInsideContainer = preferences[PREF_PORTLABELINSIDE].uValue.bValue;

	// Label Font
	if(m_bInsideContainer) {
		preferences[PREF_LABELFONT] = PreferenceVariant((long) FONT_PORT);
	} else {
		preferences[PREF_LABELFONT] = PreferenceVariant((long) FONT_PORT_OUTSIDE);
	}

	m_eAdjust = preferences[PREF_LABELLOCATION].uValue.eLocation;

	LabelPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

bool PortLabelPart::MouseMoved(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	bool handled = LabelPart::MouseMoved(nFlags, point, transformHDC);

	return handled;
}

bool PortLabelPart::MouseLeftButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	bool handled = LabelPart::MouseLeftButtonDown(nFlags, point, transformHDC);

	return handled;
}

bool PortLabelPart::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	bool handled = LabelPart::MouseRightButtonDown(hCtxMenu, nFlags, point, transformHDC);

	return handled;
}

bool PortLabelPart::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	bool handled = LabelPart::MenuItemSelected(menuItemId, nFlags, point, transformHDC);

	return handled;
}

CPoint PortLabelPart::GetTextPosition(CDC* pDC, Gdiplus::Graphics* gdip) const
{
	int d = (m_eAdjust == L_EAST)? 1 : -1;
	CPoint pt = LabelPart::GetTextPosition(pDC, gdip);
	if (!m_bInsideContainer)
		pt += CPoint(d * 7, -7);

	return pt;
}

CRect PortLabelPart::GetTextLocation(CDC* pDC, Gdiplus::Graphics* gdip) const
{
	CRect r = LabelPart::GetTextLocation(pDC, gdip);

	return r;
}

}; // namespace DecoratorSDK
