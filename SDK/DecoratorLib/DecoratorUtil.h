//################################################################################################
//
// DecoratorLib Utility Facility
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
			CComPtr<IMgaProject>				m_spProject;
			std::vector<CString> 				m_vecPathes;
			bool								m_bArePathesValid;
			CString								m_strParadigmPath;
			CString								m_strProjectPath;

			std::map<CString,BitmapBase*>			m_mapBitmaps;
			std::map<CString,TileVector*>			m_mapTileVectors;
			std::map<int,SFont*>					m_mapFonts;
			std::map<int,GdipFont*>					m_mapGdipFonts;
			std::map<CString,CPen*>					m_mapPens;
			std::map<CString,CBrush*>				m_mapBrushes;
			std::map<CString,Gdiplus::Pen*>			m_mapGdipPens;
			std::map<CString,Gdiplus::SolidBrush*>	m_mapGdipBrushes;

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
			GdipFont* GetFont( int iFontKey ) const;
			Gdiplus::Pen* GetPen( COLORREF crColor, int iWidth = 1 );
			Gdiplus::SolidBrush* GetBrush( COLORREF crColor );

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
			bool getPreference( CComPtr<IMgaFCO> spFCO, CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, CString& strValue ) const;
			bool getPreference( CComPtr<IMgaFCO> spFCO, CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, long& lValue, bool bInHexa = false ) const;
			bool getPreference( CComPtr<IMgaFCO> spFCO, CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, COLORREF& crValue ) const;
			bool getPreference( CComPtr<IMgaFCO> spFCO, CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, ELocation& eValue ) const;
			bool getPreference( CComPtr<IMgaFCO> spFCO, CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, bool& bValue ) const;

			EPrefStatus getPreferenceStatus( CComPtr<IMgaFCO> spFCO, const CString& strName ) const;

			bool getAttribute( CComPtr<IMgaFCO> spFCO, const CString& strName, CString& strValue ) const;
			bool getAttribute( CComPtr<IMgaFCO> spFCO, const CString& strName, bool& bValue ) const;
			bool setAttribute( CComPtr<IMgaFCO> spFCO, const CString& strName, const CString& strValue ) const;
			bool setAttribute( CComPtr<IMgaFCO> spFCO, const CString& strName, bool bValue ) const;

			bool getMetaFCO(const CComPtr<IMgaMetaPart> &metaPart, CComPtr<IMgaMetaFCO> &metaFco) const;

			CSize MeasureText( Gdiplus::Graphics* gdip, GdipFont* pFont, const CString& strText);
			CSize MeasureText( Gdiplus::Graphics* gdip, Gdiplus::Font* pFont, const CString& strText);
			void DrawString( Gdiplus::Graphics* gdip, const CString& strText, const CRect& crBounds, GdipFont* pFont,
							 COLORREF crColor, int iAlign, int iLength = -1, const CString& strPre = "",
							 const CString& strPost = "", bool bPeriods = true ) const;
			void DrawString( Gdiplus::Graphics* gdip, const CString& strText, const CRect& crBounds, Gdiplus::Font* pFont,
							 COLORREF crColor, int iAlign, int iLength = -1, const CString& strPre = "",
							 const CString& strPost = "", bool bPeriods = true ) const;
			void DrawRect( Gdiplus::Graphics* gdip, const CRect& cRect, COLORREF crColor, int iWidth = 1 ) const;
			void DrawBox( Gdiplus::Graphics* gdip, const CRect& cRect, COLORREF crColor, int iDepth ) const;
			COLORREF shiftColor( COLORREF crColor, int iShift ) const;

			std::vector<CString> wrapString( const CString& str, int iWrap, int iMax ) const;
			CString getStereotyped( const CString& str ) const;

			// for backward compatibility with StereotypeDecorators
			SFont* getFont( int iFontKey ) const;
			CPen* getPen( COLORREF crColor, int iWidth = 1, bool bDashed = false );
			CBrush* getBrush( COLORREF crColor );
			void drawText( CDC* pDC, const CString& strText, const CPoint& cpTopLeft,  CFont* pFont, COLORREF crColor,
							int iAlign, int iLength = -1, const CString& strPre = "", const CString& strPost = "",
							bool bPeriods = true ) const;
			void drawRect( CDC* pDC, const CRect& cRect, COLORREF crColor, int iWidth = 1 ) const;
			void drawBox( CDC* pDC, const CRect& cRect, COLORREF crColor, int iDepth ) const;

		private :
			BitmapBase* getBitmap( const CString& strName, bool bhasTC, COLORREF crTC, bool bhasBC, COLORREF crBC,
								   bool masked = false, UINT nResID = 0 );

	};

}; // namespace DecoratorSDK

#endif // DecoratorUtil_h