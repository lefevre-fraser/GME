#include "stdafx.h"
#include "myutil.h"
#include "Any.h"
#include "CodeGen.h"
#include "Method.h"
#include "Dumper.h"
#include "MakeVisitor.h"

#include <algorithm>
#include <strstream>

#include "globals.h"
extern Globals global_vars;

/*static*/ const std::string Any::m_startUPToken = "///BUP";
/*static*/ const std::string Any::m_endUPToken   = "///EUP";
/*static*/ const std::string Any::NamespaceDispSeparatorBeg_str = "_";
/*static*/ const std::string Any::NamespaceDispSeparatorEnd_str = "_";
/*static*/ const std::string Any::NamespaceDelimiter_str = "::";
/*static*/ const std::string Any::InRootFolder_str = "InRootFolder";
/*static*/ const std::string Any::NameSelectorNode_str = "myNameIs"; 
/*static*/ const std::string Any::MOFException_str = "MOFException";
/*static*/ const std::string Any::MOFOperation_str = "MOFOperation";
/*static*/ const std::string Any::MOFEnumeration_str = "MOFEnumeration";
/*static*/ const std::string Any::MOFStructure_str = "MOFStructure";
/*static*/ const std::string Any::MOFAlias_str = "MOFAlias";

/*static*/ const std::string Any::MOFStart_str = "MOF section begins";
/*static*/ const std::string Any::MOFEnd_str   = "MOF section ends";



bool AnyLexicographicSort::operator()( Any * op1, Any * op2) const
{
	std::string s1 = op1->getName();
	std::string s2 = op2->getName();
	int k = s1.compare(s2);

	return ( k < 0);
}

/*
These names must be valid BON2 class names (with the BON:: tag) so beware when changing it
*/
/*static*/ const std::string Any::KIND_TYPE_STR[] =
{
	"Atom",
	"Model",
	"Connection",
	"Set",
	"Reference",
	"FCO",
	"ASPECT",
	"Folder",
	"CONSTRAINT",
	"CONSTRAINFUNC",
	"ATTRIBUTE"
};


Any::Any( IMgaFCO* ptr)
		: m_ptr( ptr)
		, m_isInRootFolder( false)
		, m_equivs()
		, m_toEx( true)
		, m_globalHeader()
		, m_globalSource()
{
}


Any::~Any()
{ 
	m_equivs.clear();
}

void Any::initNamespace()
{
	// decide which namespace the object belongs to:
	if( Util::islibobj( m_ptr))
	{
		bool all_equivs_in_lib = true;
		for ( EquivSet_ConstIterator it = m_equivs.begin()
			; all_equivs_in_lib && it != m_equivs.end()
			; ++it)
		{
			if ( *it == m_ptr) continue;
			// --applicable to non proxies only--
			if ( Util::isproxy( *it)) continue;//ignore proxies (from m_equivs) when determining namespace
			all_equivs_in_lib = Util::islibobj( *it);
		}

		if( !all_equivs_in_lib) // it has equivs in the host project
			resetNamespace();   // so needs to be in the main namespace
		else
		{
			// find the Namespace value from the namespace holding rootfolder
			// in case of nested libs m_libRootFolder and m_nmspRootFolder are !equal
			std::string nm_val = Util::getReg( m_nmspRootFolder, "Namespace");

			if( nm_val.length() > 0) m_namespace = nm_val;
			else                     m_namespace = ""; // TODO
			//m_respPointer could be in another library then m_ptr, so the namespace could be different
		}
	}
	else // regular object, init its namespace value from the project's value
	{
		resetNamespace();
	}
}

void Any::resetNamespace()
{
	m_namespace = Dumper::getInstance()->getNamespace();
}

// applicable for folders only
void Any::initAttributes()
{
	// for folders the default value (from the meta) true
	// for fcos    the default value (from the meta) false

	m_isInRootFolder = Util::getBoolAttr( m_ptr, InRootFolder_str);
	// try to find one among the equivalent classes which is in the root folder
	EquivSet_ConstIterator it = m_equivs.begin();
	for ( ; !m_isInRootFolder && it != m_equivs.end(); ++it)
	{
		if ( *it == m_ptr) continue;
		// --applicable to non proxies only--
		if ( Util::isproxy( *it)) continue;// folderproxies don't have attributes
		m_isInRootFolder = m_isInRootFolder || Util::getBoolAttr( *it, InRootFolder_str);
	}
}


bool Any::isInRootFolder()
{
	return m_isInRootFolder;
}

bool Any::isToBeEx() const
{
	return m_toEx;
}


void Any::toBeEx( bool t)
{
	m_toEx = t;
}


bool Any::isFCO() const
{
	bool fco = false;
	fco = (getMyKind() == ATOM ||
		getMyKind() == MODEL ||
		getMyKind() == CONN ||
		getMyKind() == SET ||
		getMyKind() == REF ||
		getMyKind() == FCO_REP);
	return fco;
}


std::string Any::getName() const
{
	if ( this->m_ptr)
	{
		CComBSTR nm;
		COMTHROW( m_ptr->get_Name( &nm));
		return Util::Copy( nm);
	}
	return "NullPtrError";
}


std::string Any::getValidName() const
{
	if ( this->m_ptr)
	{
		std::string nm = getName();
		Any::convertToValidName( nm);
		return nm;
	}
	return "NullPtrError";
}

std::string Any::getStrictNmspc() const
{
	return m_namespace.empty()?"": m_namespace;
}

std::string Any::getLStrictNmspc() const
{
	return m_namespace.empty()?"": (m_namespace + Any::NamespaceDelimiter_str);
}

std::string Any::getNmspc() const
{
	// will return global_vars.m_namespace_name if m_namespace empty
	// i.e. "meta5_BON" or "NSP"
	return m_namespace.empty()?global_vars.m_namespace_name: m_namespace;
}

std::string Any::getLNmspc() const
{
	std::string t = getNmspc();
	Any::convertToValidName( t);
	return t + Any::NamespaceDelimiter_str;
}

std::string Any::getValidNmspc() const
{
	// returns "_meta5_1"  validated form of "1meta5.1"
	std::string t = getNmspc();
	Any::convertToValidName( t);
	return t;
}

std::string Any::getLStrictName() const
{
	return getLStrictNmspc() + getName();
}

std::string Any::getLName() const
{
	return getLNmspc() + getName();
}

std::string Any::getLValidNmspc() const
{
	std::string t = getValidNmspc();
	return t.empty()?"": t + Any::NamespaceDelimiter_str;
}

std::string Any::getLValidName() const
{
	return getLValidNmspc() + getValidName();
}

std::string Any::getValidNameImpl() const
{
	return getValidName() + "Impl";
}

std::string Any::getLValidNameImpl() const
{
	return getLValidNmspc() + getValidNameImpl();
}

std::string Any::getMyKindStr() const
{
	if ( isFCO() || getMyKind() == FOLDER)
		return KIND_TYPE_STR[ getMyKind()];

	throw "Error: inquireing getMyKindStr for non-fco, non-folder";
}


/*static*/ void Any::convertToValidName( std::string & p)
{
	for(int i = 0; i < p.length(); ++i)
		if( (p[i]>='a' && p[i]<='z') ||
				(p[i]>='A' && p[i]<='Z') ||
				(p[i]>='0' && p[i]<='9') ||
				(p[i]=='_'))
		{}
		else
			p[i]= '_';

	if (p[0]>='0' && p[0]<='9')
		p = '_' + p;
}


/*static*/ bool Any::checkIfValidName( const std::string & p)
{
	std::strstream error_msg;

	bool more_than_one = false;
	bool good = true;
	if (( p[0] >='a' && p[0]<='z')
		|| ( p[0] >='A' && p[0]<='Z')
		|| ( p[0] == '_'))
		{} 
	else
	{
		good = false;
		//global_vars.err << "Error in " << p << " at index 0\n";
		error_msg << "0";
		more_than_one = true;
	}
		
	for(int i = 1; i < p.length(); ++i)
	{
		if( (p[i]>='a' && p[i]<='z') ||
				(p[i]>='A' && p[i]<='Z') ||
				(p[i]>='0' && p[i]<='9') ||
				(p[i]=='_'))
		{}
		else
		{
			good = false;
			//global_vars.err << "Error in " << p << " at index " << i << "\n";
			if (more_than_one) error_msg << ", ";
			error_msg << i;

			if (!more_than_one) 
				more_than_one = true;
		}
	}
	error_msg << std::ends;
	std::string error_str ( error_msg.str());
	/*if ( !error_str.empty())
		global_vars.err << "Error in " << p << " at index "<< error_str << ".\n";*/
	return good;
}


std::string Any::getMyPrefix( int which /* = 0*/) const
{
	if ( this->m_ptr)
	{
		std::string kind = Util::kind( m_ptr);
		std::string name = Util::composePath( m_ptr);

		long relid = 0;
		COMTHROW( m_ptr->get_RelID(&relid));
		char t[16];
		sprintf( t, "%x", relid);

		ASSERT( name.length() >= 0);
		std::string tmp = name + '-' + t + '-' + kind;
		
		if( which) // in case when special metainterpreter registry is needed
			return tmp;
		return "BonExtender/" + tmp;
	}
	throw "Error: inquiring prefix for a null object\n";
}


CComPtr<IMgaRegNode> Any::getMyRegistry() const
{
	CComPtr<IMgaRegNode> rn;
	if ( this->m_ptr && this->m_parentFolder)
	{
		COMTHROW( m_parentFolder->get_RegistryNode( Util::Copy( getMyPrefix()), &rn));
		return rn;
	}

	throw 1;
}

CComPtr<IMgaRegNode> Any::getMIRegistry() const // the metainterpreter registry
{
	CComPtr<IMgaRegNode> rn;
	if ( this->m_ptr && this->m_parentFolder)
	{
		COMTHROW( m_parentFolder->get_RegistryNode( Util::Copy( getMyPrefix( 1)), &rn));
		return rn;
	}

	throw 1;
}

void Any::prepareMacros()
{
	std::string h, s, n = getValidNmspc();
	int c = (n.length() < 15) ? 15-n.length():(
	        (n.length() < 30) ? 30-n.length():(
	        (n.length() < 45) ? 45-n.length():(
			0
	)));

	//h = "class " + getValidNameImpl() + ";\n"; removed on 5/6/2004 not needed
	h  = "namespace " + n + " { " + std::string( c, ' ');
	h += "DECLARE_BONEXTENSION( BON::" + getMyKindStr() + ", " + getValidNameImpl() + ", " + getValidName()	+ " ); }\n";
	//h = "DECLARE_BONEXTENSION( BON::" + getMyKindStr() + ", " + getValidNameImpl() + ", " + getValidName()	+ " );\n";

	//s = "IMPLEMENT_BONEXTENSION( " + global_vars.m_namespace_name + "::" + getValidName() + ", \"" + getNmspc() + "::" + getName() + "\" );\n";
	s = "IMPLEMENT_BONEXTENSION( " + getValidNmspc() + Any::NamespaceDelimiter_str + getValidName() + ", \"" + getLStrictNmspc() + getName() + "\" );\n";

	m_globalSource += s;
	m_globalHeader += h;
}


void Any::prepareIniFin()
{
	Method i;

	i.m_container = this;
	i.m_virtual = true;
	i.m_returnValue = "void";
	i.m_signature = "initialize() { }";
	i.m_implementation = "";
	i.m_comment = "";


	if ( Dumper::m_bGenInit)		m_inifinMethods.push_back( i);

	i.m_signature = "finalize() { }";

	if ( Dumper::m_bGenFinalize)	m_inifinMethods.push_back( i);

	// Dumper::m_bGenAcceptTrave: 0 1 0 1 
	// Dumper::m_bGenAcceptSpeci: 0 0 1 1
	// 0, 0: none
	// 1, 0: builtin visitor style with traversal 
	// 0, 1: special visitor style without traversal
	// 1, 1: special visitor style with traversal
	createAcceptMethod( Dumper::m_bGenAcceptTrave, Dumper::m_bGenAcceptSpeci, Dumper::m_iSpecAcceptRetVal == 1);

	//if ( getMyKind() != FCO_REP && Dumper::m_bGenAcceptTrave)
	//{
	//	m_inifinMethods.push_back( this->createAcceptMethod());
	//}
	//if ( Dumper::m_bGenAcceptSpeci)
	//{
	//	m_inifinMethods.push_back( this->createSpecAcceptMethod());
	//}
}

void Any::createAcceptMethod( bool pWithTraversalOfKids, bool pSpecialized, bool pRetValBool)
{
	Method m = CodeGen::acceptMethod( this, pWithTraversalOfKids, pSpecialized, pRetValBool);
	if( pSpecialized || getMyKind() != FCO_REP) // there is no such thing that visitFCO in the built in BON::Visitor
		m_inifinMethods.push_back( m);
}

/*static*/ std::string Any::parseMOFException( const std::string& exc_str)
{
	if( exc_str.empty()) return "";

	std::string ind0 = std::string( 2 - 1, '\t'), ind = std::string( 2, '\t'), more_ind = std::string( 2 + 1, '\t');

	std::string res, ctor_signature, ctor_inilist, ctor_body, class_body, name;
	unsigned int beg = 0, nwl = exc_str.find('\n');
	name = exc_str.substr(0, nwl);

	while( nwl != std::string::npos)
	{
		beg = nwl + 1;
		nwl = exc_str.find('\n', beg);
		
		if( nwl > beg && beg < exc_str.length() - 1)
		{
			std::string par_line = exc_str.substr( beg, nwl - beg);
			int type_end = par_line.find('\t');
			std::string par_type, par_name;
			par_type = par_line.substr(0, type_end);
			par_name = par_line.substr( type_end + 1);

			if( ctor_signature.empty()) ctor_signature = "\n" + more_ind + "( ";
			else ctor_signature += "\n" + more_ind + ", ";
			
			if( ctor_body.empty()) ctor_body = "\n" + more_ind + ": ";
			else ctor_body += "\n" + more_ind + ", ";
			
			ctor_signature += par_type + " p_" + par_name;
			ctor_body += par_name + "( p_" + par_name + ")";
			class_body += "\n" + ind + par_type + " " + par_name + ";";
		}
	}

	if( name == exc_str) //no members
	{
		res = ind0 + "class " + name + "{ };\n";
	}
	else
	{
		ctor_signature = "\n" + ind + "// constructor\n" + ind + name + ctor_signature + "\n" + more_ind + ")";
		ctor_body += "\n" + ind + "{ }";
		class_body = "\n" + ind + "// members\n" + class_body;
		res = ind0 + "class " + name + "\n" + ind0 + "{\n" + ind0 + "public:\n"  + ctor_signature + ctor_body + "\n" + class_body + "\n" + ind0 + "};\n";
	}
	return res;
}


/*static*/ std::string Any::parseMOFOperation( const std::string& exc_str)
{
	if( exc_str.empty()) return "";

	std::string ind0 = std::string( 2 - 1, '\t'), ind = std::string( 2, '\t');

	std::string res, tabulated_exc_str;
	for( unsigned int i = 0; i < exc_str.length(); ++i)
	{
		tabulated_exc_str += exc_str[i];
		if( exc_str[i] == '\n') // covers simple '\n' and '\r\n' case as well
			tabulated_exc_str += ind;
	}
	res = ind0 + tabulated_exc_str;
	if( exc_str.length() > 0 && exc_str[ exc_str.length() - 1 ] != '\n') res += '\n';
	return res;
}


/*static*/ std::string Any::processMOFNode( const CComPtr<IMgaRegNode> rn, int ind_num)
{
	try {
		// put the regnodes into a map, the key will be the node's name, thus ordering is provided
		std::map< std::string, CComPtr<IMgaRegNode>, StringLex> aliases, enums, exceptions, operations, structures;
		std::map< std::string, CComPtr<IMgaRegNode>, StringLex>::iterator iter;
		CComPtr<IMgaRegNodes> rns;
		COMTHROW( rn->get_SubNodes( VARIANT_TRUE, &rns));// inquire all children
		
		long c = 0;
		if( rns) COMTHROW( rns->get_Count( &c));

		for( long i = 1; i <= c; ++i)
		{
			CComPtr<IMgaRegNode> item;
			COMTHROW( rns->get_Item( i, &item));

			CComBSTR bnm;
			COMTHROW( item->get_Name( &bnm));
			std::string nm = Util::Copy( bnm);
			if( Any::MOFAlias_str.compare( nm.substr( 0, Any::MOFAlias_str.length())) == 0 ) aliases[nm] = item;
			else if( Any::MOFEnumeration_str.compare( nm.substr( 0, Any::MOFEnumeration_str.length())) == 0) enums[nm] = item;
			else if( Any::MOFException_str.compare( nm.substr( 0, Any::MOFException_str.length())) == 0) exceptions[nm] = item;
			else if( Any::MOFOperation_str.compare( nm.substr( 0, Any::MOFOperation_str.length())) == 0) operations[nm] = item;
			else if( Any::MOFStructure_str.compare( nm.substr( 0, Any::MOFStructure_str.length())) == 0) structures[nm] = item;
		}

		std::string mof;

		// aliases first
		for( iter = aliases.begin(); iter != aliases.end(); ++iter)
		{
			CComBSTR val;
			COMTHROW( iter->second->get_Value( &val));
			mof += parseMOFOperation( Util::Copy( val)) + "\n";
		}

		// then enums
		for( iter = enums.begin(); iter != enums.end(); ++iter)
		{
			CComBSTR val;
			COMTHROW( iter->second->get_Value( &val));
			mof += parseMOFOperation( Util::Copy( val)) + "\n";
		}

		// structures
		for( iter = structures.begin(); iter != structures.end(); ++iter)
		{
			CComBSTR val;
			COMTHROW( iter->second->get_Value( &val));
			mof += parseMOFOperation( Util::Copy( val)) + "\n";
		}

		// exceptions
		for( iter = exceptions.begin(); iter != exceptions.end(); ++iter)
		{
			CComBSTR val;
			COMTHROW( iter->second->get_Value( &val));
			mof += parseMOFException( Util::Copy( val)) + "\n";
		}

		// operations
		for( iter = operations.begin(); iter != operations.end(); ++iter)
		{
			CComBSTR val;
			COMTHROW( iter->second->get_Value( &val));
			mof += parseMOFOperation( Util::Copy( val)) + "\n";
		}

		return mof;
	} catch( ...) {
		global_vars.err << MSG_ERROR << "Some error occurred during MOF parsing.\n";
		return "";
	}
}


void Any::prepareMOF()
{
	CComPtr<IMgaRegNodes> rns;
	COMTHROW( m_ptr->get_Registry( VARIANT_TRUE, &rns));

	long c = 0;
	if( rns) COMTHROW( rns->get_Count( &c));

	for( long i = 1; i <= c; ++i)
	{
		CComPtr<IMgaRegNode> item;
		COMTHROW( rns->get_Item( i, &item));

		m_sectionMOF += Any::processMOFNode( item);
	}

	EquivSet_ConstIterator it = m_equivs.begin();
	for ( ; it != m_equivs.end(); ++it)
	{
		if( m_ptr == *it) continue;

		//m_sectionMOF += Any::processMOFNode( rn);
		CComPtr<IMgaRegNodes> subnodes;
		COMTHROW( (*it)->get_Registry( VARIANT_TRUE, &subnodes));

		long d = 0;
		if( rns) COMTHROW( subnodes->get_Count( &d));

		for( long i = 1; i <= d; ++i)
		{
			CComPtr<IMgaRegNode> item;
			COMTHROW( subnodes->get_Item( i, &item));

			m_sectionMOF += Any::processMOFNode( item);
		}

	}

	//CComPtr<IMgaRegNode> my_rn	= m_ptr->getRegistry();
	//if( my_rn)
	//	m_sectionMOF = Any::processMOFNode( my_rn);

	//EquivSet_ConstIterator it = m_equivs.begin();
	//for ( ; it != m_equivs.end(); ++it)
	//{
	//	if( m_ptr == *it) continue;

	//	CComPtr<IMgaRegNode> rn = (*it)->getRegistry();
	//	if( rn)
	//		m_sectionMOF += Any::processMOFNode( rn);
	//}
}


void Any::prepare()
{
	prepareMacros();
	prepareIniFin();
#if(DO_MOF)
	prepareMOF();
#endif
}


void Any::dumpGlobals()
{
	DMP_S( m_globalSource);
	DMP_H( m_globalHeader);
}


std::string Any::dumpOrnament( bool is_abstract/* = false*/)
{
	std::string row;
	row = "//   C  L  A  S  S   " + getValidNameImpl() + "\n";//(is_abstract?" abstract":"") + " class\n";

	const std::string orn = "//*******************************************************************\n";
	
	return orn + row + orn;
}


void Any::dumpPre( std::string & h_file, std::string & c_file)
{
	// namespace opened in h and cpp files
	h_file += "namespace " + getValidNmspc() + "\n{\n";
	//c_file += "namespace " + getValidNmspc() + "\n{\n";

	h_file += dumpOrnament();
	h_file += "class " + getValidNameImpl();
	h_file += dumpClassHeader() + "{\npublic:\n";

	for( unsigned int k = 0; k < m_inifinMethods.size(); ++k)
	{
		h_file += m_inifinMethods[k].getHeader() + "\n";
		c_file += m_inifinMethods[k].getSource();
	}
}


void Any::dumpPost( std::string & h_file, std::string & c_file)
{
	h_file += "\n" + CodeGen::indent(1) + m_startUPToken + "\n" + getUserPart() + CodeGen::indent(1) +  m_endUPToken+ "\n";
	
	if( !m_sectionMOF.empty())
	{
		h_file += "\n// " + Any::MOFStart_str + "\n";
		h_file += "public:\n" + m_sectionMOF + "\n";
		h_file += "// " + Any::MOFEnd_str + "\n\n";
	}
	
	//h_file += "};\n\n\n"; 
	// namespace closed in h and cpp file
	h_file += "}; // class\n";
	h_file += "}  // namespace\n";
	h_file += "\n\n";
	//c_file += "}; // nmspc\n";
}


std::string Any::dumpClassHeader()
{
	// the place of ":" plays important role in identifying where class definitions start really
	// to prevent confusing with predefinitions like "class X;"
	// the canonical form is "class X :"
	return " :\n\t  public BON::" + getMyKindStr() + "Impl\n";
	//return " :\n  public /*Ex*/ BON::" + getMyKindStr() + "Impl\n";
}


std::string Any::getUserPart()
{
	std::ifstream old_xmp_file;
	std::string old_f_name;
	old_f_name = global_vars.header_backup_name;
	if ( old_f_name.empty()) // means that no previous version existed or the user selected not to parse the old file
		return CodeGen::indent(1) + "// add your own members here\n";

	old_xmp_file.open( old_f_name.c_str() ,std::ios_base::in);
	if ( !old_xmp_file.is_open())
		return CodeGen::indent(1) + "// ERROR accessing file\n";

	std::string up, line;
	while( !old_xmp_file.eof() && line.find( "class " + getValidNameImpl() + " :") == std::string::npos)
	{
		std::getline( old_xmp_file, line);
	}
	if ( !old_xmp_file.eof()) // found the class
	{
		while( !old_xmp_file.eof() && line.find( m_startUPToken) == std::string::npos) 
		{
			std::getline( old_xmp_file, line);
		}
		if ( !old_xmp_file.eof()) // found the start token
		{
			std::getline( old_xmp_file, line);
			while( !old_xmp_file.eof() && line.find( m_endUPToken) == std::string::npos) 
			{
				up += line + "\n";
				std::getline( old_xmp_file, line);
			}
			if ( !old_xmp_file.eof()) // found the end token
			{
			}
			else
			{
				old_xmp_file.close();
				return CodeGen::indent(1) + "//Class found. Ending token (" + m_endUPToken + ") not found\n";
			}
		}
		else
		{
			old_xmp_file.close();
			return CodeGen::indent(1) + "//Class found. Starting token (" + m_startUPToken + ") not found\n";
		}
	}
	else
	{
		old_xmp_file.close();
		return CodeGen::indent(1) + "//Class not found\n";
	}
	old_xmp_file.close();
	return up;
}

void Any::makeBackup()
{
	if( global_vars.m_outputMethod == Globals::OUTPUTMETHOD_ENUM::PERCLASS) // 
	{
		std::string dirname = getValidNmspc();
		std::string fname   = getName();
		// check dir for namespace
		if( !dirname.empty())
		{
			bool success = directoryExists( dirname.c_str());
			if( !success) success = directoryCreate( dirname.c_str());

			if( success) dirname += "\\";
			else         dirname  = "";
		}

		std::string fn = dirname + fname;// + ".cpp";
		if( !makeFileMove( ( fn + ".h").c_str(), ( fn + ".h.bak").c_str()))
			global_vars.err << MSG_ERROR << "Could not backup " << ( fn + ".h");
		if( !makeFileMove( ( fn + ".cpp").c_str(), ( fn + ".cpp.bak").c_str()))
			global_vars.err << MSG_ERROR << "Could not backup " << ( fn + ".cpp");

		//Dumper::backup( fn_c.c_str()); // makes backup if exists file
	}
}

void Any::initOutS()
{
	if( global_vars.m_outputMethod == Globals::OUTPUTMETHOD_ENUM::PERCLASS) // 
	{
		std::string dirname = getValidNmspc();
		std::string fname   = getName();
		// check dir for namespace
		if( !dirname.empty())
		{
			bool success = directoryExists( dirname.c_str());
			if( !success) success = directoryCreate( dirname.c_str());

			if( success) dirname += "\\";
			else         dirname  = "";
		}

		std::string fn_c = dirname + fname + ".cpp";
		//Dumper::backup( fn_c.c_str()); // makes backup if exists file

		m_sStream.open( fn_c.c_str(), std::ios_base::out | std::ios_base::app); // append old file
		m_sStream.seekp( 0, std::ios::end); // go to end
		int lenf = m_sStream.tellp();
		if( lenf == ( std::fstream::pos_type) 0)
		{
			m_sStream << "#include \"stdafx.h\"" << std::endl;
			m_sStream << "#include \"" << shortFileName( global_vars.header_file_name) << "\"" << std::endl;
			//m_sStream << "#include \"" << fname << ".h\"" << std::endl;
			if( Dumper::m_bGenAcceptSpeci && 0) // if special accept is generated then special visitor header included
				m_sStream << "#include \"" << shortFileName( global_vars.m_visitorHeaderFileName) << "\"" << std::endl;
		}
		else // the file existed, how come it was supposed to be moved to .bak
		{
			// it might happen that we have a 'Package' and 'package' class 
			// which is OK in GME, but not for WINDOS: filenames are similar in such a case
			// we issue a warning and append the new contents
			global_vars.err << MSG_WARNING << "Methods of class \"" << fname << "\" appended to end of file: " << fn_c << " [Hint: filenames are not case-sensitive, thus might clash!]";
		}

		m_sStream << std::endl;
		m_sStream << std::endl;
	}
}

void Any::initOutH( std::string& resu)
{
	if( global_vars.m_outputMethod == Globals::OUTPUTMETHOD_ENUM::PERCLASS) // 
	{
		std::string dirname = getValidNmspc();
		std::string fname   = getName();
		std::string cc      = capitalizeString( dirname + fname);

		// check dir for namespace
		if( !dirname.empty())
		{
			bool success = directoryExists( dirname.c_str());
			if( !success) success = directoryCreate( dirname.c_str());

			if( success) dirname += "\\";
			else         dirname  = "";
		}

		std::string fn_h = dirname + fname + ".h";
		//Dumper::backup( fn_h.c_str()); // makes backup if exists file
		
		m_hStream.open( fn_h.c_str(), std::ios_base::out | std::ios_base::app); // append old file
		m_hStream.seekp( 0, std::ios::end); // go to end
		int lenf = m_hStream.tellp();
		if( lenf == ( std::fstream::pos_type) 0) 
		{
			m_hStream << "#ifndef " << cc << "_H" << std::endl;
			m_hStream << "#define " << cc << "_H" << std::endl;
			m_hStream << std::endl;
			m_hStream << "#include \"" << shortFileName( global_vars.header_file_name) << "\"" << std::endl;
		}
		else // the file existed, how come it was supposed to be moved to .bak
		{
			// it might happen that we have a 'Package' and 'package' class 
			// which is OK in GME, but not for WINDOS: filenames are similar in such a case
			// we issue a warning and append the new contents with some minor tricks like #if 1 // dummy
			global_vars.err << MSG_WARNING << "Declaration for class \"" << fname << "\" appended to end of file: " << fn_h << " [Hint: filenames are not case-sensitive, thus might clash!]";

			m_hStream << "#if 1 // dummy" << std::endl; // just to fool finiOutH
		}

		m_hStream << std::endl;
		m_hStream << std::endl;

		// repl '\' with '/' if dirname is filled
		resu += "#include \"" + ( dirname.empty()?"":dirname.substr(0, dirname.length() - 1) + "/") + fname + ".h\"\n";
	}
}

void Any::finiOutS()
{
	if( global_vars.m_outputMethod == Globals::OUTPUTMETHOD_ENUM::PERCLASS) // 
	{
		m_sStream.close();
	}
}

void Any::finiOutH()
{
	if( global_vars.m_outputMethod == Globals::OUTPUTMETHOD_ENUM::PERCLASS) // 
	{
		m_hStream << "#endif" << std::endl;
		m_hStream.close();
	}
}

void Any::sendOutH( const std::string& content)
{
	if( global_vars.m_outputMethod == Globals::OUTPUTMETHOD_ENUM::ALLTOGETHER) // one file policy
	{
		DMP_H( content);
	}
	else if( global_vars.m_outputMethod == Globals::OUTPUTMETHOD_ENUM::PERCLASS) // 
	{
		m_hStream << content;//dmp( "this->getname", content);
	}
	else if( global_vars.m_outputMethod == Globals::OUTPUTMETHOD_ENUM::PERNAMESPACE) // 
	{
		//dmp( "this->getnamespace", content);
	}
}

void Any::sendOutS( const std::string& content)
{
	if( global_vars.m_outputMethod == Globals::OUTPUTMETHOD_ENUM::ALLTOGETHER) // one file policy
	{
		DMP_S( content);
	}
	else if( global_vars.m_outputMethod == Globals::OUTPUTMETHOD_ENUM::PERCLASS) // 
	{
		m_sStream << content;//dmp( "this->getname", content);
	}
	else if( global_vars.m_outputMethod == Globals::OUTPUTMETHOD_ENUM::PERNAMESPACE) // 
	{
		//dmp( "this->getnamespace", content);
	}
}