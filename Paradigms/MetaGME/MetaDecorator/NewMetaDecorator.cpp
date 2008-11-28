//################################################################################################
//
// New Meta decorator class
//	NewMetaDecorator.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "NewMetaDecorator.h"
#include "MetaCompositePart.h"


namespace MetaDecor {

//################################################################################################
//
// CLASS : NewMetaDecorator
//
//################################################################################################

NewMetaDecorator::NewMetaDecorator(CComPtr<IMgaNewDecoratorEvents> eventSink):
	m_part(NULL),
	m_eventSink(eventSink)
{
}

NewMetaDecorator::~NewMetaDecorator()
{
}

void NewMetaDecorator::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	m_part->Initialize(pProject, pPart, pFCO);
}

void NewMetaDecorator::Destroy()
{
	if (m_part) {
		m_part->Destroy();
		delete m_part;
		m_part = NULL;
	}
}

CString NewMetaDecorator::GetMnemonic(void) const
{
	return m_part->GetMnemonic();
}

feature_code NewMetaDecorator::GetFeatures(void) const
{
	return m_part->GetFeatures();
}

void NewMetaDecorator::SetParam(const CString& strName, VARIANT vValue)
{
	m_part->SetParam(strName, vValue);
}

void NewMetaDecorator::GetParam(const CString& strName, VARIANT* pvValue)
{
	m_part->GetParam(strName, pvValue);
}

void NewMetaDecorator::SetActive(bool bIsActive)
{
	m_part->SetActive(bIsActive);
}

CSize NewMetaDecorator::GetPreferredSize(void) const
{
	return m_part->GetPreferredSize();
}


void NewMetaDecorator::SetLocation(const CRect& location)
{
	m_part->SetLocation(location);
}

CRect NewMetaDecorator::GetLocation(void) const
{
	return m_part->GetLocation();
}

CRect NewMetaDecorator::GetLabelLocation(void) const
{
	return m_part->GetLabelLocation();
}

CRect NewMetaDecorator::GetPortLocation(CComPtr<IMgaFCO>& fco) const
{
	return m_part->GetPortLocation(fco);
}

void NewMetaDecorator::GetPorts(CComPtr<IMgaFCOs>& portFCOs) const
{
	m_part->GetPorts(portFCOs);
}

void NewMetaDecorator::Draw(CDC* pDC, Gdiplus::Graphics* gdip)
{
	m_part->Draw(pDC, gdip);
}

void NewMetaDecorator::SaveState()
{
	m_part->SaveState();
}

// New functions
void NewMetaDecorator::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									HWND parentWnd)
{
	MetaCompositePart* MetaComposite = new MetaCompositePart(NULL, m_eventSink);
	m_part = MetaComposite;

	MetaComposite->InitializeEx(pProject, pPart, pFCO, parentWnd);
}

void NewMetaDecorator::SetSelected(bool bIsSelected)
{
	m_part->SetSelected(bIsSelected);
}

bool NewMetaDecorator::MouseMoved(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMoved(nFlags, point, transformHDC);
}

bool NewMetaDecorator::MouseLeftButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseLeftButtonDown(nFlags, point, transformHDC);
}

bool NewMetaDecorator::MouseLeftButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseLeftButtonUp(nFlags, point, transformHDC);
}

bool NewMetaDecorator::MouseLeftButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseLeftButtonDoubleClick(nFlags, point, transformHDC);
}

bool NewMetaDecorator::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseRightButtonDown(hCtxMenu, nFlags, point, transformHDC);
}

bool NewMetaDecorator::MouseRightButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseRightButtonUp(nFlags, point, transformHDC);
}

bool NewMetaDecorator::MouseRightButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseRightButtonDoubleClick(nFlags, point, transformHDC);
}

bool NewMetaDecorator::MouseMiddleButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMiddleButtonDown(nFlags, point, transformHDC);
}

bool NewMetaDecorator::MouseMiddleButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMiddleButtonUp(nFlags, point, transformHDC);
}

bool NewMetaDecorator::MouseMiddleButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMiddleButtonDoubleClick(nFlags, point, transformHDC);
}

bool NewMetaDecorator::MouseWheelTurned(UINT nFlags, short distance, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseWheelTurned(nFlags, distance, point, transformHDC);
}

bool NewMetaDecorator::DragEnter(DROPEFFECT* dropEffect, COleDataObject* pDataObject, DWORD dwKeyState, const CPoint& point, HDC transformHDC)
{
	return m_part->DragEnter(dropEffect, pDataObject, dwKeyState, point, transformHDC);
}

bool NewMetaDecorator::DragLeave(void)
{
	return m_part->DragLeave();
}

bool NewMetaDecorator::DragOver(DROPEFFECT* dropEffect, COleDataObject* pDataObject, DWORD dwKeyState, const CPoint& point, HDC transformHDC)
{
	return m_part->DragOver(dropEffect, pDataObject, dwKeyState, point, transformHDC);
}

bool NewMetaDecorator::Drop(COleDataObject* pDataObject, DROPEFFECT dropEffect, const CPoint& point, HDC transformHDC)
{
	return m_part->Drop(pDataObject, dropEffect, point, transformHDC);
}

bool NewMetaDecorator::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MenuItemSelected(menuItemId, nFlags, point, transformHDC);
}

bool NewMetaDecorator::OperationCanceledByGME(void)
{
	return m_part->OperationCanceledByGME();
}

}; // namespace MetaDecor
