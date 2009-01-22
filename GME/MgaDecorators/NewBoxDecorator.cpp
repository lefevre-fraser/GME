//################################################################################################
//
// New box decorator class
//	NewBoxDecorator.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "NewBoxDecorator.h"
#include "BoxCompositePart.h"
#include <afxole.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _DEBUG
#define TRYDRAGNDROP
#endif

//################################################################################################
//
// CLASS : NewBoxDecorator
//
//################################################################################################

NewBoxDecorator::NewBoxDecorator(CComPtr<IMgaNewDecoratorEvents>& eventSink):
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
	if (m_eventSink)
		m_eventSink.Release();
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

void NewBoxDecorator::Draw(CDC* pDC, Gdiplus::Graphics* gdip)
{
	m_part->Draw(pDC, gdip);
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

bool NewBoxDecorator::DragEnter(DROPEFFECT* dropEffect, COleDataObject* pDataObject, DWORD dwKeyState, const CPoint& point, HDC transformHDC)
{
#ifdef TRYDRAGNDROP
//	pDataObject->BeginEnumFormats();
//	FORMATETC fi;
//	TRACE0("DragEnter:\n");
//	while (pDataObject->GetNextFormat(&fi) == TRUE) {
//		TRACE("\tcfFormat %d dwAspect %lu lindex %ld tymed %lu\n", fi.cfFormat, fi.dwAspect, fi.lindex, fi.tymed);
//	}
//	return DROPEFFECT_NONE;
	if (pDataObject->IsDataAvailable(CF_HDROP)) {
		*dropEffect = DROPEFFECT_COPY;
		return true;
	}
#endif
	return m_part->DragEnter(dropEffect, pDataObject, dwKeyState, point, transformHDC);
}

bool NewBoxDecorator::DragOver(DROPEFFECT* dropEffect, COleDataObject* pDataObject, DWORD dwKeyState, const CPoint& point, HDC transformHDC)
{
#ifdef TRYDRAGNDROP
	if (pDataObject->IsDataAvailable(CF_HDROP)) {
		*dropEffect = DROPEFFECT_COPY;
		return true;
	}
#endif
	return m_part->DragOver(dropEffect, pDataObject, dwKeyState, point, transformHDC);
}

bool NewBoxDecorator::Drop(COleDataObject* pDataObject, DROPEFFECT dropEffect, const CPoint& point, HDC transformHDC)
{
#ifdef TRYDRAGNDROP
	if (pDataObject->IsDataAvailable(CF_HDROP) && dropEffect == DROPEFFECT_COPY) {
		STGMEDIUM medium;
		medium.tymed = TYMED_HGLOBAL;
		pDataObject->GetData(CF_HDROP, &medium);
		return DropFile((HDROP)medium.hGlobal, point, transformHDC);
	}
#endif
	return m_part->Drop(pDataObject, dropEffect, point, transformHDC);
}

bool NewBoxDecorator::DropFile(HDROP p_hDropInfo, const CPoint& point, HDC transformHDC)
{
#ifdef TRYDRAGNDROP
	UINT nFiles = DragQueryFile(p_hDropInfo, 0xFFFFFFFF, NULL, 0);
	if (nFiles < 1)
		return false;

	for (UINT iF = 0; iF < nFiles; ++iF) {
		TCHAR szFileName[_MAX_PATH];
		UINT res = DragQueryFile(p_hDropInfo, iF, szFileName, _MAX_PATH);
		if (res > 0) {
			bool is_dir = false; 
			struct _stat fstatus;
			if (0 == _tstat(szFileName, &fstatus))
				is_dir = (fstatus.st_mode & _S_IFDIR) == _S_IFDIR;

			CString conn(szFileName);
			if (!is_dir && conn.Right(4).CompareNoCase(".txt") == 0) {
				CFile txtFile(conn, CFile::modeRead);
				char pbufRead[100];
				txtFile.Read(pbufRead, sizeof(pbufRead));
				CString msg;
				AfxMessageBox("Decorator drop: '" + conn + "' first 100 bytes: " + pbufRead + ".");
				return true;
			} else {
				AfxMessageBox("Decorator drop: '.txt' files may be dropped only. Can't open file: " + conn + "!");
			}
		} else {
			AfxMessageBox("Decorator drop: Can't inquire file information!");
		}
	}
#endif
	return m_part->DropFile(p_hDropInfo, point, transformHDC);
}

bool NewBoxDecorator::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	return m_part->MenuItemSelected(menuItemId, nFlags, point, transformHDC);
}

bool NewBoxDecorator::OperationCanceledByGME(void)
{
	return m_part->OperationCanceledByGME();
}
