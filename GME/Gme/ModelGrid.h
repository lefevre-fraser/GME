#ifndef _MODELGRID_INCLUDED_
#define _MODELGRID_INCLUDED_

class CModelGrid {
public:
	CModelGrid();
private:
	CGMEView *view;
#ifdef GRIDBITS
	unsigned int grid[GME_MAX_GRID_DIM][GME_MAX_GRID_DIM / (8 * sizeof(int))];
#else
	bool grid[GME_MAX_GRID_DIM][GME_MAX_GRID_DIM];
#endif
	int width;
	int height;
public:
	CGMEView *GetSource()				{ return view; }
	void SetSource(CGMEView *vw)		{ view = vw; }

	void Clear();
	
	void Set(CGuiObject *model,bool reset = FALSE, int aspIdx = -1);//last param introd by zolmol
	void Reset(CGuiObject *model);

	bool IsAvailable(CGuiObject *model, int aspIdx = -1);
	bool GetClosestAvailable(CGuiObject *model,CPoint &pt, int aspIdx = -1);//last param introd by zolmol
	
	bool CanNudge(CGuiObject *model,int right,int down);	

private:
	
	void Set(int x,int y);
	void Reset(int x,int y);
	bool IsAvailable(int x,int y);

	void Set(CSize &size, CPoint &center, bool reset = FALSE);

	bool IsAvailable(CPoint pt,CSize size);
	bool IsAvailableG(CPoint &pt,CSize &size);

	bool GetClosestAvailable(CSize size,CPoint &pt);
};

#endif // whole file