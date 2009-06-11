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


STDMETHODIMP CAnnotatorEventSink::Refresh()
{
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

STDMETHODIMP CAnnotatorEventSink::LabelMovingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelMoving(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelMovingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelMoved(LONG nType, LONG x, LONG y)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelResizingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelResizing(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelResizingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::LabelResized(LONG nType, LONG cx, LONG cy)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::GeneralOperationStarted(ULONGLONG operationData)
{
	m_view->BeginTransaction();
	m_view->inElementDecoratorOperation = true;
	m_view->decoratorOrAnnotator = false;
	m_view->inOpenedDecoratorTransaction = true;
	m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::GeneralOperationFinished(ULONGLONG operationData)
{
	m_view->inElementDecoratorOperation = false;
	m_view->shouldCommitOperation = true;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowMovingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowMoving(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowMovingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowMoved(LONG nType, LONG x, LONG y)
{
	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowResizingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	m_view->inElementDecoratorOperation = true;
	m_view->decoratorOrAnnotator = false;
	m_view->shouldCommitOperation = false;
	m_view->originalRect = CRect(left, top, right, bottom);

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowResizing(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
//	TODO m_guiAnnotator->ResizeObject(CRect(left, top, right, bottom));
	m_view->Invalidate();
	m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowResizingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
//	TODO m_guiAnnotator->ResizeObject(CRect(left, top, right, bottom));
	m_view->inElementDecoratorOperation = false;
	m_view->originalRect.SetRectEmpty();

	return S_OK;
}

STDMETHODIMP CAnnotatorEventSink::WindowResized(LONG nType, LONG cx, LONG cy)
{
	m_view->BeginTransaction();
	m_view->inOpenedDecoratorTransaction = true;
	m_view->shouldCommitOperation = true;

	return S_OK;
}
