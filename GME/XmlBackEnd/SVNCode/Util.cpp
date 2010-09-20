/**
 * @copyright
 * ====================================================================
 * Copyright (c) 2003 CollabNet.  All rights reserved.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution.  The terms
 * are also available at http://subversion.tigris.org/license-1.html.
 * If newer versions of this license are posted there, you may use a
 * newer version instead, at your option.
 *
 * This software consists of voluntary contributions made by many
 * individuals.  For exact contribution history, see the revision
 * history and logs, available at http://subversion.tigris.org/.
 * ====================================================================
 * @endcopyright
 *
 */
/**
 * Modified by Zoltan Molnar, Vanderbilt University, 2008
 */

#include "../StdAfx.h"
#include "../MsgConsole.h"

#if(USESVN)

#include ".\util.h"
#include <iostream> // remove this later
#include <fstream>
#include <string>
#include "svn_path.h"
#include "svn_pools.h"
#include "ThreadData.h"
#include <locale.h> // for LC_ALL

//#define _ 

/*static*/ //Pool *              Util::m_requestPool      = 0;
/*static*/ apr_pool_t*         Util::g_pool             = 0;
/*static*/ bool                Util::g_inInit           = false;
/*static*/ bool                Util::g_initException    = false;
/*static*/ ThreadData          Util::m_globalData;
/*static*/ char                Util::g_initFormatBuffer[formatBufferSize];

/*static*/ std::ofstream       Util::g_logStream;
/*static*/ int                 Util::g_logLevel         = Util::noLog;

/**
 * initialize the environment for all requests
 * @param env   the JNI environment for this request
 */
//void Util::globalInit()
//{
//	if (apr_initialize() != APR_SUCCESS)
//	{
//		printf("apr_initialize() failed.\n");
//		exit(1);
//	}
//
//	g_pool = svn_pool_create (NULL);
//}

/**
 * initialize the environment for all requests
 * @param env   the JNI environment for this request
 */
bool Util::globalInit()
{
	// this method has to be run only once during the run a 
    // programm
    static bool run = false;
    if(run) // already run
    {
		return true;
    }
    run = true;
    // do not run this part more than one time. 
    // this leaves a small time window when two threads create their first
    // SVNClient & SVNAdmin at the same time, but I do not see a better 
    // option without APR already initialized
    if(g_inInit)
    {
        return false;
    }
    g_inInit = true;
    //g_initEnv = env;

    apr_status_t status;

    /* C programs default to the "C" locale. But because svn is supposed
       to be i18n-aware, it should inherit the default locale of its
       environment.  */
    if (!setlocale(LC_ALL, ""))
    {
        if (stderr)
        {
            const char *env_vars[] = { "LC_ALL", "LC_CTYPE", "LANG", NULL };
            const char **env_var = &env_vars[0], *env_val = NULL;
            while (*env_var)
            {
                env_val = getenv(*env_var);
                if (env_val && env_val[0])
                    break;
                ++env_var;
            }

            if (!*env_var)
            {
                /* Unlikely. Can setlocale fail if no env vars are set? */
                --env_var;
                env_val = "not set";
            }

            fprintf(stderr,
                  "%s: error: cannot set LC_ALL locale\n"
                  "%s: error: environment variable %s is %s\n"
                  "%s: error: please check that your locale name is correct\n",
                  "svnjavahl", "svnjavahl", *env_var, env_val, "svnjavahl");
        }
        return FALSE;
    }

    /* Initialize the APR subsystem, and register an atexit() function
       to Uninitialize that subsystem at program exit. */
    status = apr_initialize();
    if (status)
    {
        if (stderr)
        {
            char buf[1024];
            apr_strerror(status, buf, sizeof(buf) - 1);
            fprintf(stderr,
                  "%s: error: cannot initialize APR: %s\n",
                  "svnjavahl", buf);
        }
        return FALSE;
    }

    if (0 > atexit(apr_terminate))
    {
        if (stderr)
            fprintf(stderr,
                "%s: error: atexit registration failed\n",
                "svnjavahl");
        return FALSE;
    }

#ifdef ENABLE_NLS
#ifdef WIN32
    {
        WCHAR ucs2_path[MAX_PATH];
        char* utf8_path;
        const char* internal_path;
        apr_pool_t* pool;
        apr_status_t apr_err;
        unsigned int inwords, outbytes, outlength;

        apr_pool_create (&pool, 0);
        /* get dll name - our locale info will be in '../share/locale' */
        inwords = sizeof (ucs2_path) / sizeof(ucs2_path[0]);
        HINSTANCE moduleHandle = GetModuleHandle("libsvnjavahl-1");
        GetModuleFileNameW (moduleHandle, ucs2_path, inwords);
        inwords = lstrlenW (ucs2_path);
        outbytes = outlength = 3 * (inwords + 1);
        utf8_path = (char *)apr_palloc (pool, outlength);
        apr_err = apr_conv_ucs2_to_utf8 ((const apr_wchar_t *) ucs2_path,
                                         &inwords, utf8_path, &outbytes);
        if (!apr_err && (inwords > 0 || outbytes == 0))
          apr_err = APR_INCOMPLETE;
        if (apr_err)
        {
          if (stderr)
            fprintf (stderr, "Can't convert module path to UTF-8");
          return FALSE;
        }
        utf8_path[outlength - outbytes] = '\0';
        internal_path = svn_path_internal_style (utf8_path, pool);
        /* get base path name */
        internal_path = svn_path_dirname (internal_path, pool);
        internal_path = svn_path_join (internal_path, SVN_LOCALE_RELATIVE_PATH,
                                       pool);
        bindtextdomain (PACKAGE_NAME, internal_path);
        apr_pool_destroy (pool);
    }
#else
    bindtextdomain(PACKAGE_NAME, SVN_LOCALE_DIR);
#endif
    textdomain(PACKAGE_NAME);
#endif

    /* Create our top-level pool. */
    g_pool = svn_pool_create (NULL);

#if defined(WIN32) || defined(__CYGWIN__)
    /* See http://svn.collab.net/repos/svn/trunk/notes/asp-dot-net-hack.txt */
    /* ### This code really only needs to be invoked by consumers of
       ### the libsvn_wc library, which basically means SVNClient. */
    if (getenv ("SVN_ASP_DOT_NET_HACK"))
    {
        svn_error_t *err = svn_wc_set_adm_dir("_svn", g_pool);
        if (err)
        {
            if (stderr)
            {
                fprintf(stderr,
                        "%s: error: SVN_ASP_DOT_NET_HACK failed: %s\n",
                        "svnjavahl", err->message);
            }
            svn_error_clear(err);
            return FALSE;
        }
    }
#endif

    //// build all mutexes
    //g_finalizedObjectsMutex = new JNIMutex(g_pool);
    //if(isExceptionThrown())
    //{
    //    return false;
    //}

    //g_logMutex = new JNIMutex(g_pool);
    //if(isExceptionThrown())
    //{
    //    return false;
    //}

    //g_globalPoolMutext = new JNIMutex(g_pool);
    //if(isExceptionThrown())
    //{
    //    return false;
    //}

    //// initialized the thread local storage
    //if(!JNIThreadData::initThreadData())
    //{
    //    return false;
    //}

    //setEnv(env);
    //if(isExceptionThrown())
    //{
    //    return false;
    //}

    //g_initEnv = NULL;
	m_globalData.init();
    g_inInit = false;
    return true;
}

void Util::handleAPRError(int error, const char *op)
{
	char *buffer = getFormatBuffer();
	if(buffer == NULL)
	{
		return;
	}
	apr_snprintf(buffer, formatBufferSize, 
		"an error occurred in function %s with return value %d",
		op, error);

	throwError(buffer);
} 

//static
bool Util::isOtherExceptionThrown()
{
	return false;
}

//static
bool Util::isExceptionThrown()
{
	if(g_inInit) // during init -> look in the global member
	{
		return g_initException;
	}

	// look in the thread local storage
	//JNIThreadData *data = JNIThreadData::getThreadData();
	//return data == NULL || data->m_exceptionThrown;
	return m_globalData.m_exceptionThrown;
}

//static 
void Util::setExceptionThrown()
{
	if (g_inInit)
	{
		// During global initialization, store any errors that occur
		// in in a global variable (since thread-local storage may not
		// yet be available).
		g_initException = true;
	}
	else
	{
		// When global initialization is complete, thread-local
		// storage should be available, so store the error there.
		//JNIThreadData *data = JNIThreadData::getThreadData();
		//data->m_exceptionThrown = true;
		m_globalData.m_exceptionThrown = true;
	}
}

/*static*/ void Util::throwNullPointerException( const char * p_msg)
{
	std::cout << "Exception " << p_msg << std::endl;
    //if (getLogLevel() >= errorLog)
    {
        logMessage("NullPointerException thrown");
    }

	setExceptionThrown();
}

//static
void Util::throwError(const char *message)
{
	//raiseThrowable(JAVA_PACKAGE"/JNIError", message);
	throw std::string( message);
}


/**
 * returns the global (not request specific) pool
 * @return global pool
 */
/*static*/ apr_pool_t * Util::getPool()
{
	return g_pool;
}

/**
 * build the error message from the svn error into buffer. This method calls 
 * itselft recursivly for all the chained errors
 *
 * @param err               the subversion error
 * @param depth             the depth of the call, used for formating
 * @param parent_apr_err    the apr of the previous level, used for formating
 * @param buffer            the buffer where the formated error message will
 *                          be stored
 */
void Util::assembleErrorMessage(svn_error_t *err, int depth, 
								apr_status_t parent_apr_err, 
								std::string &buffer)
{
	// buffer for a single error message
	char errbuf[256];

	/* Pretty-print the error */
	/* Note: we can also log errors here someday. */

	/* When we're recursing, don't repeat the top-level message if its
	   the same as before. */
	if (depth == 0 || err->apr_err != parent_apr_err)
	{
		/* Is this a Subversion-specific error code? */
		if ((err->apr_err > APR_OS_START_USEERR)
			&& (err->apr_err <= APR_OS_START_CANONERR))
			buffer.append(svn_strerror (err->apr_err, errbuf, sizeof (errbuf)));
		/* Otherwise, this must be an APR error code. */
		else
			buffer.append(apr_strerror (err->apr_err, errbuf, sizeof (errbuf)));
		buffer.append("\n");
	}
	if (err->message)
		buffer.append( "svn: ").append(err->message).append("\n");

	if (err->child)
		assembleErrorMessage(err->child, depth + 1, err->apr_err, buffer);

}

//static
std::string Util::makeSVNErrorMessage(svn_error_t *err)
{
    if(err == NULL)
        return "";
    std::string buffer;
    assembleErrorMessage(err, 0, APR_SUCCESS, buffer);
    return buffer;
}

/**
 * process a svn error by wraping in into a ClientExpection
 * and throwing that
 * @param err   the error to by handled
 */
/*static*/ void Util::handleSVNError( svn_error_t * p_err)
{
	if( !p_err) 
	{ 
		//std::cout << "handleSVNError: p_err is 0" << std::endl; 
		return; 
	}
	//std::cout << "Error " << ( p_err->message?p_err->message:"<<nomsg>>") << std::endl;

    if(isOtherExceptionThrown())
    {
        svn_error_clear( p_err);
		MsgConsole::ssendMsg( "[Util::handleSVNError] Unknown exception thrown.", MSG_ERROR);
		AfxMessageBox( "[Util::handleSVNError] Unknown exception thrown.");
        return;
    } 
	
	std::string buffer;
    assembleErrorMessage( p_err, 0, APR_SUCCESS, buffer);
	buffer = "SVN Error details follow:\n" + buffer;
	AfxMessageBox( buffer.c_str());

	// modifying buffer for the console
	// replacing '\n's with <br>s
	std::string::size_type p = buffer.find( "\n");
	while( std::string::npos != p)
	{
		buffer.replace( p, 1, "<br>");
		p = buffer.find( "\n");
	}
	// removing '\r's
	p = buffer.find( "\r");
	while( std::string::npos != p)
	{
		buffer.erase( p, 1);
		p = buffer.find( "\r");
	}
	MsgConsole::ssendMsg( buffer, MSG_ERROR);
	//std::cout << "Error " << buffer << std::endl;

	//if( p_err->apr_err == SVN_ERR_RA_ILLEGAL_URL)
	//	std::cout << "Error SVN_ERR_RA_ILLEGAL_URL, [URL does not exist]. " << std::endl;
	//if( p_err->apr_err == SVN_ERR_UNSUPPORTED_FEATURE)
	//	std::cout << "Error SVN_ERR_UNSUPPORTED_FEATURE, [URL refs to file instead of a directory]. " << std::endl;
	//if( p_err->apr_err == SVN_ERR_UNVERSIONED_RESOURCE)
	//	std::cout << "Error SVN_ERR_UNVERSIONED_RESOURCE " << ( p_err->file? p_err->file: "<<nofile>>") << " msg = " << ( p_err->message?p_err->message:"<<nomsg>>") << std::endl;
	//if( p_err->apr_err == SVN_ERR_RA_ILLEGAL_URL)
	//	std::cout << "Error SVN_ERR_RA_ILLEGAL_URL " << ( p_err->file? p_err->file: "<<nofile>>") << " msg = " << ( p_err->message?p_err->message:"<<nomsg>>") << std::endl;
	//if( p_err->apr_err == SVN_ERR_RA_DAV_SOCK_INIT)
	//	std::cout << "Error SVN_ERR_RA_DAV_SOCK_INIT " << (p_err->file?p_err->file:"") << " msg = " << ( p_err->message?p_err->message:"<<nomsg>>") << std::endl;
	//if( p_err->child)
	//	handleSVNError( p_err->child);
}

/*static*/ svn_error_t * Util::preprocessPath(const char *&path, apr_pool_t * pool)
{
	/* URLs and wc-paths get treated differently. */
	if (svn_path_is_url (path))
	{
		/* No need to canonicalize a URL's case or path separators. */

		/* Convert to URI. */
		path = svn_path_uri_from_iri (path, pool);
		/* Auto-escape some ASCII characters. */
		path = svn_path_uri_autoescape (path, pool);

		/* The above doesn't guarantee a valid URI. */
		if (! svn_path_is_uri_safe (path))
			return svn_error_createf (SVN_ERR_BAD_URL, 0,
			"URL '%s' is not properly URI-encoded",
			path);

		/* Verify that no backpaths are present in the URL. */
		if (svn_path_is_backpath_present (path))
			return svn_error_createf (SVN_ERR_BAD_URL, 0,
			"URL '%s' contains a '..' element",
			path);

		/* strip any trailing '/' */
		path = svn_path_canonicalize (path, pool);
	}
	else  /* not a url, so treat as a path */
	{
		const char *apr_target;
		char *truenamed_target; /* APR-encoded */
		apr_status_t apr_err;

		/* canonicalize case, and change all separators to '/'. */
		SVN_ERR (svn_path_cstring_from_utf8 (&apr_target, path,
			pool));
		apr_err = apr_filepath_merge (&truenamed_target, "", apr_target,
			APR_FILEPATH_TRUENAME, pool);

		if (!apr_err)
			/* We have a canonicalized APR-encoded target now. */
			apr_target = truenamed_target;
		else if (APR_STATUS_IS_ENOENT (apr_err))
			/* It's okay for the file to not exist, that just means we
			have to accept the case given to the client. We'll use
			the original APR-encoded target. */
			;
		else
			return svn_error_createf (apr_err, NULL,
			"Error resolving case of '%s'",
			svn_path_local_style (path,
			pool));

		/* convert back to UTF-8. */
		SVN_ERR (svn_path_cstring_to_utf8 (&path, apr_target, pool));
		path = svn_path_canonicalize (path, pool);

	}
	return NULL;
}

/** 
 * Return the request pool. The request pool will be destroyed after each 
 * request (call) 
 * @return the pool to be used for this request
 */
/*static*/ Pool * Util::getRequestPool()
{
    //return JNIThreadData::getThreadData()->m_requestPool;
	return m_globalData.m_requestPool;
	//return m_requestPool;
}
/**
 * Set the request pool in thread local storage
 * @param pool  the request pool
 */
/*static*/ void Util::setRequestPool(Pool *pool)
{
    //JNIThreadData::getThreadData()->m_requestPool = pool;
    //m_requestPool = pool;
	m_globalData.m_requestPool = pool;
}

char * Util::getFormatBuffer()
{
	if(g_inInit) // during init -> use the global buffer
	{
		return g_initFormatBuffer;
	}
	// use the buffer in the thread local storage
	//JNIThreadData *data = JNIThreadData::getThreadData();
	//if(data == NULL) // if that does not exists -> use the global buffer
	//{
	//	return g_initFormatBuffer;
	//}
	//return data->m_formatBuffer;
	return m_globalData.m_formatBuffer;
}

/** 
 * initialite the log file
 * @param level the log level
 * @param the name of the log file
 */
void Util::initLogFile(int level, const std::string& path)
{
    // lock this operation
    //JNICriticalSection cs(*g_logMutex);
    if(g_logLevel > noLog) // if the log file has been opened
    {
        g_logStream.close();
    }
    // remember the log level
    g_logLevel = level;
    //JNIStringHolder myPath(path);
	const char * myPath = path.c_str();
    if(g_logLevel > noLog) // if a new log file is needed
    {
        // open it
        g_logStream.open(myPath, std::ios::app);
    }
}

/**
 * Returns the current log level
 * @return the log level
 */
int Util::getLogLevel()
{
    return g_logLevel;
}
/**
 * write a message to the log file if needed
 * @param the log message
 */
void Util::logMessage(const char *message)
{
    // lock the log file
    //JNICriticalSection cs(*g_logMutex);
    g_logStream << message << std::endl;
}

#endif