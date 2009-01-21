//################################################################################################
//
// DecoratorLib Utility Facility
//	DecoratorUtil.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "DecoratorUtil.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include "DecoratorDefs.h"
#include "MgaUtil.h"
#include "BitmapUtil.h"

static long stereotypeCharacterType = 0;

namespace DecoratorSDK
{
	Facilities facilities;

	Facilities& getFacilities()
	{
		return facilities;
	}

	bool Convert( const CString& strValue, long& lValue, bool bIsHexa )
	{
		return sscanf( strValue, ( bIsHexa ) ? "%x" : "%d", &lValue ) == 1;
	}

	bool Convert( const CString& strValue, COLORREF& crValue )
	{
		long lValue;
		if ( ! Convert( strValue, lValue, true ) ) {
			crValue = 0x0;
			return false;
		}
		unsigned int uiR = ( lValue & 0xFF0000 ) >> 16;
		unsigned int uiG = ( lValue  & 0xFF00 ) >> 8;
		unsigned int uiB = ( lValue & 0xFF );
		crValue = RGB( uiR, uiG, uiB );
		return true;
	}

	bool Convert( const CString& strValueIn, ELocation& eValue )
	{
		int iValue = 0;
		if ( sscanf( strValueIn, "%d", &iValue ) == 1 ) {
			eValue = (ELocation) iValue;
			return true;
		}
		CString strValue = strValueIn;
		strValue.TrimLeft( _T("\t ") );
		strValue.TrimRight( _T("\t ") );
		if ( strValue == "N") {
			eValue = L_NORTH;
			return true;
		}
		if ( strValue == "NE") {
			eValue = L_NORTHEAST;
			return true;
		}
		if ( strValue == "E") {
			eValue = L_EAST;
			return true;
		}
		if ( strValue == "SE") {
			eValue = L_SOUTHEAST;
			return true;
		}
		if ( strValue == "S") {
			eValue = L_SOUTH;
			return true;
		}
		if ( strValue == "SW") {
			eValue = L_SOUTHWEST;
			return true;
		}
		if ( strValue == "W") {
			eValue = L_WEST;
			return true;
		}
		if ( strValue == "NW") {
			eValue = L_NORTHWEST;
			return true;
		}
		if ( strValue =="C") {
			eValue = L_CENTER;
			return true;
		}
		return false;
	}

//################################################################################################
//
// CLASS : Facilities
//
//################################################################################################

Facilities::Facilities()
	: m_bArePathesValid( false ), m_spProject( NULL )
{
	createFont( FONT_LABEL,			"Arial", FW_NORMAL,		false,	16 );
	createFont( FONT_PORT,			"Arial", FW_BOLD,		false,	12 );
	createFont( FONT_TYPE,			"Arial", FW_NORMAL,		false,	12 );
	createFont( FONT_PORT_OUTSIDE,	"Arial", FW_BOLD,		false,	11 );
	createFont( FONT_PORTNAME,		"Arial", FW_NORMAL,		false,	15 );
	createFont( FONT_CONNLABEL,		"Arial", FW_LIGHT,		false,	12 );
	createFont( FONT_ABSTRACT,		"Arial", FW_NORMAL,		true,	15 );

	TileVector* pTileVector = new TileVector();

	RefPoint rpTL2( RefCoord( CRP_BEGIN, 0 ), RefCoord( CRP_BEGIN, 0 ) );
	RefPoint rpBR2( RefCoord( CRP_END, 0 ), RefCoord( CRP_END, 0 ) );
	pTileVector->push_back( BackgroundTile( rpTL2, rpBR2, rpTL2, rpBR2, FT_STRETCH, FT_STRETCH ) );

//	TileVector* pTileVector = new TileVector( 1, BackgroundTile() );
	addTileVector( TILE_ATOMDEFAULT, pTileVector );

	pTileVector = new TileVector();

	RefPoint rpTL( RefCoord( CRP_BEGIN, 0 ), RefCoord( CRP_BEGIN, 0 ) );
	RefPoint rpBR( RefCoord( CRP_BEGIN, 5 ), RefCoord( CRP_BEGIN, 5 ) );
	pTileVector->push_back( BackgroundTile( rpTL, rpBR, rpTL, rpBR, FT_NONE, FT_NONE ) );
	rpTL = RefPoint( RefCoord( CRP_END, 5 ), RefCoord( CRP_BEGIN, 0 ) );
	rpBR = RefPoint( RefCoord( CRP_END, 0 ), RefCoord( CRP_BEGIN, 5 ) );
	pTileVector->push_back( BackgroundTile( rpTL, rpBR, rpTL, rpBR, FT_NONE, FT_NONE ) );
	rpTL = RefPoint( RefCoord( CRP_BEGIN, 0 ), RefCoord( CRP_END, 5 ) );
	rpBR = RefPoint( RefCoord( CRP_BEGIN, 5 ), RefCoord( CRP_END, 0 ) );
	pTileVector->push_back( BackgroundTile( rpTL, rpBR, rpTL, rpBR, FT_NONE, FT_NONE ) );
	rpTL = RefPoint( RefCoord( CRP_END, 5 ), RefCoord( CRP_END, 5 ) );
	rpBR = RefPoint( RefCoord( CRP_END, 0 ), RefCoord( CRP_END, 0 ) );
	pTileVector->push_back( BackgroundTile( rpTL, rpBR, rpTL, rpBR, FT_NONE, FT_NONE ) );

	rpTL = RefPoint( RefCoord( CRP_BEGIN, 5 ), RefCoord( CRP_BEGIN, 0 ) );
	rpBR = RefPoint( RefCoord( CRP_END, 5 ), RefCoord( CRP_BEGIN, 5 ) );
	pTileVector->push_back( BackgroundTile( rpTL, rpBR, rpTL, rpBR, FT_STRETCH, FT_NONE ) );
	rpTL = RefPoint( RefCoord( CRP_BEGIN, 5 ), RefCoord( CRP_END, 5 ) );
	rpBR = RefPoint( RefCoord( CRP_END, 5 ), RefCoord( CRP_END, 0 ) );
	pTileVector->push_back( BackgroundTile( rpTL, rpBR, rpTL, rpBR, FT_STRETCH, FT_NONE ) );
	rpTL = RefPoint( RefCoord( CRP_BEGIN, 0 ), RefCoord( CRP_BEGIN, 5 ) );
	rpBR = RefPoint( RefCoord( CRP_BEGIN, 5 ), RefCoord( CRP_END, 5 ) );
	pTileVector->push_back( BackgroundTile( rpTL, rpBR, rpTL, rpBR, FT_NONE, FT_STRETCH ) );
	rpTL = RefPoint( RefCoord( CRP_END, 5 ), RefCoord( CRP_BEGIN, 5 ) );
	rpBR = RefPoint( RefCoord( CRP_END, 0 ), RefCoord( CRP_END, 5 ) );
	pTileVector->push_back( BackgroundTile( rpTL, rpBR, rpTL, rpBR, FT_NONE, FT_STRETCH ) );

	rpTL = RefPoint( RefCoord( CRP_BEGIN, 5 ), RefCoord( CRP_BEGIN, 5 ) );
	rpBR = RefPoint( RefCoord( CRP_END, 5 ), RefCoord( CRP_END, 5 ) );
	pTileVector->push_back( BackgroundTile( rpTL, rpBR, rpTL, rpBR, FT_STRETCH, FT_STRETCH ) );

	addTileVector( TILE_MODELDEFAULT, pTileVector );

	pTileVector = new TileVector();

	rpTL = RefPoint( RefCoord( CRP_BEGIN, 0 ), RefCoord( CRP_BEGIN, 0 ) );
	rpBR = RefPoint( RefCoord( CRP_END, 0 ), RefCoord( CRP_END, 0 ) );
	pTileVector->push_back( BackgroundTile( rpTL, rpBR, rpTL, rpBR, FT_STRETCH, FT_STRETCH ) );

	addTileVector( TILE_PORTDEFAULT, pTileVector );
}

Facilities::~Facilities()
{
	for ( std::map<CString,BitmapBase*>::iterator it = m_mapBitmaps.begin() ; it != m_mapBitmaps.end() ; ++it )
		delete it->second;
	for ( std::map<CString,TileVector*>::iterator it2 = m_mapTileVectors.begin() ; it2 != m_mapTileVectors.end() ; ++it2 )
		delete it2->second;
	for ( std::map<int,SFont*>::iterator it3 = m_mapFonts.begin() ; it3 != m_mapFonts.end() ; ++it3 ) {
		it3->second->pFont->DeleteObject();
		delete it3->second->pFont;
		delete it3->second;
	}
	for ( std::map<int,GdipFont*>::iterator it4 = m_mapGdipFonts.begin() ; it4 != m_mapGdipFonts.end() ; ++it4 ) {
		delete it4->second->gdipFont;
		delete it4->second;
	}
	for ( std::map<CString,CPen*>::iterator it5 = m_mapPens.begin() ; it5 != m_mapPens.end() ; ++it5 ) {
		it5->second->DeleteObject();
		delete it5->second;
	}
	for ( std::map<CString,CBrush*>::iterator it6 = m_mapBrushes.begin() ; it6 != m_mapBrushes.end() ; ++it6 ) {
		it6->second->DeleteObject();
		delete it6->second;
	}
	for ( std::map<CString,Gdiplus::Pen*>::iterator it7 = m_mapGdipPens.begin() ; it7 != m_mapGdipPens.end() ; ++it7 )
		delete it7->second;
	for ( std::map<CString,Gdiplus::SolidBrush*>::iterator it8 = m_mapGdipBrushes.begin() ; it8 != m_mapGdipBrushes.end() ; ++it8 )
		delete it8->second;
}

bool Facilities::loadPathes( IMgaProject* pProject, bool bRefresh )
{
	if ( ! m_spProject || ! m_spProject.IsEqualObject( pProject ) )
		m_spProject = pProject;
	else
		return m_bArePathesValid = true;

	if ( bRefresh ) {
		m_vecPathes.clear();
		m_bArePathesValid = false;

		if ( pProject ) {
			long lStatus;
			COMTHROW( pProject->get_ProjectStatus( &lStatus ) );
			if ( (lStatus & 0x01L) != 0 ) {
				CComBSTR bstrParadigm;
				COMTHROW( pProject->get_ParadigmConnStr( &bstrParadigm ) );
				m_strParadigmPath = CString( bstrParadigm );
				if ( m_strParadigmPath.Find( "MGA=" ) == 0 ) {
					int iPos = m_strParadigmPath.ReverseFind( _T('\\') );
					if( iPos >= 4 ) {
						m_strParadigmPath = m_strParadigmPath.Mid( 4, iPos - 4 );
						if( m_strParadigmPath.IsEmpty() )
							m_strParadigmPath = '\\';
					}
				}

				CComBSTR bstrProject;
				COMTHROW( pProject->get_ProjectConnStr( &bstrProject ) );
				m_strProjectPath = CString( bstrProject );
				if ( m_strProjectPath.Find( "MGA=" ) == 0 ) {
					int iPos = m_strProjectPath.ReverseFind( _T('\\') );
					if( iPos >= 4 ) {
						m_strProjectPath = m_strProjectPath.Mid( 4, iPos - 4 );
						if( m_strProjectPath.IsEmpty() )
							m_strProjectPath = '\\';
					}
				}
			}
		}
	}

	if ( ! m_bArePathesValid ) {

		CString strPath;
		try {
			CComPtr<IMgaRegistrar> spRegistrar;
			COMTHROW( spRegistrar.CoCreateInstance( OLESTR( "Mga.MgaRegistrar" ) ) );
			CComBSTR bstrPath;
			COMTHROW( spRegistrar->get_IconPath( REGACCESS_BOTH, &bstrPath ) );

			CopyTo( bstrPath, strPath );
		}
		catch ( hresult_exception & ) {
		}

		strPath.Replace( "$PARADIGMDIR", m_strParadigmPath );
		strPath.Replace( "$PROJECTDIR", m_strProjectPath );

		while( ! strPath.IsEmpty() ) {
			int iPos = strPath.Find( ';' );
			if( iPos == 0) // zolmol: if accidentaly there are two semicolons, or the path starts with a semicolon
			{
				strPath = strPath.Right( strPath.GetLength() - 1 );
				continue;
			}
			CString strDir;
			if ( iPos != -1 ) {
				strDir = strPath.Left( iPos );
				strPath = strPath.Right( strPath.GetLength() - iPos - 1 );
			}
			else {
				strDir = strPath;
				strPath.Empty();
			}
			strDir.Replace( '/', '\\' );
			if ( strDir.GetAt( strDir.GetLength() - 1 ) != '\\' )
				strDir += "\\";
			m_vecPathes.push_back( strDir );
		}
		m_vecPathes.push_back( ".\\" );

		m_bArePathesValid = true;
	}

	return m_bArePathesValid;
}

bool Facilities::arePathesValid() const
{
	return m_bArePathesValid;
}

std::vector<CString> Facilities::getPathes() const
{
	return m_vecPathes;
}

bool Facilities::getPreference( CComPtr<IMgaFCO> spFCO, const CString& strName, CString& strValue ) const
{
	return getPreference(spFCO, NULL, strName, strValue);
}

bool Facilities::getPreference( CComPtr<IMgaFCO> spFCO, const CString& strName, long& lValue, bool bInHexa ) const
{
	return getPreference(spFCO, NULL, strName, lValue, bInHexa);
}

bool Facilities::getPreference( CComPtr<IMgaFCO> spFCO, const CString& strName, COLORREF& crValue ) const
{
	return getPreference(spFCO, NULL, strName, crValue);
}

bool Facilities::getPreference( CComPtr<IMgaFCO> spFCO, const CString& strName, ELocation& eValue ) const
{
	return getPreference(spFCO, NULL, strName, eValue);
}

bool Facilities::getPreference( CComPtr<IMgaFCO> spFCO, const CString& strName, bool& bValue ) const
{
	return getPreference(spFCO, NULL, strName, bValue);
}

bool Facilities::getPreference( CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, CString& strValue ) const
{
	return getPreference(NULL, spMetaFCO, strName, strValue);
}

bool Facilities::getPreference( CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, long& lValue, bool bInHexa ) const
{
	return getPreference(NULL, spMetaFCO, strName, lValue, bInHexa);
}

bool Facilities::getPreference( CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, COLORREF& crValue ) const
{
	return getPreference(NULL, spMetaFCO, strName, crValue);
}

bool Facilities::getPreference( CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, ELocation& eValue ) const
{
	return getPreference(NULL, spMetaFCO, strName, eValue);
}

bool Facilities::getPreference( CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, bool& bValue ) const
{
	return getPreference(NULL, spMetaFCO, strName, bValue);
}

bool Facilities::getPreference( CComPtr<IMgaFCO> spFCO, CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, CString& strValue ) const
{
	CComBSTR bstrPath;
	CopyTo( strName, bstrPath );
	CComBSTR bstrValue;

	try {
		if (spFCO)
			COMTHROW( spFCO->get_RegistryValue( bstrPath, &bstrValue ) );
		else if (spMetaFCO)
			COMTHROW( spMetaFCO->get_RegistryValue( bstrPath, &bstrValue ) );
		else
			ASSERT(true);
	}
	catch (hresult_exception &) {
		bstrValue.Empty();
	}

	CString strValueT;
	CopyTo( bstrValue, strValueT );
	if ( ! strValueT.IsEmpty() )
		strValue = strValueT;
	return ! strValueT.IsEmpty();
}

bool Facilities::getPreference( CComPtr<IMgaFCO> spFCO, CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, long& lValue, bool bInHexa ) const
{
	CString strValue;
	if ( ! getPreference( spFCO, spMetaFCO, strName, strValue ) )
		return false;
	long lValueT;
	if ( ! Convert( strValue, lValueT, bInHexa ) )
		return false;
	lValue = lValueT;
	return true;
}

bool Facilities::getPreference( CComPtr<IMgaFCO> spFCO, CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, COLORREF& crValue ) const
{
	CString strValue;
	if ( ! getPreference( spFCO, spMetaFCO, strName, strValue ) )
		return false;
	COLORREF crValueT;
	if ( ! Convert( strValue, crValueT ) )
		return false;
	crValue = crValueT;
	return true;
}

bool Facilities::getPreference( CComPtr<IMgaFCO> spFCO, CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, ELocation& eValue ) const
{
	CString strValue;
	if ( ! getPreference( spFCO, spMetaFCO, strName, strValue ) )
		return false;
		ELocation eValueT;
	if ( ! Convert( strValue, eValueT ) )
		return false;
	eValue = eValueT;
	return true;
}

bool Facilities::getPreference( CComPtr<IMgaFCO> spFCO, CComPtr<IMgaMetaFCO> spMetaFCO, const CString& strName, bool& bValue ) const
{
	CString strValue;
	if ( ! getPreference( spFCO, spMetaFCO, strName, strValue ) )
		return false;
	strValue.MakeLower();
	bValue = strValue == "t" || strValue == "true" || strValue == "1";
	return true;
}

EPrefStatus Facilities::getPreferenceStatus( CComPtr<IMgaFCO> spFCO, const CString& strName ) const
{
	CString strValue;
	if ( ! getPreference( spFCO, strName, strValue ) )
		return PS_UNDEFINED;

	CComPtr<IMgaRegNode> spNode;
	CComBSTR bstrName;
	CopyTo( strName, bstrName );
	COMTHROW( spFCO->get_RegistryNode( bstrName, &spNode ) );

	long lStatus;
	COMTHROW( spNode->get_Status( &lStatus ) );
	switch ( lStatus ) {
		case 0 : return PS_HERE;
		case -1 : return PS_META;
		default : return PS_INHERITED;
	}
}

bool Facilities::getAttribute( CComPtr<IMgaFCO> spFCO, const CString& strName, CString& strValue ) const
{
	if (!spFCO) {
		return false;
	}
	CComBSTR attrname;
	CopyTo( strName, attrname );
	CComBSTR bstrValue;

	try {
		COMTHROW(spFCO->get_StrAttrByName(attrname, &bstrValue));
	}
	catch (hresult_exception &) {
		bstrValue.Empty();
	}

	CString strValueT;
	CopyTo( bstrValue, strValueT );
	if ( ! strValueT.IsEmpty() )
		strValue = strValueT;
	return ! strValueT.IsEmpty();
}

bool Facilities::getAttribute( CComPtr<IMgaFCO> spFCO, const CString& strName, bool& bValue ) const
{
	if (!spFCO) {
		return false;
	}
	CComBSTR attrname;
	CopyTo( strName, attrname );
	VARIANT_BOOL vval;

	try {
		COMTHROW(spFCO->get_BoolAttrByName(attrname, &vval));
	}
	catch (hresult_exception &) {
		return false;
	}

	bValue = (vval == VARIANT_TRUE);
	return true;
}

bool Facilities::setAttribute( CComPtr<IMgaFCO> spFCO, const CString& strName, const CString& strValue ) const
{
	if (!spFCO) {
		return false;
	}
	CComBSTR attrname;
	CopyTo( strName, attrname );
	CComBSTR bstrValue;
	CopyTo( strValue, bstrValue );

	try {
		COMTHROW(spFCO->put_StrAttrByName(attrname, bstrValue));
	}
	catch (hresult_exception &) {
		return false;
	}

	return true;
}

bool Facilities::setAttribute( CComPtr<IMgaFCO> spFCO, const CString& strName, bool bValue ) const
{
	if (!spFCO) {
		return false;
	}
	CComBSTR attrname;
	CopyTo( strName, attrname );
	VARIANT_BOOL vval = bValue ? VARIANT_TRUE : VARIANT_FALSE;

	try {
		COMTHROW(spFCO->put_BoolAttrByName(attrname, vval));
	}
	catch (hresult_exception &) {
		return false;
	}

	return true;
}

bool Facilities::getMetaFCO(const CComPtr<IMgaMetaPart> &metaPart, CComPtr<IMgaMetaFCO> &metaFco) const
{
	if (!metaPart) {
		return false;
	}

	metaFco = NULL;
	CComPtr<IMgaMetaRole> metaRole;
	try {
		COMTHROW(metaPart->get_Role(&metaRole));
		VERIFY(metaRole);
		COMTHROW(metaRole->get_Kind(&metaFco));
	}
	catch (hresult_exception &) {
		metaFco = NULL;
	}
	return (metaFco != NULL);
}

BitmapBase* Facilities::getBitmap( const CString& strName, bool bHasTC, COLORREF crTC, bool bHasBC, COLORREF crBC,
								   bool masked, UINT nResID )
{
	CString strID( strName );
	if ( masked ) {
		if (nResID != 0) {
			char chBuffer[ 10 ];
			_ultoa( nResID, chBuffer, 10 );
			strID += chBuffer;
		}
		strID += "<Masked>";
	}
	if ( bHasTC ) {
		char chBuffer[ 10 ];
		_ultoa( crTC, chBuffer, 16 );
		strID += "<TC:" + CString( chBuffer ) + ">";
	}
	if ( bHasBC ) {
		char chBuffer[ 10 ];
		_ultoa( crBC, chBuffer, 16 );
		strID += "<BC:" + CString( chBuffer ) + ">";
	}

	std::map<CString,BitmapBase*>::iterator it = m_mapBitmaps.find( strID );
	if ( it != m_mapBitmaps.end() )
		return it->second;

	if (masked) {
		BitmapMasked* pBMP = NULL;
		if ( nResID != NULL )
			pBMP = new BitmapMasked( nResID, crTC, crBC );
		else
			pBMP = new BitmapMasked( strName, crTC, crBC );
		if ( pBMP->isInitialized() ) {
			m_mapBitmaps.insert( std::map<CString,BitmapBase*>::value_type( strID, pBMP ) );
			return pBMP;
		}
		delete pBMP;
		return NULL;
	}

	CString strExt, strEx2;
	if ( strName.GetLength() >= 4 ) {
		strExt = strName.Right( 4 ).MakeLower();
	
		if( strName.GetLength() >= 5) // in case of ".jpeg"
			strEx2 = strName.Right(5).MakeLower();
		
		if ( strExt != ".bmp" && strExt != ".gif" && strExt != ".png"
			&& strExt != ".jpg" && strExt != ".jpe" && strEx2 != ".jpeg" 
			&& strExt != ".res" )
			strExt = "";
	}

	if( strExt.IsEmpty()) // if no extension then try the different formats
	{
		bool success = false;
		static char * exts[] = { ".bmp", ".gif", ".png", ".jpg", ".jpe", ".jpeg" };
		for( int i = 0; !success && i < 6; ++i)
		{
			CString strName2 = strName + exts[i];
			BitmapGen* pBMP = NULL;
			if ( bHasTC )
				pBMP = ( bHasBC ) ? new BitmapGen( strName2, crTC, crBC ) : new BitmapGen( strName2, crTC, true );
			else
				pBMP = ( bHasBC ) ? new BitmapGen( strName2, crBC, false ) : new BitmapGen( strName2);
			if ( pBMP->isInitialized() ) {
				m_mapBitmaps.insert( std::map<CString,BitmapBase*>::value_type( strID, pBMP ) );
				success = true;
				return pBMP;
			}
			delete pBMP;
		}
	}
	else if( strExt != ".res") // if regular file use name as is
	{
		BitmapGen* pBMP = NULL;
		if ( bHasTC )
			pBMP = ( bHasBC ) ? new BitmapGen( strName, crTC, crBC ) : new BitmapGen( strName, crTC, true );
		else
			pBMP = ( bHasBC ) ? new BitmapGen( strName, crBC, false ) : new BitmapGen( strName);
		if ( pBMP->isInitialized() ) {
			m_mapBitmaps.insert( std::map<CString,BitmapBase*>::value_type( strID, pBMP ) );
			return pBMP;
		}
		return NULL; // if the image not found
	}

	if ( strExt == ".res" || strExt.IsEmpty() ) {
		int iID = atoi( strName.Left( strName.GetLength() - ( ( strExt.IsEmpty() ) ? 0 : 4 ) ) );
		if( iID == 0)    // might be true if specified icon filename
			return NULL; // has no extension and not found yet
		BitmapRES* pBMP = NULL;
		if ( bHasTC )
			pBMP = ( bHasBC ) ? new BitmapRES( iID, crTC, crBC ) : new BitmapRES( iID, crTC, true );
		else
			pBMP = ( bHasBC ) ? new BitmapRES( iID, crBC, false ) : new BitmapRES( iID );
		if ( pBMP->isInitialized() ) {
			m_mapBitmaps.insert( std::map<CString,BitmapBase*>::value_type( strID, pBMP ) );
			return pBMP;
		}
		delete pBMP;
		if ( ! strExt.IsEmpty() )
			return NULL;
	}
	return NULL;
}

BitmapBase* Facilities::getBitmap( const CString& strName )
{
	return getBitmap( strName, false, 0x0, false, 0x0 );
}

BitmapBase* Facilities::getBitmapT( const CString& strName, COLORREF crTransparent )
{
	return getBitmap( strName, true, crTransparent, false, 0x0 );
}

BitmapBase* Facilities::getBitmapB( const CString& strName, COLORREF crBackground )
{
	return getBitmap( strName, false, 0x0, true, crBackground );
}

BitmapBase* Facilities::getBitmapTB( const CString& strName, COLORREF crTransparent, COLORREF crBackground )
{
	return getBitmap( strName, true, crTransparent, true, crBackground );
}

BitmapBase* Facilities::getMaskedBitmap( const CString& strName, COLORREF crTransparent, COLORREF crBackground )
{
	return getBitmap( strName, true, crTransparent, true, crBackground, true );
}

BitmapBase* Facilities::getMaskedBitmap( UINT nResID, COLORREF crTransparent, COLORREF crBackground )
{
	return getBitmap( "", true, crTransparent, true, crBackground, true, nResID );
}

void Facilities::addTileVector( const CString& strName, TileVector* vecTiles )
{
	TileVector* vecStored = getTileVector( strName );
	if ( vecStored )
		delete vecStored;
	m_mapTileVectors[ strName ] = vecTiles;
}

TileVector* Facilities::getTileVector( const CString& strName ) const
{
	std::map<CString,TileVector*>::const_iterator it = m_mapTileVectors.find( strName );
	return ( it == m_mapTileVectors.end() ) ? NULL : it->second;
}

void Facilities::createFont( int iFontKey, const CString& strKind, int iBoldness, bool bItalics, int iSize )
{
	SFont* psFont = getFont( iFontKey );
	if ( psFont ) {
		psFont->pFont->DeleteObject();
		delete psFont->pFont;
		delete psFont;
	}
	m_mapFonts[ iFontKey ] = new SFont( strKind, iSize, iBoldness, bItalics );
	m_mapFonts[ iFontKey ]->pFont = new CFont();
	m_mapFonts[ iFontKey ]->pFont->CreateFont( iSize, 0, 0, 0, iBoldness, bItalics, 0, 0, ANSI_CHARSET, OUT_DEVICE_PRECIS,
												CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_SWISS, strKind );

	GdipFont* pgFont = GetFont( iFontKey );
	if ( pgFont ) {
		delete pgFont->gdipFont;
		delete pgFont;
	}

/*	int fontStyle = Gdiplus::FontStyleRegular;
	if (iBoldness == FW_BOLD)
		fontStyle |= Gdiplus::FontStyleBold;
	if (bItalics)
		fontStyle |= Gdiplus::FontStyleItalic;

	float pixelSize = static_cast<float> (iSize * 72.0 / GetDeviceCaps(GetDC(NULL), LOGPIXELSY));
	m_mapGdipFonts[ iFontKey ] = new GdipFont( strKind, iSize, iBoldness == FW_BOLD, bItalics );
	CA2W wcTxt(strKind);
	m_mapGdipFonts[ iFontKey ]->gdipFont = new Gdiplus::Font( wcTxt, pixelSize, fontStyle, Gdiplus::UnitPixel );*/

	m_mapGdipFonts[ iFontKey ] = new GdipFont( strKind, iSize, iBoldness == FW_BOLD, bItalics );
	CDC dc;
	dc.CreateCompatibleDC(NULL);
	LOGFONT logFont;
	m_mapFonts[ iFontKey ]->pFont->GetLogFont(&logFont);
	m_mapGdipFonts[ iFontKey ]->gdipFont = new Gdiplus::Font( dc.m_hDC, &logFont );
}

GdipFont* Facilities::GetFont( int iFontKey ) const
{
	std::map<int,GdipFont*>::const_iterator it = m_mapGdipFonts.find( iFontKey );
	return ( it == m_mapGdipFonts.end() ) ? NULL : it->second;
}

Gdiplus::Pen* Facilities::GetPen( COLORREF crColor, int iWidth )
{
	CString chBuffer;
	chBuffer.Format("%x-%d", crColor, iWidth);
	std::map<CString,Gdiplus::Pen*>::iterator it = m_mapGdipPens.find(chBuffer);
	if (it != m_mapGdipPens.end())
		return it->second;
	Gdiplus::Pen* pPen = new Gdiplus::Pen(Gdiplus::Color(GetRValue(crColor), GetGValue(crColor), GetBValue(crColor)), static_cast<float> (iWidth));
	m_mapGdipPens.insert( std::map<CString,Gdiplus::Pen*>::value_type(chBuffer, pPen));
	return pPen;
}

Gdiplus::SolidBrush* Facilities::GetBrush( COLORREF crColor )
{
	CString chBuffer;
	chBuffer.Format("%x", crColor);
	std::map<CString,Gdiplus::SolidBrush*>::iterator it = m_mapGdipBrushes.find(chBuffer);
	if (it != m_mapGdipBrushes.end())
		return it->second;
	Gdiplus::SolidBrush* pBrush = new Gdiplus::SolidBrush(Gdiplus::Color(GetRValue(crColor), GetGValue(crColor), GetBValue(crColor)));
	m_mapGdipBrushes.insert(std::map<CString,Gdiplus::SolidBrush*>::value_type(chBuffer, pBrush));
	return pBrush;
}

CSize Facilities::MeasureText( Gdiplus::Graphics* gdip, GdipFont* pFont, const CString& strText)
{
	return MeasureText(gdip, pFont->gdipFont, strText);
}

CSize Facilities::MeasureText( Gdiplus::Graphics* gdip, Gdiplus::Font* pFont, const CString& strText)
{
	Gdiplus::Graphics* gdip2 = NULL;
	CDC	dc;
	if (gdip == NULL) {
		dc.CreateCompatibleDC(NULL);
		gdip2 = new Gdiplus::Graphics(dc.m_hDC);
		gdip2->SetPageUnit(Gdiplus::UnitPixel);
		gdip2->SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
		gdip2->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);
		gdip = gdip2;
	}

	CA2W wcTxt(strText);
	Gdiplus::PointF origin(0, 0);
	Gdiplus::RectF rectF;
	gdip->MeasureString(wcTxt, strText.GetLength(), pFont, origin, &rectF);
	Gdiplus::SizeF sizeF;
	rectF.GetSize(&sizeF);
	CSize size(static_cast<long> (sizeF.Width), static_cast<long> (sizeF.Height));

	if (gdip2 != NULL)
		delete gdip2;
	return size;
}

void Facilities::DrawString( Gdiplus::Graphics* gdip, const CString& strText, const CRect& crBounds, GdipFont* pFont,
							 COLORREF crColor, int iAlign, int iLength, const CString& strPre, const CString& strPost, bool bPeriods ) const
{
	DrawString(gdip, strText, crBounds, pFont->gdipFont, crColor, iAlign, iLength, strPre, strPost, bPeriods);
}

void Facilities::DrawString( Gdiplus::Graphics* gdip, const CString& strText, const CRect& crBounds, Gdiplus::Font* pFont,
							 COLORREF crColor, int iAlign, int iLength, const CString& strPre, const CString& strPost, bool bPeriods ) const
{
	CString strText2( strPre + strText + strPost );
	if ( iLength != -1 && strText2.GetLength() > iLength )
		strText2 = strPre + strText.Left( iLength ) + ( ( bPeriods ) ? "..." : "" ) + strPost;

	Gdiplus::StringFormat format;
	Gdiplus::StringAlignment horizontalAlignment;
	if ((iAlign & TA_CENTER) == TA_CENTER) {
		horizontalAlignment = Gdiplus::StringAlignmentCenter;
	} else if ((iAlign & TA_RIGHT) == TA_RIGHT) {
		horizontalAlignment = Gdiplus::StringAlignmentFar;
	} else {	// TA_LEFT
		horizontalAlignment = Gdiplus::StringAlignmentNear;
	}
	format.SetAlignment(horizontalAlignment);
	Gdiplus::StringAlignment verticalAlignment;
	if ((iAlign & TA_BASELINE) == TA_BASELINE) {
		verticalAlignment = Gdiplus::StringAlignmentCenter;
	} else if ((iAlign & TA_BOTTOM) == TA_BOTTOM) {
		verticalAlignment = Gdiplus::StringAlignmentFar;
	} else {	// TA_TOP
		verticalAlignment = Gdiplus::StringAlignmentNear;
	}
	format.SetLineAlignment(verticalAlignment);

//	HDC hDC = gdip->GetHDC();
	COLORREF textColor = /*GetDeviceCaps(hDC, TECHNOLOGY) == DT_RASPRINTER ? COLOR_BLACK :*/ crColor;
//	gdip->ReleaseHDC(hDC);

	Gdiplus::SolidBrush textBrush(Gdiplus::Color(GetRValue(textColor),
												 GetGValue(textColor),
												 GetBValue(textColor)));

	CA2W wcTxt(strText2);
	Gdiplus::RectF rectF(static_cast<float> (crBounds.left),
						 static_cast<float> (crBounds.top),
						 static_cast<float> (crBounds.Width()),
						 static_cast<float> (crBounds.Height()));
	gdip->DrawString(wcTxt, strText2.GetLength(), pFont, rectF, &format, &textBrush);
}

void Facilities::DrawRect( Gdiplus::Graphics* gdip, const CRect& cRect, COLORREF crColor, int iWidth ) const
{
	Facilities* pThis = (Facilities*) this;
	Gdiplus::Pen* pPen = pThis->GetPen( crColor, iWidth );
	CRect cRect2 = cRect;
	cRect2.DeflateRect( iWidth / 2, iWidth / 2 );

	gdip->DrawRectangle(pPen, cRect2.left, cRect2.top, cRect2.Width(), cRect2.Height());
}

void Facilities::DrawBox( Gdiplus::Graphics* gdip, const CRect& cRect, COLORREF crColor, int iDepth ) const
{
	Facilities* pThis = (Facilities*) this;

	COLORREF beginColor = ShiftColor( crColor, -40 );
	COLORREF endColor = ShiftColor( crColor, 60 );

	Gdiplus::GraphicsPath edgePath;
	edgePath.AddLine(cRect.left, cRect.top, cRect.right, cRect.top);
	edgePath.AddLine(cRect.right, cRect.top, cRect.right, cRect.bottom);
	edgePath.AddLine(cRect.right, cRect.bottom, cRect.left, cRect.bottom);
	edgePath.AddLine(cRect.left, cRect.bottom, cRect.left, cRect.top);

	Gdiplus::Color darkerColor = Gdiplus::Color(GetRValue(beginColor),
												GetGValue(beginColor),
												GetBValue(beginColor));
	Gdiplus::Color lighterColor = Gdiplus::Color(GetRValue(endColor),
												 GetGValue(endColor),
												 GetBValue(endColor));
	Gdiplus::Color borderPresetColors[] = {
											darkerColor,
											lighterColor,
											darkerColor,
											darkerColor
										  };
	float borderRatio = static_cast<float> (static_cast<float> (iDepth) / cRect.Height());
	float centerRatio = static_cast<float> (static_cast<float> (iDepth) / cRect.Height() * 2.0);
	float borderInterpolationPositions[] = {
		0.0f,
		borderRatio,
		centerRatio,
		1.0f };
	Gdiplus::PathGradientBrush edgePathGradientBrush(&edgePath);
	edgePathGradientBrush.SetInterpolationColors(borderPresetColors, borderInterpolationPositions, 4);
	gdip->FillPath(&edgePathGradientBrush, &edgePath);

	CRect innerRect = cRect;
	long vBorder = static_cast<long> (static_cast<float> (iDepth) * cRect.Width() / cRect.Height());
	innerRect.InflateRect(-vBorder + 1, -iDepth + 1, -vBorder - 1, -iDepth - 1);
	Gdiplus::LinearGradientBrush linearGradientBrush(Gdiplus::Point(innerRect.left, innerRect.top),
													 Gdiplus::Point(innerRect.left, innerRect.bottom),
													 lighterColor,
													 darkerColor);
	gdip->FillRectangle(&linearGradientBrush, innerRect.left, innerRect.top, innerRect.Width(), innerRect.Height());
}

COLORREF Facilities::ShiftColor( COLORREF crColor, int iShift ) const
{
	int iR = GetRValue( crColor );
	int iG = GetGValue( crColor );
	int iB = GetBValue( crColor );
	iR = min( max( iR + iShift, 0 ), 255 );
	iG = min( max( iG + iShift, 0 ), 255 );
	iB = min( max( iB + iShift, 0 ), 255 );
	return RGB( iR, iG, iB );
}

double Facilities::Deg2Rad( long deg ) const
{
	return (deg * 2 * M_PI / 360.0);
}

std::vector<CString> Facilities::wrapString( const CString& strIn, int iWrap, int iMax ) const
{
	std::vector<CString> vecOut;
	CString str = strIn;
	str.TrimLeft();
	str.TrimRight();
	iWrap = min( iMax, iWrap );
	if ( iWrap == 0 || iWrap == -1 )
		vecOut.push_back( str );
	else {
		while ( ! str.IsEmpty() ) {
			CString str2 = str;
			if ( str.GetLength() > iWrap ) {
				str2 = str.Left( iWrap );
				int iPos = str2.ReverseFind( ' ' );
				if ( iPos == -1 || iPos < str2.GetLength() - 5 ) {
					str2 = str.Right( str.GetLength() - iWrap );
					iPos = str2.Find( ' ' );
					if ( iPos == -1 && str2.GetLength() > 5 || iPos >= 5  ) {
						str2 = str.Left( iWrap );
						str = str.Right( str.GetLength() - iWrap );
					}
					else {
						if ( iPos == -1 )
							iPos = str2.GetLength();
						str2 = str.Left( iWrap + iPos );
						str = str.Right( str.GetLength() - iWrap - iPos - 1 );
					}
				}
				else {
					str2 = str.Left( iPos );
					str = str.Right( str.GetLength() - iPos - 1 );
				}
			}
			else
				str = "";
			str2.TrimRight();
			str.TrimLeft();
			vecOut.push_back( str2 );
		}
	}
	return vecOut;
}

CString Facilities::getStereotyped( const CString& strIn ) const
{
	CString str;
	if (stereotypeCharacterType)
		str = str + STEREOTYPE_LEFTB + strIn + STEREOTYPE_RIGHTB;
	else
		str = str + STEREOTYPE_LEFTA + strIn + STEREOTYPE_RIGHTA;
	return str;
}

SFont* Facilities::getFont( int iFontKey ) const
{
	std::map<int,SFont*>::const_iterator it = m_mapFonts.find( iFontKey );
	return ( it == m_mapFonts.end() ) ? NULL : it->second;
}

CPen* Facilities::getPen( COLORREF crColor, int iWidth, bool bDashed )
{
	CString chBuffer;
	chBuffer.Format("%x-%d-%d", crColor, iWidth, bDashed);
	std::map<CString,CPen*>::iterator it = m_mapPens.find(chBuffer);
	if (it != m_mapPens.end())
		return it->second;
	CPen* pPen = new CPen(bDashed ? PS_DOT : PS_SOLID, iWidth, crColor);
	m_mapPens.insert(std::map<CString,CPen*>::value_type(chBuffer, pPen));
	return pPen;
}

CBrush* Facilities::getBrush( COLORREF crColor )
{
	CString chBuffer;
	chBuffer.Format("%x", crColor);
	std::map<CString,CBrush*>::iterator it = m_mapBrushes.find(chBuffer);
	if (it != m_mapBrushes.end())
		return it->second;
	CBrush* pBrush = new CBrush(crColor);
	m_mapBrushes.insert(std::map<CString,CBrush*>::value_type(chBuffer, pBrush));
	return pBrush;
}

void Facilities::drawText( CDC* pDC, const CString& strText, const CPoint& cpTopLeft,  CFont* pFont, COLORREF crColor, int iAlign, int iLength, const CString& strPre, const CString& strPost, bool bPeriods ) const
{
	CString strText2( strPre + strText + strPost );
	if ( iLength != -1 && strText2.GetLength() > iLength )
		strText2 = strPre + strText.Left( iLength + strPre.GetLength() ) + ( ( bPeriods ) ? "..." : "" ) + strPost;

	CFont* oldFont = pDC->SelectObject( pFont );
	pDC->SetTextAlign( iAlign );
	SetBkMode( pDC->m_hDC, TRANSPARENT );

	pDC->SetTextColor( pDC->IsPrinting() ? COLOR_BLACK : crColor );
	pDC->TextOut( cpTopLeft.x, cpTopLeft.y, strText2 );
	pDC->SelectObject( oldFont );
}

void Facilities::drawRect( CDC* pDC, const CRect& cRect, COLORREF crColor, int iWidth ) const
{
	Facilities* pThis = (Facilities*) this;
	CPen* pPen = pThis->getPen( crColor, iWidth );
	CRect cRect2 = cRect;
	cRect2.DeflateRect( iWidth / 2, iWidth / 2 );

	CPen* pPreviousPen = pDC->SelectObject( pPen );
	pDC->MoveTo( cRect.left, cRect.top );
	pDC->LineTo( cRect2.right , cRect2.top );
	pDC->LineTo( cRect2.right , cRect2.bottom );
	pDC->LineTo( cRect2.left, cRect2.bottom );
	pDC->LineTo( cRect2.left, cRect2.top );
	pDC->SelectObject( pPreviousPen );
}

void Facilities::drawBox( CDC* pDC, const CRect& cRect, COLORREF crColor, int iDepth ) const
{
	Facilities* pThis = (Facilities*) this;

	int CR_DIVIDE = 50;
	for ( int i = 0 ; i < CR_DIVIDE ; i ++ ) {
		CRect cRect2 = cRect;
		cRect2.top = min( cRect.bottom, (long) ( cRect.top + ( cRect.Height() / CR_DIVIDE + 1 ) * i ) );
		cRect2.bottom = min( cRect.bottom, (long) ( cRect2.top + ( cRect.Height() / CR_DIVIDE + 1 ) ) );
		pDC->FillSolidRect( cRect2, ShiftColor( crColor, ( i - 20 ) * 2 ) );
	}

	CR_DIVIDE = 25;
	int CR_MULTI = (int) ( (double) 70 / iDepth );
	for ( int i = 0 ; i < iDepth ; i++ ) {
		CPen* pPrevoius = pDC->SelectObject( pThis->getPen( ShiftColor( crColor, - i * CR_MULTI ) ) );
		pDC->MoveTo( cRect.left + i, cRect.top + i );
		pDC->LineTo( cRect.right - i, cRect.top + i );
		for ( int j = 0 ; j < CR_DIVIDE ; j++ ) {
			pDC->SelectObject( pThis->getPen( ShiftColor( crColor, - i * CR_MULTI + i * CR_MULTI * 2 / CR_DIVIDE * ( j + 1 ) ) ) );
			pDC->LineTo( cRect.right - i, ( j == CR_DIVIDE - 1 ) ? cRect.bottom - i : cRect.top + i + ( cRect.Height() - i * 2 ) / CR_DIVIDE * ( j + 1 ) );
		}
		pDC->SelectObject( pThis->getPen( ShiftColor( crColor, i * 10 ) ) );
		pDC->LineTo( cRect.left + i, cRect.bottom - i );
		for ( int j = 0 ; j < CR_DIVIDE ; j++ ) {
			pDC->SelectObject( pThis->getPen( ShiftColor( crColor, i * CR_MULTI - i * CR_MULTI * 2 / CR_DIVIDE * ( j + 1 ) ) ) );
			pDC->LineTo( cRect.left + i, ( j == CR_DIVIDE - 1 ) ? cRect.top + i : cRect.bottom - i - ( cRect.Height() - i * 2 ) / CR_DIVIDE * ( j + 1 ) );
		}
		pDC->SelectObject( pPrevoius );
	}
}

}; // namespace DecoratorSDK