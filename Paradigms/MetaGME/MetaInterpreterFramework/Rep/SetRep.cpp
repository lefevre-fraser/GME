#include "stdafx.h"
#include "BON.h"
#include "BONImpl.h"
#include "SetRep.h"
#include "logger.h"
#include "globals.h"
extern Globals global_vars;


void SetRep::addMember( FCO * member) 
{ 
	SetMemberList_ConstIterator it = 
		std::find( m_memberList.begin(), m_memberList.end(), member);

	if (it == m_memberList.end()) // not found
		m_memberList.push_back( member); 
	else
		global_vars.err << "Set member " << member->getName() << " is twice in set " << getName() << "\n";
} 

