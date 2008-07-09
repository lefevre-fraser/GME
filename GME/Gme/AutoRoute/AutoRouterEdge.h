#pragma once

#include "AutoRouterPort.h"

class CAutoRouterBox;
class CAutoRouterPort;
class CAutoRouterPath;
class CAutoRouterGraph;


// --------------------------- SArEdge

class CAutoRouterEdgeList;

struct SAutoRouterEdge
{
	friend CAutoRouterEdgeList;
	friend CAutoRouterGraph;

private:

	CComObjPtr<IUnknown> owner;
	CPoint* startpoint_prev;
	CPoint* startpoint;
	CPoint* endpoint;
	CPoint* endpoint_next;

	float position_y;
	long position_x1;
	long position_x2;
	int bracket_closing : 1;
	int bracket_opening : 1;
	
	SAutoRouterEdge* order_next;
	SAutoRouterEdge* order_prev;

	long section_x1;
	long section_x2;
	SAutoRouterEdge* section_next;
	SAutoRouterEdge* section_down;

	unsigned int edge_fixed : 1;
	unsigned int edge_canpassed : 1;

	SAutoRouterEdge* block_prev;
	SAutoRouterEdge* block_next;
	SAutoRouterEdge* block_trace;

	SAutoRouterEdge* closest_prev;
	SAutoRouterEdge* closest_next;
};

class CAutoRouterEdgeList
{
private:
	CAutoRouterEdgeList(int ishorizontal);
	~CAutoRouterEdgeList();

	friend CAutoRouterGraph;

private:
	void SetOwner(CComObjPtr<CAutoRouterGraph> owner);
	CComObjPtr<CAutoRouterGraph> owner;

// --- Edges

private:
	SAutoRouterEdge* CreateEdge() const;
	void AddEdges(CComObjPtr<CAutoRouterPath> path);
	void AddEdges(CComObjPtr<CAutoRouterBox> box);
	void AddEdges(CComObjPtr<CAutoRouterPort> port);
	void AddEdges(CComObjPtr<CAutoRouterGraph> graph);
	void DeleteEdges(CComObjPtr<IUnknown> object);
	void DeleteAllEdges();

	int IsEmpty() const;

private:
	int ishorizontal;

private:
	SAutoRouterEdge* GetEdge(CPoint* startpoint, CPoint* endpoint) const;
	SAutoRouterEdge* GetEdgeAt(CPoint point, int nearness = 0) const;

// --- Position

private:
	long Position_GetRealY(const SAutoRouterEdge* edge) const;
	void Position_SetRealY(SAutoRouterEdge* edge, long y) const;
	void Position_GetRealX(const SAutoRouterEdge* edge, long& x1, long& x2) const;
	void Position_GetRealO(const SAutoRouterEdge* edge, long& o1, long& o2) const;

	void Position_LoadY(SAutoRouterEdge* edge) const;
	void Position_LoadB(SAutoRouterEdge* edge) const;
	void PositionAll_StoreY() const;

	void PositionAll_LoadX() const;

#ifdef _DEBUG
private:
	void AssertValidPositions() const;
#endif

// --- Order

private:
	void Con_Order();
	void Des_Order();

private:
	void InsertBefore(SAutoRouterEdge* edge, SAutoRouterEdge* before);
	void InsertAfter(SAutoRouterEdge* edge, SAutoRouterEdge* after);
	void InsertLast(SAutoRouterEdge* edge);
	void Insert(SAutoRouterEdge* edge);
	void Remove(SAutoRouterEdge* edge);
	void Delete(SAutoRouterEdge* edge);

	SAutoRouterEdge* SlideButNotPassEdges(SAutoRouterEdge* edge, float y);

private:
	SAutoRouterEdge* order_first;
	SAutoRouterEdge* order_last;

#ifdef _DEBUG
private:
	void AssertValidOrder() const;
#endif

// --- Section

private:
	void Con_Section();
	void Des_Section();

private:
	void Section_Reset();
	void Section_BeginScan(SAutoRouterEdge* blocker);
	int Section_HasBlockedEdge();
	SAutoRouterEdge* Section_GetBlockedEdge();
	int Section_IsImmediate();

private:
	SAutoRouterEdge* section_first;
	SAutoRouterEdge* section_blocker;
	SAutoRouterEdge** section_ptr2blocked;

#ifdef _DEBUG
public:
	void Section_AssertLevel(SAutoRouterEdge* level, long x1, long x2) const;
	void AssertValidSection() const;
	void AssertSectionReady() const;
#endif

// --- Bracket

private:
	int Bracket_IsClosing(const SAutoRouterEdge* edge) const;
	int Bracket_IsOpening(const SAutoRouterEdge* edge) const;
	int Bracket_IsSmallGap(const SAutoRouterEdge* blocked, const SAutoRouterEdge* blocker) const;

	int Bracket_ShouldBeSwitched(const SAutoRouterEdge* edge, const SAutoRouterEdge* next) const;

// --- Block

private:
	int Block_PushBackward(SAutoRouterEdge* blocked, SAutoRouterEdge* blocker);
	int Block_PushForward(SAutoRouterEdge* blocked, SAutoRouterEdge* blocker);
	int Block_ScanForward();
	int Block_ScanBackward();

	int Block_SwitchWrongs();
};
