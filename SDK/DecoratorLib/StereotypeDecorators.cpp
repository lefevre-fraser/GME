//################################################################################################
//
// Mga Decorator Base
//	StereotypeDecorators.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "StereotypeDecorators.h"

#include "DecoratorDefs.h"
#include "DecoratorUtil.h"
#include "BitmapUtil.h"
#include <algorithm>

namespace DecoratorSDK
{

//################################################################################################
//
//	CLASS : DecoratorBase
//
//################################################################################################

DecoratorBase::DecoratorBase( CComPtr<IMgaMetaPart> spPart, CComPtr<IMgaFCO> spFCO )
	: m_spPart( spPart ), m_spFCO( spFCO ), m_bActive( true ), m_bHasViolation( false ), m_lBorderWidth( 0 ), m_bReferenced( false ), m_crBorder( COLOR_BLACK )
{
}

void DecoratorBase::initialize( PreferenceMap& mapPrefs )
{
	// Obtain the MetaFCO if it is required
	// Get Label and ObjectType

	PreferenceMap::iterator it = mapPrefs.find( PREF_LABEL );
	bool bNameDefined = it != mapPrefs.end();
	if ( bNameDefined )
		m_strName = *it->second.uValue.pstrValue;

	CComBSTR bstrName;
	CComPtr<IMgaMetaFCO> spMetaFCO;
	if ( ! m_spFCO ) {
		CComPtr<IMgaMetaRole> spRole;
		COMTHROW( m_spPart->get_Role( &spRole ) );
		COMTHROW( spRole->get_Kind( &spMetaFCO ) );

		if ( ! bNameDefined ) {
			COMTHROW( spRole->get_DisplayedName( &bstrName ) );
			if ( bstrName.Length() == 0 ) {
				bstrName.Empty();
				COMTHROW( spMetaFCO->get_Name( &bstrName ) );
			}
		}
		COMTHROW( spMetaFCO->get_ObjType( &m_eType ) );
	}
	else {
		if ( ! bNameDefined )
			COMTHROW( m_spFCO->get_Name( &bstrName ) );
		COMTHROW( m_spFCO->get_ObjType( &m_eType ) );
	}
	if ( ! bNameDefined )
		CopyTo( bstrName, m_strName );
	if ( m_strName == "Condition" ) {
		m_strName = "Condition";
	}

	// Label's Font

	m_iFontKey = FONT_LABEL;
	it = mapPrefs.find( PREF_LABELFONT );
	if ( it != mapPrefs.end() )
		m_iFontKey = it->second.uValue.lValue;

	// Label's Max Length

	m_iMaxTextLength = MAX_LABEL_LENGTH;
	it = mapPrefs.find( PREF_LABELLENGTH );
	if ( it != mapPrefs.end() )
		m_iMaxTextLength = it->second.uValue.lValue;

	// Label's Color

	m_crName = COLOR_BLACK;
	it = mapPrefs.find( PREF_LABELCOLOR );
	if ( it != mapPrefs.end() )
		m_crName = it->second.uValue.crValue;
	else
		if ( m_spFCO )
			getFacilities().getPreference( m_spFCO, PREF_LABELCOLOR, m_crName );

	// Label's Location

	m_eNameLocation = L_SOUTH;
	it = mapPrefs.find( PREF_LABELLOCATION );
	if ( it != mapPrefs.end() )
		m_eNameLocation = it->second.uValue.eLocation;
	else
		if ( m_spFCO )
			getFacilities().getPreference( m_spFCO, PREF_LABELLOCATION, m_eNameLocation );

	// Label's Enabled

	if ( m_spFCO ) {
		if ( ! getFacilities().getPreference( m_spFCO, PREF_LABELENABLED, m_bNameEnabled ) )
			m_bNameEnabled = true;
	}
	else
		m_bNameEnabled = true;

	// Label's Wrap

	if ( m_spFCO ) {
		if ( getFacilities().getPreference( m_spFCO, PREF_LABELWRAP, m_iNameWrapCount ) )
			m_iNameWrapCount = max( m_iNameWrapCount, 0L );
		else
			m_iNameWrapCount = 0;
	}
	else
		m_iNameWrapCount = 0;

	m_vecName = getFacilities().wrapString( m_strName, m_iNameWrapCount, m_iMaxTextLength );

	// Overlay Color

	m_bOverlay = false;
	m_crOverlay = COLOR_BLACK;
	it = mapPrefs.find( PREF_OVERLAYCOLOR );
	if ( it != mapPrefs.end() ) {
		m_bOverlay = true;
		m_crOverlay = it->second.uValue.crValue;
	}
	else
		m_bOverlay = getFacilities().getPreference( m_spFCO, spMetaFCO, PREF_OVERLAYCOLOR, m_crOverlay );

	// Bitmap and Tiles

	m_pBitmap = NULL;
	it = mapPrefs.find( PREF_ICON );
	if ( it != mapPrefs.end() ) {
		#ifndef OLD_DECORATOR_LOOKANDFEEL
			m_pBitmap = ( m_bOverlay ) ? getFacilities().getBitmapB( *it->second.uValue.pstrValue, m_crOverlay ) : getFacilities().getBitmap( *it->second.uValue.pstrValue );
		#else
			m_pBitmap = getFacilities().getBitmap( *it->second.uValue.pstrValue );
		#endif
		m_pTileVector = mapPrefs.find( PREF_TILES )->second.uValue.pTiles;
	}
	if ( ! m_pBitmap ) {
		CString strIcon;
		getFacilities().getPreference( m_spFCO, spMetaFCO, PREF_ICON, strIcon );
		m_pTileVector = mapPrefs.find( PREF_TILESUNDEF )->second.uValue.pTiles;
		if ( ! strIcon.IsEmpty() ) {
			#ifndef OLD_DECORATOR_LOOKANDFEEL
				m_pBitmap = ( m_bOverlay ) ? getFacilities().getBitmapB( strIcon, m_crOverlay ) : getFacilities().getBitmap( strIcon );
			#else
				m_pBitmap = getFacilities().getBitmap( strIcon );
			#endif
		}
		if ( ! m_pBitmap ) {
			strIcon = *mapPrefs.find( PREF_ICONDEFAULT )->second.uValue.pstrValue;
			#ifndef OLD_DECORATOR_LOOKANDFEEL
				m_pBitmap = ( m_bOverlay ) ? getFacilities().getBitmapB( strIcon, m_crOverlay ) : getFacilities().getBitmap( strIcon );
			#else
				m_pBitmap = getFacilities().getBitmap( strIcon );
			#endif
			m_pTileVector = mapPrefs.find( PREF_TILESDEFAULT )->second.uValue.pTiles;
		}
	}

	// HasViolations

	if ( m_spFCO ) {
		it = mapPrefs.find( PREF_VIOLATED );
		if ( it != mapPrefs.end() )
			m_bHasViolation = it->second.uValue.bValue;
		else
			m_bHasViolation = getFacilities().getPreferenceStatus( m_spFCO, PREF_VIOLATED ) == PS_HERE;
	}
}

objtype_enum DecoratorBase::getType() const
{
	return m_eType;
}

void DecoratorBase::setActive( bool bActive )
{
	m_bActive = bActive;
}

void DecoratorBase::setReferenced()
{
	m_bReferenced = true;
}

long DecoratorBase::getBorderWidth( bool bActive ) const
{
	long lBorderWidth = m_lBorderWidth;
	if ( ( m_bActive || bActive ) && m_bHasViolation )
		lBorderWidth += WIDTH_BORDERVIOLATION + 1;
	return lBorderWidth;
}

CSize DecoratorBase::getPreferredSize() const
{
	return CSize( m_pBitmap->getWidth() + getBorderWidth( false ) * 2, m_pBitmap->getHeight() + getBorderWidth( false ) * 2 );
}

void DecoratorBase::setLocation( const CRect& cRect )
{
	CRect cRect2 = cRect;
	/*if ( m_bNameEnabled && ! m_vecName.empty() && ! m_vecName[ 0 ].IsEmpty() ) {
		int iLabelSize = getFacilities().getFont( m_iFontKey )->iSize * m_vecName.size();
		if ( m_eNameLocation == L_NORTH )
			cRect2.top += iLabelSize;
		else if ( m_eNameLocation == L_SOUTH )
			cRect2.bottom -= iLabelSize;
	}*/
	setBoxLocation( cRect2 );
}

CRect DecoratorBase::getLocation() const
{
	CRect cRect = getBoxLocation( true );
	/*if ( m_bNameEnabled && ! m_vecName.empty() && ! m_vecName[ 0 ].IsEmpty() ) {
		int iLabelSize = getFacilities().getFont( m_iFontKey )->iSize * m_vecName.size();
		if ( m_eNameLocation == L_NORTH )
			cRect.top -= iLabelSize;
		else if ( m_eNameLocation == L_SOUTH )
			cRect.bottom += iLabelSize;
	}*/
	return cRect;
}

void DecoratorBase::setBoxLocation( const CRect& cRect )
{
	m_Rect = cRect;
}

CRect DecoratorBase::getBoxLocation( bool bWithBorder ) const
{
	if ( bWithBorder )
		return m_Rect;
	CRect cRect = m_Rect;
	cRect.DeflateRect( getBorderWidth( false ), getBorderWidth( false ) );
	return cRect;
}

ECoordRefPoint DecoratorBase::getAlignment() const
{
	switch ( m_eNameLocation ) {
		case L_NORTH :
		case L_CENTER :
		case L_SOUTH :
			return CRP_CENTER;
		case L_NORTHEAST :
		case L_EAST :
		case L_SOUTHEAST :
			return CRP_BEGIN;
		default :
			return CRP_END;
	}
}

CPoint DecoratorBase::getLabelPosition() const
{
	CPoint pt;
	CRect cRect = getBoxLocation( true );
	int iLabelSize = getFacilities().getFont( m_iFontKey )->iSize * m_vecName.size();
	switch( m_eNameLocation ) {
		case L_NORTH : case L_NORTHWEST : case L_NORTHEAST :
			pt.y = cRect.top - iLabelSize - GAP_LABEL;
			break;
		case L_SOUTH : case L_SOUTHWEST : case L_SOUTHEAST :
			pt.y = cRect.bottom + GAP_LABEL;
			break;
		default :
			pt.y = cRect.CenterPoint().y - iLabelSize / 2;
			break;
	}
	switch( m_eNameLocation ) {
		case L_WEST : case L_NORTHWEST : case L_SOUTHWEST :
			pt.x = cRect.left - GAP_LABEL;
			break;
		case L_NORTH : case L_CENTER : case L_SOUTH :
			pt.x = cRect.CenterPoint().x;
			break;
		default :
			pt.x = cRect.right + GAP_LABEL;
			break;
	}
	return pt;
}

CRect DecoratorBase::getLabelLocation() const
{

	CPoint pt = getLabelPosition();
	ECoordRefPoint eAlign = getAlignment();

	CDC dc;
	dc.CreateCompatibleDC(NULL);
	dc.SelectObject(getFacilities().getFont( m_iFontKey )->pFont);
	CSize cSize(0,0);
	for ( unsigned int i = 0 ; i < m_vecName.size() ; i++ ) {
		CSize tmpSize = dc.GetTextExtent(m_vecName[ i ]);
		cSize.cy += tmpSize.cy;
		cSize.cx = max (cSize.cx, tmpSize.cx);
	}

	if ( eAlign == CRP_CENTER )
		pt.x -= cSize.cx / 2;
	else if ( eAlign == CRP_END )
		pt.x -= cSize.cx;


	return CRect( pt.x, pt.y, pt.x + cSize.cx, pt.y + cSize.cy );
}

CComPtr<IMgaFCO> DecoratorBase::getFCO() const
{
	return m_spFCO;
}

void DecoratorBase::draw( CDC* pDC ) const
{
	drawBorder( pDC );
	drawBackground( pDC );
	if ( m_bNameEnabled )
		drawLabel( pDC );
	drawIcons( pDC );
}

void DecoratorBase::drawBorder( CDC* pDC ) const
{
	if ( m_lBorderWidth != 0 )
		getFacilities().drawRect( pDC, getBoxLocation( true ), ( m_bActive ) ? m_crBorder : COLOR_GRAY, m_lBorderWidth );
	if ( m_bHasViolation && m_bActive )
		getFacilities().drawRect( pDC, getBoxLocation( true ), COLOR_RED, WIDTH_BORDERVIOLATION );
}

void DecoratorBase::drawBackground( CDC* pDC ) const
{
	CRect cRect = getBoxLocation();
	if ( m_bActive )
		m_pBitmap->draw( NULL, pDC, cRect, *m_pTileVector );
	else
		getFacilities().drawRect( pDC, cRect, COLOR_GRAY, 2 );
}

void DecoratorBase::drawLabel( CDC* pDC ) const
{
	ECoordRefPoint eAlign = getAlignment();
	int iAlign = ( eAlign == CRP_BEGIN ) ? TA_LEFT : ( eAlign == CRP_CENTER ) ? TA_CENTER : TA_RIGHT;
	iAlign |= TA_TOP;

	int iLabelSize = getFacilities().getFont( m_iFontKey )->iSize;
	CPoint pt = getLabelPosition();
	for ( unsigned int i = 0 ; i < m_vecName.size() ; i++ )
		getFacilities().drawText( pDC, m_vecName[ i ], CPoint( pt.x, pt.y + i * iLabelSize ), getFacilities().getFont( m_iFontKey )->pFont, ( m_bActive ) ? m_crName : COLOR_GRAY, iAlign, m_iMaxTextLength, "", "", false );
}

void DecoratorBase::drawIcons( CDC* pDC ) const
{
}

//################################################################################################
//
//	CLASS : PortDecorator
//
//################################################################################################

PortDecorator::PortDecorator( CComPtr<IMgaFCO> spFCO, const CPoint& ptInner )
	: DecoratorBase( NULL, spFCO ), m_ptInner( ptInner )
	, m_bInsideContainer( true), m_eAdjust(L_WEST)
{
}

void PortDecorator::initialize( PreferenceMap& mapPrefs )
{
	// PortBitmap

	CString strIcon;
	if ( getFacilities().getPreference( m_spFCO, PREF_PORTICON, strIcon ) ) {
		mapPrefs[ PREF_ICON ] = PreferenceVariant( strIcon );
		mapPrefs[ PREF_TILES ] = PreferenceVariant( getFacilities().getTileVector( TILE_PORTDEFAULT ) );
	}

	COMTHROW( m_spFCO->get_ObjType( &m_eType ) );
	switch ( m_eType ) {
		case OBJTYPE_MODEL :
			strIcon = createResString( IDB_MODELPORT );
			break;
		case OBJTYPE_SET :
			strIcon = createResString( IDB_SETPORT );
			break;
		case OBJTYPE_REFERENCE :
			strIcon = createResString( IDB_REFERENCEPORT );
			break;
		default :
			strIcon = createResString( IDB_ATOMPORT );
			break;
	}
	mapPrefs[ PREF_ICONDEFAULT ] = PreferenceVariant( strIcon );
	mapPrefs[ PREF_TILESDEFAULT ] = PreferenceVariant( getFacilities().getTileVector( TILE_PORTDEFAULT ) );
	mapPrefs[ PREF_TILESUNDEF ] = PreferenceVariant( getFacilities().getTileVector( TILE_PORTDEFAULT ) );

	// port label displayed inside or outside container?
	m_bInsideContainer = mapPrefs[ PREF_PORTLABELINSIDE  ].uValue.bValue;

	// Label Font

	if( m_bInsideContainer)
		mapPrefs[ PREF_LABELFONT ] = PreferenceVariant( (long) FONT_PORT );
	else
		mapPrefs[ PREF_LABELFONT ] = PreferenceVariant( (long) FONT_PORT_OUTSIDE );

	m_eAdjust = mapPrefs[ PREF_LABELLOCATION ].uValue.eLocation;
	DecoratorBase::initialize( mapPrefs );
}

CSize PortDecorator::getPreferredSize() const
{
	return CSize( WIDTH_PORT, HEIGHT_PORT );
}

CPoint PortDecorator::getInnerPosition() const
{
	return m_ptInner;
}

void PortDecorator::drawBackground( CDC* pDC ) const
{
	CRect cRect = getBoxLocation();
	if ( m_bActive )
		m_pBitmap->draw( NULL, pDC, cRect, *m_pTileVector );
	else {
		cRect.right--;
		cRect.bottom--;
		getFacilities().drawRect( pDC, cRect, COLOR_GRAY, 1 );
	}
}

CPoint PortDecorator::getLabelPosition() const
{
	int d = (m_eAdjust == L_EAST)? 1: -1;
	CPoint pt = DecoratorBase::getLabelPosition();
	if( !m_bInsideContainer)
		pt += CPoint(d*7, -7); 

	return pt;
}

long PortDecorator::getLongest() const
{
	long maxv = 0;
	for ( unsigned int i = 0 ; i < m_vecName.size() ; i++ ) {
		long ilen = m_vecName[i].GetLength();
		if( maxv < ilen)
			maxv = ilen;
	}
	return maxv;
}

struct PortLess
{
	bool operator()( PortDecorator* pPortA, PortDecorator* pPortB )
	{
		return pPortA->getInnerPosition().y < pPortB->getInnerPosition().y;
	}
};

//################################################################################################
//
//	CLASS : TypeableDecorator
//
//################################################################################################

TypeableDecorator::TypeableDecorator( CComPtr<IMgaMetaPart> spPart, CComPtr<IMgaFCO> spFCO )
	: DecoratorBase( spPart, spFCO ), m_bTypeIconEnabled( false ), m_bTypeNameEnabled( false ), m_iTypeInfo( 0 ), m_strTypeName( "" )
{
}

void TypeableDecorator::initialize( PreferenceMap& mapPrefs )
{
	if ( m_spFCO ) {
		PreferenceMap::iterator it = mapPrefs.find( PREF_TYPEINFOSHOWN );
		if ( it != mapPrefs.end() )
			m_bTypeIconEnabled = it->second.uValue.bValue;
		else
			if ( ! getFacilities().getPreference( m_spFCO, PREF_TYPEINFOSHOWN, m_bTypeIconEnabled ) )
				m_bTypeIconEnabled = false;

		it = mapPrefs.find( PREF_TYPESHOWN );
		if ( it != mapPrefs.end() )
			m_bTypeNameEnabled = it->second.uValue.bValue;
		else
			if ( ! getFacilities().getPreference( m_spFCO, PREF_TYPESHOWN, m_bTypeNameEnabled ) )
				m_bTypeNameEnabled = false;


		VARIANT_BOOL bInstance = VARIANT_FALSE;
		COMTHROW( m_spFCO->get_IsInstance( &bInstance ) );
		if ( bInstance == VARIANT_TRUE ) {
			m_iTypeInfo = 3;
			if ( m_bTypeNameEnabled ) {
				CComPtr<IMgaFCO> spType;
				COMTHROW( m_spFCO->get_DerivedFrom( &spType ) );
				CComBSTR bstrName;
				COMTHROW( spType->get_Name( &bstrName ) );
				CopyTo( bstrName, m_strTypeName );
			}
		}
		else {
			CComPtr<IMgaFCO> spType;
			COMTHROW( m_spFCO->get_DerivedFrom( &spType ) );
			if ( spType )
				m_iTypeInfo = 2;
			else {
				CComPtr<IMgaFCOs> spFCOs;
				COMTHROW( m_spFCO->get_DerivedObjects( &spFCOs ) );
				long lCount = 0;
				COMTHROW( spFCOs->get_Count( &lCount ) );
				m_iTypeInfo = ( lCount == 0 ) ? 0 : 1;
			}
		}
	}

	DecoratorBase::initialize( mapPrefs );

	// TypeInheritance Bitmap and Tiles

	if ( m_spFCO && ( m_iTypeInfo == 3 || m_iTypeInfo == 2 ) ) {
		BitmapBase* pBitmap = NULL;
		TileVector* pTileVector = NULL;
		PreferenceMap::iterator it = mapPrefs.find( ( m_iTypeInfo == 2 ) ? PREF_SUBTYPEICON : PREF_INSTANCEICON );
		if ( it != mapPrefs.end() ) {
			#ifndef OLD_DECORATOR_LOOKANDFEEL
				pBitmap = ( m_bOverlay ) ? getFacilities().getBitmapB( *it->second.uValue.pstrValue, m_crOverlay ) : getFacilities().getBitmap( *it->second.uValue.pstrValue );
			#else
				pBitmap = getFacilities().getBitmap( *it->second.uValue.pstrValue );
			#endif
				pTileVector = mapPrefs.find( PREF_TILES )->second.uValue.pTiles;
		}
		if ( ! pBitmap ) {
			CString strIcon;
			if ( getFacilities().getPreference( m_spFCO, ( m_iTypeInfo == 2 ) ? PREF_SUBTYPEICON : PREF_INSTANCEICON, strIcon ) ) {
				pTileVector = mapPrefs.find( PREF_TILESUNDEF )->second.uValue.pTiles;
				if ( ! strIcon.IsEmpty() ) {
					#ifndef OLD_DECORATOR_LOOKANDFEEL
						pBitmap = ( m_bOverlay ) ? getFacilities().getBitmapB( strIcon, m_crOverlay ) : getFacilities().getBitmap( strIcon );
					#else
						pBitmap = getFacilities().getBitmap( strIcon );
					#endif
				}
			}
		}
		if ( pBitmap ) {
			m_pBitmap = pBitmap;
			m_pTileVector = pTileVector;
		}
	}
}

CPoint TypeableDecorator::getLabelPosition() const
{
	CPoint pt = DecoratorBase::getLabelPosition();

	if ( m_bTypeNameEnabled && m_iTypeInfo == 3 ) {
		int iLabelSize = getFacilities().getFont( FONT_TYPE )->iSize;
		switch( m_eNameLocation ) {
			case L_NORTH : case L_NORTHWEST : case L_NORTHEAST :
				pt.y = pt.y - iLabelSize - GAP_LABEL;
				break;
			case L_CENTER : case L_WEST : case L_EAST :
				pt.y = pt.y - iLabelSize / 2 - GAP_LABEL / 2;
				break;
		}
	}
	return pt;
}

CRect TypeableDecorator::getLabelLocation() const
{
	CRect cRect = DecoratorBase::getLabelLocation();

	if ( m_bTypeNameEnabled && m_iTypeInfo == 3 ) {
		LOGFONT logFont;
		getFacilities().getFont( FONT_TYPE )->pFont->GetLogFont( &logFont );
		ECoordRefPoint eAlign = getAlignment();

		CSize cSize( logFont.lfWidth * m_strTypeName.GetLength(), logFont.lfHeight );
		cRect.bottom += cSize.cy + GAP_LABEL;
		if ( cSize.cx > cRect.Width() ) {
			switch ( eAlign ) {
				case CRP_BEGIN :
					cRect.right += cSize.cx - cRect.Width();
					break;
				case CRP_CENTER :
					cRect.left -= ( cSize.cx - cRect.Width() ) / 2;
					cRect.right += ( cSize.cx - cRect.Width() ) / 2;
					break;
				case CRP_END :
					cRect.left -= cSize.cx - cRect.Width();
					break;
			}
		}
	}
	return cRect;
}

void TypeableDecorator::drawLabel( CDC* pDC ) const
{
	DecoratorBase::drawLabel( pDC );

	if ( m_bTypeNameEnabled && m_iTypeInfo == 3 ) {
		ECoordRefPoint eAlign = getAlignment();
		int iAlign = ( eAlign == CRP_BEGIN ) ? TA_LEFT : ( eAlign == CRP_CENTER ) ? TA_CENTER : TA_RIGHT;
		iAlign |= TA_TOP;
		CPoint pt = getLabelPosition();
		pt.y += GAP_LABEL + getFacilities().getFont( FONT_LABEL )->iSize * m_vecName.size();

		getFacilities().drawText( pDC, m_strTypeName, pt, getFacilities().getFont( FONT_TYPE )->pFont, ( m_bActive ) ? m_crName : COLOR_GRAY, iAlign, MAX_TYPE_LENGTH, "[ ", " ]" );
	}
}

void TypeableDecorator::drawIcons( CDC* pDC ) const
{
	DecoratorBase::drawIcons( pDC );

	if ( m_bTypeIconEnabled && m_iTypeInfo != 0 ) {
		CRect cRect = getBoxLocation();
		CString strRes;
		if ( m_bActive )
			strRes = createResString( ( m_iTypeInfo == 1 ) ? IDB_ICON_TYPE : ( m_iTypeInfo == 2 ) ? IDB_ICON_SUBTYPE : IDB_ICON_INSTANCE );
		else
			strRes = createResString( ( m_iTypeInfo == 1 ) ? IDB_ICON_TYPE_DIS : ( m_iTypeInfo == 2 ) ? IDB_ICON_SUBTYPE_DIS : IDB_ICON_INSTANCE_DIS );
		BitmapBase* pBitmap = getFacilities().getBitmap( strRes );
		int width = ( cRect.Width() - pBitmap->getWidth() ) /2;
		int height =  ( cRect.Height() - pBitmap->getHeight() ) /2;
		CRect rDest( cRect.left + width, cRect.top + height, cRect.left + width + pBitmap->getWidth(), cRect.top + height + pBitmap->getHeight() );
		pBitmap->draw( NULL, pDC, rDest, TileVector( 1, BackgroundTile() ) );
	}
}

//################################################################################################
//
//	CLASS : AtomDecorator
//
//################################################################################################

AtomDecorator::AtomDecorator( CComPtr<IMgaMetaPart> spPart, CComPtr<IMgaFCO> spFCO )
	: TypeableDecorator( spPart, spFCO )
{
}

void AtomDecorator::initialize( PreferenceMap& mapPrefs )
{
	mapPrefs[ PREF_ICONDEFAULT ] = PreferenceVariant( createResString( IDB_ATOM ) );
	mapPrefs[ PREF_TILESDEFAULT ] = PreferenceVariant( getFacilities().getTileVector( TILE_ATOMDEFAULT ) );
	mapPrefs[ PREF_TILESUNDEF ] = PreferenceVariant( getFacilities().getTileVector( TILE_ATOMDEFAULT ) );

	TypeableDecorator::initialize( mapPrefs );
}

void AtomDecorator::drawBackground( CDC* pDC ) const
{
	#ifndef OLD_DECORATOR_LOOKANDFEEL
		TypeableDecorator::drawBackground( pDC );
	#else
		if ( m_bActive )
			TypeableDecorator::drawBackground( pDC );
		else {
			CRect cRect = getBoxLocation();
			int iDepth = ( m_bReferenced ) ? 2 : 7;
			getFacilities().drawBox( pDC, cRect, COLOR_LIGHTGRAY, iDepth );
			getFacilities().drawRect( pDC, cRect, COLOR_GRAY );
			cRect.DeflateRect( iDepth, iDepth );
			getFacilities().drawRect( pDC, cRect, COLOR_GRAY );
		}
	#endif
}

//################################################################################################
//
//	CLASS : SetDecorator
//
//################################################################################################

SetDecorator::SetDecorator( CComPtr<IMgaMetaPart> spPart, CComPtr<IMgaFCO> spFCO )
	: TypeableDecorator( spPart, spFCO )
{
}

void SetDecorator::initialize( PreferenceMap& mapPrefs )
{
	mapPrefs[ PREF_ICONDEFAULT ] = PreferenceVariant( createResString( IDB_SET ) );
	mapPrefs[ PREF_TILESDEFAULT ] = PreferenceVariant( getFacilities().getTileVector( TILE_ATOMDEFAULT ) );
	mapPrefs[ PREF_TILESUNDEF ] = PreferenceVariant( getFacilities().getTileVector( TILE_ATOMDEFAULT ) );

	TypeableDecorator::initialize( mapPrefs );
}

void SetDecorator::drawBackground( CDC* pDC ) const
{
	#ifndef OLD_DECORATOR_LOOKANDFEEL
		TypeableDecorator::drawBackground( pDC );
	#else
		if ( m_bActive )
			TypeableDecorator::drawBackground( pDC );
		else {
			CRect cRect = getBoxLocation();
			int iDepth = ( m_bReferenced ) ? 2 : 5;
			getFacilities().drawBox( pDC, cRect, COLOR_LIGHTGRAY, iDepth );
			getFacilities().drawRect( pDC, cRect, COLOR_GRAY );
			if ( m_bReferenced ) {
				cRect.DeflateRect( iDepth, iDepth );
				getFacilities().drawRect( pDC, cRect, COLOR_GRAY );
			}
		}
	#endif
}

//################################################################################################
//
//	CLASS : ModelDecorator
//
//################################################################################################

ModelDecorator::ModelDecorator( CComPtr<IMgaMetaPart> spPart, CComPtr<IMgaFCO> spFCO )
	: TypeableDecorator( spPart, spFCO ), m_iMaxPortTextLength( MAX_PORT_LENGTH ), m_crPortText( COLOR_BLACK )
	, m_bPrtLabInside( true), m_iLongestPortTextLength( 0)
{
}

void ModelDecorator::initialize( PreferenceMap& mapPrefs )
{
	mapPrefs[ PREF_ICONDEFAULT ] = PreferenceVariant( createResString( IDB_MODEL ) );
	mapPrefs[ PREF_TILESDEFAULT ] = PreferenceVariant( getFacilities().getTileVector( TILE_MODELDEFAULT ) );
	mapPrefs[ PREF_TILESUNDEF ] = PreferenceVariant( getFacilities().getTileVector( TILE_PORTDEFAULT ) );

	if ( m_spFCO ) {
		PreferenceMap::iterator it = mapPrefs.find( PREF_PORTLABELCOLOR );
		if ( it != mapPrefs.end() )
			m_crPortText = it->second.uValue.crValue;
		else
			getFacilities().getPreference( m_spFCO, PREF_PORTLABELCOLOR, m_crPortText );

		it = mapPrefs.find( PREF_PORTLABELINSIDE );
		if ( it != mapPrefs.end() )
			m_bPrtLabInside = it->second.uValue.bValue;
		else
			getFacilities().getPreference( m_spFCO, PREF_PORTLABELINSIDE, m_bPrtLabInside );

		long o = m_iMaxPortTextLength ;
		it = mapPrefs.find( PREF_PORTLABELLENGTH );
		if ( it != mapPrefs.end() )
			m_iMaxPortTextLength = it->second.uValue.lValue;
		else
		{
			if( getFacilities().getPreference( m_spFCO, PREF_PORTLABELLENGTH, m_iMaxPortTextLength ))
				m_iMaxPortTextLength = abs( m_iMaxPortTextLength);//convert any negative value to positive
			else //if not found in registry
				m_iMaxPortTextLength = MAX_PORT_LENGTH; // the default value in Preferences
		}
		if( m_iMaxPortTextLength == 0) //if 0 it means it has to show all way long
			m_iMaxPortTextLength = 999; // so we set a huge value

		it = mapPrefs.find( PREF_BORDERCOLOR );
		if ( it != mapPrefs.end() )
			m_crBorder = it->second.uValue.crValue;
		else
			getFacilities().getPreference( m_spFCO, PREF_BORDERCOLOR, m_crBorder );

		loadPorts();
	}

	TypeableDecorator::initialize( mapPrefs );

	if ( m_vecLeftPorts.empty() && m_vecRightPorts.empty() )
		m_pTileVector = getFacilities().getTileVector( TILE_ATOMDEFAULT );
}

ModelDecorator::~ModelDecorator()
{
	for ( unsigned int i = 0 ; i < m_vecLeftPorts.size() ; i++ )
		delete m_vecLeftPorts[ i ];
	for ( unsigned int i = 0 ; i < m_vecRightPorts.size() ; i++ )
		delete m_vecRightPorts[ i ];
}

void ModelDecorator::loadPorts()
{
	CComPtr<IMgaMetaAspect>	spParentAspect;
	COMTHROW( m_spPart->get_ParentAspect( &spParentAspect ) );

	CComQIPtr<IMgaModel> spModel = m_spFCO;
	CComPtr<IMgaMetaFCO> spMetaFCO;
	COMTHROW( spModel->get_Meta( &spMetaFCO ) );
	CComQIPtr<IMgaMetaModel> spMetaModel = spMetaFCO;

	CComBSTR bstrAspect;
	COMTHROW( m_spPart->get_KindAspect( &bstrAspect ) );
	if ( bstrAspect.Length() == 0 ) {
		bstrAspect.Empty();
		COMTHROW( spParentAspect->get_Name( &bstrAspect ) );
	}
	
	HRESULT hr = spMetaModel->get_AspectByName( bstrAspect, &m_spAspect );
	
	if ( hr == E_NOTFOUND) {
		try {
			// PETER: If the proper aspect cannot be found, use the first one			
			m_spAspect = NULL;
			CComPtr<IMgaMetaAspects> spAspects;
			COMTHROW(spMetaModel->get_Aspects(&spAspects));
			ASSERT(spAspects);
			long nAspects = 0;
			COMTHROW(spAspects->get_Count(&nAspects));
			if (nAspects > 0) {
				COMTHROW(spAspects->get_Item(1, &m_spAspect));
			}
		}
		catch ( hresult_exception& ) {
		}
	}

	if ( m_spAspect ) {

		std::vector<PortDecorator*>	vecPorts;

		CComPtr<IMgaFCOs> spFCOs;
		COMTHROW( spModel->get_ChildFCOs( &spFCOs ) );
		MGACOLL_ITERATE( IMgaFCO, spFCOs ) {
			CComPtr<IMgaPart> spPart;
			if( S_OK == MGACOLL_ITER->get_Part( m_spAspect, &spPart ))
			{
			if ( spPart ) {
				CComPtr<IMgaMetaPart> spMetaPart;
				COMTHROW( spPart->get_Meta( &spMetaPart ) );
				VARIANT_BOOL vbLinked;
				COMTHROW( spMetaPart->get_IsLinked( &vbLinked ) );
				if ( vbLinked ) {
					long lX = 0;
					long lY = 0;
					//COMTHROW( spPart->GetGmeAttrs( 0, &lX, &lY ) );
					// zolmol, in case regnodes are not present or invalid will throw otherwise
					if( S_OK != spPart->GetGmeAttrs( 0, &lX, &lY ))
						ASSERT(0);
					vecPorts.push_back( new PortDecorator( MGACOLL_ITER, CPoint( lX, lY ) ) );
				}
				else
					COMTHROW( MGACOLL_ITER->Close() );
			}
			else
				COMTHROW( MGACOLL_ITER->Close() );
			}
		} MGACOLL_ITERATE_END;

		orderPorts( vecPorts );
	}
}

void ModelDecorator::orderPorts( std::vector<PortDecorator*>& vecPorts )
{
	long lMin = 100000000;
	long lMax = 0;

	for ( unsigned int i = 0 ; i < vecPorts.size() ; i++ ) {
		lMin = min( lMin, vecPorts[ i ]->getInnerPosition().x );
		lMax = max( lMax, vecPorts[ i ]->getInnerPosition().x );
	}

	for ( unsigned int i = 0 ; i < vecPorts.size() ; i++ ) {
		PreferenceMap mapPrefs;
		mapPrefs[ PREF_LABELCOLOR ] = PreferenceVariant( m_crPortText );
		mapPrefs[ PREF_LABELLENGTH ] = PreferenceVariant( (long) m_iMaxPortTextLength );
		mapPrefs[PREF_PORTLABELINSIDE] = PreferenceVariant( m_bPrtLabInside );

		if ( vecPorts[ i ]->getInnerPosition().x <= WIDTH_MODELSIDE || vecPorts[ i ]->getInnerPosition().x < lMax / 2 ) {
			mapPrefs[ PREF_LABELLOCATION ] = PreferenceVariant( m_bPrtLabInside? L_EAST : L_WEST);
			m_vecLeftPorts.push_back( vecPorts[ i ] );
		}
		else {
			mapPrefs[ PREF_LABELLOCATION ] = PreferenceVariant( m_bPrtLabInside? L_WEST: L_EAST);
			m_vecRightPorts.push_back( vecPorts[ i ] );
		}

		vecPorts[ i ]->initialize( mapPrefs );
		long k = vecPorts[ i ]->getLongest();
		if ( m_iLongestPortTextLength < k)
			m_iLongestPortTextLength = k;
	}

	std::sort( m_vecLeftPorts.begin(), m_vecLeftPorts.end(), PortLess() );
	std::sort( m_vecRightPorts.begin(), m_vecRightPorts.end(), PortLess() );
}

CSize ModelDecorator::getPreferredSize() const
{
	if ( m_vecLeftPorts.empty() && m_vecRightPorts.empty() )
		return ( ! m_pBitmap || m_pBitmap->getName() == createResString( IDB_MODEL ) ) ? CSize( WIDTH_MODEL, HEIGHT_MODEL ) : TypeableDecorator::getPreferredSize();

	LOGFONT logFont;
	getFacilities().getFont( FONT_PORT )->pFont->GetLogFont( &logFont );
	long lWidth = 0;
	if (m_bPrtLabInside )
	{
		ASSERT( m_iLongestPortTextLength >= 0 && m_iLongestPortTextLength <= 1000);
		ASSERT( m_iMaxPortTextLength >= 0 && m_iMaxPortTextLength <= 1000);
		ASSERT( m_iMaxPortTextLength); // m_iMaxPortTextLength > 0 !!! since 
		long lw = min(m_iMaxPortTextLength, m_iLongestPortTextLength);
		lWidth = ( 24 + 5 * (lw-3) + GAP_LABEL + WIDTH_PORT + GAP_XMODELPORT ) * 2 + GAP_PORTLABEL;
	}
	else
		lWidth = ( 8*3 + GAP_LABEL + WIDTH_PORT + GAP_XMODELPORT ) * 2 + GAP_PORTLABEL;

	long lHeight = GAP_YMODELPORT * 2 + max( m_vecLeftPorts.size(), m_vecRightPorts.size() ) * ( HEIGHT_PORT + GAP_PORT ) - GAP_PORT;

	return CSize( max( (long) WIDTH_MODEL, lWidth ), max( (long) HEIGHT_MODEL, lHeight ) );
}

void ModelDecorator::setBoxLocation( const CRect& cRect )
{
	TypeableDecorator::setBoxLocation( cRect );
	long lY = ( m_Rect.Height() - m_vecLeftPorts.size() * ( HEIGHT_PORT + GAP_PORT ) + GAP_PORT ) / 2;
	for ( unsigned int i = 0 ; i < m_vecLeftPorts.size() ; i++ ) {
		m_vecLeftPorts[ i ]->setBoxLocation( CRect( GAP_XMODELPORT, lY, GAP_XMODELPORT + WIDTH_PORT, lY + HEIGHT_PORT ) );
		lY += HEIGHT_PORT + GAP_PORT;
	}
	lY = ( m_Rect.Height() - m_vecRightPorts.size() * ( HEIGHT_PORT + GAP_PORT ) + GAP_PORT ) / 2;
	for ( unsigned int i = 0 ; i < m_vecRightPorts.size() ; i++ ) {
		m_vecRightPorts[ i ]->setBoxLocation( CRect( cRect.Width() - GAP_XMODELPORT - WIDTH_PORT, lY, cRect.Width() - GAP_XMODELPORT, lY + HEIGHT_PORT ) );
		lY += HEIGHT_PORT + GAP_PORT;
	}
}

void ModelDecorator::setActive( bool bActive )
{
	TypeableDecorator::setActive( bActive );
	for ( unsigned int i = 0 ; i < m_vecLeftPorts.size() ; i++ )
		m_vecLeftPorts[ i ]->setActive( bActive );
	for ( unsigned int i = 0 ; i < m_vecRightPorts.size() ; i++ )
		m_vecRightPorts[ i ]->setActive( bActive );
}

std::vector<PortDecorator*> ModelDecorator::getPorts() const
{
	std::vector<PortDecorator*> vecPorts( m_vecLeftPorts );
	for ( unsigned int i = 0 ; i < m_vecRightPorts.size() ; i++ )
			vecPorts.push_back( m_vecRightPorts[ i ] );
	return vecPorts;
}

PortDecorator* ModelDecorator::getPort( CComPtr<IMgaFCO> spFCO ) const
{
	for ( unsigned int i = 0 ; i < m_vecLeftPorts.size() ; i++ )
		if ( m_vecLeftPorts[ i ]->getFCO() == spFCO )
			return m_vecLeftPorts[ i ];
	for ( unsigned int i = 0 ; i < m_vecRightPorts.size() ; i++ )
		if ( m_vecRightPorts[ i ]->getFCO() == spFCO )
			return m_vecRightPorts[ i ];
	return NULL;
}

void ModelDecorator::drawBackground( CDC* pDC ) const
{
	CSize cExtentD = pDC->GetViewportExt();
	CSize cExtentL = pDC->GetWindowExt();
	CRect cRect = getBoxLocation();
	cRect.BottomRight() -= CPoint( 1, 1 );

	#ifndef OLD_DECORATOR_LOOKANDFEEL
		TypeableDecorator::drawBackground( pDC );
	#else
		if ( m_pBitmap->getName() != createResString( IDB_MODEL ) && m_bActive )
			TypeableDecorator::drawBackground( pDC );
		else {
			int iDepth = ( m_bReferenced ) ? 2 : ( ( m_iTypeInfo == 3 ) ? 4 : 7 );
			getFacilities().drawBox( pDC, cRect, ( ! m_bActive ) ? COLOR_LIGHTGRAY : ( m_bOverlay ) ? m_crOverlay : COLOR_GRAY, iDepth );
			CRect cRect2 = cRect;
			cRect2.InflateRect( 1, 1 );
			getFacilities().drawRect( pDC, cRect2, ( m_bActive ) ? m_crBorder : COLOR_GRAY );
			/* Commented out // inner border for Types, and Referenced models // Requested by Akos
			if ( m_iTypeInfo != 3 || m_bReferenced ) {
				cRect2 = cRect;
				cRect2.DeflateRect( iDepth, iDepth );
				getFacilities().drawRect( pDC, cRect2, ( m_bActive ) ? m_crBorder : COLOR_GRAY );
			}
			*/
		}
	#endif

	cRect.BottomRight() += CPoint( 1, 1 );
	CPoint ptOrigin = pDC->OffsetViewportOrg( (long) ( cRect.left * ( (double) cExtentD.cx / cExtentL.cx ) ), (long) ( cRect.top * ( (double) cExtentD.cy / cExtentL.cy ) ) );
	for ( unsigned int i = 0 ; i < m_vecLeftPorts.size() ; i++ )
		m_vecLeftPorts[ i ]->draw( pDC );
	for ( unsigned int i = 0 ; i < m_vecRightPorts.size() ; i++ )
		m_vecRightPorts[ i ]->draw( pDC );
	pDC->SetViewportOrg( ptOrigin );
}

//################################################################################################
//
//	CLASS : ReferenceDecorator
//
//################################################################################################

ReferenceDecorator::ReferenceDecorator( CComPtr<IMgaMetaPart> spPart, CComPtr<IMgaFCO> spFCO )
	: TypeableDecorator( spPart, spFCO ), m_pReferenced( NULL ), m_bIconRequired( false )
{
}

void ReferenceDecorator::initialize( PreferenceMap& mapPrefs )
{
	bool model_ref = false;
	if ( m_spFCO ) {
		CComPtr<IMgaFCO> spReferenced;
		CComQIPtr<IMgaReference> spReference = m_spFCO;

		CComObjPtr<IMgaFCOs> visitedRefs;
		COMTHROW(visitedRefs.CoCreateInstance(L"Mga.MgaFCOs"));

		while ( spReference ) {
			spReferenced = NULL;

			long res;
			if ( (visitedRefs->Find(spReference, 1L, &res)) == E_NOTFOUND ) {
				COMTHROW( visitedRefs->Append( spReference ) );
				COMTHROW( spReference->get_Referred( &spReferenced ) );
			}

			spReference = spReferenced;
		}

		if ( spReferenced ) {
			objtype_enum eType;
			COMTHROW( spReferenced->get_ObjType( &eType ) );
			switch ( eType ) {
				case OBJTYPE_ATOM :
					m_pReferenced = new DecoratorSDK::AtomDecorator( m_spPart, spReferenced );
					break;
				case OBJTYPE_SET :
					m_pReferenced = new DecoratorSDK::SetDecorator( m_spPart, spReferenced );
					break;
				case OBJTYPE_MODEL :
					model_ref = true;
					m_pReferenced = new DecoratorSDK::ModelDecorator( m_spPart, spReferenced );
					break;
			}
		}
	}

	mapPrefs[ PREF_ICONDEFAULT ] = PreferenceVariant( createResString( IDB_REFERENCE ) );
	mapPrefs[ PREF_TILESDEFAULT ] = PreferenceVariant( getFacilities().getTileVector( TILE_ATOMDEFAULT ) );
	mapPrefs[ PREF_TILESUNDEF ] = PreferenceVariant( getFacilities().getTileVector( TILE_ATOMDEFAULT ) );
	mapPrefs[ PREF_TYPEINFOSHOWN ] = PreferenceVariant( false );
	mapPrefs[ PREF_TYPESHOWN ] = PreferenceVariant( false );

	TypeableDecorator::initialize( mapPrefs );

	if ( m_pReferenced ) {
		PreferenceMap mapRefPrefs;

		if ( m_bOverlay )
			mapRefPrefs[ PREF_OVERLAYCOLOR ] = PreferenceVariant( m_crOverlay );

		if ( m_pBitmap->getName() != createResString( IDB_REFERENCE ) ) {
			mapRefPrefs[ PREF_ICON ] = PreferenceVariant( m_pBitmap->getName() );
			m_lBorderWidth = 0;
			objtype_enum eType;
			COMTHROW( m_pReferenced->getFCO()->get_ObjType( &eType ) );
			mapRefPrefs[ PREF_TILES ] = PreferenceVariant( getFacilities().getTileVector( ( eType == OBJTYPE_MODEL ) ? TILE_PORTDEFAULT : TILE_ATOMDEFAULT ) );
		}
		else
			m_lBorderWidth = 2;

		mapRefPrefs[ PREF_TYPESHOWN ] = PreferenceVariant( false );

		COLORREF crPortLabel;
		if ( getFacilities().getPreference( m_spFCO, PREF_PORTLABELCOLOR, crPortLabel ) )
			mapRefPrefs[ PREF_PORTLABELCOLOR ] = PreferenceVariant( crPortLabel );

		if ( getFacilities().getPreference( m_spFCO, PREF_BORDERCOLOR, m_crBorder ) )
			mapRefPrefs[ PREF_BORDERCOLOR ] = PreferenceVariant( m_crBorder );
		else
			getFacilities().getPreference( m_pReferenced->getFCO(), PREF_BORDERCOLOR, m_crBorder );

		if( m_spFCO && model_ref)
		{
			// these values will be get from the old PrefMap: mapPrefs or from the m_spFCO's registry (most likely)
			bool port_lab_inside;
			long port_lab_len;

			PreferenceMap::iterator it;
			it = mapPrefs.find( PREF_PORTLABELINSIDE );
			if ( it != mapPrefs.end() ) // the mapRefs map is not expected to contain the value
				port_lab_inside = it->second.uValue.bValue;
			else // the object's registry may contain it
				getFacilities().getPreference( m_spFCO, PREF_PORTLABELINSIDE, port_lab_inside );

			it = mapPrefs.find( PREF_PORTLABELLENGTH );
			if ( it != mapPrefs.end() )
				port_lab_len = it->second.uValue.lValue;
			else
			{
				// if not found in registry use MAX_PORT_LENGTH
				if( !getFacilities().getPreference( m_spFCO, PREF_PORTLABELLENGTH, port_lab_len ))
					port_lab_len = MAX_PORT_LENGTH; // the default value in Preferences
			}

			ASSERT ( port_lab_len >= 0 && port_lab_len <= 1000);

			// store the values in the new map: mapRefPrefs
			mapRefPrefs[ PREF_PORTLABELINSIDE ] = PreferenceVariant( port_lab_inside );
			mapRefPrefs[ PREF_PORTLABELLENGTH ] = PreferenceVariant( (long) port_lab_len );
		}
		mapRefPrefs[ PREF_VIOLATED ] = PreferenceVariant( false );

		m_pReferenced->initialize( mapRefPrefs );
		m_pReferenced->setReferenced();
	}
	else {
		m_lBorderWidth = 0;
		CString strIcon;
		if ( m_spFCO ) {
			getFacilities().getPreference( m_spFCO, PREF_NULLREFICON, strIcon );
		}
		else {
			CComPtr<IMgaMetaRole> spRole;
			COMTHROW( m_spPart->get_Role( &spRole ) );
			CComPtr<IMgaMetaFCO> spMetaFCO;
			COMTHROW( spRole->get_Kind( &spMetaFCO ) );
			getFacilities().getPreference( spMetaFCO, PREF_NULLREFICON, strIcon );
		}
		if ( ! strIcon.IsEmpty() ) {
			BitmapBase* pBitmap = NULL;
			#ifndef OLD_DECORATOR_LOOKANDFEEL
				pBitmap = ( m_bOverlay ) ? getFacilities().getBitmapB( strIcon, m_crOverlay ) : getFacilities().getBitmap( strIcon );
			#else
				pBitmap = getFacilities().getBitmap( strIcon );
			#endif
			if ( pBitmap )
				m_pBitmap = pBitmap;
		}
	}

	// m_bIconRequired = m_spFCO && m_pReferenced && ! m_pBitmap->hasBackgroundColor() && m_pBitmap->getName() == createResString( IDB_REFERENCE );
	m_bIconRequired = true;
}

ReferenceDecorator::~ReferenceDecorator()
{
	if ( m_pReferenced )
		delete m_pReferenced;
}

CSize ReferenceDecorator::getPreferredSize() const
{
	if ( m_pReferenced )
		return m_pReferenced->getPreferredSize() + CSize( m_lBorderWidth * 2, m_lBorderWidth * 2 );
	return TypeableDecorator::getPreferredSize();
}

void ReferenceDecorator::setBoxLocation( const CRect& cRect )
{
	TypeableDecorator::setBoxLocation( cRect );
	if ( m_pReferenced ) {
		CRect cRect2 = m_Rect;
		cRect2.DeflateRect( m_lBorderWidth, m_lBorderWidth );
		m_pReferenced->setBoxLocation( cRect2 );
	}
}

void ReferenceDecorator::setActive( bool bActive )
{
	TypeableDecorator::setActive( bActive );
	if ( m_pReferenced )
		m_pReferenced->setActive( bActive );
}

DecoratorBase* ReferenceDecorator::getReferenced() const
{
	return m_pReferenced;
}

void ReferenceDecorator::drawBackground( CDC* pDC ) const
{
	if ( m_pReferenced )
		m_pReferenced->drawBackground( pDC );
	else {
		#ifndef OLD_DECORATOR_LOOKANDFEEL
			TypeableDecorator::drawBackground( pDC );
		#else
			if ( m_bActive )
				TypeableDecorator::drawBackground( pDC );
			else {
				CRect cRect = getBoxLocation();
				int iDepth = 2;
				getFacilities().drawBox( pDC, cRect, COLOR_LIGHTGRAY, iDepth );
				getFacilities().drawRect( pDC, cRect, COLOR_GRAY );
				cRect.DeflateRect( iDepth, iDepth );
				getFacilities().drawRect( pDC, cRect, COLOR_GRAY );
			}
		#endif
	}
}

void ReferenceDecorator::drawIcons( CDC* pDC ) const
{
	if ( m_pReferenced )
		m_pReferenced->drawIcons( pDC );
	else
		TypeableDecorator::drawIcons( pDC );

	 if ( false /*m_bIconRequired*/ ) {
		BitmapBase* pBitmap = getFacilities().getBitmap( createResString( ( m_bActive ) ? IDB_ICON_REFERENCE : IDB_ICON_REFERENCE_DIS ) );
		CRect cRect = getBoxLocation();
		cRect.left += GAP_LABEL;
		cRect.top += GAP_LABEL;
		cRect.right = cRect.left + pBitmap->getWidth();
		cRect.bottom = cRect.top + pBitmap->getHeight();
		pBitmap->draw( NULL, pDC, cRect, TileVector( 1, BackgroundTile() ) );
	}
}

}; // namespace DecoratorSDK