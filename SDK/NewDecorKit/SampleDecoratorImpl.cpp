//################################################################################################
//
// Sample Decorator COM side Implementation
//	SampleDecoratorImpl.cpp
// This class represents the COM/ATL side of the decorator COM connection layer
// For the pure C++ side see SampleDecorator.h,cpp and SampleCompositePart.h,cpp
//
//################################################################################################

#include "StdAfx.h"
#include "DecoratorConfig.h"
#include "SampleDecoratorImpl.h"
#include "SampleDecorator.h"
#include "DecoratorExceptions.h"
#include "DecoratorInterface.h"


//################################################################################################
//
// CLASS : CSampleDecoratorImpl
//
//################################################################################################

#define VERIFY_INITIALIZATION					\
	if (!m_pNewDecorator)						\
		return E_DECORATOR_UNINITIALIZED;

#define VERIFY_LOCATION							\
	if (!m_bLocationSet)						\
		return E_DECORATOR_LOCISNOTSET;

CSampleDecoratorImpl::CSampleDecoratorImpl():
	m_pNewDecorator		(NULL),
	m_bLocationSet		(false),
	m_bInitCallFromEx	(false)
{
}

CSampleDecoratorImpl::~CSampleDecoratorImpl()
{
}

STDMETHODIMP CSampleDecoratorImpl::Initialize(IMgaProject* pProject, IMgaMetaPart* pPart, IMgaFCO* pFCO)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (pFCO && !m_bInitCallFromEx)
		return E_DECORATOR_USING_DEPRECATED_FUNCTION;

	return S_OK;
}

STDMETHODIMP CSampleDecoratorImpl::Destroy()
{
	VERIFY_INITIALIZATION

	HRESULT retVal = S_OK;
	try {
		m_pNewDecorator->Destroy();
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}

	m_bLocationSet = false;
	if (m_pNewDecorator) {
		delete m_pNewDecorator;
		m_pNewDecorator = NULL;
	}

	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::GetMnemonic(BSTR* bstrMnemonic)
{
	*bstrMnemonic = CComBSTR(DECORATOR_NAME).Detach();

	return S_OK;
}

STDMETHODIMP CSampleDecoratorImpl::GetFeatures(feature_code* pFeatureCodes)
{
	*pFeatureCodes = F_RESIZABLE | F_HASLABEL | F_MOUSEEVENTS | F_RESIZEAFTERMOD;

	return S_OK;
}

STDMETHODIMP CSampleDecoratorImpl::SetParam(BSTR bstrName, VARIANT vValue)
{
	HRESULT retVal = S_OK;
	m_bstrName = bstrName;
	m_vValue = vValue;
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::GetParam(BSTR bstrName, VARIANT* pvValue)
{
	VERIFY_INITIALIZATION

	HRESULT retVal = S_OK;
	try {
		m_pNewDecorator->GetParam(bstrName, pvValue);
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::SetActive(VARIANT_BOOL vbIsActive)
{
	VERIFY_INITIALIZATION

	HRESULT retVal = S_OK;
	try {
		m_pNewDecorator->SetActive(vbIsActive == VARIANT_TRUE);
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::GetPreferredSize(LONG* plWidth, LONG* plHeight)
{
	VERIFY_INITIALIZATION

	HRESULT retVal = S_OK;
	try {
		CSize cSize = m_pNewDecorator->GetPreferredSize();
		*plWidth = cSize.cx;
		*plHeight = cSize.cy;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}


STDMETHODIMP CSampleDecoratorImpl::SetLocation(LONG sx, LONG sy, LONG ex, LONG ey)
{
	VERIFY_INITIALIZATION

	HRESULT retVal = S_OK;
	try {
		m_pNewDecorator->SetLocation(CRect(sx, sy, ex, ey));
		m_bLocationSet = true;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::GetLocation(LONG* sx, LONG* sy, LONG* ex, LONG* ey)
{
	VERIFY_INITIALIZATION
	VERIFY_LOCATION

	HRESULT retVal = S_OK;
	try {
		CRect cRect = m_pNewDecorator->GetLocation();
		*sx = cRect.left;
		*sy = cRect.top;
		*ex = cRect.right;
		*ey = cRect.bottom;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::GetLabelLocation(LONG* sx, LONG* sy, LONG* ex, LONG* ey)
{
	VERIFY_INITIALIZATION
	VERIFY_LOCATION

	HRESULT retVal = S_OK;
	try {
		CRect labelRect = m_pNewDecorator->GetLabelLocation();
		*sx = labelRect.left;
		*sy = labelRect.top;
		*ex = labelRect.right;
		*ey = labelRect.bottom;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::GetPortLocation(IMgaFCO* pFCO, LONG* sx, LONG* sy, LONG* ex, LONG* ey)
{
	VERIFY_INITIALIZATION
	VERIFY_LOCATION

	HRESULT retVal = S_OK;
	try {
		CRect portLocation = m_pNewDecorator->GetPortLocation(CComPtr<IMgaFCO>(pFCO));
		*sx = portLocation.left;
		*sy = portLocation.top;
		*ex = portLocation.right;
		*ey = portLocation.bottom;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::GetPorts(IMgaFCOs** portFCOs)
{
	VERIFY_INITIALIZATION

	HRESULT retVal = S_OK;
	try {
		CComPtr<IMgaFCOs> portMgaFCOs;
		m_pNewDecorator->GetPorts(portMgaFCOs);
		*portFCOs = portMgaFCOs;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::Draw(HDC hdc)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	VERIFY_INITIALIZATION
	VERIFY_LOCATION

	return E_DECORATOR_USING_DEPRECATED_FUNCTION;
}

STDMETHODIMP CSampleDecoratorImpl::SaveState()
{
	VERIFY_INITIALIZATION

	return S_OK;
}

// New functions
STDMETHODIMP CSampleDecoratorImpl::InitializeEx(IMgaProject* pProject, IMgaMetaPart* pPart, IMgaFCO* pFCO,
												IMgaNewDecoratorEvents* eventSink, ULONGLONG parentWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_bInitCallFromEx = true;

	HRESULT retVal = S_OK;
	try {
		SampleDecor::SampleDecorator* sampleDecorator = new SampleDecor::SampleDecorator(CComPtr<IMgaNewDecoratorEvents>(eventSink));
		m_pNewDecorator = sampleDecorator;
		sampleDecorator->InitializeEx(CComPtr<IMgaProject>(pProject), CComPtr<IMgaMetaPart>(pPart),
									  CComPtr<IMgaFCO>(pFCO), (HWND)parentWnd);
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}

	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::DrawEx(HDC hdc, ULONGLONG gdipGraphics)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	VERIFY_INITIALIZATION
	VERIFY_LOCATION

	HRESULT retVal = S_OK;

	CDC dc;
	dc.Attach(hdc);
	{
		try {
			m_pNewDecorator->Draw(&dc, (Gdiplus::Graphics*)gdipGraphics);
		}
		catch(hresult_exception& e) {
			retVal = e.hr;
		}
		catch(DecoratorException& e) {
			retVal = e.GetHResult();
		}
	}
	dc.Detach();

	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::SetSelected(VARIANT_BOOL vbIsSelected)
{
	VERIFY_INITIALIZATION

	HRESULT retVal = S_OK;
	try {
		m_pNewDecorator->SetSelected(vbIsSelected == VARIANT_TRUE);
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::MouseMoved(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->MouseMoved(nFlags, CPoint(pointx, pointy), (HDC)transformHDC))
			retVal = S_DECORATOR_EVENT_HANDLED;
		else
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::MouseLeftButtonDown(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->MouseLeftButtonDown(nFlags, CPoint(pointx, pointy), (HDC)transformHDC))
			retVal = S_DECORATOR_EVENT_HANDLED;
		else
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::MouseLeftButtonUp(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->MouseLeftButtonUp(nFlags, CPoint(pointx, pointy), (HDC)transformHDC))
			retVal = S_DECORATOR_EVENT_HANDLED;
		else
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::MouseLeftButtonDoubleClick(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->MouseLeftButtonDoubleClick(nFlags, CPoint(pointx, pointy), (HDC)transformHDC))
			retVal = S_DECORATOR_EVENT_HANDLED;
		else
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::MouseRightButtonDown(ULONGLONG hCtxMenu, ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->MouseRightButtonDown((HMENU) hCtxMenu, nFlags, CPoint(pointx, pointy), (HDC)transformHDC))
			retVal = S_DECORATOR_EVENT_HANDLED;
		else
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::MouseRightButtonUp(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->MouseRightButtonUp(nFlags, CPoint(pointx, pointy), (HDC)transformHDC))
			retVal = S_DECORATOR_EVENT_HANDLED;
		else
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::MouseRightButtonDoubleClick(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->MouseRightButtonDoubleClick(nFlags, CPoint(pointx, pointy), (HDC)transformHDC))
			retVal = S_DECORATOR_EVENT_HANDLED;
		else
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::MouseMiddleButtonDown(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->MouseMiddleButtonDown(nFlags, CPoint(pointx, pointy), (HDC)transformHDC))
			retVal = S_DECORATOR_EVENT_HANDLED;
		else
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::MouseMiddleButtonUp(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->MouseMiddleButtonUp(nFlags, CPoint(pointx, pointy), (HDC)transformHDC))
			retVal = S_DECORATOR_EVENT_HANDLED;
		else
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::MouseMiddleButtonDoubleClick(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->MouseMiddleButtonDoubleClick(nFlags, CPoint(pointx, pointy), (HDC)transformHDC))
			retVal = S_DECORATOR_EVENT_HANDLED;
		else
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::MouseWheelTurned(ULONG nFlags, LONG distance, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->MouseWheelTurned(nFlags, (short)distance, CPoint(pointx, pointy), (HDC)transformHDC))
			retVal = S_DECORATOR_EVENT_HANDLED;
		else
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::DragEnter(ULONG* dropEffect, ULONGLONG pCOleDataObject, ULONG keyState, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->DragEnter((DROPEFFECT*)dropEffect, (COleDataObject*)pCOleDataObject, (DWORD)keyState, CPoint(pointx, pointy), (HDC)transformHDC)) {
			retVal = S_DECORATOR_EVENT_HANDLED;
		} else {
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
			*dropEffect = DROPEFFECT_NONE;
		}
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::DragOver(ULONG* dropEffect, ULONGLONG pCOleDataObject, ULONG keyState, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->DragOver((DROPEFFECT*)dropEffect, (COleDataObject*)pCOleDataObject, (DWORD)keyState, CPoint(pointx, pointy), (HDC)transformHDC)) {
			retVal = S_DECORATOR_EVENT_HANDLED;
		} else {
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
			*dropEffect = DROPEFFECT_NONE;
		}
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::Drop(ULONGLONG pCOleDataObject, ULONG dropEffect, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->Drop((COleDataObject*)pCOleDataObject, (DROPEFFECT)dropEffect, CPoint(pointx, pointy), (HDC)transformHDC))
			retVal = S_DECORATOR_EVENT_HANDLED;
		else
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::DropFile(ULONGLONG hDropInfo, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->DropFile((HDROP)hDropInfo, CPoint(pointx, pointy), (HDC)transformHDC))
			retVal = S_DECORATOR_EVENT_HANDLED;
		else
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::MenuItemSelected(ULONG menuItemId, ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->MenuItemSelected(menuItemId, nFlags, CPoint(pointx, pointy), (HDC)transformHDC))
			retVal = S_DECORATOR_EVENT_HANDLED;
		else
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CSampleDecoratorImpl::OperationCanceled()
{
	HRESULT retVal = S_OK;
	try {
		if (m_pNewDecorator->OperationCanceledByGME())
			retVal = S_DECORATOR_EVENT_HANDLED;
		else
			retVal = S_DECORATOR_EVENT_NOT_HANDLED;
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}
