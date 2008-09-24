//################################################################################################
//
// Decorator parts base class
//	PartBase.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "PartBase.h"
#include "../DecoratorExceptions.h"


namespace Decorator {

//################################################################################################
//
// CLASS : PartBase
//
//################################################################################################

PartBase::PartBase(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	m_parentPart	(pPart),
	m_eventSink		(eventSink),
	m_parentWnd		(NULL),
	m_viewDC		(NULL),
	m_bHasViolation	(false),
	m_bActive		(true),
	m_bSelected		(false),
	m_lBorderWidth	(0),
	m_bReferenced	(false)
{
}

PartBase::~PartBase()
{
	if (m_eventSink)
		m_eventSink.Release();
	// TODO: destroy more COM objects
}

void PartBase::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	m_spProject	= pProject;
	m_spPart	= pPart;
	m_spFCO		= pFCO;

	if (m_spFCO) {
		COMTHROW(m_spFCO->get_ObjType(&m_eType));
	} else {
		CComPtr<IMgaMetaRole> spRole;
		COMTHROW(m_spPart->get_Role(&spRole));

		CComPtr<IMgaMetaFCO> spMetaFCO;
		COMTHROW(spRole->get_Kind(&spMetaFCO));

		COMTHROW(spMetaFCO->get_ObjType(&m_eType));
	}

	m_bHasViolation	= false;
	m_bActive		= true;
	m_bSelected		= false;
	m_lBorderWidth	= 0;
	m_bReferenced	= false;
}

void PartBase::Destroy(void)
{
}

CString PartBase::GetMnemonic(void) const
{
	return CString();
}

feature_code PartBase::GetFeatures(void) const
{
	return 0;
}

void PartBase::SetParam(const CString& strName, VARIANT vValue)
{
}

bool PartBase::GetParam(const CString& strName, VARIANT* pvValue)
{
	return false;
}

void PartBase::SetActive(bool bIsActive)
{
	m_bActive = bIsActive;
}

CSize PartBase::GetPreferredSize(void) const
{
	return CSize(0, 0);	// empty
}

void PartBase::SetLocation(const CRect& location)
{
	SetBoxLocation(location);
}

CRect PartBase::GetLocation(void) const
{
	return GetBoxLocation(true);
}

CRect PartBase::GetLabelLocation(void) const
{
	return CRect();	// empty
}

CRect PartBase::GetPortLocation(CComPtr<IMgaFCO>& pFCO) const
{
	return CRect();	// empty
}

bool PartBase::GetPorts(CComPtr<IMgaFCOs>& portFCOs) const
{
	return false;
}

void PartBase::Draw(CDC* pDC)
{
	// empty default implementation
}

void PartBase::SaveState(void)
{
	// empty default implementation
}

void PartBase::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
							HWND parentWnd, PreferenceMap& preferences)
{
	m_parentWnd = parentWnd;

	// HasViolations
	if (m_spFCO) {
		PreferenceMap::iterator it = preferences.find(PREF_VIOLATED);
		if (it != preferences.end())
			m_bHasViolation = it->second.uValue.bValue;
		else
			m_bHasViolation = getFacilities().getPreferenceStatus(m_spFCO, PREF_VIOLATED) == PS_HERE;
	}

	m_lBorderWidth = 0;

	Initialize(pProject, pPart, pFCO);
}

void PartBase::SetSelected(bool bIsSelected)
{
	m_bSelected = bIsSelected;
}

bool PartBase::MouseMoved(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return false;
}

bool PartBase::MouseLeftButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return false;
}

bool PartBase::MouseLeftButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return false;
}

bool PartBase::MouseLeftButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return false;
}

bool PartBase::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return false;
}

bool PartBase::MouseRightButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return false;
}

bool PartBase::MouseRightButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return false;
}

bool PartBase::MouseMiddleButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return false;
}

bool PartBase::MouseMiddleButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return false;
}

bool PartBase::MouseMiddleButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return false;
}

bool PartBase::MouseWheelTurned(UINT nFlags, short distance, const CPoint& point, HDC transformHDC)
{
	return false;
}

bool PartBase::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return false;
}

bool PartBase::OperationCanceledByGME(void)
{
	return false;
}

void PartBase::Refresh(void)
{
	m_eventSink->Refresh();
}

void PartBase::CursorChanged(long newCursorID)
{
	m_eventSink->CursorChanged(newCursorID);
}

void PartBase::CursorRestored(void)
{
	m_eventSink->CursorRestored();
}

void PartBase::OperationCanceledByDecorator(void)
{
	m_eventSink->OperationCanceled();
}

void PartBase::TitleEditingStarted(CRect& location)
{
	m_eventSink->TitleEditingStarted(location.left, location.top, location.right, location.bottom);
}

void PartBase::TitleEditingFinished(CRect& location)
{
	m_eventSink->TitleEditingFinished(location.left, location.top, location.right, location.bottom);
}

void PartBase::TitleChanged(CString& newTitle)
{
	CComBSTR newTitleBStr(newTitle);
	m_eventSink->TitleChanged(newTitleBStr);
}

void PartBase::TitleMovingStarted(UINT nType, CRect& location)
{
	m_eventSink->TitleMovingStarted(nType, location.left, location.top, location.right, location.bottom);
}

void PartBase::TitleMoving(UINT nSide, CRect& location)
{
	m_eventSink->TitleMoving(nSide, location.left, location.top, location.right, location.bottom);
}

void PartBase::TitleMovingFinished(UINT nType, CRect& location)
{
	m_eventSink->TitleMovingFinished(nType, location.left, location.top, location.right, location.bottom);
}

void PartBase::TitleMoved(UINT nType, CPoint& point)
{
	m_eventSink->TitleMoved(nType, point.x, point.y);
}

void PartBase::TitleResizingStarted(UINT nType, CRect& location)
{
	m_eventSink->TitleResizingStarted(nType, location.left, location.top, location.right, location.bottom);
}

void PartBase::TitleResizing(UINT nSide, CRect& location)
{
	m_eventSink->TitleResizing(nSide, location.left, location.top, location.right, location.bottom);
}

void PartBase::TitleResizingFinished(UINT nType, CRect& location)
{
	m_eventSink->TitleResizingFinished(nType, location.left, location.top, location.right, location.bottom);
}

void PartBase::TitleResized(UINT nType, CSize& size)
{
	m_eventSink->TitleResized(nType, size.cx, size.cy);
}

void PartBase::WindowMovingStarted(UINT nType, CRect& location)
{
	m_eventSink->WindowMovingStarted(nType, location.left, location.top, location.right, location.bottom);
}

void PartBase::WindowMoving(UINT nSide, CRect& location)
{
	m_eventSink->WindowMoving(nSide, location.left, location.top, location.right, location.bottom);
}

void PartBase::WindowMovingFinished(UINT nType, CRect& location)
{
	m_eventSink->WindowMovingFinished(nType, location.left, location.top, location.right, location.bottom);
}

void PartBase::WindowMoved(UINT nType, CPoint& point)
{
	m_eventSink->WindowMoved(nType, point.x, point.y);
}

void PartBase::WindowResizingStarted(UINT nType, CRect& location)
{
	m_eventSink->WindowResizingStarted(nType, location.left, location.top, location.right, location.bottom);
}

void PartBase::WindowResizing(UINT nSide, CRect& location)
{
	m_eventSink->WindowResizing(nSide, location.left, location.top, location.right, location.bottom);
}

void PartBase::WindowResizingFinished(UINT nType, CRect& location)
{
	m_eventSink->WindowResizingFinished(nType, location.left, location.top, location.right, location.bottom);
}

void PartBase::WindowResized(UINT nType, CSize& size)
{
	m_eventSink->WindowResized(nType, size.cx, size.cy);
}

ECoordRefPoint PartBase::GetAlignment(ELocation loc) const
{
	switch (loc) {
		case L_NORTH:
		case L_CENTER:
		case L_SOUTH:
			return CRP_CENTER;
		case L_NORTHEAST:
		case L_EAST:
		case L_SOUTHEAST:
			return CRP_BEGIN;
		default:
			return CRP_END;
	}
}

long PartBase::GetBorderWidth(bool bActive) const
{
	long lBorderWidth = m_lBorderWidth;
	if ((m_bActive || bActive) && m_bHasViolation)
		lBorderWidth += WIDTH_BORDERVIOLATION + 1;
	return lBorderWidth;
}

void PartBase::SetBoxLocation(const CRect& cRect)
{
	m_Rect = cRect;
}

CRect PartBase::GetBoxLocation(bool bWithBorder) const
{
	if (bWithBorder)
		return m_Rect;
	CRect cRect = m_Rect;
	cRect.DeflateRect(GetBorderWidth(false), GetBorderWidth(false));
	return cRect;
}

void PartBase::SetReferenced(bool referenced)
{
	m_bReferenced = referenced;
}

};	// namespace Decorator
