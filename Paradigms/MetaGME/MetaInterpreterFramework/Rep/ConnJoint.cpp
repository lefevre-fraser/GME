#include "stdafx.h"
#include "ConnJoint.h"
#include "ConnectionRep.h"

/*static*/ const std::string ConnJoint::m_srcLabel = "src";
/*static*/ const std::string ConnJoint::m_dstLabel = "dst";


ConnJoint::ConnJoint
	(	ConnectionRep * ptr,
		const SDList& op1,
		const SDList& op2,
		bool bidirect,
		std::string card1 /*= ""*/, 
		std::string card2 /*= ""*/
	)
	: m_connPtr( ptr),

		m_oper1( op1), 
		m_oper2( op2),
		
		m_bidirect( bidirect),

		m_oper1Card( card1),
		m_oper2Card( card2)
{ }


ConnJoint::ConnJoint( const ConnJoint& peer):
	m_connPtr( peer.m_connPtr),

	m_oper1( peer.m_oper1), 
	m_oper2( peer.m_oper2),

	m_bidirect( peer.m_bidirect),

	m_oper1Card( peer.m_oper1Card),
	m_oper2Card( peer.m_oper2Card)
{ }


const ConnJoint& ConnJoint::operator=( const ConnJoint& peer)
{
	if ( this == &peer ) return *this;
	m_connPtr = peer.m_connPtr;

	m_oper1 = peer.m_oper1;
	m_oper2 = peer.m_oper2;

	m_bidirect = peer.m_bidirect;

	m_oper1Card = peer.m_oper1Card;
	m_oper2Card = peer.m_oper2Card;

	return *this;
}


ConnJoint::~ConnJoint() 
{
	m_oper1.clear();
	m_oper2.clear();
}


ConnJoint * ConnJoint::clone() const
{
	ConnJoint * cl = new ConnJoint( *this);
	return cl;
}

const ConnJoint::SDList& ConnJoint::getOp1() const { return m_oper1; }


const ConnJoint::SDList& ConnJoint::getOp2() const { return m_oper2; }


bool ConnJoint::isBidirect() const { return m_bidirect; }
