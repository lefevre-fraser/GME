#include "stdafx.h"
#include "BON.h"
#include "BONImpl.h"
#include "ConstraintFuncRep.h"
#include "Regexp.h"
#include "globals.h"
extern Globals global_vars;


ConstraintFuncRep::ConstraintFuncRep( BON::FCO& ptr) :
	Any( ptr),
	m_context(""), m_returntype(""), m_stereotype(""),
	m_definition(""), m_parameterlist("")
{ }


ConstraintFuncRep::~ConstraintFuncRep()
{ }


void ConstraintFuncRep::fetch()
{
	CString strWS = "[\t ]*";
	CString strID = "[_a-zA-Z][_a-zA-Z0-9]*";
	CString strT = strID + "(::" + strID + ")*";
	CString strP = strID + strWS + ":" + strWS + strT;

	std::string paramlist = m_ptr->getAttribute( "CFuncParamList")->getStringValue();
	Regexp rePL( "^(" + strWS + strP + ")?" + "(" + strWS + "," + strWS + strP + ")*$", TRUE );
	if ( ! rePL.CompiledOK() )
		global_vars.err << "Internal Interpreter Error: [REGEXP] " << rePL.GetErrorString();
	else
		if ( ! rePL.Match( paramlist.c_str() ) )
			global_vars.err << "Invalid format for parameterlist in Constraint Function: " << getName()
			<< "\r\nCorrect format: <paramname> : <paramtype> [, <paramname> : <paramtype>] ...";
	
	m_parameterlist = paramlist;

	std::string contexttype = m_ptr->getAttribute( "CFuncContext")->getStringValue();
	if ( contexttype.empty() ) 
	{
		global_vars.err << "No context found for Constraint Function: " << getName() << "\r\nIt will be Project implicitly.";
		contexttype = "gme::Project";
	}
	m_context = contexttype;

	std::string returntype = m_ptr->getAttribute( "CFuncReturnType")->getStringValue();
	if ( returntype.empty()) 
	{
		global_vars.err << "No return type found for Constraint Function: " << getName() << "\r\nIt will be bool implicitly.";
		returntype = "ocl::Boolean";
	}
	m_returntype = returntype;

	std::string definition = m_ptr->getAttribute( "CFuncDefinition")->getStringValue();
	if ( definition.empty() )
		global_vars.err <<"No definition found for Constraint Function: " << getName();
	m_definition = definition;
	
	std::string stereotype = m_ptr->getAttribute( "CFuncStereotype")->getStringValue();
	if ( stereotype == "attribute" && ! paramlist.empty()) 
	{
		global_vars.err << "Attribute cannot have parameters. Parameterlist is ignored for Constraint Function: " << getName();
		paramlist.empty();
	}
	m_stereotype = stereotype;
}

//---additional method
std::string ConstraintFuncRep::doDump()
{
	fetch();
	std::string mmm = "";
	
	mmm += indStr() + "<constraint type=\"function\" name=\"" + getName() + "\">\n";
	++ind;
	mmm += indStr() + "<![CDATA[" 
		+ m_stereotype + ";" + m_context + ";" 
		+ m_parameterlist + ";" + m_returntype + ";\n";
	mmm += indStr() + m_definition + "]]>\n";
	--ind;
	mmm += indStr() + "</constraint>\n"; 

	return mmm;
}