#include "stdafx.h"
#include "BON.h"
#include "BONImpl.h"
#include "ConnectionRep.h"
#include "ModelRep.h"
#include "Globals.h"
extern Globals global_vars;


ConnectionRep::ConnectionRep( BON::FCO& ptr) : 
    Any(ptr)
  , Constrained( ptr)
	, FCO( ptr)
	, m_jointPtrList()
{ }


ConnectionRep::~ConnectionRep()
{
	std::list<ConnJoint *>::iterator it = m_jointPtrList.begin();
	for( ; it != m_jointPtrList.end(); ++it)
	{
		ConnJoint * cj = *it;
		delete cj;
	}
	m_jointPtrList.clear();
}


/*virtual*/ ConnJoint* ConnectionRep::createJoint
	( 
		ConnectionRep * ptr, const ConnJoint::SDList& op1, const ConnJoint::SDList& op2,
		bool bidirect, std::string card1 /*= ""*/, std::string card2 /*= ""*/
	)
{
	return new ConnJoint( ptr, op1, op2, bidirect, card1, card2);
}


// semantics here: composition
// destructor will destroy all instances of ConnJoint
// pointed by the elements of m_jointPtrList container
/*virtual*/void ConnectionRep::addJoint( ConnJoint * joint)
{
	m_jointPtrList.push_back( joint);
}
