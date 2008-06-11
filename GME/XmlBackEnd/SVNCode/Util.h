/**
 * @copyright
 * ====================================================================
 * Copyright (c) 2003-2004 CollabNet.  All rights reserved.
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

#pragma once
#include "svn_client.h"
#include "Pool.h"
#include <string>

class ThreadData;
/**
 * class to hold a number of JNI relate utility methods. No Objects of this 
 * class are ever created
 */

class Util
{
public:
	enum { formatBufferSize = 2048 };

	static char *         getFormatBuffer();

	static bool           globalInit();

	static svn_error_t *  preprocessPath(const char *&path, apr_pool_t * pool);

	static void           logMessage(const char *message);
	static int            getLogLevel();
	static void           initLogFile(int level, const std::string& path);

	static void           handleAPRError(int error, const char *op);
	static bool           isOtherExceptionThrown();
	static bool           isExceptionThrown();
	static void           setExceptionThrown();
	static void           throwNullPointerException( const char *);
	static void           throwError(const char *message);

	static Pool*          getRequestPool();
	static void           setRequestPool(Pool *pool);
	
	static void           assembleErrorMessage(svn_error_t *err, int depth,
	                           apr_status_t parent_apr_err,
	                           std::string& buffer);

	static std::string    makeSVNErrorMessage(svn_error_t *err); 
	static void           handleSVNError( svn_error_t *);

	static apr_pool_t *   getPool(); 

private:

	//static Pool *m_requestPool; // was in a Thread Local Storage

	/**
	* global master pool. All other pool are subpools of this pool
	*/
	static apr_pool_t* g_pool;

	/**
	* flag, that one thread is in the init code. Cannot use mutex here since 
	* apr is not initialized yes
	*/
	static bool g_inInit;
	/**
	* flag, that an exception occured during our initialization
	*/
	static bool g_initException;

	enum { noLog, errorLog, exceptionLog, entryLog } LogLevel;
	/** 
	* the log level of this module
	*/ 
	static int g_logLevel;
	/**
	* the stream to write log messages to
	*/
	static std::ofstream g_logStream;

	static char           g_initFormatBuffer[formatBufferSize];

	static ThreadData     m_globalData; 

};
