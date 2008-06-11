#include "afx.h"
#include <atlbase.h>
#import <VCProjectEngine.dll> raw_interfaces_only raw_native_types
using namespace VCProjectEngineLibrary;

#include <strstream>
#include <map>
#include <vector>
#include <cassert>
using namespace std;

class VcprojHandler
{
public:
	
	static int doCompRenameAndGmeRelocate
		( bool gme_loc_changed
		, bool name_changed
		, const CString& old_n
		, const CString& new_n
		, const CString& old_proj_name
		, const CString& new_proj_name
		//, const CString& proj_name
		, std::vector<std::string>& m_gmeSourceFiles
		, std::string& strBONPath
		);

protected:

	static void BSTRreplace( const CComBSTR& outf, CComBSTR& outf_new, const CString& old_n, const CString& new_n);
	static int swapFiles( CComPtr<VCFile>& spOldFile, const CComBSTR& oldf, const CComBSTR& newf, CComPtr<VCProject>& spProject);
	static int copyCppSettings( CComDispatchDriver& dOld, CComDispatchDriver& dNew); 
	static int whichIDLTool( CComPtr<IDispatch>& spDispFileTool, CComPtr<VCCustomBuildTool>& spCustomBuildTool, CComPtr<VCMidlTool>& spMidlTool);
	static int copyIdlSettings( CComDispatchDriver& dOld, CComDispatchDriver& dNew); 
	static int prepareIdlSettingsForMIDL( CComPtr<VCMidlTool>& spMidlToolNew);

};