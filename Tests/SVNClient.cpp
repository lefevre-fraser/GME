#include "StdAfx.h"

#include "svngui.h"

#include "SVNClient.h"
#include "svn_client.h"
#include "svn_pools.h"
#include "svn_dso.h"
#include "svn_utf.h"
#include "svn_nls.h"
#include "svn_fs.h"
#include "svn_hash.h"

#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "shfolder.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "secur32.lib")
#pragma comment(lib, "crypt32.lib")
#pragma comment(lib, "version.lib")
#pragma comment(lib, "psapi.lib")


// Subversion libraries and dependencies
#pragma comment(lib, "libapr-1.lib")
#pragma comment(lib, "libaprutil-1.lib")
#pragma comment(lib, "libapriconv-1.lib")
#pragma comment(lib, "xml.lib")

#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")

#pragma comment(lib, "svn_client-1.lib")
#pragma comment(lib, "svn_delta-1.lib")
#pragma comment(lib, "svn_diff-1.lib")
#pragma comment(lib, "svn_fs-1.lib")
#pragma comment(lib, "libsvn_fs_fs-1.lib")
#pragma comment(lib, "libsvn_fs_util-1.lib")
#pragma comment(lib, "svn_ra-1.lib")
#pragma comment(lib, "libsvn_ra_local-1.lib")
#pragma comment(lib, "libsvn_ra_svn-1.lib")
#pragma comment(lib, "svn_repos-1.lib")
#pragma comment(lib, "svn_subr-1.lib")
#pragma comment(lib, "svn_wc-1.lib")
#pragma comment(lib, "libsvn_ra_serf-1.lib")
#pragma comment(lib, "serf-1.lib")

// These are contained by serf-1.lib
// NOTE: zlibstatD.lib includes /DEFAULTLIB:"MSVCRT" disrectives 
// (instead of "MSVCRTD"), resulting in linker warnings.

//#ifdef _DEBUG
//	#pragma comment(lib, "zlibstatD.lib")
//#else
//	#pragma comment(lib, "zlibstat.lib")
//#endif

#define SVNTHROW(FUNC) \
do { \
	svn_error_t* _err = (FUNC); \
	if( _err ) { \
		throw CSVNError(_err); \
	} \
} while(false)


CSVNError::CSVNError(svn_error_t* e) : svnError(e)
{
}

CSVNError::~CSVNError()
{
	svn_error_clear(svnError);
}

CString CSVNError::msg()
{
	char buf[SVN_ERROR_MSG_MAX];

	svn_err_best_message(svnError, buf, sizeof(buf));
	return CString(buf);
}

CSVNClient::CSVNClient() : isInitialized(false)
{
}


CSVNClient::~CSVNClient(void)
{
	POSITION p = svnFiles.GetHeadPosition();
	while (p) {
		delete svnFiles.GetNext(p);
	}

	apr_terminate();
}

void CSVNClient::initialize(void)
{
	apr_status_t status;
	apr_pool_t *pool;
	svn_error_t *err;
	svn_client_ctx_t *ctx;

	// TODO: subversion/libsvn_subr/cmdline.c contains a lot of esoteric stuff
	// such as "setvbuf", input/output encodings, exception handlers, locale settings, etc.

	/* Initialize the APR subsystem, and register an atexit() function
       to Uninitialize that subsystem at program exit. */
	status = apr_initialize();
	if (status)
    { 
		// this is not a real svn error, but coming from apr
		throw CSVNError(svn_error_create(status, NULL, NULL));
	}

	/* DSO pool must be created before any other pools used by the
	application so that pool cleanup doesn't unload DSOs too
	early. See docstring of svn_dso_initialize2(). */
	SVNTHROW(svn_dso_initialize2());

	/* Create a pool for use by the UTF-8 routines.  It will be cleaned
     up by APR at exit time. */
	pool = svn_pool_create(NULL);
	svn_utf_initialize2(FALSE, pool);
	SVNTHROW(svn_nls_init());

	/* Create top-level memory pool. */
	pool = svn_pool_create(NULL);

	/* Initialize the FS library. */
	SVNTHROW(svn_fs_initialize(pool));

	/* Initialize the RA library. */
	SVNTHROW(svn_ra_initialize(pool));

	/* Make sure the ~/.subversion run-time config files exist */
	SVNTHROW(svn_config_ensure (NULL, pool));


	/* All clients need to fill out a client_ctx object. */
	{
		svn_config_t *cfg_config;

		/* Initialize and allocate the client_ctx object. */
		SVNTHROW(svn_client_create_context (&ctx, pool));

		/* Load the run-time config file into a hash */
		SVNTHROW(svn_config_get_config (&(ctx->config), NULL, pool));

		cfg_config = (svn_config_t *)svn_hash_gets(ctx->config, SVN_CONFIG_CATEGORY_CONFIG);

		/* Set the working copy administrative directory name. */
		if (getenv ("SVN_ASP_DOT_NET_HACK"))
		{
			SVNTHROW(svn_wc_set_adm_dir ("_svn", pool));
		}

		/* Depending on what your client does, you'll want to read about
		(and implement) the various callback function types below.  */

		/* A func (& context) which receives event signals during
		checkouts, updates, commits, etc.  */
		/* ctx->notify_func2 = my_notification_func;
		ctx->notify_baton2 = NULL; */

		/* A func (& context) which can receive log messages */
		/* ctx->log_msg_func3 = my_log_msg_receiver_func;
		ctx->log_msg_baton3 = NULL; */

		/* A func (& context) which checks whether the user cancelled */
		/* ctx->cancel_func = my_cancel_checking_func;
		ctx->cancel_baton = NULL; */

		/* A func (& context) for network progress */
		/* ctx->progress_func = my_progress_func;
		ctx->progress_baton = NULL; */
		
		/* A func (& context) for conflict resolution */
		/* ctx->conflict_func2 = my_conflict_func;
		ctx->conflict_baton2 = NULL; */

		/* Make the client_ctx capable of authenticating users */
		{
			svn_auth_provider_object_t *provider;
			apr_array_header_t *providers;

			/* For caching encrypted username/password and client cert passwords - no prompting */
			SVNTHROW(svn_auth_get_platform_specific_client_providers(&providers, cfg_config, pool));

			/* For caching unencrypted username/password (also from config file) - prompting only to confirm storing creds in cleartext */
			svn_auth_get_simple_provider2(&provider,svn_cmdline_auth_plaintext_prompt, NULL /* prompt baton */, pool);
			APR_ARRAY_PUSH(providers, svn_auth_provider_object_t *) = provider;

			/* For guessing and optionally saving username - no prompting */
			svn_auth_get_username_provider(&provider, pool);
			APR_ARRAY_PUSH(providers, svn_auth_provider_object_t *) = provider;

			/* For validating server SSL certs from windows certificate store - no prompting (windows itself might show a dialog ?) */
			SVNTHROW(svn_auth_get_platform_specific_provider(&provider, "windows", "ssl_server_trust", pool));
			APR_ARRAY_PUSH(providers, svn_auth_provider_object_t *) = provider;

			/* For validating and/or storing SSL server certs (in custom files) - no prompting */
			svn_auth_get_ssl_server_trust_file_provider(&provider, pool);
			APR_ARRAY_PUSH(providers, svn_auth_provider_object_t *) = provider;

			/* For retrieving custom client certificate (file path) from server config - no prompting */
			svn_auth_get_ssl_client_cert_file_provider(&provider, pool);
			APR_ARRAY_PUSH(providers, svn_auth_provider_object_t *) = provider;

			svn_auth_get_ssl_client_cert_pw_file_provider2(&provider, svn_cmdline_auth_plaintext_passphrase_prompt, NULL /* prompt baton */, pool);
			APR_ARRAY_PUSH(providers, svn_auth_provider_object_t *) = provider;

			svn_auth_get_simple_prompt_provider(&provider, svn_cmdline_auth_simple_prompt, NULL /* prompt baton */, 2 /* retry limit */, pool);
			APR_ARRAY_PUSH(providers, svn_auth_provider_object_t *) = provider;

			svn_auth_get_username_prompt_provider(&provider, svn_cmdline_auth_username_prompt, NULL /* prompt baton */, 2 /* retry limit */, pool);
			APR_ARRAY_PUSH(providers, svn_auth_provider_object_t *) = provider;

			svn_auth_get_ssl_server_trust_prompt_provider(&provider, svn_cmdline_auth_ssl_server_trust_prompt, NULL /* prompt baton */, pool);
			APR_ARRAY_PUSH(providers, svn_auth_provider_object_t *) = provider;

			svn_auth_get_ssl_client_cert_pw_prompt_provider(&provider, svn_cmdline_auth_ssl_client_cert_pw_prompt, NULL /* prompt baton */, 2 /* retry limit */, pool);
			APR_ARRAY_PUSH(providers, svn_auth_provider_object_t *) = provider;

			/* If configuration allows, add a provider for client-cert path
				prompting, too. */
			svn_boolean_t ssl_client_cert_file_prompt;
			SVNTHROW(svn_config_get_bool(cfg_config, &ssl_client_cert_file_prompt,
										SVN_CONFIG_SECTION_AUTH,
										SVN_CONFIG_OPTION_SSL_CLIENT_CERT_FILE_PROMPT,
										FALSE));
			if (ssl_client_cert_file_prompt)
			{
				svn_auth_get_ssl_client_cert_prompt_provider(&provider, svn_cmdline_auth_ssl_client_cert_prompt, NULL /* prompt baton */, 2 /* retry limit */, pool);
				APR_ARRAY_PUSH(providers, svn_auth_provider_object_t *) = provider;
			}

			/* Register the auth-providers into the context's auth_baton. */
			svn_auth_open (&ctx->auth_baton, providers, pool);
		}
	}

	isInitialized = true;
}

CSVNFile* CSVNClient::embraceFile(const CString & filePath)
{
	ASSERT(isInitialized);

	CSVNFile* svnFile = new CSVNFile(filePath);
	if (svnFile) {
		svnFiles.AddTail(svnFile);
	}
	return svnFile;
}

void CSVNClient::forgetFile(CSVNFile* svnFile)
{
	ASSERT(isInitialized);

	POSITION p = svnFiles.Find(svnFile);
	while (p) {
		delete p;
		svnFiles.RemoveAt(p);
		p = svnFiles.Find(svnFile);
	}
}

CSVNFile::CSVNFile(const CString & filePath)
{
}

CSVNFile::~CSVNFile()
{
}

bool CSVNFile::isTracked()
{
	//TODO: implement this
	return false;
}

bool CSVNFile::isOwned()
{
	//TODO: implement this
	return false;
}

bool CSVNFile::isLatest()
{
	//TODO: implement this
	return false;
}

void CSVNFile::takeOwnership()
{
} 

void CSVNFile::commit()
{
}

