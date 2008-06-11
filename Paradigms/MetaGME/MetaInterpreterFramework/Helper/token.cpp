#include "stdafx.h"
#include "token.h"

void Token::split( const std::string& source, const std::string& delimiter, std::vector< std::string> & result)
{
	if ( delimiter.length() <= 0) return;
	unsigned int curr_token_start = 0;
	unsigned int curr_token_end = source.find( delimiter, curr_token_start);

	while ( curr_token_end != std::string::npos) // more delimiters found
	{
		result.push_back( source.substr( curr_token_start, curr_token_end - curr_token_start));
		curr_token_start = curr_token_end + delimiter.length();
		curr_token_end = source.find( delimiter, curr_token_start);
	}
	
	if ( curr_token_end == std::string::npos) // no more delimiters found
		result.push_back( source.substr( curr_token_start, source.length() - curr_token_start));

}

