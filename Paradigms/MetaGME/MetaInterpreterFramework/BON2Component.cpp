//###############################################################################################################################################
//
//	Meta and Builder Object Network V2.0 for GME
//	BON2Component.cpp
//
//###############################################################################################################################################

/*
	Copyright (c) Vanderbilt University, 2000-2004
	ALL RIGHTS RESERVED

	Vanderbilt University disclaims all warranties with regard to this
	software, including all implied warranties of merchantability
	and fitness.  In no event shall Vanderbilt University be liable for
	any special, indirect or consequential damages or any damages
	whatsoever resulting from loss of use, data or profits, whether
	in an action of contract, negligence or other tortious action,
	arising out of or in connection with the use or performance of
	this software.
*/

#include "BON2Component.h"

#include "logger.h"

#include "string"

#include "Globals.h"
extern Globals global_vars; // has to be declared in other source file

#define show_to_be_removed 0
#define show_entities	1
#define show_relations 1

namespace BON
{

//###############################################################################################################################################
//
// 	C L A S S : BON::Component
//
//###############################################################################################################################################

Component::Component()
	: m_bIsInteractive( false )
{
}

Component::~Component()
{
	/*finalize( m_project );
	m_project = NULL;*/
	if ( m_project ) {
		m_project->finalizeObjects();
		finalize( m_project );
		m_project = NULL;
	}
}

// ====================================================
// This method is called after all the generic initialization is done
// This should be empty unless application-specific initialization is needed

void Component::initialize( Project& project )
{
	// ======================
	// Insert application specific code here
}

// ====================================================
// This method is called before the whole BON2 project released and disposed
// This should be empty unless application-specific finalization is needed

void Component::finalize( Project& project )
{
	// ======================
	// Insert application specific code here
		m_entities.clear();
		m_relations.clear();
		m_toBeDeletedEntities.clear();
		m_realObj.clear();

		if ( m_sheet != 0)  
		{ 
			TO( "The merged paradigm sheet still exists"); 
			delete m_sheet; 
			m_sheet = 0; 
		}
}


void Component::scanSubModels( const Model& model)
{
	std::set<Model> models = model->getChildModels();
	std::set<Model>::iterator i = models.begin();
	for( ; i != models.end(); ++i)
		scanSubModels( *i);
}


void Component::scanModels( const Model& model, const Folder& parent)
{
  scanSubModels(model);
  entityBuilder(model, parent);
}


void Component::scanProject( Project& project)
{
	try
	{
		std::set<Folder> folders = project->getRootFolder()->getChildFolders(); // scan folders
		folders.insert( project->getRootFolder()); // including root folder
		std::set<Folder>::iterator folder_it = folders.begin();
		for( ; folder_it != folders.end(); ++folder_it)
		{
			std::set<Model> objs = (*folder_it)->getChildModels();
			std::set<Model>::iterator i = objs.begin();
			for( ; i != objs.end(); ++i)
			{
				scanModels( *i, *folder_it); // scan all root models
			}
			//(*folder_it)->getRegistry()->setValueByPath("/a/b","123");
			//(*folder_it)->getRegistry()->getChild("a")->setValueByPath("/c","4321");
			//TO((*folder_it)->getRegistry()->getDescendantByPath("a/b")->getValue());
			//TO("A path: " + (*folder_it)->getRegistry()->getDescendantByPath("a/b")->getPath());// a path = /a/b
			//(*folder_it)->getRegistry()->getDescendantByPath("a/b")->clear();
			//TO((*folder_it)->getRegistry()->getDescendantByPath("a/b")->getValue());
			//TO( (*folder_it)->getRegistry()->getChild("a")->getValueByPath("/c"));
		}
	}
	catch(...)
	{
		global_vars.err << "Error: exception thrown during project scanning.\n";
	}
}


void Component::initMembers( Project& project)
{
	m_projectName = project->getName();
	m_entities.clear();
	m_toBeDeletedEntities.clear();
	m_relations.clear();
	m_realObj.clear();
	
	m_sheet = 0;
}


void Component::entityBuilder( const Model& model, const Folder& parent)
{
	// handling sets
	std::set<Set> aspects = model->getChildSets();
	std::set<Set>::iterator aspect = aspects.begin();
	for( ; aspect != aspects.end(); ++aspect)
	{
		Entity new_elem( parent, *aspect);
		m_entities.push_back( new_elem);

		std::set<FCO> aspect_elements = (*aspect)->getMembers();
		std::set<FCO>::iterator asp_elem = aspect_elements.begin();
		for( ; asp_elem != aspect_elements.end(); ++asp_elem)
		{
			// an aspect member may be of type atom (any kind) or reference type (proxy) or
			// connection (like containment = role)
			// it cannot be of type set (aspect), or type model

			//TO( std::string("Aspect member operand\nOp1: ") + (*aspect)->getName() + "\nOp2: " + (*asp_elem)->getName());
			if ((*asp_elem)->getObjectMeta().type() == MON::OT_Atom ||
				(*asp_elem)->getObjectMeta().type() == MON::OT_Reference) 
			{ // if an atom or reference is to be an aspect member
				
				Relation rela( Relation::ASPECT_MEMBER_OP, *aspect, *asp_elem);

				if ( m_relations.end() == std::find( m_relations.begin(), m_relations.end(), rela))
					m_relations.push_back( rela);
				else
					global_vars.err << "Internal warning: Relation ASPECT_MEMBER found already in relations\n";
			}
			else if ((*asp_elem)->getObjectMeta().type() == MON::OT_Connection &&
				(*asp_elem)->getObjectMeta().name() == Relation::containment_str ) 
			{ // if a role is intended to be an aspect member
				Object src_fco, dst_model;
				Connection containment( *asp_elem);
				if (containment)
				{
					src_fco = FCO( containment->getSrc());
					dst_model = FCO( containment->getDst());
				}
				
				Relation rela( Relation::ASPECT_MEMBER_OP, *aspect, src_fco, *asp_elem, dst_model); // special ASPECT_MEMBER_OP

				if ( m_relations.end() == std::find( m_relations.begin(), m_relations.end(), rela))
					m_relations.push_back( rela);
				else
					global_vars.err << "Internal warning: Relation ASPECT_MEMBER found already in relations\n";
			}
			else
			{
				TO( std::string("Error: weird aspect member operation\nOp1: ") + (*aspect)->getName() + "\nOp2: " + (*asp_elem)->getName());
			}
		}
	}

	// handling connections
	std::set<Connection> conns = model->getChildConnections();
	std::set<Connection>::iterator conn_it = conns.begin();
	for( ; conn_it != conns.end(); ++conn_it)
	{
			#if(0)
			**
			* in case of reference:
			* op1: FCO ( referred )
			* op2: Reference
			* 
			* in other cases: 
			* op1: container
			* op2: element
			* op3: association class (in case of connector)
			*      connection line class (in case of containment and foldercontainment)
			* op4: connection line class (in case of connector: source2connector)
			* op5: connection line class (in case of connector: connector2destination)
			*
			#endif

		std::string conn_kind = (*conn_it)->getObjectMeta().name();
		if ( conn_kind == "Containment" ||
			conn_kind == "FolderContainment" ||
			conn_kind == "SetMembership" ||
			conn_kind == "ReferTo" ||
			conn_kind == "HasAspect" ||
			conn_kind == "HasConstraint" ||
			conn_kind == "HasAttribute")
		{
			Object src = FCO((*conn_it)->getSrc());
			Object dst = FCO((*conn_it)->getDst());

			Relation rela( Relation::CONTAINMENT_OP, dst, src); // create a relation object

			std::string relation_name =  (*conn_it)->getObjectMeta().name();
			if ( relation_name == Relation::containment_str)
			{
				rela.setOperation( Relation::CONTAINMENT_OP); 
				rela.setOp3( *conn_it);
			}
			else if ( relation_name == Relation::folder_containment_str)
			{
				rela.setOperation( Relation::FOLDER_CONTAINMENT_OP); 
				rela.setOp3( *conn_it);
			}
			else if ( relation_name == Relation::set_membership_str)
				rela.setOperation( Relation::SET_MEMBER_OP);
			else if ( relation_name == Relation::refer_to_str)
				rela.setOperation( Relation::REFER_TO_OP);
			else if ( relation_name == Relation::has_aspect_str)
				rela.setOperation( Relation::HAS_ASPECT_OP);
			else if ( relation_name == Relation::has_constraint_str)
				rela.setOperation( Relation::HAS_CONSTRAINT_OP);
			else if ( relation_name == Relation::has_attribute_str)
				rela.setOperation( Relation::HAS_ATTRIBUTE_OP);
			else
				global_vars.err << "ERROR in entity Builder: unhandled entity.\n";

			m_relations.push_back(rela);
		}
	}

	// handling proxies
	std::set<Reference> refs = model->getChildReferences();
	std::set<Reference>::iterator ref_it = refs.begin();
	for( ; ref_it != refs.end(); ++ref_it)
	{
		Entity new_elem( parent, *ref_it);
		m_entities.push_back( new_elem);

		try
		{
			FCO referred = (*ref_it)->getReferred();
			this->m_realObj[ *ref_it] = referred;
			std::string m1, m2;
			m1 = referred->getName();
 			m2 = (*ref_it)->getName();
		}
		catch( ... )
		{
			global_vars.err << "ERROR: Handling exeception thrown by Null proxy " << (*ref_it)->getName() << "\n";
		}
 	}
	
	// handling atoms
	std::set<Atom> atoms = model->getChildAtoms();
	std::set<Atom>::iterator atom_it = atoms.begin();
	for( ; atom_it != atoms.end(); ++atom_it)
	{
		if ( (*atom_it)->getStereotype() != OT_Set) // sets handled already
		{
			Entity new_elem( parent, *atom_it);
			
			std::string kind_name = (*atom_it)->getObjectMeta().name();
			if ( kind_name != Relation::connector_str.c_str() && 
				kind_name != Relation::inheritance_str.c_str() && 
				kind_name != Relation::int_inheritance_str.c_str() && 
				kind_name != Relation::imp_inheritance_str.c_str() && 
				kind_name != Relation::equivalence_str.c_str() &&
				kind_name != Relation::same_folder_str.c_str() && 
				kind_name != Relation::same_aspect_str.c_str())
			{
				m_entities.push_back( new_elem); // deserves the Entity status
			}
			else if ( kind_name == Relation::connector_str)
			{
				Connection in_connection_line;
				Connection out_connection_line;
				
				ConnectionEnd obj1, obj2, obja;

				std::set<Connection> con_list_ptr_i = (*atom_it)->getInConnLinks( Relation::connector_src.c_str()); // list of srcs
				std::set<Connection> con_list_ptr_o = (*atom_it)->getOutConnLinks( Relation::connector_dst.c_str());// list of dsts

				if ( !con_list_ptr_i.empty())
				{
					in_connection_line = * con_list_ptr_i.begin();
					obj1 = in_connection_line->getSrc();
					//std::string o01 = BON::FCO((*con_list_ptr_i.begin())->getSrc())->getName();
					std::string o1 = BON::FCO(obj1)->getName();
				}
				if ( !con_list_ptr_o.empty())
				{
					out_connection_line = * con_list_ptr_o.begin();
					obj2 = out_connection_line->getDst();

					//std::string o2 = BON::FCO(*obj2)->getName();
				}
				if ( !in_connection_line || !out_connection_line)
					global_vars.err << "ERROR during entity builder - handling connector \"" << (*atom_it)->getName() << "\"\n";

				
				
				// the AssociationClass connections may be <in> OR <out>
				// first check for outgoing AssociationClass connections 
				std::multiset<ConnectionEnd> a_out_list = (*atom_it)->getOutConnEnds( Relation::connector_descr);
				std::multiset<ConnectionEnd> a_in_list = (*atom_it)->getInConnEnds( Relation::connector_descr);

				if ( !a_out_list.empty())
				{
					obja = * a_out_list.begin();
					//TO(g_curr_elem + s + " [Out, C2A] "+ obja->getName() +" | " + obja->getObjectMeta().name());
				}
				else if ( !a_in_list.empty()) // if not found outgoings check for incoming AssociationClass connections 
				{
					obja = * a_in_list.begin();
					//TO(g_curr_elem + s + " [Out, C2A] "+ obja->getName() +" | " + obja->getObjectMeta().name());
				}
				else 
					global_vars.err << "ERROR: connector \"" << (*atom_it)->getName() << "\" has no Associated Class!\n";


				// insert into the relations table an association with 
				// src: obj1, dest: obj2, association class: obja, in line, and out_line
				if ( !obj1 || !obj2 || !obja || !in_connection_line || !out_connection_line)
					global_vars.err << "ERROR: Association can not be inserted into Relations\n";
				else
				{
					Relation rela( 
						Relation::ASSOCIATION_OP, 
						FCO( obj1),
						FCO( obj2),
						FCO( obja),
						in_connection_line,
						out_connection_line);
					m_relations.push_back(rela);
				}
			}
			else if ( kind_name == Relation::inheritance_str)
			{
				ConnectionEnd obj1, obj2;
				std::multiset<ConnectionEnd> in_list = (*atom_it)->getInConnEnds( Relation::inheritance_base);
				std::multiset<ConnectionEnd> out_list = (*atom_it)->getOutConnEnds( Relation::inheritance_derived);
				std::multiset<ConnectionEnd>::iterator in_it = in_list.begin();
				std::multiset<ConnectionEnd>::iterator out_it = out_list.begin();

				int how_many_bases = 0;
				for( ; in_it != in_list.end(); ++in_it ) // if outer cycle performs more than once should be an error
				{
					obj1 = * in_it;
					++how_many_bases;
					if ( how_many_bases > 1) global_vars.err << "Warning: Too many base classes\n";
					//TO(g_curr_elem + s + " [IN, Base] "+ obj1->getName() +" | " + obj1->getObjectMeta().name());
					for( ; out_it != out_list.end(); ++out_it)
					{
						//std::string s(Relation::inheritance_derived.c_str());
						//TO(g_curr_elem + s + " [Out, Derived] "+ obj2->getName() +" | " + obj2->getObjectMeta().name());
						obj2 = * out_it;

						Relation rela( Relation::INHERITANCE_OP, FCO( obj1), FCO( obj2));
						m_relations.push_back(rela);
					}
				}
			} /* end if*/
			else if ( kind_name == Relation::imp_inheritance_str)
			{
				ConnectionEnd obj1, obj2;
				std::multiset<ConnectionEnd> in_list = (*atom_it)->getInConnEnds( Relation::imp_inheritance_base);
				std::multiset<ConnectionEnd> out_list = (*atom_it)->getOutConnEnds( Relation::imp_inheritance_derived);
				std::multiset<ConnectionEnd>::iterator in_it = in_list.begin();
				std::multiset<ConnectionEnd>::iterator out_it = out_list.begin();

				int how_many_bases = 0;
				for( ; in_it != in_list.end(); ++in_it ) // if outer cycle performs more than once should be an error
				{
					obj1 = * in_it;
					++how_many_bases;
					if ( how_many_bases > 1) global_vars.err << "Warning: Too many base classes\n";
					//TO(g_curr_elem + s + " [IN, Base] "+ obj1->getName() +" | " + obj1->getObjectMeta().name());
					for( ; out_it != out_list.end(); ++out_it)
					{
						//std::string s(Relation::inheritance_derived.c_str());
						//TO(g_curr_elem + s + " [Out, Derived] "+ obj2->getName() +" | " + obj2->getObjectMeta().name());
						obj2 = * out_it;

						Relation rela( Relation::IMP_INHERITANCE_OP, FCO( obj1), FCO( obj2));
						m_relations.push_back(rela);
					}
				}
			} /* end if*/
			else if ( kind_name == Relation::int_inheritance_str)
			{
				ConnectionEnd obj1, obj2;
				std::multiset<ConnectionEnd> in_list = (*atom_it)->getInConnEnds( Relation::int_inheritance_base);
				std::multiset<ConnectionEnd> out_list = (*atom_it)->getOutConnEnds( Relation::int_inheritance_derived);
				std::multiset<ConnectionEnd>::iterator in_it = in_list.begin();
				std::multiset<ConnectionEnd>::iterator out_it = out_list.begin();

				int how_many_bases = 0;
				for( ; in_it != in_list.end(); ++in_it ) // if outer cycle performs more than once should be an error
				{
					obj1 = * in_it;
					++how_many_bases;
					if ( how_many_bases > 1) global_vars.err << "Warning: Too many base classes\n";
					//TO(g_curr_elem + s + " [IN, Base] "+ obj1->getName() +" | " + obj1->getObjectMeta().name());
					for( ; out_it != out_list.end(); ++out_it)
					{
						//std::string s(Relation::inheritance_derived.c_str());
						//TO(g_curr_elem + s + " [Out, Derived] "+ obj2->getName() +" | " + obj2->getObjectMeta().name());
						obj2 = * out_it;

						Relation rela( Relation::INT_INHERITANCE_OP, FCO( obj1), FCO( obj2));
						m_relations.push_back(rela);
					}
				}
			} /* end if*/
			else if ( kind_name == Relation::equivalence_str)
			{
				ConnectionEnd obj1, obj2;
				std::multiset<ConnectionEnd> in_list = (*atom_it)->getInConnEnds( Relation::equivalence_right);
				std::multiset<ConnectionEnd> out_list = (*atom_it)->getOutConnEnds( Relation::equivalence_left);
				std::multiset<ConnectionEnd>::iterator in_it = in_list.begin();
				std::multiset<ConnectionEnd>::iterator out_it = out_list.begin();

				int how_many_bases = 0;
				for( ; in_it != in_list.end(); ++in_it ) // if outer cycle performs more than once should be an error
				{
					obj1 = * in_it;
					++how_many_bases;
					if ( how_many_bases > 1) global_vars.err << "Warning: Too many base classes\n";
					//TO(g_curr_elem + s + " [IN, Base] "+ obj1->getName() +" | " + obj1->getObjectMeta().name());
					for( ; out_it != out_list.end(); ++out_it)
					{
						//std::string s(Relation::inheritance_derived.c_str());
						//TO(g_curr_elem + s + " [Out, Derived] "+ obj2->getName() +" | " + obj2->getObjectMeta().name());
						obj2 = * out_it;

						Relation rela( Relation::EQUIVALENCE_OP, FCO( obj1), FCO( obj2), *atom_it);
						m_relations.push_back(rela);
					}
				}
			} /* end if*/
			else if ( kind_name == Relation::same_aspect_str)
			{
				ConnectionEnd obj1, obj2;
				std::multiset<ConnectionEnd> in_list = (*atom_it)->getInConnEnds( Relation::same_aspect_right);
				std::multiset<ConnectionEnd> out_list = (*atom_it)->getOutConnEnds( Relation::same_aspect_left);
				std::multiset<ConnectionEnd>::iterator in_it = in_list.begin();
				std::multiset<ConnectionEnd>::iterator out_it = out_list.begin();

				for( ; in_it != in_list.end(); ++in_it ) // if outer cycle performs more than once should be an error
				{
					obj1 = * in_it;
					//TO(g_curr_elem + s + " [IN, Base] "+ obj1->getName() +" | " + obj1->getObjectMeta().name());
					for( ; out_it != out_list.end(); ++out_it)
					{
						//std::string s(Relation::inheritance_derived.c_str());
						//TO(g_curr_elem + s + " [Out, Derived] "+ obj2->getName() +" | " + obj2->getObjectMeta().name());
						obj2 = * out_it;

						Relation rela( Relation::SAME_ASPECT_OP, FCO( obj1), FCO( obj2), *atom_it);
						m_relations.push_back(rela);
					}
				}
			} /* end if*/
			else if ( kind_name == Relation::same_folder_str)
			{
				ConnectionEnd obj1, obj2;
				std::multiset<ConnectionEnd> in_list = (*atom_it)->getInConnEnds( Relation::same_folder_right);
				std::multiset<ConnectionEnd> out_list = (*atom_it)->getOutConnEnds( Relation::same_folder_left);
				std::multiset<ConnectionEnd>::iterator in_it = in_list.begin();
				std::multiset<ConnectionEnd>::iterator out_it = out_list.begin();

				for( ; in_it != in_list.end(); ++in_it ) // if outer cycle performs more than once should be an error
				{
					obj1 = * in_it;
					//TO(g_curr_elem + s + " [IN, Base] "+ obj1->getName() +" | " + obj1->getObjectMeta().name());
					for( ; out_it != out_list.end(); ++out_it)
					{
						//std::string s(Relation::inheritance_derived.c_str());
						//TO(g_curr_elem + s + " [Out, Derived] "+ obj2->getName() +" | " + obj2->getObjectMeta().name());
						obj2 = * out_it;

						Relation rela( Relation::SAME_FOLDER_OP, FCO( obj1), FCO( obj2), *atom_it);
						m_relations.push_back(rela);
					}
				}
			} /* end if*/
		}
	}
}


/*************************************************************************
This method is responsible for selecting in case of SameAspect or SameFolder operators the 
box whose name will be used (this will override the other name)
Rules:
	The name of the real object is used if one operand is proxy
	The name of the SameAspect operator is used if both or none operands are proxy
*/
void Component::selectFromSameAspectsFolders()
{
	Relation_Iterator rel_it = m_relations.begin();
	for( ; rel_it != m_relations.end(); ++rel_it)
	{
		if ( rel_it->getOperation() == Relation::SAME_ASPECT_OP || 
			rel_it->getOperation() == Relation::SAME_FOLDER_OP || 
			rel_it->getOperation() == Relation::EQUIVALENCE_OP)
		{
			std::string n1 = rel_it->getOp1()->getName();
			std::string n2 = rel_it->getOp2()->getName();
			if ( n1 == n2 ) // the names are the same no selection needed
			{ }
			else
			{
				bool is_proxy_first = m_realObj[ rel_it->getOp1()] != BON::Object();
				bool is_proxy_second = m_realObj[ rel_it->getOp2()] != BON::Object();
				
				ObjPointer selected_ptr = 0;
				if (is_proxy_first == is_proxy_second) // both or neither is proxy
					selected_ptr = rel_it->getOp3(); //set the sameaspect operator as resp pointer
				else if (is_proxy_first) // the second is not proxy so set is as the responsible object
					selected_ptr = rel_it->getOp2();
				else // the first is not a proxy
					selected_ptr = rel_it->getOp1();

				// the selected_ptr never points to a proxy -> later on it won't be replaced
				// with another object by Component::OperandSearchAndReplace

				// set back into the aspect/folder entity the responsible pointer
				ObjPointer to_find = is_proxy_first?m_realObj[rel_it->getOp1()]:rel_it->getOp1();

				Entity_Iterator it( m_entities.begin());
				while( it != m_entities.end()) 
				{ 
					if ( to_find == it->getPointer()) 
					{
						it->setRespPointer( selected_ptr);
					}
					++it; 
				}

				to_find = is_proxy_second?m_realObj[rel_it->getOp2()]:rel_it->getOp2();
				it = m_entities.begin();
				while( it != m_entities.end()) 
				{ 
					if ( to_find == it->getPointer()) 
					{
						it->setRespPointer( selected_ptr);
					}
					++it; 
				}
			}
		}
	}
}


Entity Component::entitySearch( ObjPointer p_ptr)
{
	Entity_Iterator it( m_entities.begin());
	while ( it != m_entities.end() && p_ptr != it->getPointer())
		++it;
	
	if ( it == m_entities.end())
		return Entity(BON::Folder(), BON::Object());
	else 
		return *it;
}


/*
Searches the relation container and replaces the proxy pointers with their real object peer
and removes the proxy from the entities container

Based on the assumption that a proxy cannot refer to another proxy
*/
void Component::proxyFinder()
{
	RealMap_Iterator real_map_it = this->m_realObj.begin();
	for(; real_map_it != m_realObj.end(); ++real_map_it)
	{
		ObjPointer proxy_for_sure = real_map_it->first;
		ObjPointer real_for_sure = real_map_it->second;

		std::string n1, n2;
		if ( proxy_for_sure != BON::Object())
			n1 = proxy_for_sure->getName();
		if ( real_for_sure != BON::Object())
			n2= real_for_sure->getName();
		
		if ( proxy_for_sure != BON::Object() && real_for_sure != BON::Object())
		{
			Entity proxy = entitySearch( proxy_for_sure);
			if ( proxy == Entity( BON::Folder(), BON::Object()))
				global_vars.err << "ERROR: Entity not found during proxyFinder: " << proxy_for_sure->getName() << "\n";
			else
			{
				operandSearchAndReplace( proxy_for_sure, real_for_sure);
				m_toBeDeletedEntities.push_back( proxy);
			}
		}
	}
}


void Component::equivalenceFinder()
{
	Relation_Iterator rel_it = m_relations.begin();
	while ( rel_it != m_relations.end())
	{
		if ( rel_it->getOperation() == Relation::EQUIVALENCE_OP ||
			rel_it->getOperation() == Relation::SAME_FOLDER_OP ||
			rel_it->getOperation() == Relation::SAME_ASPECT_OP )
		{
			Entity operand2 = entitySearch( rel_it->getOp2());
			if ( operand2 == Entity( BON::Folder(), BON::Object())) 
				global_vars.err << "ERROR: Entity not found during EquivalenceFinder: " << rel_it->getOperationStr() << "\n";

			// prevent search/replace for obvious cases like: a equiv a
			if ( rel_it->getOp1() != rel_it->getOp2() )
			{ 
				operandSearchAndReplace( rel_it->getOp2(), rel_it->getOp1());
				m_toBeDeletedEntities.push_back( operand2);
			}
			// the relation needs to be deleted either way
			rel_it = m_relations.erase( rel_it); // <- relies on that erase increments rel_it
		}
		else ++rel_it;
	}
}


/*
Searches the releation container and replaces all occurences of find_obj 
with real_obj.
Important: It replaces only the first three pointer operands (since 4th and 5th operands are
connections which cannot be proxies)
*/
void Component::operandSearchAndReplace(ObjPointer find_obj, ObjPointer real_obj)
{
	Relation_Iterator rel_it = m_relations.begin();
	for( ; rel_it != m_relations.end(); ++rel_it)
	{
		if (!rel_it->getOp1()) global_vars.err << "First operand is Null Pointer\n";
		if (!rel_it->getOp2()) global_vars.err << "Second operand is Null Pointer\n";

		ObjPointer obj = BON::Object(); obj = rel_it->getOp1();
		if ( obj == find_obj) 
			rel_it->setOp1(real_obj); 

		obj = BON::Object(); obj = rel_it->getOp2();
		if ( obj == find_obj) 
			rel_it->setOp2(real_obj); 

		// obj at this time may be BON::Object() (in most case it is)
		obj = BON::Object(); obj = rel_it->getOp3();
		if ( obj != BON::Object() && obj == find_obj) 
			rel_it->setOp3(real_obj); 

		// added recently, to be tested well <!>
		obj = BON::Object(); obj = rel_it->getOp4();
		if ( obj != BON::Object() && obj == find_obj) 
			rel_it->setOp4(real_obj); 

		obj = BON::Object(); obj = rel_it->getOp5();
		if ( obj != BON::Object() && obj == find_obj) 
			rel_it->setOp5(real_obj); 
	}
}

void Component::removeProxiesAndEquiv()
{
	Entity_Const_Iterator it = m_toBeDeletedEntities.begin();
	for ( ; it != m_toBeDeletedEntities.end(); ++it)
	{
		Entity_Iterator jt = m_entities.begin();
		while ( jt != m_entities.end() && jt->getPointer() != it->getPointer())
		 ++jt;
		if ( jt != m_entities.end() )
			m_entities.erase(jt);
	}
}


int Component::isProxy( ObjPointer ptr)
{
	if ( ptr == BON::Object()) return 0;
	if (m_realObj[ ptr] != BON::Object()) return 1;
	if (ptr->getObjectMeta().name().find("Proxy") != std::string::npos) return 2;
	return 0;
}


bool Component::checkForProxies()
{
	std::vector< ObjPointer> to_delete;
	bool correct = true;
	Entity_Iterator it(m_entities.begin());
	for( ; it != m_entities.end(); ++it)
	{
		int res;
		if ( res = isProxy( it->getPointer()))
		{
			std::string msg;
			if ( res == 1)
				msg = "Internal error: entity " + it->getPointer()->getName() + " is a proxy.";
			else if ( res == 2)
				msg = "Error: entity " + it->getPointer()->getName() + " is a NULL proxy.";

			global_vars.err << msg << " Disregarding it from the Paradigm sheet.\n";
			correct = false;
			to_delete.push_back( it->getPointer());
		}
	}

	unsigned int c = to_delete.size();
	Relation_Iterator rel_it = m_relations.begin();
	for( ; rel_it != m_relations.end(); ++rel_it)
	{
		if ( isProxy( rel_it->getOp1()))
			to_delete.push_back( rel_it->getOp1());

		if ( isProxy( rel_it->getOp2()))
			to_delete.push_back( rel_it->getOp2());

		if ( isProxy( rel_it->getOp3()))
			to_delete.push_back( rel_it->getOp3());

		if ( isProxy( rel_it->getOp4()))
			to_delete.push_back( rel_it->getOp4());

		if ( isProxy( rel_it->getOp5()))
			to_delete.push_back( rel_it->getOp5());
	}

	if ( c != to_delete.size()) correct = false;

	std::vector< ObjPointer>::iterator ee = to_delete.begin();
	for( ; ee != to_delete.end(); ++ee)
	{
		Entity_Iterator ent_it = m_entities.begin();
		while( ent_it != m_entities.end())
		{
			if (*ee != ent_it->getPointer())
				++ent_it;
			else
				ent_it = m_entities.erase( ent_it);
		}

		Relation_Iterator rel_it = m_relations.begin();
		while( rel_it != m_relations.end())
		{
			if ( rel_it->getOp1() != *ee &&
				rel_it->getOp2() != *ee &&
				rel_it->getOp3() != *ee &&
				rel_it->getOp4() != *ee &&
				rel_it->getOp5() != *ee )
				++rel_it;
			else
				rel_it = m_relations.erase( rel_it);
		}
	}
	return correct;
}


void Component::Show()
{
	std::string msg = "";
#if(show_to_be_removed)

	Entity_Iterator it_1(m_toBeDeletedEntities.begin());
	for( ; it_1 != m_toBeDeletedEntities.end(); ++it_1)
	{
		const CBuilderObject * obj = static_cast<const CBuilderObject *>(it_1->getPointer());
		msg += obj->getName() + " / " + obj->getObjectMeta().name() + "\n";
	}
	TO(msg.c_str());
#endif

	msg = " / / / / / E N T I T I E S \\ \\ \\ \\ \\ \n";

#if(show_entities)

	Entity_Iterator it_2( m_entities.begin());
	for( ; it_2 != m_entities.end(); ++it_2)
	{
		char dst[32];
		sprintf( dst, "%x", it_2->getPointer());
		msg += it_2->getPointer()->getName() + " / " + it_2->getPointer()->getObjectMeta().name() + " Addr: " + dst;

		// if proxy show its real objs
		ObjPointer objreal = m_realObj[it_2->getPointer()];
		if ( objreal != BON::Object())
		{
			msg += " is a proxy to " + objreal->getName() + "/" + objreal->getObjectMeta().name();
		}
		msg += "\n";
	}
	TO(msg.c_str());

#endif

	msg = " * * * * * * R E L A T I O N S * * * * * *\n";

#if(show_relations)


	Relation_Const_Iterator it_3 (m_relations.begin());
	for( ; it_3 != m_relations.end(); ++it_3)
	{
		ObjPointer obj1 = it_3->getOp1();
		ObjPointer obj2 = it_3->getOp2();
		ObjPointer obj3 = it_3->getOp3();
		ObjPointer obj4 = it_3->getOp4();
		ObjPointer obj5 = it_3->getOp5();
		msg += it_3->getOperationStr() + " between ";
		if ( obj1!=BON::Object() && obj2 != BON::Object() )
			msg += obj1->getName() + ":" + obj1->getObjectMeta().name() + " + " + obj2->getName() + ":" + obj2->getObjectMeta().name();
		else TO("Error in relations list\n");

		if ( obj3 != BON::Object() )
			msg += " A:" + obj3->getName() /*+ ":" + obj3->getObjectMeta().name()*/;

		if ( obj4 != BON::Object() )
			msg += " L:" + obj4->getName() /* + ":" + obj4->getObjectMeta().name()*/;
		if ( obj5 != BON::Object() )
			msg += " L:" + obj5->getName() /*+ ":" + obj5->getObjectMeta().name()*/;

		if ( it_3->getOperation() == Relation::HAS_ASPECT_OP || 
			it_3->getOperation() == Relation::ASPECT_MEMBER_OP )
		{
			char dst1[32], dst2[32];
			sprintf( dst1, "%x", obj1);
			sprintf( dst2, "%x", obj2);
			msg += "Addr1: " + std::string( dst1) + " Addr2: " + std::string( dst2);
		}

		msg += "\n";
	}
	TO(msg.c_str());

#endif
}

//void Component::createSheet()
//{
	//
	//TODO : create your own Sheet instance (should be a derived class from the Sheet)
	//       store the pointer in the m_sheet member
	//m_sheet = Dumper::getInstance();
//}	


bool Component::populateSheet( const std::string& name)
{
	m_sheet->setProjName( name);

	bool error = false;

	Entity_Iterator it_1( m_entities.begin());

	FcoRep * new_fco;
	AtomRep * new_atom;
	ModelRep * new_model;
	ConnectionRep * new_conn;
	SetRep * new_set;
	ReferenceRep * new_ref;
	FolderRep * new_folder;
	AspectRep * new_aspect;
	ConstraintRep * new_constraint;
	ConstraintFuncRep * new_constraint_func;
	AttributeRep * new_attribute;

	for( ; it_1 != m_entities.end(); ++it_1 )
	{
		ObjPointer obj = BON::Object();
		obj = it_1->getPointer();

		FCO fco( it_1->getPointer());
		FCO resp( it_1->getRespPointer());
		Folder parent_folder( it_1->getParentFolder());

		if (!obj) global_vars.err << "Populate sheet: tries to create Rep with empty Object.\n";
		else if ( !fco) global_vars.err << "Populate sheet: tries to create Rep with empty FCO.\n";
		else
		{
			try {
				if ( obj->getObjectMeta().name() == "FCO" )
				{
					new_fco = m_sheet->createFcoRep( fco);
					m_sheet->addFcoRep( new_fco);
					if (new_fco) new_fco->setParentFolder( parent_folder); 
				}
				else if ( obj->getObjectMeta().name() == "Atom" )
				{
					new_atom = m_sheet->createAtomRep( fco);
					m_sheet->addAtomRep( new_atom);
					if (new_atom) new_atom->setParentFolder( parent_folder); 
				}
				else if ( obj->getObjectMeta().name() == "Model" )
				{
					new_model = m_sheet->createModelRep( fco);
					m_sheet->addModelRep( new_model);
					if (new_model) new_model->setParentFolder( parent_folder); 
				}
				else if ( obj->getObjectMeta().name() == "Connection" )
				{
					new_conn = m_sheet->createConnectionRep( fco);
					m_sheet->addConnectionRep( new_conn);
					if (new_conn) new_conn->setParentFolder( parent_folder); 
				}
				else if ( obj->getObjectMeta().name() == "Set" )
				{
					new_set = m_sheet->createSetRep( fco);
					m_sheet->addSetRep( new_set);
					if (new_set) new_set->setParentFolder( parent_folder); 
				}
				else if ( obj->getObjectMeta().name() == "Reference" )
				{
					new_ref = m_sheet->createReferenceRep( fco);
					m_sheet->addReferenceRep( new_ref);
					if (new_ref) new_ref->setParentFolder( parent_folder); 
				}
				else if ( obj->getObjectMeta().name() == "Folder" )
				{
					new_folder = m_sheet->createFolderRep( fco, (resp != BON::Object())?resp:fco);
					m_sheet->addFolderRep( new_folder);
					if (new_folder) new_folder->setParentFolder( parent_folder); 
				}
				else if ( obj->getObjectMeta().name() == "Aspect" )
				{
					new_aspect = m_sheet->createAspectRep( fco, (resp != BON::Object())?resp:fco);
					m_sheet->addAspectRep( new_aspect);
					if (new_aspect) new_aspect->setParentFolder( parent_folder); 
				}
				else if ( obj->getObjectMeta().name() == "Constraint" )
				{
					new_constraint = m_sheet->createConstraintRep( fco);
					m_sheet->addConstraintRep( new_constraint);
					if (new_constraint) new_constraint->setParentFolder( parent_folder); 
				}
				else if ( obj->getObjectMeta().name() == "ConstraintFunc" )
				{
					new_constraint_func = m_sheet->createConstraintFuncRep( fco);
					m_sheet->addConstraintFuncRep( new_constraint_func);
					if (new_constraint_func) new_constraint_func->setParentFolder( parent_folder); 
				}
				else if ( obj->getObjectMeta().name() == "BooleanAttribute" )
				{
					new_attribute = m_sheet->createBoolAttributeRep( fco);
					m_sheet->addAttributeRep( new_attribute);
					if (new_attribute) new_attribute->setParentFolder( parent_folder); 
				}
				else if ( obj->getObjectMeta().name() == "EnumAttribute" )
				{
					new_attribute = m_sheet->createEnumAttributeRep( fco);
					m_sheet->addAttributeRep( new_attribute);
					if (new_attribute) new_attribute->setParentFolder( parent_folder); 
				}
				else if ( obj->getObjectMeta().name() == "FieldAttribute" )
				{
					new_attribute = m_sheet->createFieldAttributeRep( fco);
					m_sheet->addAttributeRep( new_attribute);
					if (new_attribute) new_attribute->setParentFolder( parent_folder); 
				}
				else 
				{ 
					global_vars.err << "Not inserted into the sheet: " << obj->getName() << " of kind: " << obj->getObjectMeta().name() << "\n";
					error = true;
				}
			}
			catch( MON::Exception p)
			{
				global_vars.err << p.getKind() << " exception caught during entity creation\n";
				error = true;
			}
			catch(...)
			{
				global_vars.err << "Something went wrong in the populateSheet for Entities\n";
				error = true;
			}
		}
	} // for m_entities

	if (error) 
	{
		global_vars.err << "Internal error during creation of entities. Exiting\n";
		return false;
	}

	Relation_Iterator rel_it = m_relations.begin();
	for( ; rel_it != m_relations.end(); ++rel_it)
	{
		try 
		{
			Relation::OPER_TYPE oper = rel_it->getOperation();
			if ( oper == Relation::INHERITANCE_OP ||
					oper == Relation::INT_INHERITANCE_OP ||
					oper == Relation::IMP_INHERITANCE_OP)
				inheritancesManager( *rel_it);
			else if ( oper == Relation::ASSOCIATION_OP)
				associationClassManager( *rel_it);
			else if ( oper == Relation::REFER_TO_OP)
				refersToManager( *rel_it);
			else if ( oper == Relation::SET_MEMBER_OP)
				setMemberManager( *rel_it);
			else if ( oper == Relation::HAS_ASPECT_OP)
				hasAspectManager( *rel_it);
			else if ( oper == Relation::CONTAINMENT_OP)
				containmentManager( *rel_it);
			else if ( oper == Relation::FOLDER_CONTAINMENT_OP)
				folderContainmentManager( *rel_it);
			else if ( oper == Relation::ASPECT_MEMBER_OP)
				aspectMemberManager( *rel_it);
			else if ( oper == Relation::HAS_CONSTRAINT_OP)
				hasConstraintManager( *rel_it);
			else if ( oper == Relation::HAS_ATTRIBUTE_OP)
				hasAttributeManager( *rel_it);
		}
		catch( MON::Exception p)
		{
			global_vars.err << p.getKind() << " exception caught during relation establishing\n";
		}
		catch(...)
		{
			global_vars.err << "Something went wrong in the populateSheet\n";
		}
	}

	if (error) 
	{
		global_vars.err << "Internal error during the relation establishment. Exiting\n";
		return false;
	}

	//CRUCIAL step: the role names may be short or long form
	if (m_sheet->finalize()) 
		return m_sheet->build();

	return false;
}


void Component::deleteSheet()
{
	if ( m_sheet) delete m_sheet;
	m_sheet = 0;
}


void Component::inheritancesManager( Relation & rel_it)
{
	Relation::OPER_TYPE relation[ ::FCO::NUMBER_OF_INHERITANCES ] = { 
		Relation::INHERITANCE_OP,
		Relation::INT_INHERITANCE_OP,
		Relation::IMP_INHERITANCE_OP 
	};

	::FCO::INHERITANCE_TYPE new_relation[ ::FCO::NUMBER_OF_INHERITANCES ] = { 
			::FCO::REGULAR,
			::FCO::INTERFACE,
			::FCO::IMPLEMENTATION
	};

	int inh_type; // FCO::INHERITANCE_TYPE
	for( inh_type = 0; inh_type != ::FCO::NUMBER_OF_INHERITANCES; ++inh_type )
	{
		if ( rel_it.getOperation() == relation[inh_type] )
		{
			ObjPointer obj1 = rel_it.getOp1();
			ObjPointer obj2 = rel_it.getOp2();

			::FCO* base = m_sheet->findFCO( rel_it.getOp1());
			::FCO* derived = m_sheet->findFCO( rel_it.getOp2());
			if ( base != 0 && derived != 0)
			{
				base->addChild( new_relation[inh_type], derived);
				derived->addParent( new_relation[inh_type], base);
				//TO( "some inh " + obj1->getName() + " <|-- " + obj2->getName());
			}
			else
			{
				if ( base == 0 )
					global_vars.err << "No base peer present in inheritance relation: " << obj1->getName() << " <|---- " << obj2->getName() << "\n";
				if ( derived == 0 )
					global_vars.err << "No derived peer present in inheritance relation: " << obj1->getName() << " <|---- " << obj2->getName() << "\n";
			} // if
		} // if
	} // for inheritance
}


void Component::associationClassManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::ASSOCIATION_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();
		ObjPointer obj3 = rel_it.getOp3();
		// the obj4 points to the connection line between the source and the connector
		// the obj5 points to the connection line between the connector and destination
		BON::Connection obj4( rel_it.getOp4());
		BON::Connection obj5( rel_it.getOp5());

		::FCO* op1 = m_sheet->findFCO( rel_it.getOp1());
		::FCO* op2 = m_sheet->findFCO( rel_it.getOp2());
		::FCO* op3 = m_sheet->findFCO( rel_it.getOp3());

		if ( op1 != 0 && op2 != 0 && op3 != 0)
		{
			// asking the rolenames and cardinalities
			std::string src_role = "src", dst_role = "dst";
			std::string src_card = "0..*", dst_card = "0..*";

			src_card = obj4->getAttribute( "Cardinality")->getStringValue();
			dst_card = obj5->getAttribute( "Cardinality")->getStringValue();

			src_role = obj4->getAttribute( "srcRolename")->getStringValue();
			if ( src_role != "" && src_role != "src") 
				global_vars.err << "Incorrect Rolename attribute: <" << src_role << "> of " << obj4->getName() + "\n";

			dst_role = obj5->getAttribute( "dstRolename")->getStringValue();
			if ( dst_role != "" && dst_role != "dst") 
				global_vars.err << "Incorrect Rolename attribute: <" << dst_role << "> of " << obj5->getName() + "\n";


			//TO( src_role + ":"+ dst_role +"|" + src_card +":"+dst_card);
			ConnJoint::SDList list_op1, list_op2;
			list_op1.push_back( op1);
			list_op2.push_back( op2);

			if ( op3->getMyKind() != Any::CONN ) global_vars.err << "Error: How can happen that the association class is Not a Connection.\n";
			ConnectionRep * conn_obj = dynamic_cast< ConnectionRep * > ( op3 );

			if (conn_obj) 
			{
				ConnJoint * assoc = conn_obj->createJoint( conn_obj, list_op1, list_op2, 
					                                             src_role == dst_role,
				                                               src_card, dst_card);
				conn_obj->addJoint( assoc ); // op3 describes the association of op1 and op2

				// the object will be deleted later by its owner
			}
			else global_vars.err << "ERROR after dynamic_cast - conn\n";
			//TO( obj3->getName() + " : " + obj1->getName() + " >--> " + obj2->getName());
		}
		else if ( obj3 == BON::Object() )
			global_vars.err << "Association relation is not complete. Association class missing. Op1: " + obj1->getName() + " Op2: " + obj2->getName() + "\n";
		else 
			global_vars.err << "Association relation is not complete. Some part missing. Op1: " + obj1->getName() + " Op2: " + obj2->getName() + " Association class: " + obj3->getName() + "\n";
	} // if
}


void Component::setMemberManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::SET_MEMBER_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();

		::FCO* set = m_sheet->findFCO( rel_it.getOp1());
		::FCO* member = m_sheet->findFCO( rel_it.getOp2());
		if ( set != 0 && member != 0)
		{
			if ( set->getMyKind() != Any::SET ) global_vars.err << "Not a set on left hand side of set_member relation\n";
			SetRep * set_obj = dynamic_cast< SetRep * > ( set );
			if (set_obj) set_obj->addMember( member);
			else global_vars.err << "ERROR after dynamic_cast - set\n";

			//TO( obj1->getName() + " has member " + obj2->getName() );
		}
		else
		{
			if ( set == 0 )
				global_vars.err << "No set peer present in set_member relation. " << obj1->getName() << " missing.\n";
			if ( member == 0 )
				global_vars.err << "No member peer present in set_member relation. " << obj2->getName() << " missing.\n";
		} // if
	} // if
}


void Component::refersToManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::REFER_TO_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();

		::FCO* elem = m_sheet->findFCO( rel_it.getOp1());
		::FCO* ref = m_sheet->findFCO( rel_it.getOp2());
		if ( elem != 0 && ref != 0)
		{
			ReferenceRep * ref_obj = dynamic_cast<ReferenceRep *>( ref);
			if ( !ref_obj || ref->getMyKind() != Any::REF)
				global_vars.err << "Not reference referring\n";
			else
				ref_obj->addInitialReferee( elem);
			elem->addRefersToMe( ref_obj);

			//TO( obj2->getName() + " ----> " + obj1->getName() );
		}
		else
		{
			if ( elem == 0 )
				global_vars.err << "No referee peer present in RefersTo relation. " << obj1->getName() << " missing.\n";
			if ( ref == 0 )
				global_vars.err << "No reference peer present in RefersTo relation. " << obj2->getName() << " missing.\n";
		} // if
	} // if
}


void Component::hasAspectManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::HAS_ASPECT_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();

		::FCO* model = m_sheet->findFCO( rel_it.getOp1());
		Any* aspect = m_sheet->findAny( rel_it.getOp2());
		if ( model != 0 && aspect != 0)
		{
			ModelRep * model_obj = dynamic_cast< ModelRep * > ( model );
			AspectRep * aspect_obj = dynamic_cast< AspectRep * > ( aspect );
			if (!aspect_obj) 
				global_vars.err << "ERROR after dynamic_cast - has aspect - aspect is 0\n";
			if (!model_obj || !aspect_obj || model->getMyKind() != Any::MODEL ) 
				global_vars.err << "ERROR after dynamic_cast " << (aspect_obj?"aspect is 0":(model_obj?"model is 0":"wrong kind")) << "\n";
			else
				model_obj->addAspect( aspect_obj); //adding the aspect_ptr to the model

			//TO( obj1->getName() + " has aspect " + obj2->getName() );
		}
		else
		{
			if ( model == 0 )
				global_vars.err << "No model peer present in has_aspect relation. " << obj1->getName() << " missing.\n";
			if ( aspect == 0 )
				global_vars.err << "No aspect peer present in has_aspect relation. " <<	obj2->getName() << " missing.\n";
		} // if
	} // if
}


void Component::containmentManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::CONTAINMENT_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();
		BON::Connection obj3( rel_it.getOp3());

		::FCO* model = m_sheet->findFCO( rel_it.getOp1());
		::FCO* fco = m_sheet->findFCO( rel_it.getOp2());

		if ( model != 0 && fco != 0)
		{
			ModelRep * model_obj = dynamic_cast< ModelRep * > ( model);
			if (!model_obj || model->getMyKind() != Any::MODEL) 
				global_vars.err << "ERROR: after dynamic_cast - containment - model is 0 / Not model contains an FCO\n";

			if ( !obj3) 
				global_vars.err << "ERROR: Null containment line class - containmentManager\n";

			bool is_a_port = obj3->getAttribute("IsPort")->getBooleanValue();
			std::string comp_role = obj3->getAttribute("Rolename")->getStringValue();
			std::string card = obj3->getAttribute("Cardinality")->getStringValue();

			RoleRep role( 
				comp_role,
				fco,
				model_obj,
				is_a_port, 
				card,
				false, // inh flag
				false); // long form flag -> will be set later by initRoleNames

			// is prevented multiple insertion? - yes, though similar rolename should be checked
			// this listing of the connections handles a rolename (a containment line) only once !!!
			model_obj->addRole( fco, role);
			//fco->iAmPartOf( model_obj);
		}
		else
		{
			if ( model == 0 )
				global_vars.err << "No model peer present in containment relation. " << obj1->getName() << " missing.\n";
			if ( fco == 0 )
				global_vars.err << "No fco peer present in containment relation. " << obj2->getName() << " missing.\n";
		} // if
	} // if
}


void Component::folderContainmentManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::FOLDER_CONTAINMENT_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();
		BON::Connection obj3( rel_it.getOp3());

		Any* folder = m_sheet->findAny( rel_it.getOp1());
		Any* any = m_sheet->findAny( rel_it.getOp2());
		if ( folder != 0 && any != 0)
		{
			if ( folder->getMyKind() != Any::FOLDER ) global_vars.err << "Not a folder contains an FCO\n";

			FolderRep * folder_obj = dynamic_cast< FolderRep * > ( folder );
			if (!folder_obj) global_vars.err << "ERROR after dynamic_cast - folder_containment - folder is 0\n";
			
			std::string card = "0..*";//obj3->getAttribute( "Cardinality")->getStringValue();

			if ( any->getMyKind() != Any::FOLDER) 
			{
				::FCO * fco = dynamic_cast< ::FCO *>( any);
				if (!fco) global_vars.err << "ERROR after dynamic cast - folder containment - subfolder is 0\n";
				else folder_obj->addFCO( fco, card);
			}
			else 
			{
				FolderRep * sub_f = dynamic_cast< FolderRep *>( any);
				if ( !sub_f) global_vars.err << "ERROR after dynamic cast - folder containment - subfolder is 0\n";
				else folder_obj->addSubFolderRep( sub_f, card);
			}
		}
		else
		{
			if ( folder == 0 )
				global_vars.err << "No folder peer present in folder_containment relation. " <<  obj1->getName() << " missing.\n";
			if ( any == 0 )
				global_vars.err << "No element peer present in folder_containment relation. " << obj2->getName() << " missing.\n";
		} // if
	} // if
}


void Component::aspectMemberManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::ASPECT_MEMBER_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();

		Any* aspect = m_sheet->findAny( rel_it.getOp1());
		::FCO* member = m_sheet->findFCO( rel_it.getOp2());
		if ( aspect != 0 && member != 0)
		{
			if ( aspect->getMyKind() != Any::ASPECT ) global_vars.err << "Not aspect consists of FCOs\n";

			AspectRep * aspect_obj = dynamic_cast< AspectRep * > ( aspect );
			if ( !aspect_obj) global_vars.err << "ERROR after dynamic_cast - aspect member - aspect is 0\n";

			if ( rel_it.getOp3() != BON::Object() && 
				rel_it.getOp4() != BON::Object()) // means a role is only the aspect member
			{
				std::string rolename = Connection( rel_it.getOp3())->getAttribute("Rolename")->getStringValue();
				bool is_a_port = Connection( rel_it.getOp3())->getAttribute("IsPort")->getBooleanValue();
				std::string card = Connection( rel_it.getOp3())->getAttribute("Cardinality")->getStringValue();

				//ModelRep * model = static_cast<ModelRep*>( m_sheet->findFCO( rel_it.getOp4())); // op4 is the container model
				ModelRep * model = dynamic_cast<ModelRep*>( m_sheet->findFCO( rel_it.getOp4())); // op4 is the container model
				if ( model != 0)
				{
					RoleRep role( 
						rolename,
						member,
						model,
						is_a_port, 
						card,
						false, // inh flag
						false); // long form flag -> will be set later by initRoleNames

					aspect_obj->addRRole( role);
				}
				else // model cannot be found //<!> needs testing
					global_vars.err << "No model (op4) present in aspect_member relation. " << rel_it.getOp4()->getName() << " missing.\n";
			}
			else // means regular aspect membership
				aspect_obj->addFCO( member);
			//TO( obj1->getName() + " aspect member " + obj2->getName() );
		}
		else
		{
			if ( aspect == 0 )
				global_vars.err << "No aspect peer present in aspect_member relation. " << obj1->getName() << " missing.\n";
			if ( member == 0 )
				global_vars.err << "No member peer present in aspect_member relation. " << obj2->getName() << " missing.\n";
		} // if
	} // if
}


void Component::hasConstraintManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::HAS_CONSTRAINT_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();

		Constrained* consed = m_sheet->findConstrained( rel_it.getOp1());
		Any* constraint = m_sheet->findAny( rel_it.getOp2());
		if ( consed != 0 && constraint != 0)
		{
			ConstraintRep *constraint_obj = dynamic_cast< ConstraintRep * >(constraint);

			consed->addInitialConstraintRep( constraint_obj);
			constraint_obj->attachedTo();

			/*if (any && (any->isFCO() || any->getMyKind() == Any::FOLDER)) 
			{
				any->addInitialConstraintRep( constraint_obj);
				constraint_obj->attachedTo();
			}
			else
				global_vars.err << constraint_obj->getName() << " constraint is owned by " << any->getName() << " which is neither FCO nor Folder\n";*/
		}
		else
		{
			if ( consed == 0 )
				global_vars.err << "No owner (FCO or Folder) peer present in has_constraint relation. " << obj1->getName() << " missing.\n";
			if ( constraint == 0 )
				global_vars.err << "No Constraint peer present in has_constraint relation. " <<  obj2->getName() + " missing.\n";
		} // if
	} // if
}


void Component::hasAttributeManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::HAS_ATTRIBUTE_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();

		::FCO* fco = m_sheet->findFCO( rel_it.getOp1());
		Any* attr = m_sheet->findAny( rel_it.getOp2());
		if ( fco != 0 && attr != 0)
		{
			AttributeRep * attr_obj = dynamic_cast< AttributeRep *>( attr); // <?> dynamic cast
			fco->addInitialAttribute( attr_obj);
			if ( !attr_obj->isGlobal())
				attr_obj->addOwner( fco);
		}
		else
		{
			if ( fco == 0 )
				global_vars.err << "No fco peer present in has_attribute relation. " << obj1->getName() << " missing.\n";
			if ( attr == 0 )
				global_vars.err << "No attribute peer present in has_attribute relation. " <<  obj2->getName() << " missing.\n";
		} // if
	} // if
}


/**
 * Does the hard work for the aspects also like: 
 * inserting into model, inquering the aspect members
 */
void Component::CHECK()
{
	Relation_Iterator rel_it = m_relations.begin();
	// check if all the m_relations have their correct number of operands
	for( ; rel_it != m_relations.end(); ++rel_it)
	{
		if (rel_it->getOperation() == Relation::ASSOCIATION_OP)
		{
			bool three_op = rel_it->getOp3() != BON::Object();
			if( rel_it->getOp1() == BON::Object() || 
				rel_it->getOp2() == BON::Object() || 
				rel_it->getOp3() == BON::Object() || 
				rel_it->getOp4() == BON::Object() || 
				rel_it->getOp5() == BON::Object() )
				global_vars.err << "Error: ASSOCIATION has one operand 0\n";
			Entity ent1 = entitySearch( rel_it->getOp1());
			Entity ent2 = entitySearch( rel_it->getOp2());
			Entity ent3 = entitySearch( rel_it->getOp3());

			ObjPointer o1 = rel_it->getOp1();
				
			ObjPointer ptr, o2 = rel_it->getOp2();

			if ( ent1 == Entity( BON::Folder(), BON::Object()) )
			{
				ptr = rel_it->getOp1();
				m_entities.push_back( Entity( BON::Folder(), rel_it->getOp1()));
				if ( ptr != BON::Object())
					TO( std::string("CHECK: Operand 1 of ") + rel_it->getOperationStr() + " is not present in Entities\n" + 
						ptr->getName() + " : " + ptr->getObjectMeta().name() + " has been inserted");
				else
					TO( std::string("CHECK: Operand 1 of ") + rel_it->getOperationStr() + " is null\n");
			}
			if ( ent2 == Entity( BON::Folder(), BON::Object()))
			{
				ptr = rel_it->getOp2();
				m_entities.push_back( Entity( BON::Folder(), rel_it->getOp2()));
				if ( ptr != BON::Object())
					TO( std::string("CHECK: Operand 2 of ") + rel_it->getOperationStr() + " is not present in Entities\n" + 
						ptr->getName() + " : " + ptr->getObjectMeta().name() + " has been inserted");
				else
					TO( std::string("CHECK: Operand 2 of ") + rel_it->getOperationStr() + " is null\n");
			}
			if ( ent3 == Entity( BON::Folder(), BON::Object()))
			{
				if ( three_op )
				{
					ptr = rel_it->getOp3();
					m_entities.push_back( Entity( BON::Folder(), rel_it->getOp3()));
					TO( std::string("CHECK: Operand 3 of ") + rel_it->getOperationStr() + " is not present in Entities\n" + 
						ptr->getName() + " : " + ptr->getObjectMeta().name() + " has been inserted");
				}
				else 
				{
					TO("CHECK: Association without Connection class: " + o1->getName() + " o " + o2->getName() );
				}
			}
		}
		else
		{
			if( rel_it->getOp1() == BON::Object() ||
				rel_it->getOp2() == BON::Object() )
				TO( rel_it->getOperationStr() + "has one operand 0");

			Entity ent1 = entitySearch( rel_it->getOp1());
			Entity ent2 = entitySearch( rel_it->getOp2());
			ObjPointer ptr = BON::Object();
			if ( ent1 == Entity( BON::Folder(), BON::Object()))
			{
				ptr = rel_it->getOp1();
				m_entities.push_back( Entity( BON::Folder(), rel_it->getOp1()));
				if ( ptr != BON::Object())
					TO( std::string("CHECK: Operand 1 of ") + rel_it->getOperationStr() + " is not present in Entities\n" + 
						ptr->getName() + " : " + ptr->getObjectMeta().name() + " has been inserted");
				else
					TO( std::string("CHECK: Operand 1 of ") + rel_it->getOperationStr() + " is null\n"); 
			}
			if ( ent2 == Entity( BON::Folder(), BON::Object()))
			{
				ptr = rel_it->getOp2();
				m_entities.push_back( Entity( BON::Folder(), rel_it->getOp2()));
				ObjPointer ptr2 = rel_it->getOp1();
				std::string peer1, peer2;
				if ( ptr2 != BON::Object())
					peer1 = ptr2->getName() + " " + ptr2->getObjectMeta().name();
				if ( rel_it->getOp2())
					peer2 = rel_it->getOp2()->getName() + " " + rel_it->getOp2()->getObjectMeta().name();
				TO( std::string("CHECK: Operand 2 of ") + rel_it->getOperationStr() + " is not present in Entities\n" + 
					ptr->getName() + " : " + ptr->getObjectMeta().name() + " has been inserted\n" + 
					"Operand1: " + peer1 + "\n" +
					"Operand2: " + peer2 + "\n");
				
				// try to check the members of a set
				if (rel_it->getOperation() == Relation::HAS_ASPECT_OP )
				{
					// we have an aspect pointed by op2
					ObjPointer t_ptr = rel_it->getOp2();
					ObjPointer obj = t_ptr;
					//BON::Set set = dynamic_cast<BON::Set>(obj);
					BON::Set set = BON::Set( obj);
					if (!set) TO("ERROR during set manipulation");
					
					std::set<FCO> list = set->getMembers();
					std::set<FCO>::iterator list_it = list.begin();
					std::string mmm;
					while ( list_it != list.end())
					{
						FCO actual = *list_it;
						Relation rela( Relation::ASPECT_MEMBER_OP, t_ptr, actual);
						m_relations.push_back(rela);
						mmm += actual->getName() + "/" + actual->getObjectMeta().name() + "\n";
						++list_it;
					}
					TO( "Aspect members are:\n" + mmm);
				}
			}
			if ( rel_it->getOperation() == Relation::CONTAINMENT_OP ||
				rel_it->getOperation() == Relation::FOLDER_CONTAINMENT_OP )
			{
				if (rel_it->getOp3() == BON::Object())
					TO( "(Folder)Containment line object not present in m_relations list");
			}
		} // end if
	} // end for

	Relation_Iterator rel_it1 = m_relations.begin();
	// check if all the relations have their correct number of operands
	for( ; rel_it1 != m_relations.end(); ++rel_it1)
	{
		Relation_Iterator rel_it2 = m_relations.begin();
		// check if all the relations have their correct number of operands
		for( ; rel_it2 != m_relations.end(); ++rel_it2)
		{
			if (rel_it1->getOperation() == Relation::HAS_ATTRIBUTE_OP &&
				rel_it2->getOperation() == Relation::HAS_ATTRIBUTE_OP )
			{
				//CHECK if the same attribute is contained twice by the FCO
				if ( rel_it1->getOp1() == rel_it2->getOp1() 
					&& rel_it1->getOp2() == rel_it2->getOp2() 
					&& rel_it1 != rel_it2)
				{
					ObjPointer o1 = rel_it1->getOp1();
						
					ObjPointer o2 = rel_it1->getOp2();
					TO("Same attribute " + o2->getName() +
						" contained twice by " + o1->getName());
				}
			}
		}
	}
}


// ====================================================
// This is the main component method for Interpereters and Plugins.
// May also be used in case of invokeable Add-Ons
void Component::invokeEx( Project& project, FCO& currentFCO, const std::set<FCO>& setSelectedFCOs, long lParam )
{
	// ======================
	// Insert application specific code here

	initMembers( project);

	global_vars.err.open( "error.log", std::ios_base::out);

	try {
		scanProject( project);

		CHECK();

		selectFromSameAspectsFolders();
		proxyFinder();
		equivalenceFinder();
		removeProxiesAndEquiv();
		while ( !checkForProxies()) { }
		
		bool do_at_all = true;
		if ( do_at_all)
		{
			if ( Sheet::checkInstance())
				global_vars.err << "Internal error: merged paradigm sheet already exists\n";

			createSheet(); // modify this method to create your own specialized sheet

			try {
				populateSheet( m_projectName);
			} catch( ... ) {
				global_vars.err << "Error: exception thrown by populateSheet\n";
			}

			if ( !Sheet::checkInstance())
				global_vars.err << "Internal error: sheet doesn't exist\n";
			
			deleteSheet();
		}
		else
			global_vars.err << "Exited before populating the Merged Paradigm Sheet. Proxy or other problem may exist.\n";
	}	catch (...)	{
		global_vars.err << "Internal error: Exception thrown by Component.\n";
		deleteSheet();
	}

	if ( Sheet::checkInstance())
		global_vars.err << "Internal error: Merged Paradigm Sheet still exists\n";

	global_vars.err.close();
	AfxMessageBox( "Job finished", MB_ICONINFORMATION);
}

// ====================================================
// This is the obsolete component interface
// This present implementation either tries to call InvokeEx, or does nothing except of a notification

void Component::invoke( Project& project, const std::set<FCO>& setModels, long lParam )
{
	#ifdef SUPPORT_OLD_INVOKE
		Object focus;
		invokeEx( project, focus, setModels, lParam );
	#else
		if ( m_bIsInteractive )
			AfxMessageBox("This BON2 Component does not support the obsolete invoke mechanism!");
	#endif
}


// ====================================================
// GME currently does not use this function
// You only need to implement it if other invokation mechanisms are used
void Component::objectInvokeEx( Project& project, Object& currentObject, const std::set<Object>& setSelectedObjects, long lParam )
	{
		if ( m_bIsInteractive )
			AfxMessageBox("This BON2 Component does not support objectInvokeEx method!");
	}

// ====================================================
// Implement application specific parameter-mechanism in these functions

Util::Variant Component::getParameter( const std::string& strName )
{
	// ======================
	// Insert application specific code here

	return Util::Variant();
}

void Component::setParameter( const std::string& strName, const Util::Variant& varValue )
{
	// ======================
	// Insert application specific code here
}

#ifdef GME_ADDON

// ====================================================
// If the component is an Add-On, then this method is called for every Global Event

void Component::globalEventPerformed( globalevent_enum event )
{
	// ======================
	// Insert application specific code here
}

// ====================================================
// If the component is an Add-On, then this method is called for every Object Event

void Component::objectEventPerformed( Object& object, unsigned long event, VARIANT v )
{
	// ======================
	// Insert application specific code here
}

#endif // GME_ADDON


}; // namespace BON

