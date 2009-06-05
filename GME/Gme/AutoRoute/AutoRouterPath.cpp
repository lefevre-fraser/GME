// AutoRouterPath.cpp : Implementation of CAutoRouterPath

#include "stdafx.h"
#include "AutoRouterPath.h"
#include "AutoRouterBox.h"
#include "AutoRouterGraph.h"
#include "AutoRouterPort.h"


void InitCustomPathData(CustomPathData& pathData)
{
	pathData.version					= CONNECTIONCUSTOMIZATIONDATAVERSION;
	pathData.aspect						= 0;
	pathData.edgeIndex					= 0;
	pathData.edgeCount					= 0;
	pathData.type						= SimpleEdgeDisplacement;
	pathData.horizontalOrVerticalEdge	= true;
	pathData.x							= 0;
	pathData.y							= 0;
	pathData.numOfExtraLongData			= 0;
	pathData.l1							= 0;
	pathData.l2							= 0;
	pathData.l3							= 0;
	pathData.l4							= 0;
	pathData.numOfExtraDoubleData		= 0;
	pathData.d1							= 0.0;
	pathData.d2							= 0.0;
	pathData.d3							= 0.0;
	pathData.d4							= 0.0;
	pathData.d5							= 0.0;
	pathData.d6							= 0.0;
	pathData.d7							= 0.0;
	pathData.d8							= 0.0;
}

void CopyCustomPathData(const CustomPathData& src, CustomPathData& dst)
{
	dst.version						= src.version;
	dst.aspect						= src.aspect;
	dst.edgeIndex					= src.edgeIndex;
	dst.edgeCount					= src.edgeCount;
	dst.type						= src.type;
	dst.horizontalOrVerticalEdge	= src.horizontalOrVerticalEdge;
	dst.x							= src.x;
	dst.y							= src.y;
	dst.numOfExtraLongData			= src.numOfExtraLongData;
	dst.l1							= src.l1;
	dst.l2							= src.l2;
	dst.l3							= src.l3;
	dst.l4							= src.l4;
	dst.numOfExtraDoubleData		= src.numOfExtraDoubleData;
	dst.d1							= src.d1;
	dst.d2							= src.d2;
	dst.d3							= src.d3;
	dst.d4							= src.d4;
	dst.d5							= src.d5;
	dst.d6							= src.d6;
	dst.d7							= src.d7;
	dst.d8							= src.d8;
}


// CAutoRouterPath implementation

CAutoRouterPath::CAutoRouterPath():
	owner(NULL),
	startport(NULL),
	endport(NULL),
	attributes(ARPATH_Default),
	state(ARPATHST_Default),
	isAutoRoutingOn(true)
{
}

CAutoRouterPath::~CAutoRouterPath()
{
	DeleteAll();
	this->SetOwner(NULL);
}

// --- Points

POSITION CAutoRouterPath::GetPointPosAt(const CPoint& point, int nearness) const
{
	POSITION pos = points.GetHeadPosition();
	while( pos != NULL )
	{
		POSITION oldpos = pos;
		if( IsPointNear(points.GetNext(pos), point, nearness) )
			return oldpos;
	}
	
	return NULL;
}

POSITION CAutoRouterPath::GetEdgePosAt(const CPoint& point, int nearness) const
{
	CPoint a;
	CPoint b;

	POSITION pos = points.GetTailEdge(a, b);
	while( pos != NULL )
	{
		if( IsPointNearLine(point, a, b, nearness) )
			return pos;

		points.GetPrevEdge(pos, a, b);
	}

	return NULL;
}

bool CAutoRouterPath::IsConnected(void) const
{
	return (state & ARPATHST_Connected) != 0;
}

void CAutoRouterPath::AddTail(CPoint& p)
{
	ASSERT( !IsConnected() );
	points.AddTail(p);
}

void CAutoRouterPath::DeleteAll(void)
{
	points.RemoveAll();
	state = ARPATHST_Default;
}

bool CAutoRouterPath::HasNoPoint(void) const
{
	return points.IsEmpty() == TRUE;
}

long CAutoRouterPath::GetPointCount(void) const
{
	return points.GetCount();
}

CPoint CAutoRouterPath::GetStartPoint(void) const
{
	ASSERT( points.GetCount() >= 2 );

	return points.GetHead();
}

CPoint CAutoRouterPath::GetEndPoint(void) const
{
	ASSERT( points.GetCount() >= 2 );

	return points.GetTail();
}

CRect CAutoRouterPath::GetStartBox(void) const
{
	CAutoRouterBox* startbox = startport->GetOwner();
	return startbox->GetRect();
}

CRect CAutoRouterPath::GetEndBox(void) const
{
	CAutoRouterBox* endbox = endport->GetOwner();
	return endbox->GetRect();
}

CPoint CAutoRouterPath::GetOutOfBoxStartPoint(RoutingDirection hintDir) const
{
	const CRect startBoxRect = GetStartBox();

	ASSERT( hintDir != Dir_Skew );
	ASSERT( points.GetCount() >= 2 );
	POSITION pos = points.GetHeadPosition();
	CPoint p = points.GetNext(pos);
	RoutingDirection d = GetDir(points.GetAt(pos) - p);
	if (d == Dir_Skew)
		d = hintDir;
	ASSERT( IsRightAngle(d) );

	GetPointCoord(p, d) = GetRectOuterCoord(startBoxRect, d);
	ASSERT( points.GetAt(pos) == p || GetDir(points.GetAt(pos) - p) == d ); 

	return p;
}

CPoint CAutoRouterPath::GetOutOfBoxEndPoint(RoutingDirection hintDir) const
{
	const CRect endBoxRect = GetEndBox();

	ASSERT( hintDir != Dir_Skew );
	ASSERT( points.GetCount() >= 2 );
	POSITION pos = points.GetTailPosition();
	CPoint p = points.GetPrev(pos);
	RoutingDirection d = GetDir(points.GetAt(pos) - p);
	if (d == Dir_Skew)
		d = hintDir;
	ASSERT( IsRightAngle(d) );

	GetPointCoord(p, d) = GetRectOuterCoord(endBoxRect, d);
	ASSERT( points.GetAt(pos) == p || GetDir(points.GetAt(pos) - p) == d ); 

	return p;
}

void CAutoRouterPath::SimplifyTrivially(void)
{
	ASSERT( !IsConnected() );

	if( points.GetCount() <= 2 )
		return;
	
	POSITION pos = points.GetHeadPosition();

	POSITION pos1 = pos;
	ASSERT( pos1 != NULL );
	CPoint p1 = points.GetNext(pos);

	POSITION pos2 = pos;
	ASSERT( pos2 != NULL );
	CPoint p2 = points.GetNext(pos);

	RoutingDirection dir12 = GetDir(p2-p1);

	POSITION pos3 = pos;
	ASSERT( pos3 != NULL );
	CPoint p3 = points.GetNext(pos);

	RoutingDirection dir23 = GetDir(p3-p2); 

	for(;;)
	{
		if( dir12 == Dir_None || dir23 == Dir_None ||
			(dir12 != Dir_Skew && dir23 != Dir_Skew &&
			(dir12 == dir23 || dir12 == ReverseDir(dir23)) ) )
		{
			points.RemoveAt(pos2);
			dir12 = GetDir(p3-p1);
		}
		else
		{
			pos1 = pos2;
			p1 = p2;
			dir12 = dir23;
		}

		if( pos == NULL )
			return;

		pos2 = pos3;
		p2 = p3;

		pos3 = pos;
		p3 = points.GetNext(pos);

		dir23 = GetDir(p3-p2);
	}

#ifdef _DEBUG
	AssertValidPoints();
#endif
}

CPointListPath& CAutoRouterPath::GetPointList(void)
{
	return points;
}

void CAutoRouterPath::SetPoints(CPointListPath& pls)
{
	points.RemoveAll();
	POSITION pos = pls.GetHeadPosition();
	while( pos != NULL )
	{
		points.AddTail(pls.GetNext(pos));
	}
}

// --- Data

CRect CAutoRouterPath::GetSurroundRect(void) const
{
	CRect rect(INT_MAX,INT_MAX,INT_MIN,INT_MIN);

	POSITION pos = points.GetHeadPosition();
	while( pos != NULL )
	{
		CPoint point = points.GetNext(pos);

		rect.left = min(rect.left, point.x);
		rect.top = min(rect.top, point.y);
		rect.right = max(rect.right, point.x);
		rect.bottom = max(rect.bottom, point.y);
	}

	if( rect.left == INT_MAX || rect.top == INT_MAX ||
		rect.right == INT_MIN || rect.bottom == INT_MIN )
	{
		rect.SetRectEmpty();
	}

	return rect;
}

bool CAutoRouterPath::IsEmpty(void) const
{
	return points.IsEmpty() == TRUE;
}

bool CAutoRouterPath::IsPathAt(const CPoint& point, long nearness) const
{
	return GetEdgePosAt(point, nearness) != NULL;
}

bool CAutoRouterPath::IsPathClip(const CRect& r) const
{
	CPoint a;
	CPoint b;

	POSITION pos = points.GetTailEdge(a, b);
	while( pos != NULL )
	{
		if( IsLineClipRect(a, b, r) )
		{
			return true;
		}

		points.GetPrevEdge(pos, a, b);
	}

	return false;
}

void CAutoRouterPath::SetAttributes(long attr)
{
	attributes = attr;
}

long CAutoRouterPath::GetAttributes(void) const
{
	return attributes;
}

bool CAutoRouterPath::IsFixed(void) const
{
	return ((attributes & ARPATH_Fixed) != 0);
}

bool CAutoRouterPath::IsMoveable(void) const
{
	return ((attributes & ARPATH_Fixed) == 0);
}

bool CAutoRouterPath::IsHighLighted(void) const
{
	return ((attributes & ARPATH_HighLighted) != 0);
}

long CAutoRouterPath::GetState(void) const
{
	return state;
}

void CAutoRouterPath::SetState(long s)
{
	ASSERT( owner != NULL );

	state = s;

#ifdef _DEBUG
	AssertValid();
#endif
}

RoutingDirection CAutoRouterPath::GetEndDir(void) const
{
	unsigned int a = attributes & ARPATH_EndMask;
	return	a & ARPATH_EndOnTop ? Dir_Top :
			a & ARPATH_EndOnRight ? Dir_Right :
			a & ARPATH_EndOnBottom ? Dir_Bottom :
			a & ARPATH_EndOnLeft ? Dir_Left : Dir_None;
}

RoutingDirection CAutoRouterPath::GetStartDir(void) const
{
	unsigned int a = attributes & ARPATH_StartMask;
	return	a & ARPATH_StartOnTop ? Dir_Top :
			a & ARPATH_StartOnRight ? Dir_Right :
			a & ARPATH_StartOnBottom ? Dir_Bottom :
			a & ARPATH_StartOnLeft ? Dir_Left : Dir_None;
}

CAutoRouterGraph* CAutoRouterPath::GetOwner(void) const
{
	return owner;
}

bool CAutoRouterPath::HasOwner(void) const
{
	return owner != NULL;
}

void CAutoRouterPath::SetOwner(CAutoRouterGraph* graph)
{
	owner = graph;
}

// --- Ports

void CAutoRouterPath::SetStartPort(CAutoRouterPort* port)
{
	startport = port;
}

void CAutoRouterPath::SetEndPort(CAutoRouterPort* port)
{
	endport = port;
}

void CAutoRouterPath::ClearPorts(void)
{
	startport = NULL;
	endport = NULL;
}

CAutoRouterPort* CAutoRouterPath::GetStartPort(void)
{
	return startport;
}

CAutoRouterPort* CAutoRouterPath::GetEndPort(void)
{
	return endport;
}

void CAutoRouterPath::SetEndDir(long arpath_end)
{
	attributes = (attributes & ~ARPATH_EndMask) + (unsigned int)arpath_end;
}

void CAutoRouterPath::SetStartDir(long arpath_start)
{
	attributes = (attributes & ~ARPATH_StartMask) + (unsigned int)arpath_start;
}

void CAutoRouterPath::SetCustomPathData(const std::vector<CustomPathData>& pDat)
{
	customPathData = pDat;
}

void CAutoRouterPath::ApplyCustomizationsBeforeAutoConnectPoints(CPointListPath& plist)
{
	plist.RemoveAll();

	if (customPathData.empty())
		return;

	std::vector<CustomPathData>::iterator ii = customPathData.begin();
	while (ii != customPathData.end()) {
		if ((*ii).type == SimpleEdgeDisplacement) {
			// it is done in a next phase
		} else if ((*ii).type == CustomPointCustomization) {
			if (!isAutoRoutingOn)
				plist.AddTail(CPoint((*ii).x, (*ii).y));
		} else {
			// unknown displacement type
		}
		++ii;
	}
}

void CAutoRouterPath::ApplyCustomizationsAfterAutoConnectPointsAndStuff(void)
{
	if (customPathData.empty())
		return;

	if (isAutoRoutingOn) {
		std::vector<CustomPathData>::iterator ii = customPathData.begin();
		int numEdges = points.GetSize() - 1;
		while (ii != customPathData.end()) {
			if ((*ii).edgeCount != numEdges &&
				(*ii).type == SimpleEdgeDisplacement)
			{
				pathDataToDelete.push_back(*ii);
				ii = customPathData.erase(ii);
			} else {
				++ii;
			}
		}
	}

	CPoint* startpoint = NULL;
	CPoint* endpoint = NULL;

	int currEdgeIndex = 0;
	POSITION pos = points.GetHeadEdgePtrs(startpoint, endpoint);
	while (pos != NULL) {
		std::vector<CustomPathData>::iterator ii = customPathData.begin();
		while (ii != customPathData.end()) {
			bool increment = true;
			if (currEdgeIndex == (*ii).edgeIndex) {
				if ((*ii).type == SimpleEdgeDisplacement) {
					RoutingDirection dir = GetDir(*endpoint - *startpoint);
					bool isHorizontalVar = (IsHorizontal(dir) != 0);
					if ((*ii).horizontalOrVerticalEdge == isHorizontalVar) {
						if ((*ii).horizontalOrVerticalEdge) {
							startpoint->y = (*ii).y;
							endpoint->y = (*ii).y;
						} else {
							startpoint->x = (*ii).x;
							endpoint->x = (*ii).x;
						}
					} else {
						// something went wrong, invalid data: direction (horz/vert) not match
						ASSERT(false);
						pathDataToDelete.push_back(*ii);
						ii = customPathData.erase(ii);
						increment = false;
					}
				} else if ((*ii).type == CustomPointCustomization) {
					// it is done in a previous phase
				} else {
					// unknown displacement type
				}
			}
			if (increment)
				++ii;
		}

		points.GetNextEdgePtrs(pos, startpoint, endpoint);
		currEdgeIndex++;
	}
}

void CAutoRouterPath::RemovePathCustomizations(void)
{
	std::vector<CustomPathData>::iterator ii = customPathData.begin();
	while (ii != customPathData.end()) {
		pathDataToDelete.push_back(*ii);
		++ii;
	}
	customPathData.clear();
}

void CAutoRouterPath::MarkPathCustomizationsForDeletion(long asp)
{
	std::vector<CustomPathData>::iterator ii = customPathData.begin();
	while (ii != customPathData.end()) {
		if ((*ii).aspect == asp)
			pathDataToDelete.push_back(*ii);
		++ii;
	}
}

void CAutoRouterPath::RemoveInvalidPathCustomizations(long asp)
{
	// We only inhibit/delete those edges, which has an edge count
	// (redundand data intended for this very sanity check)
	// doesn't equal to edge count
	std::vector<CustomPathData>::iterator ii = customPathData.begin();
	int numEdges = points.GetSize() - 1;
	while (ii != customPathData.end()) {
		if ((*ii).aspect == asp) {
			if ((*ii).edgeCount != numEdges &&
				(*ii).type == SimpleEdgeDisplacement)
			{
				ii = customPathData.erase(ii);
			} else {
				++ii;
			}
		} else {
			++ii;
		}
	}
}

bool CAutoRouterPath::AreTherePathCustomizations(void) const
{
	return !customPathData.empty();
}

bool CAutoRouterPath::AreThereDeletedPathCustomizations(void) const
{
	return !pathDataToDelete.empty();
}

void CAutoRouterPath::GetDeletedCustomPathData(std::vector<CustomPathData>& cpd) const
{
	std::vector<CustomPathData>::const_iterator ii = pathDataToDelete.begin();
	while(ii != pathDataToDelete.end()) {
		cpd.push_back(*ii);
		++ii;
	}
}

void CAutoRouterPath::GetCustomizedEdgeIndexes(std::vector<int>& indexes) const
{
	indexes.clear();
	std::vector<CustomPathData>::const_iterator ii = customPathData.begin();
	while(ii != customPathData.end())
	{
		long edgeIndex = (*ii).edgeIndex;
		indexes.push_back(edgeIndex);
		++ii;
	}
}

bool CAutoRouterPath::IsAutoRouted(void) const
{
	return isAutoRoutingOn;
}

void CAutoRouterPath::SetAutoRouting(bool autoRoutingState)
{
	isAutoRoutingOn = autoRoutingState;
}

void CAutoRouterPath::Destroy(void)
{
	SetStartPort(NULL);
	SetEndPort(NULL);
}

// --- Debug

#ifdef _DEBUG

void CAutoRouterPath::AssertValid()
{
	if( startport != NULL )
		startport->AssertValid();

	if( endport != NULL )
		endport->AssertValid();

	if( IsConnected() )
		ASSERT( !points.IsEmpty() );
	else
		ASSERT( points.IsEmpty() );
}

void CAutoRouterPath::AssertValidPos(POSITION pos) const
{
	points.AssertValidPos(pos);
}

#pragma warning( disable : 4701 )

void CAutoRouterPath::AssertValidPoints() const
{
	points.AssertValid();

	if( points.IsEmpty() )
		return;

#ifdef _DEBUG_DEEP
	TRACE("CAutoRouterPath::AssertValidPoints (count=%ld) START\n", points.GetCount());
#endif

	POSITION pos = points.GetHeadPosition();
	ASSERT( points.GetCount() >= 2 && pos != NULL );

	POSITION p1p = NULL;
	POSITION p2p = NULL;
	POSITION p3p;

	CPoint p1;
	CPoint p2;

	RoutingDirection d12;
	RoutingDirection d23;
	d23 = d12 = Dir_None;// init by zolmol

	while( pos != NULL )
	{
		p3p = p2p;
		p2p = p1p;
		p1p = pos;

		p2 = p1;
		p1 = points.GetNext(pos);

#ifdef _DEBUG_DEEP
		TRACE("%p (%ld,%ld)\n", p1p, p1.x, p1.y);
#endif
		d23 = d12;
		if( p2p != NULL )
		{
			d12 = GetDir(p2 - p1);
			ASSERT( d12 == Dir_Skew || IsRightAngle(d12) );
		}

		if( p3p != NULL && d12 != Dir_Skew && d23 != Dir_Skew )
			ASSERT( AreInRightAngle(d12, d23) );
	}

#ifdef _DEBUG_DEEP
	TRACE("CAutoRouterPath::AssertValidPoints END\n");
#endif

}

#endif

// CAutoRouterPath
