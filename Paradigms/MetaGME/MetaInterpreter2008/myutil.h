#pragma once

#include <string>
#include "ComponentLib.h"
#include "GMECOM.h"

//interface IMgaFCO;
//interface IMgaFolder;
//interface IMgaProject;

namespace Util
{
	CComBSTR	Copy( const std::string& str );
	std::string	Copy( const CComBSTR& bstr );
	std::string CopyV( const CComVariant& pvar);
	std::string gvbp( IMgaRegNode* p_rn, const std::string& p_path);
	void svbp( IMgaRegNode* p_rn, const std::string& p_path, const std::string& p_value);

	std::string getReg( IMgaFolder* ptr, const std::string& p_path);
	std::string getReg( IMgaFCO* ptr, const std::string& p_path);
	void        setReg( IMgaFCO* ptr, const std::string& p_path, const std::string& p_value);

	bool islibobj( IMgaObject* p_ptr);
	bool isproxy( IMgaFCO* p_ptr);
	std::string name( IMgaObject* ptr);
	std::string name( IMgaFCO* ptr);
	std::string kind( IMgaObject* p_ptr);
	std::string getStrAttr( IMgaFCO* p_ptr, const std::string& p_attrName);
	bool        getBoolAttr( IMgaFCO* p_ptr, const std::string& p_attrName);
	long        getLongAttr( IMgaFCO* p_ptr, const std::string& p_attrName);
	bool        isAttrStatHere( IMgaFCO* p_fco, const std::string& p_attrName);
	IMgaAttribute* getAttrib( IMgaFCO* p_fco, const std::string& p_attrName);

	std::string composePath( IMgaObject * ptr, bool p_upUntilFolders = false); // SF/OutputSignal-24-Atom
}

