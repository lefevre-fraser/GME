//################################################################################################
//
// Annotator Event Sink implementation
//	AnnotatorEventSink.h
//
//################################################################################################

#if !defined(AFX_ANNOTATOREVENTSINK_H__2709B864_A353_4C26_9AF8_40948D2CBC1A__INCLUDED_)
#define AFX_ANNOTATOREVENTSINK_H__2709B864_A353_4C26_9AF8_40948D2CBC1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "mga.h"
#include "MgaDecorator.h"
#include "GmeLib.h"
#include "resource.h"


class CGMEView;
class CGuiAnnotator;

//################################################################################################
//
// CLASS : CAnnotatorEventSink
//
//################################################################################################

class ATL_NO_VTABLE CAnnotatorEventSink :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAnnotatorEventSink, &CLSID_AnnotatorEventSink>,
	public ISupportErrorInfoImpl<&IID_IMgaElementDecoratorEvents>,
	public IMgaElementDecoratorEvents
{
protected:
	CAnnotatorEventSink();           // protected constructor used by dynamic creation

public:
DECLARE_REGISTRY_RESOURCEID(IDR_ANNOTATOREVENTSINK)
DECLARE_NOT_AGGREGATABLE(CAnnotatorEventSink)

BEGIN_COM_MAP(CAnnotatorEventSink)
	COM_INTERFACE_ENTRY(IMgaElementDecoratorEvents)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// Attributes
public:

// Operations
public:
	void SetView(CGMEView* view);
	void SetGuiAnnotator(CGuiAnnotator* guiAnnotator);

// Overrides
public:
// Implementation

public:
	~CAnnotatorEventSink();

protected:
	CGMEView*					m_view;
	CGuiAnnotator*				m_guiAnnotator;

public:
	STDMETHOD( Refresh )						( void );
	STDMETHOD( OperationCanceled )				( void );
	STDMETHOD( CursorChanged )					( /*[in]*/ LONG newCursorID );
	STDMETHOD( CursorRestored )					( void );

	STDMETHOD( LabelEditingStarted )			( /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelEditingFinished )			( /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelChanged )					( /*[in]*/ BSTR newLabel );
	STDMETHOD( LabelMovingStarted )				( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelMoving )					( /*[in]*/ LONG nSide, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelMovingFinished )			( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelMoved )						( /*[in]*/ LONG nType, /*[in]*/ LONG x, /*[in]*/ LONG y );
	STDMETHOD( LabelResizingStarted )			( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelResizing )					( /*[in]*/ LONG nSide, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelResizingFinished )			( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelResized )					( /*[in]*/ LONG nType, /*[in]*/ LONG cx, /*[in]*/ LONG cy );

	STDMETHOD( GeneralOperationStarted )		( /*[in]*/ ULONGLONG operationData );
	STDMETHOD( GeneralOperationFinished )		( /*[in]*/ ULONGLONG operationData );

	STDMETHOD( WindowMovingStarted )			( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( WindowMoving )					( /*[in]*/ LONG nSide, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( WindowMovingFinished )			( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( WindowMoved )					( /*[in]*/ LONG nType, /*[in]*/ LONG x, /*[in]*/ LONG y );

	STDMETHOD( WindowResizingStarted )			( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( WindowResizing )					( /*[in]*/ LONG nSide, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( WindowResizingFinished )			( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( WindowResized )					( /*[in]*/ LONG nType, /*[in]*/ LONG cx, /*[in]*/ LONG cy );
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANNOTATOREVENTSINK_H__2709B864_A353_4C26_9AF8_40948D2CBC1A__INCLUDED_)
