//################################################################################################
//
// PortLabel part class (decorator part)
//	PortLabelPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "PortLabelPart.h"


namespace Decorator {

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
	m_offsetPositions	= false;
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
	if (m_bInsideContainer)
		m_offsetPositions = true;

	bool handled = LabelPart::MouseMoved(nFlags, point, transformHDC);

	m_offsetPositions = false;

	return handled;
}

bool PortLabelPart::MouseLeftButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_bInsideContainer)
		m_offsetPositions = true;

	bool handled = LabelPart::MouseLeftButtonDown(nFlags, point, transformHDC);

	m_offsetPositions = false;

	return handled;
}

bool PortLabelPart::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_bInsideContainer)
		m_offsetPositions = true;

	bool handled = LabelPart::MouseRightButtonDown(hCtxMenu, nFlags, point, transformHDC);

	m_offsetPositions = false;

	return handled;
}

bool PortLabelPart::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (m_bInsideContainer)
		m_offsetPositions = true;

	bool handled = LabelPart::MenuItemSelected(menuItemId, nFlags, point, transformHDC);

	m_offsetPositions = false;

	return handled;
}

CPoint PortLabelPart::GetTextPosition(void) const
{
	int d = (m_eAdjust == L_EAST)? 1: -1;
	CPoint pt = LabelPart::GetTextPosition();
	if (!m_bInsideContainer)
		pt += CPoint(d * 7, -7);

	return pt;
}

CRect PortLabelPart::GetLabelLocation(void) const
{
	CRect r = LabelPart::GetLabelLocation();
	if (m_offsetPositions)
		r += m_parentPart->GetParent()->GetLocation().TopLeft();
	return r;
}

}; // namespace Decorator
