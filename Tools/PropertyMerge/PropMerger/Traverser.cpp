#include "StdAfx.h"
#include ".\traverser.h"
#include <fstream>
#include <algorithm>

#define _WIN32_DCOM  // for COInitializeEx

const char * const_default_out_dir = "clip/";

Traverser::Traverser( const std::string& p_path, const std::string& p_dirPath, bool p_hier1d, bool p_hier2d)
	: m_path( p_path)
	, m_inDirPath( p_dirPath)
	, m_hier1d( p_hier1d)
	, m_hier2d( p_hier2d)
{
	setPathPrefix();

	//std::cout << ( ( m_hier1d||m_hier2d)? "Input files will be searched for in subdirectories" : "Input files will be taken from one dir") << std::endl;

	// init COM
	HRESULT hr = CoInitializeEx(0, COINIT_APARTMENTTHREADED);
	ASSERT( SUCCEEDED( hr));
	//BOOL rt = AfxOleInit();
	//ASSERT( rt);
}

Traverser::~Traverser(void)
{
	m_xmlParser.Release();
	m_theGme.Release();

	//m_theProj.Release();
	//m_theTerr.Release();

	// uninit COM
	CoUninitialize();
}

void Traverser::setPathPrefix()
{
	if( !m_inDirPath.empty())
	{
		m_pathPrefix = m_inDirPath;
		if( m_pathPrefix[ m_pathPrefix.length() - 1] != '/'
		 ||	m_pathPrefix[ m_pathPrefix.length() - 1] != '\\')
			m_pathPrefix.append( "/");
	}
	else
	{
		std::string::size_type p = m_path.find_last_of( '\\');
		if( p == std::string::npos)
			p = m_path.find_last_of( '/');

		if( p != std::string::npos)
		{
			m_pathPrefix = m_path.substr( 0, p + 1); // tailing '\\' also
		}

		m_pathPrefix.append( const_default_out_dir);
	}
}

void Traverser::loadIgnorables()
{
	std::string ign_f_name( m_pathPrefix.c_str());
	ign_f_name.append( "objs2ignore.txt");

	std::ifstream f;
	f.open( ign_f_name.c_str());

	if( f)
	{
		char buff[42];
		while( f && f.getline( &buff[0], sizeof( buff) - 1, '\n'))
		{
			m_ignoreList.push_back( std::string( buff));
		}
		
		f.close();
	}
	else
	{
		consoleMsg( "Could not open ignoreable object list file: ", MSG_ERROR);
		consoleMsg( ign_f_name.c_str(), MSG_ERROR);
	}
}

bool Traverser::foundAsIgnoreable( const CComBSTR& p_objId)
{
	char *buff;
	CopyTo( p_objId, &buff);
	std::string o_id( buff);
	if( buff) delete [] buff;

	return std::find( m_ignoreList.begin(), m_ignoreList.end(), o_id) != m_ignoreList.end();
}

CComPtr<IGMEOLEApp> Traverser::getGME( IMgaProject *p_project)
{
	CComPtr<IGMEOLEApp> ret;
	if( !p_project) return ret;

	CComBSTR bstrName("GME.Application");
	CComQIPtr<IMgaClient> pClient;
	HRESULT hr = p_project->GetClientByName( bstrName, &pClient);
	if( FAILED( hr)) 
	{
		//ASSERT(0);
		//throw "Can't retrieve GME Application object";
	}
	if( SUCCEEDED( hr) && pClient) {
		CComQIPtr<IDispatch> pDispatch;
		COMTHROW( pClient->get_OLEServer( &pDispatch));
		if( pDispatch) {
			COMTHROW( pDispatch.QueryInterface( &ret));
		}
	}

	return ret;
}

void Traverser::stdConsoleMsg( const char *    p_msg, int p_type, bool p_prefixed)
{
	std::cout << std::endl;

	if( p_prefixed)
	{
		switch( p_type) {	
			case MSG_ERROR:    std::cout << "E: ";break;
			case MSG_INFO:     std::cout << "I: ";break;
			case MSG_WARNING:  std::cout << "W: ";break;
			case MSG_NORMAL:
			default:           std::cout << "N: ";break;
		}
	} 

	std::cout << (p_msg ? p_msg:"<null>");
}

void Traverser::stdConsoleMsg( const CComBSTR& p_msg, int p_type, bool p_prefixed)
{
	std::cout << std::endl;

	if( p_prefixed)
	{
		switch( p_type) {	
			case MSG_ERROR:    std::cout << "E: ";break;
			case MSG_INFO:     std::cout << "I: ";break;
			case MSG_WARNING:  std::cout << "W: ";break;
			case MSG_NORMAL:
			default:           std::cout << "N: ";break;
		}
	} 

	char * msg = 0;
	CopyTo( p_msg, &msg); // msg will be freed by us
	std::cout << (msg ? msg:"<null>");
	if( msg) 
		delete [] msg;
}

void Traverser::consoleMsg( const CComBSTR& p_msg, int p_type, bool p_prefixed)
{
	if( !m_theGme) 
	{
		stdConsoleMsg( p_msg, p_type, p_prefixed); 
		return;
	}
	m_theGme->ConsoleMessage( p_msg, (msgtype_enum) p_type);
}

void Traverser::consoleMsg( const char *    p_msg, int p_type, bool p_prefixed)
{
	if( !m_theGme)
	{
		stdConsoleMsg( p_msg, p_type, p_prefixed); 
		return;
	}
	m_theGme->ConsoleMessage( CComBSTR( p_msg), (msgtype_enum) p_type);
}

bool Traverser::fileFound( const char * p_file)
{
	FILE *f = fopen( p_file, "r");
	if( f) // file present
	{
		fclose( f);
		return true; 
	}

	return false;
}

bool Traverser::fileFound( const CComBSTR& p_file)
{
	char *buff = 0;
	CopyTo( p_file, &buff);

	bool rv = fileFound( buff);

	if( buff) delete [] buff;

	return rv;
}

void Traverser::createMgaDtd()
{
	std::string dtd_f_name( m_pathPrefix.c_str());
	dtd_f_name.append( "mga.dtd");

	if( fileFound( dtd_f_name.c_str())) return;

	//consoleMsg( "Could not find mga.dtd file in the directory. Please copy it there.", MSG_ERROR);
	//throw -1;

	char * data = 0;
	DWORD  len  = 0;
	bool   sc   = true;

	HMODULE hm = 0;//GetModuleHandle("PropMerge.dll");
	if( !hm) sc = false;
	else {
		HRSRC res1 = FindResource(hm, "IDR_MGA.DTD", "DTD"); // mga.dtd is copied into this resource
		if( !res1) sc = false;
		else {
			HGLOBAL res2 = LoadResource(hm, res1);
			if( !res2) sc = false;
			else {
				data = ( char* )LockResource( res2);
				if( !data) sc = false;
				else {
					len = SizeofResource(hm, res1);
				}
			}
		}
	}

	FILE *f;
	// create, if we have the content
	if( sc)
		f = fopen( dtd_f_name.c_str(), "w");

	if( !sc || !f || !data || !len)
	{
		consoleMsg( "Could not create mga.dtd file in clip directory. Please copy it there.", MSG_ERROR);
		throw -1;
	}

	fwrite( data, len, 1, f);
	fclose( f);
}

CComBSTR Traverser::makeFileName( const CComBSTR& p_gd, bool *p_fileExists)
{
	CComBSTR ret;
	ret.Append( m_pathPrefix.c_str());
	if( m_hier1d || m_hier2d)
	{
		char *bf = 0;
		CopyTo( p_gd, &bf);
		if( bf)
		{
			ret.Append( std::string( 1, bf[1]).c_str()); // the 2nd char is the first digit since it starts with '{'
			if( m_hier2d)
				ret.Append( std::string( 1, bf[2]).c_str()); // the two digit option
			ret.Append( "/");
			delete [] bf;
		}
	}
	ret.AppendBSTR( p_gd);

	*p_fileExists = fileFound( ret);
	return ret;
}

template <typename T>
void Traverser::dealWith( IMgaProject *p_project, IMgaTerritory *p_terr, T   *p_item)
{
	if( !m_xmlParser) return;
	if( !p_item) 
	{
		ASSERT(0);
		return;
	}

	CComBSTR gd;
	COMTHROW( p_item->GetGuidDisp( &gd));

	bool file_exists = false;
	CComBSTR fname = makeFileName( gd, &file_exists);

	try
	{
		COMTHROW( p_project->CommitTransaction());
	}
	catch(...)
	{
		COMTHROW( p_project->AbortTransaction());
		consoleMsg( "Error before commiting to ", MSG_ERROR);
		consoleMsg( gd, MSG_ERROR);
	}

	try
	{
		if( file_exists)
			COMTHROW( m_xmlParser->ParseFCOs( p_item, fname));
		else if( !foundAsIgnoreable( gd))
		{
			fname.Append( " not found for object below ");
			consoleMsg( fname, MSG_ERROR);//("No such file found as " + fname).c_str(), MSG_ERROR);
			consoleMsg( gd, MSG_ERROR, false);
		}
	}
	catch(...)
	{
		consoleMsg( "Error during parsing into ", MSG_ERROR);
		consoleMsg( gd, MSG_ERROR);
	}
	
	try 
	{
		COMTHROW( p_project->BeginTransaction( p_terr));
	}
	catch(...)
	{
		consoleMsg( "Could not restart transaction after parsing into ", MSG_ERROR);
		consoleMsg( gd, MSG_ERROR);
		throw;
	}
}

void Traverser::traverse( IMgaProject *p_project, IMgaTerritory *p_terr, IMgaFolder *p_curr)
{
	if( !p_curr) return;

	CComPtr<IMgaFolders> subs;
	CComPtr<IMgaFCOs>    objs;
	long                 len = 0;

	COMTHROW( p_curr->get_ChildFolders( &subs));
	if( subs) COMTHROW( subs->get_Count( &len));
	for( long i = 1; i <= len; ++i)
	{
		CComPtr<IMgaFolder> item_i;
		COMTHROW( subs->get_Item( i, &item_i));

		if( !item_i)
		{
			ASSERT(0);
			continue;
		}

		dealWith( p_project, p_terr, item_i.p);

		traverse( p_project, p_terr, item_i);
	}

	len = 0; // will be reused
	COMTHROW( p_curr->get_ChildFCOs( &objs));
	if( objs) COMTHROW( objs->get_Count( &len));
	for( long i = 1; i <= len; ++i)
	{
		CComPtr<IMgaFCO> item_i;
		COMTHROW( objs->get_Item( i, &item_i));

		if( !item_i)
		{
			ASSERT(0);
			continue;
		}

		dealWith( p_project, p_terr, item_i.p);

		objtype_enum ot;
		COMTHROW( item_i->get_ObjType( &ot));
		if( ot == OBJTYPE_MODEL)
		{
			CComQIPtr<IMgaModel> item_m( item_i);
			ASSERT( item_m);
			traverse( p_project, p_terr, item_m);
		}
	}
}

void Traverser::traverse( IMgaProject *p_project, IMgaTerritory *p_terr, IMgaModel  *p_curr)
{
	if( !p_curr) return;

	CComPtr<IMgaFolders> subs;
	CComPtr<IMgaFCOs>    objs;
	long                 len = 0;

	COMTHROW( p_curr->get_ChildFCOs( &objs));
	if( objs) COMTHROW( objs->get_Count( &len));
	for( long i = 1; i <= len; ++i)
	{
		CComPtr<IMgaFCO> item_i;
		COMTHROW( objs->get_Item( i, &item_i));

		if( !item_i)
		{
			ASSERT(0);
			continue;
		}

		dealWith( p_project, p_terr, item_i.p);

		objtype_enum ot;
		COMTHROW( item_i->get_ObjType( &ot));
		if( ot == OBJTYPE_MODEL)
		{
			CComQIPtr<IMgaModel> item_m( item_i);
			ASSERT( item_m);
			traverse( p_project, p_terr, item_m);
		}
	}
}


// This is the main component method for interpereters and plugins. 
// May als be used in case of invokeable addons
long Traverser::InvokeEx( IMgaProject *project,  IMgaFCO *currentobj,  
									IMgaFCOs *selectedobjs,  long param) {
	COMTRY {
		CComPtr<IMgaTerritory> terr;

		consoleMsg( "Import started from: ", MSG_INFO);
		consoleMsg( m_pathPrefix.c_str(), MSG_INFO);

		//try {
		//	createMgaDtd();
		//} catch(...) {
		//}
		
		try {
			m_theGme = getGME( project);
		} catch(...) {
			consoleMsg( "Executed outside of the GME application", MSG_INFO);
		}

		loadIgnorables();

		m_xmlParser.CoCreateInstance( L"Mga.MgaParser");
		//m_theProj = CComPtr<IMgaProject>( project);


		COMTHROW( project->CreateTerritory( NULL, &terr));
		COMTHROW( project->BeginTransaction( terr));

		try 
		{
			CComPtr<IMgaFolder> rf;
			COMTHROW( project->get_RootFolder( &rf));

			dealWith( project, terr, rf.p);
			traverse( project, terr, rf);

			COMTHROW( project->CommitTransaction());
		}
		catch( hresult_exception& hr)
		{
			consoleMsg( "HResult Exception during traversal:", MSG_ERROR);
			consoleMsg( hr.what(), MSG_ERROR);

			project->AbortTransaction(); 
			throw; 
		}
		catch(...)
		{
			project->AbortTransaction(); 
			throw; 
		}
	} COMCATCH(;);
}


void Traverser::exec()
{
	CComPtr<IMgaProject> the_proj;
	the_proj.CoCreateInstance( L"Mga.MgaProject");
	if( !the_proj)
	{
		consoleMsg( "Could not create Mga.MgaProject COM class!", MSG_ERROR);
		return;
	}

	if( m_path.empty())
	{
		consoleMsg( "Input file not provided!", MSG_ERROR);
		return;
	}

	CComBSTR b_path( "MGA=");
	b_path.Append( m_path.c_str());
	
	// Open
	try
	{
		COMTHROW( the_proj->Open( b_path));
	}
	catch( hresult_exception& hr)
	{
		consoleMsg( "Could not open project file:", MSG_ERROR);
		consoleMsg( b_path, MSG_ERROR);
		consoleMsg( "HResult Exception during execution:", MSG_ERROR);
		consoleMsg( hr.what(), MSG_ERROR);
		return;
	}

	// Invoke traversal
	try
	{
		COMTHROW( InvokeEx( the_proj, 0, 0, 0));
	}
	catch( hresult_exception& hr)
	{
		consoleMsg( "HResult Exception during execution:", MSG_ERROR);
		consoleMsg( hr.what(), MSG_ERROR);
	}
	catch( ...)
	{
		consoleMsg( "Unknown exception during execution", MSG_ERROR);
	}

	// Save
	try
	{
		COMTHROW( the_proj->Save( b_path, VARIANT_TRUE)); // ?keepoldname?
	}
	catch( hresult_exception& hr)
	{
		consoleMsg( "HResult Exception during save", MSG_ERROR);
		consoleMsg( hr.what(), MSG_ERROR);
	}
	catch( ...)
	{
		consoleMsg( "Unknown exception during save", MSG_ERROR);
	}
	
	// Close
	try
	{
		COMTHROW( the_proj->Close( VARIANT_FALSE)); // ?abort?
	}
	catch( hresult_exception& hr)
	{
		consoleMsg( "HResult Exception during close", MSG_ERROR);
		consoleMsg( hr.what(), MSG_ERROR);
	}
	catch( ...)
	{
		consoleMsg( "Unknown exception during close", MSG_ERROR);
	}
}

