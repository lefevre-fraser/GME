// AutoRouterGraph.cpp : Implementation of CAutoRouterGraph

#include "stdafx.h"
#include "AutoRouterGraph.h"
#include "AutoRouterBox.h"
#include "AutoRouterPort.h"
#include "AutoRouterPath.h"
#include "AutoRouterEdge.h"


// Functions for CMapCARObject2CPoints and CMapCARPath2CPointList, see AutoRouterGraph.h
template<>
BOOL AFXAPI CompareElements< LPPointList, LPPointList >
	 (const LPPointList* pElement1, const LPPointList* pElement2)
{
	if ((*pElement1)->GetCount() != (*pElement2)->GetCount())
		return false;

	POSITION pointpos1 = (*pElement1)->GetHeadPosition();
	POSITION pointpos2 = (*pElement2)->GetHeadPosition();

	while( pointpos1 != NULL )
	{
		CPoint point1 = (*pElement1)->GetNext(pointpos1);
		CPoint point2 = (*pElement2)->GetNext(pointpos2);
		if( point1 != point2 )
		{
			return false;
		}
	}

	return true;
}

template<>
UINT AFXAPI HashKey<void*> (void* key)
{
	return (UINT)key;
}

template<>
BOOL AFXAPI CompareElements< CARPoints, CARPoints >
	 (const CARPoints* pElement1, const CARPoints* pElement2)
{
	if (pElement1->size() != pElement2->size())
		return false;
	CARPoints::const_iterator ii = pElement1->begin();
	CARPoints::const_iterator jj = pElement2->begin();
	while (ii != pElement1->end()) {
		if ((*ii) != (*jj))
			return false;
	}
	return true;
}

// --- CAutoRouterGraph

CAutoRouterGraph::CAutoRouterGraph():
	horizontal(1),
	vertical(0)
{
}

HRESULT CAutoRouterGraph::FinalConstruct(void)
{
	horizontal.SetOwner(this);
	vertical.SetOwner(this);

	CalculateSelfPoints();
	AddSelfEdges();

	return S_OK;
}

void CAutoRouterGraph::FinalRelease(void)
{
}

// --- Boxes

void CAutoRouterGraph::Remove(CComPtr<IAutoRouterBox> box)
{
	DeleteBoxAndPortEdges(box);

	std::vector<CComPtr<IAutoRouterPath> >::iterator iter;
	iter = paths.begin();
	
	while(iter != paths.end())
	{
		int iteratorChanged = 0;

		CComPtr<IAutoRouterPath> path = *iter;

		CComPtr<IAutoRouterPort> startPort;
		COMTHROW(path->GetStartPort(&startPort));
		ASSERT(startPort != NULL);
		CComPtr<IAutoRouterBox> startbox;
		COMTHROW(startPort->GetOwner(&startbox));

		CComPtr<IAutoRouterPort> endPort;
		COMTHROW(path->GetEndPort(&endPort));
		ASSERT(endPort != NULL);
		CComPtr<IAutoRouterBox> endbox;
		COMTHROW(endPort->GetOwner(&endbox));

		if( (startbox == box || endbox == box) )
		{
			//DeletePath:
			VARIANT_BOOL hasOwner;
			COMTHROW(path->HasOwner(&hasOwner));
			if( hasOwner == VARIANT_TRUE )
			{
				DeleteEdges(path.p);
				path->SetOwner(NULL);

				iter = paths.erase(iter);
				iteratorChanged = 1;
			}

			path->Destroy();
		}

		if (iteratorChanged==0)
			++iter;
	}

	box->SetOwner(NULL);

	std::vector<CComPtr<IAutoRouterBox> >::iterator iter2 = std::find(boxes.begin(), boxes.end(), box);

	if (iter2 == boxes.end())
	{
		//error
	}

	boxes.erase(iter2);
}

void CAutoRouterGraph::DeleteAllBoxes()
{
	for (CAutoRouterBoxList::size_type i = 0; i<boxes.size(); i++)
	{
		DeleteBoxAndPortEdges(boxes[i]);
		boxes[i]->Destroy();
	}

	boxes.clear();
}

CComPtr<IAutoRouterBox> CAutoRouterGraph::GetBoxAt(const CPoint& point, int nearness) const
{
	std::vector<CComPtr<IAutoRouterBox> >::const_iterator iter = boxes.begin();
	while (iter != boxes.end())
	{
		VARIANT_BOOL isBoxAt = VARIANT_FALSE;
		COMTHROW((*iter)->IsBoxAt(point.x, point.y, nearness, &isBoxAt));
		if( isBoxAt == VARIANT_TRUE )
		{
			return (*iter);
		}
		++iter;
	}

	return NULL;
}

void CAutoRouterGraph::SetPortAttr(CComPtr<IAutoRouterPort> port, unsigned int attr)
{
	DisconnectPathsFrom(port);
	port->SetAttributes(attr);
}

int  CAutoRouterGraph::IsRectClipBoxes(const CRect& rect) const
{
	for (CAutoRouterBoxList::size_type i = 0; i < boxes.size(); i++)
	{
		long p1, p2, p3, p4;
		COMTHROW(boxes[i]->GetRect(&p1, &p2, &p3, &p4));
		const CRect boxRect(p1, p2, p3, p4);
		if( IsRectClip(rect, boxRect) )
			return 1;
	}
	return 0;
}

int  CAutoRouterGraph::IsLineClipBoxes(const CPoint& p1, const CPoint& p2) const
{
	CRect rect(p1, p2);
	rect.NormalizeRect();
	ASSERT( rect.left == rect.right || rect.top == rect.bottom );

	if( rect.left == rect.right)
		rect.right++;
	if( rect.top == rect.bottom )
		rect.bottom++;

	return IsRectClipBoxes(rect);
}

int  CAutoRouterGraph::CanBoxAt(const CRect& rect) const
{
	return !IsRectClipBoxes(InflatedRect(rect, 1));
}

void CAutoRouterGraph::Add(CComPtr<IAutoRouterPath> path)
{
	ASSERT( path != NULL );
	VARIANT_BOOL hasOwner;
	COMTHROW(path->HasOwner(&hasOwner));
	ASSERT( hasOwner == VARIANT_FALSE );

	path->SetOwner(this);

	paths.push_back(path);

	AddEdges(path);

#ifdef _DEBUG
	AssertValidPath(path);
#endif
}

void CAutoRouterGraph::Remove(CComPtr<IAutoRouterPath> path)
{
	DeleteEdges(path.p);

	path->SetOwner(NULL);


	std::vector<CComPtr<IAutoRouterPath> >::iterator iter = std::find(paths.begin(), paths.end(), path);

	if (iter == paths.end())
	{
		//error
	}

	paths.erase(iter);
}

void CAutoRouterGraph::DeleteAllPaths()
{
	std::vector<CComPtr<IAutoRouterPath> >::iterator iter;
	iter = paths.begin();

	while (iter != paths.end())
	{
		CComPtr<IUnknown> pUnk = (*iter);
		DeleteEdges(pUnk);

		(*iter)->Destroy();
		++iter;
	}

	paths.clear();
}

CAutoRouterEdge* CAutoRouterGraph::GetListEdgeAt(const CPoint& point, int nearness) const
{
	CAutoRouterEdge* edge;

	edge = horizontal.GetEdgeAt(point, nearness);
	if( edge )
		return edge;

	return vertical.GetEdgeAt(point, nearness);
}

// --- Boxes && Paths

CRect CAutoRouterGraph::GetSurroundRect() const
{
	CRect rect(0,0,0,0);

	for (CAutoRouterBoxList::size_type i = 0; i < boxes.size(); i++)
	{
		long p1, p2, p3, p4;
		COMTHROW(boxes[i]->GetRect(&p1, &p2, &p3, &p4));
		const CRect boxRect(p1, p2, p3, p4);
		rect |= boxRect;
	}

	for (CAutoRouterPathList::size_type i = 0; i < paths.size(); i++)
	{
		long p1, p2, p3, p4;
		COMTHROW(paths[i]->GetSurroundRect(&p1, &p2, &p3, &p4));
		rect |= CRect(p1, p2, p3, p4);
	}

	return rect;
}

CComPtr<IAutoRouterBox> CAutoRouterGraph::GetOutOfBox(CPoint& point, RoutingDirection dir) const
{
	ASSERT( IsRightAngle(dir) );

	CComPtr<IAutoRouterBox> boxby = NULL;

	std::vector<CComPtr<IAutoRouterBox> >::const_iterator iter = boxes.begin();

	while (iter != boxes.end())
	{
		long p1, p2, p3, p4;
		COMTHROW((*iter)->GetRect(&p1, &p2, &p3, &p4));
		const CRect boxRect(p1, p2, p3, p4);
		if( boxRect.PtInRect(point) )
		{
			boxby = *iter;
			iter = boxes.begin();

			GetPointCoord(point, dir) = GetRectOuterCoord(boxRect, dir);
		}
		++iter;
	}

	return boxby;
}

CComPtr<IAutoRouterBox> CAutoRouterGraph::GoToNextBox(CPoint& point, RoutingDirection dir, long stophere) const
{
	ASSERT( IsRightAngle(dir) );
	ASSERT( GetPointCoord(point, dir) != stophere );

	CComPtr<IAutoRouterBox> boxby = NULL;

	std::vector<CComPtr<IAutoRouterBox> >::const_iterator iter = boxes.begin();

	while (iter != boxes.end())
	{
		long p1, p2, p3, p4;
		COMTHROW((*iter)->GetRect(&p1, &p2, &p3, &p4));
		const CRect boxRect(p1, p2, p3, p4);
		if( IsPointInDirFrom(point, boxRect, ReverseDir(dir)) &&
			IsPointBetweenSides(point, boxRect, dir) &&
			IsCoordInDirFrom(stophere, GetRectOuterCoord(boxRect, ReverseDir(dir)), dir) )
		{
			stophere = GetRectOuterCoord(boxRect, ReverseDir(dir));
			boxby = *iter;
		}
		++iter;
	}

	GetPointCoord(point, dir) = stophere;

	return boxby;
}

void CAutoRouterGraph::GetLimitsOfEdge(const CPoint& startPt, const CPoint& endPt, long& min, long& max) const
{
	long t;
	CPoint start = startPt;
	CPoint end = endPt;

	std::vector<CComPtr<IAutoRouterBox> >::const_iterator iter = boxes.begin();

	if( start.y == end.y )
	{
		if( start.x > end.x )
		{
			t = start.x;
			start.x = end.x;
			end.x = t;
		}

		while( iter != boxes.end())
		{
			long p1, p2, p3, p4;
			COMTHROW((*iter)->GetRect(&p1, &p2, &p3, &p4));
			const CRect rect(p1, p2, p3, p4);
			++iter;

			if(start.x < rect.right && rect.left <= end.x)
			{
				if( rect.bottom <= start.y && rect.bottom > min )
					min = rect.bottom;
				if( rect.top > start.y && rect.top < max )
					max = rect.top;
			}
		}
	}
	else
	{
		ASSERT( start.x == end.x );

		if( start.y > end.y )
		{
			t = start.y;
			start.y = end.y;
			end.y = t;
		}

		while( iter != boxes.end())
		{
			long p1, p2, p3, p4;
			COMTHROW((*iter)->GetRect(&p1, &p2, &p3, &p4));
			const CRect rect(p1, p2, p3, p4);
			++iter;

			if(start.y < rect.bottom && rect.top <= end.y)
			{
				if( rect.right <= start.x && rect.right > min )
					min = rect.right;
				if( rect.left > start.x && rect.left < max )
					max = rect.left;
			}
		}
	}

	max--;
}

bool CAutoRouterGraph::Connect(CComPtr<IAutoRouterPath> path)
{
	CComPtr<IAutoRouterPort> startport;
	COMTHROW(path->GetStartPort(&startport));
	CComPtr<IAutoRouterPort> endport;
	COMTHROW(path->GetEndPort(&endport));

	RoutingDirection startdir;
	COMTHROW(path->GetStartDir(&startdir));
	VARIANT_BOOL startportHasLimited = VARIANT_FALSE;
	VARIANT_BOOL startportCanHave = VARIANT_TRUE;
	if (startdir != Dir_None) {
		COMTHROW(startport->HasLimitedDirs(&startportHasLimited));
		COMTHROW(startport->CanHaveStartEndPointOn(startdir, 1, &startportCanHave));
	}
	if( startdir == Dir_None ||															// recalc startdir if empty
		startportHasLimited == VARIANT_TRUE && startportCanHave == VARIANT_FALSE)		// or is limited and userpref is invalid
	{
		long endportCenterX, endportCenterY;
		COMTHROW(endport->GetCenter(&endportCenterX, &endportCenterY));
		RoutingDirection startportDir;
		COMTHROW(startport->GetStartEndDirTo(endportCenterX, endportCenterY, 1, Dir_None, &startportDir));
		startdir = startportDir;
	}

	RoutingDirection enddir;
	COMTHROW(path->GetEndDir(&enddir));
	VARIANT_BOOL endportHasLimited = VARIANT_FALSE;
	VARIANT_BOOL endportCanHave = VARIANT_TRUE;
	if (enddir != Dir_None) {
		COMTHROW(endport->HasLimitedDirs(&endportHasLimited));
		COMTHROW(endport->CanHaveStartEndPointOn(enddir, 0, &endportCanHave));
	}
	if( enddir == Dir_None ||															// like above
		endportHasLimited == VARIANT_TRUE && endportCanHave == VARIANT_FALSE)
	{
		long startportCenterX, startportCenterY;
		COMTHROW(startport->GetCenter(&startportCenterX, &startportCenterY));
		RoutingDirection endportDir;
		COMTHROW(endport->GetStartEndDirTo(startportCenterX, startportCenterY, 0,
										   startport == endport ? startdir : Dir_None, &endportDir));

		enddir = endportDir;
	}

	long startpointx, startpointy;
	COMTHROW(startport->CreateStartEndPointOn(startdir, &startpointx, &startpointy));
	CPoint startpoint(startpointx, startpointy);
	long endpointx, endpointy;
	COMTHROW(endport->CreateStartEndPointOn(enddir, &endpointx, &endpointy));
	CPoint endpoint(endpointx, endpointy);

	if( startpoint == endpoint )
		startpoint = StepOneInDir(startpoint, NextClockwiseDir(startdir));

	return Connect(path, startpoint, endpoint);
}

bool CAutoRouterGraph::Connect(CComPtr<IAutoRouterPath> path, CPoint& startpoint, CPoint& endpoint)
{
	VARIANT_BOOL isConnected = VARIANT_TRUE;
	COMTHROW(path->IsConnected(&isConnected));
	ASSERT( isConnected == VARIANT_FALSE );
	ASSERT( startpoint != endpoint );

	CComPtr<IAutoRouterPort> startPort;
	COMTHROW(path->GetStartPort(&startPort));
	ASSERT(startPort != NULL);
	RoutingDirection startdir;
	COMTHROW(startPort->OnWhichEdge(startpoint.x, startpoint.y, &startdir));

	CComPtr<IAutoRouterPort> endPort;
	COMTHROW(path->GetEndPort(&endPort));
	ASSERT(endPort != NULL);
	RoutingDirection enddir;
	COMTHROW(endPort->OnWhichEdge(endpoint.x, endpoint.y, &enddir));
	ASSERT( IsRightAngle(startdir) && IsRightAngle(enddir) );

	CPoint start = startpoint;
	GetOutOfBox(start, startdir);
	ASSERT( start != startpoint );

	CPoint end = endpoint;
	GetOutOfBox(end, enddir);
	ASSERT( end != endpoint );

	VARIANT_BOOL isEmpty = VARIANT_TRUE;
	COMTHROW(path->IsEmpty(&isEmpty));
	ASSERT( isEmpty == VARIANT_TRUE );

	CPointListPath ret;
	VARIANT_BOOL isAutoRouted = VARIANT_FALSE;
	COMTHROW(path->IsAutoRouted(&isAutoRouted));
	if (isAutoRouted == VARIANT_TRUE)
		ConnectPoints(ret, start, end, startdir, enddir);

	// ******************************************************************

	SAFEARRAY* pArr = NULL;
	pArr = SafeArrayCreateVector(VT_I4, 0, 2 * ret.GetSize());
	long position = 0;
	POSITION pos = ret.GetHeadPosition();
	while(pos)
	{
		CPoint point = ret.GetNext(pos);
		COMTHROW(SafeArrayPutElement(pArr, &position, &point.x));
		position++;
		COMTHROW(SafeArrayPutElement(pArr, &position, &point.y));
		position++;
	}

	COMTHROW(path->ApplyCustomizationsBeforeAutoConnectPoints(&pArr));

	//one dim., long elements
	if ((pArr)->cDims == 1 && (pArr)->cbElements == 4)
	{
		ret.RemoveAll();
		//length
		long elementNum = (pArr)->rgsabound[0].cElements;
		if (elementNum > 0)
		{
			ASSERT(elementNum % 2 == 0);
			//lock it before use
			SafeArrayLock(pArr);
			long* pArrElements = (long*) (pArr)->pvData;
			for (int i = 0; i < elementNum / 2; i++)
			{
				CPoint p(pArrElements[2 * i], pArrElements[2 * i + 1]);
				ret.AddTail(p);
			}
			SafeArrayUnlock(pArr);
		}
	}
	//clear memory
	SafeArrayDestroy(pArr);

	// *********************************************************

	COMTHROW(path->DeleteAll());

	COMTHROW(path->AddTail(startpoint.x, startpoint.y));
	pos = ret.GetHeadPosition();
	while( pos != NULL )
	{
		const CPoint p = ret.GetNext(pos);
		COMTHROW(path->AddTail(p.x, p.y));
	}
	COMTHROW(path->AddTail(endpoint.x, endpoint.y));

	if (isAutoRouted == VARIANT_TRUE) {
		COMTHROW(path->SimplifyTrivially());
		SimplifyPathPoints(path);
		CenterStairsInPathPoints(path, startdir, enddir);
	}
	COMTHROW(path->SetState(ARPATHST_Connected));

	// Apply custom edge modifications - step 1
	// (Step 1: Move the desired edges - see in CAutoRouterGraph::Connect(CComPtr<IAutoRouterPath> path, CPoint& startpoint, CPoint& endpoint)
	//  Step 2: Fix the desired edges - see in CAutoRouterEdgeList::AddEdges(CComPtr<IAutoRouterPath> path))
	COMTHROW(path->ApplyCustomizationsAfterAutoConnectPointsAndStuff());

	return AddEdges(path);
}

void CAutoRouterGraph::ConnectPoints(CPointListPath& ret, CPoint& start, CPoint& end, RoutingDirection hintstartdir, RoutingDirection hintenddir)
{
	ASSERT( ret.IsEmpty() );

	CPoint& thestart = start;

	while( start != end )
	{
		RoutingDirection dir1 = ExGetMajorDir(end-start);
		RoutingDirection dir2 = ExGetMinorDir(end-start);
		ASSERT( dir1 != Dir_None );

		ASSERT( dir1 == GetMajorDir(end-start) );
		ASSERT( dir2 == Dir_None || dir2 == GetMinorDir(end-start) );

		if( ret.IsEmpty() && dir2 == hintstartdir && dir2 != Dir_None )
		{
			dir2 = dir1;
			dir1 = hintstartdir;
		}

		ret.AddTail(start);
		CPoint old = start;

		CComPtr<IAutoRouterBox> box = GoToNextBox(start, dir1, end);
		if( start == old )
		{
			ASSERT( box != NULL );
			long p1, p2, p3, p4;
			COMTHROW(box->GetRect(&p1, &p2, &p3, &p4));
			const CRect rect(p1, p2, p3, p4);

			if( dir2 == Dir_None )
				dir2 = NextClockwiseDir(dir1);

			ASSERT( dir1 != dir2 && dir1 != Dir_None && dir2 != Dir_None );

			if( IsPointInDirFrom(end, rect, dir2) )
			{
				ASSERT( !IsPointInDirFrom(start, rect, dir2) );
				GoToNextBox(start, dir2, end);
				ASSERT( IsPointInDirFrom(start, rect, dir2) );
			}
			else
			{
				ASSERT( IsPointBetweenSides(end, rect, dir1) );
				ASSERT( !IsPointIn(end, rect) );

				int rev = 0;

				if( ReverseDir(dir2) == hintenddir )
					rev = 1;
				else if( dir2 != hintenddir )
				{
					if( IsPointBetweenSides(thestart, rect, dir1) )
					{
						if(	IsPointInDirFrom(rect.TopLeft()+rect.BottomRight(), start + end, dir2) )
							rev = 1;
					}
					else
						if( IsPointInDirFrom(start, thestart, dir2) )
							rev = 1;
				}

				if( rev )
				{
					dir2 = ReverseDir(dir2);
				}

				GetPointCoord(start, dir2) = GetRectOuterCoord(rect, dir2);

				ASSERT( start != old );
				ret.AddTail(start);

				old = start;

				GetPointCoord(start, dir1) = GetRectOuterCoord(rect, dir1);
				ASSERT( IsPointInDirFrom(end, start, dir1) );
				if( GetPointCoord(start, dir1) != GetPointCoord(end, dir1) )
					GoToNextBox(start, dir1, end);
			}

			ASSERT( start != old );
		}
	}

	ret.AddTail(end);
}

void CAutoRouterGraph::DisconnectAll()
{
	std::vector<CComPtr<IAutoRouterPath> >::iterator iter;
	iter = paths.begin();
	
	while(iter != paths.end())
	{
		Disconnect(*iter);
		++iter;
	}
}

void CAutoRouterGraph::Disconnect(CComPtr<IAutoRouterPath> path)
{
	VARIANT_BOOL isConnected = VARIANT_TRUE;
	COMTHROW(path->IsConnected(&isConnected));
	if( isConnected == VARIANT_TRUE )
		DeleteEdges(path.p);

	path->DeleteAll();
}

void CAutoRouterGraph::DisconnectPathsClipping(const CRect& rect)
{
	std::vector<CComPtr<IAutoRouterPath> >::reverse_iterator iter;
	iter = paths.rbegin();

	while(iter != paths.rend())
	{
		VARIANT_BOOL isPathClip = VARIANT_TRUE;
		COMTHROW((*iter)->IsPathClip(rect.left, rect.top, rect.right, rect.bottom, &isPathClip));
		if( isPathClip == VARIANT_TRUE )
			Disconnect(*iter);
		++iter;
	}
}

void CAutoRouterGraph::DisconnectPathsFrom(CComPtr<IAutoRouterBox> box)
{
	std::vector<CComPtr<IAutoRouterPath> >::reverse_iterator iter;
	iter = paths.rbegin();

	while(iter != paths.rend())
	{
		CComPtr<IAutoRouterPath> path = *iter;

		CComPtr<IAutoRouterPort> startPort;
		COMTHROW(path->GetStartPort(&startPort));
		ASSERT(startPort != NULL);
		CComPtr<IAutoRouterBox> startbox;
		COMTHROW(startPort->GetOwner(&startbox));
		ASSERT(startbox != NULL);

		CComPtr<IAutoRouterPort> endPort;
		COMTHROW(path->GetEndPort(&endPort));
		ASSERT(endPort != NULL);
		CComPtr<IAutoRouterBox> endbox;
		COMTHROW(endPort->GetOwner(&endbox));
		ASSERT(endbox != NULL);

		if( (startbox == box || endbox == box) )
			Disconnect(path);

		++iter;
	}
}

void CAutoRouterGraph::DisconnectPathsFrom(CComPtr<IAutoRouterPort> port)
{
	std::vector<CComPtr<IAutoRouterPath> >::reverse_iterator iter;
	iter = paths.rbegin();
	
	while(iter != paths.rend())
	{
		CComPtr<IAutoRouterPath> path = *iter;

		CComPtr<IAutoRouterPort> startport;
		COMTHROW(path->GetStartPort(&startport));
		CComPtr<IAutoRouterPort> endport;
		COMTHROW(path->GetEndPort(&endport));

		if( (startport == port || endport == port) )
			Disconnect(path);

		++iter;
	}
}

// --- Edges

void CAutoRouterGraph::AddSelfEdges(void)
{
	horizontal.AddEdges(this, selfpoints);
	vertical.AddEdges(this, selfpoints);
}

void CAutoRouterGraph::AddEdges(CComPtr<IAutoRouterGraph> graph)
{
	long p1x, p1y, p2x, p2y, p3x, p3y, p4x, p4y;
	COMTHROW(graph->GetSelfPoints(&p1x, &p1y, &p2x, &p2y, &p3x, &p3y, &p4x, &p4y));
	std::vector<CPoint> selfPoints;
	selfPoints.push_back(CPoint(p1x, p1y));
	selfPoints.push_back(CPoint(p2x, p2y));
	selfPoints.push_back(CPoint(p3x, p3y));
	selfPoints.push_back(CPoint(p4x, p4y));
	arObjectsPointsCache.SetAt(graph.p, selfPoints);
	CMapCARObject2CPoints::CPair* pVal = arObjectsPointsCache.PLookup(graph.p);
	horizontal.AddEdges(graph, pVal->value);
	vertical.AddEdges(graph, pVal->value);
}

void CAutoRouterGraph::AddEdges(CComPtr<IAutoRouterBox> box)
{
	long p1x, p1y, p2x, p2y, p3x, p3y, p4x, p4y;
	COMTHROW(box->GetSelfPoints(&p1x, &p1y, &p2x, &p2y, &p3x, &p3y, &p4x, &p4y));
	std::vector<CPoint> selfPoints;
	selfPoints.push_back(CPoint(p1x, p1y));
	selfPoints.push_back(CPoint(p2x, p2y));
	selfPoints.push_back(CPoint(p3x, p3y));
	selfPoints.push_back(CPoint(p4x, p4y));
	arObjectsPointsCache.SetAt(box.p, selfPoints);
	CMapCARObject2CPoints::CPair* pVal = arObjectsPointsCache.PLookup(box.p);
	horizontal.AddEdges(box, pVal->value);
	vertical.AddEdges(box, pVal->value);
}

void CAutoRouterGraph::AddEdges(CComPtr<IAutoRouterPort> port)
{
	long p1x, p1y, p2x, p2y, p3x, p3y, p4x, p4y;
	COMTHROW(port->GetSelfPoints(&p1x, &p1y, &p2x, &p2y, &p3x, &p3y, &p4x, &p4y));
	std::vector<CPoint> selfPoints;
	selfPoints.push_back(CPoint(p1x, p1y));
	selfPoints.push_back(CPoint(p2x, p2y));
	selfPoints.push_back(CPoint(p3x, p3y));
	selfPoints.push_back(CPoint(p4x, p4y));
	arObjectsPointsCache.SetAt(port.p, selfPoints);
	CMapCARObject2CPoints::CPair* pVal = arObjectsPointsCache.PLookup(port.p);
	horizontal.AddEdges(port, pVal->value);
	vertical.AddEdges(port, pVal->value);
}

bool CAutoRouterGraph::AddEdges(CComPtr<IAutoRouterPath> path)
{
	CPointListPath* pointList = new CPointListPath();
	GetPointList(path, *pointList);

	CPointListPath* pointList2;
	BOOL found = arPathPointsCache.Lookup(path, pointList2);
	if (found)
	{
		delete pointList2;
		arPathPointsCache.RemoveKey(path.p);
	}

	arPathPointsCache.SetAt(path.p, pointList);
	VARIANT_BOOL isAutoRouted = VARIANT_FALSE;
	COMTHROW(path->IsAutoRouted(&isAutoRouted));
	if (isAutoRouted == VARIANT_TRUE)
		return horizontal.AddEdges(path, *pointList) && vertical.AddEdges(path, *pointList);
	
	return true;
}

void CAutoRouterGraph::DeleteEdges(CComPtr<IUnknown> object)
{
	horizontal.DeleteEdges(object);
	vertical.DeleteEdges(object);
}

void CAutoRouterGraph::AddAllEdges()
{
	ASSERT( horizontal.IsEmpty() && vertical.IsEmpty() );

	std::vector<CComPtr<IAutoRouterBox> >::iterator iter;
	iter = boxes.begin();

	while (iter != boxes.end())
	{
		AddBoxAndPortEdges(*iter);
		++iter;
	}

	std::vector<CComPtr<IAutoRouterPath> >::iterator iterP;
	iterP = paths.begin();

	while (iterP != paths.end())
	{
		AddEdges(*iterP);
		iterP++;
	}
}

void CAutoRouterGraph::DeleteAllEdges()
{
	horizontal.DeleteAllEdges();
	vertical.DeleteAllEdges();
}

void CAutoRouterGraph::AddBoxAndPortEdges(CComPtr<IAutoRouterBox> box)
{
	ASSERT( box != NULL );

	AddEdges(box);

	SAFEARRAY* pArr = NULL;
	COMTHROW(box->GetPortList(&pArr));
	//one dim., long elements
	if ((pArr)->cDims == 1)
	{
		//length
		long elementNum = (pArr)->rgsabound[0].cElements;
		if (elementNum > 0)
		{
			for (long i = 0; i < elementNum; i++)
			{
				CComPtr<IAutoRouterPort> pUnk;
				SafeArrayGetElement(pArr, &i, &pUnk);
				AddEdges(pUnk);
			}
		}
	}
	//clear memory
	SafeArrayDestroy(pArr);
}

void CAutoRouterGraph::DeleteBoxAndPortEdges(CComPtr<IAutoRouterBox> box)
{
	ASSERT( box != NULL );

	DeleteEdges(box.p);

	SAFEARRAY* pArr = NULL;
	COMTHROW(box->GetPortList(&pArr));
	//one dim., long elements
	if ((pArr)->cDims == 1)
	{
		//length
		long elementNum = (pArr)->rgsabound[0].cElements;
		if (elementNum > 0)
		{
			for (long i = 0; i < elementNum; i++)
			{
				CComPtr<IUnknown> pUnk;
				SafeArrayGetElement(pArr, &i, &pUnk);
				DeleteEdges(pUnk);
			}
		}
	}
	//clear memory
	SafeArrayDestroy(pArr);
}

CAutoRouterEdgeList& CAutoRouterGraph::GetEdgeList(int ishorizontal)
{
	return ishorizontal ? horizontal : vertical;
}

// --- Path && Edges

int CAutoRouterGraph::CanDeleteTwoEdgesAt(CComPtr<IAutoRouterPath> path, CPointListPath& points, POSITION pos) const
{
#ifdef _DEBUG
	CComPtr<IAutoRouterGraph> ownerGraph;
	COMTHROW(path->GetOwner(&ownerGraph));
	ASSERT( ownerGraph.p == this );
	static_cast<CAutoRouterPath*>(path.p)->AssertValid();
	VARIANT_BOOL isConnected = VARIANT_TRUE;
	COMTHROW(path->IsConnected(&isConnected));
	ASSERT( isConnected == VARIANT_TRUE );
	points.AssertValidPos(pos);
#ifdef _DEBUG_DEEP
//	horizontal.AssertValidPathEdges(path, points);
//	vertical.AssertValidPathEdges(path, points);
#endif
#endif

	POSITION pointpos = pos;
	CPoint point = points.GetNext(pos);
	POSITION npointpos = pos;
	if( npointpos == NULL )
		return 0;
	CPoint npoint = points.GetNext(pos);
	POSITION nnpointpos = pos;
	if( nnpointpos == NULL )
		return 0;

	pos = pointpos;
	points.GetPrev(pos);
	POSITION ppointpos = pos; if( ppointpos == NULL ) return 0;
	CPoint ppoint = points.GetPrev(pos);
	POSITION pppointpos = pos; if( pppointpos == NULL ) return 0;
	if( npoint == point) return 0; // direction of zero-length edges can't be determined, so don't delete them

	ASSERT( pppointpos != NULL && ppointpos != NULL && pointpos != NULL && npointpos != NULL && nnpointpos != NULL );

	RoutingDirection dir = GetDir(npoint - point);
	ASSERT( IsRightAngle(dir) );
	int ishorizontal = IsHorizontal(dir);

	CPoint newpoint;
	GetPointCoord(newpoint, ishorizontal) = GetPointCoord(npoint, ishorizontal);
	GetPointCoord(newpoint, !ishorizontal) = GetPointCoord(ppoint, !ishorizontal);

	ASSERT( GetDir(newpoint - ppoint) == dir );

	if( IsLineClipBoxes(newpoint, npoint) ) return 0;
	if( IsLineClipBoxes(newpoint, ppoint) ) return 0;

	return 1;
}

void CAutoRouterGraph::DeleteTwoEdgesAt(CComPtr<IAutoRouterPath> path, CPointListPath& points, POSITION pos)
{
#ifdef _DEBUG
	CComPtr<IAutoRouterGraph> ownerGraph;
	COMTHROW(path->GetOwner(&ownerGraph));
	ASSERT( ownerGraph.p == this );
	static_cast<CAutoRouterPath*>(path.p)->AssertValid();
	VARIANT_BOOL isConnected = VARIANT_TRUE;
	COMTHROW(path->IsConnected(&isConnected));
	ASSERT( isConnected == VARIANT_TRUE );
	points.AssertValidPos(pos);
#ifdef _DEBUG_DEEP
//	horizontal.AssertValidPathEdges(path, points);
//	vertical.AssertValidPathEdges(path, points);
#endif
#endif

	POSITION pointpos = pos;
	CPoint* point = &(points.GetNext(pos));
	POSITION npointpos = pos;
	CPoint* npoint = &(points.GetNext(pos));
	POSITION nnpointpos = pos;
	CPoint* nnpoint = &(points.GetNext(pos));
	POSITION nnnpointpos = pos;
	pos = pointpos;
	points.GetPrev(pos);
	POSITION ppointpos = pos;
	CPoint* ppoint = &(points.GetPrev(pos));
	POSITION pppointpos = pos;
	CPoint* pppoint = &(points.GetAt(pos));

	ASSERT( pppointpos != NULL && ppointpos != NULL && pointpos != NULL && npointpos != NULL && nnpointpos != NULL );
	ASSERT( pppoint != NULL && ppoint != NULL && point != NULL && npoint != NULL && nnpoint != NULL );

	RoutingDirection dir = GetDir(*npoint - *point);
	ASSERT( IsRightAngle(dir) );
	int ishorizontal = IsHorizontal(dir);

	CPoint newpoint;
	GetPointCoord(newpoint, ishorizontal) = GetPointCoord(*npoint, ishorizontal);
	GetPointCoord(newpoint, !ishorizontal) = GetPointCoord(*ppoint, !ishorizontal);

	ASSERT( GetDir(newpoint - *ppoint) == dir );

	ASSERT( !IsLineClipBoxes(newpoint, *npoint) );
	ASSERT( !IsLineClipBoxes(newpoint, *ppoint) );

	CAutoRouterEdgeList& hlist = GetEdgeList(ishorizontal);
	CAutoRouterEdgeList& vlist = GetEdgeList(!ishorizontal);

	CAutoRouterEdge* ppedge = hlist.GetEdgeByPointer(pppoint, ppoint);
	CAutoRouterEdge* pedge = vlist.GetEdgeByPointer(ppoint, point);
	CAutoRouterEdge* nedge = hlist.GetEdgeByPointer(point, npoint);
	CAutoRouterEdge* nnedge = vlist.GetEdgeByPointer(npoint, nnpoint);

	ASSERT( ppedge != NULL && pedge != NULL && nedge != NULL && nnedge != NULL );

	vlist.Delete(pedge);
	hlist.Delete(nedge);

	points.RemoveAt(pointpos);
	points.RemoveAt(npointpos);
	points.SetAt(ppointpos, newpoint);

	ASSERT( ppedge->GetEndPoint() == *ppoint && ppedge->GetEndPointNext() == *point );
	ppedge->SetEndPointNext(nnpoint);

	ASSERT( nnedge->GetStartPoint() == *npoint && nnedge->GetStartPointPrev() == *point );
	nnedge->SetStartPoint(ppoint);
	nnedge->SetStartPointPrev(pppoint);

	if( nnnpointpos != NULL )
	{
		CAutoRouterEdge* nnnedge = hlist.GetEdgeByPointer(nnpoint, &(points.GetAt(nnnpointpos)));
		ASSERT( nnnedge != NULL );
		ASSERT( nnnedge->GetStartPointPrev() == *npoint && nnnedge->GetStartPoint() == *nnpoint );
		nnnedge->SetStartPointPrev(ppoint);
	}

	if( *nnpoint == newpoint )
		DeleteSamePointsAt(path, points, ppointpos);

	// Update Points back
	UpdatePathPointsFromCache(path, false);

#ifdef _DEBUG_DEEP
	static_cast<CAutoRouterPath*>(path.p)->AssertValid();
	horizontal.AssertValidPathEdges(path, points);
	vertical.AssertValidPathEdges(path, points);
#endif
}

void CAutoRouterGraph::DeleteSamePointsAt(CComPtr<IAutoRouterPath> path, CPointListPath& points, POSITION pos)
{
#ifdef _DEBUG
	CComPtr<IAutoRouterGraph> ownerGraph;
	COMTHROW(path->GetOwner(&ownerGraph));
	ASSERT( ownerGraph.p == this );
	static_cast<CAutoRouterPath*>(path.p)->AssertValid();
	VARIANT_BOOL isConnected = VARIANT_TRUE;
	COMTHROW(path->IsConnected(&isConnected));
	ASSERT( isConnected == VARIANT_TRUE );
	points.AssertValidPos(pos);
#endif

	POSITION pointpos = pos;
	CPoint* point = &(points.GetNext(pos));
	POSITION npointpos = pos;
	CPoint* npoint = &(points.GetNext(pos));
	POSITION nnpointpos = pos;
	CPoint* nnpoint = &(points.GetNext(pos));
	POSITION nnnpointpos = pos;
	pos = pointpos;
	points.GetPrev(pos);
	POSITION ppointpos = pos;
	CPoint* ppoint = &(points.GetPrev(pos));
	POSITION pppointpos = pos;
	CPoint* pppoint = pos == NULL ? NULL : &(points.GetAt(pos));

	ASSERT( ppointpos != NULL && pointpos != NULL && npointpos != NULL && nnpointpos != NULL );
	ASSERT( ppoint != NULL && point != NULL && npoint != NULL && nnpoint != NULL );
	ASSERT( *point == *npoint && *point != *ppoint );

	RoutingDirection dir = GetDir(*point - *ppoint);
	ASSERT( IsRightAngle(dir) );
	int ishorizontal = IsHorizontal(dir);

	CAutoRouterEdgeList& hlist = GetEdgeList(ishorizontal);
	CAutoRouterEdgeList& vlist = GetEdgeList(!ishorizontal);

	CAutoRouterEdge* pedge = hlist.GetEdgeByPointer(ppoint, point);
	CAutoRouterEdge* nedge = vlist.GetEdgeByPointer(point, npoint);
	CAutoRouterEdge* nnedge = hlist.GetEdgeByPointer(npoint, nnpoint);

	ASSERT( pedge != NULL && nedge != NULL && nnedge != NULL );

	vlist.Delete(pedge);
	hlist.Delete(nedge);

	points.RemoveAt(pointpos);
	points.RemoveAt(npointpos);

	if( pppointpos != NULL )
	{
		CAutoRouterEdge* ppedge = vlist.GetEdgeByPointer(pppoint, ppoint);
		ASSERT( ppedge != NULL && ppedge->GetEndPoint() == *ppoint && ppedge->GetEndPointNext() == *point );
		ppedge->SetEndPointNext(nnpoint);
	}

	ASSERT( nnedge->GetStartPoint() == *npoint && nnedge->GetStartPointPrev() == *point );
	nnedge->SetStartPoint(ppoint);
	nnedge->SetStartPointPrev(pppoint);

	if( nnnpointpos != NULL )
	{
		CAutoRouterEdge* nnnedge = vlist.GetEdgeByPointer(nnpoint, &(points.GetAt(nnnpointpos)));
		ASSERT( nnnedge != NULL && nnnedge->GetStartPointPrev() == *npoint && nnnedge->GetStartPoint() == *nnpoint );
		nnnedge->SetStartPointPrev(ppoint);
	}

#ifdef _DEBUG_DEEP
	static_cast<CAutoRouterPath*>(path.p)->AssertValid();
//	horizontal.AssertValidPathEdges(path, points);
//	vertical.AssertValidPathEdges(path, points);
#endif
}

int CAutoRouterGraph::SimplifyPaths()
{
	int was = 0;

	std::vector<CComPtr<IAutoRouterPath> >::iterator iter;
	iter = paths.begin();

	while (iter != paths.end())
	{
		CComPtr<IAutoRouterPath> path = *iter;
		++iter;

		VARIANT_BOOL isAutoRouted = VARIANT_FALSE;
		COMTHROW(path->IsAutoRouted(&isAutoRouted));
		if (isAutoRouted == VARIANT_TRUE) {
			CMapCARPath2CPointList::CPair* pVal = arPathPointsCache.PLookup(path);
			ASSERT(pVal != NULL);
			POSITION pointpos = pVal->value->GetHeadPosition();

			while( pointpos != NULL )
			{
				if( CanDeleteTwoEdgesAt(path, *(pVal->value), pointpos) )
				{
					DeleteTwoEdgesAt(path, *(pVal->value), pointpos);
					was = 1;
					break;
				}
				pVal->value->GetNext(pointpos);
			}
		}
	}

	return was;
}

#pragma warning(disable: 4700)
void CAutoRouterGraph::CenterStairsInPathPoints(CComPtr<IAutoRouterPath> path, RoutingDirection hintstartdir, RoutingDirection hintenddir)
{
	ASSERT( path != NULL );
	VARIANT_BOOL isConnected = VARIANT_TRUE;
	COMTHROW(path->IsConnected(&isConnected));
	ASSERT( isConnected == VARIANT_FALSE );

	CPointListPath pointList;
	GetPointList(path, pointList);

#ifdef _DEBUG
	static_cast<CAutoRouterPath*>(path.p)->AssertValidPoints();
#endif

	bool modified = false;

	CPoint p1;
	CPoint p2;
	CPoint p3;
	CPoint p4;

	POSITION p1p = NULL;
	POSITION p2p = NULL;
	POSITION p3p = NULL;
	POSITION p4p = NULL;

	RoutingDirection d12 = Dir_None;
	RoutingDirection d23 = Dir_None;
	RoutingDirection d34 = Dir_None;

	long pX, pY;
	COMTHROW(path->GetOutOfBoxStartPoint(&pX, &pY, hintstartdir));
	const CPoint outOfBoxStartPoint(pX, pY);
	COMTHROW(path->GetOutOfBoxEndPoint(&pX, &pY, hintenddir));
	const CPoint outOfBoxEndPoint(pX, pY);

	POSITION pos = pointList.GetHeadPosition();
	ASSERT( pos != NULL );

	p1p = pos;
	p1 = pointList.GetNext(pos);

	while( pos != NULL )
	{
		p4p = p3p;
		p3p = p2p;
		p2p = p1p;
		p1p = pos;

		p4 = p3;
		p3 = p2;
		p2 = p1;
		p1 = pointList.GetNext(pos);

		d34 = d23;
		d23 = d12;

		if( p2p != NULL )
		{
			d12 = GetDir(p2 - p1);
#ifdef _DEBUG
			ASSERT( IsRightAngle(d12) );
			if( p3p != NULL )
				ASSERT( AreInRightAngle(d12, d23) );
#endif
		}

		if( p4p != NULL && d12 == d34 )
		{
			ASSERT( p1p != NULL && p2p != NULL && p3p != NULL && p4p != NULL );

			CPoint np2 = p2;
			CPoint np3 = p3;
			int h = IsHorizontal(d12);

			long p4x = GetPointCoord(p4, h);
			long p3x = GetPointCoord(p3, h);
			long p1x = GetPointCoord(p1, h);

			if( p1x < p4x )
			{
				long t = p1x;
				p1x = p4x;
				p4x = t;
			}

			if( p4x < p3x && p3x < p1x )
			{
				long m = (p4x + p1x)/2;
				GetPointCoord(np2, h) = m;
				GetPointCoord(np3, h) = m;

				GetLimitsOfEdge(np2, np3, p4x, p1x);

				m = (p4x + p1x)/2;
				GetPointCoord(np2, h) = m;
				GetPointCoord(np3, h) = m;

				if( !IsLineClipBoxes(np2, np3) &&
					!IsLineClipBoxes(p1p == pointList.GetTailPosition() ? outOfBoxEndPoint : p1, np2) &&
					!IsLineClipBoxes(p4p == pointList.GetHeadPosition() ? outOfBoxStartPoint : p4, np3) )
				{
					p2 = np2;
					p3 = np3;
					pointList.SetAt(p2p, p2);
					pointList.SetAt(p3p, p3);
					modified = true;
				}
			}
		}
	}

	if (modified)
		UpdatePoints(path, pointList, true);

#ifdef _DEBUG
	static_cast<CAutoRouterPath*>(path.p)->AssertValidPoints();
#endif
}

void CAutoRouterGraph::SimplifyPathPoints(CComPtr<IAutoRouterPath> path)
{
	ASSERT( path != NULL );
	VARIANT_BOOL isConnected = VARIANT_TRUE;
	COMTHROW(path->IsConnected(&isConnected));
	ASSERT( isConnected == VARIANT_FALSE );

	CPointListPath pointList;
	GetPointList(path, pointList);

#ifdef _DEBUG
	static_cast<CAutoRouterPath*>(path.p)->AssertValidPoints();
#endif

	bool modified = false;

	CPoint p1;
	CPoint p2;
	CPoint p3;
	CPoint p4;
	CPoint p5;

	POSITION p1p = NULL;
	POSITION p2p = NULL;
	POSITION p3p = NULL;
	POSITION p4p = NULL;
	POSITION p5p = NULL;

	POSITION pos = pointList.GetHeadPosition();
	ASSERT( pos != NULL );

	p1p = pos;
	p1 = pointList.GetNext(pos);

	while( pos != NULL )
	{
		p5p = p4p;
		p4p = p3p;
		p3p = p2p;
		p2p = p1p;
		p1p = pos;

		p5 = p4;
		p4 = p3;
		p3 = p2;
		p2 = p1;
		p1 = pointList.GetNext(pos);

		if( p5p != NULL )
		{
			ASSERT( p1p != NULL && p2p != NULL && p3p != NULL && p4p != NULL && p5p != NULL );
			ASSERT( p1 != p2 && p2 != p3 && p3 != p4 && p4 != p5 );

			RoutingDirection d = GetDir(p2 - p1);
			ASSERT( IsRightAngle(d) );
			int h = IsHorizontal(d);

			CPoint np3;
			GetPointCoord(np3, h) = GetPointCoord(p5, h);
			GetPointCoord(np3, !h) = GetPointCoord(p1, !h);

			if( !IsLineClipBoxes(p2, np3) && !IsLineClipBoxes(np3, p4) )
			{
				modified = true;
				pointList.RemoveAt(p2p);
				pointList.RemoveAt(p4p);
				pointList.SetAt(p3p, np3);
				if( np3 == p1 )
					pointList.RemoveAt(p1p);
				if( np3 == p5 )
					pointList.RemoveAt(p5p);

				p1p = NULL;
				p2p = NULL;
				p3p = NULL;
				p4p = NULL;

				pos = pointList.GetHeadPosition();
			}
		}
	}

	if (modified)
		UpdatePoints(path, pointList, false);

#ifdef _DEBUG
	static_cast<CAutoRouterPath*>(path.p)->AssertValidPoints();
#endif
}
#pragma warning(default: 4700)

void CAutoRouterGraph::ConnectAllDisconnectedPaths()
{
	std::vector<CComPtr<IAutoRouterPath> >::iterator iter;

	bool success = false;
	bool giveup = false;
	while (!success && !giveup) {
		success = true;
		iter = paths.begin();
		while (iter != paths.end() && success)
		{
			CComPtr<IAutoRouterPath> path = *iter;

			VARIANT_BOOL isConnected = VARIANT_TRUE;
			COMTHROW(path->IsConnected(&isConnected));
			if( isConnected == VARIANT_FALSE )
			{
				success = Connect(path);
				if (!success) {
					// Something is messed up, probably an existing edge customization results in a zero length edge
					// In that case we try to delete any customization for this path to recover from the problem
					VARIANT_BOOL areThere = VARIANT_FALSE;
					COMTHROW(path->AreTherePathCustomizations(&areThere));
					if (areThere == VARIANT_TRUE)
						COMTHROW(path->RemovePathCustomizations());
					else
						giveup = true;
				}
			}

			++iter;
		}
		if (!success && !giveup)
			DisconnectAll();	// There was an error, delete halfway results to be able to start a new pass
	}
}

bool CAutoRouterGraph::IsEdgeFixed(CComPtr<IAutoRouterPath> path, const CPoint& startpoint, const CPoint& endpoint)
{
	RoutingDirection d = GetDir(endpoint - startpoint);
	int h = IsHorizontal(d);

	CAutoRouterEdgeList& elist = GetEdgeList(h);

	CAutoRouterEdge* edge = elist.GetEdge(path, startpoint, endpoint);
	if (edge != NULL)
		return edge->GetEdgeFixed() && !edge->GetEdgeCustomFixed();

	ASSERT(false);
	return true;
}

// --- SelfPoints

void CAutoRouterGraph::CalculateSelfPoints()
{
	ASSERT(selfpoints.size() == 0);

	if (selfpoints.size() == 0) {
		selfpoints.push_back(CPoint(ED_MINCOORD, ED_MINCOORD));
		selfpoints.push_back(CPoint(ED_MAXCOORD, ED_MINCOORD));
		selfpoints.push_back(CPoint(ED_MAXCOORD, ED_MAXCOORD));
		selfpoints.push_back(CPoint(ED_MINCOORD, ED_MAXCOORD));
	} else {
		ASSERT(selfpoints.size() == 4);

		selfpoints[0].x = ED_MINCOORD;
		selfpoints[0].y = ED_MINCOORD;

		selfpoints[1].x = ED_MAXCOORD;
		selfpoints[1].y = ED_MINCOORD;

		selfpoints[2].x = ED_MAXCOORD;
		selfpoints[2].y = ED_MAXCOORD;

		selfpoints[3].x = ED_MINCOORD;
		selfpoints[3].y = ED_MAXCOORD;
	}
}

STDMETHODIMP CAutoRouterGraph::CreateBox(IAutoRouterBox** result)
{
	CComObjPtr<CAutoRouterBox> box;
	CreateComObject(box);

	return ::QueryInterface(box, result);
}

STDMETHODIMP CAutoRouterGraph::AddBox(IAutoRouterBox* box)
{
	long p1, p2, p3, p4;
	HRESULT hr = box->GetRect(&p1, &p2, &p3, &p4);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	const CRect rect(p1, p2, p3, p4);

	DisconnectPathsClipping(rect);

	box->SetOwner(this);

	boxes.push_back(box);

	AddBoxAndPortEdges(box);

	return S_OK; 
}

STDMETHODIMP CAutoRouterGraph::DeleteBox(IAutoRouterBox* box)
{
	VARIANT_BOOL hasOwner = VARIANT_FALSE;
	HRESULT hr = box->HasOwner(&hasOwner);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;

	if( hasOwner == VARIANT_TRUE )
	{
		Remove(box);
	}
	
	return box->Destroy();
}

STDMETHODIMP CAutoRouterGraph::ShiftBoxBy(IAutoRouterBox* box, long sizeX, long sizeY)
{
	CSize offset(sizeX, sizeY);

	DeleteBoxAndPortEdges(box);
	HRESULT hr = box->ShiftBy(offset.cx, offset.cy);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	AddBoxAndPortEdges(box);

	long p1, p2, p3, p4;
	hr = box->GetRect(&p1, &p2, &p3, &p4);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	const CRect rect(p1, p2, p3, p4);
	DisconnectPathsClipping(rect);
	DisconnectPathsFrom(box);

	return S_OK;
}

STDMETHODIMP CAutoRouterGraph::AutoRoute(long aspect, long* result)
{
	ConnectAllDisconnectedPaths();

	int updated = 0;
	int last = 0;
	int c = 100;		// max # of total op
	int dm = 10;		// max # of distribution op
	int d = 0;

	while( c > 0 )
	{
		if (c < 100)
			UpdatePaths();
		DumpPaths(0, c);
		if( c > 0 )
		{
			if( last == 1 )
				break;

			c--;
			if( SimplifyPaths() )
			{
				updated = 1;
				last = 1;
			}
		}

		DumpPaths(1, c);
		if( c > 0 )
		{
			if( last == 2 )
				break;

			c--;
			if( horizontal.Block_ScanBackward() )
			{
				DumpPaths(2, c);
				updated = 1;

				do {
					c--;
					DumpPaths(3, c);
				} while( c > 0 && horizontal.Block_ScanBackward() );
				DumpPaths(4, c);

				if( last < 2 || last > 5 )
					d = 0;
				else if( ++d >= dm )
					break;

				last = 2;
			}
		}

		DumpPaths(5, c);
		if( c > 0 )
		{
			if( last == 3 )
				break;

			c--;
			if( horizontal.Block_ScanForward() )
			{
				DumpPaths(6, c);
				updated = 1;

				do {
					c--;
					DumpPaths(7, c);
				} while( c > 0 && horizontal.Block_ScanForward() );
				DumpPaths(8, c);

				if( last < 2 || last > 5 )
					d = 0;
				else if( ++d >= dm )
					break;

				last = 3;
			}
		}

		DumpPaths(9, c);
		if( c > 0 )
		{
			if( last == 4 )
				break;

			c--;
			if( vertical.Block_ScanBackward() )
			{
				updated = 1;

				do
				c--;
				while( c > 0 && vertical.Block_ScanBackward() );

				if( last < 2 || last > 5 )
					d = 0;
				else if( ++d >= dm )
					break;

				last = 4;
			}
		}

		DumpPaths(10, c);
		if( c > 0 )
		{
			if( last == 5 )
				break;

			c--;
			if( vertical.Block_ScanForward() )
			{
				updated = 1;

				do
				c--;
				while( c > 0 && vertical.Block_ScanForward() );

				if( last < 2 || last > 5 )
					d = 0;
				else if( ++d >= dm )
					break;

				last = 5;
			}
		}

		DumpPaths(11, c);
		if( c > 0 )
		{
			if( last == 6 )
				break;

			c--;
			if( horizontal.Block_SwitchWrongs() )
			{
				updated = 1;
				last = 6;
			}
		}

		DumpPaths(12, c);
		if( c > 0 )
		{
			if( last == 7 )
				break;

			c--;
			if( vertical.Block_SwitchWrongs() )
			{
				updated = 1;
				last = 7;
			}
		}

		if( last == 0 )
			break;
	}
	UpdatePaths();

	if( c <= 0 )
	{
		// MessageBeep(MB_ICONEXCLAMATION);
		updated = -1;
	}

	// Check customized connection if there's any clip against boxes
	{
		std::vector<CComPtr<IAutoRouterPath> >::iterator pathiter;
		pathiter = paths.begin();

		HRESULT hr = S_OK;
		while (pathiter != paths.end())
		{
			CComPtr<IAutoRouterPath> path = *pathiter;

			VARIANT_BOOL areThere = VARIANT_FALSE;
			hr = path->AreTherePathCustomizations(&areThere);
			ASSERT(SUCCEEDED(hr));
			if (FAILED(hr))
				return hr;
			if (areThere == VARIANT_TRUE)
			{
				long sp1 = 0, sp2 = 0, sp3 = 0, sp4 = 0;
				HRESULT hr = path->GetStartBox(&sp1, &sp2, &sp3, &sp4);
				ASSERT(SUCCEEDED(hr));
				if (FAILED(hr))
					return hr;
				const CRect startBoxRect(sp1, sp2, sp3, sp4);
				long ep1 = 0, ep2 = 0, ep3 = 0, ep4 = 0;
				hr = path->GetEndBox(&ep1, &ep2, &ep3, &ep4);
				ASSERT(SUCCEEDED(hr));
				if (FAILED(hr))
					return hr;
				const CRect endBoxRect(ep1, ep2, ep3, ep4);

				std::vector<CComPtr<IAutoRouterBox> >::const_iterator boxiter = boxes.begin();

				while (boxiter != boxes.end())
				{
					long p1, p2, p3, p4;
					hr = (*boxiter)->GetRect(&p1, &p2, &p3, &p4);
					const CRect boxRect(p1, p2, p3, p4);
					if ((startBoxRect.IsRectEmpty() || !IsRectIn(startBoxRect, boxRect)) &&
						(endBoxRect.IsRectEmpty() || !IsRectIn(endBoxRect, boxRect)))
					{
						VARIANT_BOOL isPathClip = VARIANT_FALSE;
						hr = path->IsPathClip(boxRect.left, boxRect.top, boxRect.right, boxRect.bottom, &isPathClip);
						if (isPathClip == VARIANT_TRUE)
						{
							path->MarkPathCustomizationsForDeletion(aspect);
							updated = -2;
						}
					}

					++boxiter;
				}
			}

			++pathiter;
		}
	}

	*result = updated;
	return S_OK;
}

STDMETHODIMP CAutoRouterGraph::DeletePath( IAutoRouterPath* path)
{
	VARIANT_BOOL hasOwner;
	HRESULT hr = path->HasOwner(&hasOwner);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	if( hasOwner == VARIANT_TRUE )
	{
		Remove(path);
	}

	return path->Destroy();
}

STDMETHODIMP CAutoRouterGraph::DeleteAll()
{
	EmptyPointsCache();
	DeleteAllPaths();
	DeleteAllBoxes();
	return S_OK;
}

STDMETHODIMP CAutoRouterGraph::GetPathAt(long pointX, long pointY, long nearness, IAutoRouterPath** result)
{
	std::vector<CComPtr<IAutoRouterPath> >::iterator iter;
	iter = paths.begin();

	while (iter != paths.end())
	{
		CComPtr<IAutoRouterPath> path = *iter;

		VARIANT_BOOL isPathAt = VARIANT_TRUE;
		HRESULT hr = path->IsPathAt(pointX, pointY, nearness, &isPathAt);
		ASSERT(SUCCEEDED(hr));
		if (FAILED(hr))
			return hr;
		if( isPathAt == VARIANT_TRUE )
			return path->QueryInterface(IID_IAutoRouterPath,(void**)result);

		++iter;
	}

	result = NULL;
	return S_OK;
}

STDMETHODIMP CAutoRouterGraph::AddPath(VARIANT_BOOL isAutoRouted, IAutoRouterPort* startport, IAutoRouterPort* endport, IAutoRouterPath** result)
{
	CComObjPtr<CAutoRouterPath> cpath;
	CreateComObject(cpath);
	CComQIPtr<IAutoRouterPath> path = cpath;

	path->SetAutoRouting(isAutoRouted);
	path->SetStartPort(startport);
	path->SetEndPort(endport);
	Add(path);

	return path->QueryInterface(IID_IAutoRouterPath, (void**)result);
}

STDMETHODIMP CAutoRouterGraph::IsEdgeFixed(IAutoRouterPath* path, long startX, long startY, long endX, long endY, VARIANT_BOOL* result)
{
	bool isFixed = IsEdgeFixed(CComPtr<IAutoRouterPath>(path), CPoint(startX, startY), CPoint(endX, endY));
	if (isFixed)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterGraph::GetSelfPoints(long* p1x, long* p1y, long* p2x, long* p2y, long* p3x, long* p3y, long* p4x, long* p4y)
{
	*p1x = selfpoints[0].x;
	*p1y = selfpoints[0].y;
	*p2x = selfpoints[1].x;
	*p2y = selfpoints[1].y;
	*p3x = selfpoints[2].x;
	*p3y = selfpoints[2].y;
	*p4x = selfpoints[3].x;
	*p4y = selfpoints[3].y;

	return S_OK;
}

STDMETHODIMP CAutoRouterGraph::Destroy()
{
	DeleteEdges(this);
	DeleteAll();

	horizontal.SetOwner(NULL);
	vertical.SetOwner(NULL);

	AddRef();
	Release();

	return S_OK;
}

void CAutoRouterGraph::EmptyPointsCache(void)
{
	CMapCARPath2CPointList::CPair* pCurVal;
	pCurVal = arPathPointsCache.PGetFirstAssoc();
	while (pCurVal != NULL) {
		// pCurVal->key:	CAutoRouterPath*
		// pCurVal->value:	CPointList*
		delete pCurVal->value;
		pCurVal = arPathPointsCache.PGetNextAssoc(pCurVal);
	}
	arPathPointsCache.RemoveAll();
	arObjectsPointsCache.RemoveAll();
}

bool CAutoRouterGraph::UpdatePathPointsFromCache(CComPtr<IAutoRouterPath> path, bool modifyOrSet)
{
	CMapCARPath2CPointList::CPair* pVal = arPathPointsCache.PLookup(path.p);
	ASSERT(pVal != NULL);
	if (pVal == NULL)
		return false;

	HRESULT hr = UpdatePoints(path, *(pVal->value), modifyOrSet);
	if (FAILED(hr))
		return false;
	return true;
}

bool CAutoRouterGraph::UpdatePaths(void)
{
	std::vector<CComPtr<IAutoRouterPath> >::iterator iter;
	iter = paths.begin();

	while (iter != paths.end())
	{
		VARIANT_BOOL isAutoRouted = VARIANT_FALSE;
		COMTHROW((*iter)->IsAutoRouted(&isAutoRouted));
		if (isAutoRouted == VARIANT_TRUE) {
			if (!UpdatePathPointsFromCache(*iter))
				return false;
		}
		++iter;
	}
	return true;
}

void CAutoRouterGraph::GetPointList(CComPtr<IAutoRouterPath> path, CPointListPath& pointList) const
{
	SAFEARRAY* pArr = NULL;
	COMTHROW(path->GetPointList(&pArr));
	//one dim., long elements
	if ((pArr)->cDims == 1 && (pArr)->cbElements == 4)
	{
		pointList.RemoveAll();
		//length
		long elementNum = (pArr)->rgsabound[0].cElements;
		if (elementNum > 0)
		{
			ASSERT(elementNum % 2 == 0);
			//lock it before use
			SafeArrayLock(pArr);
			long* pArrElements = (long*) (pArr)->pvData;
			for (int i = 0; i < elementNum / 2; i++)
			{
				CPoint p(pArrElements[2 * i], pArrElements[2 * i + 1]);
				pointList.AddTail(p);
			}
			SafeArrayUnlock(pArr);
		}
	}
	//clear memory
	SafeArrayDestroy(pArr);
}

bool CAutoRouterGraph::UpdatePoints(CComPtr<IAutoRouterPath> path, const CPointListPath& pointList, bool modifyOrSet)
{
	VARIANT_BOOL isAutoRouted = VARIANT_FALSE;
	COMTHROW(path->IsAutoRouted(&isAutoRouted));
	if (isAutoRouted == VARIANT_FALSE)
		return true;

	SAFEARRAY* pArr = NULL;
	pArr = SafeArrayCreateVector(VT_I4, 0, 2 * pointList.GetSize());

	HRESULT hr = S_OK;
	long position = 0;
	POSITION pos = pointList.GetHeadPosition();
	while(pos && SUCCEEDED(hr))
	{
		CPoint point = pointList.GetNext(pos);
		hr = SafeArrayPutElement(pArr, &position, &point.x);
		ASSERT(SUCCEEDED(hr));
		position++;
		hr = SafeArrayPutElement(pArr, &position, &point.y);
		ASSERT(SUCCEEDED(hr));
		position++;
	}
	if (FAILED(hr))
		return false;

	if (modifyOrSet)
		hr = path->ModifyPoints(pArr);
	else
		hr = path->SetPoints(pArr);
	if (FAILED(hr))
		return false;

	//clear memory
	hr = SafeArrayDestroy(pArr);
	if (FAILED(hr))
		return false;

	return true;
}

void CAutoRouterGraph::AssertValid() const
{
	std::vector<CComPtr<IAutoRouterBox> >::const_iterator iter = boxes.begin();

	while (iter != boxes.end())
	{
		AssertValidBox(*iter);
		++iter;
	}

	std::vector<CComPtr<IAutoRouterPath> >::const_iterator iter2 = paths.begin();
	
	while(iter2 != paths.end())
	{
		AssertValidPath(*iter2);
		++iter2;
	}
}

void CAutoRouterGraph::AssertValidBox(CComPtr<IAutoRouterBox> box) const
{
	static_cast<CAutoRouterBox*>(box.p)->AssertValid();
	CComPtr<IAutoRouterGraph> ownerGraph;
	COMTHROW(box->GetOwner(&ownerGraph));
	ASSERT( ownerGraph.p == this );

	std::vector<CComPtr<IAutoRouterBox> >::const_iterator iter = std::find(boxes.begin(), boxes.end(), box);
	ASSERT (iter != boxes.end());
}

void CAutoRouterGraph::AssertValidPath(CComPtr<IAutoRouterPath> path) const
{
	static_cast<CAutoRouterPath*>(path.p)->AssertValid();
	CComPtr<IAutoRouterGraph> ownerGraph;
	COMTHROW(path->GetOwner(&ownerGraph));
	ASSERT( ownerGraph.p == this );

	std::vector<CComPtr<IAutoRouterPath> >::const_iterator iter = std::find(paths.begin(), paths.end(), path);
	ASSERT (iter != paths.end());

	CPointListPath pointList;
	GetPointList(path, pointList);

	CComPtr<IAutoRouterPort> startPort;
	COMTHROW(path->GetStartPort(&startPort));
	ASSERT(startPort != NULL);
	static_cast<CAutoRouterPort*>(startPort.p)->AssertValid();
	CComPtr<IAutoRouterBox> ownerBox;
	COMTHROW(startPort->GetOwner(&ownerBox));
	CComPtr<IAutoRouterGraph> boxOwnerGraph;
	COMTHROW(ownerBox->GetOwner(&boxOwnerGraph));
	ASSERT( boxOwnerGraph.p == this );
	static_cast<CAutoRouterBox*>(ownerBox.p)->AssertValidPort(startPort);

	VARIANT_BOOL isConnected = VARIANT_TRUE;
	COMTHROW(path->IsConnected(&isConnected));
	if( isConnected == VARIANT_TRUE )
		static_cast<CAutoRouterPort*>(startPort.p)->AssertValidStartEndPoint(pointList.GetHead(), Dir_None, 1);

	CComPtr<IAutoRouterPort> endPort;
	COMTHROW(path->GetEndPort(&endPort));
	ASSERT(endPort != NULL);
	static_cast<CAutoRouterPort*>(endPort.p)->AssertValid();
	CComPtr<IAutoRouterBox> ownerBox2;
	COMTHROW(endPort->GetOwner(&ownerBox2));
	CComPtr<IAutoRouterGraph> boxOwnerGraph2;
	COMTHROW(ownerBox2->GetOwner(&boxOwnerGraph2));
	ASSERT( boxOwnerGraph2.p == this );
	static_cast<CAutoRouterBox*>(ownerBox2.p)->AssertValidPort(endPort);

	if( isConnected == VARIANT_TRUE )
	{
		static_cast<CAutoRouterPort*>(endPort.p)->AssertValidStartEndPoint(pointList.GetTail(), Dir_None, 0);
	}
	else
	{
		VARIANT_BOOL hasNoPoint = VARIANT_TRUE;
		COMTHROW(path->HasNoPoint(&hasNoPoint));
		ASSERT( hasNoPoint == VARIANT_TRUE );
	}

	static_cast<CAutoRouterPath*>(path.p)->AssertValidPoints();

	if( !pointList.IsEmpty() )
	{
		ASSERT( pointList.GetCount() >= 2 );
		POSITION pos = pointList.GetHeadPosition();
		ASSERT( pos != NULL );

		ASSERT( IsPointInBox(pointList.GetNext(pos)) );

		while( pos != NULL )
		{
			CPoint p = pointList.GetNext(pos);
			if( pos != NULL )
				ASSERT( !IsPointInBox(p) );
			else
				ASSERT( IsPointInBox(p) );
		}
	}
}

void CAutoRouterGraph::DumpPaths(int pos, int c)
{
#ifdef _DEBUG_DEEP
/*	TRACE2("Paths dump pos %ld, c %ld:\n", pos, c);
	std::vector<CComPtr<IAutoRouterPath> >::iterator iter;
	iter = paths.begin();
	int i = 0;

	while (iter != paths.end())
	{
		TRACE1("%ld. Path:\n", i);
//		DumpPoints((*iter)->GetPoints(), "DumpPaths");

		++iter;
		i++;
	}

	DumpEdgeLists();*/
#endif
}

void CAutoRouterGraph::DumpEdgeLists(void)
{
#ifdef _DEBUG_DEEP
	horizontal.DumpEdges("Horizontal edges:");
	vertical.DumpEdges("Vertical edges:");
#endif
}

// CAutoRouterGraph
