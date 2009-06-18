//################################################################################################
//
// PartBrowser Decorator Event Sink implementation for PartBrowser
//	PartBrowserDecoratorEventSink.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "PartBrowserDecoratorEventSink.h"
#include "MgaDecorator_i.c"


//################################################################################################
//
// CLASS : CPartBrowserDecoratorEventSink
//
//################################################################################################

CPartBrowserDecoratorEventSink::CPartBrowserDecoratorEventSink()
{
}

CPartBrowserDecoratorEventSink::~CPartBrowserDecoratorEventSink()
{
}

///////////////////////////////////////////////////////////////////////////
// IMgaElementDecoratorEvents

STDMETHODIMP CPartBrowserDecoratorEventSink::Refresh()
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::OperationCanceled()
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::CursorChanged(LONG newCursorID)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::CursorRestored()
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::LabelEditingStarted(LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::LabelEditingFinished(LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::LabelChanged(BSTR newLabel)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::LabelMovingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::LabelMoving(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::LabelMovingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::LabelMoved(LONG nType, LONG x, LONG y)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::LabelResizingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::LabelResizing(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::LabelResizingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::LabelResized(LONG nType, LONG cx, LONG cy)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::GeneralOperationStarted(ULONGLONG operationData)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::GeneralOperationFinished(ULONGLONG operationData)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::WindowMovingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::WindowMoving(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::WindowMovingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::WindowMoved(LONG nType, LONG x, LONG y)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::WindowResizingStarted(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::WindowResizing(LONG nSide, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::WindowResizingFinished(LONG nType, LONG left, LONG top, LONG right, LONG bottom)
{
	return S_OK;
}

STDMETHODIMP CPartBrowserDecoratorEventSink::WindowResized(LONG nType, LONG cx, LONG cy)
{
	return S_OK;
}
