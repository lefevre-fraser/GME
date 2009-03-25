// AutoRouterPath.h : Declaration of the CAutoRouterPath

#pragma once
#include "resource.h"       // main symbols

//#include <oleauto.h>

#include "AutoRoute/ArHelper.h"

#include "AutoRouterPort.h"
#include "AutoRouterBox.h"

//#include "GME.h"
#include "gmelib.h"

#define ARPATH_EndOnDefault		0x0000
#define ARPATH_EndOnTop			0x0010
#define ARPATH_EndOnRight		0x0020
#define ARPATH_EndOnBottom		0x0040
#define ARPATH_EndOnLeft		0x0080
#define ARPATH_EndMask			(ARPATH_EndOnTop | ARPATH_EndOnRight | ARPATH_EndOnBottom | ARPATH_EndOnLeft)


#define ARPATH_StartOnDefault	0x0000
#define ARPATH_StartOnTop		0x0100
#define ARPATH_StartOnRight		0x0200
#define ARPATH_StartOnBottom	0x0400
#define ARPATH_StartOnLeft		0x0800
#define ARPATH_StartMask		(ARPATH_StartOnTop | ARPATH_StartOnRight | ARPATH_StartOnBottom | ARPATH_StartOnLeft)

#define ARPATH_HighLighted		0x0002		// attributes
#define ARPATH_Fixed			0x0001
#define ARPATH_Default			0x0000

#define ARPATHST_Connected		0x0001		// states
#define ARPATHST_Default		0x0000

typedef CList<CPoint, CPoint&>				CPointList;

class CAutoRouterGraph;
class CAutoRouterEdgeList;
class CAutoRouterPort;

// CAutoRouterPath

class ATL_NO_VTABLE CAutoRouterPath : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAutoRouterPath, &CLSID_AutoRouterPath>,
	public IDispatchImpl<IAutoRouterPath, &IID_IAutoRouterPath, &LIBID_GmeLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAutoRouterPath();

	//only the COM interface methods are public, thus we need lots of friends
	friend CAutoRouterGraph;
	friend CAutoRouterEdgeList;

DECLARE_REGISTRY_RESOURCEID(IDR_AUTOROUTERPATH)


BEGIN_COM_MAP(CAutoRouterPath)
	COM_INTERFACE_ENTRY(IAutoRouterPath)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease() 
	{		
		DeleteAll();
		this->SetOwner(NULL);
	}

private:
	void SetOwner(CComObjPtr<CAutoRouterGraph> graph);

	CComObjPtr<CAutoRouterGraph> owner;

// --- Ports (FOR EXTERNAL USE)

private:
	void SetStartPort(CComObjPtr<CAutoRouterPort> port);
	void SetEndPort(CComObjPtr<CAutoRouterPort> port);
	void ClearPorts();
	CComObjPtr<CAutoRouterPort> GetStartPort() const;
	CComObjPtr<CAutoRouterPort> GetEndPort() const;

private:
	CComObjPtr<CAutoRouterPort> startport;							// reference
	CComObjPtr<CAutoRouterPort> endport;							// reference

// --- Points (FOR EXTERNAL USE)

private:
	void AddTail(CPoint point);
	void DeleteAll();
	
	int HasNoPoint() const { return points.IsEmpty(); }
	int GetPointCount() const { return points.GetCount(); }

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	CPoint GetOutOfBoxStartPoint() const;
	CPoint GetOutOfBoxEndPoint() const;

	POSITION GetPointPosAt(CPoint point, int nearness = 0) const;
	POSITION GetEdgePosAt(CPoint point, int nearness = 0) const;

	void SimplifyTrivially();

	CPointList points;

// --- Edges

private:
	POSITION GetHeadEdge(CPoint& start, CPoint& end) const;
	POSITION GetTailEdge(CPoint& start, CPoint& end) const;
	void GetNextEdge(POSITION& pos, CPoint& start, CPoint& end) const;
	void GetPrevEdge(POSITION& pos, CPoint& start, CPoint& end) const;
	void GetEdge(POSITION pos, CPoint& start, CPoint& end) const;

	POSITION GetHeadEdgePtrs(CPoint*& start, CPoint*& end);
	POSITION GetTailEdgePtrs(CPoint*& start, CPoint*& end);
	void GetNextEdgePtrs(POSITION& pos, CPoint*& start, CPoint*& end);
	void GetPrevEdgePtrs(POSITION& pos, CPoint*& start, CPoint*& end);
	void GetEdgePtrs(POSITION pos, CPoint*& start, CPoint*& end);
	CPoint* GetStartPoint(POSITION pos);
	CPoint* GetEndPoint(POSITION pos);
 	CPoint* GetPointBeforeEdge(POSITION pos);
	CPoint* GetPointAfterEdge(POSITION pos);

	POSITION GetEdgePosBeforePoint(POSITION pos) const;
	POSITION GetEdgePosAfterPoint(POSITION pos) const;
	POSITION GetEdgePosForStartPoint(CPoint* startpoint);

	int IsEdgeHorizontal(POSITION pos);

// --- Data (FOR EXTERNAL USE)

private:
	CRect GetSurroundRect() const;

	int IsPathAt(CPoint point, int nearness = 0) const { return GetEdgePosAt(point, nearness) != NULL; }
	int IsPathClip(CRect rect) const;

	void SetAttributes(unsigned int attr);
	unsigned int GetAttributes() const { return attributes; }

	int IsFixed() const { return (attributes & ARPATH_Fixed) != 0; }
	int IsMoveable() const { return (attributes & ARPATH_Fixed) == 0; }
	int IsHighLighted() const { return (attributes & ARPATH_HighLighted) != 0; }

	int GetState() const { return state; };
	int IsConnected() const { return (state & ARPATHST_Connected) != 0; }

	EArDir GetEndDir() const;
	EArDir GetStartDir() const;

private:
	void SetState(int state);

	unsigned int attributes;
	int state;

private:

public:
	STDMETHOD(GetOwner)(IAutoRouterGraph** result);
	STDMETHOD(SetEndDir)(long arpath_end);
	STDMETHOD(SetStartDir)(long arpath_start);
	STDMETHOD(GetPointList)(SAFEARRAY **pArr);
	STDMETHOD(Destroy)();
};

OBJECT_ENTRY_AUTO(__uuidof(AutoRouterPath), CAutoRouterPath)
