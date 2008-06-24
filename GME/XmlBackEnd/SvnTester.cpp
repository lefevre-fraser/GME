// SvnTester.cpp : Implementation of CSvnTester

#include "stdafx.h"
#include "SvnTester.h"
#include "SvnLoginDlg.h"
#include "SvnTestDlg.h"
#include "CommonMFC.h"

// CSvnTester
std::string g_storedUserName;
std::string g_storedPassWord;

STDMETHODIMP CSvnTester::info(BSTR p_url, VARIANT_BOOL p_byAPI, VARIANT_BOOL p_recursive, BSTR* p_ptrResultMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_svnUrl   = "";
	m_username = "";
	m_password = "";

	try {
		if( p_byAPI == VARIANT_TRUE)
		{
#if(USESVN)
			if( getLoginData())
			{
				m_apiSvn = new HiClient( m_username, m_password);
				if( !m_apiSvn) {
					AfxMessageBox( "SVN implementation client object could not be created!");
					throw hresult_exception( E_FAIL);
				}

				CopyTo( p_url, m_svnUrl);

				std::string info_msg;
				std::string author;
				std::string owner;

				m_apiSvn->info( m_svnUrl, p_recursive == VARIANT_TRUE /*rec*/, true /*assemble info*/, info_msg, author, owner);

				CopyTo( info_msg, p_ptrResultMsg);
			}
			else CopyTo( std::string( "Canceled."), p_ptrResultMsg);
#else
			return E_NOTIMPL;
#endif
		}
		else
		{
			m_cmdSvn = new CmdClient( false /*m_svnShowCmdLineWindows*/, true /*m_svnRedirectOutput*/); 
			if( !m_cmdSvn) {
				AfxMessageBox( "SVN implementation client object could not be created!");
				throw hresult_exception( E_FAIL);
			}

			CopyTo( p_url, m_svnUrl);

			std::string info_msg;
			std::string author;
			std::string owner;

			m_cmdSvn->info( m_svnUrl, p_recursive == VARIANT_TRUE /*rec*/, true /*assemble info*/, info_msg, author, owner);

			CopyTo( info_msg, p_ptrResultMsg);
		}
		return S_OK;

	}catch(hresult_exception &) {
		ASSERT( 0);
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CSvnTester::status(BSTR p_path, VARIANT_BOOL p_byAPI, VARIANT_BOOL p_onServer, BSTR* p_ptrResultMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_svnUrl   = "";
	m_username = "";
	m_password = "";

	try {
		if( p_byAPI == VARIANT_TRUE)
		{
#if(USESVN)
			if( getLoginData())
			{
				m_apiSvn = new HiClient( m_username, m_password);
				if( !m_apiSvn) {
					AfxMessageBox( "SVN implementation client object could not be created!");
					throw hresult_exception( E_FAIL);
				}

				std::string path;
				std::string stat_msg;

				CopyTo( p_path, path);

				bool out_of_date    = false;
				bool repo_entry_mod = false;
				bool sc;

				if( p_onServer == VARIANT_TRUE)
					sc = m_apiSvn->statusOnServer( path, true /*assemble info*/, stat_msg, &out_of_date, &repo_entry_mod);
				else
					sc = m_apiSvn->status( path, true /*assemble info*/, stat_msg);

				CopyTo( stat_msg, p_ptrResultMsg);
			}
			else CopyTo( std::string( "Canceled."), p_ptrResultMsg);
#else
			return E_NOTIMPL;
#endif
		}
		else
		{
			m_cmdSvn = new CmdClient( false /*m_svnShowCmdLineWindows*/, true /*m_svnRedirectOutput*/); 
			if( !m_cmdSvn) {
				AfxMessageBox( "SVN implementation client object could not be created!");
				throw hresult_exception( E_FAIL);
			}

			std::string path;
			std::string stat_msg;
			CopyTo( p_path, path);

			bool out_of_date    = false;
			bool sc;

			if( p_onServer == VARIANT_TRUE)
				sc = m_cmdSvn->statusOnServer( path, true /*assemble info*/, stat_msg, &out_of_date);
			else
				sc = m_cmdSvn->status( path, true /*assemble info*/, stat_msg);

			CopyTo( stat_msg, p_ptrResultMsg);
		}
		return S_OK;

	}catch(hresult_exception &) {
		ASSERT( 0);
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CSvnTester::cleanup(BSTR p_path, VARIANT_BOOL p_byAPI, BSTR* p_ptrResultMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	try {
		if( p_byAPI == VARIANT_TRUE)
		{
#if(USESVN)
			if( getLoginData())
			{
				m_apiSvn = new HiClient( m_username, m_password);
				if( !m_apiSvn) {
					AfxMessageBox( "SVN implementation client object could not be created!");
					throw hresult_exception( E_FAIL);
				}

				std::string path;
				std::string stat_msg;

				CopyTo( p_path, path);

				m_apiSvn->cleanup( path);
			}
			else CopyTo( std::string( "Canceled."), p_ptrResultMsg);
#else
			return E_NOTIMPL;
#endif
		}
		else
		{
			m_cmdSvn = new CmdClient( false /*m_svnShowCmdLineWindows*/, true /*m_svnRedirectOutput*/); 
			if( !m_cmdSvn) {
				AfxMessageBox( "SVN implementation client object could not be created!");
				throw hresult_exception( E_FAIL);
			}

			std::string path;
			std::string stat_msg;
			CopyTo( p_path, path);

			m_cmdSvn->cleanup( path, true /*assemble info*/, stat_msg);

			CopyTo( stat_msg, p_ptrResultMsg);
		}
		return S_OK;

	}catch(hresult_exception &) {
		ASSERT( 0);
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CSvnTester::resolve(BSTR p_path, VARIANT_BOOL p_byAPI, VARIANT_BOOL p_recursive)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	try {
		if( p_byAPI == VARIANT_TRUE)
		{
#if(USESVN)
			if( getLoginData())
			{
				m_apiSvn = new HiClient( m_username, m_password);
				if( !m_apiSvn) {
					AfxMessageBox( "SVN implementation client object could not be created!");
					throw hresult_exception( E_FAIL);
				}

				std::string path;
				CopyTo( p_path, path);

				m_apiSvn->resolve( path, p_recursive == VARIANT_TRUE);
			}
			else throw hresult_exception(E_FAIL);
#else
			return E_NOTIMPL;
#endif
		}
		else
		{
			m_cmdSvn = new CmdClient( false /*m_svnShowCmdLineWindows*/, true /*m_svnRedirectOutput*/); 
			if( !m_cmdSvn) {
				AfxMessageBox( "SVN implementation client object could not be created!");
				throw hresult_exception( E_FAIL);
			}

			std::string path;
			CopyTo( p_path, path);

			m_cmdSvn->resolve( path, p_recursive == VARIANT_TRUE);
		}
		return S_OK;

	}catch(hresult_exception &) {
		ASSERT( 0);
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CSvnTester::commit(BSTR p_path, VARIANT_BOOL p_byAPI, VARIANT_BOOL p_recursive)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	try {
		if( p_byAPI == VARIANT_TRUE)
		{
#if(USESVN)
			if( getLoginData())
			{
				m_apiSvn = new HiClient( m_username, m_password);
				if( !m_apiSvn) {
					AfxMessageBox( "SVN implementation client object could not be created!");
					throw hresult_exception( E_FAIL);
				}

				std::string path;
				CopyTo( p_path, path);

				m_apiSvn->commitAll( path, false);
			}
			else throw hresult_exception(E_FAIL);
#else
			return E_NOTIMPL;
#endif
		}
		else
		{
			m_cmdSvn = new CmdClient( false /*m_svnShowCmdLineWindows*/, true /*m_svnRedirectOutput*/); 
			if( !m_cmdSvn) {
				AfxMessageBox( "SVN implementation client object could not be created!");
				throw hresult_exception( E_FAIL);
			}

			std::string path;
			CopyTo( p_path, path);

			m_cmdSvn->commit( path);
		}
		return S_OK;

	}catch(hresult_exception &) {
		ASSERT( 0);
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CSvnTester::checkout(BSTR p_url, BSTR p_path, VARIANT_BOOL p_byAPI, VARIANT_BOOL p_recursive)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	try {
		if( p_byAPI == VARIANT_TRUE)
		{
#if(USESVN)
			if( getLoginData())
			{
				m_apiSvn = new HiClient( m_username, m_password);
				if( !m_apiSvn) {
					AfxMessageBox( "SVN implementation client object could not be created!");
					throw hresult_exception( E_FAIL);
				}

				std::string url;
				CopyTo( p_url, url);
				std::string ldir;
				CopyTo( p_path, ldir);

				m_apiSvn->lightCheckOut( url, ldir);
			}
			else throw hresult_exception(E_FAIL);
#else
			return E_NOTIMPL;
#endif
		}
		else
		{
			m_cmdSvn = new CmdClient( false /*m_svnShowCmdLineWindows*/, true /*m_svnRedirectOutput*/); 
			if( !m_cmdSvn) {
				AfxMessageBox( "SVN implementation client object could not be created!");
				throw hresult_exception( E_FAIL);
			}

			std::string url;
			CopyTo( p_url, url);

			std::string ldir;
			CopyTo( p_path, ldir);
			
			m_cmdSvn->lightCheckOut( url, ldir);
		}
		return S_OK;

	}catch(hresult_exception &) {
		ASSERT( 0);
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CSvnTester::add(BSTR p_path, VARIANT_BOOL p_byAPI, VARIANT_BOOL p_recursive)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	try {
		if( p_byAPI == VARIANT_TRUE)
		{
#if(USESVN)
			if( getLoginData())
			{
				m_apiSvn = new HiClient( m_username, m_password);
				if( !m_apiSvn) {
					AfxMessageBox( "SVN implementation client object could not be created!");
					throw hresult_exception( E_FAIL);
				}

				std::string path;
				CopyTo( p_path, path);

				m_apiSvn->add( path, p_recursive == VARIANT_TRUE);
			}
			else throw hresult_exception(E_FAIL);
#else
			return E_NOTIMPL;
#endif
		}
		else
		{
			m_cmdSvn = new CmdClient( false /*m_svnShowCmdLineWindows*/, true /*m_svnRedirectOutput*/); 
			if( !m_cmdSvn) {
				AfxMessageBox( "SVN implementation client object could not be created!");
				throw hresult_exception( E_FAIL);
			}

			std::string path;
			CopyTo( p_path, path);
			
			m_cmdSvn->add( path, p_recursive == VARIANT_TRUE);
		}
		return S_OK;

	}catch(hresult_exception &) {
		ASSERT( 0);
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CSvnTester::propset(BSTR p_path, BSTR p_propname, BSTR p_propval, VARIANT_BOOL p_byAPI, VARIANT_BOOL p_recursive)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	try {
		if( p_byAPI == VARIANT_TRUE)
		{
#if(USESVN)
			if( getLoginData())
			{
				m_apiSvn = new HiClient( m_username, m_password);
				if( !m_apiSvn) {
					AfxMessageBox( "SVN implementation client object could not be created!");
					throw hresult_exception( E_FAIL);
				}

				std::string path;
				CopyTo( p_path, path);

				m_apiSvn->lockableProp( path);
			}
			else throw hresult_exception(E_FAIL);
#else
			return E_NOTIMPL;
#endif
		}
		else
		{
			m_cmdSvn = new CmdClient( false /*m_svnShowCmdLineWindows*/, true /*m_svnRedirectOutput*/); 
			if( !m_cmdSvn) {
				AfxMessageBox( "SVN implementation client object could not be created!");
				throw hresult_exception( E_FAIL);
			}

			std::string path;
			CopyTo( p_path, path);

			m_cmdSvn->lockableProp( path);
		}
		return S_OK;

	}catch(hresult_exception &) {
		ASSERT( 0);
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CSvnTester::lock(BSTR p_path, VARIANT_BOOL p_force, VARIANT_BOOL p_byAPI)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	try {
		if( p_byAPI == VARIANT_TRUE)
		{
#if(USESVN)
			if( getLoginData())
			{
				m_apiSvn = new HiClient( m_username, m_password);
				if( !m_apiSvn) {
					AfxMessageBox( "SVN implementation client object could not be created!");
					throw hresult_exception( E_FAIL);
				}

				std::string path;
				CopyTo( p_path, path);

				m_apiSvn->tryLock( path);
			}
			else throw hresult_exception(E_FAIL);
#else
			return E_NOTIMPL;
#endif
		}
		else
		{
			m_cmdSvn = new CmdClient( false /*m_svnShowCmdLineWindows*/, true /*m_svnRedirectOutput*/); 
			if( !m_cmdSvn) {
				AfxMessageBox( "SVN implementation client object could not be created!");
				throw hresult_exception( E_FAIL);
			}

			std::string path;
			CopyTo( p_path, path);

			m_cmdSvn->tryLock( path);
		}
		return S_OK;

	}catch(hresult_exception &) {
		ASSERT( 0);
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CSvnTester::unlock(BSTR p_path, VARIANT_BOOL p_force, VARIANT_BOOL p_byAPI)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	try {
		if( p_byAPI == VARIANT_TRUE)
		{
#if(USESVN)
			if( getLoginData())
			{
				m_apiSvn = new HiClient( m_username, m_password);
				if( !m_apiSvn) {
					AfxMessageBox( "SVN implementation client object could not be created!");
					throw hresult_exception( E_FAIL);
				}

				std::string path;
				CopyTo( p_path, path);

				m_apiSvn->unLock( path);
			}
			else throw hresult_exception(E_FAIL);
#else
			return E_NOTIMPL;
#endif
		}
		else
		{
			m_cmdSvn = new CmdClient( false /*m_svnShowCmdLineWindows*/, true /*m_svnRedirectOutput*/); 
			if( !m_cmdSvn) {
				AfxMessageBox( "SVN implementation client object could not be created!");
				throw hresult_exception( E_FAIL);
			}

			std::string path;
			CopyTo( p_path, path);

			m_cmdSvn->unLock( path);
		}
		return S_OK;

	}catch(hresult_exception &) {
		ASSERT( 0);
		return E_FAIL;
	}

	return S_OK;
}

STDMETHODIMP CSvnTester::update(BSTR p_path, VARIANT_BOOL p_byAPI)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	try {
		if( p_byAPI == VARIANT_TRUE)
		{
#if(USESVN)
			if( getLoginData())
			{
				m_apiSvn = new HiClient( m_username, m_password);
				if( !m_apiSvn) {
					AfxMessageBox( "SVN implementation client object could not be created!");
					throw hresult_exception( E_FAIL);
				}

				std::string path;
				CopyTo( p_path, path);

				m_apiSvn->getLatest( path);
			}
			else throw hresult_exception(E_FAIL);
#else
			return E_NOTIMPL;
#endif
		}
		else
		{
			m_cmdSvn = new CmdClient( false /*m_svnShowCmdLineWindows*/, true /*m_svnRedirectOutput*/); 
			if( !m_cmdSvn) {
				AfxMessageBox( "SVN implementation client object could not be created!");
				throw hresult_exception( E_FAIL);
			}

			std::string path;
			CopyTo( p_path, path);
			
			m_cmdSvn->getLatest( path);
		}
		return S_OK;

	}catch(hresult_exception &) {
		ASSERT( 0);
		return E_FAIL;
	}

	return S_OK;
}

bool createFile( CString& p_path, CString& p_res)
{
const char* data = 
"### --File created by GME-- ###\n\
### Section for configuring tunnel agents.\n\
[tunnels]\n\
### Configure svn protocol tunnel schemes here.\n\
### the 'ssh' scheme is defined.  You can define other schemes to\n\
### be used with 'svn+scheme://hostname/path' URLs.  A scheme\n\
### definition is simply a command, optionally prefixed by an\n\
### environment variable name which can override the command if it\n\
### is defined.  The command (or environment variable) may contain\n\
### arguments, using standard shell quoting for arguments with\n\
### spaces.  The command will be invoked as:\n\
###   <command> <hostname> svnserve -t\n\
### (If the URL includes a username, then the hostname will be\n\
### passed to the tunnel agent as <user>@<hostname>.)  If the\n\
### built-in ssh scheme were not predefined, it could be defined\n\
### as:\n\
#ssh = $SVN_SSH ssh\n\
#ssh = c:\\bin\\plink.exe\n\
#ssh = c:\\bin\\TortoisePlink.exe";

	CString &res = p_res; // it is not cleared !!!
	FILE *f = 0;
	f = fopen( (LPCTSTR) p_path, "r");
	if( !f)
	{
		f = fopen( (LPCTSTR) p_path, "w");
		int sz = 0;
		if( f) sz = fwrite( data, strlen(data), 1, f);

		if( sz == 1)
		{
			res.Append( "OK - Configuration file '");
			res.Append( p_path);
			res.Append( "' created succesfully.\n");
		}
		else
		{
			res.Append( "FAILED - Configuration file '");
			res.Append( p_path);
			res.Append( "' was not found and could not be created.\n");
			return false;
		}
	}
	else
	{
		res.Append( "OK - Configuration file '");
		res.Append( p_path);
		res.Append( "' found.\n");
	}

	fclose( f);
	return true;
}

bool createDir( const CString& p_path, const CString& p_dirFriendlyName, CString& p_res)
{
	WIN32_FILE_ATTRIBUTE_DATA attr;
	BOOL    succ = TRUE;
	CString &res = p_res; // it is not cleared !!!

	succ = GetFileAttributesEx( p_path, GetFileExInfoStandard, &attr);
	if( succ == TRUE && ( FILE_ATTRIBUTE_DIRECTORY == (attr.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))) { 
		res.Append( "OK - ");
		res.Append( p_dirFriendlyName);
		res.Append( " folder found: '");
		res.Append( p_path);
		res.Append( "'.\n");
	} else
	{
		succ = CreateDirectory( p_path, NULL);
		if( succ == TRUE)
		{
			res.Append( "OK - ");
			res.Append( p_dirFriendlyName);
			res.Append( " folder created succesfully: '");
			res.Append( p_path);
			res.Append( "'.\n");
		}
		else
		{
			res.Append( "FAILED - ");
			res.Append( p_dirFriendlyName);
			res.Append( " folder was not found and could not be created: '");
			res.Append( p_path);
			res.Append( "'.\n");
			return false;
		}
	}

	return true;
}

STDMETHODIMP CSvnTester::testSubversionSettingsDir(BSTR* p_resultMsg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString str_res;
	CComBSTR res;

	try 
	{
		char        app_data_path[ _MAX_PATH];
		if( !SHGetSpecialFolderPath( NULL, app_data_path, CSIDL_APPDATA, true)) //most likely C:\Documents and Settings\<username>\Application Data
		{
			res.Append( "FAILED - Application Data folder in user directory could not be found.");
			return S_OK;
		}
		else
		{
			res.Append( "OK - Application Data folder found: '");
			res.Append( app_data_path);
			res.Append( "'.\n");

			CString path;
			
			path = CString( app_data_path) + "\\Subversion";
			if( !createDir( path, "Subversion", str_res))
				throw hresult_exception(E_FAIL); // error

			path += "\\config";         // a file
			createFile( path, str_res); // retval disregarded here

			path = CString( app_data_path) + "\\Subversion\\auth";
			if( !createDir( path, "Subversion/auth", str_res))
				throw hresult_exception(E_FAIL); // error

			path = CString(app_data_path) + "\\Subversion\\auth\\svn.simple";
			if( !createDir( path, "Credential directory [Subversion/auth/svn.simple]", str_res))
				throw hresult_exception(E_FAIL); // error

			path = CString(app_data_path) + "\\Subversion\\auth\\svn.ssl.server";
			if( !createDir( path, "Certificates directory [Subversion/auth/svn.ssl.server]", str_res))
				throw hresult_exception(E_FAIL); // error

		}
		
		CopyTo( str_res, &res);
		*p_resultMsg = res.Detach();
	}
	catch(hresult_exception &) {
		CopyTo( str_res, &res);
		*p_resultMsg = res.Detach();

		ASSERT( 0);
		return E_FAIL;
	}

	return S_OK;
}
STDMETHODIMP CSvnTester::testSubversionSettingsDlg()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CComBSTR res;
	HRESULT hr = testSubversionSettingsDir( &res);
	
	CString rstr;
	CopyTo( res, rstr);
	rstr.Replace( "\n", "\r\n");

	CSvnTestDlg d;
	d.setContent( rstr);
	d.DoModal();

	return hr;
}

bool CSvnTester::getLoginData()
{
	CSvnLoginDlg dlg( 1); // uname & passw
	dlg.m_user     = g_storedUserName.c_str();
	dlg.m_password = g_storedPassWord.c_str();
	dlg.m_database = m_svnUrl.c_str();
	//dlg.disableSshOption() is not called on dlg
	// because we don't know too much about the 
	// parameters

	if( dlg.DoModal() == IDOK )
	{
		g_storedUserName = m_username = dlg.m_user;
		g_storedPassWord = m_password = dlg.m_password;
		return true;
	}
	else
	{
		m_username = "";
		m_password = "";
	}

	if( dlg.wasAborted())
		throw hresult_exception(E_FAIL);

	return false;
}
