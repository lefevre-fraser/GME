//################################################################################################
//
// Decorator Event Sink implementation
//	DecoratorEventSink.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "DecoratorEventSink.h"
#include "GMEView.h"
#include "MgaDecorator_i.c"


//################################################################################################
//
// CLASS : CDecoratorEventSink
//
//################################################################################################

IMPLEMENT_DYNCREATE(CDecoratorEventSink, CCmdTarget)


HRESULT CDecoratorEventSink::QuerySinkInterface(void** ppv)
{
	return m_xEventSink.QueryInterface(IID_IMgaNewDecoratorEvents, ppv);
}

CDecoratorEventSink::CDecoratorEventSink():
	m_view(NULL),
	m_guiObject(NULL)
{
	TRACE("EventSink contruct %p\n", this);
//	EnableAutomation();	// only needed for Dispatch maps
}

CDecoratorEventSink::~CDecoratorEventSink()
{
	TRACE("EventSink destruct %p\n", this);
}

void CDecoratorEventSink::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}


BEGIN_INTERFACE_MAP(CDecoratorEventSink, CCmdTarget)
	INTERFACE_PART(CDecoratorEventSink, IID_IMgaNewDecoratorEvents, EventSink)
END_INTERFACE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDecoratorEventSink::XEventSink - native COM interface - peter
STDMETHODIMP_(ULONG) CDecoratorEventSink::XEventSink::AddRef()
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CDecoratorEventSink::XEventSink::Release()
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);
	return pThis->ExternalRelease();
}

STDMETHODIMP CDecoratorEventSink::XEventSink::QueryInterface(REFIID riid, void** ppv)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);
	return pThis->ExternalQueryInterface(&riid, ppv);
}


STDMETHODIMP CDecoratorEventSink::XEventSink::Refresh()
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::OperationCanceled()
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	pThis->m_view->CancelDecoratorOperation(false);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::CursorChanged(LONG newCursorID)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	pThis->m_view->isCursorChangedByDecorator = true;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::CursorRestored()
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	pThis->m_view->isCursorChangedByDecorator = false;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::TitleEditingStarted(LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	pThis->m_view->inNewDecoratorOperation = true;
	pThis->m_view->decoratorOrAnnotator = true;
	pThis->m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::TitleEditingFinished(LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	if (pThis->m_view->inOpenedDecoratorTransaction) {
		pThis->m_view->PostMessage(WM_USER_COMMITTRAN, 0, 0);
	} else {
		pThis->m_view->inOpenedDecoratorTransaction = false;
		pThis->m_view->shouldCommitOperation = false;
		pThis->m_view->inNewDecoratorOperation = false;
		pThis->m_view->objectInDecoratorOperation = NULL;
		pThis->m_view->annotatorInDecoratorOperation = NULL;
	}

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::TitleChanged(BSTR newTitle)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	pThis->m_view->BeginTransaction();
	pThis->m_view->inOpenedDecoratorTransaction = true;
	pThis->m_view->shouldCommitOperation = true;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::TitleMovingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::TitleMoving(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::TitleMovingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::TitleMoved(LONG nType, LONG x, LONG y)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::TitleResizingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::TitleResizing(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::TitleResizingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::TitleResized(LONG nType, LONG cx, LONG cy)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::WindowMovingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::WindowMoving(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::WindowMovingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::WindowMoved(LONG nType, LONG x, LONG y)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::WindowResizingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	pThis->m_view->inNewDecoratorOperation = true;
	pThis->m_view->decoratorOrAnnotator = true;
	pThis->m_view->shouldCommitOperation = false;
	pThis->m_view->originalRect = CRect(left, top, right, bottom);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::WindowResizing(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	pThis->m_guiObject->ResizeObject(CRect(left, top, right, bottom));
	pThis->m_view->Invalidate();
	pThis->m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::WindowResizingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	pThis->m_guiObject->ResizeObject(CRect(left, top, right, bottom));
	pThis->m_view->inNewDecoratorOperation = false;
	pThis->m_view->originalRect.SetRectEmpty();

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::WindowResized(LONG nType, LONG cx, LONG cy)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	pThis->m_view->BeginTransaction();
	pThis->m_view->inOpenedDecoratorTransaction = true;
	pThis->m_view->shouldCommitOperation = true;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::GeneralOperationStarted(ULONGLONG operationData)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	pThis->m_view->BeginTransaction();
	pThis->m_view->inNewDecoratorOperation = true;
	pThis->m_view->decoratorOrAnnotator = true;
	pThis->m_view->inOpenedDecoratorTransaction = true;
	pThis->m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::GeneralOperationFinished(ULONGLONG operationData)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	pThis->m_view->inNewDecoratorOperation = false;
	pThis->m_view->shouldCommitOperation = true;

	return S_OK;
}
