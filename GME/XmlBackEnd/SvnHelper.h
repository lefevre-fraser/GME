#pragma once

#include <string>

class CSvnHelper
{
public:
	CSvnHelper(void);
	~CSvnHelper(void);
	
	static void invokeInfo  ( const std::string& p_url,       bool p_apiAccess, bool p_recursive);
	static void invokeStatus( const std::string& p_localPath, bool p_apiAccess);
	static void invokeCleanUp( const std::string& p_localPath, bool p_apiAccess);
	static void invokeResolve( const std::string& p_localPath, bool p_apiAccess, bool p_recursive);
	static void invokeCheckout( const std::string& p_url, const std::string& p_localPath, bool p_apiAccess);
	static void invokeCommit( const std::string& p_localPath, bool p_apiAccess);
	static void invokeUpdate( const std::string& p_localPath, bool p_apiAccess);
	static void invokeLock( const std::string& p_localPath, bool p_apiAccess);
	static void invokeUnlock( const std::string& p_localPath, bool p_apiAccess);
	static void invokeTestSubDirs();
};
