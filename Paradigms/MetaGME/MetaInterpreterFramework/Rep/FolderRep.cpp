#include "stdafx.h"
#include "FolderRep.h"
#include "globals.h"
extern Globals global_vars;


std::string FolderRep::getName() const
{
	if (m_respPointer == BON::FCO())
		return std::string("Null pointer error in getFolderName");
	return m_respPointer->getName();//<!>
}


std::string FolderRep::getDispName() const
{
	//return getName();<!> mod on 10/21
	if (m_respPointer == BON::FCO())
	{
		global_vars.err << "Null pointer error in getDispName for aspect \"" + getName() + "\"\n";
		return std::string("Null pointer error in getDispName for folder \"") + getName() + "\"";
	}
	else
	{
		return m_ptr->getAttribute("DisplayedName")->getStringValue();//<!> //<!> modified from m_respPointer
	}
}


void FolderRep::addFCO( FCO * ptr, const std::string& card)
{
	if ( std::find( m_fcoList.begin(), m_fcoList.end(), ptr) == m_fcoList.end()) // not found
	{
		m_fcoList.push_back( ptr);
		m_fcoCardList.push_back( card);
	}
	else
		global_vars.err << "CHECK: "<< ptr->getName() << " contained by folder " << getName() << " twice. Disregarded.\n";
}


bool FolderRep::isFCOContained( FCO * ptr)
{
	return m_fcoList.end() != std::find( m_fcoList.begin(), m_fcoList.end(), ptr);
}


void FolderRep::addSubFolderRep( FolderRep *ptr, const std::string& card)
{
	if ( std::find( m_subFolderList.begin(), m_subFolderList.end(), ptr) 
		== m_subFolderList.end()) // not found
	{
		m_subFolderList.push_back( ptr);
		m_subCardList.push_back( card);
	}
	else
		global_vars.err << "CHECK: Folder " << ptr->getName() << " contained by folder "  << getName() << " twice. Disregarded.\n";
}

