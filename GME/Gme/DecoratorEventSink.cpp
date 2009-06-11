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

void CDecoratorEventSink::SetView(CGMEView* view)
{
	m_view = view;
}

void CDecoratorEventSink::SetGuiObject(CGuiObject* guiObject)
{
	m_guiObject = guiObject;
}

CDecoratorEventSink::CDecoratorEventSink():
	m_view(NULL),
	m_guiObject(NULL)
{
}

CDecoratorEventSink::~CDecoratorEventSink()
{
}


///////////////////////////////////////////////////////////////////////////
// IMgaElementDecoratorEvents

STDMETHODIMP CDecoratorEventSink::Refresh()
{
	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::OperationCanceled()
{
	m_view->CancelDecoratorOperation(false);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::CursorChanged(LONG newCursorID)
{
	m_view->isCursorChangedByDecorator = true;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::CursorRestored()
{
	m_view->isCursorChangedByDecorator = false;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::LabelEditingStarted(LONG left, LONG top, LONG right, LONG bottom)
{
	m_view->inElementDecoratorOperation = true;
	m_view->decoratorOrAnnotator = true;
	m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::LabelEditingFinished(LONG left, LONG top, LONG right, LONG bottom)
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

STDMETHODIMP CDecoratorEventSink::LabelChanged(BSTR newLabel)
{
	m_view->BeginTransaction();
	m_view->inOpenedDecoratorTransaction = true;
	m_view->shouldCommitOperation = true;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::LabelMovingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::LabelMoving(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::LabelMovingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::LabelMoved(LONG nType, LONG x, LONG y)
{
	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::LabelResizingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::LabelResizing(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::LabelResizingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::LabelResized(LONG nType, LONG cx, LONG cy)
{
	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::GeneralOperationStarted(ULONGLONG operationData)
{
	m_view->BeginTransaction();
	m_view->inElementDecoratorOperation = true;
	m_view->decoratorOrAnnotator = true;
	m_view->inOpenedDecoratorTransaction = true;
	m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::GeneralOperationFinished(ULONGLONG operationData)
{
	m_view->inElementDecoratorOperation = false;
	m_view->shouldCommitOperation = true;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::WindowMovingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::WindowMoving(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::WindowMovingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::WindowMoved(LONG nType, LONG x, LONG y)
{
	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::WindowResizingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	m_view->inElementDecoratorOperation = true;
	m_view->decoratorOrAnnotator = true;
	m_view->shouldCommitOperation = false;
	m_view->originalRect = CRect(left, top, right, bottom);

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::WindowResizing(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	m_guiObject->ResizeObject(CRect(left, top, right, bottom));
	m_view->Invalidate();
	m_view->shouldCommitOperation = false;

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::WindowResizingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	m_guiObject->ResizeObject(CRect(left, top, right, bottom));
	m_view->inElementDecoratorOperation = false;
	m_view->originalRect.SetRectEmpty();

	return S_OK;
}

STDMETHODIMP CDecoratorEventSink::WindowResized(LONG nType, LONG cx, LONG cy)
{
	m_view->BeginTransaction();
	m_view->inOpenedDecoratorTransaction = true;
	m_view->shouldCommitOperation = true;

	return S_OK;
}
