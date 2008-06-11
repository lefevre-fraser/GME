#include "stdafx.h"
#include "BON.h"
#include "BONImpl.h"
#include "ReferenceRep.h"
#include "ModelRep.h"
#include "logger.h"
#include "globals.h"
extern Globals global_vars;


void ModelRep::addRole( FCO* whose, RoleSeriesValue& role) 
{ 
	RoleMapValue &series = m_initialRoleMap[ whose ];

	// avoiding double insertion
	// searching for the role in the role register
	RoleSeries_Iterator it = std::find( series.begin(), series.end(), role);

	if ( it == series.end() ) // not found
		series.push_back( role);
	else 
		global_vars.err << "Error: Found duplicate role \"" << role.getSmartRoleName() << "\" in model \"" << getName() << "\"\n";
}


void ModelRep::initRoles()
{
	RoleMap_Iterator it = m_initialRoleMap.begin();
	for( ; it != m_initialRoleMap.end(); ++it)
	{
		RoleMapKey fco = it->first; // FCO *
		std::string nn = fco->getName();

		std::vector<FCO*> children;
		fco->getIntDescendants( children);

		int how_many_non_abstract = 0;
		if ( !fco->isAbstract()) ++how_many_non_abstract;
		for( unsigned int i = 0; i < children.size(); ++i)
		{
			std::string cn = children[i]->getName();
			if (! children[i]->isAbstract()) 
				++how_many_non_abstract;
		}

		// at this point the how_many_non_abstract
		// value indicates how many non abstract instances may exist
		// and how many will have the use the same role names
		// so if this value is greater than 1 then long form, otherwise 
		// short form (default) should be used

		if ( how_many_non_abstract > 1 ) // long_form_flag needs to be true for this fco's roles
		{
			RoleMapValue &series = it->second;
			RoleSeries_Iterator role_it = series.begin();
			for(; role_it != series.end(); ++role_it)
			{
				role_it->setLongForm( true);
			}
		}
	}
}


std::vector< ModelRep* > ModelRep::getInnerModels() const
{
	std::vector< ModelRep* > models;

	RoleMap_ConstIterator it = m_initialRoleMap.begin();
	while ( it != m_initialRoleMap.end())
	{
		FCO * const ptr = it->first; // ModelRep *
		if ( ptr->getMyKind() == Any::MODEL)
		{
			ModelRep * mod_ptr = dynamic_cast< ModelRep *> ( ptr);
			models.push_back( mod_ptr);
		}
		++it;
	}
	return models;
}


void ModelRep::addAspect( AspectRep * asp_ptr)
{
	std::vector<AspectRep*>::iterator ii = 
		std::find( m_initialAspectList.begin(), m_initialAspectList.end(), asp_ptr);

	if (ii == m_initialAspectList.end()) // not found
		m_initialAspectList.push_back(asp_ptr);
	else
		global_vars.err << "CHECK: Model \"" << getName() << "\" has aspect \"" << asp_ptr->getName() << "\" associated twice\n";
}


const ModelRep::AspectRepPtrList& ModelRep::getAspectRepPtrList() const
{
	return m_initialAspectList;
}


bool ModelRep::getRoles( FCO * ptr, RoleMapValue& map_val) const
{
	RoleMap_ConstIterator it = m_initialRoleMap.find( ptr);
	if ( it == m_initialRoleMap.end())
		return false;

	map_val = it->second;
	return true;
}

