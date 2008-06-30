#include "stdafx.h"
#include "VcprojHandler.h"
#include "Afxwin.h"
#include "vector"

void VcprojHandler::BSTRreplace( const CComBSTR& outf, CComBSTR& outf_new, const CString& old_n, const CString& new_n)
{
	CString r = outf;
	r.Replace( old_n, new_n);
	outf_new = (LPCTSTR) r;
}

int VcprojHandler::swapFiles( CComPtr<VCFile>& spOldFile, const CComBSTR& oldf, const CComBSTR& newf, CComPtr<VCProject>& spProject)
{
	strstream scout;
	HRESULT hr;
	CComQIPtr<VCFile> spNewFile;

	// add the new file
	VARIANT_BOOL var;
	hr = spProject->CanAddFile( newf, &var );
	if( SUCCEEDED( hr ) && var )
	{
		CComPtr<IDispatch> spDispFile;
		hr = spProject->AddFile( newf, &spDispFile );
		if( FAILED( hr ) )
		{
			scout << "Error: cannot add the new source file." << endl;
			return 1;
		}

		spNewFile = spDispFile;
	}
	else
		return 1;

	if( !spNewFile)
	{
		int i = 0;
		++i;
		return 1;
	}

	// Access FileConfigurations collection of the OLD and NEW file
	CComPtr<IDispatch> spDispColOld;
	CComPtr<IDispatch> spDispColNew;
	hr = spOldFile->get_FileConfigurations( &spDispColOld );
	hr = spNewFile->get_FileConfigurations( &spDispColNew );
	if( SUCCEEDED( hr ) )
	{
		CComQIPtr<IVCCollection> spFileConfigsCollOld = spDispColOld;
		CComQIPtr<IVCCollection> spFileConfigsCollNew = spDispColNew;

		// Iterator through the configurations of the NEW file
		long ee = 0;
		hr = spFileConfigsCollNew->get_Count( &ee);
		for( long ii = 1; ii <= ee; ++ii)
		{
			CComPtr<IDispatch> spDispFileConfigNew;
			// Inquire the ii-th configuration
			hr = spFileConfigsCollNew->Item( CComVariant( (long) ii ), &spDispFileConfigNew );
			if( SUCCEEDED( hr ) )
			{
				CComQIPtr<VCFileConfiguration> spFileConfigNew = spDispFileConfigNew;
				// inquire the configuration's name
				CComBSTR configNameNew;
				spFileConfigNew->get_Name( &configNameNew);
				
				// inquire (based on name) this specific configuration of the OLD file
				CComPtr<IDispatch> spDispFileConfigOld;
				CComQIPtr<VCFileConfiguration> spFileConfigOld;
				hr = spFileConfigsCollOld->Item( CComVariant( configNameNew), &spDispFileConfigOld);
				if( SUCCEEDED( hr) )
				{
					spFileConfigOld = spDispFileConfigOld;
				}

				if( spFileConfigOld) // copy settings if old config is available
				{
					// Get the default tool associated with this configuration of this file
					CComPtr<IDispatch> spDispFileToolNew;
					CComPtr<IDispatch> spDispFileToolOld;
					hr = spFileConfigNew->get_Tool( &spDispFileToolNew );
					hr = spFileConfigOld->get_Tool( &spDispFileToolOld );

					if( SUCCEEDED( hr ) )
					{
						CString fname = oldf;
						if( -1 != fname.Find(".cpp")) // found
						{
							CComDispatchDriver fileToolOld( spDispFileToolOld );
							CComDispatchDriver fileToolNew( spDispFileToolNew );
							copyCppSettings( fileToolOld, fileToolNew);
						}
						else if( -1 != fname.Find(".idl"))
						{
							// which tool is set for the new file?
							CComPtr<VCCustomBuildTool> spCustomBuildToolNew;
							CComPtr<VCMidlTool> spMidlToolNew;
							int k = whichIDLTool( spDispFileToolNew, spCustomBuildToolNew, spMidlToolNew);
							if( k == 0) { ASSERT( 0); }
							else if( k == 1) // custom built
							{}
							else if( k == 2) // midl built
							{
								prepareIdlSettingsForMIDL( spMidlToolNew);
							}
						}
					}
					else
						scout << "Error: cannot get the tool associated with the source file." << endl;
				}

			}
			else
				scout << "Error: cannot get the configuration of the source file." << endl;
		}
	}

	return 0;
}

int VcprojHandler::whichIDLTool(CComPtr<IDispatch>& spDispFileTool, CComPtr<VCCustomBuildTool>& spCustomBuildTool, CComPtr<VCMidlTool>& spMidlTool)
{
	strstream scout;
	HRESULT hr;
	
	hr = spDispFileTool->QueryInterface( __uuidof( VCCustomBuildTool ), (void**)&spCustomBuildTool );
	if( FAILED( hr ) || !spCustomBuildTool )
	{
		scout << "Error: cannot get the raw interface of the custom build tool." << endl;
		hr = spDispFileTool->QueryInterface( __uuidof( VCMidlTool ), (void**)&spMidlTool );
		if( FAILED( hr ) || !spMidlTool )
		{
			scout << "Error: cannot get the raw interface of the midl tool." << endl;
		}
		else
		{
			return 2; // IDL file is "MIDL" built
		}
	}
	else
	{
		return 1;  // IDL file is "custom built"
	}
	return 0;
}

// called when settings from CPP file need to be copied to another CPP file
int VcprojHandler::copyCppSettings( CComDispatchDriver& dOld, CComDispatchDriver& dNew)
{
	HRESULT hr;
	static const int len = 6;
	static char* props[ len ] = 
		{ "Optimization"
		, "AdditionalIncludeDirectories"
		, "PreprocessorDefinitions"
		, "UsePrecompiledHeader"
		, "BrowseInformation"
		, "BasicRuntimeChecks"
	};
	
	// these option-set could be used to accomplish a complete copy of the deleted cpp file
	static char * all_properties[] = 
		{ "AdditionalOptions"
		, "Optimization"
		, "GlobalOptimizations"
		, "InlineFunctionExpansion"
		, "EnableIntrinsicFunctions"
		, "ImproveFloatingPointConsistency"
		, "FavorSizeOrSpeed"
		, "OmitFramePointers"
		, "EnableFiberSafeOptimizations"
		, "OptimizeForProcessor"
		, "OptimizeForWindowsApplication"
		, "AdditionalIncludeDirectories"
		, "AdditionalUsingDirectories"
		, "PreprocessorDefinitions"
		, "IgnoreStandardIncludePath"
		, "GeneratePreprocessedFile"
		, "KeepComments"
		, "StringPooling"
		, "MinimalRebuild"
		, "ExceptionHandling"
		, "BasicRuntimeChecks"
		, "SmallerTypeCheck"
		, "RuntimeLibrary"
		, "StructMemberAlignment"
		, "BufferSecurityCheck"
		, "EnableFunctionLevelLinking"
		, "EnableEnhancedInstructionSet"
		, "DisableLanguageExtensions"
		, "DefaultCharIsUnsigned"
		, "TreatWChar_tAsBuiltInType"
		, "ForceConformanceInForLoopScope"
		, "RuntimeTypeInfo"
		, "UsePrecompiledHeader"
		, "PrecompiledHeaderThrough"
		, "PrecompiledHeaderFile"
		, "ExpandAttributedSource"
		, "AssemblerOutput"
		, "AssemblerListingLocation"
		, "ObjectFile"
		, "ProgramDataBaseFileName"
		, "BrowseInformation"
		, "BrowseInformationFile"
		, "WarningLevel"
		, "WarnAsError"
		, "SuppressStartupBanner"
		, "Detect64BitPortabilityProblems"
		, "DebugInformationFormat"
		, "CompileAsManaged"
		, "CallingConvention"
		, "CompileAs"
		, "DisableSpecificWarnings"
		, "ForcedIncludeFiles"
		, "ForcedUsingFiles"
		, "ShowIncludes"
		, "UndefinePreprocessorDefinitions"
		, "UndefineAllPreprocessorDefinitions"
	};

	for( int i = 0; i < len; ++i)
	{
		CComVariant var;
		hr = dOld.GetPropertyByName( CComBSTR( props[i]), &var);
		hr = dNew.PutPropertyByName( CComBSTR( props[i]), &var);
	}

	return 0;
}

// called when settings from one custom built IDL file need to be copied to another custom built IDL file
int VcprojHandler::copyIdlSettings( CComDispatchDriver& dOld, CComDispatchDriver& dNew)
{
	HRESULT hr;
	static const int len = 3;
	static char* props[ len ] = 
		{ "Description"
		, "CommandLine"
		, "Outputs"
		};
	for( int i = 0; i < len; ++i)
	{
		CComVariant var;
		hr = dOld.GetPropertyByName( CComBSTR( props[i]), &var);
		hr = dNew.PutPropertyByName( CComBSTR( props[i]), &var);
	}

	return 0;
}

// called when a MIDL built IDL file needs settings to be added (does not regard the old settings)
int VcprojHandler::prepareIdlSettingsForMIDL( CComPtr<VCMidlTool>& spMidlToolNew)
{
	strstream scout;
	HRESULT hr;

	CComBSTR inc_path;
	hr = spMidlToolNew->get_AdditionalIncludeDirectories( &inc_path);
	if( SUCCEEDED( hr))
	{
		CString ip = inc_path;
		if( -1 == ip.Find("$(ProjectDir)"))
		{
			if( !ip.IsEmpty()) ip += ",";
			ip += "$(ProjectDir)";
		}
		CComBSTR new_inc_path = ip;
		hr = spMidlToolNew->put_AdditionalIncludeDirectories( new_inc_path);
		if( FAILED( hr))
		{
			scout << "Error: could not set AdditionalIncludeDirectories property for MIDLTool." << endl;
		}
	}
	else
	{
		scout << "Error: could not get AdditionalIncludeDirectories property for MIDLTool." << endl;
	}

	CComBSTR tlb_outputfile;
	hr = spMidlToolNew->get_TypeLibraryName( &tlb_outputfile);
	if( SUCCEEDED( hr))
	{
		CComBSTR new_tlb_outputfile("$(OutDir)/ComponentLib.tlb");
		hr = spMidlToolNew->put_TypeLibraryName( new_tlb_outputfile);
		if( FAILED( hr))
		{
			scout << "Error: could not set TypeLibraryName property for MIDLTool." << endl;
		}
	}
	
	//CComBSTR h_outputfile; do not set header file now
	//hr = spMidlToolNew->get_HeaderFileName( &h_outputfile);
	//if( SUCCEEDED( hr))
	//{
	//	CComBSTR new_h_outputfile("ComponentLib.h");
	//	hr = spMidlToolNew->put_HeaderFileName( new_h_outputfile);
	//	if( FAILED( hr))
	//	{
	//		scout << "Error: could not set HeaderFileName property for MIDLTool." << endl;
	//	}
	//}

	return 1;
}

int VcprojHandler::doCompRenameAndGmeRelocate
	( bool gme_loc_changed
	, bool name_changed
	, const CString& old_n
	, const CString& new_n
	, const CString& old_proj_name
	, const CString& new_proj_name
	, std::vector<std::string>& m_gmeSourceFiles
	, std::string& strBONPath)
{
	ostrstream scout;

	HRESULT hr = S_OK;
	// Create the VCProjectEngine
	CComPtr<VCProjectEngine> spEngine;
	hr = CoCreateInstance( __uuidof(VCProjectEngineObject), NULL, CLSCTX_INPROC_SERVER, __uuidof(VCProjectEngine), (void**)&spEngine );
	if( FAILED( hr ) || !spEngine )
	{
		scout << "Error: cannot create VCProjectEngine object." << endl;
		return 1;
	}

	// Open an existing project.
	CComPtr<IDispatch> spDispProj;
	hr = spEngine->LoadProject( CComBSTR( (LPCTSTR) old_proj_name ), &spDispProj );
	if( FAILED( hr ) || !spDispProj )
	{
		scout << "Error: cannot open the specified project." << endl;
		return 1;
	}
	CComQIPtr<VCProject> spProject = spDispProj;
	if( !spProject )
	{
		scout << "Error: cannot query VCProject interface." << endl;
		return 1;
	}

	if( name_changed) // if needed only
	{
		// Change the project's name
		CComBSTR name, name_new(new_n);
		hr = spProject->get_Name( &name);
		BSTRreplace( name, name_new, old_n, new_n);
		if( SUCCEEDED( hr))// && name == (LPCTSTR) old_n)
		{
			hr = spProject->put_Name( name_new );
			if( FAILED( hr ) )
			{
				scout << "Error: cannot change project name." << endl;
			}
		}
	}

	//
	// Access the configurations collection of the project
	CComPtr<IDispatch> spDispConfigs;
	hr = spProject->get_Configurations( &spDispConfigs );
	if( FAILED( hr ) || !spDispConfigs )
	{
		scout << "Error: cannot access the configurations collecion." << endl;
		return 1;
	}
	CComQIPtr<IVCCollection> spConfigCol = spDispConfigs;

	long e = 0;
	spConfigCol->get_Count( &e);
	for( long i = 1; i <= e; ++i) // for each configuration
	{
		CComPtr<IDispatch> spDispConfig;

		hr = spConfigCol->Item( CComVariant( (long) i), &spDispConfig );
		if( FAILED( hr ) || !spDispConfig )
		{
			scout << "Error: cannot get the Debug configuraion." << endl;
			return 1;
		}
		CComQIPtr<VCConfiguration> spConfig = spDispConfig;

		// Access the Tools collection for this configuration
		CComPtr<IDispatch> spDispTools;
		hr = spConfig->get_Tools( &spDispTools );
		if( FAILED( hr ) )
		{
			scout << "Error: cannot access the tools collection." << endl;
			return 1;
		}
		CComQIPtr<IVCCollection> spToolCol = spDispTools;

		{
			// Enumerate the Tools collection
			CComPtr<IDispatch> spDispTool1;
			hr = spToolCol->Item( CComVariant( L"VCCLCompilerTool" ), &spDispTool1 );
			if( FAILED( hr ) )
			{
				scout << "Error: cannot get IDispatch interface of the compiler tool." << endl;
			}
			else
			{
				// Get the VCCLCompilerTool interface and directly change a property
				CComPtr<VCCLCompilerTool> spCLCompiler;
				hr = spDispTool1->QueryInterface( __uuidof( VCCLCompilerTool ), (void**)&spCLCompiler );
				if( FAILED( hr ) || !spCLCompiler )
				{
					scout << "Error: cannot get the raw interface of the compiler tool." << endl;
				}
				else
				{
					if( name_changed) // if needed only
					{
						//
						// PrecompiledHeaderFile attribute
						CComBSTR outf, outf_new;
						hr = spCLCompiler->get_PrecompiledHeaderFile( &outf);
						if( FAILED( hr ) )
						{
							scout << "Error: cannot get the PrecompiledHeaderFile property." << endl;
						}
						else
						{
							BSTRreplace( outf, outf_new, old_n, new_n);

							hr = spCLCompiler->put_PrecompiledHeaderFile( outf_new);
							if( FAILED( hr ) )
							{
								scout << "Error: cannot set the PrecompiledHeaderFile property." << endl;
							}
						}
					}

					if( gme_loc_changed) // if needed only
					{
						//
						// AdditionalIncludeDirectories attribute
						CComBSTR inc;
						hr = spCLCompiler->get_AdditionalIncludeDirectories( &inc);
						if( FAILED( hr ) )
						{
							scout << "Error: cannot get the AdditionalIncludeDirectories property." << endl;
						}
						else
						{
							CComBSTR inc_new( inc);
							CString inc_d = inc;
							if( inc_d.IsEmpty())
							{
								inc_new.Append("./,");
								inc_new.Append( strBONPath.c_str() );
							}
							else
							{
								if( inc_d.Find("./") == -1 && inc_d.Find(".\\") == -1)
									inc_new.Append(",./");
								if( inc_d.Find( strBONPath.c_str()) == -1) // if it is not there already
								{
									inc_new.Append( ",");
									inc_new.Append( strBONPath.c_str() );
								}
							}
							hr = spCLCompiler->put_AdditionalIncludeDirectories( inc_new);
							if( FAILED( hr ) )
							{
								scout << "Error: cannot set the AdditionalIncludeDirectories property." << endl;
							}
						}
					}
				}
			}
		}

		{
			CComPtr<IDispatch> spDispTool2;
			hr = spToolCol->Item( CComVariant( L"VCLinkerTool" ), &spDispTool2 );
			if( FAILED( hr ) )
			{
				scout << "Error: cannot get IDispatch interface of the linker tool." << endl;
			}
			else
			{
				if( name_changed) // if needed only
				{
					// Get the VCLinkerTool interface and directly change a property
					CComPtr<VCLinkerTool> spLinker;
					hr = spDispTool2->QueryInterface( __uuidof( VCLinkerTool ), (void**)&spLinker );
					if( FAILED( hr ) || !spLinker )
					{
						scout << "Error: cannot get the raw interface of the linker tool." << endl;
					}
					else
					{
						// changing the OutputFile property
						CComBSTR outf, outf_new;
						hr = spLinker->get_OutputFile( &outf);
						if( FAILED( hr ) )
						{
							scout << "Error: cannot get the OutputFile property." << endl;
						}
						else
						{
							BSTRreplace( outf, outf_new, old_n, new_n);

							hr = spLinker->put_OutputFile( outf_new);
							if( FAILED( hr ) )
							{
								scout << "Error: cannot set the OutputFile property." << endl;
							}
						}

						// changing the ProgramDatabaseFile property
						CComBSTR pdbf, pdbf_new;
						hr = spLinker->get_ProgramDatabaseFile( &pdbf);
						if( FAILED( hr ) )
						{
							scout << "Error: cannot get the ProgramDatabaseFile property." << endl;
						}
						else
						{
							BSTRreplace( pdbf, pdbf_new, old_n, new_n);

							hr = spLinker->put_ProgramDatabaseFile( pdbf_new);
							if( FAILED( hr ) )
							{
								scout << "Error: cannot set the ProgramDatabaseFile property." << endl;
							}
						}

						// changing the ImportLibrary property
						CComBSTR imlf, imlf_new;
						hr = spLinker->get_ImportLibrary( &imlf);
						if( FAILED( hr ) )
						{
							scout << "Error: cannot get the ImportLibrary property." << endl;
						}
						else
						{
							BSTRreplace( imlf, imlf_new, old_n, new_n);

							hr = spLinker->put_ImportLibrary( imlf_new);
							if( FAILED( hr ) )
							{
								scout << "Error: cannot set the ImportLibrary property." << endl;
							}
						}
					}
				}
			}
		}

		{
			CComPtr<IDispatch> spDispTool3;
			hr = spToolCol->Item( CComVariant( L"VCMIDLTool" ), &spDispTool3 );
			if( FAILED( hr ) )
			{
				scout << "Error: cannot get IDispatch interface of the MIDL tool." << endl;
			}
			else
			{
				if( name_changed) // if needed only
				{
					// Get the VCMIDLTool interface and directly change a property
					CComPtr<VCMidlTool> spMidl;
					hr = spDispTool3->QueryInterface( __uuidof( VCMidlTool ), (void**)&spMidl );
					if( FAILED( hr ) || !spMidl )
					{
						scout << "Error: cannot get the raw interface of the MIDL tool." << endl;
					}
					else
					{
						CComBSTR tlbf, tlbf_new;
						hr = spMidl->get_TypeLibraryName( &tlbf);
						if( FAILED( hr ) )
						{
							scout << "Error: cannot get the TypeLibraryName property." << endl;
						}
						else
						{
							BSTRreplace( tlbf, tlbf_new, old_n, new_n);

							hr = spMidl->put_TypeLibraryName( tlbf_new);
							if( FAILED( hr ) )
							{
								scout << "Error: cannot set the TypeLibraryName property." << endl;
							}
						}
					}
				}
			}
		}
	}


	//
	// Access Files collection
	CComPtr<IDispatch> spDispFiles;
	hr = spProject->get_Files( &spDispFiles );
	if( SUCCEEDED( hr ) )
	{
		CComQIPtr<IVCCollection> spCol = spDispFiles;

		// Access all files in the project
		std::vector< CComPtr<VCFile> > todel;
		long e1 = 0;
		spCol->get_Count( &e1);
		for( long i1 = 1; i1 <= e1; ++i1)
		{
			CComPtr<IDispatch> spDispFile;
			hr = spCol->Item( CComVariant( (long) i1), &spDispFile );
			if( SUCCEEDED( hr ) )
			{
				CComQIPtr<VCFile> spFile = spDispFile;
				
				CComBSTR rp;
				hr = spFile->get_RelativePath( &rp);
				if( SUCCEEDED( hr))
				{
					CString r = rp;
					bool found = false;
					unsigned int j;
					for( j = 0; !found && j < m_gmeSourceFiles.size(); ++j)
					{
						CString mmm = m_gmeSourceFiles[j].c_str();
						if( -1 != r.Find( m_gmeSourceFiles[j].c_str()))
							found = true;
					}
					if( found && --j < m_gmeSourceFiles.size())
					{
						// found, so change its relative path
						CString new_str = strBONPath.c_str();
						new_str += m_gmeSourceFiles[j].c_str();
						new_str.Replace( "/", "\\");
						CComBSTR new_rp = new_str;
						if( 0 != r.CompareNoCase( new_str))
						{
							swapFiles( spFile, rp, new_rp, spProject); // spFile will be deleted
							todel.push_back( spFile );
						}
					}
				}
			}
		}

		for( unsigned int lll = 0; lll < todel.size(); ++lll)
		{
			hr = spProject->RemoveFile( todel[ lll ] );
			if( FAILED( hr))
			{
				scout << "Error: cannot remove old file from project." << endl;
			}
		}
	}


	// ---------- DONE with transformations, must save it--------
	// the name may be equal with the old name since the name must not change
	// so the file might exist
	hr = spProject->put_ProjectFile( CComBSTR( (LPCTSTR) new_proj_name ) );
	if( FAILED( hr ) )
	{
		scout << "Error: cannot set new project file name." << endl;
	}

	bool save_failed = false;
	hr = spProject->Save( );
	if( FAILED( hr ) )
	{
		scout << "Error: cannot save project." << endl;
		save_failed = true;
	}

	spEngine->RemoveProject( spDispProj );

	if( save_failed && scout.pcount() > 0) // any errors on the stream ?
	{
		return 1;
	}	

	return 0;
}
