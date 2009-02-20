// AutoRouterGraph.h : Declaration of the CAutoRouterGraph

#pragma once
#include "resource.h"       // main symbols

#include "GME.h"
#include "gmelib.h"
#include "AutoRoute/ArHelper.h" 
#include "AutoRouterPath.h"
#include "AutoRouterEdge.h"
#include "AutoRouterPort.h"
#include "AutoRouterBox.h"

class CAutoRouterPort;
class CAutoRouterBox;
class CAutoRouterPath;
class CAutoRouterEdgeList;
struct SAutoRouterEdge;

#include <vector>
#include <algorithm>
using namespace std;
typedef vector<CComObjPtr<CAutoRouterBox> > CAutoRouterBoxList;
typedef vector<CComObjPtr<CAutoRouterPath> > CAutoRouterPathList;

typedef CList<CPoint, CPoint&>				CPointList;

// CAutoRouterGraph
class ATL_NO_VTABLE CAutoRouterGraph : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAutoRouterGraph, &CLSID_AutoRouterGraph>,
	public IDispatchImpl<IAutoRouterGraph, &IID_IAutoRouterGraph, &LIBID_GmeLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CAutoRouterGraph();

	//only the COM interface methods are public, thus we need lots of friends
	friend CAutoRouterEdgeList;

DECLARE_REGISTRY_RESOURCEID(IDR_AUTOROUTERGRAPH)


BEGIN_COM_MAP(CAutoRouterGraph)
	COM_INTERFACE_ENTRY(IAutoRouterGraph)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		horizontal.SetOwner(this);
		vertical.SetOwner(this);

		CalculateSelfPoints();
		AddEdges(this);

		return S_OK;
	}

	void FinalRelease() 
	{
	}

//box:

private:
	void Remove(CComObjPtr<CAutoRouterBox> box);

	void DeleteAllBoxes();
	const CAutoRouterBoxList& GetBoxList() const { return boxes; }
	int HasNoBox() const { return boxes.size()==0; }
	int GetBoxCount() const { return boxes.size(); }

	void SetPortAttr(CComObjPtr<CAutoRouterPort> port, unsigned int attr);

	int IsRectClipBoxes(CRect rect) const;
	int IsLineClipBoxes(CPoint p1, CPoint p2) const;
	int CanBoxAt(CRect rect) const;

	CComObjPtr<CAutoRouterBox> AddAtomicPort(CRect rect, unsigned int attr);

//path:
	CComObjPtr<CAutoRouterPath> CreatePath() const;
	void Add(CComObjPtr<CAutoRouterPath> path);
	void Remove(CComObjPtr<CAutoRouterPath> path);

	void DeleteAllPaths();
	const CAutoRouterPathList& GetPathList() const { return paths; }
	int HasNoPath() const { return paths.size()==0; }
	int GetPathCount() const { return paths.size(); }

	SAutoRouterEdge* GetListEdgeAt(CPoint point, int nearness = 0) const;

	//CComObjPtr<CAutoRouterPath> AddPath(const CPointList& points, unsigned int attr);
	//CComObjPtr<CAutoRouterPath> AddPath(CPoint startpoint, CPoint endpoint);

// --- Boxes && Paths (FOR EXTERNAL USE)

private:
	int IsEmpty() const { return (boxes.size()==0) && (paths.size()==0); }

	CRect GetSurroundRect() const;

// --- Navigation

private:
	CComObjPtr<CAutoRouterBox> GetOutOfBox(CPoint& point, EArDir dir) const;

	CComObjPtr<CAutoRouterBox> GoToNextBox(CPoint& point, EArDir dir, long stophere) const;
	CComObjPtr<CAutoRouterBox> GoToNextBox(CPoint& point, EArDir dir, CPoint stophere) const 
		{ return GoToNextBox(point, dir, GetPointCoord(stophere, dir)); }

	CComObjPtr<CAutoRouterBox> GoToNextBox(CPoint& point, EArDir dir, long stop1, long stop2) const
		{ return GoToNextBox(point, dir, ChooseInDir(stop1, stop2,ReverseDir(dir))); }
	CComObjPtr<CAutoRouterBox> GoToNextBox(CPoint& point, EArDir dir, CPoint stop1, CPoint stop2) const
		{ return GoToNextBox(point, dir, GetPointCoord(stop1, dir), GetPointCoord(stop2, dir)); }

	void GetLimitsOfEdge(CPoint start, CPoint end, long& min, long& max) const;

private:
	void Connect(CComObjPtr<CAutoRouterPath> path);
	void Connect(CComObjPtr<CAutoRouterPath> path, CPoint startpoint, CPoint endpoint);

	void ConnectPoints(CPointList& ret, CPoint startpoint, CPoint endpoint, EArDir hintstartdir, EArDir hintenddir);

	void DisconnectAll();
	void Disconnect(CComObjPtr<CAutoRouterPath> path);

	void DisconnectPathsClipping(CRect rect);
	void DisconnectPathsFrom(CComObjPtr<CAutoRouterBox> box);
	void DisconnectPathsFrom(CComObjPtr<CAutoRouterPort> port);

// --- Edges

private:
	void AddEdges(CComObjPtr<CAutoRouterGraph> graph) { horizontal.AddEdges(graph); vertical.AddEdges(graph);}
	void AddEdges(CComObjPtr<CAutoRouterBox> box) { horizontal.AddEdges(box); vertical.AddEdges(box);}
	void AddEdges(CComObjPtr<CAutoRouterPort> port) { horizontal.AddEdges(port); vertical.AddEdges(port); }
	void AddEdges(CComObjPtr<CAutoRouterPath> path) { horizontal.AddEdges(path); vertical.AddEdges(path); }
	void DeleteEdges(CComObjPtr<IUnknown> object) { horizontal.DeleteEdges(object); vertical.DeleteEdges(object); }

	void AddAllEdges();
	void DeleteAllEdges() {horizontal.DeleteAllEdges(); vertical.DeleteAllEdges(); }

	void AddBoxAndPortEdges(CComObjPtr<CAutoRouterBox> box);
	void DeleteBoxAndPortEdges(CComObjPtr<CAutoRouterBox> box);

	 CAutoRouterEdgeList& GetEdgeList(int ishorizontal) { return ishorizontal ? horizontal : vertical; }

private:

	 CAutoRouterEdgeList horizontal;
	 CAutoRouterEdgeList vertical;

// --- Path && Edges

private:
	int CanDeleteTwoEdgesAt(CComObjPtr<CAutoRouterPath> path, POSITION pos);
	void DeleteTwoEdgesAt(CComObjPtr<CAutoRouterPath> path, POSITION pos);
	void DeleteSamePointsAt(CComObjPtr<CAutoRouterPath> path, POSITION pos);
	int SimplifyPaths();
	void CenterStairsInPathPoints(CComObjPtr<CAutoRouterPath> path);
	void SimplifyPathPoints(CComObjPtr<CAutoRouterPath> path);
	void ConnectAllDisconnectedPaths();

public:
	STDMETHOD(CreateBox)(IAutoRouterBox** result);
	STDMETHOD(Add)(IAutoRouterBox* box);
	STDMETHOD(DeleteBox)(IAutoRouterBox* box);
	STDMETHOD(ShiftBy)(IAutoRouterBox* box, long sizeX, long sizeY);
	STDMETHOD(AutoRoute)(long* result);
	STDMETHOD(DeletePath)( IAutoRouterPath* path);
	STDMETHOD(DeleteAll)();
	STDMETHOD(Destroy)();
	STDMETHOD(GetPathAt)(long pointX, long pointY, long nearness, IAutoRouterPath** result);
	STDMETHOD(AddPath)( IAutoRouterPort* startport,  IAutoRouterPort* endport, IAutoRouterPath** result);

private:
	CAutoRouterBoxList boxes;
	CAutoRouterPathList paths;


private:
	void CalculateSelfPoints();

	CPoint selfpoints[4];
};

OBJECT_ENTRY_AUTO(__uuidof(AutoRouterGraph), CAutoRouterGraph)
