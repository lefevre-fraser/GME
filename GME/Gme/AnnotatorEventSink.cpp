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

void CAnnotatorEventSink::SetView(CGMEView* view)
{
	m_view = view;
}

void CAnnotatorEventSink::SetGuiAnnotator(CGuiAnnotator* guiAnnotator)
{
	m_guiAnnotator = guiAnnotator;
}

CAnnotatorEventSink::CAnnotatorEventSink():
	m_view(NULL),
	m_guiAnnotator(NULL)
{
}

CAnnotatorEventSink::~CAnnotatorEventSink()
{
}


///////////////////////////////////////////////////////////////////////////
// IMgaElementDecoratorEvents

STDMETHODIMP CAnnotatorEventSink::Refresh()
{
	m_view->Invalidate();

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::OperationCanceled()
{
	m_view->CancelDecoratorOperation(false);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::CursorChanged(LONG newCursorID)
{
	m_view->isCursorChangedByDecorator = true;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::CursorRestored()
{
	m_view->isCursorChangedByDecorator = false;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelEditingStarted(LONG left, LONG top, LONG right, LONG bottom)
{
	m_view->inElementDecoratorOperation = true;
	m_view->decoratorOrAnnotator = false;
	m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelEditingFinished(LONG left, LONG top, LONG right, LONG bottom)
{
	if (m_view->inOpenedDecoratorTransaction) {
		// Deferred Commit operation, we cannot do commit now because it would kill the underlying decoprator also
		// Commit results in a whle refresh: complete destruction and regeneration of Gui* wrapper classes, and this destroys decorators also
		m_view->PostMessage(WM_USER_COMMITTRAN, 0, 0);
	} else {
		m_view->inOpenedDecoratorTransaction = false;
		m_view->shouldCommitOperation = false;
		m_view->inElementDecoratorOperation = false;
		m_view->objectInDecoratorOperation = NULL;
		m_view->annotatorInDecoratorOperation = NULL;
	}

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelChanged(BSTR newLabel)
{
	m_view->BeginTransaction();
	m_view->inOpenedDecoratorTransaction = true;
	m_view->shouldCommitOperation = true;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelMovingStarted(LONG nFlags, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelMoving(LONG nFlags, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelMovingFinished(LONG nFlags, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelMoved(LONG nFlags, LONG x, LONG y)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelResizingStarted(LONG nFlags, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelResizing(LONG nFlags, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelResizingFinished(LONG nFlags, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelResized(LONG nFlags, LONG cx, LONG cy)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::GeneralOperationStarted(ULONGLONG operationData)
{
	m_operationData = (void*)operationData;

	m_view->BeginTransaction();
	m_view->inElementDecoratorOperation = true;
	m_view->decoratorOrAnnotator = false;
	m_view->inOpenedDecoratorTransaction = true;
	m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::GeneralOperationFinished(ULONGLONG* operationData)
{
	if (operationData != NULL)
		*operationData = (ULONGLONG)m_operationData;

	m_view->inElementDecoratorOperation = false;
	m_view->shouldCommitOperation = true;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowMovingStarted(LONG nFlags, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowMoving(LONG nFlags, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowMovingFinished(LONG nFlags, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowMoved(LONG nFlags, LONG x, LONG y)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowResizingStarted(LONG nFlags, LONG left, LONG top, LONG right, LONG bottom)
{
	m_view->inElementDecoratorOperation = true;
	m_view->decoratorOrAnnotator = false;
	m_view->shouldCommitOperation = false;
	m_view->originalRect = CRect(left, top, right, bottom);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowResizing(LONG nFlags, LONG left, LONG top, LONG right, LONG bottom)
{
//	TODO m_guiAnnotator->ResizeObject(CRect(left, top, right, bottom));
	m_view->Invalidate();
	m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowResizingFinished(LONG nFlags, LONG left, LONG top, LONG right, LONG bottom)
{
//	TODO m_guiAnnotator->ResizeObject(CRect(left, top, right, bottom));
	m_view->inElementDecoratorOperation = false;
	m_view->originalRect.SetRectEmpty();

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowResized(LONG nFlags, LONG cx, LONG cy)
{
	m_view->BeginTransaction();
	m_view->inOpenedDecoratorTransaction = true;
	m_view->shouldCommitOperation = true;

	return S_OK;
}
