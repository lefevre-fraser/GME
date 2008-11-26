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
	delete arrowHeadPath;
}


CGraphics::CGraphics()
{
}

CGraphics::~CGraphics()
{
}

void CGraphics::Initialize(void)
{
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
	for (std::map<CString,Gdiplus::Pen*>::iterator it = m_mapGdipPens.begin() ; it != m_mapGdipPens.end() ; ++it)
		delete it->second;
	DeleteBrushes(gdipBrushes);

	POSITION pos = allFonts.GetHeadPosition();
	while(pos)
		delete allFonts.GetNext(pos);
	pos = allGdipFonts.GetHeadPosition();
	while(pos)
		delete allGdipFonts.GetNext(pos);

	for (int i = 0; i < GME_DIRECTION_NUM; i++) {
		delete arrows[i];
		delete diamonds[i];
		delete apexes[i];
		delete bullets[i];
		delete leftHalfArrows[i];
		delete rightHalfArrows[i];
	}
}

void CGraphics::DeleteBrushes(GdipBrushTable& gdipBrushTable)
{
	POSITION pos = gdipBrushTable.GetStartPosition();
	void* pt;
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

Gdiplus::Font* CGraphics::GetGdipFont(GMEFontKind kind)
{
	return GetGdipFont(kind, fontBoldness[kind], fontSemiboldness[kind]);
}

Gdiplus::Font* CGraphics::GetGdipFont(int kindsize, bool bold, bool semibold)
{
	return bold ? boldGdipFonts[kindsize] : (semibold ? semiboldGdipFonts[kindsize] : normalGdipFonts[kindsize]);
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
	CString chBuffer;
	chBuffer.Format("%x-%d-%d-%d-%ld", color, isPrinting, dash, isViewMagnified, width);
	std::map<CString,Gdiplus::Pen*>::iterator it = m_mapGdipPens.find(chBuffer);
	if (it != m_mapGdipPens.end())
		return it->second;

	Gdiplus::Color gdipColor(GetRValue(color), GetGValue(color), GetBValue(color));
	float fWidth = static_cast<float> (isPrinting ? 1 : width);
	Gdiplus::Pen* pen = new Gdiplus::Pen(gdipColor, fWidth);
	if (dash) {
		Gdiplus::REAL dashPatternVals[2] = {
			5.0f,	// dash length 5
			2.0f	// space length 2
		};
		pen->SetDashPattern(dashPatternVals, 2);
		pen->SetDashStyle(Gdiplus::DashStyleCustom);
		pen->SetDashCap(Gdiplus::DashCapRound);
//	} else {
//		pen->SetDashStyle(Gdiplus::DashStyleSolid);
	}

	m_mapGdipPens.insert(std::map<CString,Gdiplus::Pen*>::value_type(chBuffer, pen));
	return pen;
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

void CGraphics::DrawGrid(Gdiplus::Graphics* gdip, int xSpace, int ySpace, int maxx, int maxy, COLORREF color)
{
	Gdiplus::Pen* pen = GetGdipPen2(gdip, color);
	for(int x = 0 ; x < maxx; x += xSpace)
		gdip->DrawLine(pen, x, 0, x, maxy);
	for(int y = 0; y < maxy; y += ySpace)
		gdip->DrawLine(pen, 0, y, maxx, y);
}

void CGraphics::DrawConnection(Gdiplus::Graphics* gdip, const CPointList &points, COLORREF color, int lineType,
							   int srcEnd, int dstEnd, bool mark, bool isViewMagnified, int lineStyle)
{
	if (points.GetCount() == 0)
		return;

	ASSERT(points.GetCount() >= 2);

//	HDC hDC = gdip->GetHDC();
	bool isPrinting = false;	//GetDeviceCaps(hDC, TECHNOLOGY) == DT_RASPRINTER;
//	gdip->ReleaseHDC(hDC);
//	if (isPrinting)
//		color = GME_BLACK_COLOR;

	// the color has to be altered a little bit, because the predefined PenMap has color at its key 
	// so it will confuse this bold Pen with already existing pens
	Gdiplus::Pen* pen = GetGdipPen(gdip, color, isPrinting, lineType > 0, isViewMagnified, lineStyle);
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

	CA2W wcTxt(txt);
	Gdiplus::RectF rectF;
	gdip->MeasureString(wcTxt, txt.GetLength(), font, pointF, &rectF);
	gdip->DrawString(wcTxt, txt.GetLength(), font, rectF, &format, &textBrush);
}

Gdiplus::RectF CGraphics::MeasureText2(Gdiplus::Graphics* gdip, CString& txt, CPoint& pt, Gdiplus::Font* font)
{
	Gdiplus::PointF pointF(static_cast<float> (pt.x),
						   static_cast<float> (pt.y));

	CA2W wcTxt(txt);
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
