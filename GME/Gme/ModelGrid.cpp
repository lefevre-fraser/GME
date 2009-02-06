#include "stdafx.h"

#include "GMEApp.h"
#include "GMEStd.h"
#include "GuiObject.h"
#include "ModelGrid.h"

//////////////////////////////////// CModelGrid //////////////////////////////////

CModelGrid::CModelGrid()
{
#ifdef GRIDBITS
	width = GME_MAX_GRID_DIM / (8 * sizeof(int));
#else
	width = GME_MAX_GRID_DIM;
#endif
	height = GME_MAX_GRID_DIM;
	Clear();
	view = 0;
}

#ifdef GRIDBITS

#define trafo()		ASSERT(sizeof(int) == 4);						\
					unsigned int xi = (x >> 5);						\
					ASSERT(xi < (unsigned int)width);  				\
					ASSERT(y < height);  							\
					unsigned int mask = 1 << ((unsigned int)x & 0x1F);

inline bool CModelGrid::IsAvailable(int x,int y)
{
	trafo();
	return ((grid[y][xi] & mask) == 0);
}

inline void CModelGrid::Set(int x,int y)
{
	trafo();
	grid[y][xi] |= mask;
}

inline void CModelGrid::Reset(int x,int y)
{
	trafo();
	mask = ~mask;
	grid[y][xi] &= mask;
}

#else

inline bool CModelGrid::IsAvailable(int x,int y)
{
	return !grid[y][x];
}

inline void CModelGrid::Set(int x,int y)
{
	grid[y][x] = true;
}

inline void CModelGrid::Reset(int x,int y)
{
	grid[y][x] = false;
}

#endif

void CModelGrid::Clear()
{
	int i;
	memset(grid,0,sizeof(grid));
	for(i = 0; i < width; i++) {	// frame!
#ifdef GRIDBITS
		grid[0][i] = (unsigned int)~0;
		grid[height - 1][i] = (unsigned int)~0;
#else
		Set(i,0);
		Set(i,GME_MAX_GRID_DIM-1);
#endif
	}
	for(i = 0; i < height; i++) {
		Set(0,i);
		Set(GME_MAX_GRID_DIM-1,i);
	}
	view = 0;
}

bool CModelGrid::IsAvailableG(CPoint &pt,CSize &halfSize)  // centerpoint!
{
	int startx = pt.x - halfSize.cx;
	int starty = pt.y - halfSize.cy;
	int endx = pt.x + halfSize.cx;
	int endy = pt.y + halfSize.cy;
	if(startx < 0 || starty < 0 || endx >= GME_MAX_GRID_DIM || endy >= GME_MAX_GRID_DIM)
		return false;
	for(int i = starty; i < endy; i++)
		for(int j = startx; j < endx; j++)
			if(!IsAvailable(j,i))
				return false;
	return true;
}


#define FindStartEnd(pt,size,chk)											\
	pt.x = (pt.x / GME_GRID_SIZE) * GME_GRID_SIZE;							\
	pt.y = (pt.y / GME_GRID_SIZE) * GME_GRID_SIZE;							\
	int startx = (pt.x - size.cx / 2 - 1) / GME_GRID_SIZE;					\
	int starty = (pt.y - size.cy / 2 - 1) / GME_GRID_SIZE;					\
	int endx = (pt.x + size.cx / 2 + GME_GRID_SIZE) / GME_GRID_SIZE;		\
	int endy = (pt.y + size.cy / 2 + GME_GRID_SIZE) / GME_GRID_SIZE;		\
	if(chk) {																\
		ASSERT(startx >= 0);												\
		ASSERT(starty >= 0);												\
		ASSERT(endx < GME_MAX_GRID_DIM);									\
		ASSERT(endy < GME_MAX_GRID_DIM);									\
	}


bool CModelGrid::IsAvailable(CPoint pt,CSize size)  // centerpoint!
{
	FindStartEnd(pt,size,0);
	if(startx < 0 || starty < 0 || endx >= GME_MAX_GRID_DIM || endy >= GME_MAX_GRID_DIM)
		return false;
	for(int y = starty; y < endy; y++)
		for(int x = startx; x < endx; x++)
			if(!IsAvailable(x,y))
				return false;
	return true;
}


#define	test_and_return_if_found()					\
			if(IsAvailableG(test,size)) {			\
				pt.x = test.x * GME_GRID_SIZE;		\
				pt.y = test.y * GME_GRID_SIZE;		\
				return TRUE;						\
			}

bool CModelGrid::GetClosestAvailable(CSize size,CPoint &pt) // centerpoint!
{
	if(IsAvailable(pt,size)) {
		pt.x = (pt.x / GME_GRID_SIZE) * GME_GRID_SIZE;
		pt.y = (pt.y / GME_GRID_SIZE) * GME_GRID_SIZE;
		return TRUE;
	}
	pt.x /= GME_GRID_SIZE;
	pt.y /= GME_GRID_SIZE;
	pt.x = max(0,min(GME_MAX_GRID_DIM - 1,pt.x));
	pt.y = max(0,min(GME_MAX_GRID_DIM - 1,pt.y));
	size.cx = (size.cx / 2 + GME_GRID_SIZE) / GME_GRID_SIZE;
	size.cy = (size.cy / 2 + GME_GRID_SIZE) / GME_GRID_SIZE;
	CPoint test = pt;
	for(int rad = 1; rad < GME_MAX_GRID_DIM; rad++) {
		test.x = pt.x - rad;
		if(test.x >= 0)
			for(test.y = max(0,pt.y - rad); test.y < min(GME_MAX_GRID_DIM,pt.y + rad + 1); test.y++)
				test_and_return_if_found();
		test.x = pt.x + rad;
		if(test.x < GME_MAX_GRID_DIM)
			for(test.y = max(0,pt.y - rad); test.y < min(GME_MAX_GRID_DIM,pt.y + rad + 1); test.y++)
				test_and_return_if_found();
		test.y = pt.y - rad;
		if(test.y >= 0)
			for(test.x = max(0,pt.x - rad) + 1; test.x < min(GME_MAX_GRID_DIM,pt.x + rad + 1) - 1; test.x++)
				test_and_return_if_found();
		test.y = pt.y + rad;
		if(test.y < GME_MAX_GRID_DIM)
			for(test.x = max(0,pt.x - rad) + 1; test.x < min(GME_MAX_GRID_DIM,pt.x + rad + 1) - 1; test.x++)
				test_and_return_if_found();
	}
	return FALSE;
}


void CModelGrid::Set(CSize &size, CPoint &center, bool reset)
{
	FindStartEnd(center,size,1);
	for(int y = starty; y < endy; y++)
		for(int x = startx; x < endx; x++)
			reset ? Reset(x,y) : Set(x,y);
}



///////////////////////////////////////////////////
// Public methods - accepts objects as parameters

/*
Mod by ZolMol:  If called from CGMEView::SyncOnGrid then
				the object (*model) might not have the same aspects as its parent so
				calling GetLocation or GetNameLocation with default parameter might
				cause null ptr dereferencing
*/
void CModelGrid::Set(CGuiObject *model,bool reset, int aspIdx)
{
	CRect loc = model->GetLocation( aspIdx);
	CPoint pt = loc.CenterPoint();
	CSize s = loc.Size();
	Set(s,pt,reset);

	if (theApp.labelAvoidance) {
		loc = model->GetNameLocation( aspIdx);
		pt = loc.CenterPoint();
		s = loc.Size();
		Set(s,pt,reset);
	}
}

void CModelGrid::Reset(CGuiObject *model)
{
	Set(model,TRUE);
}

bool CModelGrid::IsAvailable(CGuiObject *model, int aspIdx) 
{
	CRect rect = model->GetLocation(aspIdx);
	bool avail = modelGrid.IsAvailable(rect.CenterPoint(), rect.Size());

	if (theApp.labelAvoidance) {
		rect = model->GetNameLocation(aspIdx);
		avail = avail && modelGrid.IsAvailable(rect.CenterPoint(), rect.Size());
	}

	return avail;
}

/*
Mod by ZolMol:  If called from CGMEView::SyncOnGrid then
				the object (*model) might not have the same aspects as its parent so
				calling GetLocation or GetNameLocation with default parameter might
				cause null ptr dereferencing
*/
bool CModelGrid::GetClosestAvailable(CGuiObject *model,CPoint &pt, int aspIdx)
{
	CRect unionLoc;
	CRect loc = model->GetLocation( aspIdx);
	if (theApp.labelAvoidance) {
		CRect nameLoc = model->GetNameLocation( aspIdx);
		unionLoc.UnionRect(&loc, &nameLoc);
	}
	else {
		unionLoc = loc;
	}
	
	CSize offset = unionLoc.CenterPoint() - loc.CenterPoint();

	offset.cx -= offset.cx % GME_GRID_SIZE;
	offset.cy -= offset.cy % GME_GRID_SIZE;

	pt += offset;

	bool ret = GetClosestAvailable(unionLoc.Size(), pt);

	pt -= offset;

	return ret;
}

bool CModelGrid::CanNudge(CGuiObject *model,int right,int down)
{
	ASSERT(right == 0 || down == 0); // no diagonal nudge!
	CRect r = model->GetLocation(); // comment by ZolMol: this is correct since the parent aspect is always valid, and an object is moved (nudged) within the parents aspect only
	right *= GME_GRID_SIZE;
	down *= GME_GRID_SIZE;
	r.right += right;
	r.left += right;
	r.top += down;
	r.bottom += down;
	bool can = IsAvailable(r.CenterPoint(),r.Size());

	if (theApp.labelAvoidance) {
		r = model->GetNameLocation();
		r.right += right;
		r.left += right;
		r.top += down;
		r.bottom += down;
		can = can && IsAvailable(r.CenterPoint(),r.Size());
	}

	return can;
}
