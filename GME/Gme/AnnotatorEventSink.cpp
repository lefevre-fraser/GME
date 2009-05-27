//################################################################################################
//
// Annotator Event Sink implementation
//	AnnotatorEventSink.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "AnnotatorEventSink.h"
#include "GMEView.h"


//################################################################################################
//
// CLASS : CAnnotatorEventSink
//
//################################################################################################

IMPLEMENT_DYNCREATE(CAnnotatorEventSink, CCmdTarget)


void CAnnotatorEventSink::SetView(CGMEView* view)
{
	m_view = view;
}

void CAnnotatorEventSink::SetGuiAnnotator(CGuiAnnotator* guiAnnotator)
{
	m_guiAnnotator = guiAnnotator;
}

HRESULT CAnnotatorEventSink::QuerySinkInterface(void** ppv)
{
	return m_xEventSink.QueryInterface(IID_IMgaElementDecoratorEvents, ppv);
}

CAnnotatorEventSink::CAnnotatorEventSink():
	m_view(NULL),
	m_guiAnnotator(NULL)
{
	EnableAutomation();	// only needed for Dispatch maps
}

CAnnotatorEventSink::~CAnnotatorEventSink()
{
}

void CAnnotatorEventSink::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CAnnotatorEventSink, CCmdTarget)
	//{{AFX_MSG_MAP(CAnnotatorEventSink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAnnotatorEventSink, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CAnnotatorEventSink)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CAnnotatorEventSink, CCmdTarget)
	INTERFACE_PART(CAnnotatorEventSink, IID_IMgaElementDecoratorEvents, EventSink)
END_INTERFACE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CAnnotatorEventSink::XEventSink - native COM interface - peter
STDMETHODIMP_(ULONG) CAnnotatorEventSink::XEventSink::AddRef()
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CAnnotatorEventSink::XEventSink::Release()
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);
	return pThis->ExternalRelease();
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::QueryInterface(REFIID riid, void** ppv)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);
	return pThis->ExternalQueryInterface(&riid, ppv);
}


STDMETHODIMP CAnnotatorEventSink::XEventSink::Refresh()
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::OperationCanceled()
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	pThis->m_view->CancelDecoratorOperation(false);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::CursorChanged(LONG newCursorID)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	pThis->m_view->isCursorChangedByDecorator = true;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::CursorRestored()
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	pThis->m_view->isCursorChangedByDecorator = false;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::LabelEditingStarted(LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	pThis->m_view->inElementDecoratorOperation = true;
	pThis->m_view->decoratorOrAnnotator = false;
	pThis->m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::LabelEditingFinished(LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

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

STDMETHODIMP CAnnotatorEventSink::XEventSink::LabelChanged(BSTR newLabel)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	pThis->m_view->BeginTransaction();
	pThis->m_view->inOpenedDecoratorTransaction = true;
	pThis->m_view->shouldCommitOperation = true;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::LabelMovingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::LabelMoving(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::LabelMovingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::LabelMoved(LONG nType, LONG x, LONG y)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::LabelResizingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::LabelResizing(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::LabelResizingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::LabelResized(LONG nType, LONG cx, LONG cy)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::GeneralOperationStarted(ULONGLONG operationData)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	pThis->m_view->BeginTransaction();
	pThis->m_view->inElementDecoratorOperation = true;
	pThis->m_view->decoratorOrAnnotator = false;
	pThis->m_view->inOpenedDecoratorTransaction = true;
	pThis->m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::GeneralOperationFinished(ULONGLONG operationData)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	pThis->m_view->inElementDecoratorOperation = false;
	pThis->m_view->shouldCommitOperation = true;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::WindowMovingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::WindowMoving(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::WindowMovingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::WindowMoved(LONG nType, LONG x, LONG y)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::WindowResizingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	pThis->m_view->inElementDecoratorOperation = true;
	pThis->m_view->decoratorOrAnnotator = false;
	pThis->m_view->shouldCommitOperation = false;
	pThis->m_view->originalRect = CRect(left, top, right, bottom);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::WindowResizing(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

//	TODO pThis->m_guiAnnotator->ResizeObject(CRect(left, top, right, bottom));
	pThis->m_view->Invalidate();
	pThis->m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::WindowResizingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

//	TODO pThis->m_guiAnnotator->ResizeObject(CRect(left, top, right, bottom));
	pThis->m_view->inElementDecoratorOperation = false;
	pThis->m_view->originalRect.SetRectEmpty();

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::XEventSink::WindowResized(LONG nType, LONG cx, LONG cy)
{
	METHOD_PROLOGUE(CAnnotatorEventSink,EventSink);

	pThis->m_view->BeginTransaction();
	pThis->m_view->inOpenedDecoratorTransaction = true;
	pThis->m_view->shouldCommitOperation = true;

	return S_OK;
}
