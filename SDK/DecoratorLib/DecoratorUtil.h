//################################################################################################
//
// Mga Decorator Base
//	DecoratorUtil.h
//
//################################################################################################

#ifndef DecoratorUtil_h
#define DecoratorUtil_h

#pragma warning( disable : 4786 )

#include "StdAfx.h"

#include <vector>
#include <map>

#include "mga.h"
#include "meta.h"

#include "DecoratorDefs.h"

namespace DecoratorSDK
{
	class BitmapBase;
	class Facilities;

	class BackgroundTile;
	typedef std::vector<BackgroundTile> TileVector;

	Facilities& getFacilities();

//################################################################################################
//
// CLASS : Facilities
//
//################################################################################################

	class Facilities
	{
		private :
			CComPtr<IMgaProject>			m_spProject;
			std::vector<CString> 			m_vecPathes;
			bool							m_bArePathesValid;
			CString							m_strParadigmPath;
			CString							m_strProjectPath;

			std::map<CString,BitmapBase*>	m_mapBitmaps;
			std::map<CString,TileVector*>	m_mapTileVectors;
			std::map<int,SFont*>			m_mapFonts;
			std::map<CString,CPen*>			m_mapPens;
			std::map<CString,CBrush*>		m_mapBrushes;

		public :
			Facilities();
			~Facilities();

			bool loadPathes( IMgaProject* pProject, bool bRefresh = false );
			bool arePathesValid() const;
			std::vector<CString> getPathes() const;

			BitmapBase* getBitmap( const CString& strName );
			BitmapBase* getBitmapT( const CString& strName, COLORREF crTransparent );
			BitmapBase* getBitmapB( const CString& strName, COLORREF crBackground );
			BitmapBase* getBitmapTB( const CString& strName, COLORREF crTransparent, COLORREF crBackground );
			BitmapBase* getMaskedBitmap( const CString& strName, COLORREF crTransparent, COLORREF crBackground );
			BitmapBase* getMaskedBitmap( UINT nResID, COLORREF crTransparent, COLORREF crBackground );

			void addTileVector( const CString& strName, TileVector* vecTiles );
			TileVector* getTileVector( const CString& strName ) const;

			void createFont( int iFontKey, const CString& strKind, int iBoldness, bool bItalics, int iSize );
			SFont* getFont( int iFontKey ) const;

			CPen* getPen( COLORREF crColor, int iWidth = 1, bool bDashed = false );
			CBrush* getBrush( COLORREF crColor );

			bool getPreference( CComPtr<IMgaFCO> spFCO, const CString& strName, CString& strValue ) const;
			bool getPreference( CComPtr<IMgaFCO> spFCO, const CString& strName, long& lValue, bool bInHexa = false ) const;
			bool getPreference( CComPtr<IMgaFCO> spFCO, const CString& strName, COLORREF& crValue ) const;
			bool getPreference( CComPtr<IMgaFCO> spFCO, const CString& strName, ELocation& eValue ) const;
			bool getPreference( CComPtr<IMgaFCO> spFCO, const CString& strName, bool& bValue ) const;
			bool getPreference( CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, CString& strValue ) const;
			bool getPreference( CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, long& lValue, bool bInHexa = false ) const;
			bool getPreference( CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, COLORREF& crValue ) const;
			bool getPreference( CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, ELocation& eValue ) const;
			bool getPreference( CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, bool& bValue ) const;

			EPrefStatus getPreferenceStatus( CComPtr<IMgaFCO> spFCO, const CString& strName ) const;

			void drawText( CDC* pDC, const CString& strText, const CPoint& cpTopLeft,  CFont* pFont, COLORREF crColor,
							int iAlign, int iLength = -1, const CString& strPre = "", const CString& strPost = "",
							bool bPeriods = true ) const;
			void drawCenteredText( CDC* pDC, const CString& strText, RECT r, CFont* pFont, COLORREF crColor ) const;
			void drawLeftText( CDC* pDC, const CString& strText, RECT r, CFont* pFont, COLORREF crColor ) const;
			void drawLeftMultiText( CDC* pDC, const CString& strText, RECT r, CFont* pFont, COLORREF crColor ) const;
			void drawRightText( CDC* pDC, const CString& strText, RECT r, CFont* pFont, COLORREF crColor ) const;
			void drawRect( CDC* pDC, const CRect& cRect, COLORREF crColor, int iWidth = 1 ) const;
			void drawBox( CDC* pDC, const CRect& cRect, COLORREF crColor, int iDepth ) const;
			void draw3DBox( CDC* pDC, const CRect& rect, int borderSize, COLORREF brColor, COLORREF modelColor,
							bool special = false);
			void draw3DBox( CDC* pDC, const CRect& rect, COLORREF brColor, COLORREF color, bool special = false);
			void drawFlatBox( CDC* pDC, const CRect& rect, COLORREF brColor, COLORREF color);
			COLORREF shiftColor( COLORREF crColor, int iShift ) const;
			COLORREF getDarkBorderColor(COLORREF color);
			COLORREF getLightBorderColor(COLORREF color);

			std::vector<CString> wrapString( const CString& str, int iWrap, int iMax );

		private :
			BitmapBase* getBitmap( const CString& strName, bool bhasTC, COLORREF crTC, bool bhasBC, COLORREF crBC,
								   bool masked = false, UINT nResID = 0 );

	};

}; // namespace DecoratorSDK

#endif // Decorator_h