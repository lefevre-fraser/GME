#include "stdafx.h"
#include "MgaXslt.h"
#include "CommonStl.h"
#include <fstream>

#include <xalanc/Include/PlatformDefinitions.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xalanc/XalanTransformer/XalanTransformer.hpp>

std::string CMgaXslt::getMgaDTDFromResource()
{
	HMODULE hm = GetModuleHandle("PARSER.DLL");
	if( !hm) return "";

	HRSRC res1 = FindResource(hm, "MGA.DTD", "DTD");
	if( !res1) return "";
	
	HGLOBAL res2 = LoadResource(hm, res1);
	if( !res2) return "";
	
	char *data = ( char* )LockResource( res2);
	if( !data) return "";

	DWORD uLen = SizeofResource(hm, res1);
	return std::string( data, uLen);
}

STDMETHODIMP CMgaXslt::ApplyXslt( BSTR p_stylesheet_f_name, BSTR p_in_f_name, BSTR p_out_f_name, BSTR * out_error)
{
	XALAN_USING_XERCES(XMLPlatformUtils)
	XALAN_USING_XERCES(XMLException)

	XALAN_USING_XALAN(XalanTransformer)
	XALAN_USING_XALAN(XalanCompiledStylesheet)

	std::string style_sheet( 1 + GetCharLength( p_stylesheet_f_name), ' ');
	std::string in_file( 1 + GetCharLength( p_in_f_name), ' ');
	std::string out_file( 1 + GetCharLength( p_out_f_name), ' ');
	std::string error;

	CopyTo( p_stylesheet_f_name, style_sheet);
	CopyTo( p_in_f_name, in_file);
	CopyTo( p_out_f_name, out_file);

	int	theResult = 0;

	// Call the static initializer for Xerces.
	try
	{
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException&)
	{
		theResult = E_XSLT_XERCES_INIT;
	}

	bool dtd_created = false;
	std::string dtd_name;
	try 
	{
		if ( theResult == 0)
		{
			// Initialize Xalan.
			XalanTransformer::initialize();
			
			// Create a XalanTransformer.
			XalanTransformer theXalanTransformer; 
			
			// Compile the stylesheet.
			const XalanCompiledStylesheet*	theCompiledStylesheet = 0;
			
			theResult =	theXalanTransformer.compileStylesheet( style_sheet.c_str(), theCompiledStylesheet);
			
			if (theResult != 0)
			{
				theResult = E_XSLT_COMPILE_ERROR;
				error = theXalanTransformer.getLastError();
			}
			else
			{
				assert(theCompiledStylesheet != 0);
		
				// make sure mga.dtd file exists in the directory of the in_file
				// if file doesn't exist we create a temporary mga.dtd file
				// in that directory, which will be deleted after the transformation
				// the content of this file is the same as the latest original mga.dtd
				// but Xalan can be fooled even with an empty file
				int dir_end = in_file.rfind('\\');
				if( dir_end != std::string::npos) // directory part found
					dtd_name += in_file.substr( 0, dir_end+1);
				dtd_name += "mga.dtd";
				
				std::fstream dtd_file;
				dtd_file.open( dtd_name.c_str(), std::ios_base::in);
				if( !dtd_file.is_open()) // failure, we will create a temporary dtd file
				{
					std::string mga_dtd_content = getMgaDTDFromResource();
					if( mga_dtd_content.length() > 0 )
					{
						dtd_created = true;
						std::ofstream dtd_temp;
						dtd_temp.open( dtd_name.c_str(), std::ios_base::out);
						if( dtd_temp.is_open())
							dtd_temp << mga_dtd_content;
						else
							throw "Error: mga.dtd file not found, and could not create a temporary one either!";

						dtd_temp.close();
					}
				}
				else // file found
					dtd_file.close();

				// Do the transform.
				theResult = theXalanTransformer.transform
					( in_file.c_str()
					, theCompiledStylesheet
					, out_file.c_str()
					);
				
				// I don't have to do this, since the transformer will
				// clean this up when it's destroyed, but why not...
				theXalanTransformer.destroyStylesheet(theCompiledStylesheet);

				if ( theResult != 0)
				{
					theResult = E_XSLT_TRANSF_ERROR;
					error = theXalanTransformer.getLastError();
				}
			}
		}
	} 
	catch( std::string& m)
	{
		error = m;
		theResult = E_XSLT_ERROR;
	}
	catch( ...)
	{
		theResult = E_XSLT_ERROR;
	}

	if( dtd_created)
		remove(dtd_name.c_str());

	// Terminate Xalan...
	XalanTransformer::terminate();

	// Terminate Xerces...
	XMLPlatformUtils::Terminate();

	// Clean up the ICU, if it's integrated.
	XalanTransformer::ICUCleanUp();

	CopyTo( error, out_error);

	return (theResult == 0)? S_OK : theResult;
}
