#pragma once
#include <string>
#include "CallLogger.h"

class CmdClient
	: public CallLogger
{
	const char   * m_stdo; // "stdo.tmp"
	const char   * m_stde; // "stde.tmp"
	bool         m_showCmdWindows;
	bool         m_redirectOutput;

	static const char * m_cs_checkout;
	static const char * m_cs_update;
	static const char * m_cs_lock;
	static const char * m_cs_unlock;
	static const char * m_cs_mkdir;
	static const char * m_cs_propset_needs_lock;
	static const char * m_cs_add;
	static const char * m_cs_commit;
	static const char * m_cs_info;
	static const char * m_cs_status;
	static const char * m_cs_cleanup;
	static const char * m_cs_resolved;

	std::string  m_svnPath;
public:

	CmdClient( bool p_showCmdWindows, bool p_redirectOutput);

	void         setLog                 ( bool p_val);
	void         setSvnPath             ( const std::string& p_svnPath);

	//tobe void         getCheckOutUserSVN     ( XmlObject * obj, std::string& user, bool& newfile);
	bool         getLatest              ( const std::string& p_dir);
	bool         isCheckedOutByElse     ( const std::string& p_file);
	bool         isLockedByUser         ( const std::string& p_path, std::string& p_holderUserName);
	bool         lightCheckOut          ( const std::string& p_url, const std::string& p_localDestPath); // this is used as svn checkout (in contrast with lock+checkout as in other versioning systems)
	bool         isVersioned            ( const std::string& p_file, bool p_isADir = false, bool p_suppressErrorMsg = false);
	bool         info                   ( const std::string& p_url, bool p_recursive, bool p_assembleInfoMsg, std::string& p_resultMsg, std::string& p_author, std::string& p_holder);
	bool         status                 ( const std::string& p_path, bool p_assembleStatMsg, std::string& p_resultMsg);
	bool         statusOnServer         ( const std::string& p_path, bool p_assembleStatMsg, std::string& p_resultMsg, bool *p_outOfDate);
	bool         cleanup                ( const std::string& p_path, bool p_assembleStatMsg, std::string& p_resultMsg);
	bool         resolve                ( const std::string& p_path, bool p_recursive);

	bool         lockableProp           ( const std::string& p_file);
	bool         applyLock              ( const std::string& p_file); // obsolete
	bool         removeLock             ( const std::string& p_file); // obsolete
	bool         tryLock                ( const std::string& p_file);
	bool         unLock                 ( const std::string& p_file);
	bool         bulkUnLock             ( const std::vector< std::string>& p_vect);
	//bool         mkdirWithUpdate        ( const std::string& p_url, const std::string& p_path, const std::string& p_dir); // obsolete
	bool         mkdirOnServer          ( const std::string& p_path);
	bool         add                    ( const std::string& p_file, bool p_recursive = false);
	bool         commit                 ( const std::string& p_dirOrFile, bool p_initialCommit = false, bool p_noUnlock = false);
	bool         update                 ( const std::string& p_dirOrFile);

protected:

	int          execute                ( const char * p);
	bool         check                  ( long p_code, bool p_suppressNonversionedErrorMsg = false);
	void         redirect               ( std::string& p_cmd);
	void         loadContents           ( const char * p_fname, std::string& p_fileContent);
	void         dumpContents           ( const char * p_fname, long p_type);

	DWORD        runSilent              ( const char* p_strFunct, const char* p_strstrParams, bool p_silent = true);
	std::string  command                ( const char * p_command, const char * p_par = 0);

	std::string  findLastChangeAuthor   ( const std::string& p_out);
	std::string  findLockOwner          ( const std::string& p_out);
	bool         isFileOutOfDate        ( const std::string& p_out, const std::string& p_filename);
};