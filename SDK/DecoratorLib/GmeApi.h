#pragma once

#include "GmeVersion.h"
#if defined(GME_VERSION_MAJOR) && GME_VERSION_MAJOR < 11
#if defined(LIBCOMPILE)
#import "libid:9E9AAACF-28B8-11D3-B36C-0060082DF884" // CORELib
#import "libid:0ADEEC71-D83A-11D3-B36B-005004D38590" //METALib
#import "libid:270B4F86-B17C-11D3-9AD1-00AA00B6FE26" //MGALib
#import "libid:461F30AE-3BF0-11D4-B3F0-005004D38590" //MGAUTILLib

#define get_Kind get_kind
#define get_Referred get_referred
using MGAUTILLib::IMgaRegistrar;
typedef MGAUTILLib::edgesmoothmode_enum edgesmoothmode_enum;
typedef MGAUTILLib::fontsmoothmode_enum fontsmoothmode_enum;
using MGAUTILLib::REGACCESS_USER;
using MGAUTILLib::REGACCESS_BOTH;
// n.b. no_namespace is important, since Decorators will use midl which doesn't produce namespaces
#import "libid:0ADEEC71-D83A-11D3-B36B-005004CC8592" no_namespace, raw_interfaces_only //GmeLib
typedef unsigned long feature_code;

const unsigned long F_RESIZABLE	= 1<<0;
const unsigned long	F_MOUSEEVENTS =	1<<1;
const unsigned long	F_HASLABEL =	1<<2;
const unsigned long	F_HASSTATE = 1<<3;
const unsigned long	F_HASPORTS = 1<<4;
const unsigned long	F_ANIMATION = 1<<5;
const unsigned long	F_IMGPATH = 1<<6;
const unsigned long	F_RESIZEAFTERMOD = 1<<7;
using MGALib::OBJECT_EXISTS;
using MGALib::OBJECT_DELETED;
using MGALib::OBJECT_ZOMBIE;
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
#else
#include "DecoratorLib.h"

#endif
#else
#include "Gme.h"
#include "Mga.h"
#include "MgaUtil.h"
#endif
