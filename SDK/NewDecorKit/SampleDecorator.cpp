//################################################################################################
//
// Sample decorator class
//	SampleDecorator.cpp
// This class represents the C++ side of the decorator COM connection layer
// This is still just a relay class like teh COM/ATL SampleDecoratorImpl.h,cpp,
// the meat should go into the composite part or into the parts in the composite part
//
//################################################################################################

#include "StdAfx.h"
#include "SampleDecorator.h"
#include "SampleCompositePart.h"


namespace SampleDecor {

//################################################################################################
//
// CLASS : SampleDecorator
//
//################################################################################################

SampleDecorator::SampleDecorator(CComPtr<IMgaNewDecoratorEvents>& eventSink):
	m_part(NULL),
	m_eventSink(eventSink)
{
}

SampleDecorator::~SampleDecorator()
{
}

void SampleDecorator::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	m_part->Initialize(pProject, pPart, pFCO);
}

void SampleDecorator::Destroy()
{
	if (m_part) {
		m_part->Destroy();
		delete m_part;
		m_part = NULL;
	}
}

CString SampleDecorator::GetMnemonic(void) const
{
	return m_part->GetMnemonic();
}

feature_code SampleDecorator::GetFeatures(void) const
{
	return m_part->GetFeatures();
}

void SampleDecorator::SetParam(const CString& strName, VARIANT vValue)
{
	m_part->SetParam(strName, vValue);
}

void SampleDecorator::GetParam(const CString& strName, VARIANT* pvValue)
{
	m_part->GetParam(strName, pvValue);
}

void SampleDecorator::SetActive(bool bIsActive)
{
	m_part->SetActive(bIsActive);
}

CSize SampleDecorator::GetPreferredSize(void) const
{
	return m_part->GetPreferredSize();
}


void SampleDecorator::SetLocation(const CRect& location)
{
	m_part->SetLocation(location);
}

CRect SampleDecorator::GetLocation(void) const
{
	return m_part->GetLocation();
}

CRect SampleDecorator::GetLabelLocation(void) const
{
	return m_part->GetLabelLocation();
}

CRect SampleDecorator::GetPortLocation(CComPtr<IMgaFCO>& fco) const
{
	return m_part->GetPortLocation(fco);
}

void SampleDecorator::GetPorts(CComPtr<IMgaFCOs>& portFCOs) const
{
	m_part->GetPorts(portFCOs);
}

void SampleDecorator::Draw(CDC* pDC, Gdiplus::Graphics* gdip)
{
	m_part->Draw(pDC, gdip);
}

void SampleDecorator::SaveState()
{
	m_part->SaveState();
}

// New functions
void SampleDecorator::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
								   HWND parentWnd)
{
	SampleCompositePart* sampleComposite = new SampleCompositePart(NULL, m_eventSink);
	m_part = sampleComposite;

	sampleComposite->InitializeEx(pProject, pPart, pFCO, parentWnd);
}

void SampleDecorator::SetSelected(bool bIsSelected)
{
	m_part->SetSelected(bIsSelected);
}

bool SampleDecorator::MouseMoved(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMoved(nFlags, point, transformHDC);
}

bool SampleDecorator::MouseLeftButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseLeftButtonDown(nFlags, point, transformHDC);
}

bool SampleDecorator::MouseLeftButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseLeftButtonUp(nFlags, point, transformHDC);
}

bool SampleDecorator::MouseLeftButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseLeftButtonDoubleClick(nFlags, point, transformHDC);
}

bool SampleDecorator::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseRightButtonDown(hCtxMenu, nFlags, point, transformHDC);
}

bool SampleDecorator::MouseRightButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseRightButtonUp(nFlags, point, transformHDC);
}

bool SampleDecorator::MouseRightButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseRightButtonDoubleClick(nFlags, point, transformHDC);
}

bool SampleDecorator::MouseMiddleButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMiddleButtonDown(nFlags, point, transformHDC);
}

bool SampleDecorator::MouseMiddleButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMiddleButtonUp(nFlags, point, transformHDC);
}

bool SampleDecorator::MouseMiddleButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMiddleButtonDoubleClick(nFlags, point, transformHDC);
}

bool SampleDecorator::MouseWheelTurned(UINT nFlags, short distance, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseWheelTurned(nFlags, distance, point, transformHDC);
}

bool SampleDecorator::DragEnter(DROPEFFECT* dropEffect, COleDataObject* pDataObject, DWORD dwKeyState, const CPoint& point, HDC transformHDC)
{
	return m_part->DragEnter(dropEffect, pDataObject, dwKeyState, point, transformHDC);
}

bool SampleDecorator::DragOver(DROPEFFECT* dropEffect, COleDataObject* pDataObject, DWORD dwKeyState, const CPoint& point, HDC transformHDC)
{
	return m_part->DragOver(dropEffect, pDataObject, dwKeyState, point, transformHDC);
}

bool SampleDecorator::Drop(COleDataObject* pDataObject, DROPEFFECT dropEffect, const CPoint& point, HDC transformHDC)
{
	return m_part->Drop(pDataObject, dropEffect, point, transformHDC);
}

bool SampleDecorator::DropFile(HDROP p_hDropInfo, const CPoint& point, HDC transformHDC)
{
	return m_part->DropFile(p_hDropInfo, point, transformHDC);
}

bool SampleDecorator::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MenuItemSelected(menuItemId, nFlags, point, transformHDC);
}

bool SampleDecorator::OperationCanceledByGME(void)
{
	return m_part->OperationCanceledByGME();
}

}; // namespace SampleDecor
