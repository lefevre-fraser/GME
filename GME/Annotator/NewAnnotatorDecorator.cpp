//################################################################################################
//
// New Annotator decorator class
//	NewAnnotatorDecorator.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "NewAnnotatorDecorator.h"
#include "AnnotatorCompositePart.h"


namespace AnnotatorDecor {

//################################################################################################
//
// CLASS : NewAnnotatorDecorator
//
//################################################################################################

NewAnnotatorDecorator::NewAnnotatorDecorator(CComPtr<IMgaElementDecoratorEvents>& eventSink):
	m_part(NULL),
	m_eventSink(eventSink)
{
}

NewAnnotatorDecorator::~NewAnnotatorDecorator()
{
}

void NewAnnotatorDecorator::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	m_part->Initialize(pProject, pPart, pFCO);
}

void NewAnnotatorDecorator::Destroy()
{
	if (m_part) {
		m_part->Destroy();
		delete m_part;
		m_part = NULL;
	}
}

CString NewAnnotatorDecorator::GetMnemonic(void) const
{
	return m_part->GetMnemonic();
}

feature_code NewAnnotatorDecorator::GetFeatures(void) const
{
	return m_part->GetFeatures();
}

void NewAnnotatorDecorator::SetParam(const CString& strName, VARIANT vValue)
{
	m_strName = strName;
	m_vValue = vValue;
}

void NewAnnotatorDecorator::GetParam(const CString& strName, VARIANT* pvValue)
{
	m_part->GetParam(strName, pvValue);
}

void NewAnnotatorDecorator::SetActive(bool bIsActive)
{
	m_part->SetActive(bIsActive);
}

CSize NewAnnotatorDecorator::GetPreferredSize(void) const
{
	return m_part->GetPreferredSize();
}


void NewAnnotatorDecorator::SetLocation(const CRect& location)
{
	m_part->SetLocation(location);
}

CRect NewAnnotatorDecorator::GetLocation(void) const
{
	return m_part->GetLocation();
}

CRect NewAnnotatorDecorator::GetLabelLocation(void) const
{
	return m_part->GetLabelLocation();
}

CRect NewAnnotatorDecorator::GetPortLocation(CComPtr<IMgaFCO>& fco) const
{
	return m_part->GetPortLocation(fco);
}

void NewAnnotatorDecorator::GetPorts(CComPtr<IMgaFCOs>& portFCOs) const
{
	m_part->GetPorts(portFCOs);
}

void NewAnnotatorDecorator::Draw(CDC* pDC, Gdiplus::Graphics* gdip)
{
	m_part->Draw(pDC, gdip);
}

void NewAnnotatorDecorator::SaveState()
{
	m_part->SaveState();
}

// New functions
void NewAnnotatorDecorator::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
										 HWND parentWnd)
{
	AnnotatorCompositePart* annotatorComposite = new AnnotatorCompositePart(NULL, m_eventSink);
	m_part = annotatorComposite;
	m_part->SetParam(m_strName, m_vValue);

	annotatorComposite->InitializeEx(pProject, pPart, pFCO, parentWnd);
}

void NewAnnotatorDecorator::SetSelected(bool bIsSelected)
{
	m_part->SetSelected(bIsSelected);
}

bool NewAnnotatorDecorator::MouseMoved(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMoved(nFlags, point, transformHDC);
}

bool NewAnnotatorDecorator::MouseLeftButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseLeftButtonDown(nFlags, point, transformHDC);
}

bool NewAnnotatorDecorator::MouseLeftButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseLeftButtonUp(nFlags, point, transformHDC);
}

bool NewAnnotatorDecorator::MouseLeftButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseLeftButtonDoubleClick(nFlags, point, transformHDC);
}

bool NewAnnotatorDecorator::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseRightButtonDown(hCtxMenu, nFlags, point, transformHDC);
}

bool NewAnnotatorDecorator::MouseRightButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseRightButtonUp(nFlags, point, transformHDC);
}

bool NewAnnotatorDecorator::MouseRightButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseRightButtonDoubleClick(nFlags, point, transformHDC);
}

bool NewAnnotatorDecorator::MouseMiddleButtonDown(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMiddleButtonDown(nFlags, point, transformHDC);
}

bool NewAnnotatorDecorator::MouseMiddleButtonUp(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMiddleButtonUp(nFlags, point, transformHDC);
}

bool NewAnnotatorDecorator::MouseMiddleButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseMiddleButtonDoubleClick(nFlags, point, transformHDC);
}

bool NewAnnotatorDecorator::MouseWheelTurned(UINT nFlags, short distance, const CPoint& point, HDC transformHDC)
{
	return m_part->MouseWheelTurned(nFlags, distance, point, transformHDC);
}

bool NewAnnotatorDecorator::DragEnter(DROPEFFECT* dropEffect, COleDataObject* pDataObject, DWORD dwKeyState, const CPoint& point, HDC transformHDC)
{
	return m_part->DragEnter(dropEffect, pDataObject, dwKeyState, point, transformHDC);
}

bool NewAnnotatorDecorator::DragOver(DROPEFFECT* dropEffect, COleDataObject* pDataObject, DWORD dwKeyState, const CPoint& point, HDC transformHDC)
{
	return m_part->DragOver(dropEffect, pDataObject, dwKeyState, point, transformHDC);
}

bool NewAnnotatorDecorator::Drop(COleDataObject* pDataObject, DROPEFFECT dropEffect, const CPoint& point, HDC transformHDC)
{
	return m_part->Drop(pDataObject, dropEffect, point, transformHDC);
}

bool NewAnnotatorDecorator::DropFile(HDROP p_hDropInfo, const CPoint& point, HDC transformHDC)
{
	return m_part->DropFile(p_hDropInfo, point, transformHDC);
}

bool NewAnnotatorDecorator::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MenuItemSelected(menuItemId, nFlags, point, transformHDC);
}

bool NewAnnotatorDecorator::OperationCanceledByGME(void)
{
	return m_part->OperationCanceledByGME();
}

}; // namespace AnnotatorDecor
