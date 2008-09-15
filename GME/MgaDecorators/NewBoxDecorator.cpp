//################################################################################################
//
// New box decorator class
//	NewBoxDecorator.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "NewBoxDecorator.h"
#include "Parts/BoxCompositePart.h"


namespace Decorator {

//################################################################################################
//
// CLASS : NewBoxDecorator
//
//################################################################################################

NewBoxDecorator::NewBoxDecorator(CComPtr<IMgaNewDecoratorEvents> eventSink):
	m_part(NULL),
	m_eventSink(eventSink)
{
}

NewBoxDecorator::~NewBoxDecorator()
{
}

void NewBoxDecorator::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	m_part->Initialize(pProject, pPart, pFCO);
}

void NewBoxDecorator::Destroy()
{
	if (m_part) {
		m_part->Destroy();
		delete m_part;
		m_part = NULL;
	}
}

CString NewBoxDecorator::GetMnemonic(void) const
{
	return m_part->GetMnemonic();
}

feature_code NewBoxDecorator::GetFeatures(void) const
{
	return m_part->GetFeatures();
}

void NewBoxDecorator::SetParam(const CString& strName, VARIANT vValue)
{
	m_part->SetParam(strName, vValue);
}

void NewBoxDecorator::GetParam(const CString& strName, VARIANT* pvValue)
{
	m_part->GetParam(strName, pvValue);
}

void NewBoxDecorator::SetActive(bool bIsActive)
{
	m_part->SetActive(bIsActive);
}

CSize NewBoxDecorator::GetPreferredSize(void) const
{
	return m_part->GetPreferredSize();
}


void NewBoxDecorator::SetLocation(const CRect& location)
{
	m_part->SetLocation(location);
}

CRect NewBoxDecorator::GetLocation(void) const
{
	return m_part->GetLocation();
}

CRect NewBoxDecorator::GetLabelLocation(void) const
{
	return m_part->GetLabelLocation();
}

CRect NewBoxDecorator::GetPortLocation(CComPtr<IMgaFCO>& fco) const
{
	return m_part->GetPortLocation(fco);
}

void NewBoxDecorator::GetPorts(CComPtr<IMgaFCOs>& portFCOs) const
{
	m_part->GetPorts(portFCOs);
}

void NewBoxDecorator::Draw(CDC* pDC)
{
	m_part->Draw(pDC);
}

void NewBoxDecorator::SaveState()
{
	m_part->SaveState();
}

// New functions
void NewBoxDecorator::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									HWND parentWnd)
{
	BoxCompositePart* boxComposite = new BoxCompositePart(NULL, m_eventSink);
	m_part = boxComposite;

	boxComposite->InitializeEx(pProject, pPart, pFCO, parentWnd);
}

void NewBoxDecorator::SetSelected(bool bIsSelected)
{
	m_part->SetSelected(bIsSelected);
}

bool NewBoxDecorator::MouseMoved(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent)
{
	return m_part->MouseMoved(nFlags, lpoint, dpoint, zoomPercent);
}

bool NewBoxDecorator::MouseLeftButtonDown(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent)
{
	return m_part->MouseLeftButtonDown(nFlags, lpoint, dpoint, zoomPercent);
}

bool NewBoxDecorator::MouseLeftButtonUp(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent)
{
	return m_part->MouseLeftButtonUp(nFlags, lpoint, dpoint, zoomPercent);
}

bool NewBoxDecorator::MouseLeftButtonDoubleClick(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent)
{
	return m_part->MouseLeftButtonDoubleClick(nFlags, lpoint, dpoint, zoomPercent);
}

bool NewBoxDecorator::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent)
{
	return m_part->MouseRightButtonDown(hCtxMenu, nFlags, lpoint, dpoint, zoomPercent);
}

bool NewBoxDecorator::MouseRightButtonUp(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent)
{
	return m_part->MouseRightButtonUp(nFlags, lpoint, dpoint, zoomPercent);
}

bool NewBoxDecorator::MouseRightButtonDoubleClick(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent)
{
	return m_part->MouseRightButtonDoubleClick(nFlags, lpoint, dpoint, zoomPercent);
}

bool NewBoxDecorator::MouseMiddleButtonDown(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent)
{
	return m_part->MouseMiddleButtonDown(nFlags, lpoint, dpoint, zoomPercent);
}

bool NewBoxDecorator::MouseMiddleButtonUp(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent)
{
	return m_part->MouseMiddleButtonUp(nFlags, lpoint, dpoint, zoomPercent);
}

bool NewBoxDecorator::MouseMiddleButtonDoubleClick(UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent)
{
	return m_part->MouseMiddleButtonDoubleClick(nFlags, lpoint, dpoint, zoomPercent);
}

bool NewBoxDecorator::MouseWheelTurned(UINT nFlags, short distance, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent)
{
	return m_part->MouseWheelTurned(nFlags, distance, lpoint, dpoint, zoomPercent);
}

bool NewBoxDecorator::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& lpoint, const CPoint& dpoint, long zoomPercent)
{
	return m_part->MenuItemSelected(menuItemId, nFlags, lpoint, dpoint, zoomPercent);
}

bool NewBoxDecorator::OperationCanceledByGME(void)
{
	return m_part->OperationCanceledByGME();
}
/*
void NewBoxDecorator::Refresh(void)
{
	m_eventSink->Refresh();
}

void NewBoxDecorator::CursorChanged(long newCursorID)
{
	m_eventSink->CursorChanged(newCursorID);
}

void NewBoxDecorator::CursorRestored(void)
{
	m_eventSink->CursorRestored();
}

void NewBoxDecorator::OperationCanceledByDecorator(void)
{
	m_eventSink->OperationCanceled();
}

void NewBoxDecorator::TitleEditingStarted(CRect& location)
{
	m_eventSink->TitleEditingStarted(location.left, location.top, location.right, location.bottom);
}

void NewBoxDecorator::TitleEditingFinished(CRect& location)
{
	m_eventSink->TitleEditingFinished(location.left, location.top, location.right, location.bottom);
}

void NewBoxDecorator::TitleChanged(CString& newTitle)
{
	CComBSTR newTitleBStr(newTitle);
	m_eventSink->TitleChanged(newTitleBStr);
}

void NewBoxDecorator::TitleMovingStarted(UINT nType, CRect& location)
{
	m_eventSink->TitleMovingStarted(nType, location.left, location.top, location.right, location.bottom);
}

void NewBoxDecorator::TitleMoving(UINT nSide, CRect& location)
{
	m_eventSink->TitleMoving(nSide, location.left, location.top, location.right, location.bottom);
}

void NewBoxDecorator::TitleMovingFinished(UINT nType, CRect& location)
{
	m_eventSink->TitleMovingFinished(nType, location.left, location.top, location.right, location.bottom);
}

void NewBoxDecorator::TitleMoved(UINT nType, CPoint& point)
{
	m_eventSink->TitleMoved(nType, point.x, point.y);
}

void NewBoxDecorator::TitleResizingStarted(UINT nType, CRect& location)
{
	m_eventSink->TitleResizingStarted(nType, location.left, location.top, location.right, location.bottom);
}

void NewBoxDecorator::TitleResizing(UINT nSide, CRect& location)
{
	m_eventSink->TitleResizing(nSide, location.left, location.top, location.right, location.bottom);
}

void NewBoxDecorator::TitleResizingFinished(UINT nType, CRect& location)
{
	m_eventSink->TitleResizingFinished(nType, location.left, location.top, location.right, location.bottom);
}

void NewBoxDecorator::TitleResized(UINT nType, CSize& size)
{
	m_eventSink->TitleResized(nType, size.cx, size.cy);
}

void NewBoxDecorator::WindowMovingStarted(UINT nType, CRect& location)
{
	m_eventSink->WindowMovingStarted(nType, location.left, location.top, location.right, location.bottom);
}

void NewBoxDecorator::WindowMoving(UINT nSide, CRect& location)
{
	m_eventSink->WindowMoving(nSide, location.left, location.top, location.right, location.bottom);
}

void NewBoxDecorator::WindowMovingFinished(UINT nType, CRect& location)
{
	m_eventSink->WindowMovingFinished(nType, location.left, location.top, location.right, location.bottom);
}

void NewBoxDecorator::WindowMoved(UINT nType, CPoint& point)
{
	m_eventSink->WindowMoved(nType, point.x, point.y);
}

void NewBoxDecorator::WindowResizingStarted(UINT nType, CRect& location)
{
	m_eventSink->WindowResizingStarted(nType, location.left, location.top, location.right, location.bottom);
}

void NewBoxDecorator::WindowResizing(UINT nSide, CRect& location)
{
	m_eventSink->WindowResizing(nSide, location.left, location.top, location.right, location.bottom);
}

void NewBoxDecorator::WindowResizingFinished(UINT nType, CRect& location)
{
	m_eventSink->WindowResizingFinished(nType, location.left, location.top, location.right, location.bottom);
}

void NewBoxDecorator::WindowResized(UINT nType, CSize& size)
{
	m_eventSink->WindowResized(nType, size.cx, size.cy);
}
*/
}; // namespace Decorator
