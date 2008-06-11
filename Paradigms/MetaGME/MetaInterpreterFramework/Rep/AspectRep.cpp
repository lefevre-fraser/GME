#include "stdafx.h"
#include "BON.h"
#include "BONImpl.h"
#include "AspectRep.h"
#include "RoleRep.h"
#include "ModelRep.h"
#include "globals.h"
extern Globals global_vars;


AspectRep::AspectRep( BON::FCO& ptr, BON::FCO& resp_ptr)
: Any( ptr), 
	m_respPointer( resp_ptr)
{ 
	m_fcoInitialList.clear();

	if (m_respPointer == BON::FCO()) 
		global_vars.err << "Fatal Error during AspectRep constructor: m_respPointer is 0\n";
}


AspectRep::~AspectRep()
{
	m_fcoInitialList.clear();
}



Any::KIND_TYPE AspectRep::getMyKind() const { return Any::ASPECT; }


std::string AspectRep::getName() const
{
	// using m_respPointer instead of m_ptr
	if (m_respPointer == BON::FCO())
	{
		global_vars.err << "Null pointer error in getAspectName\n";
		return std::string("Null pointer error in getAspectName");
	}
	else
	{
		return m_respPointer->getName();
	}
}


std::string AspectRep::getDispName() const
{
	if (m_respPointer == BON::FCO()) 
	{
		global_vars.err << "Null pointer error in getDispName for aspect \"" + getName() + "\"\n";
		return std::string("Null pointer error in getDispName for aspect \"") + getName() + "\"";
	}
	else
	{
		return m_ptr->getAttribute("DisplayedName")->getStringValue(); // <!> modified from m_respPointer
	}
}


void AspectRep::addFCO( FCO* fco) 
{
	m_fcoInitialList.push_back( fco); 
}


void AspectRep::addRRole( RoleRep & role)
{
	m_roleInitialList.push_back( role);
}


