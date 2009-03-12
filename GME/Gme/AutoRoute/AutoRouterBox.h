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
using namespace std;
typedef vector<CComObjPtr<CAutoRouterPort> > CAutoRouterPortList;
//typedef CTypedPtrList<CObList, CAutoRouterPort*>	CAutoRouterPortList;

// CAutoRouterBox

class ATL_NO_VTABLE CAutoRouterBox : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAutoRouterBox, &CLSID_AutoRouterBox>,
	public IDispatchImpl<IAutoRouterBox, &IID_IAutoRouterBox, &LIBID_GmeLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAutoRouterBox();

	//only the COM interface methods are public, thus we need lots of friends
	friend CAutoRouterGraph;
	friend CAutoRouterEdgeList;
	friend CAutoRouterPath;

DECLARE_REGISTRY_RESOURCEID(IDR_AUTOROUTERBOX)


BEGIN_COM_MAP(CAutoRouterBox)
	COM_INTERFACE_ENTRY(IAutoRouterBox)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease() 
	{
	}

private:
	void DeleteAllPorts();
	const CAutoRouterPortList& GetPortList() const { return ports; }
	int HasNoPort() const { return ports.size()==0; }
	int GetPortCount() const { return ports.size(); }

	int IsAtomic() const { return atomic; }

	CRect GetRect() const { return rect; }
	int IsRectEmpty() const { return rect.IsRectEmpty(); }

	int IsBoxAt(CPoint point, int nearness = 0) const { return IsPointIn(point, rect, nearness); }
	int IsBoxClip(CRect r) const { return IsRectClip(rect, r); }
	int IsBoxIn(CRect r) const { return IsRectIn(rect, r); }

	void SetRect(CPoint point) { ShiftBy(point - rect.TopLeft()); }
	void ShiftBy(CSize offset);

	void CalculateSelfPoints();

	void SetOwner(CComObjPtr<CAutoRouterGraph> o);

public:
	STDMETHOD(GetOwner)(IAutoRouterGraph** result);
	STDMETHOD(CreatePort)(IAutoRouterPort** result);
	STDMETHOD(Add)(IAutoRouterPort* port);
	STDMETHOD(Delete)(IAutoRouterPort* port);
	STDMETHOD(SetRect)(long p1, long p2, long p3, long p4);
	STDMETHOD(Destroy)();

private:
	CRect rect;
	CPoint selfpoints[4];
	int atomic;

	CAutoRouterPortList ports;
	CComObjPtr<CAutoRouterGraph> owner;

};

OBJECT_ENTRY_AUTO(__uuidof(AutoRouterBox), CAutoRouterBox)
