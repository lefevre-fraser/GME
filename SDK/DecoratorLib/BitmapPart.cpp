//################################################################################################
//
// Bitmap decorator class
//	BitmapPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "BitmapPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : BitmapPart
//
//################################################################################################

BitmapPart::BitmapPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink):
	VectorPart			(pPart, eventSink),
	m_pBitmap			(NULL),
	m_pTileVector		(NULL),
	m_crBorder			(COLOR_BLACK),
	m_bRoundCornerRect	(false),
	m_bRoundCornerRadius(9)
{
}

BitmapPart::~BitmapPart()
{
}

feature_code BitmapPart::GetFeatures(void) const
{
	// TODO: it depends, if it is resizable
	return F_RESIZABLE | F_MOUSEEVENTS;
}

CSize BitmapPart::GetPreferredSize(void) const
{
	CSize size = VectorPart::GetPreferredSize();
	if (size.cx * size.cy != 0)
		return size;

	return CSize(m_pBitmap->getWidth() + GetBorderWidth(false) * 2, m_pBitmap->getHeight() + GetBorderWidth(false) * 2);
}

void BitmapPart::Draw(CDC* pDC, Gdiplus::Graphics* gdip)
{
	VectorPart::Draw(pDC, gdip);

	DrawBorder(pDC, gdip);
	DrawBackground(pDC, gdip);
	DrawIcons(pDC, gdip);
}

// New functions
void BitmapPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
							  HWND parentWnd, PreferenceMap& preferences)
{
	VectorPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);

	CComPtr<IMgaMetaFCO> spMetaFCO;
	if (!pFCO) {
		CComPtr<IMgaMetaRole> spRole;
		COMTHROW(pPart->get_Role(&spRole));
		COMTHROW(spRole->get_Kind(&spMetaFCO));
	}

	// Overlay Color
	m_bOverlay = false;
	m_crOverlay = COLOR_BLACK;
	PreferenceMap::iterator it = preferences.find(PREF_OVERLAYCOLOR);
	if (it != preferences.end()) {
		m_bOverlay = true;
		m_crOverlay = it->second.uValue.crValue;
	} else {
		m_bOverlay = getFacilities().getPreference(pFCO, spMetaFCO, PREF_OVERLAYCOLOR, m_crOverlay);
	}

	// Border Color
	m_crBorder = COLOR_BLACK;
	it = preferences.find(PREF_BORDERCOLOR);
	if (it != preferences.end())
		m_crBorder = it->second.uValue.crValue;
	else
		getFacilities().getPreference(pFCO, PREF_BORDERCOLOR, m_crBorder);

	// Check if we should create masked bitmap
	bool bMasked = false;
	it = preferences.find(PREF_ISMASKEDBITMAP);
	if (it != preferences.end())
		bMasked = true;

	// Bitmap
	m_pBitmap = NULL;
	it = preferences.find(PREF_ICON);
	if (it != preferences.end()) {
		if (!bMasked) {
#ifndef OLD_DECORATOR_LOOKANDFEEL
			if (m_bOverlay)
				m_pBitmap = getFacilities().getBitmapB(*it->second.uValue.pstrValue, m_crOverlay);
			else
				m_pBitmap = getFacilities().getBitmap(*it->second.uValue.pstrValue);
#else
			m_pBitmap = getFacilities().getBitmap(*it->second.uValue.pstrValue);
#endif
		} else {
			UINT bitmapResID = (UINT)(it->second.uValue.lValue);
			COLORREF crTransparent = COLOR_WHITE;
			it = preferences.find(PREF_TRANSPARENTCOLOR);
			if (it != preferences.end())
				crTransparent = it->second.uValue.crValue;
			COLORREF crGayedOut = COLOR_GRAYED_OUT;
			it = preferences.find(PREF_GRAYEDOUTCOLOR);
			if (it != preferences.end())
				crGayedOut = it->second.uValue.crValue;
			m_pBitmap = getFacilities().getMaskedBitmap(bitmapResID, crTransparent, crGayedOut );
		}
		m_pTileVector = preferences.find(PREF_TILES)->second.uValue.pTiles;
	}
	if (!m_pBitmap) {
		CString strIcon;
		getFacilities().getPreference(pFCO, spMetaFCO, PREF_ICON, strIcon);
		m_pTileVector = preferences.find(PREF_TILESUNDEF)->second.uValue.pTiles;
		if (!strIcon.IsEmpty()) {
#ifndef OLD_DECORATOR_LOOKANDFEEL
			if (m_bOverlay)
				m_pBitmap = getFacilities().getBitmapB(strIcon, m_crOverlay);
			else
				m_pBitmap = getFacilities().getBitmap(strIcon);
#else
			m_pBitmap = getFacilities().getBitmap(strIcon);
#endif
		}
		if (!m_pBitmap) {
			strIcon = *preferences.find(PREF_ICONDEFAULT)->second.uValue.pstrValue;
#ifndef OLD_DECORATOR_LOOKANDFEEL
			if (m_bOverlay)
				m_pBitmap = getFacilities().getBitmapB(strIcon, m_crOverlay);
			else
				m_pBitmap = getFacilities().getBitmap(strIcon);
#else
			m_pBitmap = getFacilities().getBitmap(strIcon);
#endif
			m_pTileVector = preferences.find(PREF_TILESDEFAULT)->second.uValue.pTiles;
		}
	}

	m_bRoundCornerRect = false;
	it = preferences.find(PREF_ROUNDCORNERRECT);
	if (it != preferences.end()) {
		m_bRoundCornerRect = it->second.uValue.bValue;
	} else {
		getFacilities().getPreference(m_spFCO, m_spMetaFCO, PREF_ROUNDCORNERRECT, m_bRoundCornerRect);
	}

	m_bRoundCornerRadius = 9;
	it = preferences.find(PREF_ROUNDCORNERRADIUS);
	if (it != preferences.end()) {
		m_bRoundCornerRadius = it->second.uValue.bValue;
	} else {
		getFacilities().getPreference(m_spFCO, m_spMetaFCO, PREF_ROUNDCORNERRADIUS, m_bRoundCornerRadius, false);
	}

	SimpleCoordCommand* leftMost	= new SimpleCoordCommand(LeftMost);
	SimpleCoordCommand* topMost		= new SimpleCoordCommand(TopMost);
	SimpleCoordCommand* rightMost	= new SimpleCoordCommand(RightMost);
	SimpleCoordCommand* bottomMost	= new SimpleCoordCommand(BottomMost);
	m_coordCommands.push_back(leftMost);
	m_coordCommands.push_back(topMost);
	m_coordCommands.push_back(rightMost);
	m_coordCommands.push_back(bottomMost);

	AddCommand(VectorCommand(VectorCommand::BeginPath));

	if (m_bRoundCornerRect) {
		ComplexCoordCommand* leftoRadius = new ComplexCoordCommand(LeftMost);
		leftoRadius->AddCommand(OneConstant, m_bRoundCornerRadius, CoordAdd);
		ComplexCoordCommand* topoRadius = new ComplexCoordCommand(TopMost);
		topoRadius->AddCommand(OneConstant, m_bRoundCornerRadius, CoordAdd);
		ComplexCoordCommand* rightoRadius = new ComplexCoordCommand(RightMost);
		rightoRadius->AddCommand(OneConstant, m_bRoundCornerRadius, CoordSubstract);
		ComplexCoordCommand* bottomoRadius = new ComplexCoordCommand(BottomMost);
		bottomoRadius->AddCommand(OneConstant, m_bRoundCornerRadius, CoordSubstract);

		ComplexCoordCommand* lefto2Radius = new ComplexCoordCommand(LeftMost);
		lefto2Radius->AddCommand(OneConstant, 2 * m_bRoundCornerRadius, CoordAdd);
		ComplexCoordCommand* topo2Radius = new ComplexCoordCommand(TopMost);
		topo2Radius->AddCommand(OneConstant, 2 * m_bRoundCornerRadius, CoordAdd);
		ComplexCoordCommand* righto2Radius = new ComplexCoordCommand(RightMost);
		righto2Radius->AddCommand(OneConstant, 2 * m_bRoundCornerRadius, CoordSubstract);
		ComplexCoordCommand* bottomo2Radius = new ComplexCoordCommand(BottomMost);
		bottomo2Radius->AddCommand(OneConstant, 2 * m_bRoundCornerRadius, CoordSubstract);

		AbsoluteCoordCommand* radiusCommand = new AbsoluteCoordCommand(m_bRoundCornerRadius);
		AbsoluteCoordCommand* diameterCommand = new AbsoluteCoordCommand(2 * m_bRoundCornerRadius);
		SimpleCoordCommand* angle0Command = new SimpleCoordCommand(ZeroConstant);
		AbsoluteCoordCommand* angle90Command = new AbsoluteCoordCommand(90);
		AbsoluteCoordCommand* angle180Command = new AbsoluteCoordCommand(180);
		AbsoluteCoordCommand* angle270Command = new AbsoluteCoordCommand(270);

		m_coordCommands.push_back(leftoRadius);
		m_coordCommands.push_back(topoRadius);
		m_coordCommands.push_back(rightoRadius);
		m_coordCommands.push_back(bottomoRadius);
		m_coordCommands.push_back(lefto2Radius);
		m_coordCommands.push_back(topo2Radius);
		m_coordCommands.push_back(righto2Radius);
		m_coordCommands.push_back(bottomo2Radius);
		m_coordCommands.push_back(radiusCommand);
		m_coordCommands.push_back(diameterCommand);
		m_coordCommands.push_back(angle0Command);
		m_coordCommands.push_back(angle90Command);
		m_coordCommands.push_back(angle180Command);
		m_coordCommands.push_back(angle270Command);

		std::vector<const CoordCommand*> m_arcParams;
		m_arcParams.push_back(leftMost);
		m_arcParams.push_back(topMost);
		m_arcParams.push_back(diameterCommand);
		m_arcParams.push_back(diameterCommand);
		m_arcParams.push_back(angle180Command);
		m_arcParams.push_back(angle90Command);
		AddCommand(VectorCommand(m_arcParams, VectorCommand::AddArcToPath));
		AddCommand(VectorCommand(leftoRadius, topMost, rightoRadius, topMost, VectorCommand::AddLineToPath));
		m_arcParams[0] = righto2Radius;
		m_arcParams[1] = topMost;
		m_arcParams[2] = diameterCommand;
		m_arcParams[3] = diameterCommand;
		m_arcParams[4] = angle270Command;
		m_arcParams[5] = angle90Command;
		AddCommand(VectorCommand(m_arcParams, VectorCommand::AddArcToPath));
		AddCommand(VectorCommand(rightMost, topoRadius, rightMost, bottomoRadius, VectorCommand::AddLineToPath));
		m_arcParams[0] = righto2Radius;
		m_arcParams[1] = bottomo2Radius;
		m_arcParams[2] = diameterCommand;
		m_arcParams[3] = diameterCommand;
		m_arcParams[4] = angle0Command;
		m_arcParams[5] = angle90Command;
		AddCommand(VectorCommand(m_arcParams, VectorCommand::AddArcToPath));
		AddCommand(VectorCommand(rightoRadius, bottomMost, leftoRadius, bottomMost, VectorCommand::AddLineToPath));
		m_arcParams[0] = leftMost;
		m_arcParams[1] = bottomo2Radius;
		m_arcParams[2] = diameterCommand;
		m_arcParams[3] = diameterCommand;
		m_arcParams[4] = angle90Command;
		m_arcParams[5] = angle90Command;
		AddCommand(VectorCommand(m_arcParams, VectorCommand::AddArcToPath));
		AddCommand(VectorCommand(leftMost, bottomoRadius, leftMost, topoRadius, VectorCommand::AddLineToPath));
	} else {
		AddCommand(VectorCommand(leftMost,		bottomMost,	rightMost,		bottomMost,	VectorCommand::AddLineToPath));
		AddCommand(VectorCommand(rightMost,		bottomMost,	rightMost,		topMost,	VectorCommand::AddLineToPath));
		AddCommand(VectorCommand(rightMost,		topMost,	leftMost,		topMost,	VectorCommand::AddLineToPath));
		AddCommand(VectorCommand(leftMost,		topMost,	leftMost,		bottomMost,	VectorCommand::AddLineToPath));
	}

	AddCommand(VectorCommand(VectorCommand::EndPath));
	AddCommand(VectorCommand(VectorCommand::CopyShadowPath));
	AddCommand(VectorCommand(VectorCommand::CastShadowPath));
}

void BitmapPart::DrawBorder(CDC* pDC, Gdiplus::Graphics* gdip)
{
	if (m_lBorderWidth != 0)
		getFacilities().DrawRect(gdip, GetBoxLocation(true), (m_bActive) ? m_crBorder : COLOR_GRAY, m_lBorderWidth);
	if (m_bHasViolation && m_bActive)
		getFacilities().DrawRect(gdip, GetBoxLocation(true), COLOR_RED, WIDTH_BORDERVIOLATION);
}

void BitmapPart::DrawBackground(CDC* pDC, Gdiplus::Graphics* gdip)
{
	CRect cRect = GetBoxLocation(false);
	if (m_bActive)
		m_pBitmap->draw(gdip, pDC, cRect, *m_pTileVector);
	else
		getFacilities().DrawRect(gdip, cRect, COLOR_GRAY, 2);
}

void BitmapPart::DrawIcons(CDC* pDC, Gdiplus::Graphics* gdip)
{
}

}; // namespace DecoratorSDK
