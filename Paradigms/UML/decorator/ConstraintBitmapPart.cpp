//################################################################################################
//
// Constraint Bitmap decorator class
//	ConstraintBitmapPart.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "ConstraintBitmapPart.h"


//################################################################################################
//
// CLASS : ConstraintBitmapPart
//
//################################################################################################

ConstraintBitmapPart::ConstraintBitmapPart(PartBase* pPart, CComPtr<IMgaNewDecoratorEvents> eventSink, long bitmapResID,
										   COLORREF transparentColor, COLORREF grayedOutColor):
	BitmapPart		(pPart, eventSink),
	m_lBitmapResID	(bitmapResID),
	m_crTransparent	(transparentColor),
	m_crGrayedOut	(grayedOutColor)
{
}

ConstraintBitmapPart::~ConstraintBitmapPart()
{
}

void ConstraintBitmapPart::Initialize(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO)
{
	BitmapPart::Initialize(pProject, pPart, pFCO);
}

feature_code ConstraintBitmapPart::GetFeatures(void) const
{
	return F_RESIZABLE | F_MOUSEEVENTS;
}

// New functions
void ConstraintBitmapPart::InitializeEx(CComPtr<IMgaProject>& pProject, CComPtr<IMgaMetaPart>& pPart, CComPtr<IMgaFCO>& pFCO,
										HWND parentWnd, DecoratorSDK::PreferenceMap& preferences)
{
	preferences[DecoratorSDK::PREF_ISMASKEDBITMAP]		= DecoratorSDK::PreferenceVariant(true);

	preferences[DecoratorSDK::PREF_ICONDEFAULT]			= DecoratorSDK::PreferenceVariant(DecoratorSDK::createResString(IDB_ATOM));
	preferences[DecoratorSDK::PREF_TILESDEFAULT]		= DecoratorSDK::PreferenceVariant(DecoratorSDK::getFacilities().getTileVector(DecoratorSDK::TILE_ATOMDEFAULT));
	preferences[DecoratorSDK::PREF_TILESUNDEF]			= DecoratorSDK::PreferenceVariant(DecoratorSDK::getFacilities().getTileVector(DecoratorSDK::TILE_ATOMDEFAULT));
	preferences[DecoratorSDK::PREF_TILES]				= DecoratorSDK::PreferenceVariant(DecoratorSDK::getFacilities().getTileVector(DecoratorSDK::TILE_ATOMDEFAULT));

	preferences[DecoratorSDK::PREF_ICON]				= DecoratorSDK::PreferenceVariant(m_lBitmapResID);
	preferences[DecoratorSDK::PREF_TRANSPARENTCOLOR]	= DecoratorSDK::PreferenceVariant(m_crTransparent);
	preferences[DecoratorSDK::PREF_GRAYEDOUTCOLOR]		= DecoratorSDK::PreferenceVariant(m_crGrayedOut);
	BitmapPart::InitializeEx(pProject, pPart, pFCO, parentWnd, preferences);
}

void ConstraintBitmapPart::DrawBackground(CDC* pDC)
{
	CRect cRect = GetBoxLocation(false);
	UINT modifFlags = DecoratorSDK::MF_TRANSPARENT;
	if (!m_bActive)
		modifFlags |= DecoratorSDK::MF_GREYED;
	m_pBitmap->draw(pDC, cRect, *m_pTileVector, modifFlags);
}
