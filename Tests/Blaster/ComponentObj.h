#if !defined(AFX_INTERPRETEROBJ_H__1DBDD345_023D_11D2_BBB3_0040051F7117__INCLUDED_)
#define AFX_INTERPRETEROBJ_H__1DBDD345_023D_11D2_BBB3_0040051F7117__INCLUDED_


#include "GMECOM.h"
#include "ComponentConfig.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// InterpreterObj.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComponentObj command target

class CComponentObj : public CCmdTarget
{

	DECLARE_DYNCREATE(CComponentObj)

	CComponentObj();           // protected constructor used by dynamic creation
	void RegisterActiveObject();
	unsigned long registeractiveobjectret;

// Attributes
public:

// Operations
public:
	IMgaComponent* GetInterface() { return &m_xComponent; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComponentObj)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CComponentObj();
	void UnregisterActiveObject();

	// Generated message map functions
	//{{AFX_MSG(CComponentObj)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CComponentObj)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CComponentObj)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	DECLARE_INTERFACE_MAP()
	BEGIN_INTERFACE_PART(Component, IMgaComponent)
		STDMETHODIMP Invoke(IMgaProject* gme, IMgaFCOs *models, long param);
		STDMETHODIMP Initialize(struct IMgaProject *);
		STDMETHODIMP Enable(VARIANT_BOOL newVal);
        STDMETHODIMP get_InteractiveMode(VARIANT_BOOL *enabled);
        
        STDMETHODIMP put_InteractiveMode(VARIANT_BOOL enabled);
        STDMETHODIMP get_ComponentType( componenttype_enum *t);
        STDMETHODIMP get_ComponentName(BSTR *pVal) { 
			*pVal = CComBSTR(COMPONENT_NAME).Detach();
			return S_OK; 
		};
        STDMETHODIMP get_Paradigm( BSTR *pVal) { 
			*pVal = CComBSTR(PARADIGMS).Detach();
			return S_OK; 
		};
	END_INTERFACE_PART(Component)

	BEGIN_INTERFACE_PART(VersionInfo, IMgaVersionInfo)
		STDMETHODIMP get_version(enum MgaInterfaceVersion *pVal);
	END_INTERFACE_PART(VersionInfo)

};


#define COMCLASS		CComponentObj::XComponent
#define COMPROLOGUE		METHOD_PROLOGUE(CComponentObj,Component)

class CPushRoutingFrame
{
protected:
	CFrameWnd* pOldRoutingFrame;
	_AFX_THREAD_STATE* pThreadState;

public:
	CPushRoutingFrame(CFrameWnd* pNewRoutingFrame)
	{
		pThreadState = AfxGetThreadState();
		pOldRoutingFrame = pThreadState->m_pRoutingFrame;
		pThreadState->m_pRoutingFrame = pNewRoutingFrame;
	}
	~CPushRoutingFrame()
	{ pThreadState->m_pRoutingFrame = pOldRoutingFrame; }
};



class CComponentReg
{
public:
	CComponentReg();

	CStringList paradigms;
	HRESULT RegisterParadigms();
	HRESULT UnregisterParadigms();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERPRETEROBJ_H__1DBDD345_023D_11D2_BBB3_0040051F7117__INCLUDED_)
