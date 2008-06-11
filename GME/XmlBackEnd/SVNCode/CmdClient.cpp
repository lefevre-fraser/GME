#include "StdAfx.h"
#include "CmdClient.h"
#include "FileHelp.h"
#include "MsgConsole.h"
#include <fstream>
#include <direct.h>

// statics
const char * CmdClient::m_cs_checkout            = "co"; // a light checkout, with no consequences on locks!
const char * CmdClient::m_cs_update              = "update";
const char * CmdClient::m_cs_lock                = "lock";
const char * CmdClient::m_cs_unlock              = "unlock";
const char * CmdClient::m_cs_mkdir               = "mkdir";
const char * CmdClient::m_cs_propset_needs_lock  = "propset svn:needs-lock 'na'";
const char * CmdClient::m_cs_add                 = "add";
const char * CmdClient::m_cs_commit              = "commit";
const char * CmdClient::m_cs_info                = "info";
const char * CmdClient::m_cs_status              = "status";
const char * CmdClient::m_cs_cleanup             = "cleanup";
const char * CmdClient::m_cs_resolved            = "resolved";

CmdClient::CmdClient( bool p_showCmdWindows, bool p_redirectOutput)
	: m_stdo( "stdo.tmp")
	, m_stde( "stde.tmp")
	, m_showCmdWindows( p_showCmdWindows)
	, m_redirectOutput( p_redirectOutput)
	, m_svnPath( "svn")
	, CallLogger()
{
}

std::string CmdClient::command( const char * p_command, const char * p_par /*= 0*/)
{
	return m_svnPath + " " + p_command + " " + (p_par? p_par : "") + " ";
}

void CmdClient::setSvnPath( const std::string& p_svnPath)
{
	m_svnPath = p_svnPath;
}

//void CmdClient::getCheckOutUserSVN(XmlObject * obj, string& user, bool& newfile)
//{
//	ASSERT( m_sourceControl == SC_SUBVERSION );
//	ASSERT( obj->isContainer() );
//	ASSERT( m_svnByAPI);
//
//	if( m_svnByAPI)
//	{
//		std::string fname;
//		getContainerFileName( obj, fname, true);
//		//char buff[100];
//		//bool ret = m_svn->isLockedBy( fname.c_str(), &buff[0], 100);
//		//if( ret)
//		//	user = buff;
//		bool ret = m_svn->isLockedByUser( fname, user);
//		newfile = false; // todo
//	}
//}

bool CmdClient::isCheckedOutByElse( const std::string& p_file)
{
	//ASSERT( isVersionedInSVN( p_file));
	if( !FileHelp::isFileReadOnly( p_file)) 
		return false; // file is svnlocked by us

	if( applyLock( p_file))
	{
		// success: was not checked out by somebody else
		if( removeLock( p_file))
			return false;
	}
	return true;
}

bool CmdClient::isLockedByUser( const std::string& p_path/*, std::string& p_lastAuthor*/, std::string& p_holderUserName)
{
	// ret val is always true
	// p_username !empty indicates whether is held or not
	return info( p_path, false /*recursive*/, false /*assemble inf msg*/, std::string() /*msg*/, std::string() /*p_lastAuthor*/, p_holderUserName);
}

bool CmdClient::lightCheckOut( const std::string& p_url, const std::string& p_localDestPath)
{
	std::string cmd = command( m_cs_checkout) + p_url + " " + p_localDestPath;
	redirect( cmd);

	int r;
	r = execute( cmd.c_str());

	return check( r);
}

bool CmdClient::getLatest( const std::string& p_dir)
{
	int r0;
	r0 = _chdir( p_dir.c_str());
	check( r0 );

	// what about a clean?, or what about the first time this is called: 'svn checkout' should be used
	std::string cmd = command( m_cs_update) + " . ";
	redirect( cmd);

	int r;
	r = execute( cmd.c_str());

	return check( r);
}

// obsolete
bool CmdClient::applyLock( const std::string& p_file)
{
	std::string cmd = command( m_cs_lock) + p_file;
	redirect( cmd);

	int r;
	r = execute( cmd.c_str());

	return check( r);
}

bool CmdClient::removeLock( const std::string& p_file)
{
	std::string cmd = command( m_cs_unlock) + p_file;
	redirect( cmd);

	int r;
	r = execute( cmd.c_str());

	return check( r);
}

bool CmdClient::tryLock( const std::string& p_file)
{
	// is locked already? // optimization, but might mislead
	WIN32_FILE_ATTRIBUTE_DATA attr;
	BOOL res = GetFileAttributesEx( p_file.c_str(), GetFileExInfoStandard, &attr );
	if( (attr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY //non-dir
	 && (attr.dwFileAttributes & FILE_ATTRIBUTE_READONLY)  != FILE_ATTRIBUTE_READONLY) //non-read-only
		return true; // lock present

	// process with lock command
	std::string cmd = command( m_cs_lock) + p_file;
	redirect( cmd);

	int r;
	r = execute( cmd.c_str());

	return check( r);
}

bool CmdClient::unLock( const std::string& p_file)
{
	// is unlocked already? // optimization, but might mislead
	WIN32_FILE_ATTRIBUTE_DATA attr;
	BOOL res = GetFileAttributesEx( p_file.c_str(), GetFileExInfoStandard, &attr );
	if( (attr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY //non-dir
	 && (attr.dwFileAttributes & FILE_ATTRIBUTE_READONLY)  == FILE_ATTRIBUTE_READONLY) //read-only
		return true; // presumably unlocked, that's why is read-only

	// process with unlock command
	std::string cmd = command( m_cs_unlock) + p_file;
	redirect( cmd);

	int r;
	r = execute( cmd.c_str());

	return check( r);
}

bool CmdClient::bulkUnLock( const std::vector< std::string>& p_vect)
{
	std::string files_concat;
	for( int i = 0; i < p_vect.size(); ++i)
	{
		if( !files_concat.empty())
			files_concat += " ";
		files_concat += p_vect[i];
	}

	// process with unlock command (several target files)
	std::string cmd = command( m_cs_unlock) + files_concat;
	redirect( cmd);

	int r;
	r = execute( cmd.c_str());

	return check( r);
}

bool CmdClient::mkdirOnServer( const std::string& p_path)
{
	// creates and commits the versioned directory on the server
	std::string cmd = command( m_cs_mkdir) + p_path + " -m \"initial checkin\"";
	redirect( cmd);

	int r;
	r = execute( cmd.c_str());

	return check( r );
}

// obsolete
//bool CmdClient::mkdirWithUpdate( const std::string& p_url, const std::string& p_path, const std::string& p_dir)
//{
//	// creates and commits the versioned directory on the server
//	std::string cmd = command( m_cs_mkdir);
//	cmd += p_url + "/" + p_dir + " -m \"initial checkin\"";
//	redirect( cmd);
//
//	int r = execute( cmd.c_str());
//	bool err = check( r );
//	
//	// check out a working copy to local directory
//	//r = _chdir( m_folderPath);
//	//check( r );
//
//	// svn checkout URL PATH form can be used also e.g.:
//	// svn checkout svn://localhost/svn_02 f:\t\at\an\svn_02
//	std::string cmd2 = command( m_cs_checkout);
//	cmd2 += p_url + '/' + p_dir + ' ' + p_path;
//	redirect( cmd2);
//
//	r = execute( cmd2.c_str());
//	bool err2 = check( r);
//
//	// change into the newly created directory
//	r = _chdir( p_path.c_str());
//
//	return err && err2 && check( r);
//}

bool CmdClient::lockableProp( const std::string& p_file)
{
	// svn propset svn:needs-lock 'anyvalue' <file>
	std::string cmd = command( m_cs_propset_needs_lock) + p_file;

	redirect( cmd);

	int r;
	r = execute( cmd.c_str());

	return check( r);
}

bool CmdClient::add( const std::string& p_entity, bool p_recursive /* = false*/)
{
	std::string cmd = command( m_cs_add) + (p_recursive?"": " -N ") + p_entity;
	//std::string cmt_line( "svn commit ");
	//cmt_line.append( p_entity);
	redirect( cmd);

	int r;
	r = execute( cmd.c_str());
	//r2 = execute( cmt_line.c_str());

	return check( r);
}


bool CmdClient::commit( const std::string& p_dirOrFile, bool p_initialCommit /* = false*/, bool p_noUnlock /* = false*/)
{
	if( !p_initialCommit && !p_noUnlock && FileHelp::isFile( p_dirOrFile) && !FileHelp::isFileReadOnly( p_dirOrFile))
		removeLock( p_dirOrFile); // commit does not always remove lock, [at least when diff is empty]

	std::string cmd = command( m_cs_commit) + " -m \"ok\" " + p_dirOrFile;

	if( p_noUnlock) 
		cmd.append( " --no-unlock ");

	redirect( cmd);

	int r;
	r = execute( cmd.c_str());

	return check( r);
}

bool CmdClient::update( const std::string& p_dirOrFile)
{
	std::string cmd = command( m_cs_update) + p_dirOrFile;
	redirect( cmd);

	int r;
	r = execute( cmd.c_str());

	return check( r);
}

bool CmdClient::isVersioned( const std::string& p_file, bool p_isADir /*= false*/, bool p_suppressErrorMsg /*=false*/)
{
	if( p_isADir)
	{
		if( FileHelp::isFile( p_file))
		{
			ASSERT( 0); // it should be a directory
			return false;
		}
	}
	else
	{
		// may be redundant sometimes, but needed when called from makeSureFileExistsInVerSys
		if( !FileHelp::fileExist( p_file)) // the file even not exists not even a file
			return false;
	}

	//std::string status_line = "svn status " + p_file;
	std::string cmd = command( m_cs_info) + p_file;
	redirect( cmd);
	// error given in case file not committed: <<filename>>.txt:  (Not a versioned resource)

	int r;
	r = execute( cmd.c_str());

	return check( r);
}

#if(0)
// this is like isVersioned, but expects an element not be versioned, thus
// won't dump any error message onto the console.
// In other words its default behaviour is a little different.
bool CmdClient::isNotVersioned( const std::string& p_fileUrl, bool p_isADir = false, bool p_suppressErrorMsg = false)
{
	if( p_isADir)
	{
		if( FileHelp::isFile( p_file))
		{
			ASSERT( 0); // it should be a directory
			return false;
		}
	}
	else
	{
		// file doesn't exist, means that is not versioned either
		if( !FileHelp::fileExist( p_file))
			return true;
	}

	std::string cmd = command( m_cs_info) + p_file;
	redirect( cmd);
	// error given in case file not committed: <<filename>>.txt:  (Not a versioned resource)

	int r;
	r = execute( cmd.c_str());

	if( r != 0) // error executing it
		return true;

	if( p_suppressErrorMsg)
	std::string error_msg;
	loadContents( m_stde, error_msg); // std out file
	if( !error_msg.empty())
		return true; // if errors => not versioned

	return false;
}
#endif

bool CmdClient::info( const std::string& p_url, bool p_recursive, bool p_assembleInfoMsg, std::string& p_resultMsg, std::string& p_author, std::string& p_holder)
{
	std::string cmd = command( m_cs_info) + p_url;
	redirect( cmd);

	int r;
	r = execute( cmd.c_str());
	
	std::string  fc;

	loadContents( m_stdo, fc); // std out file

	//p_author = m_vssUser;                           // fooling the author consistency check
	p_author.clear();                               // clear the in params
	p_holder.clear();

	p_author = findLastChangeAuthor( fc);
	p_holder = findLockOwner( fc);

	if( p_assembleInfoMsg)
	{
		p_resultMsg.append( "\nOutput:\n");
		p_resultMsg.append( fc);

		p_resultMsg.append( "\nError (if any):\n");
		loadContents( m_stde, fc); // std error file
		p_resultMsg.append( fc);
	}

	return true; // always true, since the stde is captured and shown
}

bool CmdClient::status( const std::string& p_path, bool p_assembleStatMsg, std::string& p_resultMsg)
{
	std::string cmd = command( m_cs_status) + p_path;
	redirect( cmd);

	int r;
	r = execute( cmd.c_str());
	
	std::string  fc;

	loadContents( m_stdo, fc); // std out file

	if( p_assembleStatMsg)
	{
		p_resultMsg.append( "\nOutput:\n");
		p_resultMsg.append( fc);

		p_resultMsg.append( "\nError (if any):\n");
		loadContents( m_stde, fc); // std error file
		p_resultMsg.append( fc);
	}

	return true; // always true, since the stde is captured and shown
}

bool CmdClient::statusOnServer( const std::string& p_path, bool p_assembleStatMsg, std::string& p_resultMsg, bool *p_outOfDate)
{
	std::string cmd = command( m_cs_status) + " --show-updates " + p_path; // ! compares local copy to the latest version on the server
	redirect( cmd);

	int r;
	r = execute( cmd.c_str());
	
	std::string  fc;

	loadContents( m_stdo, fc); // std out file

	if( p_outOfDate)
		*p_outOfDate = isFileOutOfDate( fc, p_path);           // parse/analyze content

	if( p_assembleStatMsg)
	{
		p_resultMsg.append( "\nOutput:\n");
		p_resultMsg.append( fc);

		p_resultMsg.append( "\nError (if any):\n");
		loadContents( m_stde, fc); // std error file
		p_resultMsg.append( fc);
	}

	return true; // always true, since the stde is captured and shown
}

bool CmdClient::cleanup( const std::string& p_path, bool p_assembleStatMsg, std::string& p_resultMsg)
{
	std::string cmd = command( m_cs_cleanup) + p_path;
	redirect( cmd);

	int r;
	r = execute( cmd.c_str());
	
	std::string  fc;

	loadContents( m_stdo, fc); // std out file

	if( p_assembleStatMsg)
	{
		p_resultMsg.append( "\nOutput:\n");
		p_resultMsg.append( fc);

		p_resultMsg.append( "\nError (if any):\n");
		loadContents( m_stde, fc); // std error file
		p_resultMsg.append( fc);
	}

	return true; // always true, since the stde is captured and shown
}

bool CmdClient::resolve( const std::string& p_path, bool p_recursive)
{
	std::string cmd = command( m_cs_resolved) + (p_recursive?" -R ":"") + p_path;
	redirect( cmd);

	int r;
	r = execute( cmd.c_str());
	
	return check( r);
}

// static
DWORD CmdClient::runSilent(const char* p_strFunct, const char* p_strstrParams, bool p_silent /*= true*/)
{
	STARTUPINFO          startup_info;
	PROCESS_INFORMATION  process_info;

	char *env_CMD        = NULL;
	char *default_CMD    = "CMD.EXE";
	char  args[4096];

	ULONG rc;

	//static HANDLE hi, ho, he;
	
	memset(&startup_info, 0, sizeof(startup_info)); // clear all members
	startup_info.cb = sizeof(STARTUPINFO);
	startup_info.dwFlags = STARTF_USESHOWWINDOW;
	if( p_silent)
	{
		startup_info.wShowWindow = SW_HIDE;
		//startup_info.dwFlags | = STARTF_USESTDHANDLES;
		//startup_info.hStdError = he;
		//startup_info.hStdInput = hi;
		//startup_info.hStdOutput = ho;
	}
	else 
	{
		startup_info.wShowWindow = SW_SHOW;
	}

	args[0] = 0;

	env_CMD = getenv("COMSPEC");

	if(env_CMD) strcpy(args, env_CMD);
	else        strcpy(args, default_CMD);

	// "/c" option - Do the command then terminate the command window
	//if( p_silent) strcat(args, " /c "); 
	strcat( args, " /c ");
	//the application you would like to run from the command window
	strcat(args, p_strFunct);  
	strcat(args, " "); 
	//the parameters passed to the application being run from the command window.
	strcat(args, p_strstrParams); 

	if (!CreateProcess( NULL, args, NULL, NULL, FALSE,
		CREATE_NEW_CONSOLE, NULL, NULL,
		&startup_info, &process_info))
	{
		return GetLastError();
	}

	//if( p_silent) 
	{
		WaitForSingleObject(process_info.hProcess, INFINITE);
		if(!GetExitCodeProcess(process_info.hProcess, &rc))
			rc = 0;

		CloseHandle(process_info.hThread);
		CloseHandle(process_info.hProcess);
	}
	//else
	{
		//GetStartupInfo()process_info.hProcess
	}

	return rc;	
}

int CmdClient::execute( const char * p)
{
	log( p, "");
	return runSilent( "", p, !m_showCmdWindows);
	// the alternative could be to use the system() call:
	//return system( p); // this can set errno
}


bool CmdClient::check( long p_ret, bool p_suppressNonversionedErrorMsg /*= false*/)
{
	bool no_error = true;
	
	// svn related std output and std error handling
	WIN32_FILE_ATTRIBUTE_DATA attre, attro;
	BOOL res = GetFileAttributesEx( m_stde, GetFileExInfoStandard, &attre );
	BOOL rep = GetFileAttributesEx( m_stdo, GetFileExInfoStandard, &attro );

	if( res && attre.nFileSizeHigh == 0 && attre.nFileSizeLow == 0) { } // no problem
	else if( res) {
		no_error = false; 
		if( !p_suppressNonversionedErrorMsg) 
			dumpContents( m_stde, MSG_ERROR);
	}

	if( rep && attro.nFileSizeHigh == 0 && attro.nFileSizeLow == 0) { } // no problem
	else if( rep) {
		dumpContents( m_stdo, MSG_INFO);
	}

	// execution related problems
	if( p_ret != 0)
	{
		no_error = false;
	}

	// if execute uses the system() 
	if( p_ret == -1)
	{
		no_error = false;
		// errno global variable handling:
		switch( errno)
		{
		case E2BIG:// The space required for the arguments and environment settings exceeds 32 K. 
			MsgConsole::ssendMsg( "Cmd.exe execution error: E2BIG", MSG_ERROR);
			break;
		case EACCES:// The specified file has a locking or sharing violation. 
			MsgConsole::ssendMsg( "Cmd.exe execution error: EACCES", MSG_ERROR);
			break;
		case EMFILE:// Too many files open (the specified file must be opened to determine whether it is executable). 
			MsgConsole::ssendMsg( "Cmd.exe execution error: EMFILE", MSG_ERROR);
			break;
		case ENOENT:// File or path not found. 
			MsgConsole::ssendMsg( "Cmd.exe execution error: ENOENT", MSG_ERROR);
			break;
		case ENOEXEC:// The specified file is not executable or has an invalid executable-file format. 
			MsgConsole::ssendMsg( "Cmd.exe execution error: ENOEXEC", MSG_ERROR);
			break;
		case ENOMEM: 
			MsgConsole::ssendMsg( "Cmd.exe execution error: ENOMEM", MSG_ERROR);
			break;
		default:
			MsgConsole::ssendMsg( "Cmd.exe execution error: <<unkown>>", MSG_ERROR);
		}
	}

	return no_error;
}

// static
void CmdClient::loadContents( const char * p_fname, std::string& p_fileContent)
{
	p_fileContent.clear();

	std::ifstream f;
	f.open( p_fname, std::ios_base::in);
	if( !f.is_open()) 
		return;

	char buffer[1024];
	while( f)
	{
		if( !p_fileContent.empty()) p_fileContent += '\n';
		f.getline( buffer, 1024);
		p_fileContent.append( buffer);
	}
	f.close();
}

void CmdClient::dumpContents( const char * p_fname, long p_msgType)
{
	//FILE * f = fopen( p_fname, "r");
	//if( !f) sendMsg( std::string( "Could not open file: ") + p_fname, p_msgType);
	//char buffer[1024];
	//while( !feof( f))
	//{
	//	fread( buffer, 1, 1024, f);
	//	sendMsg( buffer, p_msgType);
	//}
	//fclose( f);
	std::ifstream f;
	f.open( p_fname, std::ios_base::in);
	if( !f.is_open()) 
	{
		MsgConsole::ssendMsg( std::string( "Could not open file: ") + p_fname, p_msgType);
		return;
	}

	char buffer[1024];
	while( f)
	{
		f.getline( buffer, 1024);
		MsgConsole::ssendMsg( std::string( "SVN> ") + buffer, p_msgType);
	}
	f.close();
}

// static
void CmdClient::redirect( std::string& p_cmd)
{
	if( m_redirectOutput)
		p_cmd.append( std::string( " 1> ") + m_stdo + " 2>" + m_stde + " ");//p_cmd.append( " 1>stdo.tmp 2>stde.tmp ");
}

std::string CmdClient::findLastChangeAuthor( const std::string& p_out)
{
	const char * lca_str = "\nLast Changed Author: ";
	const int    lca_len = strlen( lca_str);

	int ps = p_out.find( lca_str);
	int ps_end = p_out.find( "\n", ps + 1);
	if( ps != std::string::npos && ps_end != std::string::npos)
	{
		return p_out.substr( ps + lca_len, ps_end - ps - lca_len);
	}

	return "";
}

std::string CmdClient::findLockOwner( const std::string& p_out)
{
	const char * lca_str = "\nLock Owner: ";
	const int    lca_len = strlen( lca_str);

	int ps = p_out.find( lca_str);
	int ps_end = p_out.find( "\n", ps + 1);
	if( ps != std::string::npos && ps_end != std::string::npos)
	{
		return p_out.substr( ps + lca_len, ps_end - ps - lca_len);
	}

	return "";
}

bool CmdClient::isFileOutOfDate( const std::string& p_out, const std::string& p_filename) // parser for 'status --show-updates <file>
{
//possible outcomes of a status -u invokation
//F:\t\at\sftest0519>svn status  f18e8ba9d40b1646bfc4812cd1e8f887.xml
//
//F:\t\at\sftest0519>svn status  f18e8ba9d40b1646bfc4812cd1e8f887.xml
//     O *     2294   f18e8ba9d40b1646bfc4812cd1e8f887.xml
//Status against revision:   2297
//F:\t\at\sftest0519>svn status -u f18e8ba9d40b1646bfc4812cd1e8f887.xml
//       *     2294   f18e8ba9d40b1646bfc4812cd1e8f887.xml
	bool res = false;

	int fname_pos = p_out.find( p_filename);
	if( fname_pos != std::string::npos) // it is the response line for the entry
	{
		int star_pos = p_out.find( '*');
		if( star_pos != std::string::npos // '*' found
		 && star_pos < fname_pos)         // pos of '*' is before the pos of entry
			res = true;
	}

	return res;
}