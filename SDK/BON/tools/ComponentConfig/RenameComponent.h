#pragma warning ( disable : 4786 )

#include "VcprojHandler.h"
#include <fstream>
#include <map>
#include <cassert>
using namespace std;

/************************SearchAndReplace class************************
Written by Jonathan Sprinkle

Purpose:  Perform a case-sensitive search and replace of strings
					in a file.

Usage:		For static calls only, modifies files on the system level,
					not the filestream level.

	Parameters:
			--- const map<string,string> &_search_replace
					contains the LHS, RHS replacement strings.  if empty, no changes
					will be made to the interior of the file (although it may still
					be renamed).

			--- const string &_oldname
					the name of the file in which to perform the search and replace

			--- const string &_newname=""
					the name of the file to be created.  if left blank, it is
					the same as the old file name.
					
			--- bool deleteOld=true
				  if true, the old file will be deleted, else it will be kept

**********************************************************************/

class SearchAndReplace
{
public:
	static void replace( const map<string,string> &_search_replace, const string &_oldname, const string &_newname="", bool deleteOld=true )
	{
		string _actualnewname;
		if( (_newname.length( ) == 0) || (_newname == _oldname))
		{ 
			_actualnewname = "__" + _oldname;
			assert( deleteOld );
		}
		else
		{
			_actualnewname = _newname;
		}
		std::ifstream _old( _oldname.data( ) );
		std::ofstream _new( _actualnewname.data( ) );
		if( _old.good( ) && _new.good( ) )
		{
			while( !_old.eof( ) && _old.good( ) )
			{
				string line;
				getline( _old, line );
				map<string,string>::const_iterator _it = _search_replace.begin( );
				for( ; _it != _search_replace.end( ); _it++ )
				{
					line = replace( line, (*_it).first, (*_it).second );
				}
				_new << line << endl;
			}
		}
		_old.close( );
		_new.close( );
		if( _newname != _actualnewname ) // deleteOld will be true...
		{
			assert( deleteOld );
			DeleteFile( _oldname.data( ) );
			MoveFile( _actualnewname.data( ), _oldname.data( ) );
		}
		else if( deleteOld )
		{
			DeleteFile( _oldname.data( ) );
		}
		return;
	}
protected:
	static string replace( const string str, const string &_search, const string &_replace )
	{
		string result=str;
		int length = _search.length( );
		int replaceLoc = result.find( _search );
		if( replaceLoc != -1 )
		{
			result.replace( replaceLoc, length, _replace );
		}
		return result;
	}
};

// end class SearchAndReplace

/************************RenameComponent7 class*************************
ReWritten by Zoltan Molnar

Purpose:	Similar to RenameComponent, for Visual Studio 7

					Files modified:
					- *.vcproj --> becomes [componentName]originalName.vcproj
									--> changes all calls to the component identity
											to match that of 'componentName' instead of 'Component'
					- *.def --> sets file access rights to normal
									--> changes the name of the output .DLL
									--> resets file access rights to readonly
					- *.sln --> changes the name of the .vcproj file included, and
											the name of the component it represents to reflect
											the wishes of the interpreter writer

**********************************************************************/
class RenameComponent7
{
public:
	RenameComponent7
		( bool is_gmeloc_changed
		, bool is_compname_changed
		, int comp_tech
		, std::vector<std::string>& m_gmeSourceFiles
		, std::string& strBONPath
		, string _vcprojFileName
		, string _componentName  // new component name
		, string _oldComponentName
		)

		: oldVcprojFileName( _vcprojFileName )
		, newVcprojFileName( _vcprojFileName )
		, oldComponentName( _oldComponentName )
		, componentName( _componentName )
	{
		switch( comp_tech) // component technology
		{
		case 1: tech_name = "BONComponent"; // BON
			break;
		case 2: tech_name = "Interpreter"; // Old BON
			break;
		case 3: tech_name = "Component"; // Raw
			break;
		case 4: tech_name = "BON2Component"; // BON2
			break;
		};
		//AfxMessageBox( tech_name.c_str());

		bool ini = false;
		if( oldComponentName == "" )
		{
			is_gmeloc_changed = ini = true; // initially need to update the settings

			// component name will be the technology name
			oldComponentName = tech_name;
			
			// calculate the new vcproj filename
			newVcprojFileName = componentName + tech_name + ".vcproj";
			componentName += tech_name;
		}
		else
		{
			componentName += tech_name;
			oldComponentName += tech_name;
			int pos = newVcprojFileName.find( oldComponentName);
			if( pos != string::npos) // found
			{
				newVcprojFileName.replace( pos, oldComponentName.length(), componentName);
			}
		}

		proj2sln["Component.vcproj"]		= "Component.sln";
		proj2sln["BONComponent.vcproj"]		= "BONComponent.sln";
		proj2sln["BON2Component.vcproj"]	= "BON2Component.sln";

		if( !oldComponentName.empty())
			proj2sln[ oldComponentName + ".vcproj"] = tech_name + ".sln";

		/*if( !oldComponentName.empty())
		{
			if( oldVcprojFileName.find( "BON2" ) != -1 )
			{
				proj2sln[oldComponentName + "BON2Component.vcproj"] = "BON2Component.sln";
			}
			else if( oldVcprojFileName.find( "BON" ) != -1 )
			{
				proj2sln[oldComponentName + "BONComponent.vcproj"] = "BONComponent.sln";
			}
			else
			{
				proj2sln[oldComponentName + "Component.vcproj"] = "Component.sln";
			}
		}*/
		
		if( is_gmeloc_changed || is_compname_changed)
		{
			// make a backup file is we are going to touch the project file
			bool can_delete = false;
			CString backup = oldVcprojFileName.c_str();
			backup += ".old";
			SetLastError( 0);
			
			// make a copy of the original project file with ".old" extension
			CopyFile( oldVcprojFileName.c_str(), (LPCTSTR)backup, FALSE); // FALSE: don't fail if ".old" already exists, overwrite it
			
			if( 0 == GetLastError()) // success
				can_delete = true;

			if( 0 == VcprojHandler::doCompRenameAndGmeRelocate
				( is_gmeloc_changed
				, is_compname_changed
				, oldComponentName.c_str()
				, componentName.c_str()
				, oldVcprojFileName.c_str()
				, newVcprojFileName.c_str()
				, m_gmeSourceFiles
				, strBONPath))
			{
				if( is_compname_changed && can_delete) // delete the old project file only if the name has changed, and the backup was successful
				{
					DeleteFile( oldVcprojFileName.c_str());
				}
				
				if( is_compname_changed) // these are changing only if compname_changed
				{
					doSln( );
					doDef(ini);
				}
			}
			else
				throw "Component Rename failed";
		}
	}

	string getComponentName( ) { return componentName; }

protected:
	string oldVcprojFileName;
	string newVcprojFileName;
	string oldComponentName;
	string componentName;
	string tech_name;
	map<string, string> proj2sln;

	void doDef( bool first = false )
	{
		map<string,string> _s_r;
		if( first)
			_s_r[ "Component.DLL"] = componentName + ".DLL";
		else
			_s_r[oldComponentName + ".DLL"] = componentName + ".DLL";
		SetFileAttributes( "component.def", FILE_ATTRIBUTE_NORMAL );
		SearchAndReplace::replace( _s_r, "component.def" );
		SetFileAttributes( "component.def", FILE_ATTRIBUTE_READONLY );
	}
	void doSln( )
	{
		assert( proj2sln.find(oldVcprojFileName) != proj2sln.end( ) );
		string slnName = proj2sln[oldVcprojFileName];
		map<string,string> _s_r;
		_s_r["\"" + oldComponentName + "\""] = "\"" + componentName + "\"";
		_s_r[oldVcprojFileName] = newVcprojFileName;
		SearchAndReplace::replace( _s_r, slnName );
	}
};

/************************RenameComponent class*************************
Written by Jonathan Sprinkle

Purpose:	To transform a standard GME Interpreter compiled with visual
					studio 6.0 (either BON or COM based) from the standard
					component name to the customized name of the component.  This
					allows interpreter writers to create a DLL that is the name
					of their component, as well as including more than one
					component in a workspace/solution.

					Files modified:
					- *.dsp --> becomes [componentName]originalName.dsp
									--> changes all calls to the component identity
											to match that of 'componentName' instead of 'Component'
					- *.def --> sets file access rights to normal
									--> changes the name of the output .DLL
									--> resets file access rights to readonly
					- *.dsw --> changes the name of the .DSP file included, and
											the name of the component it represents to reflect
											the wishes of the interpreter writer

**********************************************************************/
class RenameComponent	// obsolete, please use RenameComponent7 instead
{
public:
	RenameComponent( string _componentName, string _dspFileName, string _oldComponentName="Component" )
		: componentName( _componentName ), oldComponentName( _oldComponentName ),
			componentizedFilename( _componentName + _dspFileName ),
			dspFileName( _dspFileName )
	{
		if( oldComponentName.length( ) > 0 && componentizedFilename.find( oldComponentName ) != -1 )
		{
			componentizedFilename.replace( componentizedFilename.find( oldComponentName ), oldComponentName.length( ), "" );
		}
		if( oldComponentName == "" ) oldComponentName = "Component";
		dsp2dsw["Component.dsp"]		= "Component.dsw";
		dsp2dsw["BONComponent.dsp"]	= "BONComponent.dsw";
		dsp2dsw["BON2Component.dsp"]	= "BON2Component.dsw";
		if( oldComponentName.compare( "Component" ) != 0 )
		{
			if( _dspFileName.find( "BON2" ) != -1 )
			{
				dsp2dsw[oldComponentName + "BON2Component.dsp"] = "BON2Component.dsw";
			}
			else if( _dspFileName.find( "BON" ) != -1 )
			{
				dsp2dsw[oldComponentName + "BONComponent.dsp"] = "BONComponent.dsw";
			}
			else
			{
				dsp2dsw[oldComponentName + "Component.dsp"] = "Component.dsw";
			}
		}
		doDsp( );
		doDef( );
		doDsw( );
	}
	string getComponentizedFilename( ) { return componentizedFilename; }
	string getComponentName( ) { return componentName; }
	map<string, string> dsp2dsw;

protected:
	string componentName;
	string componentizedFilename;
	string dspFileName;
	string oldComponentName;
	void doDsp( )
	{
		map<string,string> _s_r;
		_s_r["\"" + oldComponentName + " "] = "\"" + componentName + " ";
		_s_r["\"" + oldComponentName + "\""] = "\"" + componentName + "\"";
		_s_r[oldComponentName + ".dll"] = componentName + ".dll";
		SearchAndReplace::replace( _s_r, dspFileName, componentizedFilename );
	}
	void doDef( )
	{
		map<string,string> _s_r;
		_s_r[oldComponentName + ".DLL"] = componentName + ".DLL";
		SetFileAttributes( "component.def", FILE_ATTRIBUTE_NORMAL );
		SearchAndReplace::replace( _s_r, "component.def" );
		SetFileAttributes( "component.def", FILE_ATTRIBUTE_READONLY );
	}
	void doDsw( )
	{
		assert( dsp2dsw.find(dspFileName) != dsp2dsw.end( ) );
		string dswName = dsp2dsw[dspFileName];
		map<string,string> _s_r;
		_s_r["\"" + oldComponentName + "\""] = "\"" + componentName + "\"";
		_s_r[dspFileName] = componentizedFilename;
		SearchAndReplace::replace( _s_r, dswName );
	}

};

// end class RenameComponent
