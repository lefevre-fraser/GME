//################################################################################################
//
// DecoratorLib Utility Facility
//	DecoratorUtil.cpp
//
//################################################################################################

#include "StdAfx.h"
#include "DecoratorUtil.h"

#include "DecoratorDefs.h"
#include "MgaUtil.h"
#include "BitmapUtil.h"

static long stereotypeCharacterType = 1;

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
	createFont( FONT_LABEL,			"Arial", FW_NORMAL,		false,	18 );
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
	for ( std::map<CString,CPen*>::iterator it4 = m_mapPens.begin() ; it4 != m_mapPens.end() ; ++it4 ) {
		it4->second->DeleteObject();
		delete it4->second;
	}
	for ( std::map<CString,CBrush*>::iterator it5 = m_mapBrushes.begin() ; it5 != m_mapBrushes.end() ; ++it5 ) {
		it5->second->DeleteObject();
		delete it5->second;
	}
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
}

SFont* Facilities::getFont( int iFontKey ) const
{
	std::map<int,SFont*>::const_iterator it = m_mapFonts.find( iFontKey );
	return ( it == m_mapFonts.end() ) ? NULL : it->second;
}

CPen* Facilities::getPen( COLORREF crColor, int iWidth, bool bDashed )
{
	char chBuffer[ 30 ];
	sprintf( chBuffer, "%x-%d-%d", crColor, iWidth, bDashed );
	std::map<CString,CPen*>::iterator it = m_mapPens.find( CString( chBuffer ) );
	if ( it != m_mapPens.end() )
		return it->second;
	CPen* pPen = new CPen( bDashed ? PS_DOT : PS_SOLID, iWidth, crColor );
	m_mapPens.insert( std::map<CString,CPen*>::value_type( CString( chBuffer ), pPen ) );
	return pPen;
}

CBrush* Facilities::getBrush( COLORREF crColor )
{
	char chBuffer[ 30 ];
	sprintf( chBuffer, "%x", crColor );
	std::map<CString,CBrush*>::iterator it = m_mapBrushes.find( CString( chBuffer ) );
	if ( it != m_mapBrushes.end() )
		return it->second;
	CBrush* pBrush = new CBrush( crColor );
	m_mapBrushes.insert( std::map<CString,CBrush*>::value_type( CString( chBuffer ), pBrush ) );
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

void Facilities::drawCenteredText( CDC* pDC, const CString& strText, RECT r, CFont* pFont, COLORREF crColor ) const
{
	if (pFont == 0)
		return;
	CFont* oldFont = pDC->SelectObject( pFont );
	SetBkMode( pDC->m_hDC, TRANSPARENT );
	pDC->SetTextColor( pDC->IsPrinting() ? COLOR_BLACK : crColor );
	pDC->DrawText( strText, &r, DT_VCENTER | DT_SINGLELINE | DT_CENTER | DT_WORD_ELLIPSIS );
	pDC->SelectObject( oldFont );
}

void Facilities::drawLeftText( CDC* pDC, const CString& strText, RECT r, CFont* pFont, COLORREF crColor ) const
{
	if (pFont == 0)
		return;
	CFont* oldFont = pDC->SelectObject( pFont );
	SetBkMode( pDC->m_hDC, TRANSPARENT );
	pDC->SetTextColor( pDC->IsPrinting() ? COLOR_BLACK : crColor );
	pDC->DrawText( strText, &r, DT_VCENTER | DT_SINGLELINE | DT_LEFT );
	pDC->SelectObject( oldFont );
}

void Facilities::drawLeftMultiText( CDC *pDC, const CString& strText, RECT r, CFont* pFont, COLORREF crColor ) const
{
	if (pFont == 0)
		return;
	CFont* oldFont = pDC->SelectObject( pFont );
	SetBkMode( pDC->m_hDC, TRANSPARENT );
	pDC->SetTextColor( pDC->IsPrinting() ? COLOR_BLACK : crColor );
	pDC->DrawText( strText, &r, DT_VCENTER | DT_WORD_ELLIPSIS | DT_WORDBREAK | DT_LEFT );
	pDC->SelectObject( oldFont );
}


void Facilities::drawRightText( CDC *pDC, const CString& strText, RECT r, CFont* pFont, COLORREF crColor ) const
{
	if (pFont == 0)
		return;
	CFont* oldFont = pDC->SelectObject( pFont );
	SetBkMode( pDC->m_hDC, TRANSPARENT );
	pDC->SetTextColor( pDC->IsPrinting() ? COLOR_BLACK : crColor );
	pDC->DrawText( strText, &r, DT_VCENTER | DT_SINGLELINE | DT_RIGHT );
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
		pDC->FillSolidRect( cRect2, shiftColor( crColor, ( i - 20 ) * 2 ) );
	}

	CR_DIVIDE = 25;
	int CR_MULTI = (int) ( (double) 70 / iDepth );
	for ( int i = 0 ; i < iDepth ; i++ ) {
		CPen* pPrevoius = pDC->SelectObject( pThis->getPen( shiftColor( crColor, - i * CR_MULTI ) ) );
		pDC->MoveTo( cRect.left + i, cRect.top + i );
		pDC->LineTo( cRect.right - i, cRect.top + i );
		for ( int j = 0 ; j < CR_DIVIDE ; j++ ) {
			pDC->SelectObject( pThis->getPen( shiftColor( crColor, - i * CR_MULTI + i * CR_MULTI * 2 / CR_DIVIDE * ( j + 1 ) ) ) );
			pDC->LineTo( cRect.right - i, ( j == CR_DIVIDE - 1 ) ? cRect.bottom - i : cRect.top + i + ( cRect.Height() - i * 2 ) / CR_DIVIDE * ( j + 1 ) );
		}
		pDC->SelectObject( pThis->getPen( shiftColor( crColor, i * 10 ) ) );
		pDC->LineTo( cRect.left + i, cRect.bottom - i );
		for ( int j = 0 ; j < CR_DIVIDE ; j++ ) {
			pDC->SelectObject( pThis->getPen( shiftColor( crColor, i * CR_MULTI - i * CR_MULTI * 2 / CR_DIVIDE * ( j + 1 ) ) ) );
			pDC->LineTo( cRect.left + i, ( j == CR_DIVIDE - 1 ) ? cRect.top + i : cRect.bottom - i - ( cRect.Height() - i * 2 ) / CR_DIVIDE * ( j + 1 ) );
		}
		pDC->SelectObject( pPrevoius );
	}
}

void Facilities::draw3DBox( CDC* pDC, const CRect& rect, int borderSize, COLORREF brColor, COLORREF modelColor, bool special )
{
	if (special)
		borderSize = borderSize * 2;
	else
		borderSize++;

	CRect r = rect;
	r.DeflateRect( borderSize - 2, borderSize - 2 );
	pDC->FillSolidRect( r, modelColor );

	CPen* pen = getPen( brColor );
	CPen* oldpen = pDC->SelectObject( pen );

	CRect brect = r;
	CPen* hiPen = getPen( getLightBorderColor( modelColor ) );
	CPen* loPen = getPen( getDarkBorderColor( modelColor ) );
	for ( int i = 0; i < borderSize; i++ ) {
		pDC->MoveTo( CPoint( brect.left, brect.bottom ) );
		pDC->SelectObject( hiPen );
		pDC->LineTo( brect.TopLeft() );
		pDC->SelectObject( hiPen );
		pDC->LineTo( CPoint( brect.right, brect.top ) );
		pDC->SelectObject( loPen );
		pDC->LineTo( brect.BottomRight() );
		pDC->SelectObject( loPen );
		pDC->LineTo( CPoint( brect.left, brect.bottom ) );
		brect.InflateRect( 1, 1 );
	}

	pDC->SelectObject( pen );
	if ( !special )
		r.InflateRect(borderSize,borderSize);
	pDC->MoveTo( r.TopLeft() );
	pDC->LineTo( CPoint( r.right, r.top ) );
	pDC->LineTo( r.BottomRight() );
	pDC->LineTo( CPoint( r.left, r.bottom ) );
	pDC->LineTo( r.TopLeft() );
	if ( !special )
		r.DeflateRect( borderSize, borderSize );

	pDC->SelectObject( oldpen );
}

void Facilities::draw3DBox( CDC* pDC, const CRect& rect, COLORREF brColor, COLORREF color, bool isType)
{
	draw3DBox( pDC, rect, GME_3D_BORDER_SIZE, brColor, color, isType );
}

void Facilities::drawFlatBox( CDC* pDC, const CRect& rect, COLORREF brColor, COLORREF color )
{
	draw3DBox( pDC, rect, 0, brColor, color );
}

COLORREF Facilities::shiftColor( COLORREF crColor, int iShift ) const
{
	int iR = GetRValue( crColor );
	int iG = GetGValue( crColor );
	int iB = GetBValue( crColor );
	iR = min( max( iR + iShift, 0 ), 255 );
	iG = min( max( iG + iShift, 0 ), 255 );
	iB = min( max( iB + iShift, 0 ), 255 );
	return RGB( iR, iG, iB );
}

COLORREF Facilities::getLightBorderColor(COLORREF color) const
{
	int b = (color & 0xff0000) >> 16;
	int g = (color & 0xff00) >> 8;
	int r = (color & 0xff);
	r = min(0xff,r + 0x40);
	g = min(0xff,g + 0x40);
	b = min(0xff,b + 0x40);
	return RGB(r,g,b);
}

COLORREF Facilities::getDarkBorderColor(COLORREF color) const
{
	int b = (color & 0xff0000) >> 16;
	int g = (color & 0xff00) >> 8;
	int r = (color & 0xff);
	r = max(0,r - 0x40);
	g = max(0,g - 0x40);
	b = max(0,b - 0x40);
	return RGB(r,g,b);
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

}; // namespace DecoratorSDK