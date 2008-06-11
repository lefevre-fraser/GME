#include "stdafx.h"

#include "MyUtil.h"
#include "AspectRep.h"
#include "RoleRep.h"
#include "ModelRep.h"
#include "Dumper.h"

#include <algorithm>

#include "globals.h"
extern Globals global_vars;

/*static*/ const std::string AspectRep::m_aspectRegistryRoot = "AspectRegistry";
/*static*/ const std::string AspectRep::m_aspectMetaRefsRoot = "AspectMetaRefs";
/*static*/ const std::string AspectRep::m_aspectNamesRoot    = "AspectSelNames";

bool PartCompare::operator()( const PartRep& peer1, const PartRep& peer2) const
{
	std::string name1 = peer1.getRoleRepPtr()->getSmartRoleName();
	std::string name2 = peer2.getRoleRepPtr()->getSmartRoleName();

	int k = name1.compare( name2);
	return ( k < 0);
}


bool AspectCompare::operator()( const AspectRep* peer1, const AspectRep* peer2) const
{
	return peer1->lessThan( *peer2);
}


bool AspNamePriorityComp::operator()( const Type& p1, const Type& p2) const
{
	return p1.second != p2.second ? p1.second < p2.second : (p1.first.compare( p2.first) < 0);
}


AspectRep::AspectRep( IMgaFCO* ptr, IMgaFCO* resp_ptr)
	: Any( ptr)
	, m_priority( 0)
	, m_respPointer( resp_ptr)
	, m_fcoInitialList()
	, m_roleInitialList()
	, m_fcoFinalList()
	, m_roleFinalList()
	, m_partsMap()

{ 
#if(0)
	if (m_respPointer == CComPtr<IMgaFCO>(0)) 
	{
		//v0global_vars.err << "Fatal Error during AspectRep constructor: m_respPointer is 0\n";
p		global_vars.err << MSG_WARNING << "Dummy aspect created. You should define aspects for the models.\n";
	}
#endif
}


AspectRep::~AspectRep()
{
	m_fcoInitialList.clear();
	m_roleInitialList.clear();
	m_fcoFinalList.clear();
	m_roleFinalList.clear();
	m_partsMap.clear();
}


std::string AspectRep::doDump() { return ""; }


Any::KIND_TYPE AspectRep::getMyKind() const { return Any::ASPECT; }


std::string AspectRep::getName() const
{
#if(0)
	// using m_respPointer instead of m_ptr
	if (m_respPointer == CComPtr<IMgaFCO>(0))
	{
		global_vars.err << MSG_ERROR << "Null pointer error in getAspectName\n";
		return std::string("Null pointer error in getAspectName");
	}
	else
	{
		return m_respPointer->getName();
	}
#else
#if(0)
	if( m_respPointer != CComPtr<IMgaFCO>(0))
	{
		return m_respPointer->getName();
	}
	else
	{
		return "Aspect";
	}
#else // new way
	if( m_respPointer)
	{
		CComBSTR nm;
		COMTHROW( m_respPointer->get_Name( &nm));
		return Util::Copy( nm);
	}
	else if( m_ptr)
	{
		CComBSTR nm;
		COMTHROW( m_ptr->get_Name( &nm));
		return Util::Copy( nm);
	}
	else // dummy aspect
	{
		return "Aspect";
	}
#endif
#endif
}

std::string AspectRep::getDispName() const
{
#if(0)
	if (m_respPointer == CComPtr<IMgaFCO>(0)) 
	{
		global_vars.err << MSG_ERROR << "Null pointer error in getDispName for aspect \"" + getName() + "\"\n";
		return std::string("Null pointer error in getDispName for aspect \"") + getName() + "\"";
	}
	else
	{
		return m_ptr->getAttribute( Any::DisplayedName_str)->getStringValue(); //<!> modified from m_respPointer
	}
#else
	//what about a reform such that dispname is allowed only for lonely aspects (which are not equivalent with any other)
	//<!> 

	// or what about deciding using the selected aspect's dispname attribute 
	// (what happens if the user does not know which aspect did he selected from 
	// the aspects with similar name)
#if(0)
	if( m_ptr != CComPtr<IMgaFCO>(0)) 
	{
		return m_ptr->getAttribute( Any::DisplayedName_str)->getStringValue(); //<!> modified from m_respPointer
	}
	else
	{
		return "Aspect";	
	}
#else // new way
	if( m_respPointer) // not a plain fco, it has its resppointer set
	{
		//return "";
		return m_userSelectedDisplayName;
	}
	else if( m_ptr)
	{
		CComBSTR val;
		COMTHROW( m_ptr->get_StrAttrByName( Util::Copy( Any::DisplayedName_str), &val));
		return Util::Copy( val);
	}
	else // dummy aspect
	{
		return "";
	}
#endif
#endif
}


std::string AspectRep::getMyPrefix() const
{
	// any modification in the registry policy should be syched with
	// the Broker::initFromObj method
	return AspectRep::m_aspectRegistryRoot + "/" + AspectRep::m_aspectMetaRefsRoot + "/" + getName();
}


CComPtr<IMgaRegNode> AspectRep::getMyRegistry() const
{
	// any modification in the registry policy should be syched with
	// the Broker::initFromObj method
	//if ( this->m_ptr && this->m_parentFolder)
	//return m_parentFolder->getRegistry()->getChild( getMyPrefix());
	CComPtr<IMgaRegNode> rn;
	COMTHROW( Sheet::m_BON_Project_Root_Folder->get_RegistryNode( Util::Copy( getMyPrefix()), &rn));
	return rn;
}


//
// these two methods are used only for selected name storing
//
/*static*/ std::string AspectRep::getMyPrefix( IMgaFCO* fco, IMgaFolder* f)
{
	ASSERT( fco);
	CComBSTR nm;
	COMTHROW( fco->get_Name( &nm));
	return AspectRep::m_aspectRegistryRoot + "/" + AspectRep::m_aspectNamesRoot + "/" + Util::Copy( nm);
}


/*static*/ CComPtr<IMgaRegNode> AspectRep::getMyRegistry( IMgaFCO* fco, IMgaFolder* f)
{
	ASSERT( fco);
	ASSERT( f);
	CComPtr<IMgaRegNode> rn;
	COMTHROW( Sheet::m_BON_Project_Root_Folder->get_RegistryNode( Util::Copy( AspectRep::getMyPrefix( fco, f)), &rn));
	return rn;
}


void AspectRep::addFCO( FCO* fco) 
{
	m_fcoInitialList.push_back( fco); 
}


void AspectRep::addRRole( RoleRep & role)
{
	m_roleInitialList.push_back( role);
}


bool AspectRep::findFinalFCO( const FCO * fco_ptr) const
{
	return ( m_fcoFinalList.end() != 
		std::find(m_fcoFinalList.begin(), m_fcoFinalList.end(), fco_ptr));
}


bool AspectRep::findFinalRole( const RoleRep& a_role) const
{
	std::vector<RoleRep>::const_iterator it = m_roleFinalList.begin();
	bool found = false;
	while ( it != m_roleFinalList.end() && !found)
	{
		if ( a_role.getFCOPtr() == it->getFCOPtr() &&
			a_role.getModelRepPtr() == it->getModelRepPtr() &&
			a_role.getOnlyRoleName() == it->getOnlyRoleName())
		{
			found = true;
		}
		++it;
	}
	return found;
}


void AspectRep::extendAspectWithDescendants()
{
	// 1st scenario
	// expand aspect membership ( if FCOA is selected to appear in AspA)
	// M1<>---------FCOA -set_member----AspA
	//               |
	//              /^\
	//          FCOB   FCOC
	//
	// if FCOA is member of AspA aspect, then FCOB and FCOC is also a member of AspA
	//  
	//
	// 2nd scenario
	// in case when only a role (of FCOA in a model) is specified as part of an aspect 
	// that role should be extended for FCOB and FCOC as well and for the model
	// descendants inherited from the model. I.e.
	//
	// AspA-----<>M1<>-------FCOA
	//            |
	//           /^\
	//         M2   M3
	//           
	//
	// if the role between M1--FCOA is specified as an aspect member then M2,M3 in AspA should show
	// FCOA and its descendants

	std::vector<FCO*>::iterator init_it = m_fcoInitialList.begin();
	for( ; init_it != m_fcoInitialList.end(); ++init_it)
	{
		FCO* fco_ptr = *init_it;
		std::string fco_nm = fco_ptr->getName();
		std::vector<FCO*> children;
		fco_ptr->getIntDescendants( children);
		children.push_back( fco_ptr);

		for( unsigned int i = 0; i < children.size(); ++i)
			if ( m_fcoFinalList.end() == // not found
				std::find( m_fcoFinalList.begin(), m_fcoFinalList.end(), children[i])) 
				m_fcoFinalList.push_back( children[i]);
	}

	// a task similar to ModelRep::inherit needs to be done
	std::vector< RoleRep>::iterator r_init_it = m_roleInitialList.begin();
	for( ; r_init_it != m_roleInitialList.end(); ++r_init_it)
	{
		FCO* fco_ptr = r_init_it->getFCOPtr();
		std::vector<FCO*> children;
		fco_ptr->getIntDescendants( children);
		children.push_back( fco_ptr);

		ModelRep* model_ptr = r_init_it->getModelRepPtr();
		std::vector<FCO*> model_descendants;
		model_ptr->getImpDescendants( model_descendants);
		model_descendants.push_back( model_ptr);

		for( unsigned int i = 0; i < children.size(); ++i)
		{
			for( unsigned int j = 0; j < model_descendants.size(); ++j)
			{
				ModelRep * model_desc = dynamic_cast<ModelRep *>(model_descendants[j]);
				if (!model_desc) global_vars.err << MSG_ERROR << "Internal error: model descendant badly casted to model\n";

				RoleRep r(
					r_init_it->getOnlyRoleName(),
					children[i],
					model_desc,
					r_init_it->isPort(),
					r_init_it->getCardinality(),
					j + 1 == model_descendants.size(),//r_init_it->isInheritedRole(),
					r_init_it->isLongForm()
					);

				if ( m_roleFinalList.end() == // not found
					std::find( m_roleFinalList.begin(), m_roleFinalList.end(), r)) 
					m_roleFinalList.push_back( r);
			}
		}
	}
}


void AspectRep::sortPartMap()
{
	PartCompare partCompare;
	ModelPartsMap_Iterator it = m_partsMap.begin();
	for( ; it != m_partsMap.end(); ++it)
	{
		PartRepSeries &p = it->second;
		std::sort( p.begin(), p.end(), partCompare);
	}
}


void AspectRep::addPart2Map( ModelRep * mod_ptr, const PartRep & part)
{
	PartRepSeries & series = m_partsMap[mod_ptr];
	if ( series.end() == // not found
		std::find( series.begin(), series.end(), part))
		series.push_back( part);
	else
		global_vars.err << MSG_ERROR << "Part " << part.getRoleRepPtr()->getSmartRoleName() 
		<< " attempted to insert twice into aspect " << m_ptr << "\n";
}


const AspectRep::PartRepSeries& AspectRep::getPartSeries( ModelRep* mod_ptr)
{
	return m_partsMap[ mod_ptr];
}


bool AspectRep::lessThan( const AspectRep& rep) const
{
	if ( m_priority) // non-zero value means the order was overwritten by the user
		return m_priority < rep.m_priority;

	unsigned int x, y;
	unsigned int rep_x, rep_y;
	getXY( &x, &y);
	rep.getXY( &rep_x, &rep_y);
	return ( y < rep_y || (y == rep_y && x < rep_x ));
}


void AspectRep::getXY( unsigned int * x, unsigned int * y) const
{
	if( m_ptr != CComPtr<IMgaFCO>(0))
	{
		std::string val = Util::getReg( m_ptr, "PartRegs/Visualization/Position");
		int v = sscanf( val.c_str(), "%d, %d", x, y);
		ASSERT( v == 2);
	}
	else // created aspect
	{
		*x = *y = 0;
	}
}


void AspectRep::setPriority( int prior)
{
	ASSERT( prior > 0);
	m_priority = prior;
}

int AspectRep::getPriority() const
{
	return m_priority;
}


bool AspectRep::isDummy() const
{
	return m_ptr == CComPtr<IMgaFCO>(0) && m_respPointer == CComPtr<IMgaFCO>(0);
}
