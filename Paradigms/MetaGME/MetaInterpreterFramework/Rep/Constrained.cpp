#include "stdafx.h"
#include "Constrained.h"
#include "globals.h"
extern Globals global_vars;


Constrained::Constrained( BON::FCO& ptr) :
  Any( ptr)
{ }


Constrained::~Constrained()
{ }


void Constrained::addInitialConstraintRep( ConstraintRep * constraint)
{
	ConstraintRepPtrList_ConstIterator it = 
		std::find( m_initialConstraintList.begin(), m_initialConstraintList.end(), constraint);

	if ( it == m_initialConstraintList.end())
		m_initialConstraintList.push_back( constraint);
	else
		global_vars.err << constraint->getName() << " constraint owned by " << getName() << " twice\n";
}


const Constrained::ConstraintRepPtrList& Constrained::getInitialConstraintRepPtrList() const
{
	int i = m_initialConstraintList.size(); 
	return m_initialConstraintList;
}
