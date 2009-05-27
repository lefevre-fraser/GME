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


void CDecoratorEventSink::SetView(CGMEView* view)
{
	m_view = view;
}

void CDecoratorEventSink::SetGuiObject(CGuiObject* guiObject)
{
	m_guiObject = guiObject;
}

HRESULT CDecoratorEventSink::QuerySinkInterface(void** ppv)
{
	return m_xEventSink.QueryInterface(IID_IMgaElementDecoratorEvents, ppv);
}

CDecoratorEventSink::CDecoratorEventSink():
	m_view(NULL),
	m_guiObject(NULL)
{
	EnableAutomation();	// only needed for Dispatch maps
}

CDecoratorEventSink::~CDecoratorEventSink()
{
}

void CDecoratorEventSink::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CDecoratorEventSink, CCmdTarget)
	//{{AFX_MSG_MAP(CDecoratorEventSink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CDecoratorEventSink, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CDecoratorEventSink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CDecoratorEventSink, CCmdTarget)
	INTERFACE_PART(CDecoratorEventSink, IID_IMgaElementDecoratorEvents, EventSink)
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

STDMETHODIMP CDecoratorEventSink::XEventSink::LabelEditingStarted(LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	pThis->m_view->inElementDecoratorOperation = true;
	pThis->m_view->decoratorOrAnnotator = true;
	pThis->m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::LabelEditingFinished(LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	if (pThis->m_view->inOpenedDecoratorTransaction) {
		// Deferred Commit operation, we cannot do commit now because it would kill the underlying decoprator also
		// Commit results in a whle refresh: complete destruction and regeneration of Gui* wrapper classes, and this destroys decorators also
		pThis->m_view->PostMessage(WM_USER_COMMITTRAN, 0, 0);
	} else {
		pThis->m_view->inOpenedDecoratorTransaction = false;
		pThis->m_view->shouldCommitOperation = false;
		pThis->m_view->inElementDecoratorOperation = false;
		pThis->m_view->objectInDecoratorOperation = NULL;
		pThis->m_view->annotatorInDecoratorOperation = NULL;
	}

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::LabelChanged(BSTR newLabel)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	pThis->m_view->BeginTransaction();
	pThis->m_view->inOpenedDecoratorTransaction = true;
	pThis->m_view->shouldCommitOperation = true;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::LabelMovingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::LabelMoving(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::LabelMovingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::LabelMoved(LONG nType, LONG x, LONG y)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::LabelResizingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::LabelResizing(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::LabelResizingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::LabelResized(LONG nType, LONG cx, LONG cy)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::GeneralOperationStarted(ULONGLONG operationData)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	pThis->m_view->BeginTransaction();
	pThis->m_view->inElementDecoratorOperation = true;
	pThis->m_view->decoratorOrAnnotator = true;
	pThis->m_view->inOpenedDecoratorTransaction = true;
	pThis->m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::XEventSink::GeneralOperationFinished(ULONGLONG operationData)
{
	METHOD_PROLOGUE(CDecoratorEventSink,EventSink);

	pThis->m_view->inElementDecoratorOperation = false;
	pThis->m_view->shouldCommitOperation = true;

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

	pThis->m_view->inElementDecoratorOperation = true;
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
	pThis->m_view->inElementDecoratorOperation = false;
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
