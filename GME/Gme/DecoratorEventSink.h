//################################################################################################
//
// Decorator Event Sink implementation
//	DecoratorEventSink.h
//
//################################################################################################

#if !defined(AFX_DECORATOREVENTSINK_H__EB95C56D_04BC_47c9_A71B_305184F5FC44__INCLUDED_)
#define AFX_DECORATOREVENTSINK_H__EB95C56D_04BC_47c9_A71B_305184F5FC44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "mga.h"
#include "MgaDecorator.h"
#include "GmeLib.h"
#include "resource.h"


class CGMEView;
class CGuiObject;

//################################################################################################
//
// CLASS : CDecoratorEventSink
//
//################################################################################################

class CDecoratorEventSink : public CCmdTarget
{
	DECLARE_DYNCREATE(CDecoratorEventSink)

	CDecoratorEventSink();           // protected constructor used by dynamic creation
public:


// Attributes
public:

// Operations
public:
	void SetView(CGMEView* view) { m_view = view; }
	void SetGuiObject(CGuiObject* guiObject) { m_guiObject = guiObject; }
	HRESULT QuerySinkInterface(void** ppv);

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDecoratorEventSink)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation

public:
	~CDecoratorEventSink();

protected:
	CGMEView*					m_view;
	CGuiObject*					m_guiObject;

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CEventSink)

	// Generated message map functions
	//{{AFX_MSG(CDecoratorEventSink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CDecoratorEventSink)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

public:
// Native COM interfaces - peter
	DECLARE_INTERFACE_MAP()

	BEGIN_INTERFACE_PART(EventSink, IMgaNewDecoratorEvents)
		STDMETHOD( Refresh )						( void );
		STDMETHOD( OperationCanceled )				( void );
		STDMETHOD( CursorChanged )					( /*[in]*/ LONG newCursorID );
		STDMETHOD( CursorRestored )					( void );

		STDMETHOD( TitleEditingStarted )			( /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
		STDMETHOD( TitleEditingFinished )			( /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
		STDMETHOD( TitleChanged )					( /*[in]*/ BSTR newTitle );
		STDMETHOD( TitleMovingStarted )				( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
		STDMETHOD( TitleMoving )					( /*[in]*/ LONG nSide, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
		STDMETHOD( TitleMovingFinished )			( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
		STDMETHOD( TitleMoved )						( /*[in]*/ LONG nType, /*[in]*/ LONG x, /*[in]*/ LONG y );
		STDMETHOD( TitleResizingStarted )			( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
		STDMETHOD( TitleResizing )					( /*[in]*/ LONG nSide, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
		STDMETHOD( TitleResizingFinished )			( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
		STDMETHOD( TitleResized )					( /*[in]*/ LONG nType, /*[in]*/ LONG cx, /*[in]*/ LONG cy );

		STDMETHOD( WindowMovingStarted )			( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
		STDMETHOD( WindowMoving )					( /*[in]*/ LONG nSide, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
		STDMETHOD( WindowMovingFinished )			( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
		STDMETHOD( WindowMoved )					( /*[in]*/ LONG nType, /*[in]*/ LONG x, /*[in]*/ LONG y );

		STDMETHOD( WindowResizingStarted )			( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
		STDMETHOD( WindowResizing )					( /*[in]*/ LONG nSide, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
		STDMETHOD( WindowResizingFinished )			( /*[in]*/ LONG nType, /*[in]*/ LONG left, /*[in]*/ LONG top, /*[in]*/ LONG right, /*[in]*/ LONG bottom );
		STDMETHOD( WindowResized )					( /*[in]*/ LONG nType, /*[in]*/ LONG cx, /*[in]*/ LONG cy );

		STDMETHOD( GeneralOperationStarted )		( /*[in]*/ ULONGLONG operationData );
		STDMETHOD( GeneralOperationFinished )		( /*[in]*/ ULONGLONG operationData );
	END_INTERFACE_PART(EventSink)
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DECORATOREVENTSINK_H__EB95C56D_04BC_47c9_A71B_305184F5FC44__INCLUDED_)
