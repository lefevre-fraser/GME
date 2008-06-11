#ifndef TOKEN_H
#define TOKEN_H

#include "string"
#include "vector"


class Token
{
public:
	void split( const std::string& source, const std::string& delimiter, std::vector< std::string> & addIt);

};

#endif // TOKEN_H