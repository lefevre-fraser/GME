//################################################################################################
//
// New box decorator class
//	NewBoxDecorator.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "NewBoxDecorator.h"
#include "BoxCompositePart.h"


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
	DecoratorSDK::BoxCompositePart* boxComposite = new DecoratorSDK::BoxCompositePart(NULL, m_eventSink);
	m_part = boxComposite;

	boxComposite->InitializeEx(pProject, pPart, pFCO, parentWnd);
}

void NewBoxDecorator::SetSelected(bool bIsSelected)
{
	m_part->SetSelected(bIsSelected);
}

bool NewBoxDecorator::MouseMoved(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMoved(nFlags, point, transformHDC);
}

bool NewBoxDecorator::MouseLeftButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseLeftButtonDown(nFlags, point, transformHDC);
}

bool NewBoxDecorator::MouseLeftButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseLeftButtonUp(nFlags, point, transformHDC);
}

bool NewBoxDecorator::MouseLeftButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseLeftButtonDoubleClick(nFlags, point, transformHDC);
}

bool NewBoxDecorator::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseRightButtonDown(hCtxMenu, nFlags, point, transformHDC);
}

bool NewBoxDecorator::MouseRightButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseRightButtonUp(nFlags, point, transformHDC);
}

bool NewBoxDecorator::MouseRightButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseRightButtonDoubleClick(nFlags, point, transformHDC);
}

bool NewBoxDecorator::MouseMiddleButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMiddleButtonDown(nFlags, point, transformHDC);
}

bool NewBoxDecorator::MouseMiddleButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMiddleButtonUp(nFlags, point, transformHDC);
}

bool NewBoxDecorator::MouseMiddleButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMiddleButtonDoubleClick(nFlags, point, transformHDC);
}

bool NewBoxDecorator::MouseWheelTurned(UINT nFlags, short distance, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseWheelTurned(nFlags, distance, point, transformHDC);
}

bool NewBoxDecorator::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MenuItemSelected(menuItemId, nFlags, point, transformHDC);
}

bool NewBoxDecorator::OperationCanceledByGME(void)
{
	return m_part->OperationCanceledByGME();
}
