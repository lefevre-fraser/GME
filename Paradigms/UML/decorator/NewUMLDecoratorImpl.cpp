//################################################################################################
//
// New UML Decorator COM side Implementation
//	NewUMLDecoratorImpl.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "NewUMLDecoratorImpl.h"
#include "NewUMLDecorator.h"
#include "DecoratorExceptions.h"
#include "DecoratorInterface.h"


//################################################################################################
//
// CLASS : CNewUMLDecoratorImpl
//
//################################################################################################

#define VERIFY_INITIALIZATION					\
	if (!m_pNewDecorator)						\
		return E_DECORATOR_UNINITIALIZED;

#define VERIFY_LOCATION							\
	if (!m_bLocationSet)						\
		return E_DECORATOR_LOCISNOTSET;

CNewUMLDecoratorImpl::CNewUMLDecoratorImpl():
	m_pNewDecorator		(NULL),
	m_bLocationSet		(false),
	m_bInitCallFromEx	(false)
{
}

CNewUMLDecoratorImpl::~CNewUMLDecoratorImpl()
{
}

STDMETHODIMP CNewUMLDecoratorImpl::Initialize(IMgaProject* pProject, IMgaMetaPart* pPart, IMgaFCO* pFCO)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (pFCO && !m_bInitCallFromEx)
		return E_DECORATOR_USING_DEPRECATED_FUNCTION;

	return S_OK;
}

STDMETHODIMP CNewUMLDecoratorImpl::Destroy()
{
	m_bLocationSet = false;
	if (m_pNewDecorator) {
		delete m_pNewDecorator;
		m_pNewDecorator = NULL;
	}

	return S_OK;
}

STDMETHODIMP CNewUMLDecoratorImpl::GetMnemonic(BSTR* bstrMnemonic)
{
	*bstrMnemonic = CComBSTR("NewUMLDecorator").Detach();

	return S_OK;
}

STDMETHODIMP CNewUMLDecoratorImpl::GetFeatures(feature_code* pFeatureCodes)
{
	*pFeatureCodes = F_HASLABEL;

	return S_OK;
}

STDMETHODIMP CNewUMLDecoratorImpl::SetParam(BSTR bstrName, VARIANT vValue)
{
	VERIFY_INITIALIZATION

	HRESULT retVal = S_OK;
	try {
		m_pNewDecorator->SetParam(bstrName, vValue);
	}
	catch(hresult_exception& e) {
		retVal = e.hr;
	}
	catch(DecoratorException& e) {
		retVal = e.GetHResult();
	}
	return retVal;
}

STDMETHODIMP CNewUMLDecoratorImpl::GetParam(BSTR bstrName, VARIANT* pvValue)
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

STDMETHODIMP CNewUMLDecoratorImpl::SetActive(VARIANT_BOOL vbIsActive)
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

STDMETHODIMP CNewUMLDecoratorImpl::GetPreferredSize(LONG* plWidth, LONG* plHeight)
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


STDMETHODIMP CNewUMLDecoratorImpl::SetLocation(LONG sx, LONG sy, LONG ex, LONG ey)
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

STDMETHODIMP CNewUMLDecoratorImpl::GetLocation(LONG* sx, LONG* sy, LONG* ex, LONG* ey)
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

STDMETHODIMP CNewUMLDecoratorImpl::GetLabelLocation(LONG* sx, LONG* sy, LONG* ex, LONG* ey)
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

STDMETHODIMP CNewUMLDecoratorImpl::GetPortLocation(IMgaFCO* pFCO, LONG* sx, LONG* sy, LONG* ex, LONG* ey)
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

STDMETHODIMP CNewUMLDecoratorImpl::GetPorts(IMgaFCOs** portFCOs)
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

STDMETHODIMP CNewUMLDecoratorImpl::Draw(HDC hdc)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	VERIFY_INITIALIZATION
	VERIFY_LOCATION

	return E_DECORATOR_USING_DEPRECATED_FUNCTION;
}

STDMETHODIMP CNewUMLDecoratorImpl::SaveState()
{
	VERIFY_INITIALIZATION

	return S_OK;
}

// New functions
STDMETHODIMP CNewUMLDecoratorImpl::InitializeEx(IMgaProject* pProject, IMgaMetaPart* pPart, IMgaFCO* pFCO,
												IMgaNewDecoratorEvents* eventSink, ULONGLONG parentWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_bInitCallFromEx = true;

	HRESULT retVal = S_OK;
	try {
		UMLDecor::NewUMLDecorator* newUMLDecorator = new UMLDecor::NewUMLDecorator(CComPtr<IMgaNewDecoratorEvents>(eventSink));
		m_pNewDecorator = newUMLDecorator;

		newUMLDecorator->InitializeEx(CComPtr<IMgaProject>(pProject), CComPtr<IMgaMetaPart>(pPart),
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

STDMETHODIMP CNewUMLDecoratorImpl::DrawEx(HDC hdc, ULONGLONG gdipGraphics)
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

STDMETHODIMP CNewUMLDecoratorImpl::SetSelected(VARIANT_BOOL vbIsSelected)
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

STDMETHODIMP CNewUMLDecoratorImpl::MouseMoved(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::MouseLeftButtonDown(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::MouseLeftButtonUp(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::MouseLeftButtonDoubleClick(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::MouseRightButtonDown(ULONGLONG hCtxMenu, ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::MouseRightButtonUp(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::MouseRightButtonDoubleClick(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::MouseMiddleButtonDown(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::MouseMiddleButtonUp(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::MouseMiddleButtonDoubleClick(ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::MouseWheelTurned(ULONG nFlags, LONG distance, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::DragEnter(ULONG* dropEffect, ULONGLONG pCOleDataObject, ULONG keyState, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::DragOver(ULONG* dropEffect, ULONGLONG pCOleDataObject, ULONG keyState, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::Drop(ULONGLONG pCOleDataObject, ULONG dropEffect, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::DropFile(ULONGLONG hDropInfo, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::MenuItemSelected(ULONG menuItemId, ULONG nFlags, LONG pointx, LONG pointy, ULONGLONG transformHDC)
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

STDMETHODIMP CNewUMLDecoratorImpl::OperationCanceled()
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
