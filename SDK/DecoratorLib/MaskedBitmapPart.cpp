//################################################################################################
//
// Masked Bitmap decorator class
//	MaskedBitmapPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "MaskedBitmapPart.h"


namespace DecoratorSDK {

//################################################################################################
//
// CLASS : MaskedBitmapPart
//
//################################################################################################

MaskedBitmapPart::MaskedBitmapPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink, long bitmapResID,
								   COLORREF transparentColor, COLORREF grayedOutColor):
	BitmapPart		(pPart, eventSink),
	m_lBitmapResID	(bitmapResID),
	m_crTransparent	(transparentColor),
	m_crGrayedOut	(grayedOutColor)
{
}

MaskedBitmapPart::~MaskedBitmapPart()
{
}

void MaskedBitmapPart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	BitmapPart::Initialize(pProject, pPart, pFCO);
}

feature_code MaskedBitmapPart::GetFeatures(void) const
{
	return F_RESIZABLE | F_MOUSEEVENTS;
}

// New functions
void MaskedBitmapPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
										HWND parentWnd, PreferenceMap& preferences)
{
	preferences[PREF_ISMASKEDBITMAP]	= PreferenceVariant(true);

	preferences[PREF_ICONDEFAULT]		= PreferenceVariant(createResString(IDB_ATOM));
	preferences[PREF_TILESDEFAULT]		= PreferenceVariant(getFacilities().getTileVector(TILE_ATOMDEFAULT));
	preferences[PREF_TILESUNDEF]		= PreferenceVariant(getFacilities().getTileVector(TILE_ATOMDEFAULT));
	preferences[PREF_TILES]				= PreferenceVariant(getFacilities().getTileVector(TILE_ATOMDEFAULT));

	preferences[PREF_ICON]				= PreferenceVariant(m_lBitmapResID);
	preferences[PREF_TRANSPARENTCOLOR]	= PreferenceVariant(m_crTransparent);
	preferences[PREF_GRAYEDOUTCOLOR]	= PreferenceVariant(m_crGrayedOut);
	BitmapPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

void MaskedBitmapPart::DrawBackground(CDC* pDC)
{
	CRect cRect = GetBoxLocation(false);
	UINT modifFlags = MF_TRANSPARENT;
	if (!m_bActive)
		modifFlags |= MF_GREYED;
	m_pBitmap->draw(pDC, cRect, *m_pTileVector, modifFlags);
}

}; // namespace DecoratorSDK
