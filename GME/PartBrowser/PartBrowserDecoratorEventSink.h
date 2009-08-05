//################################################################################################
//
// PartBrowser Decorator Event Sink implementation for PartBrowser
//	PartBrowserDecoratorEventSink.h
//
//################################################################################################

#if !defined(AFX_PARTBROWSERDECORATOREVENTSINK_H__9829B754_62D2_4BAD_A70D_E5F22160A529__INCLUDED_)
#define AFX_PARTBROWSERDECORATOREVENTSINK_H__9829B754_62D2_4BAD_A70D_E5F22160A529__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "mga.h"
#include "MgaDecorator.h"
#include "PartBrowseridl.h"
#include "resource.h"


//################################################################################################
//
// CLASS : CPartBrowserDecoratorEventSink
//
//################################################################################################

class CPartBrowserDecoratorEventSink :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPartBrowserDecoratorEventSink, &CLSID_PartBrowserDecoratorEventSink>,
	public ISupportErrorInfoImpl<&IID_IMgaElementDecoratorEvents>,
	public IMgaElementDecoratorEvents
{
protected:
	CPartBrowserDecoratorEventSink();           // protected constructor used by dynamic creation

public:
DECLARE_REGISTRY_RESOURCEID(IDR_DECORATOREVENTSINK)
DECLARE_NOT_AGGREGATABLE(CPartBrowserDecoratorEventSink)

BEGIN_COM_MAP(CPartBrowserDecoratorEventSink)
	COM_INTERFACE_ENTRY(IMgaElementDecoratorEvents)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

// Attributes
public:

// Operations
public:

// Overrides
public:
// Implementation

public:
	~CPartBrowserDecoratorEventSink();

protected:

public:
	STDMETHOD( Refresh )						( /*[in]*/ refresh_mode_enum refreshMode );
	STDMETHOD( OperationCanceled )				( void );
	STDMETHOD( CursorChanged )					( /*[in]*/ LONG newCursorID );
	STDMETHOD( CursorRestored )					( void );

	STDMETHOD( LabelEditingStarted )			( /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelEditingFinished )			( /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelChanged )					( /*[in]*/ BSTR newLabel );
	STDMETHOD( LabelMovingStarted )				( /*[in]*/ LONG nFlags, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelMoving )					( /*[in]*/ LONG nFlags, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelMovingFinished )			( /*[in]*/ LONG nFlags, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelMoved )						( /*[in]*/ LONG nFlags, /*[in]*/ LONG x, /*[in]*/ LONG y );
	STDMETHOD( LabelResizingStarted )			( /*[in]*/ LONG nFlags, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelResizing )					( /*[in]*/ LONG nFlags, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelResizingFinished )			( /*[in]*/ LONG nFlags, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( LabelResized )					( /*[in]*/ LONG nFlags, /*[in]*/ LONG cx, /*[in]*/ LONG cy );

	STDMETHOD( GeneralOperationStarted )		( /*[in]*/ ULONGLONG operationData );
	STDMETHOD( GeneralOperationFinished )		( /*[out]*/ ULONGLONG* operationData );

	STDMETHOD( WindowMovingStarted )			( /*[in]*/ LONG nFlags, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( WindowMoving )					( /*[in]*/ LONG nFlags, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( WindowMovingFinished )			( /*[in]*/ LONG nFlags, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( WindowMoved )					( /*[in]*/ LONG nFlags, /*[in]*/ LONG x, /*[in]*/ LONG y );

	STDMETHOD( WindowResizingStarted )			( /*[in]*/ LONG nFlags, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( WindowResizing )					( /*[in]*/ LONG nFlags, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( WindowResizingFinished )			( /*[in]*/ LONG nFlags, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
	STDMETHOD( WindowResized )					( /*[in]*/ LONG nFlags, /*[in]*/ LONG cx, /*[in]*/ LONG cy );
};

OBJECT_ENTRY_AUTO(__uuidof(PartBrowserDecoratorEventSink), CPartBrowserDecoratorEventSink) 

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARTBROWSERDECORATOREVENTSINK_H__9829B754_62D2_4BAD_A70D_E5F22160A529__INCLUDED_)
