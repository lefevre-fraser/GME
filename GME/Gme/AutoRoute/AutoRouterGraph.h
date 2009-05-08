// AutoRouterGraph.h : Declaration of the CAutoRouterGraph

#pragma once
#include "resource.h"       // main symbols

#include "AutoRoute/ArHelper.h" 
#include "AutoRouterPath.h"
#include "AutoRouterEdge.h"
#include "AutoRouterPort.h"
#include "AutoRouterBox.h"

#include "GME.h"
#include "gmelib.h"

#include <vector>
#include <algorithm>


typedef std::vector<CComPtr<IAutoRouterBox> > CAutoRouterBoxList;
typedef std::vector<CComPtr<IAutoRouterPath> > CAutoRouterPathList;

typedef CList<CPoint, CPoint&> CPointList;

typedef CMap<IAutoRouterPath*, IAutoRouterPath*, CPointListPath*, CPointListPath* > CMapCARPath2CPointList;
typedef CMap<void*, void*, std::vector<CPoint>, std::vector<CPoint> > CMapCARObject2CPoints;

// Functions for CMapCARObject2CPoints and CMapCARPath2CPointList, see AutoRouterGraph.cpp
typedef CPointListPath* LPPointList;

template<>
BOOL AFXAPI CompareElements< LPPointList, LPPointList >
	 (const LPPointList* pElement1, const LPPointList* pElement2);

template<>
UINT AFXAPI HashKey< void* > (void* key);

typedef std::vector<CPoint> CARPoints;

template<>
BOOL AFXAPI CompareElements< CARPoints, CARPoints >
	 (const CARPoints* pElement1, const CARPoints* pElement2);
// End of functions for CMapCARObject2CPoints and CMapCARPath2CPointList, see AutoRouterGraph.cpp


// CAutoRouterGraph
class ATL_NO_VTABLE CAutoRouterGraph : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAutoRouterGraph, &CLSID_AutoRouterGraph>,
	public IDispatchImpl<IAutoRouterGraph, &IID_IAutoRouterGraph, &LIBID_GmeLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAutoRouterGraph();

DECLARE_REGISTRY_RESOURCEID(IDR_AUTOROUTERGRAPH)


BEGIN_COM_MAP(CAutoRouterGraph)
	COM_INTERFACE_ENTRY(IAutoRouterGraph)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct(void);
	void FinalRelease(void);

//box:

private:
	void Remove(CComPtr<IAutoRouterBox> box);

	void DeleteAllBoxes();
	const CAutoRouterBoxList& GetBoxList() const { return boxes; }
	int HasNoBox() const { return boxes.size() == 0; }
	int GetBoxCount() const { return boxes.size(); }

	void SetPortAttr(CComPtr<IAutoRouterPort> port, unsigned int attr);

	int IsRectClipBoxes(const CRect& rect) const;
	int IsLineClipBoxes(const CPoint& p1, const CPoint& p2) const;
	int CanBoxAt(const CRect& rect) const;
	CComPtr<IAutoRouterBox> GetBoxAt(const CPoint& point, int nearness = 0) const;

	CComPtr<IAutoRouterBox> AddAtomicPort(const CRect& rect, unsigned int attr);

//path:
	void Add(CComPtr<IAutoRouterPath> path);
	void Remove(CComPtr<IAutoRouterPath> path);

	void DeleteAllPaths();
	const CAutoRouterPathList& GetPathList() const { return paths; }
	int HasNoPath() const { return paths.size() == 0; }
	int GetPathCount() const { return paths.size(); }

	CAutoRouterEdge* GetListEdgeAt(const CPoint& point, int nearness = 0) const;

// --- Boxes && Paths (FOR EXTERNAL USE)

	int IsEmpty() const { return (boxes.size() == 0) && (paths.size() == 0); }

	CRect GetSurroundRect() const;

// --- Navigation

	CComPtr<IAutoRouterBox> GetOutOfBox(CPoint& point, RoutingDirection dir) const;
	CComPtr<IAutoRouterBox> GoToNextBox(CPoint& point, RoutingDirection dir, long stophere) const;
	CComPtr<IAutoRouterBox> GoToNextBox(CPoint& point, RoutingDirection dir, CPoint& stophere) const 
		{ return GoToNextBox(point, dir, GetPointCoord(stophere, dir)); }

	CComPtr<IAutoRouterBox> GoToNextBox(CPoint& point, RoutingDirection dir, long stop1, long stop2) const
		{ return GoToNextBox(point, dir, ChooseInDir(stop1, stop2, ReverseDir(dir))); }
	CComPtr<IAutoRouterBox> GoToNextBox(CPoint& point, RoutingDirection dir, CPoint& stop1, CPoint& stop2) const
		{ return GoToNextBox(point, dir, GetPointCoord(stop1, dir), GetPointCoord(stop2, dir)); }

	void GetLimitsOfEdge(const CPoint& start, const CPoint& end, long& min, long& max) const;
	int IsPointInBox(const CPoint& point) const { return GetBoxAt(point) != NULL; }

	bool Connect(CComPtr<IAutoRouterPath> path);
	bool Connect(CComPtr<IAutoRouterPath> path, CPoint& startpoint, CPoint& endpoint);

	void ConnectPoints(CPointListPath& ret, CPoint& startpoint, CPoint& endpoint, RoutingDirection hintstartdir, RoutingDirection hintenddir);

	void DisconnectAll();
	void Disconnect(CComPtr<IAutoRouterPath> path);

	void DisconnectPathsClipping(const CRect& rect);
	void DisconnectPathsFrom(CComPtr<IAutoRouterBox> box);
	void DisconnectPathsFrom(CComPtr<IAutoRouterPort> port);

// --- Edges

	void AddSelfEdges(void);
	void AddEdges(CComPtr<IAutoRouterGraph> graph);
	void AddEdges(CComPtr<IAutoRouterBox> box);
	void AddEdges(CComPtr<IAutoRouterPort> port);
	bool AddEdges(CComPtr<IAutoRouterPath> path);
	void DeleteEdges(CComPtr<IUnknown> object);

	void AddAllEdges();
	void DeleteAllEdges();

	void AddBoxAndPortEdges(CComPtr<IAutoRouterBox> box);
	void DeleteBoxAndPortEdges(CComPtr<IAutoRouterBox> box);

	CAutoRouterEdgeList& GetEdgeList(bool ishorizontal);

	CAutoRouterEdgeList horizontal;
	CAutoRouterEdgeList vertical;

// --- Path && Edges

	int CanDeleteTwoEdgesAt(CComPtr<IAutoRouterPath> path, CPointListPath& points, POSITION pos) const;
	void DeleteTwoEdgesAt(CComPtr<IAutoRouterPath> path, CPointListPath& points, POSITION pos);
	void DeleteSamePointsAt(CComPtr<IAutoRouterPath> path, CPointListPath& points, POSITION pos);
	int SimplifyPaths();
	void CenterStairsInPathPoints(CComPtr<IAutoRouterPath> path, RoutingDirection hintstartdir, RoutingDirection hintenddir);
	void SimplifyPathPoints(CComPtr<IAutoRouterPath> path);
	void ConnectAllDisconnectedPaths();
	bool IsEdgeFixed(CComPtr<IAutoRouterPath> path, const CPoint& startpoint, const CPoint& endpoint);

public:
	STDMETHOD(CreateBox)(IAutoRouterBox** result);
	STDMETHOD(AddBox)(IAutoRouterBox* box);
	STDMETHOD(DeleteBox)(IAutoRouterBox* box);
	STDMETHOD(ShiftBoxBy)(IAutoRouterBox* box, long sizeX, long sizeY);

	STDMETHOD(AutoRoute)(long aspect, long* result);
	STDMETHOD(DeletePath)(IAutoRouterPath* path);
	STDMETHOD(DeleteAll)();
	STDMETHOD(GetPathAt)(long pointX, long pointY, long nearness, IAutoRouterPath** result);
	STDMETHOD(AddPath)(VARIANT_BOOL isAutoRouted, IAutoRouterPort* startport,  IAutoRouterPort* endport, IAutoRouterPath** result);
	STDMETHOD(IsEdgeFixed)(IAutoRouterPath* path, long startX, long startY, long endX, long endY, VARIANT_BOOL* result);

	STDMETHOD(GetSelfPoints)(long* p1x, long* p1y, long* p2x, long* p2y, long* p3x, long* p3y, long* p4x, long* p4y);

	STDMETHOD(Destroy)();

private:
	CAutoRouterBoxList boxes;
	CAutoRouterPathList paths;

	std::vector<CPoint> selfpoints;
	void CalculateSelfPoints();

	// Helper stores and container to overcome CPoint pointer distributions
	CMapCARPath2CPointList arPathPointsCache;
	CMapCARObject2CPoints arObjectsPointsCache;
	void EmptyPointsCache(void);
	bool UpdatePathPointsFromCache(CComPtr<IAutoRouterPath> path, bool modifyOrSet = true);
	bool SetPathPointsFromCache(CComPtr<IAutoRouterPath> path);
	bool UpdatePaths(void);

	void GetPointList(CComPtr<IAutoRouterPath> path, CPointListPath& pointList) const;
	bool UpdatePoints(CComPtr<IAutoRouterPath> path, const CPointListPath& pointList, bool modifyOrSet);

// --- Debug

#ifdef _DEBUG
public:
	virtual void AssertValid() const;
	void AssertValidBox(CComPtr<IAutoRouterBox> box) const;
	void AssertValidPath(CComPtr<IAutoRouterPath> path) const;
	void DumpPaths(int pos, int c);
	void DumpEdgeLists(void);
#endif
};

OBJECT_ENTRY_AUTO(__uuidof(AutoRouterGraph), CAutoRouterGraph)
