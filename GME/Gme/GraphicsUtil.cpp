#include "stdafx.h"

#include "GMEstd.h"
#include "GraphicsUtil.h"

static bool fontBoldness[GME_FONT_KIND_NUM]		= { false, false, false };
static bool fontSemiboldness[GME_FONT_KIND_NUM]	= { true, true, false };
static int  fontSizes[GME_FONT_KIND_NUM]		= { 18, 15, 12 };


static int arrowXCoords[] = {-5, -7, -1, -7};
static int arrowYCoords[] = {0, -3, 0, 3};
static int leftHalfXCoords[] = {-1, -10};
static int leftHalfYCoords[] = {0, -5};
static int rightHalfXCoords[] = {-1, -10 };
static int rightHalfYCoords[] = {0, 5};
static int diamondXCoords[] = {-11, -6, -1, -6};
static int diamondYCoords[] = {0, -3, 0, 3};
static int apexXCoords[] = { -9, -9, -1 };
static int apexYCoords[] = { -5, 5, 0 };
static int bulletXCoords[] = { -1, -2, -3, -5, -6, -7, -7, -6, -5, -3, -2, -1 };
static int bulletYCoords[] = { -1, -2, -3, -3, -2, -1, 1, 2, 3, 3, 2, 1 };

//////////////////////////////////// CArrowHead //////////////////////////////

CArrowHead::CArrowHead(int dir, int* xCoords, int* yCoords, int numln)
{
	segments = numln;
	path = new CPoint[segments];
	for(int i = 0; i < segments; i++) {
		switch(dir) {
		case GME_RIGHT_DIRECTION:
			path[i].x = xCoords[i], path[i].y = yCoords[i];
			break;
		case GME_LEFT_DIRECTION:
			path[i].x = -xCoords[i], path[i].y = -yCoords[i];
			break;
		case GME_UP_DIRECTION:
			path[i].x = yCoords[i], path[i].y = -xCoords[i];
			break;
		case GME_DOWN_DIRECTION:
			path[i].x = -yCoords[i], path[i].y = +xCoords[i];
			break;
		default:
			ASSERT(FALSE);
			break;
		}
	}
}

CArrowHead::~CArrowHead()
{
	delete [] path;
}

void CArrowHead::Draw(CDC *pDC, CPoint &tip, bool bPen)
{
	pDC->MoveTo(path[0] + tip);
	pDC->BeginPath();
	for (int i = 1; i<segments; i++) {
		pDC->LineTo(path[i] + tip);
	}
	pDC->EndPath();
	pDC->FillPath();

	if ( bPen ) {
		pDC->MoveTo(path[0] + tip);
		for (int i = 1; i<segments; i++) {
			pDC->LineTo(path[i] + tip);
		}
		pDC->LineTo(path[0] + tip);
	}
}

void CArrowHead::Draw(Gdiplus::Graphics* gdip, Gdiplus::Pen* pen, Gdiplus::Brush* brush, CPoint& tip, bool bPen)
{
	Gdiplus::GraphicsPath* arrowHeadPath = new Gdiplus::GraphicsPath();
	for (int i = 1; i < segments; i++)
		arrowHeadPath->AddLine(path[i - 1].x + tip.x, path[i - 1].y + tip.y, path[i].x + tip.x, path[i].y + tip.y);
	gdip->FillPath(brush, arrowHeadPath);

	if (bPen) {
		arrowHeadPath->AddLine(path[segments - 1].x + tip.x, path[segments - 1].y + tip.y, path[0].x + tip.x, path[0].y + tip.y);
		gdip->DrawPath(pen, arrowHeadPath);
	}
}


CGraphics::CGraphics()
{
}

CGraphics::~CGraphics()
{
}

void CGraphics::Initialize(void)
{
	GetPen(GME_BACKGROUND_COLOR	);
	GetPen(GME_BORDER_COLOR		);
	GetPen(GME_MODEL_COLOR		);
	GetPen(GME_NAME_COLOR		);
	GetPen(GME_PORTNAME_COLOR	);
	GetPen(GME_CONNECTION_COLOR	);
	GetPen(GME_GRAYED_OUT_COLOR	);
	GetPen(GME_GRID_COLOR		);
	GetPen(GME_BLACK_COLOR		);
	GetPen(GME_WHITE_COLOR		);
	GetPen(GME_GREY_COLOR		);
	GetPen(GME_BACKGROUND_COLOR	, false, true);
	GetPen(GME_BORDER_COLOR		, false, true);
	GetPen(GME_MODEL_COLOR		, false, true);
	GetPen(GME_NAME_COLOR		, false, true);
	GetPen(GME_PORTNAME_COLOR	, false, true);
	GetPen(GME_CONNECTION_COLOR	, false, true);
	GetPen(GME_GRAYED_OUT_COLOR	, false, true);
	GetPen(GME_GRID_COLOR		, false, true);
	GetPen(GME_BLACK_COLOR		, false, true);
	GetPen(GME_WHITE_COLOR		, false, true);
	GetPen(GME_GREY_COLOR		, false, true);

	GetPen(GME_BACKGROUND_COLOR	, true, true);
	GetPen(GME_BORDER_COLOR		, true, true);
	GetPen(GME_MODEL_COLOR		, true, true);
	GetPen(GME_NAME_COLOR		, true, true);
	GetPen(GME_PORTNAME_COLOR	, true, true);
	GetPen(GME_CONNECTION_COLOR	, true, true);
	GetPen(GME_GRAYED_OUT_COLOR	, true, true);
	GetPen(GME_GRID_COLOR		, true, true);
	GetPen(GME_BLACK_COLOR		, true, true);
	GetPen(GME_WHITE_COLOR		, true, true);
	GetPen(GME_GREY_COLOR		, true, true);

	GetPen(GME_BACKGROUND_COLOR	, true, false);
	GetPen(GME_BORDER_COLOR		, true, false);
	GetPen(GME_MODEL_COLOR		, true, false);
	GetPen(GME_NAME_COLOR		, true, false);
	GetPen(GME_PORTNAME_COLOR	, true, false);
	GetPen(GME_CONNECTION_COLOR	, true, false);
	GetPen(GME_GRAYED_OUT_COLOR	, true, false);
	GetPen(GME_GRID_COLOR		, true, false);
	GetPen(GME_BLACK_COLOR		, true, false);
	GetPen(GME_WHITE_COLOR		, true, false);
	GetPen(GME_GREY_COLOR		, true, false);

	CreateFonts(normalFonts, normalGdipFonts, FW_LIGHT);
	CreateFonts(semiboldFonts, semiboldGdipFonts, FW_NORMAL);
	CreateFonts(boldFonts, boldGdipFonts, FW_SEMIBOLD);

	for(int i = 0; i < GME_DIRECTION_NUM; i++) {
		arrows[i] = new CArrowHead( i, arrowXCoords, arrowYCoords, 4 );
		diamonds[i] = new CArrowHead( i, diamondXCoords, diamondYCoords, 4 );
		apexes[i] = new CArrowHead( i, apexXCoords, apexYCoords, 3 );
		bullets[i] = new CArrowHead( i, bulletXCoords, bulletYCoords, 12 );
		leftHalfArrows[i]  = new CArrowHead( i, leftHalfXCoords, leftHalfYCoords, 2);
		rightHalfArrows[i] = new CArrowHead( i, rightHalfXCoords, rightHalfYCoords, 2);
	}
}

void CGraphics::Uninitialize(void)
{
	DeletePens(pens, gdipPens);
	DeletePens(dashPens, gdipDashPens);
	DeletePens(dashMagnifiedPens, gdipDashMagnifiedPens);
	DeletePens(printPens, gdipPrintPens);
	DeletePens(dashPrintPens, gdipDashPrintPens);
	DeleteBrushes(brushes, gdipBrushes);

	POSITION pos = allFonts.GetHeadPosition();
	while(pos)
		delete allFonts.GetNext(pos);
	pos = allGdipFonts.GetHeadPosition();
	while(pos)
		delete allGdipFonts.GetNext(pos);

	for(int i = 0; i < GME_DIRECTION_NUM; i++) {
		delete arrows[i];
		delete diamonds[i];
		delete apexes[i];
		delete bullets[i];
		delete leftHalfArrows[i];
		delete rightHalfArrows[i];
	}
}

void CGraphics::DeletePens(CPenTable &penTable, GdipPenTable& gdipPenTable)
{
	POSITION pos = penTable.GetStartPosition();
	CPen *pen;
	void *pt;
	while(pos) {
		penTable.GetNextAssoc(pos,pt,pen);
		delete pen;
	}

	pos = gdipPenTable.GetStartPosition();
	Gdiplus::Pen* gdipPen;
	while(pos) {
		gdipPenTable.GetNextAssoc(pos, pt, gdipPen);
		delete gdipPen;
	}
}

void CGraphics::DeleteBrushes(CBrushTable& brushTable, GdipBrushTable& gdipBrushTable)
{
	POSITION pos = brushTable.GetStartPosition();
	CBrush* brush;
	void* pt;
	while(pos) {
		brushTable.GetNextAssoc(pos, pt, brush);
		delete brush;
	}

	pos = gdipBrushTable.GetStartPosition();
	Gdiplus::SolidBrush* gdipBrush;
	while(pos) {
		gdipBrushTable.GetNextAssoc(pos, pt, gdipBrush);
		delete gdipBrush;
	}
}


void CGraphics::CreateFonts(CFont** font, Gdiplus::Font** gdipFont, int boldness)
{
	for (int i = 0; i < GME_FONT_KIND_NUM; i++) {
		font[i] = new CFont();
		font[i]->CreateFont(fontSizes[i],0,0,0,boldness,0,0,0,ANSI_CHARSET,
							OUT_DEVICE_PRECIS,CLIP_DEFAULT_PRECIS,
							PROOF_QUALITY,FF_SWISS,"Arial");
		allFonts.AddHead(font[i]);

		CDC dc;
		dc.CreateCompatibleDC(NULL);
		LOGFONT logFont;
		font[i]->GetLogFont(&logFont);
		gdipFont[i] = new Gdiplus::Font( dc.m_hDC, &logFont );
		allGdipFonts.AddHead(gdipFont[i]);
	}
}


CFont* CGraphics::GetFont(GMEFontKind kind)
{
	return GetFont(kind, fontBoldness[kind], fontSemiboldness[kind]);
}

CFont* CGraphics::GetFont(int kindsize, bool bold, bool semibold)
{
	return bold ? boldFonts[kindsize] : (semibold ? semiboldFonts[kindsize] : normalFonts[kindsize]);
}

Gdiplus::Font* CGraphics::GetGdipFont(GMEFontKind kind)
{
	return GetGdipFont(kind, fontBoldness[kind], fontSemiboldness[kind]);
}

Gdiplus::Font* CGraphics::GetGdipFont(int kindsize, bool bold, bool semibold)
{
	return bold ? boldGdipFonts[kindsize] : (semibold ? semiboldGdipFonts[kindsize] : normalGdipFonts[kindsize]);
}

CPen* CGraphics::GetPen(COLORREF color, bool isPrinting, bool dash, bool isViewMagnified, int width /* = 1 */)
{
	LOGBRUSH logb = {BS_SOLID, 0, 0};
	DWORD dashstyle[2] = {4, 2};
	DWORD solidstyle[2] = {4, 0};
	// print real dashed line
	CPen *pen = 0;
	if( width != 1 || !((dash ? (isPrinting? dashPrintPens: isViewMagnified ? dashMagnifiedPens : dashPens) : (isPrinting? printPens: pens)).Lookup((void *)color,pen))) {
		pen = new CPen();
//		pen->CreatePen((dash ? PS_DOT : PS_SOLID),1,color);
//		pen->CreatePen((dash ? (isPrinting? PS_DASH: PS_DOT) : PS_SOLID),1,color);
		logb.lbColor = color; 
//		pen->CreatePen((dash ? (isPrinting? PS_USERSTYLE|PS_GEOMETRIC: PS_DOT|PS_GEOMETRIC) : 
//			PS_SOLID|PS_GEOMETRIC), (isPrinting? 5: 1),
//			&logb, (dash && isPrinting)? 2: 0, (dash && isPrinting)? dashstyle: NULL);
		pen->CreatePen((dash ? (isPrinting? PS_USERSTYLE|PS_GEOMETRIC: isViewMagnified ? PS_DASH|PS_GEOMETRIC : PS_DOT) : 
			(isPrinting? PS_USERSTYLE|PS_GEOMETRIC: PS_SOLID|PS_GEOMETRIC)), (isPrinting? 1: width),
				&logb, (isPrinting)? 2: 0, (isPrinting)? (dash? dashstyle: solidstyle): NULL);
		if( width == 1) // only if regular
		(dash ? (isPrinting? dashPrintPens: isViewMagnified ? dashMagnifiedPens : dashPens) : (isPrinting? printPens: pens)).SetAt((void *)color,pen);
	}
	ASSERT(pen);
	return pen;
}

Gdiplus::Pen* CGraphics::GetGdipPen2(Gdiplus::Graphics* gdip, COLORREF color, bool dash, bool isViewMagnified,
									 int width /* = 1 */)
{
	// TODO
//	HDC hDC = gdip->GetHDC();
//	bool isPrinting = GetDeviceCaps(hDC, TECHNOLOGY) == DT_RASPRINTER;
//	gdip->ReleaseHDC(hDC);
	return GetGdipPen(gdip, color, /*isPrinting*/ false, dash, isViewMagnified, width);
}

Gdiplus::Pen* CGraphics::GetGdipPen(Gdiplus::Graphics* gdip, COLORREF color, bool isPrinting, bool dash,
									bool isViewMagnified, int width /* = 1 */)
{
	Gdiplus::Pen* pen = NULL;
	if (width != 1 || !((dash ? (isPrinting ? gdipDashPrintPens: isViewMagnified ? gdipDashMagnifiedPens : gdipDashPens) : (isPrinting? gdipPrintPens: gdipPens)).Lookup((void *)color,pen)))
	{
		Gdiplus::Color gdipColor(GetRValue(color), GetGValue(color), GetBValue(color));
		float fWidth = static_cast<float> (isPrinting ? 1 : width);
		pen = new Gdiplus::Pen(gdipColor, fWidth);
		if (dash) {
			pen->SetDashStyle(Gdiplus::DashStyleDash);
			pen->SetDashCap(Gdiplus::DashCapFlat);
//		} else {
//			pen->SetDashStyle(Gdiplus::DashStyleSolid);
		}

		if (width == 1) // only if regular
			(dash ? (isPrinting ? gdipDashPrintPens: isViewMagnified ? gdipDashMagnifiedPens : gdipDashPens) : (isPrinting? gdipPrintPens: gdipPens)).SetAt((void *)color,pen);
	}
	ASSERT(pen);
	return pen;
}

CBrush* CGraphics::GetBrush(COLORREF color)
{
	CBrush* brush = 0;
	if(!(brushes.Lookup((void*)color,brush))) {
		brush = new CBrush();
		brush->CreateSolidBrush(color);
		brushes.SetAt((void*)color,brush);
	}
	ASSERT(brush);
	return brush;
}

Gdiplus::SolidBrush* CGraphics::GetGdipBrush(COLORREF color)
{
	Gdiplus::SolidBrush* brush = NULL;
	if(!(gdipBrushes.Lookup((void*)color, brush))) {
		brush = new Gdiplus::SolidBrush(Gdiplus::Color(GetRValue(color), GetGValue(color), GetBValue(color)));
		gdipBrushes.SetAt((void*)color, brush);
	}
	ASSERT(brush);
	return brush;
}

void CGraphics::DrawMark(CDC *pDC,int x1,int x2,int y1,int y2)
{
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
}

void CGraphics::DrawGrid(CDC *pDC,int xSpace,int ySpace,int maxx,int maxy,COLORREF color)
{
	CPen *pen = GetPen(color, pDC->IsPrinting()!=FALSE);
	CPen *oldpen = pDC->SelectObject(pen);
	for(int x = 0 ; x < maxx; x += xSpace)
		DrawMark(pDC,x,x,0,maxy);
	for(int y = 0; y < maxy; y += ySpace)
		DrawMark(pDC,0,maxx,y,y);
	pDC->SelectObject(oldpen);
}

void CGraphics::DrawGrid(Gdiplus::Graphics* gdip, int xSpace, int ySpace, int maxx, int maxy, COLORREF color)
{
	Gdiplus::Pen* pen = GetGdipPen2(gdip, color);
	for(int x = 0 ; x < maxx; x += xSpace)
		gdip->DrawLine(pen, x, 0, x, maxy);
	for(int y = 0; y < maxy; y += ySpace)
		gdip->DrawLine(pen, 0, y, maxx, y);
}

void CGraphics::DrawConnection(CDC *pDC, const CPointList &points, COLORREF color, int lineType,
							   int srcEnd, int dstEnd, bool mark, bool isViewMagnified, int lineStyle /* = 0 */)
{
	if( points.GetCount()==0 )
		return;

	ASSERT(points.GetCount() >= 2);

	if(pDC->IsPrinting()) {
		color = GME_BLACK_COLOR;
	}

	// the color has to be altered a little bit, because the predefined PenMap has color at its key 
	// so it will confuse this bold Pen with already existing pens
	//CPen *pen = GetPen(color, pDC->IsPrinting()!=FALSE, lineType > 0);
	CPen *pen = GetPen(/*lineStyle > 0? (color+0x0f0f0f):*/ color, pDC->IsPrinting() != FALSE, lineType > 0,
					   isViewMagnified, lineStyle > 0 ? 5: 1);
	CPen *oldpen = pDC->SelectObject(pen);
	CBrush *brush = GetBrush(color);
	CBrush *oldbrush = pDC->SelectObject(brush);

	CPoint beforeLast;
	CPoint last;
	POSITION pos = points.GetHeadPosition();
	if(pos)	{
		CPoint pt = points.GetNext(pos);
		last = pt;
		pDC->MoveTo(pt);
		while(pos) {
			pt = points.GetNext(pos);
			beforeLast = last;
			last = pt;
			pDC->LineTo(pt);
		}
	}
	CPen *headpen = GetPen(color, pDC->IsPrinting()!=FALSE);
	pDC->SelectObject (headpen);

	POSITION pos2 = points.GetHeadPosition();
	CPoint first = points.GetNext(pos2);
	CPoint second = points.GetNext(pos2);

	pDC->SelectObject( GetBrush( ( srcEnd == GME_EMPTYDIAMOND_END || srcEnd == GME_EMPTYAPEX_END || srcEnd == GME_EMPTYBULLET_END ) ? GME_WHITE_COLOR : color ) );

	DrawArrow(pDC, second, first, srcEnd);

	pDC->SelectObject( GetBrush( ( dstEnd == GME_EMPTYDIAMOND_END || dstEnd == GME_EMPTYAPEX_END || dstEnd == GME_EMPTYBULLET_END ) ? GME_WHITE_COLOR : color ) );

	DrawArrow(pDC, beforeLast, last, dstEnd);

	pDC->SelectObject(oldbrush);
	pDC->SelectObject(oldpen);
	
	if( lineStyle > 0) pen->DeleteObject(); // delete special pen
}

void CGraphics::DrawArrow(CDC* pDC, CPoint& beforeLast, CPoint& last, int iEnd)
{
	int dir = 0;
	if(beforeLast.x == last.x)
		dir = beforeLast.y > last.y ? dir = GME_UP_DIRECTION : GME_DOWN_DIRECTION;
	else
		dir = beforeLast.x > last.x ? dir = GME_LEFT_DIRECTION : GME_RIGHT_DIRECTION;
	switch( iEnd ) {
		case GME_ARROW_END :
			arrows[ dir ]->Draw( pDC, last, false );
			break;
		case GME_DIAMOND_END :
		case GME_EMPTYDIAMOND_END :
			diamonds[ dir ]->Draw( pDC, last, iEnd == GME_EMPTYDIAMOND_END );
			break;
		case GME_APEX_END :
		case GME_EMPTYAPEX_END :
			apexes[ dir ]->Draw( pDC, last, iEnd == GME_EMPTYAPEX_END );
			break;
		case GME_BULLET_END :
		case GME_EMPTYBULLET_END :
			bullets[ dir ]->Draw( pDC, last, iEnd == GME_EMPTYBULLET_END );
			break;
		case GME_HALFARROWLEFT_END :
			leftHalfArrows[ dir ]->Draw( pDC, last, true );
			break;
		case GME_HALFARROWRIGHT_END :
			rightHalfArrows[ dir ]->Draw( pDC, last, true );
			break;
	}
}

void CGraphics::DrawText(CDC *pDC,CString &txt,CPoint &pt,CFont *font,COLORREF color,int align)
{
	if(font == 0)
		return;
	pDC->SelectObject(font);
	pDC->SetTextAlign(align);
	SetBkMode(pDC->m_hDC,TRANSPARENT);
	pDC->SetTextColor(pDC->IsPrinting() ? GME_BLACK_COLOR : color);
	pDC->TextOut(pt.x,pt.y,(LPCTSTR)txt,txt.GetLength());
}

void CGraphics::DrawConnection(Gdiplus::Graphics* gdip, const CPointList &points, COLORREF color, int lineType,
							   int srcEnd, int dstEnd, bool mark, bool isViewMagnified, int lineStyle /* = 0 */)
{
	if (points.GetCount() == 0)
		return;

	ASSERT(points.GetCount() >= 2);

	HDC hDC = gdip->GetHDC();
	bool isPrinting = GetDeviceCaps(hDC, TECHNOLOGY) == DT_RASPRINTER;
	gdip->ReleaseHDC(hDC);
	if (isPrinting)
		color = GME_BLACK_COLOR;

	// the color has to be altered a little bit, because the predefined PenMap has color at its key 
	// so it will confuse this bold Pen with already existing pens
	Gdiplus::Pen* pen = GetGdipPen(gdip, color, isPrinting, lineType > 0, isViewMagnified, lineStyle > 0 ? 5 : 1);
	Gdiplus::Brush* brush = GetGdipBrush(color);

	CPoint beforeLast;
	CPoint last;
	POSITION pos = points.GetHeadPosition();
	if (pos) {
		CPoint pt = points.GetNext(pos);
		last = pt;
		while (pos) {
			pt = points.GetNext(pos);
			gdip->DrawLine(pen, last.x, last.y, pt.x, pt.y);
			beforeLast = last;
			last = pt;
		}
	}
	Gdiplus::Pen* headpen = GetGdipPen(gdip, color, isPrinting);

	POSITION pos2 = points.GetHeadPosition();
	CPoint first = points.GetNext(pos2);
	CPoint second = points.GetNext(pos2);

	Gdiplus::Brush* headBrush = NULL;
	headBrush = GetGdipBrush((srcEnd == GME_EMPTYDIAMOND_END ||
							  srcEnd == GME_EMPTYAPEX_END ||
							  srcEnd == GME_EMPTYBULLET_END) ? GME_WHITE_COLOR : color);

	DrawArrow(gdip, headpen, headBrush, second, first, srcEnd);

	headBrush = GetGdipBrush((dstEnd == GME_EMPTYDIAMOND_END ||
							  dstEnd == GME_EMPTYAPEX_END ||
							  dstEnd == GME_EMPTYBULLET_END) ? GME_WHITE_COLOR : color);

	DrawArrow(gdip, headpen, headBrush, beforeLast, last, dstEnd);
	
	if (lineStyle > 0)
		delete pen; // delete special pen
}

void CGraphics::DrawArrow(Gdiplus::Graphics* gdip, Gdiplus::Pen* pen, Gdiplus::Brush* brush,
						  CPoint& beforeLast, CPoint& last, int iEnd)
{
	int dir = 0;
	if(beforeLast.x == last.x)
		dir = beforeLast.y > last.y ? dir = GME_UP_DIRECTION : GME_DOWN_DIRECTION;
	else
		dir = beforeLast.x > last.x ? dir = GME_LEFT_DIRECTION : GME_RIGHT_DIRECTION;
	switch( iEnd ) {
		case GME_ARROW_END :
			arrows[dir]->Draw(gdip, pen, brush, last, false);
			break;
		case GME_DIAMOND_END :
		case GME_EMPTYDIAMOND_END :
			diamonds[dir]->Draw(gdip, pen, brush, last, iEnd == GME_EMPTYDIAMOND_END);
			break;
		case GME_APEX_END :
		case GME_EMPTYAPEX_END :
			apexes[dir]->Draw(gdip, pen, brush, last, iEnd == GME_EMPTYAPEX_END);
			break;
		case GME_BULLET_END :
		case GME_EMPTYBULLET_END :
			bullets[dir]->Draw(gdip, pen, brush, last, iEnd == GME_EMPTYBULLET_END);
			break;
		case GME_HALFARROWLEFT_END :
			leftHalfArrows[dir]->Draw(gdip, pen, brush, last, true);
			break;
		case GME_HALFARROWRIGHT_END :
			rightHalfArrows[dir]->Draw(gdip, pen, brush, last, true);
			break;
	}
}

void CGraphics::DrawGdipText(Gdiplus::Graphics* gdip, CString& txt, CPoint& pt, Gdiplus::Font* font, COLORREF color, int align)
{
	if (font == NULL)
		return;

	Gdiplus::StringFormat format;
	Gdiplus::StringAlignment horizontalAlignment;
	if ((align & TA_CENTER) == TA_CENTER) {
		horizontalAlignment = Gdiplus::StringAlignmentCenter;
	} else if ((align & TA_RIGHT) == TA_RIGHT) {
		horizontalAlignment = Gdiplus::StringAlignmentFar;
	} else {	// TA_LEFT
		horizontalAlignment = Gdiplus::StringAlignmentNear;
	}
	format.SetAlignment(horizontalAlignment);
	Gdiplus::StringAlignment verticalAlignment;
	if ((align & TA_BASELINE) == TA_BASELINE) {
		verticalAlignment = Gdiplus::StringAlignmentCenter;
	} else if ((align & TA_BOTTOM) == TA_BOTTOM) {
		verticalAlignment = Gdiplus::StringAlignmentFar;
	} else {	// TA_TOP
		verticalAlignment = Gdiplus::StringAlignmentNear;
	}
	format.SetLineAlignment(verticalAlignment);

	// TODO
//	HDC hDC = gdip->GetHDC();
//	COLORREF textColor = GetDeviceCaps(hDC, TECHNOLOGY) == DT_RASPRINTER ? GME_BLACK_COLOR : color;
//	gdip->ReleaseHDC(hDC);
	COLORREF textColor = color;

	Gdiplus::SolidBrush textBrush(Gdiplus::Color(GetRValue(textColor),
												 GetGValue(textColor),
												 GetBValue(textColor)));

	Gdiplus::PointF pointF(static_cast<float> (pt.x),
						   static_cast<float> (pt.y));

	USES_CONVERSION;
	WCHAR* wcTxt = (WCHAR*)A2W(txt);

	Gdiplus::RectF rectF;
	gdip->MeasureString(wcTxt, txt.GetLength(), font, pointF, &rectF);
	gdip->DrawString((WCHAR*)A2W(txt), txt.GetLength(), font, rectF, &format, &textBrush);
}

Gdiplus::RectF CGraphics::MeasureText2(Gdiplus::Graphics* gdip, CString& txt, CPoint& pt, Gdiplus::Font* font)
{
	Gdiplus::PointF pointF(static_cast<float> (pt.x),
						   static_cast<float> (pt.y));

	USES_CONVERSION;
	WCHAR* wcTxt = (WCHAR*)A2W(txt);

	Gdiplus::RectF rectF;
	gdip->MeasureString(wcTxt, txt.GetLength(), font, pointF, &rectF);
	return rectF;
}

CSize CGraphics::MeasureText(Gdiplus::Graphics* gdip, CString& txt, CPoint& pt, Gdiplus::Font* font)
{
	Gdiplus::RectF rectF = MeasureText2(gdip, txt, pt, font);
	Gdiplus::SizeF sizeF;
	rectF.GetSize(&sizeF);
	CSize size(static_cast<long> (sizeF.Width), static_cast<long> (sizeF.Height));
	return size;
}
