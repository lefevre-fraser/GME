// AutoRouterPort.cpp : Implementation of CAutoRouterPort
#include "stdafx.h"
#include "AutoRouterPort.h"
#include "gmelib_i.c"
#include "AutoRouterBox.h"


CAutoRouterPort::CAutoRouterPort():	owner(NULL),
									limitedDirections( false),
									rect(0,0,0,0),
									attributes(ARPORT_Default)
{
	CalculateSelfPoints();
}
int CAutoRouterPort::CanHaveStartEndPointOn(EArDir dir, int isstart) const
{
	int d = (int) dir;
	ASSERT( 0 <= d && d <= 3 );

	if( isstart )
		d += 4;

	return (attributes & (1 << d)) != 0;
}

int CAutoRouterPort::CanHaveStartEndPoint(int isstart) const
{
	return (attributes & (isstart ? ARPORT_StartOnAll : ARPORT_EndOnAll)) != 0;
}

int CAutoRouterPort::CanHaveStartEndPointHorizontal(int ishorizontal) const
{
	return (attributes & (ishorizontal ? ARPORT_StartEndHorizontal : ARPORT_StartEndVertical)) != 0;
}

EArDir CAutoRouterPort::GetStartEndDirTo(CPoint point, int isstart, EArDir notthis) const
{
	ASSERT( !IsRectEmpty() );

	CSize offset = point - rect.CenterPoint();

	EArDir dir1 = GetMajorDir(offset);

	if( dir1 != notthis && CanHaveStartEndPointOn(dir1, isstart) )
		return dir1;

	EArDir dir2 = GetMinorDir(offset);

	if( dir2 != notthis && CanHaveStartEndPointOn(dir2, isstart) )
		return dir2;

	EArDir dir3 = ReverseDir(dir2);

	if( dir3 != notthis && CanHaveStartEndPointOn(dir3, isstart) )
		return dir3;

	EArDir dir4 = ReverseDir(dir1);

	if( dir4 != notthis && CanHaveStartEndPointOn(dir4, isstart) )
		return dir4;

	if( CanHaveStartEndPointOn(dir1, isstart) )
		return dir1;

	if( CanHaveStartEndPointOn(dir2, isstart) )
		return dir2;

	if( CanHaveStartEndPointOn(dir3, isstart) )
		return dir3;

	if( CanHaveStartEndPointOn(dir4, isstart) )
		return dir4;

	return Dir_Top;
}

int CAutoRouterPort::CanCreateStartEndPointAt(CPoint point, int isstart, int nearness) const
{
	return CanHaveStartEndPoint(isstart) && IsPointIn(point, rect, nearness);
}

CPoint CAutoRouterPort::CreateStartEndPointAt(CPoint point, int isstart) const
{
	ASSERT( !IsRectEmpty() );

	EArDir dir = Dir_None;

	CArFindNearestLine nearest(point);

	if( CanHaveStartEndPointOn(Dir_Top, isstart) && nearest.HLine(rect.left, rect.right-1, rect.top) )
		dir = Dir_Top;

	if( CanHaveStartEndPointOn(Dir_Right, isstart) && nearest.VLine(rect.top, rect.bottom-1, rect.right-1) )
		dir = Dir_Right;

	if( CanHaveStartEndPointOn(Dir_Bottom, isstart) && nearest.HLine(rect.left, rect.right-1, rect.bottom-1) )
		dir = Dir_Bottom;

	if( CanHaveStartEndPointOn(Dir_Left, isstart) && nearest.VLine(rect.top, rect.bottom-1, rect.left) )
		dir = Dir_Left;

	ASSERT( IsRightAngle(dir) );

	if( IsConnectToCenter() )
		return CreateStartEndPointOn(dir);

	if( point.x < rect.left )
		point.x = rect.left;
	else if( rect.right <= point.x )
		point.x = rect.right-1;

	if( point.y < rect.top )
		point.y = rect.top;
	else if( rect.bottom <= point.y )
		point.y = rect.bottom-1;

	switch(dir)
	{
	case Dir_Top:
		point.y = rect.top;
		break;

	case Dir_Right:
		point.x = rect.right-1;
		break;

	case Dir_Bottom:
		point.y = rect.bottom-1;
		break;

	case Dir_Left:
		point.x = rect.left;
		break;
	}

	return point;
}

CPoint CAutoRouterPort::CreateStartEndPointOn(EArDir dir) const
{
	ASSERT( !IsRectEmpty() );
	ASSERT( IsRightAngle(dir) );

	switch( dir )
	{
	case Dir_Top:
		return CPoint((rect.left + rect.right)/2, rect.top);

	case Dir_Bottom:
		return CPoint((rect.left + rect.right)/2, rect.bottom-1);

	case Dir_Left:
		return CPoint(rect.left, (rect.top + rect.bottom)/2);
	}

	return CPoint(rect.right-1, (rect.top + rect.bottom)/2);
}


// --- Data


void CAutoRouterPort::ShiftBy(CSize offset)
{
	ASSERT( !rect.IsRectEmpty() );

	rect += offset;
	CalculateSelfPoints();
}

void CAutoRouterPort::CalculateSelfPoints()
{
	selfpoints[0].x = rect.left;
	selfpoints[0].y = rect.top;

	selfpoints[1].x = rect.right - 1;
	selfpoints[1].y = rect.top;

	selfpoints[2].x = rect.right - 1;
	selfpoints[2].y = rect.bottom - 1;

	selfpoints[3].x = rect.left;
	selfpoints[3].y = rect.bottom - 1;
}

void CAutoRouterPort::SetOwner(CComObjPtr<CAutoRouterBox> o)
{
	owner = o;
}


STDMETHODIMP CAutoRouterPort::SetRect(long p1, long p2, long p3, long p4)
{
	CRect r(p1, p2, p3, p4);
	ASSERT( r.Width() >= 3 && r.Height() >= 3 );

	rect = r;
	CalculateSelfPoints();

	return S_OK;
}
STDMETHODIMP CAutoRouterPort::SetAttributes(long attr)
{
	attributes = (unsigned int)attr;
	return S_OK;
}
STDMETHODIMP CAutoRouterPort::SetLimitedDirs( long p_ltd) 
{ 
	limitedDirections = (p_ltd != 0); 
	return S_OK;
}
STDMETHODIMP CAutoRouterPort::GetOwner(IAutoRouterBox** result)
{
	return owner->QueryInterface(IID_IAutoRouterBox,(void**)result);
}
