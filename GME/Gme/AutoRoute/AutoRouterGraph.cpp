// AutoRouterGraph.cpp : Implementation of CAutoRouterGraph

#include "stdafx.h"
#include "AutoRouterGraph.h"
#include "AutoRouterBox.h"
#include "AutoRouterPort.h"
#include "AutoRouterPath.h"
#include "AutoRouterEdge.h"

CAutoRouterGraph::CAutoRouterGraph():	horizontal(1),
										vertical(0)
{
}

// --- Boxes

void CAutoRouterGraph::Remove(CComObjPtr<CAutoRouterBox> box)
{

	DeleteBoxAndPortEdges(box);

	vector<CComObjPtr<CAutoRouterPath> >::iterator iter;
	iter = paths.begin();
	
	while( iter!=paths.end())
	{
		int iteratorChanged = 0;

		CComObjPtr<CAutoRouterPath> path = *iter;
		
		HRESULT res;
		CComPtr<IAutoRouterBox> ownerStart;
		res = path->GetStartPort()->GetOwner(&ownerStart);
		CComObjPtr<CAutoRouterBox> startbox = static_cast<CAutoRouterBox*>(ownerStart.p);

		CComPtr<IAutoRouterBox> ownerEnd;
		res = path->GetEndPort()->GetOwner(&ownerEnd);
		CComObjPtr<CAutoRouterBox> endbox = static_cast<CAutoRouterBox*>(ownerEnd.p);

		if( (startbox == box || endbox == box) )
		{
			//DeletePath:
			if( path->owner != NULL )
			{
				DeleteEdges(path.p);
				path->SetOwner(NULL);

				iter = paths.erase(iter);
				iteratorChanged = 1;
			}

			path->Destroy();
		}

		if (iteratorChanged==0)
			iter++;
	}

	box->SetOwner(NULL);

	vector<CComObjPtr<CAutoRouterBox> >::iterator iter2 = std::find(boxes.begin(), boxes.end(), box);

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

void CAutoRouterGraph::SetPortAttr(CComObjPtr<CAutoRouterPort> port, unsigned int attr)
{
	DisconnectPathsFrom(port);
	port->SetAttributes(attr);
}

int  CAutoRouterGraph::IsRectClipBoxes(CRect rect) const
{
	for (CAutoRouterBoxList::size_type i = 0; i<boxes.size(); i++)
	{
		if( IsRectClip(rect, boxes[i]->rect) )
			return 1;
	}
	return 0;
}

int  CAutoRouterGraph::IsLineClipBoxes(CPoint p1, CPoint p2) const
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

int  CAutoRouterGraph::CanBoxAt(CRect rect) const
{
	return !IsRectClipBoxes(InflatedRect(rect, 1));
}

CComObjPtr<CAutoRouterPath> CAutoRouterGraph::CreatePath() const
{
	CComObjPtr<CAutoRouterPath> path;
	CreateComObject(path);

	return path;
}

void CAutoRouterGraph::Add(CComObjPtr<CAutoRouterPath> path)
{
	ASSERT( path != NULL && path->owner == NULL );

	path->SetOwner(this);

	paths.push_back(path);

	AddEdges(path);
}

void CAutoRouterGraph::Remove(CComObjPtr<CAutoRouterPath> path)
{
	DeleteEdges(path.p);

	path->SetOwner(NULL);


	vector<CComObjPtr<CAutoRouterPath> >::iterator iter = std::find(paths.begin(), paths.end(), path);

	if (iter == paths.end())
	{
		//error
	}

	paths.erase(iter);
}

void CAutoRouterGraph::DeleteAllPaths()
{
	vector<CComObjPtr<CAutoRouterPath> >::iterator iter;
	iter = paths.begin();

	while (iter != paths.end())
	{
		DeleteEdges((static_cast<CAutoRouterPath*>((*iter).p)));

		(*iter)->Destroy();
		iter++;
	}

	paths.clear();
}

SAutoRouterEdge* CAutoRouterGraph::GetListEdgeAt(CPoint point, int nearness) const
{
	SAutoRouterEdge* edge;

	edge = horizontal.GetEdgeAt(point, nearness);
	if( edge )
		return edge;

	return vertical.GetEdgeAt(point, nearness);
}

// --- Boxes && Paths

CRect CAutoRouterGraph::GetSurroundRect() const
{
	CRect rect(0,0,0,0);

	for (CAutoRouterBoxList::size_type i = 0; i<boxes.size(); i++)
	{
		rect |= boxes[i]->rect;
	}

	for (CAutoRouterPathList::size_type i = 0; i<paths.size(); i++)
	{
		rect |= paths[i]->GetSurroundRect();
	}

	return rect;
}

CComObjPtr<CAutoRouterBox> CAutoRouterGraph::GetOutOfBox(CPoint& point, EArDir dir) const
{
	ASSERT( IsRightAngle(dir) );

	CComObjPtr<CAutoRouterBox> boxby = NULL;

	vector<CComObjPtr<CAutoRouterBox> >::const_iterator iter = boxes.begin();

	while (iter != boxes.end())
	{
		if( (static_cast<CAutoRouterBox*>((*iter).p))->rect.PtInRect(point) )
		{
			CRect& rect = (*iter)->rect;
			boxby = *iter;
			iter = boxes.begin();

			GetPointCoord(point, dir) = GetRectOuterCoord(rect, dir);
		}
		iter++;
	}

	return boxby;
}

CComObjPtr<CAutoRouterBox> CAutoRouterGraph::GoToNextBox(CPoint& point, EArDir dir, long stophere) const
{
	ASSERT( IsRightAngle(dir) );
	ASSERT( GetPointCoord(point, dir) != stophere );

	CComObjPtr<CAutoRouterBox> boxby = NULL;

	vector<CComObjPtr<CAutoRouterBox> >::const_iterator iter = boxes.begin();

	while (iter != boxes.end())
	{
		CComObjPtr<CAutoRouterBox> box = *iter;
		CRect& rect = box->rect;

		if( IsPointInDirFrom(point, rect, ReverseDir(dir)) &&
			IsPointBetweenSides(point, rect, dir) &&
			IsCoordInDirFrom(stophere, GetRectOuterCoord(rect, ReverseDir(dir)), dir) )
		{
			stophere = GetRectOuterCoord(rect, ReverseDir(dir));
			boxby = box;
		}
		iter++;
	}

	GetPointCoord(point, dir) = stophere;

	return boxby;
}

void CAutoRouterGraph::GetLimitsOfEdge(CPoint start, CPoint end, long& min, long& max) const
{
	long t;

	vector<CComObjPtr<CAutoRouterBox> >::const_iterator iter = boxes.begin();

	CComObjPtr<CAutoRouterBox> box;

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
			box = *iter;
			iter++;
			CRect& rect = box->rect;

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
			box = *iter;
			iter++;
			CRect& rect = box->rect;

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

void CAutoRouterGraph::Connect(CComObjPtr<CAutoRouterPath> path)
{
	CComObjPtr<CAutoRouterPort> startport = path->GetStartPort();
	CComObjPtr<CAutoRouterPort> endport = path->GetEndPort();

	EArDir startdir = path->GetStartDir();
	if( startdir == Dir_None                                                                // recalc startdir if empty
		|| startport->HasLimitedDirs() && !startport->CanHaveStartEndPointOn( startdir, 1)) // or is limited and userpref is invalid
		startdir = startport->GetStartEndDirTo(endport->GetCenter(), 1);

	EArDir enddir = path->GetEndDir();
	if( enddir == Dir_None                                                                  // like above
		|| endport->HasLimitedDirs() && !endport->CanHaveStartEndPointOn( enddir, 0))
		enddir = endport->GetStartEndDirTo(startport->GetCenter(), 0, startport == endport ? startdir : Dir_None );

	CPoint startpoint = startport->CreateStartEndPointOn(startdir);
	CPoint endpoint = endport->CreateStartEndPointOn(enddir);

	if( startpoint == endpoint )
		startpoint = StepOneInDir(startpoint, NextClockwiseDir(startdir));

	Connect(path, startpoint, endpoint);
}

void CAutoRouterGraph::Connect(CComObjPtr<CAutoRouterPath> path, CPoint startpoint, CPoint endpoint)
{
	ASSERT( !path->IsConnected() );
	ASSERT( startpoint != endpoint );

	EArDir startdir = path->GetStartPort()->OnWhichEdge(startpoint);
	EArDir enddir = path->GetEndPort()->OnWhichEdge(endpoint);
	ASSERT( IsRightAngle(startdir) && IsRightAngle(enddir) );

	CPoint start = startpoint;
	GetOutOfBox(start, startdir);
	ASSERT( start != startpoint );

	CPoint end = endpoint;
	GetOutOfBox(end, enddir);
	ASSERT( end != endpoint );

	CPointList ret;
	const CPointList& points = path->points;
	ASSERT( points.IsEmpty() );

	ConnectPoints(ret, start, end, startdir, enddir);

	path->DeleteAll();
	path->AddTail(startpoint);

	POSITION pos = ret.GetHeadPosition();
	while( pos != NULL )
		path->AddTail(ret.GetNext(pos));

	path->AddTail(endpoint);

	path->SimplifyTrivially();
	SimplifyPathPoints(path);
	CenterStairsInPathPoints(path);
	path->SetState(ARPATHST_Connected);

	AddEdges(path);
}

void CAutoRouterGraph::ConnectPoints(CPointList& ret, CPoint start, CPoint end, EArDir hintstartdir, EArDir hintenddir)
{
	ASSERT( ret.IsEmpty() );

	CPoint thestart = start;

	while( start != end )
	{
		EArDir dir1 = ExGetMajorDir(end-start);
		EArDir dir2 = ExGetMinorDir(end-start);
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

		CAutoRouterBox* box = GoToNextBox(start, dir1, end);
		if( start == old )
		{
			ASSERT( box != NULL );
			CRect& rect = box->rect;

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
	vector<CComObjPtr<CAutoRouterPath> >::iterator iter;
	iter = paths.begin();
	
	while(iter != paths.end())
	{
		Disconnect((static_cast<CAutoRouterPath*>((*iter).p)));
		iter++;
	}
}

void CAutoRouterGraph::Disconnect(CComObjPtr<CAutoRouterPath> path)
{
	if( path->IsConnected() )
		DeleteEdges(path.p);

	path->DeleteAll();
}

void CAutoRouterGraph::DisconnectPathsClipping(CRect rect)
{
	vector<CComObjPtr<CAutoRouterPath> >::reverse_iterator iter;
	iter = paths.rbegin();
	
	while(iter != paths.rend())
	{
		if( (static_cast<CAutoRouterPath*>((*iter).p))->IsPathClip(rect) )
			Disconnect((static_cast<CAutoRouterPath*>((*iter).p)));
		iter++;
	}
}

void CAutoRouterGraph::DisconnectPathsFrom(CComObjPtr<CAutoRouterBox> box)
{
	vector<CComObjPtr<CAutoRouterPath> >::reverse_iterator iter;
	iter = paths.rbegin();
	
	while(iter != paths.rend())
	{
		CComObjPtr<CAutoRouterPath> path = *iter;

		CComPtr<IAutoRouterBox> ownerStart;
		path->GetStartPort()->GetOwner(&ownerStart);
		CComObjPtr<CAutoRouterBox> startbox = static_cast<CAutoRouterBox*>(ownerStart.p);

		CComPtr<IAutoRouterBox> ownerEnd;
		path->GetEndPort()->GetOwner(&ownerEnd);
		CComObjPtr<CAutoRouterBox> endbox = static_cast<CAutoRouterBox*>(ownerEnd.p);

		if( (startbox == box || endbox == box) )
			Disconnect(path);

		iter++;
	}
}

void CAutoRouterGraph::DisconnectPathsFrom(CComObjPtr<CAutoRouterPort> port)
{
	vector<CComObjPtr<CAutoRouterPath> >::reverse_iterator iter;
	iter = paths.rbegin();
	
	while(iter != paths.rend())
	{
		CComObjPtr<CAutoRouterPath> path = *iter;

		CComObjPtr<CAutoRouterPort> startport = path->GetStartPort();
		CComObjPtr<CAutoRouterPort> endport = path->GetEndPort();

		if( (startport == port || endport == port) )
			Disconnect(path);

		iter++;
	}
}

// --- Edges

void CAutoRouterGraph::AddAllEdges()
{
	ASSERT( horizontal.IsEmpty() && vertical.IsEmpty() );

	vector<CComObjPtr<CAutoRouterBox> >::iterator iter;
	iter = boxes.begin();

	while (iter != boxes.end())
	{
		AddBoxAndPortEdges(*iter);
		iter++;
	}

	vector<CComObjPtr<CAutoRouterPath> >::iterator iterP;
	iterP = paths.begin();

	while (iterP != paths.end())
	{
		AddEdges((static_cast<CAutoRouterPath*>((*iterP).p)));
		iterP++;
	}
}

void CAutoRouterGraph::AddBoxAndPortEdges(CComObjPtr<CAutoRouterBox> box)
{
	ASSERT( box != NULL );

	AddEdges(box);

	for(int i=0; i<box->GetPortCount();i++)
	{
		AddEdges((box->GetPortList())[i]);
	}
}

void CAutoRouterGraph::DeleteBoxAndPortEdges(CComObjPtr<CAutoRouterBox> box)
{
	ASSERT( box != NULL );

	DeleteEdges(box.p);

	for(int i=0; i<box->GetPortCount();i++)
	{
		DeleteEdges(((box->GetPortList())[i]).p);
	}
}

// --- Path && Edges

int CAutoRouterGraph::CanDeleteTwoEdgesAt(CComObjPtr<CAutoRouterPath> path, POSITION pos)
{
	CPointList& points = path->points;

	POSITION pointpos = pos;
	CPoint* point = &(points.GetNext(pos));
	POSITION npointpos = pos; if( npointpos == NULL ) return 0;
	CPoint* npoint = &(points.GetNext(pos));
	POSITION nnpointpos = pos; if( nnpointpos == NULL ) return 0;
	CPoint* nnpoint = &(points.GetNext(pos));

	pos = pointpos;
	points.GetPrev(pos);
	POSITION ppointpos = pos; if( ppointpos == NULL ) return 0;
	CPoint* ppoint = &(points.GetPrev(pos));
	POSITION pppointpos = pos; if( pppointpos == NULL ) return 0;
	CPoint* pppoint = &(points.GetAt(pos));
	if( *npoint == *point) return 0; // direction of zero-length edges can't be determined, so don't delete them

	ASSERT( pppointpos != NULL && ppointpos != NULL && pointpos != NULL && npointpos != NULL && nnpointpos != NULL );
	ASSERT( pppoint != NULL && ppoint != NULL && point != NULL && npoint != NULL && nnpoint != NULL );

	EArDir dir = GetDir(*npoint - *point);
	ASSERT( IsRightAngle(dir) );
	int ishorizontal = IsHorizontal(dir);

	CPoint newpoint;
	GetPointCoord(newpoint, ishorizontal) = GetPointCoord(*npoint, ishorizontal);
	GetPointCoord(newpoint, !ishorizontal) = GetPointCoord(*ppoint, !ishorizontal);

	ASSERT( GetDir(newpoint - *ppoint) == dir );

	if( IsLineClipBoxes(newpoint, *npoint) ) return 0;
	if( IsLineClipBoxes(newpoint, *ppoint) ) return 0;

	return 1;
}

void CAutoRouterGraph::DeleteTwoEdgesAt(CComObjPtr<CAutoRouterPath> path, POSITION pos)
{
	CPointList& points = path->points;

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

	EArDir dir = GetDir(*npoint - *point);
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

	SAutoRouterEdge* ppedge = hlist.GetEdge(pppoint, ppoint);
	SAutoRouterEdge* pedge = vlist.GetEdge(ppoint, point);
	SAutoRouterEdge* nedge = hlist.GetEdge(point, npoint);
	SAutoRouterEdge* nnedge = vlist.GetEdge(npoint, nnpoint);

	ASSERT( ppedge != NULL && pedge != NULL && nedge != NULL && nnedge != NULL );

	vlist.Delete(pedge);
	hlist.Delete(nedge);

	points.RemoveAt(pointpos);
	points.RemoveAt(npointpos);
	points.SetAt(ppointpos, newpoint);

	ASSERT( ppedge->endpoint == ppoint && ppedge->endpoint_next == point );
	ppedge->endpoint_next = nnpoint;

	ASSERT( nnedge->startpoint == npoint && nnedge->startpoint_prev == point );
	nnedge->startpoint = ppoint;
	nnedge->startpoint_prev = pppoint;

	if( nnnpointpos != NULL )
	{
		SAutoRouterEdge* nnnedge = hlist.GetEdge(nnpoint, &(points.GetAt(nnnpointpos)));
		ASSERT( nnnedge != NULL );
		ASSERT( nnnedge->startpoint_prev == npoint && nnnedge->startpoint == nnpoint );
		nnnedge->startpoint_prev = ppoint;
	}

	if( *nnpoint == newpoint )
		DeleteSamePointsAt(path, ppointpos);
}

void CAutoRouterGraph::DeleteSamePointsAt(CComObjPtr<CAutoRouterPath> path, POSITION pos)
{
	CPointList& points = path->points;

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

	EArDir dir = GetDir(*point - *ppoint);
	ASSERT( IsRightAngle(dir) );
	int ishorizontal = IsHorizontal(dir);

	CAutoRouterEdgeList& hlist = GetEdgeList(ishorizontal);
	CAutoRouterEdgeList& vlist = GetEdgeList(!ishorizontal);

	SAutoRouterEdge* pedge = hlist.GetEdge(ppoint, point);
	SAutoRouterEdge* nedge = vlist.GetEdge(point, npoint);
	SAutoRouterEdge* nnedge = hlist.GetEdge(npoint, nnpoint);

	ASSERT( pedge != NULL && nedge != NULL && nnedge != NULL );

	vlist.Delete(pedge);
	hlist.Delete(nedge);

	points.RemoveAt(pointpos);
	points.RemoveAt(npointpos);

	if( pppointpos != NULL )
	{
		SAutoRouterEdge* ppedge = vlist.GetEdge(pppoint, ppoint);
		ASSERT( ppedge != NULL && ppedge->endpoint == ppoint && ppedge->endpoint_next == point );
		ppedge->endpoint_next = nnpoint;
	}

	ASSERT( nnedge->startpoint == npoint && nnedge->startpoint_prev == point );
	nnedge->startpoint = ppoint;
	nnedge->startpoint_prev = pppoint;

	if( nnnpointpos != NULL )
	{
		SAutoRouterEdge* nnnedge = vlist.GetEdge(nnpoint, &(points.GetAt(nnnpointpos)));
		ASSERT( nnnedge != NULL && nnnedge->startpoint_prev == npoint && nnnedge->startpoint == nnpoint );
		nnnedge->startpoint_prev = ppoint;
	}
}

int CAutoRouterGraph::SimplifyPaths()
{
	int was = 0;

	vector<CComObjPtr<CAutoRouterPath> >::iterator iter;
	iter = paths.begin();

	while (iter != paths.end())
	{
		CComObjPtr<CAutoRouterPath> path = *iter;
		iter++;

		CPointList& points = path->points;
		POSITION pointpos = points.GetHeadPosition();

		while( pointpos != NULL )
		{
			if( CanDeleteTwoEdgesAt(path, pointpos) )
			{
				DeleteTwoEdgesAt(path, pointpos);
				was = 1;
				break;
			}
			points.GetNext(pointpos);
		}
	}

	return was;
}

#pragma warning(disable: 4700)
void CAutoRouterGraph::CenterStairsInPathPoints(CComObjPtr<CAutoRouterPath> path)
{
	ASSERT( path != NULL );
	ASSERT( !path->IsConnected() );
	CPointList& points = path->points;
	ASSERT( points.GetCount() >= 2 );

	CPoint p1;
	CPoint p2;
	CPoint p3;
	CPoint p4;

	POSITION p1p = NULL;
	POSITION p2p = NULL;
	POSITION p3p = NULL;
	POSITION p4p = NULL;

	EArDir d12 = Dir_None;
	EArDir d23 = Dir_None;
	EArDir d34 = Dir_None;

	POSITION pos = points.GetHeadPosition();
	ASSERT( pos != NULL );

	p1p = pos;
	p1 = points.GetNext(pos);

	while( pos != NULL )
	{
		p4p = p3p;
		p3p = p2p;
		p2p = p1p;
		p1p = pos;

		p4 = p3;
		p3 = p2;
		p2 = p1;
		p1 = points.GetNext(pos);

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
					!IsLineClipBoxes(p1p == points.GetTailPosition() ? path->GetOutOfBoxEndPoint() : p1, np2) &&
					!IsLineClipBoxes(p4p == points.GetHeadPosition() ? path->GetOutOfBoxStartPoint() : p4, np3) )
				{
					p2 = np2;
					p3 = np3;
					points.SetAt(p2p, p2);
					points.SetAt(p3p, p3);
				}
			}
		}
	}
}

void CAutoRouterGraph::SimplifyPathPoints(CComObjPtr<CAutoRouterPath> path)
{
	ASSERT( path != NULL );
	ASSERT( !path->IsConnected() );
	CPointList& points = path->points;
	ASSERT( points.GetCount() >= 2 );

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

	POSITION pos = points.GetHeadPosition();
	ASSERT( pos != NULL );

	p1p = pos;
	p1 = points.GetNext(pos);

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
		p1 = points.GetNext(pos);

		if( p5p != NULL )
		{
			ASSERT( p1p != NULL && p2p != NULL && p3p != NULL && p4p != NULL && p5p != NULL );
			ASSERT( p1 != p2 && p2 != p3 && p3 != p4 && p4 != p5 );

			EArDir d = GetDir(p2 - p1);
			ASSERT( IsRightAngle(d) );
			int h = IsHorizontal(d);

			CPoint np3;
			GetPointCoord(np3, h) = GetPointCoord(p5, h);
			GetPointCoord(np3, !h) = GetPointCoord(p1, !h);

			if( !IsLineClipBoxes(p2, np3) && !IsLineClipBoxes(np3, p4) )
			{
				points.RemoveAt(p2p);
				points.RemoveAt(p4p);
				points.SetAt(p3p, np3);
				if( np3 == p1 )
					points.RemoveAt(p1p);
				if( np3 == p5 )
					points.RemoveAt(p5p);

				p1p = NULL;
				p2p = NULL;
				p3p = NULL;
				p4p = NULL;

				pos = points.GetHeadPosition();
			}
		}
	}
}
#pragma warning(default: 4700)

void CAutoRouterGraph::ConnectAllDisconnectedPaths()
{
	vector<CComObjPtr<CAutoRouterPath> >::iterator iter;
	iter = paths.begin();

	while (iter != paths.end())
	{
		CComObjPtr<CAutoRouterPath> path = *iter;

		if( !path->IsConnected() )
			Connect(path);

		iter++;
	}
}

// --- SelfPoints

void  CAutoRouterGraph::CalculateSelfPoints()
{
	selfpoints[0].x = ED_MINCOORD;
	selfpoints[0].y = ED_MINCOORD;

	selfpoints[1].x = ED_MAXCOORD;
	selfpoints[1].y = ED_MINCOORD;

	selfpoints[2].x = ED_MAXCOORD;
	selfpoints[2].y = ED_MAXCOORD;

	selfpoints[3].x = ED_MINCOORD;
	selfpoints[3].y = ED_MAXCOORD;
}

STDMETHODIMP CAutoRouterGraph::CreateBox(IAutoRouterBox** result)
{
	CComObjPtr<CAutoRouterBox> box;
	CreateComObject(box);

	return ::QueryInterface(box,result);
}
STDMETHODIMP CAutoRouterGraph::Add(IAutoRouterBox* box)
{
	CComObjPtr<CAutoRouterBox> b = static_cast<CAutoRouterBox*>(box);

	DisconnectPathsClipping(b->GetRect());

	b->SetOwner(this);

	boxes.push_back(b);

	AddBoxAndPortEdges(b);

	return S_OK; 
}
STDMETHODIMP CAutoRouterGraph::DeleteBox(IAutoRouterBox* box)
{
	CComObjPtr<CAutoRouterBox> b = static_cast<CAutoRouterBox*>(box);

	if( b->owner != NULL )
	{
		Remove(b);
	}
	
	return b->Destroy();
}
STDMETHODIMP CAutoRouterGraph::ShiftBy(IAutoRouterBox* box, long sizeX, long sizeY)
{
	CSize offset(sizeX, sizeY);

	CComObjPtr<CAutoRouterBox> b = static_cast<CAutoRouterBox*>(box);

	DeleteBoxAndPortEdges(b);
	b->ShiftBy(offset);
	AddBoxAndPortEdges(b);

	DisconnectPathsClipping(b->GetRect());
	DisconnectPathsFrom(b);

	return S_OK;
}

STDMETHODIMP CAutoRouterGraph::AutoRoute(long* result)
{
	ConnectAllDisconnectedPaths();

	int updated = 0;
	int last = 0;
	int c = 100;		// max # of total op
	int dm = 10;		// max # of distribution op
	int d = 0;

	while( c > 0 )
	{
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

		if( c > 0 )
		{
			if( last == 2 )
				break;

			c--;
			if( horizontal.Block_ScanBackward() )
			{
				updated = 1;

				do
				c--;
				while( c > 0 && horizontal.Block_ScanBackward() );

				if( last < 2 || last > 5 )
					d = 0;
				else if( ++d >= dm )
					break;

				last = 2;
			}
		}

		if( c > 0 )
		{
			if( last == 3 )
				break;

			c--;
			if( horizontal.Block_ScanForward() )
			{
				updated = 1;

				do
				c--;
				while( c > 0 && horizontal.Block_ScanForward() );

				if( last < 2 || last > 5 )
					d = 0;
				else if( ++d >= dm )
					break;

				last = 3;
			}
		}

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

	if( c <= 0 )
	{
		// MessageBeep(MB_ICONEXCLAMATION);
		updated = -1;
	}

	*result = updated;
	return S_OK;
}
STDMETHODIMP CAutoRouterGraph::DeletePath( IAutoRouterPath* path)
{
	CComObjPtr<CAutoRouterPath> p = static_cast<CAutoRouterPath*>(path);

	if( p->owner != NULL )
	{
		Remove(p);
	}

	return p->Destroy();	
}
STDMETHODIMP CAutoRouterGraph::DeleteAll() 
{ 
	DeleteAllPaths(); 
	DeleteAllBoxes(); 
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

STDMETHODIMP CAutoRouterGraph::GetPathAt(long pointX, long pointY, long nearness, IAutoRouterPath** result)
{
	vector<CComObjPtr<CAutoRouterPath> >::iterator iter;
	iter = paths.begin();

	while (iter != paths.end())
	{
		CComObjPtr<CAutoRouterPath> path = *iter;
		if( path->IsPathAt(CPoint(pointX,pointY), nearness) )
			return path->QueryInterface(IID_IAutoRouterPath,(void**)result);

		iter++;
	}

	result = NULL;
	return S_OK;
}

STDMETHODIMP CAutoRouterGraph::AddPath(IAutoRouterPort* startport, IAutoRouterPort* endport, IAutoRouterPath** result)
{
	CComObjPtr<CAutoRouterPath> path = CreatePath();

	path->SetStartPort(static_cast<CAutoRouterPort*>(startport));
	path->SetEndPort(static_cast<CAutoRouterPort*>(endport));
	Add(path);

	return path->QueryInterface(IID_IAutoRouterPath,(void**)result);
}


// CAutoRouterGraph
