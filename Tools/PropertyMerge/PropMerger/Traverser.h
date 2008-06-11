#pragma once

#include "IDLComp\GMEIDLs_h.h"
#include <string>
#include <vector>

class Traverser
{
public:
	Traverser(void);
	Traverser( const std::string& p_path, const std::string& p_dirRoot, bool p_hier1d, bool p_hier2d);
	~Traverser(void);
	void exec();

	long InvokeEx( IMgaProject *project,  IMgaFCO *currentobj,  IMgaFCOs *selectedobjs,  long param);

protected:
	const bool                m_hier1d;
	const bool                m_hier2d;
	const std::string         m_path;
	const std::string         m_inDirPath;
	std::string               m_pathPrefix; // calculated

	std::vector< std::string> m_ignoreList;

	CComPtr<IMgaParser> m_xmlParser;
	CComPtr<IGMEOLEApp> m_theGme;

	//CComPtr<IMgaProject>     m_theProj;
	//CComPtr<IMgaTerritory>   m_theTerr;

	CComPtr<IGMEOLEApp> getGME( IMgaProject *p_project);

	void stdConsoleMsg( const char *    p_msg, int p_type, bool p_prefixed);
	void stdConsoleMsg( const CComBSTR& p_msg, int p_type, bool p_prefixed);

	void consoleMsg( const CComBSTR& p_msg, int p_type, bool p_prefixed = true);
	void consoleMsg( const char *    p_msg, int p_type, bool p_prefixed = true);

	void         setPathPrefix();
	CComBSTR     makeFileName( const CComBSTR& p_gd, bool *p_fileExists);
	bool         fileFound( const char *      p_file);
	bool         fileFound( const CComBSTR&   p_file);

	void         createMgaDtd();
	bool         foundAsIgnoreable( const CComBSTR& p_objId);
	void         loadIgnorables();


	void traverse( IMgaProject *p_project, IMgaTerritory *p_terr, IMgaFolder *p_curr);
	void traverse( IMgaProject *p_project, IMgaTerritory *p_terr, IMgaModel  *p_curr);

	template <typename T> // for IMgaFCO* and IMgaFolder*
	void dealWith( IMgaProject *p_project, IMgaTerritory *p_terr, T      *p_item);
};
