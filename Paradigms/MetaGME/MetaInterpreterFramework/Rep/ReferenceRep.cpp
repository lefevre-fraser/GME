#include "stdafx.h"
#include "BON.h"
#include "BONImpl.h"
#include "ReferenceRep.h"
#include "ModelRep.h"
#include "globals.h"
extern Globals global_vars;


ReferenceRep::ReferenceRep( BON::FCO& ptr) :
    Any( ptr)
  , Constrained( ptr)
  , FCO( ptr)
	, m_initialReferees()
{ }


ReferenceRep::~ReferenceRep() 
{ 
	m_initialReferees.clear();
}


void ReferenceRep::addInitialReferee( FCO * refd ) 
{	
	if ( std::find( m_initialReferees.begin(), m_initialReferees.end(), refd) 
		== m_initialReferees.end()) // not found
		m_initialReferees.push_back( refd );
	else
		global_vars.err << "Warning: Reference \"" << getName() << "\" referring twice to fco: \"" << refd->getName() << "\". Disregarded.\n";
}


FCO * ReferenceRep::getInitialReferee() const
{
	if (checkNotEmpty()) return m_initialReferees[0];
	else return 0; // or an exception
}


const ReferenceRep::RefereeList& ReferenceRep::getInitialReferees() const
{
	return m_initialReferees;
}


bool ReferenceRep::checkNotEmpty() const
{
	return !m_initialReferees.empty();
}
