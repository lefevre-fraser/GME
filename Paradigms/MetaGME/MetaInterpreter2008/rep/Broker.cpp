#include "stdafx.h"

#include "logger.h"
#include "Broker.h"
#include "AspectRep.h"
#include "map"

/* static vars to be initialized */
int	Broker::m_constraintId = 1;
const int Broker::INVALID_METAREF = -1;
const int Broker::INITIAL_METAREF = 1001; // the next available metaref
const std::string Broker::ROOTFOLDER_METAREF_STR = "1000"; // used by the "RootFolder"
int	Broker::m_metaRefId = INITIAL_METAREF;
int Broker::m_firstFree = INITIAL_METAREF;
std::list<Broker::MetaRefNode> Broker::m_metaRefDB;


/*This method resets all static variables of Broker. Called by the Dumper::~Dumper*/
void Broker::reset()
{
	m_metaRefDB.clear();
	m_firstFree = INITIAL_METAREF;

	m_constraintId = 0;
	m_metaRefId = INITIAL_METAREF;
}


void Broker::init()
{
	// this is called after the actual project registry has been scanned through
	// and the values can be set based on the information found
	m_constraintId = 1;
	m_metaRefId = (m_firstFree > INITIAL_METAREF)?m_firstFree : INITIAL_METAREF;
	/*char d[10];
	sprintf(d, "%i", m_metaRefId);
	global_vars.err <<  std::string(d) << " used as max metaref\n";*/

	m_metaRefDB.clear(); // after we know the greatest metaref this can be deleted
}


int Broker::getNextConstraintId()
{
	return m_constraintId++;
}


int Broker::getNextMetaRefId()
{
	return m_metaRefId++;
}

std::string Broker::getRegistryTokenName( IMgaObject* obj)
{
	std::string kind = Util::kind( obj);
	std::string name = Util::composePath( obj, true);

	long relid = 0;
	COMTHROW( obj->get_RelID(&relid));
	char t[16];
	sprintf( t, "%x", relid);

	ASSERT( name.length() >= 0);
	std::string tmp = name + '-' + t + '-' + kind;
	//return kind + "s" + name + t;
	return tmp;
}


void Broker::initFromObj( IMgaObject* obj, IMgaFolder* folder, const std::string& kind)
{
	// any modification in the registry policy should be syched with
	// the Any::getMyPrefix() Broker::initFromObj method

	std::string token = Broker::getRegistryTokenName( obj) + "/MetaRef";

	CComPtr<IMgaRegNode> rn;
	COMTHROW( folder->get_RegistryNode( Util::Copy( token), &rn));

	initFromRegistry( obj, folder, rn);
}

// folder is the root folder
void Broker::initFromAspectObj( IMgaObject* obj, const std::string& name, IMgaFolder* folder)
{
	// any modification in the registry policy should be syched with
	// the Broker::initFromObj method
	//std::string token = obj->getID() + ":" + obj->getName() + "/MetaRef";
	std::string token = AspectRep::m_aspectRegistryRoot + '/' + AspectRep::m_aspectMetaRefsRoot + '/' + name + "/MetaRef";

	CComPtr<IMgaRegNode> rn;
	COMTHROW( folder->get_RegistryNode( Util::Copy( token), &rn));

	initFromRegistry( obj, folder, rn);
}

void Broker::initFromRegistry(  IMgaObject* obj, IMgaFolder* folder, IMgaRegNode* reg_node)
{
	long status = 0; 
	COMTHROW( reg_node->get_Status( &status));

	if ( status == 0) // 0: here, -1: in meta, >=1: inherited")]
	{
		CComBSTR val;
		COMTHROW( reg_node->get_Value( &val));

		std::string sval = Util::Copy( val);
		int k = 0;
		if( !sval.empty())
		{
			int sc = sscanf( sval.c_str(), "%d", &k);
			ASSERT( sc == 1);
		}
		
		CComBSTR path;
		COMTHROW( reg_node->get_Path( &path));

		MetaRefNode node( obj, folder, Util::Copy( path), k);
		m_metaRefDB.push_back( node);
		m_firstFree = max( m_firstFree, node.metaref + 1);
	}

	// subnodes here
	CComPtr<IMgaRegNodes> children;
	COMTHROW( reg_node->get_SubNodes( VARIANT_TRUE, &children));

	long c = 0;
	if( children) COMTHROW( children->get_Count( &c));

	// for all subnodes
	for( long i = 1; i <= c; ++i)
	{
		CComPtr<IMgaRegNode> item;
		COMTHROW( children->get_Item( i, &item));

		initFromRegistry( obj, folder, item);
	}
}


void Broker::checkDuplicates()
{
	// map of metaref_int, and metaRefDB::iterator
	// since the list allows removing elements without invalidating iterators
	std::map< int, MetaRefDB_Iterator > check_map;

	MetaRefDB_Iterator it = m_metaRefDB.begin();
	for( ; it != m_metaRefDB.end(); ++it)
	{
		MetaRefNode node = *it;

		std::map< int, MetaRefDB_Iterator >::iterator map_it = check_map.end();
		map_it = check_map.find( node.metaref); 

		if ( map_it != check_map.end()) // same metaref found in the check_map
		{
			MetaRefDB_Iterator jt = map_it->second;
			MetaRefNode otherNode = *jt;
			int t_1 = otherNode.metaref;
			bool flag = false;

			CComBSTR b_id1, b_id2, b_nm;
			COMTHROW( node.obj->get_ID( &b_id1));
			COMTHROW( otherNode.obj->get_ID( &b_id2));
			std::string m1 = Util::Copy( b_id1);
			std::string m2 = Util::Copy( b_id2);
			//bool similar = (node.obj == otherNode.obj);//t
			COMTHROW( node.obj->get_Name( &b_nm));
			std::string p = Util::Copy( b_nm);
			if ( m1 < m2)
			{
				m_metaRefDB.erase( jt);
				check_map[ node.metaref] = it;
				flag = true;
			}
			else
			{
				it = m_metaRefDB.erase(it); // "it" will point to the next element
				--it; // decrement in order to stay consistent within the for cycle
				flag = false;
			}
			std::string token = (flag ? otherNode : node).path.substr(1);
			try {
				//(flag ? otherNode : node).obj->getRegistry()->getDescendantByPath( dpath.substr(1))->clear(); // reset the respective node
				if ( flag)
				{
					CComPtr<IMgaRegNode> rn;
					COMTHROW( otherNode.folder->get_RegistryNode( Util::Copy( token), &rn));
					if( rn) COMTHROW( rn->Clear()); //reset
				}
				else
				{
					CComPtr<IMgaRegNode> rn;
					COMTHROW( node.folder->get_RegistryNode( Util::Copy( token), &rn));
					if( rn) COMTHROW( rn->Clear()); //reset
				}
#ifdef _DEBUG
				CComBSTR btnodnm, bonodnm;
				COMTHROW( node.obj->get_Name( &btnodnm));
				COMTHROW( otherNode.obj->get_Name( &bonodnm));
				std::string fmtstr = std::string("Duplicate metaref found. Class ") + (flag ? Util::Copy( bonodnm) : Util::Copy( btnodnm)) +
					" subnode: " + std::string((flag ? otherNode : node).path.empty() ? "n/a" : (flag ? otherNode : node).path + " has been reset to Undefined value");
				std::string n1str = "Name" + Util::Copy( btnodnm) + " path: " + node.path;
				std::string n2str = "Name" + Util::Copy( bonodnm) + " path: " + otherNode.path;
				//if (t_1) global_vars.err << fmtstr << "\n" << n1str << "\n" << n2str << "\n";
#endif
			}
			catch(...) {
				// in case of library fco-s the operation above is causing an assertion/exception
			}
		}
		else 
		{
			check_map[node.metaref] = it;
		}
	}
}

