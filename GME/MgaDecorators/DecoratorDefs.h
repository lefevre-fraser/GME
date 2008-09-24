//################################################################################################
//
// Mga Decorator Base
//	DecoratorDefs.h
//
//################################################################################################

#ifndef DecoratorDefs_h
#define DecoratorDefs_h

#pragma warning( disable : 4786 )

#include "StdAfx.h"
#include "resource.h"
#include "..\Gme\GmeStd.h"

//################################################################################################
//
// IMPORTANT :
// use Compiler Definition OLD_DECORATOR_LOOKANDFEEL to see Previous Decorator Look & Feel
//
//################################################################################################

namespace Decorator
{
	enum ELocation {
		L_NORTH			= GME_NORTH,
		L_SOUTH			= GME_SOUTH,
		L_WEST			= GME_WEST,
		L_EAST			= GME_EAST,
		L_SOUTHWEST		= GME_SOUTHWEST,
		L_SOUTHEAST		= GME_SOUTHEAST,
		L_NORTHWEST		= GME_NORTHWEST,
		L_NORTHEAST		= GME_NORTHEAST,
		L_CENTER		= GME_CENTER
	};

	enum EPrefStatus {
		PS_HERE			= 0,
		PS_META			= -1,
		PS_INHERITED	= 1,
		PS_UNDEFINED	= 2
	};

	static const char* PREF_LABELLOCATION 			= "namePosition";
	static const char* PREF_ICON					= "icon";
	static const char* PREF_PORTICON				= "porticon";
	static const char* PREF_SUBTYPEICON				= "subTypeIcon";
	static const char* PREF_INSTANCEICON			= "instanceIcon";
	static const char* PREF_NULLREFICON				= "nullRefIcon";
	static const char* PREF_OVERLAYCOLOR			= "color";
	static const char* PREF_LABELCOLOR				= "nameColor";
	static const char* PREF_PORTLABELCOLOR			= "portColor";
	static const char* PREF_PORTLABELINSIDE 		= "portLabelInside";
	static const char* PREF_TYPESHOWN				= "isTypeShown";
	static const char* PREF_TYPEINFOSHOWN			= "isTypeInfoShown";
	static const char* PREF_PORTLABELLENGTH			= "portLabelLength";
	static const char* PREF_BORDERCOLOR				= "borderColor";

	static const char* PREF_LABELFONT				= "labelFont";
	static const char* PREF_LABELLENGTH				= "labelLength";

	static const char* PREF_ICONDEFAULT				= "iconDefault";
	static const char* PREF_TILESDEFAULT			= "tilesDefault";
	static const char* PREF_TILESUNDEF				= "tilesUndefined";

	static const char* PREF_TILES					= "tiles";
	static const char* PREF_LABEL					= "label";

	static const char* PREF_LABELWRAP				= "nameWrap";
	static const char* PREF_LABELENABLED			= "isNameEnabled";

	static const char* PREF_VIOLATED				= "isViolated";

	static const char* PREF_PREFERREDSIZE			= "preferredSize";

	static const int FONT_LABEL 	= 0;
	static const int FONT_PORT 	= 1;
	static const int FONT_TYPE 	= 2;
	static const int FONT_PORT_OUTSIDE 	= 3;

	static const int GAP_LABEL 	= 2;
	static const int GAP_PORT = 3;
	static const int GAP_XMODELPORT = 4;
	static const int GAP_YMODELPORT = 8;
	static const int GAP_PORTLABEL = 20;

	static const COLORREF COLOR_BLACK 			= RGB( 0x00, 0x00, 0x00 );
	static const COLORREF COLOR_GRAY 			= RGB( 0xB0, 0xB0, 0xB0 );
	static const COLORREF COLOR_LIGHTGRAY		= RGB( 0xF3, 0xF3, 0xF3 );
	static const COLORREF COLOR_RED 			= RGB( 0xFF, 0x00, 0x00 );

	static const int MAX_LABEL_LENGTH		= 64;
	static const int MAX_TYPE_LENGTH		= 90;
	static const int MAX_PORT_LENGTH		= 3;

	static const int WIDTH_MODEL			= 113;
	static const int HEIGHT_MODEL			= 71;
	static const int WIDTH_PORT				= 10;
	static const int HEIGHT_PORT			= 11;
	static const int WIDTH_BORDERVIOLATION	= 2;
	static const int WIDTH_BORDERMODELBOX	= 7;
	static const int WIDTH_MODELSIDE		= 100;

	static const char* TILE_ATOMDEFAULT		= "$TILE$Atom_Default";
	static const char* TILE_MODELDEFAULT	= "$TILE$Model_Default";
	static const char* TILE_PORTDEFAULT		= "$TILE$Port_Default";

	static const char* CTX_MENU_STR_RENAME			= "Rename";
	static const char* CTX_MENU_STR_RESETSIZE		= "Reset to original size";
	static const unsigned int CTX_MENU_ID_RENAME	= DECORATOR_CTX_MENU_MINID + 0;
	static const unsigned int CTX_MENU_ID_RESETSIZE	= DECORATOR_CTX_MENU_MINID + 1;

	struct SFont
	{
		CFont*		pFont;
		int			iSize;
		CString		strName;
		bool		bBold;

		SFont( const CString& _strName, int _iSize, bool _bBold )
			: pFont( NULL ), strName( _strName ), iSize( _iSize ), bBold( _bBold )
		{
		}
	};

	struct SRGB
	{
		int r;
		int g;
		int b;

		SRGB( int _r, int _g, int _b )
			: r( _r ), g( _g ), b( _b )
		{
		}
	};

	struct SHSB
	{
		int h;
		int s;
		int b;

		SHSB( int _h, int _s, int _b )
			: h( _h ), s( _s ), b( _b )
		{
		}
	};

	SRGB 		CRtoRGB( COLORREF rc );
	SHSB 		CRtoHSB( COLORREF rc );
	SRGB 		HSBtoRGB( SHSB hsb );
	COLORREF 	HSBtoCR( SHSB hsb );
	SHSB 		RGBtoHSB( SRGB rgb );
	COLORREF 	RGBtoCR( SRGB rgb );

	CString createResString( int iID );

}; // namespace Decorator

#endif // DecoratorDefs_h