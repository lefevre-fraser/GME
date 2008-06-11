#include "stdafx.h"

#include "MyUtil.h"
#include "FCO.h"
#include "ReferenceRep.h"
#include "logger.h"
#include "Token.h"
#include <list>
#include <algorithm>

#include "globals.h"
extern Globals global_vars;


/*static*/ const std::string FCO::IsAbstract_str = "IsAbstract";
/*static*/ const std::string FCO::Icon_str = "Icon";
/*static*/ const std::string FCO::PortIcon_str = "PortIcon";
/*static*/ const std::string FCO::Decorator_str = "Decorator";
/*static*/ const std::string FCO::IsHotspotEnabled_str = "IsHotspotEnabled";
/*static*/ const std::string FCO::IsTypeShown_str = "IsTypeShown";
/*static*/ const std::string FCO::GeneralPreferences_str = "GeneralPreferences";
/*static*/ const std::string FCO::NamePosition_str = "NamePosition";
/*static*/ const std::string FCO::SubTypeIcon_str = "SubTypeIcon";
/*static*/ const std::string FCO::InstanceIcon_str = "InstanceIcon";
/*static*/ const std::string FCO::NameWrapNum_str = "NameWrapNum";
/*static*/ const std::string FCO::IsNameEnabled_str = "IsNameEnabled";


FCO::FCO( IMgaFCO* ptr, IMgaFCO* resp_ptr)
	: Any( ptr)
	, m_respPointer( resp_ptr)
	, m_isAbstract( false)
	, m_bAttrIsHotspotEnabled( true)
	, m_bAttrIsTypeShown( false)
	, m_bAttrIsNameEnabled( true)
	, m_iAttrNamePosition( 0)
	, m_iAttrNameWrapNum( 0)
	, m_references()
	, m_partOf()
	, m_partOfFinal()
	, m_initialAttributeList()
	, m_finalAttributeList()
{ 
	for ( int i = 0; i < NUMBER_OF_INHERITANCES; ++i)
	{
		m_childList[i].clear();
		m_parentList[i].clear();
		m_ancestors[i].clear();
		m_descendants[i].clear();
	}
}


FCO::~FCO() 
{ 
	m_references.clear();
	m_partOf.clear();
	m_partOfFinal.clear();
	m_initialAttributeList.clear();
	m_finalAttributeList.clear();

	for ( int i = 0; i < NUMBER_OF_INHERITANCES; ++i)
	{
		m_childList[i].clear();
		m_parentList[i].clear();
		m_ancestors[i].clear();
		m_descendants[i].clear();
	}
}


std::string FCO::getName() const
{
	if( m_respPointer)
	{
		CComBSTR nm;
		COMTHROW( m_respPointer->get_Name( &nm));
		return m_namespace + (m_namespace.empty()?"":Any::NamespaceDelimiter_str) + Util::Copy( nm);
	}
	else
	{
		CComBSTR nm;
		COMTHROW( m_ptr->get_Name( &nm));
		return m_namespace + (m_namespace.empty()?"":Any::NamespaceDelimiter_str) + Util::Copy( nm);
	}
}


std::string FCO::getDispName() const
{
	if( m_respPointer) // not a plain fco, it has its resppointer set
	{
		// previously return "";
		return m_userSelectedDisplayName;
	}
	else
	{
		return m_sAttrDispName;
	}
}


void FCO::initAttributes()
{
	m_isInRootFolder = m_isInRootFolder || Util::getBoolAttr( m_ptr, InRootFolder_str);

	// isAbstract: true iff all values (which are set) are true
	bool isabs = true; // if any of the set values is false it will change
	bool isabs_set = false;
	//m_isAbstract = m_isAbstract && m_ptr->getAttribute( IsAbstract_str)->getBooleanValue();
	if( Util::isAttrStatHere( m_ptr, IsAbstract_str))
	{
		isabs = isabs && Util::getBoolAttr( m_ptr, IsAbstract_str);
		isabs_set = true;
	}

	// general pref
	bool isgenpref_set = false;
	if( Util::isAttrStatHere( m_ptr, GeneralPreferences_str))
	{
		m_sAttrGenPref = Util::getStrAttr( m_ptr, GeneralPreferences_str);
		isgenpref_set = true;
	}

	// displayed name
	bool isdispname_set = false;
	if( Util::isAttrStatHere( m_ptr, DisplayedName_str))
	{
		m_sAttrDispName = Util::getStrAttr( m_ptr, DisplayedName_str);
		isdispname_set = true;
	}

	// --applicable to non proxies only--

	bool ishotspotenabled_set = false;
	if( Util::isAttrStatHere( m_ptr, IsHotspotEnabled_str))
	{
		m_bAttrIsHotspotEnabled	= Util::getBoolAttr( m_ptr, IsHotspotEnabled_str);// def val: TRUE (dumped if FALSE)
		ishotspotenabled_set = true;

	}
	
	bool istypeshown_set = false;
	if( Util::isAttrStatHere( m_ptr, IsTypeShown_str))
	{
		m_bAttrIsTypeShown		= Util::getBoolAttr( m_ptr, IsTypeShown_str);		// def val: FALSE (dumped if TRUE)
		istypeshown_set = true;
	}
	
	bool isnameenabled_set = false;
	if( Util::isAttrStatHere( m_ptr, IsNameEnabled_str))
	{
		m_bAttrIsNameEnabled	= Util::getBoolAttr( m_ptr, IsNameEnabled_str);	// def val: TRUE (dumped if FALSE)
		isnameenabled_set = true;
	}

	bool isnamepos_set = false;
	//if( Util::isAttrStatHere( m_ptr, NamePosition_str))
	{
		m_iAttrNamePosition	= Util::getLongAttr( m_ptr, NamePosition_str);// dumped anyway
		isnamepos_set = true;
	}

	bool isnamewrapnum_set = false;
	if( Util::isAttrStatHere( m_ptr, NameWrapNum_str))
	{
		m_iAttrNameWrapNum	= Util::getLongAttr( m_ptr, NameWrapNum_str); // dumped if not 0
		isnamewrapnum_set = true;
	}

	bool icon_set = false;
	if( Util::isAttrStatHere( m_ptr, Icon_str))
	{
		m_sAttrIcon = Util::getStrAttr( m_ptr, Icon_str); // dumped if not empty
		icon_set = true;
	}

	bool porticon_set = false;
	if( Util::isAttrStatHere( m_ptr, PortIcon_str))
	{
		m_sAttrPortIcon = Util::getStrAttr( m_ptr, PortIcon_str);
		porticon_set = true;
	}

	bool subtypeicon_set = false;
	if( Util::isAttrStatHere( m_ptr, SubTypeIcon_str))
	{
		m_sAttrSubTypeIcon = Util::getStrAttr( m_ptr, SubTypeIcon_str);
		subtypeicon_set = true;
	}

	bool instanceicon_set = false;
	if( Util::isAttrStatHere( m_ptr, InstanceIcon_str))
	{
		m_sAttrInstanceIcon = Util::getStrAttr( m_ptr, InstanceIcon_str);
		instanceicon_set = true;
	}

	bool decorator_set = false;
	if( Util::isAttrStatHere( m_ptr, Decorator_str))
	{
		m_sAttrDecorator = Util::getStrAttr( m_ptr, Decorator_str);
		decorator_set = true;
	}

	// proxies have only the following attributes: abstract, inrootfolder, displayedname, generalpref
	// real objects have beside these other attributes

	// abstract iff all equivalent classes are abstract
	EquivSet_ConstIterator it = m_equivs.begin();
	for ( ; it != m_equivs.end(); ++it)
	{
		if ( *it == m_ptr) continue;
		
		// --the following 4 attributes are applicable to proxies as well--
		// InRootFolder: true if one is at least true
		m_isInRootFolder = m_isInRootFolder || Util::getBoolAttr( (*it), InRootFolder_str);

		// isAbstract: true if all objects are true
		//m_isAbstract = m_isAbstract && (*it)->getAttribute( IsAbstract_str)->getBooleanValue();
		if( Util::isAttrStatHere( *it, IsAbstract_str)) // if set by the user
		{
			isabs = isabs && Util::getBoolAttr( (*it), IsAbstract_str);
			isabs_set = true;
		}
#if(1)
		// general pref
		if ( !isgenpref_set && Util::isAttrStatHere( *it, GeneralPreferences_str))
		{
			m_sAttrGenPref = Util::getStrAttr( (*it), GeneralPreferences_str);
			isgenpref_set = true;
		}

		// displayed name
		if ( !isdispname_set && Util::isAttrStatHere( *it, DisplayedName_str))
		{
			m_sAttrDispName = Util::getStrAttr( (*it), DisplayedName_str);
			isdispname_set = true;
		}

		// --applicable to non proxies only--
		if ( Util::isproxy( *it)) continue;

		if( !ishotspotenabled_set && Util::isAttrStatHere( *it, IsHotspotEnabled_str))
		{
			m_bAttrIsHotspotEnabled	= m_bAttrIsHotspotEnabled || Util::getBoolAttr( (*it), IsHotspotEnabled_str);
			ishotspotenabled_set = true;
		}
		
		if( !istypeshown_set && Util::isAttrStatHere( *it, IsTypeShown_str))
		{
			m_bAttrIsTypeShown		= m_bAttrIsTypeShown || Util::getBoolAttr( (*it), IsTypeShown_str);
			istypeshown_set = true;
		}
		
		if( !isnameenabled_set && Util::isAttrStatHere( *it, IsNameEnabled_str))
		{
			m_bAttrIsNameEnabled	= m_bAttrIsNameEnabled || Util::getBoolAttr( (*it), IsNameEnabled_str);
			isnameenabled_set = true;
		}


		if ( !isnamepos_set && Util::isAttrStatHere( *it, NamePosition_str))
		{
			m_iAttrNamePosition	= Util::getLongAttr( (*it), NamePosition_str);
			isnamepos_set = true;
		}
		if ( !isnamewrapnum_set && Util::isAttrStatHere( *it, NameWrapNum_str))
		{
			m_iAttrNameWrapNum	= Util::getLongAttr( (*it), NameWrapNum_str);
			isnamewrapnum_set = true;
		}


		if ( !icon_set && Util::isAttrStatHere( *it, Icon_str))
		{
			m_sAttrIcon = Util::getStrAttr( (*it), Icon_str);
			icon_set = true;
		}
		if ( !porticon_set && Util::isAttrStatHere( *it, PortIcon_str))
		{
			m_sAttrPortIcon = Util::getStrAttr( (*it), PortIcon_str);
			porticon_set = true;
		}
		if( !subtypeicon_set && Util::isAttrStatHere( *it, SubTypeIcon_str))
		{
			m_sAttrSubTypeIcon = Util::getStrAttr( (*it), SubTypeIcon_str);
			subtypeicon_set = true;
		}
		if ( !instanceicon_set && Util::isAttrStatHere( *it, InstanceIcon_str))
		{
			m_sAttrInstanceIcon = Util::getStrAttr( (*it), InstanceIcon_str);
			instanceicon_set = true;
		}
		if ( !decorator_set && Util::isAttrStatHere( *it, Decorator_str))
		{
			m_sAttrDecorator = Util::getStrAttr( (*it), Decorator_str);
			decorator_set = true;
		}
#endif
	}
	
	if( isabs_set) m_isAbstract = isabs;

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


void FCO::iAmPartOfFinal( ModelRep * mod_ptr)
{
	std::vector<ModelRep *>::iterator jt = 
		std::find( m_partOfFinal.begin(), m_partOfFinal.end(), mod_ptr);

	// not inserting two times
	if (jt == m_partOfFinal.end() )
		m_partOfFinal.push_back( mod_ptr);
	else { }
}


const FCO::ModelRepPtrList& FCO::modelsIAmPartOf()
{
	return m_partOf;
}


const FCO::ModelRepPtrList& FCO::modelsIAmPartOfFinal()
{
	return m_partOfFinal;
}


bool FCO::amIPartOf(const ModelRep * mod_ptr) const
{
	ModelRepPtrList_ConstIterator it = 
		std::find( m_partOf.begin(), m_partOf.end(), mod_ptr);
	return ( it != m_partOf.end());
}


bool FCO::amIPartOfFinal(const ModelRep * mod_ptr) const
{
	ModelRepPtrList_ConstIterator it = 
		std::find( m_partOfFinal.begin(), m_partOfFinal.end(), mod_ptr);
	
	return ( it != m_partOfFinal.end());
}


// returns if this is not part of any model
bool FCO::checkIsPartOf()
{
	return !m_partOf.empty();
}


bool FCO::checkIsPartOfFinal()
{
	return !m_partOfFinal.empty();
}


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
		global_vars.err << MSG_ERROR << m_ptr << " fco has another kind of ancestor or descendant.\n";
	return same_kind;
}


// initial reference list
void FCO::addRefersToMe( ReferenceRep * ref_obj)
{
	m_references.push_back( ref_obj);
}


const FCO::ReferenceRepList& FCO::getReferences() const
{
	return m_references;
}

// final reference list
void FCO::addFinalRefersToMe( ReferenceRep * ref_obj)
{
	if( std::find( m_finalReferences.begin(), m_finalReferences.end(), ref_obj) == m_finalReferences.end())
		m_finalReferences.push_back( ref_obj);
}


const FCO::ReferenceRepList& FCO::getFinalReferences() const
{
	return m_finalReferences;
}


/*
Dealing with the case when R1->R2->R3->M. 
They all have similar aspects, and connecting is allowed through these.
Previously named getAllMyReferences
*/
FCO::ReferenceRepList FCO::getTransitiveReferencesToMe() const
{
	ReferenceRepList multiple_refs = this->getFinalReferences();
	std::list< ReferenceRep * > ref_list;
	ref_list.insert( ref_list.end(), multiple_refs.begin(), multiple_refs.end());

	while ( !ref_list.empty())
	{
		ReferenceRep * r = *ref_list.begin(); // take a ref from the final references to me
		ref_list.pop_front();
		std::vector< ReferenceRep *> temp = r->getFinalReferences(); // take its references

		std::vector<ReferenceRep *>::iterator temp_it = temp.begin();
		for( ; temp_it != temp.end(); ++temp_it)
		{
			if( std::find( multiple_refs.begin(), multiple_refs.end(), *temp_it) == multiple_refs.end()) // not found a ref in the current transitive ref list
			{
				multiple_refs.push_back( *temp_it); // multiple_refs is growing
				ref_list.push_back( *temp_it); // ref_list contains the new elements
			}
		}
	}
	return multiple_refs;
}


//
// inheritance related methods
//
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
		global_vars.err << MSG_WARNING << "CHECK: " << (*jt)->getPtr() <<
			" base class is two times in direct inheritance " <<
			" relation with the derived class " <<
			m_ptr << "\n";
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


void FCO::setAncestors( INHERITANCE_TYPE type, const std::vector<FCO*> &anc_list)
{
	ASSERT( type != REGULAR);
	//global_vars.err << getName() << " . # of ancest: " << anc_list.size() << " with type: "<< type << "\n";

	m_ancestors[type].clear();
	m_ancestors[type].insert( m_ancestors[type].end(), anc_list.begin(), anc_list.end());
}


void FCO::setDescendants( INHERITANCE_TYPE type, const std::vector<FCO*> &desc_list)
{
	ASSERT( type != REGULAR);
	//global_vars.err << getName() << " . # of desc: " << desc_list.size() << " with type: "<< type << "\n";

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


const FCO::AttributeRepPtrList& FCO::getInitialAttributeRepPtrList() const
{
	return m_initialAttributeList;
}


void FCO::addInitialAttribute( AttributeRep * attr)
{
	AttributeRepPtrList_ConstIterator it = 
		std::find( m_initialAttributeList.begin(), m_initialAttributeList.end(), attr);

	if ( it == m_initialAttributeList.end()) // not found so insert
		m_initialAttributeList.push_back( attr);
	else 
		global_vars.err << MSG_ERROR << attr->getPtr() << " attribute owned by " << m_ptr << " twice\n";
}


void FCO::addFinalAttribute( AttributeRep * attr)
{
	AttributeRepPtrList_ConstIterator it = 
		std::find( m_finalAttributeList.begin(), m_finalAttributeList.end(), attr);

	if ( it == m_finalAttributeList.end()) // not found so insert
		m_finalAttributeList.push_back( attr);
	/*else not an error because of multiple inheritance
		global_vars.err << attr->getName() << " attribute owned by " << getName() << " twice\n";*/
}


void FCO::addFinalAttributeList(const AttributeRepPtrList& t_list)
{
	AttributeRepPtrList_ConstIterator it_pos = t_list.begin();
	for( ; it_pos != t_list.end(); ++it_pos)
		addFinalAttribute( *it_pos);
}

bool FCO::findFinalAttributeBasedOnName( const std::string & name)
{
	AttributeRepPtrList_Iterator it;
	it = m_finalAttributeList.begin();
	while( it != m_finalAttributeList.end() && !((*it)->getName() == name /*&& (*it)->isViewable()*/))
		++it;
	return ( it != m_finalAttributeList.end()); // if found
}


// dumps out all owned (non-global) attributes
std::string FCO::dumpAttributes()
{
	std::string mmm = "";
	AttributeRepPtrList_Iterator it;
	
	AnyLexicographicSort lex;
	std::string last_name = "";
	std::sort( m_finalAttributeList.begin(), m_finalAttributeList.end(), lex );

	it = m_finalAttributeList.begin();
	for( ; it != m_finalAttributeList.end(); ++it)
		if ( !(*it)->isGlobal())
		{
			//if ( (*it)->isViewable())
			mmm += (*it)->doDumpAttr( getName());
			if ( last_name != "" && last_name == (*it)->getName())
				global_vars.err << MSG_ERROR << "Duplicate attribute name " << (*it)->getPtr() << " found for " << m_ptr << "\n";
			last_name = (*it)->getName();
		}

	return mmm;
}


// dumps out sorted attribute name list 
std::string FCO::dumpAttributeList( bool check_viewable /* = false */ )
{
	std::list<AttributeRep*> temp_list;
	std::list<AttributeRep*>::iterator t_it;
	std::string mmm = "";

	AttributeRepPtrList_Iterator it;
	
	it = m_finalAttributeList.begin();
	for( ; it != m_finalAttributeList.end(); ++it)
		if ( !check_viewable || (*it)->isViewable())
		{
			t_it = temp_list.begin();
			while( t_it != temp_list.end() && (*t_it)->lessThan(*it))
				++t_it;
			temp_list.insert( t_it, *it);
		}

	if ( !temp_list.empty())
	{
		mmm = " attributes = \"";
		for( t_it = temp_list.begin(); t_it != temp_list.end(); ++t_it)
		{
			if (t_it != temp_list.begin()) mmm += " ";
			mmm += (*t_it)->getName();
		}
		mmm += "\"";
	}
	return mmm;
}


std::string FCO::dumpIcon()
{
	std::string mmm;
	std::vector<FCO*> ancestors;
	getImpAncestors( ancestors);
	std::vector<FCO*>::iterator it = ancestors.begin();
	for( ; it != ancestors.end(); ++it)
	{
		mmm += (*it)->dumpIcon();
	}

	//if ( this->m_ptr)
	{
		std::string &icon = m_sAttrIcon;//m_ptr->getAttribute( Icon_str)->getStringValue();

		if( !icon.empty())
			mmm += indStr() + "<regnode name = \"icon\" value =\"" + icon + "\"></regnode>\n";
	}
	return mmm;
}


std::string FCO::dumpPortIcon()
{
	std::string mmm;
	std::vector<FCO*> ancestors;
	getImpAncestors( ancestors);
	std::vector<FCO*>::iterator it = ancestors.begin();
	for( ; it != ancestors.end(); ++it)
	{
		mmm += (*it)->dumpPortIcon();
	}

	//if ( this->m_ptr)
	{
		std::string &icon = m_sAttrPortIcon;//m_ptr->getAttribute( PortIcon_str)->getStringValue();

		if( !icon.empty())
			mmm += indStr() + "<regnode name = \"porticon\" value =\"" + icon + "\"></regnode>\n";
	}
	return mmm;
}


std::string FCO::dumpDecorator()
{
	std::string mmm;
	std::vector<FCO*> ancestors;
	getImpAncestors( ancestors);
	std::vector<FCO*>::iterator it = ancestors.begin();
	for( ; it != ancestors.end(); ++it)
	{
		mmm += (*it)->dumpDecorator();
	}

	//if ( this->m_ptr)
	{
		std::string &icon = m_sAttrDecorator;//m_ptr->getAttribute( Decorator_str)->getStringValue();

		if( !icon.empty())
			mmm += indStr() + "<regnode name = \"decorator\" value =\"" + icon + "\"></regnode>\n";
	}
	return mmm;

}


std::string FCO::dumpHotspotEnabled()
{
	std::string mmm;
	std::vector<FCO*> ancestors;
	getImpAncestors( ancestors);
	std::vector<FCO*>::iterator it = ancestors.begin();
	for( ; it != ancestors.end(); ++it)
	{
		mmm += (*it)->dumpHotspotEnabled();
	}

	//if ( this->m_ptr)
	{
		bool &icon = m_bAttrIsHotspotEnabled;//m_ptr->getAttribute( IsHotspotEnabled_str)->getBooleanValue();

		if( !icon)
			mmm += indStr() + "<regnode name = \"isHotspotEnabled\" value =\"false\"></regnode>\n";
	}
	return mmm;
}


std::string FCO::dumpTypeShown()
{
	std::string mmm;
	std::vector<FCO*> ancestors;
	getImpAncestors( ancestors);
	std::vector<FCO*>::iterator it = ancestors.begin();
	for( ; it != ancestors.end(); ++it)
	{
		mmm += (*it)->dumpTypeShown();
	}

	//if ( this->m_ptr)
	{
		bool &icon = m_bAttrIsTypeShown;//m_ptr->getAttribute( IsTypeShown_str)->getBooleanValue();

		if( icon)
			mmm += indStr() + "<regnode name = \"isTypeShown\" value =\"true\"></regnode>\n";
	}
	return mmm;
}

std::string FCO::dumpGeneralPref()
{
	std::string mmm;
	std::vector<FCO*> ancestors;
	getImpAncestors( ancestors);
	std::vector<FCO*>::iterator it = ancestors.begin();
	for( ; it != ancestors.end(); ++it)
	{
		mmm += (*it)->dumpGeneralPref();
	}
	
	//if ( this->m_ptr)
	{
		std::string &prefs_1 = m_sAttrGenPref;//m_ptr->getAttribute( GeneralPreferences_str)->getStringValue();

		if (prefs_1.empty()) return mmm;

		bool berr = false;
		//CString prefs = prefs_1.c_str();
		std::string prefs = prefs_1;
		//CStringArray prefArr;
		std::vector< std::string > prefArr;
		//CTokenEx	 tok;
		Tokenizer tok;
		//tok.Split(prefs, _T("\n"), prefArr);
		tok.split( prefs, _T("\n"), prefArr);
		//for (int i = 0; i < prefArr.GetSize(); i++) {
		for (int i = 0; i < prefArr.size(); i++) {
			//CStringArray prefPair;
			std::vector< std::string > prefPair;
			//tok.Split(prefArr[i], _T("="), prefPair);
			tok.split( prefArr[i], _T("="), prefPair);
			// Compatibility with the older format
			//if (prefPair.GetSize() != 2) {
			if (prefPair.size() != 2) {
				//prefPair.RemoveAll();
				prefPair.clear();
				//tok.Split(prefArr[i], _T(","), prefPair);
				tok.split( prefArr[i], _T(","), prefPair);
				//if (prefPair.GetSize() == 2) {
				if (prefPair.size() == 2) {
					global_vars.err << MSG_WARNING << "Warning: Deprecated general preferences format for " << m_ptr << ".\n" << MSG_NORMAL << "Valid format:\n\t<prefname1> = <value1>\n\t<prefname2> = <value2>\n\t...\n";
				}
			}
			//if (prefPair.GetSize() == 2) {
			if (prefPair.size() == 2) {
				//prefPair[0].TrimLeft();
				tok.trimLeft( prefPair[0]);
				//prefPair[0].TrimRight();
				tok.trimRight( prefPair[0]);
				//prefPair[1].TrimLeft();
				tok.trimLeft( prefPair[1]);
				//prefPair[1].TrimRight();
				tok.trimRight( prefPair[1]);
				//mmm += indStr() + "<regnode name = \"" + (LPCTSTR)prefPair[0] + "\" value =\"" + (LPCTSTR)prefPair[1] + "\"></regnode>\n";
				if( prefPair[0].empty())
					global_vars.err << MSG_ERROR << "Empty General Preference token found at " << m_ptr << " with \"" << prefPair[1] << "\" as value.\n";
				else
					mmm += indStr() + "<regnode name = \"" + prefPair[0] + "\" value =\"" + prefPair[1] + "\"></regnode>\n";
			}
			else {
				berr = true;
				break;
			}
		}
		if(berr) {
			global_vars.err << MSG_ERROR << "Invalid general preferences specification for " << m_ptr << ".\n"
				<< MSG_NORMAL << "Valid format:\n\t<prefname1> = <value1>\n\t<prefname2> = <value2>\n\t...\n";
		}
	}
	return mmm;
}
 

std::string FCO::dumpNamePosition() const
{
	std::string mmm;
	//if ( this->m_ptr)
	{
		int name_pos = min(8,max(0,m_iAttrNamePosition));//m_ptr->getAttribute( NamePosition_str)->getIntegerValue();
		char p[2];
		sprintf(p, "%d", name_pos);
		mmm = std::string( p);
	}
	//else mmm = "NullPtrError";
	return indStr() + "<regnode name = \"namePosition\" value =\"" + mmm +"\">" + "</regnode>\n";
}


std::string FCO::dumpSubTypeIcon() const
{
	std::string mmm;
	std::vector<FCO*> ancestors;
	getImpAncestors( ancestors);
	std::vector<FCO*>::iterator it = ancestors.begin();
	for( ; it != ancestors.end(); ++it)
	{
		mmm += (*it)->dumpSubTypeIcon();
	}

	//if ( this->m_ptr)
	{
		const std::string &icon = m_sAttrSubTypeIcon;//m_ptr->getAttribute( SubTypeIcon_str)->getStringValue();

		if( !icon.empty())
			mmm += indStr() + "<regnode name = \"subTypeIcon\" value =\"" + icon + "\"></regnode>\n";
	}
	return mmm;
}


std::string FCO::dumpInstanceIcon() const
{
	std::string mmm;
	std::vector<FCO*> ancestors;
	getImpAncestors( ancestors);
	std::vector<FCO*>::iterator it = ancestors.begin();
	for( ; it != ancestors.end(); ++it)
	{
		mmm += (*it)->dumpInstanceIcon();
	}

	//if ( this->m_ptr)
	{
		const std::string &icon = m_sAttrInstanceIcon;//m_ptr->getAttribute( InstanceIcon_str)->getStringValue();

		if( !icon.empty())
			mmm += indStr() + "<regnode name = \"instanceIcon\" value =\"" + icon + "\"></regnode>\n";
	}
	return mmm;
}


std::string FCO::dumpNameWrap() const
{
	std::string mmm;
	std::vector<FCO*> ancestors;
	getImpAncestors( ancestors);
	std::vector<FCO*>::iterator it = ancestors.begin();
	for( ; it != ancestors.end(); ++it)
	{
		mmm += (*it)->dumpNameWrap();
	}

	//if ( this->m_ptr)
	{
		const int &icon = m_iAttrNameWrapNum;//m_ptr->getAttribute( NameWrapNum_str)->getIntegerValue();
		char p[64];
		sprintf(p, "%d", icon);
		std::string icon_str( (const char *) p);// = m_ptr->getAttribute( NameWrapNum_str)->getStringValue();
		if( icon != 0)
			mmm += indStr() + "<regnode name = \"nameWrap\" value =\"" + icon_str + "\"></regnode>\n";
	}
	return mmm;
}


std::string FCO::dumpNameEnabled() const
{
	std::string mmm;
	std::vector<FCO*> ancestors;
	getImpAncestors( ancestors);
	std::vector<FCO*>::iterator it = ancestors.begin();
	for( ; it != ancestors.end(); ++it)
	{
		mmm += (*it)->dumpNameEnabled();
	}

	//if ( this->m_ptr)
	{
		const bool &icon = m_bAttrIsNameEnabled;//m_ptr->getAttribute( IsNameEnabled_str)->getBooleanValue();

		if( !icon)
			mmm += indStr() + "<regnode name = \"isNameEnabled\" value =\"false\"></regnode>\n";
	}
	return mmm;
}
