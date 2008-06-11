#include "stdafx.h"
#include "BON.h"
#include "BONImpl.h"
#include "FCO.h"
#include "ReferenceRep.h"
#include "TokenEx.h"
#include "list"
#include "algorithm"
#include "logger.h"
#include "globals.h"
extern Globals global_vars;


FCO::FCO( BON::FCO& ptr) :
	  Any( ptr)
	, Constrained( ptr)
	, m_isAbstract( false)
	, m_references()
	, m_partOf()
	, m_initialAttributeList()
{ 
	for ( int i = 0; i < NUMBER_OF_INHERITANCES; ++i)
	{
		m_childList[i].clear();
		m_parentList[i].clear();
		m_ancestors[i].clear();
		m_descendants[i].clear();
	}
	if ( m_ptr != BON::FCO())
	m_isAbstract = m_ptr->getAttribute("IsAbstract")->getBooleanValue();
}


FCO::~FCO() 
{ 
	m_references.clear();
	m_partOf.clear();
	m_initialAttributeList.clear();

	for ( int i = 0; i < NUMBER_OF_INHERITANCES; ++i)
	{
		m_childList[i].clear();
		m_parentList[i].clear();
		m_ancestors[i].clear();
		m_descendants[i].clear();
	}
}


bool FCO::isAbstract() const
{
	return m_isAbstract;
}


void FCO::abstract( bool is)
{
	m_isAbstract = is;
}


void FCO::iAmPartOf( ModelRep * mod_ptr)
{
	std::vector<ModelRep *>::iterator jt = 
		std::find( m_partOf.begin(), m_partOf.end(), mod_ptr);

	// not inserting two times
	if (jt == m_partOf.end())
		m_partOf.push_back( mod_ptr);
	else { }
}


const FCO::ModelRepPtrList& FCO::modelsIAmPartOf()
{
	return m_partOf;
}


bool FCO::amIPartOf(const ModelRep * mod_ptr) const
{
	ModelRepPtrList_ConstIterator it = 
		std::find( m_partOf.begin(), m_partOf.end(), mod_ptr);
	return ( it != m_partOf.end());
}


// returns if this is not part of any model
bool FCO::checkIsPartOf()
{
	return !m_partOf.empty();
}


void FCO::addRefersToMe( ReferenceRep * ref_obj)
{
	m_references.push_back( ref_obj);
}


const FCO::ReferenceRepList& FCO::getReferences() const
{
	return m_references;
}


const FCO::AttributeRepPtrList& FCO::getInitialAttributeRepPtrList() const
{
	return m_initialAttributeList;
}


void FCO::addInitialAttribute( AttributeRep * attr)
{
	AttributeRepPtrList_ConstIterator it = 
		std::find( m_initialAttributeList.begin(), m_initialAttributeList.end(), attr);

	if ( it == m_initialAttributeList.end()) // not found so insert
	{
		m_initialAttributeList.push_back( attr);
	}
	else 
		global_vars.err << attr->getName() << " attribute owned by " << getName() << " twice\n";
}


//
// inheritance related methods
//
bool FCO::checkInheritance()
{
	bool same_kind = true;
	KIND_TYPE kind_type = getMyKind();

	INHERITANCE_TYPE type[ NUMBER_OF_INHERITANCES ] ={ REGULAR, INTERFACE, IMPLEMENTATION};
	for(int i = 0; i < NUMBER_OF_INHERITANCES && same_kind; ++i)
	{
		INHERITANCE_TYPE inh_type = type[i];
		std::vector<FCO*> * vectors[] = {
			&m_childList[inh_type], 
			&m_parentList[inh_type], 
			&m_ancestors[inh_type], 
			&m_descendants[inh_type] 
		};
		for(int k = 0; k < 4 && same_kind; ++k)
		{
			std::vector<FCO*>::iterator it = vectors[k]->begin();
			for( ; it != vectors[k]->end() && same_kind; ++it)
				if ((*it)->getMyKind() != FCO_REP)
					same_kind = same_kind && kind_type == (*it)->getMyKind();
		}
	}
	if (!same_kind) 
		global_vars.err << "ERROR: \"" << getName() << "\" fco has another kind of ancestor or descendant.\n";
	return same_kind;
}


void FCO::addParent( INHERITANCE_TYPE type, FCO * ptr) 
{ 

	//checking for multiple instances of the same base class
	std::vector<FCO *>::iterator jt = 
		std::find( m_parentList[type].begin(), m_parentList[type].end(), ptr);

	// not inserting two times
	if (jt == m_parentList[type].end())
		m_parentList[type].push_back( ptr);
	else 
	{
		global_vars.err << "CHECK: " << (*jt)->getName() <<
			" base class is two times in direct inheritance " <<
			" relation with the derived class " <<
			getName();
	}
}


void FCO::addChild( INHERITANCE_TYPE type,  FCO * ptr) 
{ 
	std::vector<FCO *>::iterator jt = 
		std::find( m_childList[type].begin(), m_childList[type].end(), ptr);
	
	// not inserting two times
	if (jt == m_childList[type].end())
		m_childList[type].push_back( ptr);
	else 
	{ }	// error already noticed by addParent
}


const std::vector<FCO *>&  FCO::getParents( INHERITANCE_TYPE type)
{
	return m_parentList[type];
}


const std::vector<FCO *>& FCO::getChildren( INHERITANCE_TYPE type)
{
	return m_childList[type];
}


bool FCO::hasParent( const FCO * par, INHERITANCE_TYPE type) const
{
	bool has = false;
	if ( type != REGULAR)
	{
		std::vector<FCO*>::const_iterator it = 
			std::find( m_parentList[REGULAR].begin(), m_parentList[REGULAR].end(), par);

		if ( it != m_parentList[REGULAR].end()) // found
			has = has || true;
	}
	if (has) return has;

	std::vector<FCO*>::const_iterator it = 
		std::find( m_parentList[type].begin(), m_parentList[type].end(), par);

	if ( it != m_parentList[type].end()) // found
		has = has || true;

	return has;
}


bool FCO::hasExactParent( const FCO * par, INHERITANCE_TYPE type) const
{
	std::vector<FCO*>::const_iterator it = 
		std::find( m_parentList[type].begin(), m_parentList[type].end(), par);

	return ( it != m_parentList[type].end()); // found
}


void FCO::setAncestors( INHERITANCE_TYPE type, const std::vector<FCO*> &anc_list)
{
	m_ancestors[type].clear();
	m_ancestors[type].insert( m_ancestors[type].end(), anc_list.begin(), anc_list.end());
}


void FCO::setDescendants( INHERITANCE_TYPE type, const std::vector<FCO*> &desc_list)
{
	m_descendants[type].clear();
	m_descendants[type].insert( m_descendants[type].end(), desc_list.begin(), desc_list.end());
}


void FCO::getIntAncestors( std::vector<FCO*> & ancestors) const
{
	ancestors.insert( ancestors.end(), m_ancestors[INTERFACE].begin(), m_ancestors[INTERFACE].end());	
}


void FCO::getIntDescendants( std::vector<FCO*> & descendants) const
{
	descendants.insert( descendants.end(), m_descendants[INTERFACE].begin(), m_descendants[INTERFACE].end());	
}


void FCO::getImpAncestors( std::vector<FCO*> & ancestors) const
{
	ancestors.insert( ancestors.end(), m_ancestors[IMPLEMENTATION].begin(), m_ancestors[IMPLEMENTATION].end());	
}


void FCO::getImpDescendants( std::vector<FCO*> & descendants) const
{
	descendants.insert( descendants.end(), m_descendants[IMPLEMENTATION].begin(), m_descendants[IMPLEMENTATION].end());	
}


std::vector<FCO *> FCO::getAllChildren()
{
	std::vector<FCO*> rr = getChildren( FCO::REGULAR);
	rr.insert( rr.end(), getChildren( FCO::INTERFACE).begin(), getChildren( FCO::INTERFACE).end());
	rr.insert( rr.end(), getChildren( FCO::IMPLEMENTATION).begin(), getChildren( FCO::IMPLEMENTATION).end());
	return rr;
}


std::vector<FCO *> FCO::getAllParents()
{
	std::vector<FCO*> rr = getParents( FCO::REGULAR);
	rr.insert( rr.end(), getParents( FCO::INTERFACE).begin(), getParents( FCO::INTERFACE).end());
	rr.insert( rr.end(), getParents( FCO::IMPLEMENTATION).begin(), getParents( FCO::IMPLEMENTATION).end());
	return rr;
}


std::vector<FCO *> FCO::getAllAncestors()
{
	std::vector<FCO *> impl, intf;
	getImpAncestors( impl);
	getIntAncestors( intf);

	std::vector<FCO *>::iterator it = intf.begin();
	for( ; it != intf.end(); ++it) // check all int
	{
		if ( impl.end() == std::find( impl.begin(), impl.end(), *it)) // not found
			impl.push_back( *it);
	}
	return impl;	
}


std::vector<FCO *> FCO::getAllDescendants()
{
	std::vector<FCO *> impl, intf;
	getImpDescendants( impl);
	getIntDescendants( intf);

	std::vector<FCO *>::iterator it = intf.begin();
	for( ; it != intf.end(); ++it) // check all int
	{
		if ( impl.end() == std::find( impl.begin(), impl.end(), *it)) // not found
			impl.push_back( *it);
	}
	return impl;	
}
