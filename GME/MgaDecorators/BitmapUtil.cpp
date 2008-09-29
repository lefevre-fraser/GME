//################################################################################################
//
// Mga Decorator Base
//	BitmapUtil.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "BitmapUtil.h"

#include "DecoratorUtil.h"
#include "resource.h"
#include "DecoratorDefs.h"

namespace Decorator
{

//################################################################################################
//
// CLASS : RefCoord
//
//################################################################################################

RefCoord::RefCoord()
	: m_eType( CRP_BEGIN ), m_lPos( 0 )
{
}

RefCoord::RefCoord( ECoordRefPoint eType, long lPos )
	: m_eType( eType ), m_lPos( lPos )
{
}

RefCoord::RefCoord( const RefCoord& rc )
	: m_eType( rc.m_eType ), m_lPos( rc.m_lPos )
{
}

RefCoord& RefCoord::operator=( const RefCoord& rc )
{
	if ( this != &rc ) {
		m_eType = rc.m_eType;
		m_lPos = rc.m_lPos;
	}
	return *this;
}

long RefCoord::getPos() const
{
	return m_lPos;
}

ECoordRefPoint RefCoord::getRef() const
{
	return m_eType;
}

long RefCoord::calcPos( long lLength )
{
	long lResult = 0;
	switch ( m_eType ) {
		case CRP_BEGIN :
			lResult = m_lPos;
			break;
		case CRP_END :
			lResult = lLength - m_lPos;
			break;
		case CRP_CENTER :
			lResult = lLength / 2 + m_lPos;
			break;
	}
	lResult = ( lResult < 0 ) ? 0 : lResult;
	return ( lResult > lLength ) ? lLength : lResult;
}


//################################################################################################
//
// CLASS : RefPoint
//
//################################################################################################

RefPoint::RefPoint()
{
}

RefPoint::RefPoint( const RefCoord& rcX, const RefCoord& rcY )
	: m_rcX( rcX ), m_rcY( rcY )
{
}

RefPoint::RefPoint( const RefPoint& rp )
	: m_rcX( rp.m_rcX ), m_rcY( rp.m_rcY )
{
}

RefPoint& RefPoint::operator=( const RefPoint rp )
{
	if ( this != &rp ) {
		m_rcX = rp.m_rcX;
		m_rcY = rp.m_rcY;
	}
	return *this;
}

RefCoord RefPoint::getX() const
{
	return m_rcX;
}

RefCoord RefPoint::getY() const
{
	return m_rcY;
}

CPoint RefPoint::calcPoint( long lWidth, long lHeight )
{
	return CPoint( m_rcX.calcPos( lWidth ), m_rcY.calcPos( lHeight ) );
}

//################################################################################################
//
// CLASS : BitmapBase
//
//################################################################################################

BitmapBase::BitmapBase( const CString& strName )
	: m_lWidth( 0 ), m_lHeight( 0 ), m_bHasTransparentColor( false ),
	m_crTransparentColor( 0x0 ), m_bHasBackgroundColor( false ), m_crBackgroundColor( 0x0 )
{
	setName( strName );
}

BitmapBase::BitmapBase( const CString& strName, COLORREF crColor, bool bIsTransparent )
	: m_lWidth( 0 ), m_lHeight( 0 ), m_bHasTransparentColor( bIsTransparent ),
	m_crTransparentColor( ( bIsTransparent ) ? crColor : 0x0 ), m_bHasBackgroundColor( ! bIsTransparent), m_crBackgroundColor( ( ! bIsTransparent ) ? crColor : 0x0  )
{
	setName( strName );
}

BitmapBase::BitmapBase( const CString& strName, COLORREF crTransparentColor, COLORREF crBackgroundColor )
	: m_lWidth( 0 ), m_lHeight( 0 ), m_bHasTransparentColor( true ),
	m_crTransparentColor( ( crTransparentColor ) ), m_bHasBackgroundColor( true ), m_crBackgroundColor( crBackgroundColor )
{
	setName( strName );
}

BitmapBase::~BitmapBase()
{
}

void BitmapBase::setName( const CString& strName )
{
	int iPos = strName.ReverseFind( '\\' );
	int iPos2 = strName.ReverseFind( '/' );
	iPos = max( iPos, iPos2 );
	m_strName = ( iPos == -1 ) ? strName : strName.Right( strName.GetLength() - iPos - 1 );
}

CString BitmapBase::getName() const
{
	return m_strName;
}

long BitmapBase::getWidth() const
{
	return m_lWidth;
}

long BitmapBase::getHeight() const
{
	return m_lHeight;
}

bool BitmapBase::hasTransparentColor() const
{
	return m_bHasTransparentColor;
}

bool BitmapBase::hasBackgroundColor() const
{
	return m_bHasBackgroundColor;
}

COLORREF BitmapBase::getTransparentColor() const
{
	return m_crTransparentColor;
}

COLORREF BitmapBase::getBackgroundColor() const
{
	return m_crBackgroundColor;
}

void BitmapBase::setSize( long lWidth, long lHeight )
{
	m_lWidth = lWidth;
	m_lHeight = lHeight;
}

void BitmapBase::draw( CDC* pDC, const CRect& cRect, const TileVector& vecTiles ) const
{
	for ( unsigned long i = 0 ; i < vecTiles.size() ; i++ ) {

		CPoint srcTopLeft = vecTiles[ i ].getPartTopLeft().calcPoint( m_lWidth, m_lHeight );
		CPoint srcBottomRight = vecTiles[ i ].getPartBottomRight().calcPoint( m_lWidth, m_lHeight );
		long lSrcWidth = srcBottomRight.x - srcTopLeft.x;
		long lSrcHeight = srcBottomRight.y - srcTopLeft.y;

		CPoint dstTopLeft = vecTiles[ i ].getTopLeft().calcPoint( cRect.Width(), cRect.Height() ) + cRect.TopLeft();
		CPoint dstBottomRight = vecTiles[ i ].getBottomRight().calcPoint( cRect.Width(), cRect.Height() ) + cRect.TopLeft();
		long lDstWidth = dstBottomRight.x - dstTopLeft.x;
		long lDstHeight = dstBottomRight.y - dstTopLeft.y;

		long lHNumber = 1;
		long lHMod = 0;
		if ( vecTiles[ i ].getHorizontalFill() == FT_TILE ) {
			lHMod = lDstWidth % lSrcWidth;
			lHNumber = lDstWidth / lSrcWidth + ( ( ! lHMod ) ? 0 : 1 );
		}

		long lVNumber = 1;
		long lVMod = 0;
		if ( vecTiles[ i ].getVerticalFill() == FT_TILE ) {
			lVMod = lDstHeight % lSrcHeight;
			lVNumber = lDstHeight / lSrcHeight + ( ( ! lVMod ) ? 0 : 1 );
		}

		for ( long h = 0 ; h < lHNumber ; h++ ) {

			long lSrcRight = srcBottomRight.x;
			long lDstLeft = dstTopLeft.x;
			long lDstRight = 0;
			switch ( vecTiles[ i ].getHorizontalFill() ) {
				case FT_NONE :
					lDstRight = dstTopLeft.x + lSrcWidth;
					break;
				case FT_STRETCH :
					lDstRight = dstBottomRight.x;
					break;
				case FT_TILE :
					if ( h == lHNumber - 1 && ! lHMod )
						lSrcRight = srcTopLeft.x + lHMod;
					lDstLeft += h * lSrcWidth;
					lDstRight = ( h == lHNumber - 1 && ! lHMod ) ? dstBottomRight.x : lDstLeft + lSrcWidth;
					break;
			}

			for ( long v = 0 ; v < lVNumber ; v++ ) {

				long lSrcBottom = srcBottomRight.y;
				long lDstTop = dstTopLeft.y;
				long lDstBottom = 0;
				switch ( vecTiles[ i ].getVerticalFill() ) {
					case FT_NONE :
						lDstBottom = dstTopLeft.y + lSrcHeight;
						break;
					case FT_STRETCH :
						lDstBottom = dstBottomRight.y;
						break;
					case FT_TILE :
						if ( v == lVNumber - 1 && ! lVMod )
							lSrcBottom = srcTopLeft.y + lVMod;
						lDstTop += v * lSrcHeight;
						lDstBottom = ( v == lVNumber - 1 && ! lVMod ) ? dstBottomRight.y : lDstTop + lSrcHeight;
						break;
				}

				draw( pDC, CRect( srcTopLeft.x, srcTopLeft.y, lSrcRight, lSrcBottom ), CRect( lDstLeft, lDstTop, lDstRight, lDstBottom ), SRCCOPY );
			}
		}
	}
	if ( m_bHasBackgroundColor ) {
		CDC dcMemory;
		dcMemory.CreateCompatibleDC( pDC );
		CBitmap bmp;
		 bmp.CreateCompatibleBitmap( pDC, cRect.Width(), cRect.Height() );
		dcMemory.SelectObject( &bmp );
		dcMemory.FillSolidRect( CRect( 0, 0, cRect.Width(), cRect.Height() ), m_crBackgroundColor );
		CPen pen;
		pen.CreatePen( PS_SOLID, 6, m_crBackgroundColor );
		dcMemory.SelectObject( &pen );
		dcMemory.MoveTo( 0 , 0 );
		dcMemory.LineTo( 60, 60 );
		pDC->StretchBlt( cRect.left, cRect.top, cRect.Width(), cRect.Height(), &dcMemory, 0, 0, cRect.Width(), cRect.Height(), SRCAND );
	}
}


//################################################################################################
//
// CLASS : BitmapDIB
//
//################################################################################################

BitmapDIB::BitmapDIB( const CString& strName )
	: BitmapBase( strName ), m_hDIB( NULL )
{
	load( strName );
}

BitmapDIB::BitmapDIB( const CString& strName, COLORREF crColor, bool bIsTransparent )
	: BitmapBase( strName , crColor, bIsTransparent ), m_hDIB( NULL )
{
	load( strName );
}

BitmapDIB::BitmapDIB( const CString& strName, COLORREF crTransparentColor, COLORREF crBackgroundColor )
	: BitmapBase( strName, crTransparentColor, crBackgroundColor ), m_hDIB( NULL )
{
	load( strName );
}

BitmapDIB::~BitmapDIB()
{
	if ( isInitialized() ) {
		::GlobalUnlock( (HGLOBAL) m_hDIB );
		::GlobalFree( (HGLOBAL) m_hDIB );
	}
}

void BitmapDIB::draw( CDC* pDC, const CRect& srcRect, const CRect& dstRect, DWORD dwOpCode ) const
{
	if ( isInitialized() ) {
		CRect srcRectCopy = srcRect;
		CRect dstRectCopy = dstRect;
		::PaintDIB( pDC->m_hDC, &dstRectCopy, m_hDIB, &srcRectCopy, NULL );
	}
}

void BitmapDIB::load( const CString& strName )
{
	if ( ! m_hDIB ) {
		if ( ! getFacilities().arePathesValid() )
			return;
		std::vector<CString> vecPathes = getFacilities().getPathes();

		CString strFName = strName;

		CFile fDIB;
		CFileException fexDIB;
		for ( unsigned int i = 0 ; i < vecPathes.size() ; i++ ) {
			if ( fDIB.Open( vecPathes[ i ] + strFName, CFile::modeRead | CFile::shareDenyWrite, &fexDIB ) ) {
				TRY {
					m_hDIB = ::ReadDIBFile( fDIB );
					fDIB.Close();
					if ( m_hDIB ) {
						LPSTR lpDIB = (LPSTR) ::GlobalLock( (HGLOBAL) m_hDIB );
						setSize( ::DIBWidth( lpDIB ), ::DIBHeight( lpDIB) );
						::GlobalUnlock( (HGLOBAL) m_hDIB );
						return;
					}
				}
				CATCH (CFileException, eLoad) {
					fDIB.Abort();
					m_hDIB = NULL;
					AfxMessageBox( "Error Reading Bitmap File: " + vecPathes[ i ] + strFName, MB_OK | MB_ICONSTOP );
					return;
				} END_CATCH
			}
		}
	}
}

bool BitmapDIB::isInitialized() const
{
	return m_hDIB != NULL;
}

//################################################################################################
//
// CLASS : BitmapGen
//
//################################################################################################


BitmapGen::BitmapGen( const CString& strName )
	: BitmapBase( strName ), m_pImage( NULL )
{
	load( strName );
}

BitmapGen::BitmapGen( const CString& strName, COLORREF crColor, bool bIsTransparent )
	: BitmapBase( strName, crColor, bIsTransparent ), m_pImage( NULL )
{
	load( strName );
}

BitmapGen::BitmapGen( const CString& strName, COLORREF crTransparentColor, COLORREF crBackgroundColor )
	: BitmapBase( strName, crTransparentColor, crBackgroundColor ), m_pImage( NULL )
{
	load( strName );
}
BitmapGen::~BitmapGen()
{
	if( m_pImage) 
	{
		delete m_pImage;
		m_pImage = NULL;
	}
}

void BitmapGen::draw( CDC* pDC, const CRect& srcRect, const CRect& dstRect, DWORD dwOpCode ) const
{
	ASSERT( m_pImage);
	Graphics graphics(pDC->m_hDC);
	graphics.SetPageUnit( UnitPixel);
	Status st = graphics.DrawImage(m_pImage, dstRect.left, dstRect.top, dstRect.Width(), dstRect.Height());
	if( st == Win32Error) // in case of corrupted image file (although successfully loaded)
		graphics.FillRectangle( &SolidBrush(Color::Red), dstRect.left, dstRect.top, dstRect.Width(), dstRect.Height());
}

void BitmapGen::load( const CString& strName )
{
	if ( ! m_pImage ) {
		if ( ! getFacilities().arePathesValid() )
			return;
		std::vector<CString> vecPathes = getFacilities().getPathes();

		bool success = false;
		CString strFName = strName;

		for ( unsigned int i = 0 ; !success && i < vecPathes.size() ; i++ )
		{
			m_pImage = Image::FromFile( CA2W( (LPCTSTR) vecPathes[ i ] + strFName));
			if( m_pImage && m_pImage->GetLastStatus() == Ok)
			{
				ASSERT( m_pImage->GetWidth() > 0); // valid sizes, otherwise AutoRouter fails
				ASSERT( m_pImage->GetHeight() > 0); 
				setSize( m_pImage->GetWidth(), m_pImage->GetHeight() );
				success = true;
			}
		}

		if( !success && m_pImage)
		{
			delete m_pImage;
			m_pImage = NULL;
		}
	}
}

bool BitmapGen::isInitialized() const
{
	return m_pImage != NULL;
}

//################################################################################################
//
// CLASS : BitmapRES
//
//################################################################################################

BitmapRES::BitmapRES( UINT uiID  )
	: BitmapBase( createResString( uiID ) ), m_pBitmap( NULL )
{
	load( uiID );
}

BitmapRES::BitmapRES( UINT uiID, COLORREF crColor, bool bIsTransparent )
	: BitmapBase( createResString( uiID ), crColor, bIsTransparent ), m_pBitmap( NULL )
{
	load( uiID );
}

BitmapRES::BitmapRES( UINT uiID, COLORREF crTransparentColor, COLORREF crBackgroundColor )
	: BitmapBase( createResString( uiID ), crTransparentColor, crBackgroundColor ), m_pBitmap( NULL )
{
	load( uiID );
}

BitmapRES::~BitmapRES()
{
	delete m_pBitmap;
	m_pBitmap = NULL;
}

void BitmapRES::draw( CDC* pDC, const CRect& srcRect, const CRect& dstRect, DWORD dwOpCode ) const
{
	Graphics graphics(pDC->m_hDC);
	graphics.SetPageUnit( UnitPixel);
	graphics.DrawImage( m_pBitmap, dstRect.left, dstRect.top, dstRect.Width(), dstRect.Height());
}

void BitmapRES::load( UINT uiID )
{
	// create a GDI+ Bitmap from the resource
	m_pBitmap = new Bitmap( ::AfxGetInstanceHandle(), (WCHAR*) MAKEINTRESOURCE( uiID));
	if( !m_pBitmap) {
		m_pBitmap = NULL;
		return;
	}

	setSize( m_pBitmap->GetWidth(), m_pBitmap->GetHeight());
}

bool BitmapRES::isInitialized() const
{
	return m_pBitmap != NULL;
}

//################################################################################################
//
// CLASS : BackgroundTile
//
//################################################################################################

BackgroundTile::BackgroundTile()
	: m_rpPartTopLeft( RefPoint() ), m_rpPartBottomRight( RefPoint( RefCoord( CRP_END, 0 ), RefCoord( CRP_END, 0 ) ) ),
	m_rpTopLeft( RefPoint() ), m_rpBottomRight( RefPoint( RefCoord( CRP_END, 0 ), RefCoord( CRP_END, 0 ) ) ),
	m_eFillVertical( FT_NONE ), m_eFillHorizontal( FT_NONE )
{
}

BackgroundTile::BackgroundTile( const RefPoint& rpPTL, const RefPoint& rpPBR, const RefPoint& rpTL, const RefPoint& rpBR, EFillType eFH, EFillType eFV )
	: m_rpPartTopLeft( rpPTL ), m_rpPartBottomRight( rpPBR ), m_rpTopLeft( rpTL ), m_rpBottomRight( rpBR ), m_eFillVertical( eFV ), m_eFillHorizontal( eFH )
{
}

BackgroundTile::BackgroundTile( const BackgroundTile& bt )
	: m_rpPartTopLeft( bt.m_rpPartTopLeft ), m_rpPartBottomRight( bt.m_rpPartBottomRight ), m_rpTopLeft( bt.m_rpTopLeft ),
	m_rpBottomRight( bt.m_rpBottomRight ), m_eFillVertical( bt.m_eFillVertical ), m_eFillHorizontal( bt.m_eFillHorizontal )
{
}

BackgroundTile& BackgroundTile::operator=( const BackgroundTile& bt )
{
	if ( this != &bt ) {
		m_rpPartTopLeft = bt.m_rpPartTopLeft;
		m_rpPartBottomRight = bt.m_rpPartBottomRight;
		m_rpTopLeft = bt.m_rpTopLeft;
		m_rpBottomRight = bt.m_rpBottomRight;
		m_eFillVertical = bt.m_eFillVertical;
		m_eFillHorizontal = bt.m_eFillHorizontal;
	}
	return *this;
}

RefPoint BackgroundTile::getPartTopLeft() const
{
	return m_rpPartTopLeft;
}

RefPoint BackgroundTile::getPartBottomRight() const
{
	return m_rpPartBottomRight;
}

RefPoint BackgroundTile::getTopLeft() const
{
	return m_rpTopLeft;
}

RefPoint BackgroundTile::getBottomRight() const
{
	return m_rpBottomRight;
}

EFillType BackgroundTile::getHorizontalFill() const
{
	return m_eFillHorizontal;
}

EFillType BackgroundTile::getVerticalFill() const
{
	return m_eFillVertical;
}

}; // namespace Decorator