
#ifndef __ARHELPER_H
#define __ARHELPER_H

// --------------------------- CRect && CPoint


CRect InflatedRect(const CRect& rect, int a);
CRect DeflatedRect(const CRect& rect, int a);

int IsPointNear(const CPoint& p1, const CPoint& p2, int nearness = 0);
int IsPointIn(const CPoint& point, const CRect& rect, int nearness = 0);
int IsRectIn(const CRect& r1, const CRect& r2);
int IsRectClip(const CRect& r1, const CRect& r2);

int IsPointNearHLine(const CPoint& p, long x1, long x2, long y, int nearness = 0);
int IsPointNearVLine(const CPoint& p, long y1, long y2, long x, int nearness = 0);
int DistanceFromHLine(const CPoint& p, long x1, long x2, long y);
int DistanceFromVLine(const CPoint& p, long y1, long y2, long x);

int IsPointNearLine(const CPoint& point, const CPoint& start, const CPoint& end, int nearness = 0);
int IsLineMeetHLine(const CPoint& start, const CPoint& end, long x1, long x2, long y);
int IsLineMeetVLine(const CPoint& start, const CPoint& end, long y1, long y2, long x);
int IsLineClipRect(const CPoint& start, const CPoint& end, const CRect& rect);
int Intersect(long first_x1, long first_x2, long second_x1, long second_x2);

int IsOpeningBracket(CPoint* start_prev, CPoint* start, CPoint* end, CPoint* end_next, int ishorizontal);
int IsClosingBracket(CPoint* start_prev, CPoint* start, CPoint* end, CPoint* end_next, int ishorizontal);


// --------------------------- EArDir


enum EArDir
{
	Dir_None = -1,
	Dir_Top,
	Dir_Right,
	Dir_Bottom,
	Dir_Left,
	Dir_Skew
};

inline int IsHorizontal(EArDir dir) { return dir == Dir_Right || dir == Dir_Left; }
inline int IsVertical(EArDir dir) { return dir == Dir_Top || dir == Dir_Bottom; }
inline int IsRightAngle(EArDir dir) { return Dir_Top <= dir && dir <= Dir_Left; }
inline int IsTopLeft(EArDir dir) { return dir == Dir_Top || dir == Dir_Left; }
inline int IsBottomRight(EArDir dir) { return dir == Dir_Bottom || dir == Dir_Right; }
int AreInRightAngle(EArDir dir1, EArDir dir2);
EArDir NextClockwiseDir(EArDir dir);
EArDir PrevClockwiseDir(EArDir dir);
EArDir ReverseDir(EArDir dir);

CPoint StepOneInDir(const CPoint& point, EArDir dir);
long& GetRectCoord(CRect& rect, EArDir dir);
long GetRectOuterCoord(const CRect& rect, EArDir dir);
inline long& GetPointCoord(CPoint& point, int ishorizontal) { return ishorizontal ? point.x : point.y; }
inline long& GetPointCoord(CPoint& point, EArDir dir) { return IsHorizontal(dir) ? point.x : point.y; }
inline long ChooseInDir(long a, long b, EArDir dir) { return IsTopLeft(dir) ? min(a,b) : max(a,b); }

EArDir GetMajorDir(const CSize& offset);
EArDir GetMinorDir(const CSize& offset);
EArDir ExGetMajorDir(const CSize& offset);
EArDir ExGetMinorDir(const CSize& offset);
EArDir GetDir(const CSize& offset, EArDir nodir = Dir_None);
int IsPointInDirFrom(const CPoint& point, const CPoint& from, EArDir dir);
int IsPointInDirFrom(const CPoint& point, const CRect& rect, EArDir dir);
int IsPointBetweenSides(const CPoint& point, const CRect& rect, int ishorizontal = 1);
inline int IsPointBetweenSides(const CPoint& point, const CRect& rect, EArDir dir) { return IsPointBetweenSides(point, rect, IsHorizontal(dir)); }
int IsCoordInDirFrom(long coord, long from, EArDir dir);

EArDir OnWhichEdge(const CRect& rect, const CPoint& point);


// --------------------------- CArFindNearestLine


class CArFindNearestLine
{
public:
	CArFindNearestLine(const CPoint& p): point(p), dist1(INT_MAX), dist2(INT_MAX) { }

	int HLine(int x1, int x2, int y);
	int VLine(int y1, int y2, int x);
	int Was() { return dist1 < INT_MAX && dist2 < INT_MAX; }

public:
	CPoint point;
	int dist1;		// |(x,y)| = max(|x|,|y|)
	int dist2;		// |(x,y)| = |x| or |y|
};


#endif//__ARHELPER_H
