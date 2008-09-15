#ifndef GME_GraphicsUtil_h
#define GME_GraphicsUtil_h


class CArrowHead {
public:
	CArrowHead(int dir,int *xCoords,int *yCoords,int numln );
	~CArrowHead();
public:
	int segments;
	CPoint *path;

public:
	void Draw(CDC *pDC,CPoint &tip, bool bPen );
};

class CGraphics {
public:
	CGraphics();
	~CGraphics();
public:
	CPenTable pens;
	CPenTable dashPens;
	CPenTable dashMagnifiedPens;
	CPenTable dashPrintPens;
	CPenTable printPens;
	CBrushTable brushes;
	CFont *normalFonts[GME_FONT_KIND_NUM];
	CFont *semiboldFonts[GME_FONT_KIND_NUM];
	CFont *boldFonts[GME_FONT_KIND_NUM];
	CFontList allFonts;													// for destruction only
	CArrowHead *arrows[GME_DIRECTION_NUM];
	CArrowHead *diamonds[GME_DIRECTION_NUM];
	CArrowHead *apexes[GME_DIRECTION_NUM];
	CArrowHead *bullets[GME_DIRECTION_NUM];
	CArrowHead *leftHalfArrows[GME_DIRECTION_NUM];
	CArrowHead *rightHalfArrows[GME_DIRECTION_NUM];

public:
	CPen *GetPen(COLORREF color, bool isPrinting = false, bool dash = false, bool isViewMagnified = false, int width = 1);
	CBrush *GetBrush(COLORREF color);
	CFont *GetFont(GMEFontKind kind);
	CFont *GetFont(int kindsize, bool bold = false, bool semibold = false);
	void DeletePens(CPenTable &penTable);
	void DeleteBrushes(CBrushTable &brushTable);
	void CreateFonts(CFont **font,int boldness);
	void DrawMark(CDC *pDC,int x1,int x2,int y1,int y2);
	void DrawGrid(CDC *pDC,int xSpace,int ySpace,int maxx,int maxy,COLORREF color = GME_GRID_COLOR);
	void DrawArrow(CDC *pDC,CPoint &beforeLast,CPoint &last, int iEnd );
	void DrawConnection(CDC *pDC, const CPointList &points, COLORREF color, int lineType, int srcEnd, int dstEnd,
						bool mark, bool isViewMagnified, int lineStyle = 0);
	void DrawText(CDC *pDC,CString &txt,CPoint &pt,CFont *font,COLORREF color,int align);

};

extern CGraphics graphics;

#endif // whole file

