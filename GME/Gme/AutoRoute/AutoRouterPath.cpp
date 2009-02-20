// AutoRouterPath.cpp : Implementation of CAutoRouterPath

#include "stdafx.h"
#include "AutoRouterPath.h"
#include "AutoRouterBox.h"
#include "AutoRouterGraph.h"
#include "AutoRouterPort.h"



CAutoRouterPath::CAutoRouterPath(): owner(NULL),
					startport(NULL),
					endport(NULL),
					attributes(ARPATH_Default),
					state(ARPATHST_Default),
					extptr(NULL)
{
}


void CAutoRouterPath::SetOwner(CComObjPtr<CAutoRouterGraph> o)
{	
	owner = o;
}

// --- Ports

void CAutoRouterPath::SetStartPort(CComObjPtr<CAutoRouterPort> port)
{
	startport = port;
}

void CAutoRouterPath::SetEndPort(CComObjPtr<CAutoRouterPort> port)
{
	endport = port;
}

void CAutoRouterPath::ClearPorts()
{
	startport = NULL;
	endport = NULL;
}

CComObjPtr<CAutoRouterPort> CAutoRouterPath::GetStartPort() const
{
	ASSERT( startport != NULL );
	return startport;
}

CComObjPtr<CAutoRouterPort> CAutoRouterPath::GetEndPort() const
{
	ASSERT( endport != NULL );
	return endport;
}

// --- Points

void CAutoRouterPath::AddTail(CPoint point)
{
	ASSERT( !IsConnected() );
	points.AddTail(point);
}

void CAutoRouterPath::DeleteAll()
{
	points.RemoveAll();
	state = ARPATHST_Default;
}

CPoint CAutoRouterPath::GetStartPoint() const
{
	ASSERT( points.GetCount() >= 2 );

	return points.GetHead();
}

CPoint CAutoRouterPath::GetEndPoint() const
{
	ASSERT( points.GetCount() >= 2 );

	return points.GetTail();
}

CPoint CAutoRouterPath::GetOutOfBoxStartPoint() const
{
	ASSERT( points.GetCount() >= 2 );

	POSITION pos = points.GetHeadPosition();
	CPoint p = points.GetNext(pos);
	EArDir d = GetDir(points.GetAt(pos) - p);
	ASSERT( IsRightAngle(d) );

	CComPtr<IAutoRouterBox> ownerStart;
	GetStartPort()->GetOwner(&ownerStart);
	CComObjPtr<CAutoRouterBox> startbox = static_cast<CAutoRouterBox*>(ownerStart.p);	

	GetPointCoord(p, d) = GetRectOuterCoord(startbox->GetRect(), d);
	ASSERT( points.GetAt(pos) == p || GetDir(points.GetAt(pos) - p) == d ); 

	return p;
}

CPoint CAutoRouterPath::GetOutOfBoxEndPoint() const
{
	ASSERT( points.GetCount() >= 2 );

	POSITION pos = points.GetTailPosition();
	CPoint p = points.GetPrev(pos);
	EArDir d = GetDir(points.GetAt(pos) - p);
	ASSERT( IsRightAngle(d) );

	CComPtr<IAutoRouterBox> ownerEnd;
	GetEndPort()->GetOwner(&ownerEnd);
	CComObjPtr<CAutoRouterBox> endbox = static_cast<CAutoRouterBox*>(ownerEnd.p);

	GetPointCoord(p, d) = GetRectOuterCoord(endbox->GetRect(), d);
	ASSERT( points.GetAt(pos) == p || GetDir(points.GetAt(pos) - p) == d ); 

	return p;
}

POSITION CAutoRouterPath::GetPointPosAt(CPoint point, int nearness) const
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

POSITION CAutoRouterPath::GetEdgePosAt(CPoint point, int nearness) const
{
	CPoint a;
	CPoint b;

	POSITION pos = GetTailEdge(a, b);
	while( pos != NULL )
	{
		if( IsPointNearLine(point, a, b, nearness) )
			return pos;

		GetPrevEdge(pos, a, b);
	}

	return NULL;
}

void CAutoRouterPath::SimplifyTrivially()
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

	EArDir dir12 = GetDir(p2-p1);

	POSITION pos3 = pos;
	ASSERT( pos3 != NULL );
	CPoint p3 = points.GetNext(pos);

	EArDir dir23 = GetDir(p3-p2); 

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

}

// --- Edges

POSITION CAutoRouterPath::GetHeadEdge(CPoint& start, CPoint& end) const
{
	if( points.GetCount() < 2 )
		return NULL;

	POSITION pos = points.GetHeadPosition();
	ASSERT( pos != NULL );

	start = points.GetNext(pos);
	ASSERT( pos != NULL );

	end = points.GetAt(pos);

	return pos;
}

POSITION CAutoRouterPath::GetTailEdge(CPoint& start, CPoint& end) const
{
	if( points.GetCount() < 2 )
		return NULL;

	POSITION pos = points.GetTailPosition();
	ASSERT( pos != NULL );

	end = points.GetPrev(pos);
	ASSERT( pos != NULL );

	start = points.GetAt(pos);

	return pos;
}

void CAutoRouterPath::GetNextEdge(POSITION& pos, CPoint& start, CPoint& end) const
{

	points.GetNext(pos);
	ASSERT( pos != NULL );

	POSITION p = pos;
	start = points.GetNext(p);
	if( p == NULL )
		pos = NULL;
	else
		end = points.GetAt(p);
}

void CAutoRouterPath::GetPrevEdge(POSITION& pos, CPoint& start, CPoint& end) const
{
	end = points.GetPrev(pos);
	if( pos != NULL )
		start = points.GetAt(pos);
}

void CAutoRouterPath::GetEdge(POSITION pos, CPoint& start, CPoint& end) const
{
	start = points.GetNext(pos);
	ASSERT( pos != NULL );

	end = points.GetAt(pos);
}

POSITION CAutoRouterPath::GetHeadEdgePtrs(CPoint*& start, CPoint*& end)
{
	if( points.GetCount() < 2 )
		return NULL;

	POSITION pos = points.GetHeadPosition();
	ASSERT( pos != NULL );

	start = &(points.GetNext(pos));
	ASSERT( pos != NULL );

	end = &(points.GetAt(pos));

	return pos;
}

POSITION CAutoRouterPath::GetTailEdgePtrs(CPoint*& start, CPoint*& end)
{
	if( points.GetCount() < 2 )
		return NULL;

	POSITION pos = points.GetTailPosition();
	ASSERT( pos != NULL );

	end = &(points.GetPrev(pos));
	ASSERT( pos != NULL );

	start = &(points.GetAt(pos));

	return pos;
}

void CAutoRouterPath::GetNextEdgePtrs(POSITION& pos, CPoint*& start, CPoint*& end)
{
	points.GetNext(pos);
	ASSERT( pos != NULL );

	POSITION p = pos;
	start = &(points.GetNext(p));
	if( p == NULL )
		pos = NULL;
	else
		end = &(points.GetAt(p));
}

void CAutoRouterPath::GetPrevEdgePtrs(POSITION& pos, CPoint*& start, CPoint*& end)
{
	end = &(points.GetPrev(pos));
	if( pos != NULL )
		start = &(points.GetAt(pos));
}

void CAutoRouterPath::GetEdgePtrs(POSITION pos, CPoint*& start, CPoint*& end)
{
	start = &(points.GetNext(pos));
	ASSERT( pos != NULL );

	end = &(points.GetAt(pos));
}

CPoint* CAutoRouterPath::GetStartPoint(POSITION pos)
{
	return &(points.GetAt(pos));
}

CPoint* CAutoRouterPath::GetEndPoint(POSITION pos)
{
	points.GetNext(pos);
	ASSERT( pos != NULL );

	return &(points.GetAt(pos));
}

CPoint* CAutoRouterPath::GetPointBeforeEdge(POSITION pos)
{
	points.GetPrev(pos);
	if( pos == NULL )
		return NULL;

	return &(points.GetAt(pos));
}

CPoint* CAutoRouterPath::GetPointAfterEdge(POSITION pos)
{
	points.GetNext(pos);
	ASSERT( pos != NULL );

	points.GetNext(pos);
	if( pos == NULL )
		return NULL;

	return &(points.GetAt(pos));
}

POSITION CAutoRouterPath::GetEdgePosBeforePoint(POSITION pos) const
{
	points.GetPrev(pos);
	return pos;
}

POSITION CAutoRouterPath::GetEdgePosAfterPoint(POSITION pos) const
{
	POSITION p = pos;
	points.GetNext(p);
	if( p == NULL )
		return NULL;

	return pos;
}

POSITION CAutoRouterPath::GetEdgePosForStartPoint(CPoint* startpoint)
{
	POSITION pos = points.GetHeadPosition();
	while( pos != NULL )
	{
		if( &(points.GetNext(pos)) == startpoint )
		{
			ASSERT( pos != NULL );
			points.GetPrev(pos);
			break;
		}
	}

	ASSERT( pos != NULL );
	return pos;
}

// --- Data

CRect CAutoRouterPath::GetSurroundRect() const
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

int CAutoRouterPath::IsPathClip(CRect rect) const
{
	CPoint a;
	CPoint b;

	POSITION pos = GetTailEdge(a, b);
	while( pos != NULL )
	{
		if( IsLineClipRect(a, b, rect) )
			return 1;

		GetPrevEdge(pos, a, b);
	}

	return 0;
}

void CAutoRouterPath::SetAttributes(unsigned int attr)
{
	attributes = attr;
}

void CAutoRouterPath::SetState(int s)
{
	ASSERT( owner != NULL );

	state = s;
}

EArDir CAutoRouterPath::GetEndDir() const
{
	unsigned int a = attributes & ARPATH_EndMask;
	return a & ARPATH_EndOnTop ? Dir_Top : 
	a & ARPATH_EndOnRight ? Dir_Right : 
	a & ARPATH_EndOnBottom ? Dir_Bottom :
	a & ARPATH_EndOnLeft ? Dir_Left : Dir_None;
}

EArDir CAutoRouterPath::GetStartDir() const
{
	unsigned int a = attributes & ARPATH_StartMask;
	return a & ARPATH_StartOnTop ? Dir_Top : 
	a & ARPATH_StartOnRight ? Dir_Right : 
	a & ARPATH_StartOnBottom ? Dir_Bottom :
	a & ARPATH_StartOnLeft ? Dir_Left : Dir_None;
}

STDMETHODIMP CAutoRouterPath::GetOwner(IAutoRouterGraph** result)
{
	return owner->QueryInterface(IID_IAutoRouterGraph,(void**)result);
}
STDMETHODIMP CAutoRouterPath::SetEndDir(long arpath_end)
{
	attributes = (attributes & ~ARPATH_EndMask) + (unsigned int)arpath_end;
	return S_OK;
}
STDMETHODIMP CAutoRouterPath::SetStartDir(long arpath_start)
{
	attributes = (attributes & ~ARPATH_StartMask) + (unsigned int)arpath_start;
	return S_OK;
}
STDMETHODIMP CAutoRouterPath::GetExtPtr(ULONGLONG* address)
{
	*address = extptr;
	return S_OK;
}
STDMETHODIMP CAutoRouterPath::SetExtPtr(ULONGLONG address)
{
	extptr = address;
	return S_OK;
}
STDMETHODIMP CAutoRouterPath::GetPointList(SAFEARRAY **pArr)
{
	HRESULT res = S_OK;

	if (!pArr) return E_POINTER;

	//set bounds
	SAFEARRAYBOUND bound[1];
	bound[0].lLbound	= 0;
	bound[0].cElements	= 2 * points.GetSize();

	//create safearray
	if (*pArr == NULL)
		*pArr = SafeArrayCreate(VT_I4,1,bound);
	else
		SafeArrayRedim(*pArr,bound);

	//lock before usage
	res = SafeArrayLock(*pArr);
	if (res) 
		return res;

	//get pointer to start
	long* pArrElements = (long*)(*pArr)->pvData;
	long position = 0;

	{
		POSITION pos;
		pos = points.GetHeadPosition();

		while(pos)
		{
			ASSERT(position < 32);
			CPoint point = points.GetNext(pos); 
			pArrElements[position]		= point.x;
			pArrElements[position + 1]	= point.y;
			position += 2;
		}
	}

	//unlock
	res = SafeArrayUnlock(*pArr);
	
	return res;

	//usage:
	//if ((*pArr)->cDims != 1 || (*pArr)->cbElements != 4)
}

STDMETHODIMP CAutoRouterPath::Destroy()
{
	SetStartPort(NULL);
	SetEndPort(NULL);

	return S_OK;
}

// CAutoRouterPath
