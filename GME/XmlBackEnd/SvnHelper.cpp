#include "stdafx.h"
#include "SvnHelper.h"
#include "SvnTestDlg.h"
#include "svauto.h"
#include "..\Common\CommonMfc.h"

CSvnHelper::CSvnHelper(void)
{
}

CSvnHelper::~CSvnHelper(void)
{
}

//static
void CSvnHelper::invokeInfo( const std::string& p_url, bool p_apiAccess, bool p_recursive )
{
	CComPtr<ISvnTester> p;
	p.CoCreateInstance( L"Mga.XmlbackEnd.SvnTester");
	if( !p) {
		AfxMessageBox( "Info test-command failed because could not create test object.");
		return;
	}

	CComBSTR       url   = p_url.c_str();
	CComBSTR       res;
	VARIANT_BOOL   byapi = p_apiAccess?VARIANT_TRUE : VARIANT_FALSE;
	VARIANT_BOOL   recur = p_recursive?VARIANT_TRUE : VARIANT_FALSE;

	if( SUCCEEDED( p->info( url, byapi, recur, &res)))
	{
		CString r; CopyTo( res, r);
		r.Replace( "\n", "\r\n");
		CSvnTestDlg d;
		d.setContent( r);
		d.DoModal();
		//AfxMessageBox( r);
	}
	else
		AfxMessageBox( ("Info test-command failed with " + p_url).c_str());
}

//static
void CSvnHelper::invokeStatus( const std::string& p_localPath, bool p_apiAccess)
{
	CComPtr<ISvnTester> p;
	p.CoCreateInstance( L"Mga.XmlbackEnd.SvnTester");
	if( !p) {
		AfxMessageBox( "Status test-command failed because could not create test object.");
		return;
	}

	CComBSTR       path   = p_localPath.c_str();
	CComBSTR       res;
	VARIANT_BOOL   byapi = p_apiAccess?VARIANT_TRUE : VARIANT_FALSE;
	VARIANT_BOOL   onsrv = VARIANT_TRUE;

	if( SUCCEEDED( p->status( path, byapi, onsrv, &res)))
	{
		CString r; CopyTo( res, r);
		r.Replace( "\n", "\r\n");
		CSvnTestDlg d;
		d.setContent( r);
		d.DoModal();
		//AfxMessageBox( r);
	}
	else
		AfxMessageBox( ("Status test-command failed with " + p_localPath).c_str());
}

//static
void CSvnHelper::invokeCleanUp( const std::string& p_localPath, bool p_apiAccess)
{
	CComPtr<ISvnTester> p;
	p.CoCreateInstance( L"Mga.XmlbackEnd.SvnTester");
	if( !p) {
		AfxMessageBox( "CleanUp command failed because could not create invoker object.");
		return;
	}

	CComBSTR       path   = p_localPath.c_str();
	CComBSTR       res;
	VARIANT_BOOL   byapi = p_apiAccess?VARIANT_TRUE : VARIANT_FALSE;

	if( SUCCEEDED( p->cleanup( path, byapi, &res)))
	{
		CString r; CopyTo( res, r);
		r.Replace( "\n", "\r\n");
		CSvnTestDlg d;
		d.setContent( r);
		d.DoModal();
		//AfxMessageBox( r);
	}
	else
		AfxMessageBox( ("CleanUp command failed with " + p_localPath).c_str());
}

//static
void CSvnHelper::invokeResolve( const std::string& p_localPath, bool p_apiAccess, bool p_recursive)
{
	CComPtr<ISvnTester> p;
	p.CoCreateInstance( L"Mga.XmlbackEnd.SvnTester");
	if( !p) {
		AfxMessageBox( "Resolve command failed because could not create invoker object.");
		return;
	}

	CComBSTR       path   = p_localPath.c_str();
	VARIANT_BOOL   byapi = p_apiAccess?VARIANT_TRUE : VARIANT_FALSE;
	VARIANT_BOOL   recur = p_recursive?VARIANT_TRUE : VARIANT_FALSE;

	if( SUCCEEDED( p->resolve( path, byapi, recur)))
		AfxMessageBox( ("Resolve command executed with " + p_localPath).c_str(), MB_ICONINFORMATION);
	else
		AfxMessageBox( ("Resolve command failed with " + p_localPath).c_str());
}

//static
void CSvnHelper::invokeCheckout( const std::string& p_url, const std::string& p_localPath, bool p_apiAccess)
{
	CComPtr<ISvnTester> p;
	p.CoCreateInstance( L"Mga.XmlbackEnd.SvnTester");
	if( !p) {
		AfxMessageBox( "Checkout command failed because could not create invoker object.");
		return;
	}

	CComBSTR       url    = p_url.c_str();
	CComBSTR       path   = p_localPath.c_str();
	VARIANT_BOOL   byapi = p_apiAccess?VARIANT_TRUE : VARIANT_FALSE;

	if( SUCCEEDED( p->checkout( url, path, byapi, VARIANT_TRUE)))
		AfxMessageBox( ("Checkout command executed with " + p_localPath).c_str(), MB_ICONINFORMATION);
	else
		AfxMessageBox( ("Checkout command failed with " + p_localPath).c_str());
}

//static
void CSvnHelper::invokeCommit( const std::string& p_localPath, bool p_apiAccess)
{
	CComPtr<ISvnTester> p;
	p.CoCreateInstance( L"Mga.XmlbackEnd.SvnTester");
	if( !p) {
		AfxMessageBox( "Commit command failed because could not create invoker object.");
		return;
	}

	CComBSTR       path   = p_localPath.c_str();
	VARIANT_BOOL   byapi = p_apiAccess?VARIANT_TRUE : VARIANT_FALSE;

	if( SUCCEEDED( p->commit( path, byapi, VARIANT_TRUE)))
		AfxMessageBox( ("Commit command executed with " + p_localPath).c_str(), MB_ICONINFORMATION);
	else
		AfxMessageBox( ("Commit command failed with " + p_localPath).c_str());
}

//static
void CSvnHelper::invokeUpdate( const std::string& p_localPath, bool p_apiAccess)
{
	CComPtr<ISvnTester> p;
	p.CoCreateInstance( L"Mga.XmlbackEnd.SvnTester");
	if( !p) {
		AfxMessageBox( "Update command failed because could not create invoker object.");
		return;
	}

	CComBSTR       path  = p_localPath.c_str();
	VARIANT_BOOL   byapi = p_apiAccess?VARIANT_TRUE : VARIANT_FALSE;

	if( SUCCEEDED( p->update( path, byapi)))
		AfxMessageBox( ("Update command executed with " + p_localPath).c_str(), MB_ICONINFORMATION);
	else
		AfxMessageBox( ("Update command failed with " + p_localPath).c_str());
}

//static 
void CSvnHelper::invokeLock( const std::string& p_localPath, bool p_apiAccess)
{
	CComPtr<ISvnTester> p;
	p.CoCreateInstance( L"Mga.XmlbackEnd.SvnTester");
	if( !p) {
		AfxMessageBox( "Lock command failed because could not create invoker object.");
		return;
	}

	CComBSTR       path  = p_localPath.c_str();
	VARIANT_BOOL   byapi = p_apiAccess?VARIANT_TRUE : VARIANT_FALSE;

	if( SUCCEEDED( p->lock( path, VARIANT_FALSE, byapi)))
		AfxMessageBox( ("Lock command executed with " + p_localPath).c_str(), MB_ICONINFORMATION);
	else
		AfxMessageBox( ("Lock command failed with " + p_localPath).c_str());
}

//static 
void CSvnHelper::invokeUnlock( const std::string& p_localPath, bool p_apiAccess)
{
	CComPtr<ISvnTester> p;
	p.CoCreateInstance( L"Mga.XmlbackEnd.SvnTester");
	if( !p) {
		AfxMessageBox( "Unlock command failed because could not create invoker object.");
		return;
	}

	CComBSTR       path  = p_localPath.c_str();
	VARIANT_BOOL   byapi = p_apiAccess?VARIANT_TRUE : VARIANT_FALSE;

	if( SUCCEEDED( p->unlock( path, VARIANT_FALSE, byapi)))
		AfxMessageBox( ("Unlock command executed with " + p_localPath).c_str(), MB_ICONINFORMATION);
	else
		AfxMessageBox( ("Unlock command failed with " + p_localPath).c_str());
}

//static
void CSvnHelper::invokeTestSubDirs()
{
	CComPtr<ISvnTester> p;
	p.CoCreateInstance( L"Mga.XmlbackEnd.SvnTester");
	if( !p) {
		AfxMessageBox( "Testing connectivity failed because could not create invoker object.");
		return;
	}

	p->testSubversionSettingsDlg();
}
