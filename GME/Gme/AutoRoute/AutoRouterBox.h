// AutoRouterBox.h : Declaration of the CAutoRouterBox

#pragma once
#include "resource.h"       // main symbols



#include "AutoRoute/ArHelper.h"

#define ED_MAXCOORD		100000
#define ED_MINCOORD		0
#define ED_SMALLGAP		15

class CAutoRouterPort;
class CAutoRouterGraph;
class CAutoRouterEdgeList;
class CAutoRouterPath;

#include "AutoRouterPort.h"
#include "AutoRouterGraph.h"

#include "GME.h"
#include "gmelib.h"

#include <vector>
typedef std::vector<CComPtr<IAutoRouterPort> > CAutoRouterPortList;

// CAutoRouterBox

class ATL_NO_VTABLE CAutoRouterBox : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAutoRouterBox, &CLSID_AutoRouterBox>,
	public IDispatchImpl<IAutoRouterBox, &IID_IAutoRouterBox, &LIBID_GmeLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAutoRouterBox();

DECLARE_REGISTRY_RESOURCEID(IDR_AUTOROUTERBOX)


BEGIN_COM_MAP(CAutoRouterBox)
	COM_INTERFACE_ENTRY(IAutoRouterBox)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct(void);
	void FinalRelease(void);

private:
	void CalculateSelfPoints();
	void DeleteAllPorts();

public:
	STDMETHOD(GetOwner)(IAutoRouterGraph** result);
	STDMETHOD(HasOwner)(VARIANT_BOOL* result);
	STDMETHOD(SetOwner)(IAutoRouterGraph* graph);

	STDMETHOD(CreatePort)(IAutoRouterPort** result);
	STDMETHOD(HasNoPort)(VARIANT_BOOL* result);
	STDMETHOD(GetPortCount)(long* result);
	STDMETHOD(IsAtomic)(VARIANT_BOOL* result);
	STDMETHOD(AddPort)(IAutoRouterPort* port);
	STDMETHOD(DeletePort)(IAutoRouterPort* port);
	STDMETHOD(GetPortList)(SAFEARRAY** pArr);

	STDMETHOD(GetRect)(long* p1, long* p2, long* p3, long* p4);
	STDMETHOD(IsRectEmpty)(VARIANT_BOOL* result);
	STDMETHOD(SetRect)(long p1, long p2, long p3, long p4);
	STDMETHOD(SetRectByPoint)(long px, long py);
	STDMETHOD(ShiftBy)(long offsetx, long offsety);
	STDMETHOD(GetSelfPoints)(long* p1x, long* p1y, long* p2x, long* p2y, long* p3x, long* p3y, long* p4x, long* p4y);

	STDMETHOD(IsBoxAt)(long px, long py, long nearness, VARIANT_BOOL* result);
	STDMETHOD(IsBoxClip)(long p1, long p2, long p3, long p4, VARIANT_BOOL* result);
	STDMETHOD(IsBoxIn)(long p1, long p2, long p3, long p4, VARIANT_BOOL* result);

	STDMETHOD(Destroy)();

private:
	CRect rect;
	CPoint selfpoints[4];
	int atomic;

	CAutoRouterPortList ports;
	CComPtr<IAutoRouterGraph> owner;

// --- Debug

#ifdef _DEBUG
public:
	virtual void AssertValid() const;
	void AssertValidPort(CComPtr<IAutoRouterPort> port) const;
#endif
};

OBJECT_ENTRY_AUTO(__uuidof(AutoRouterBox), CAutoRouterBox)
