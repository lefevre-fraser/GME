// AutoRouterPort.cpp : Implementation of CAutoRouterPort
#include "stdafx.h"
#include "AutoRouterPort.h"
#include "AutoRouterBox.h"


CAutoRouterPort::CAutoRouterPort():	owner(NULL),
									limitedDirections( false),
									rect(0,0,0,0),
									attributes(ARPORT_Default)
{
	CalculateSelfPoints();
}

HRESULT CAutoRouterPort::FinalConstruct(void)
{
	return S_OK;
}

void CAutoRouterPort::FinalRelease(void)
{
	this->SetOwner(NULL);
}

// Private methods

// --- Data

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

// COM interface

STDMETHODIMP CAutoRouterPort::GetOwner(IAutoRouterBox** result)
{
	return owner->QueryInterface(IID_IAutoRouterBox,(void**)result);
}

STDMETHODIMP CAutoRouterPort::HasOwner(VARIANT_BOOL* result)
{
	if (owner != NULL)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::SetOwner(IAutoRouterBox* box)
{
	owner = box;

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::GetRect(long* p1, long* p2, long* p3, long* p4)
{
	*p1 = rect.left;
	*p2 = rect.top;
	*p3 = rect.right;
	*p4 = rect.bottom;

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::IsRectEmpty(VARIANT_BOOL* result)
{
	if (rect.IsRectEmpty())
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::GetCenter(long* px, long* py)
{
	const CPoint center = rect.CenterPoint();
	*px = center.x;
	*py = center.y;

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::SetRect(long p1, long p2, long p3, long p4)
{
	CRect r(p1, p2, p3, p4);
	ASSERT( r.Width() >= 3 && r.Height() >= 3 );

	rect = r;
	CalculateSelfPoints();

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::ShiftBy(long offsetx, long offsety)
{
	ASSERT( !rect.IsRectEmpty() );

	const CPoint offset(offsetx, offsety);
	rect += offset;

	CalculateSelfPoints();

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::GetSelfPoints(long* p1x, long* p1y, long* p2x, long* p2y, long* p3x, long* p3y, long* p4x, long* p4y)
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

STDMETHODIMP CAutoRouterPort::GetAttributes(long* result)
{
	*result = attributes;
	return S_OK;
}

STDMETHODIMP CAutoRouterPort::SetAttributes(long attr)
{
	attributes = (unsigned int)attr;
	return S_OK;
}

STDMETHODIMP CAutoRouterPort::IsConnectToCenter(VARIANT_BOOL* result)
{
	if ((attributes & ARPORT_ConnectToCenter) != 0)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::HasLimitedDirs(VARIANT_BOOL* result)
{
	if (limitedDirections)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::SetLimitedDirs(VARIANT_BOOL ltd)
{
	limitedDirections = (ltd == VARIANT_TRUE);
	return S_OK;
}

STDMETHODIMP CAutoRouterPort::IsPortAt(long px, long py, long nearness, VARIANT_BOOL* result)
{
	const CPoint point(px, py);
	if (IsPointIn(point, rect, nearness))
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::IsPortClip(long p1, long p2, long p3, long p4, VARIANT_BOOL* result)
{
	const CRect r(p1, p2, p3, p4);
	if (IsRectClip(rect, r))
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::IsPortIn(long p1, long p2, long p3, long p4, VARIANT_BOOL* result)
{
	const CRect r(p1, p2, p3, p4);
	if (IsRectIn(rect, r))
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::OnWhichEdge(long px, long py, RoutingDirection* result)
{
	RoutingDirection dir = ::OnWhichEdge(rect, CPoint(px, py));
	*result = dir;

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::CanHaveStartEndPointOn(RoutingDirection dir, long isstart, VARIANT_BOOL* result)
{
	int d = (int) dir;
	ASSERT( 0 <= d && d <= 3 );

	if( isstart )
		d += 4;

	if ((attributes & (1 << d)) != 0)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::CanHaveStartEndPoint(long isstart, VARIANT_BOOL* result)
{
	if ((attributes & (isstart ? ARPORT_StartOnAll : ARPORT_EndOnAll)) != 0)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::CanHaveStartEndPointHorizontal(long ishorizontal, VARIANT_BOOL* result)
{
	if ((attributes & (ishorizontal ? ARPORT_StartEndHorizontal : ARPORT_StartEndVertical)) != 0)
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::GetStartEndDirTo(long px, long py, long isstart, RoutingDirection notthis, RoutingDirection* result)
{
	ASSERT( !rect.IsRectEmpty() );

	const CPoint point(px, py);
	CSize offset = point - rect.CenterPoint();

	HRESULT hr;
	VARIANT_BOOL canHave = VARIANT_FALSE;

	RoutingDirection dir1 = GetMajorDir(offset);

	if (dir1 != notthis)
	{
		hr = CanHaveStartEndPointOn(dir1, isstart, &canHave);
		ASSERT(SUCCEEDED(hr));
		if (FAILED(hr))
			return hr;
		if (canHave == VARIANT_TRUE)
		{
			*result = dir1;
			return S_OK;
		}
	}

	RoutingDirection dir2 = GetMinorDir(offset);

	if (dir2 != notthis)
	{
		hr = CanHaveStartEndPointOn(dir2, isstart, &canHave);
		ASSERT(SUCCEEDED(hr));
		if (FAILED(hr))
			return hr;
		if (canHave == VARIANT_TRUE)
		{
			*result = dir2;
			return S_OK;
		}
	}

	RoutingDirection dir3 = ReverseDir(dir2);

	if (dir3 != notthis)
	{
		hr = CanHaveStartEndPointOn(dir3, isstart, &canHave);
		ASSERT(SUCCEEDED(hr));
		if (FAILED(hr))
			return hr;
		if (canHave == VARIANT_TRUE)
		{
			*result = dir3;
			return S_OK;
		}
	}

	RoutingDirection dir4 = ReverseDir(dir1);

	if (dir4 != notthis)
	{
		hr = CanHaveStartEndPointOn(dir4, isstart, &canHave);
		ASSERT(SUCCEEDED(hr));
		if (FAILED(hr))
			return hr;
		if (canHave == VARIANT_TRUE)
		{
			*result = dir4;
			return S_OK;
		}
	}

	hr = CanHaveStartEndPointOn(dir1, isstart, &canHave);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	if (canHave == VARIANT_TRUE)
	{
		*result = dir1;
		return S_OK;
	}

	hr = CanHaveStartEndPointOn(dir2, isstart, &canHave);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	if (canHave == VARIANT_TRUE)
	{
		*result = dir2;
		return S_OK;
	}

	hr = CanHaveStartEndPointOn(dir3, isstart, &canHave);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	if (canHave == VARIANT_TRUE)
	{
		*result = dir3;
		return S_OK;
	}

	hr = CanHaveStartEndPointOn(dir4, isstart, &canHave);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	if (canHave == VARIANT_TRUE)
	{
		*result = dir4;
		return S_OK;
	}

	*result = Dir_Top;
	return S_OK;
}

STDMETHODIMP CAutoRouterPort::CanCreateStartEndPointAt(long px, long py, long isstart, long nearness, VARIANT_BOOL* result)
{
	VARIANT_BOOL canHave = VARIANT_FALSE;
	HRESULT hr = CanHaveStartEndPoint(isstart, &canHave);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	if (canHave == VARIANT_TRUE && IsPointIn(CPoint(px, py), rect, nearness))
		*result = VARIANT_TRUE;
	else
		*result = VARIANT_FALSE;

	return S_OK;
}

STDMETHODIMP CAutoRouterPort::CreateStartEndPointAt(long px, long py, long isstart, long* resultX, long* resultY)
{
	ASSERT( !rect.IsRectEmpty() );

	RoutingDirection dir = Dir_None;

	CPoint point(px, py);
	CArFindNearestLine nearest(point);

	VARIANT_BOOL canHave = VARIANT_FALSE;

	HRESULT hr = CanHaveStartEndPointOn(Dir_Top, isstart, &canHave);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	if( canHave == VARIANT_TRUE && nearest.HLine(rect.left, rect.right - 1, rect.top) )
		dir = Dir_Top;

	hr = CanHaveStartEndPointOn(Dir_Right, isstart, &canHave);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	if( canHave == VARIANT_TRUE && nearest.VLine(rect.top, rect.bottom - 1, rect.right - 1) )
		dir = Dir_Right;

	hr = CanHaveStartEndPointOn(Dir_Bottom, isstart, &canHave);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	if( canHave == VARIANT_TRUE && nearest.HLine(rect.left, rect.right - 1, rect.bottom - 1) )
		dir = Dir_Bottom;

	hr = CanHaveStartEndPointOn(Dir_Left, isstart, &canHave);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	if( canHave == VARIANT_TRUE && nearest.VLine(rect.top, rect.bottom - 1, rect.left) )
		dir = Dir_Left;

	ASSERT( IsRightAngle(dir) );

	VARIANT_BOOL isConnect = VARIANT_FALSE;
	hr = IsConnectToCenter(&isConnect);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	if( isConnect == VARIANT_TRUE )
	{
		hr = CreateStartEndPointOn(dir, resultX, resultY);
		return S_OK;
	}

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
		point.x = rect.right - 1;
		break;

	case Dir_Bottom:
		point.y = rect.bottom - 1;
		break;

	case Dir_Left:
		point.x = rect.left;
		break;
	}

	*resultX = point.x;
	*resultY = point.y;
	return S_OK;
}

STDMETHODIMP CAutoRouterPort::CreateStartEndPointOn(RoutingDirection dir, long* resultX, long* resultY)
{
	ASSERT( !rect.IsRectEmpty() );
	ASSERT( IsRightAngle(dir) );

	CPoint retPoint;
	switch( dir )
	{
	case Dir_Top: {
			retPoint = CPoint((rect.left + rect.right) / 2, rect.top);
			*resultX = retPoint.x;
			*resultY = retPoint.y;
			return S_OK;
		}

	case Dir_Bottom: {
			retPoint = CPoint((rect.left + rect.right) / 2, rect.bottom - 1);
			*resultX = retPoint.x;
			*resultY = retPoint.y;
			return S_OK;
		}

	case Dir_Left: {
			retPoint = CPoint(rect.left, (rect.top + rect.bottom) / 2);
			*resultX = retPoint.x;
			*resultY = retPoint.y;
			return S_OK;
		}
	}

	retPoint = CPoint(rect.right - 1, (rect.top + rect.bottom) / 2);
	*resultX = retPoint.x;
	*resultY = retPoint.y;
	return S_OK;
}

STDMETHODIMP CAutoRouterPort::CreateStartEndPointTo(long px, long py, long isstart, long* resultX, long* resultY)
{
	RoutingDirection dir;
	HRESULT hr = GetStartEndDirTo(px, py, isstart, Dir_None, &dir);
	ASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;
	hr = CreateStartEndPointOn(dir, resultX, resultY);
	ASSERT(SUCCEEDED(hr));

	return hr;
}

#ifdef _DEBUG
void CAutoRouterPort::AssertValid() const
{
}

void CAutoRouterPort::AssertValidStartEndPoint(const CPoint& point, RoutingDirection dir, int isstart)
{
	ASSERT( !rect.IsRectEmpty() );

	RoutingDirection comDir;
	COMTHROW(OnWhichEdge(point.x, point.y, &comDir));
	if( dir == Dir_None )
	{
		dir = comDir;
		ASSERT( IsRightAngle(dir) );
	}
	else
	{
		ASSERT( dir == comDir );
	}

	VARIANT_BOOL canHave = VARIANT_FALSE;
	COMTHROW(CanHaveStartEndPointOn(dir, isstart, &canHave));
	ASSERT( canHave == VARIANT_TRUE );
}
#endif
