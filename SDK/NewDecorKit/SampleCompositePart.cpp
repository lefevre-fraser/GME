//################################################################################################
//
// Sample decorator composite part class
//	SampleCompositePart.cpp
// Contains the specific decorator parts which compose the final decorator
//
//################################################################################################

#include "StdAfx.h"
#define __Meta_h__
#define __Mga_h__
#define __MgaDecorator_h__
#include "DecoratorLib.h"
#include <sys/types.h>
#include <sys/stat.h>
#include "GMEOLEData.h"
#include "SampleCompositePart.h"
#include "DiamondVectorPart.h"
#include "TypeableLabelPart.h"

#include "DecoratorExceptions.h"

static const unsigned int	CTX_MENU_ID_SAMPLE		= DECORATOR_CTX_MENU_MINID + 100;
static const char*			CTX_MENU_STR_SAMPLE		= "Sample Decorator Ctx Menu Item";


namespace SampleDecor {

//################################################################################################
//
// CLASS : SampleCompositePart
//
//################################################################################################

SampleCompositePart::SampleCompositePart(DecoratorSDK::PartBase* pPart, CComPtr<IMgaNewDecoratorEvents>& eventSink):
	ObjectAndTextPart(pPart, eventSink)
{
}

SampleCompositePart::~SampleCompositePart()
{
}

CRect SampleCompositePart::GetPortLocation(CComPtr<IMgaFCO>& fco) const
{
	throw PortNotFoundException();
}

CRect SampleCompositePart::GetLabelLocation(void) const
{
	HRESULT retVal = S_OK;
	std::vector<PartBase*>::const_iterator ii = m_compositeParts.begin();
	if (m_compositeParts.size() > 1)
		++ii;	// we expect that the second part is the label if there's more than one part
	if (ii != m_compositeParts.end()) {
		try {
			return (*ii)->GetLabelLocation();
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}

	throw DecoratorException((DecoratorExceptionCode)retVal);
}

// New functions
void SampleCompositePart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									   HWND parentWnd, DecoratorSDK::PreferenceMap& preferences)
{
	//
	// TODO: Add needed parts to the composite
	//		 This time it is the desired vectorial shape plus a versatile label part
	//
	try {
		if (pProject) {
			AddObjectPart(new DecoratorSDK::DiamondVectorPart(this, m_eventSink,
															  static_cast<long> (24 * 2),
															  static_cast<long> (24)));
			AddTextPart(new DecoratorSDK::TypeableLabelPart(this, m_eventSink));
		}
	}
	catch (hresult_exception& e) {
		throw DecoratorException((DecoratorExceptionCode)e.hr);
	}

	CompositePart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

void SampleCompositePart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
									   HWND parentWnd)
{
	//
	// Initialize the Decorator utilities facility framework
	//
	DecoratorSDK::getFacilities().loadPathes(pProject, true);

	DecoratorSDK::PreferenceMap preferencesMap;
	InitializeEx(pProject, pPart, pFCO, parentWnd, preferencesMap);
}

bool SampleCompositePart::MouseLeftButtonDoubleClick(UINT nFlags, const CPoint& point, HDC transformHDC)
{
	CRect ptRect = m_compositeParts[0]->GetBoxLocation();
	if (ptRect.PtInRect(point)) {
		AfxMessageBox("SampleDecorator double clicked!");
		GeneralOperationStarted(NULL);
		// TODO: do something
		GeneralOperationFinished(NULL);
		return true;
	}

	return CompositePart::MouseLeftButtonDoubleClick(nFlags, point, transformHDC);
}

bool SampleCompositePart::MouseRightButtonDown(HMENU hCtxMenu, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	CRect ptRect = m_compositeParts[0]->GetBoxLocation();
	if (ptRect.PtInRect(point)) {
		::AppendMenu(hCtxMenu, MF_STRING | MF_ENABLED, CTX_MENU_ID_SAMPLE, CTX_MENU_STR_SAMPLE);
		return true;
	}

	return CompositePart::MouseRightButtonDown(hCtxMenu, nFlags, point, transformHDC);
}

bool SampleCompositePart::DragEnter(DROPEFFECT* dropEffect, COleDataObject* pDataObject, DWORD dwKeyState, const CPoint& point, HDC transformHDC)
{
	if (pDataObject->IsDataAvailable(CF_HDROP)) {
		*dropEffect = DROPEFFECT_COPY;
		return true;
	}

	return CompositePart::DragEnter(dropEffect, pDataObject, dwKeyState, point, transformHDC);
}

bool SampleCompositePart::DragOver(DROPEFFECT* dropEffect, COleDataObject* pDataObject, DWORD dwKeyState, const CPoint& point, HDC transformHDC)
{
	if (pDataObject->IsDataAvailable(CF_HDROP)) {
		*dropEffect = DROPEFFECT_COPY;
		return true;
	}

	return CompositePart::DragOver(dropEffect, pDataObject, dwKeyState, point, transformHDC);
}

bool SampleCompositePart::Drop(COleDataObject* pDataObject, DROPEFFECT dropEffect, const CPoint& point, HDC transformHDC)
{
	if (pDataObject->IsDataAvailable(CF_HDROP) && dropEffect == DROPEFFECT_COPY) {
		STGMEDIUM medium;
		medium.tymed = TYMED_HGLOBAL;
		pDataObject->GetData(CF_HDROP, &medium);
		return DropFile((HDROP)medium.hGlobal, point, transformHDC);
	}

	return CompositePart::Drop(pDataObject, dropEffect, point, transformHDC);
}

bool SampleCompositePart::DropFile(HDROP p_hDropInfo, const CPoint& point, HDC transformHDC)
{
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
				UINT readLen = txtFile.Read(pbufRead, sizeof(pbufRead) - 1);
				pbufRead[readLen] = 0;
				CString msg;
				AfxMessageBox("SampleDecorator drop: '" + conn + "' first 100 bytes: " + pbufRead + ".");
				return true;
			} else {
				AfxMessageBox("SampleDecorator drop: '.txt' files may be dropped only. Can't open file: " + conn + "!");
			}
		} else {
			AfxMessageBox("SampleDecorator drop: Can't inquire file information!");
		}
	}

	return CompositePart::DropFile(p_hDropInfo, point, transformHDC);
}

bool SampleCompositePart::MenuItemSelected(UINT menuItemId, UINT nFlags, const CPoint& point, HDC transformHDC)
{
	if (menuItemId == CTX_MENU_ID_SAMPLE) {
		AfxMessageBox("Sample Decorator Ctx Menu Item clicked!");
		GeneralOperationStarted(NULL);
		// TODO: do something
		GeneralOperationFinished(NULL);
		return true;
	}

	return CompositePart::MenuItemSelected(menuItemId, nFlags, point, transformHDC);
}

}; // namespace SampleDecor
