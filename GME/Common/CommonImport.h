// Header file for missing bits from MIDL-generated .hs when using #import
#include "comdef.h"

typedef short metaid_type;
typedef long objid_type;
typedef short attrid_type;
typedef unsigned char valtype_type;
typedef unsigned char locking_type;
typedef short lockval_type;
typedef VARIANT guid_type;

typedef long metaref_type;

typedef BSTR ID_type;


// From InterfaceColl.h

template<class COLL>
struct TypeName_MgaColl2Elem {
	typedef IUnknown element_type;
	typedef IUnknown collection_type;
};
template<class ELEM>
struct TypeName_MgaElem2Coll {
	typedef IUnknown element_type;
	typedef IUnknown collection_type;
};


#define _MGA_COLLECTION_(NAME) _MGA_COLLECTION2_(NAME, NAME##s)
#define _MGA_COLLECTION2_(IMgaX, IMgaXs) \
struct IMgaX; struct IMgaXs; \
template<> struct ::TypeName_MgaColl2Elem<IMgaXs> \
  { typedef IMgaXs collection_type; typedef IMgaX element_type; }; \
template<> struct ::TypeName_MgaElem2Coll<IMgaX> \
 { typedef IMgaXs collection_type; typedef IMgaX element_type; };

_MGA_COLLECTION_(ICoreMetaObject)
_MGA_COLLECTION_(ICoreMetaAttribute)
_MGA_COLLECTION_(ICoreObject)
_MGA_COLLECTION_(ICoreAttribute)

_MGA_COLLECTION_(IMgaMetaAspect)
_MGA_COLLECTION_(IMgaMetaRole)
_MGA_COLLECTION_(IMgaMetaFCO)
_MGA_COLLECTION_(IMgaMetaAttribute)
_MGA_COLLECTION_(IMgaMetaFolder)
_MGA_COLLECTION_(IMgaMetaPointerSpec)
_MGA_COLLECTION_(IMgaMetaRegNode)
_MGA_COLLECTION_(IMgaConstraint)
_MGA_COLLECTION_(IMgaMetaPart)
_MGA_COLLECTION_(IMgaMetaModel)
_MGA_COLLECTION_(IMgaMetaConnJoint)
_MGA_COLLECTION_(IMgaMetaPointerItem)
_MGA_COLLECTION_(IMgaMetaEnumItem)
_MGA_COLLECTION_(IMgaFolder)
_MGA_COLLECTION_(IMgaFCO)
_MGA_COLLECTION_(IMgaAttribute)
_MGA_COLLECTION_(IMgaPart)
_MGA_COLLECTION_(IMgaConnPoint)
_MGA_COLLECTION_(IMgaRegNode)
_MGA_COLLECTION_(IMgaAddOn)
_MGA_COLLECTION2_(IMgaTerritory, IMgaTerritories)
_MGA_COLLECTION_(IMgaComponent)
_MGA_COLLECTION_(IMgaClient)
_MGA_COLLECTION_(IMgaObject)

#define TYPENAME_COLL2ELEM(COLL) typename ::TypeName_MgaColl2Elem<COLL>::element_type
#define TYPENAME_ELEM2COLL(ELEM) typename ::TypeName_MgaElem2Coll<ELEM>::collection_type


typedef 
enum mgaerrors
    {	E_MGA_NOT_IMPLEMENTED	= 0x87650000,
	E_MGA_NOT_SUPPORTED	= 0x87650001,
	E_MGA_MODULE_INCOMPATIBILITY	= 0x87650010,
	E_MGA_PARADIGM_NOTREG	= 0x87650011,
	E_MGA_PARADIGM_INVALID	= 0x87650012,
	E_MGA_COMPONENT_ERROR	= 0x87650013,
	E_MGA_DATA_INCONSISTENCY	= 0x87650021,
	E_MGA_META_INCOMPATIBILITY	= 0x87650022,
	E_MGA_PROJECT_OPEN	= 0x87650031,
	E_MGA_PROJECT_NOT_OPEN	= 0x87650032,
	E_MGA_READ_ONLY_ACCESS	= 0x87650033,
	E_MGA_NOT_IN_TERRITORY	= 0x87650034,
	E_MGA_NOT_IN_TRANSACTION	= 0x87650035,
	E_MGA_ALREADY_IN_TRANSACTION	= 0x87650036,
	E_MGA_MUST_ABORT	= 0x87650037,
	E_MGA_TARGET_DESTROYED	= 0x87650038,
	E_MGA_FOREIGN_PROJECT	= 0x87650041,
	E_MGA_FOREIGN_OBJECT	= 0x87650042,
	E_MGA_OBJECT_DELETED	= 0x87650051,
	E_MGA_OBJECT_ZOMBIE	= 0x87650052,
	E_MGA_ZOMBIE_NOPROJECT	= 0x87650053,
	E_MGA_ZOMBIE_CLOSED_PROJECT	= 0x87650054,
	E_MGA_INVALID_ARG	= 0x87650060,
	E_MGA_ARG_RANGE	= 0x87650061,
	E_MGA_INPTR_NULL	= 0x87650062,
	E_MGA_OUTPTR_NONEMPTY	= 0x87650063,
	E_MGA_OUTPTR_NULL	= 0x87650064,
	E_MGA_NAME_NOT_FOUND	= 0x87650070,
	E_MGA_NAME_DUPLICATE	= 0x87650071,
	E_MGA_META_VIOLATION	= 0x87650072,
	E_MGA_NOT_CHANGEABLE	= 0x87650073,
	E_MGA_OP_REFUSED	= 0x87650074,
	E_MGA_LIBOBJECT	= 0x87650075,
	E_META_INVALIDATTR	= 0x87650080,
	E_META_INVALIDASPECT	= 0x87650081,
	E_MGA_ACCESS_TYPE	= 0x87650082,
	E_MGA_BAD_ENUMVALUE	= 0x87650083,
	E_MGA_REFPORTS_USED	= 0x87650131,
	E_MGA_VIRTUAL_NODE	= 0x87650136,
	E_MGA_BAD_POSITIONVALUE	= 0x87650137,
	E_MGA_ROOTFCO	= 0x87650138,
	E_MGA_NOT_ROOTOBJECT	= 0x87650138,
	E_MGA_BAD_COLLENGTH	= 0x87650140,
	E_MGA_INVALID_ROLE	= 0x87650142,
	E_MGA_BAD_ID	= 0x87650143,
	E_MGA_NOT_DERIVABLE	= 0x87650144,
	E_MGA_OBJECT_NOT_MEMBER	= 0x87650145,
	E_MGA_NOT_CONNECTIBLE	= 0x87650146,
	E_MGA_NO_ROLE	= 0x87650147,
	E_MGA_CONNROLE_USED	= 0x87650148,
	E_MGA_NOT_DERIVED	= 0x87650149,
	E_MGA_NOT_INSTANCE	= 0x87650150,
	E_MGA_INSTANCE	= 0x87650151,
	E_MGA_REFERENCE_EXPECTED	= 0x87650152,
	E_MGA_FILTERFORMAT	= 0x87650153,
	E_MGA_GEN_OUT_OF_SPACE	= 0x87650154,
	E_MGA_INVALID_TARGET	= 0x87650155,
	E_MGA_LONG_DERIVCHAIN	= 0x87650156,
	E_MGA_LIB_DIFF	= 0x87650157,
	E_MGA_BAD_MASKVALUE	= 0x87650170,
	E_MGA_CONSTRAINT_VIOLATION	= 0x87657fff,
	E_MGA_ERRCODE_ERROR	= 0x87658000
    } 	mgaerrors;

enum mgautil_error
    {	E_MGAUTIL_COMPONENTPROXY_NOTINITIALIZED	= 0x80737001
    } 	mgautil_error;


typedef unsigned long feature_code;
const unsigned long F_RESIZABLE	= 1<<0;
const unsigned long	F_MOUSEEVENTS =	1<<1;
const unsigned long	F_HASLABEL =	1<<2;
const unsigned long	F_HASSTATE = 1<<3;
const unsigned long	F_HASPORTS = 1<<4;
const unsigned long	F_ANIMATION = 1<<5;
const unsigned long	F_IMGPATH = 1<<6;
const unsigned long	F_RESIZEAFTERMOD = 1<<7;


typedef enum decorator_error {
	E_DECORATOR_UNKNOWN_PARAMETER	=	0x80737001,
	E_DECORATOR_INIT_WITH_NULL	=	0x80737002,
	E_DECORATOR_UNINITIALIZED	=	0x80737003,
	E_DECORATOR_LOCISNOTSET = 0x80737004,
	E_DECORATOR_PORTNOTFOUND	=	0x80737005,
	E_DECORATOR_USING_DEPRECATED_FUNCTION	= 0x80737006,
	E_DECORATOR_NOT_IMPLEMENTED	= 0x80737007,
	S_DECORATOR_EVENT_HANDLED	= 0x00737001,
	S_DECORATOR_EVENT_NOT_HANDLED	= 0x00737002
} decorator_error;


typedef enum component_startmode_enum {
	GME_MAIN_START		= 0,
	GME_BROWSER_START	= 1,
	GME_CONTEXT_START	= 2,
	GME_EMBEDDED_START  = 3,
	GME_MENU_START		= 16,
	GME_BGCONTEXT_START = 18,
	GME_ICON_START		= 32, 
	METAMODEL_CHECK_SYNTAX  = 101,
	CONSTMGR_SHOW_CONSTRAINTS = 102,
	GME_SILENT_MODE		= 128
} component_startmode_enum;

typedef enum inserttype_enum {
	ADDITION = 0,
	MERGE    = 1
} inserttype_enum;
