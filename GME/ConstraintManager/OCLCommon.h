//###############################################################################################################################################
//
//	Object Constraint Language Generic Manager
//	OCLCommon.h
//
//###############################################################################################################################################

#ifndef OCLCommon_h
#define OCLCommon_h

/*
in case of GME STLport is used (under VC 7.x)
in case of UDM MSVC's own STL
*/

#ifndef FOR_GME
#ifdef _WIN32
#if (_MSC_VER == 1200)
#include <stl_user_config.h>
#endif
#endif
#endif
#include <vector>
#include <map>
#include <set>
#include <string>
#include "stdio.h"

#define TABSTR "    "

typedef std::vector< std::string >	StringVector;
typedef StringVector			TypeSeq;

bool operator!=( const std::string& str1, const std::string& str2 );

struct Position
{
	int iLine;
	int iColumn;
};

std::string& Trim( std::string& strIn );

typedef std::map< int , Position > PositionMap;

namespace OclCommon {

	void Convert( const TypeSeq& ts, std::string& s );
	int Convert( const std::string& s, TypeSeq& ts );

}; // namespace OclCommon

#endif //OCLCommon_h
