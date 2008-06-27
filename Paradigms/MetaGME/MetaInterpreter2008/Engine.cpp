#include "stdafx.h"
#include "RawComponent.h"
#include "logger.h"
#include <string>
#include "Dumper.h"
#include "NameSpecDlg.h"
#include "globals.h"

extern Globals global_vars;
extern NameSpecDlg * dlg;

void RawComponent::entityBuilder( IMgaModel* model, IMgaFolder* parent)
{
	CComPtr<IMgaFCOs> children;
	COMTHROW( model->get_ChildFCOs( &children));

	long c = 0;
	if( children) COMTHROW( children->get_Count( &c));

	for( long i = 1; i <= c; ++i)
	{
		CComPtr<IMgaFCO> a_chi;
		COMTHROW( children->get_Item( i, &a_chi));

		CComQIPtr<IMgaSet> a_set( a_chi);
		CComQIPtr<IMgaReference> a_ref( a_chi);
		CComQIPtr<IMgaConnection> a_con( a_chi);
		CComQIPtr<IMgaAtom> a_ato( a_chi);


		// handling sets (which in MetaGME are only the aspects)
		if( a_set)
		{
			Entity new_elem( parent, a_set);
			storeEntity( new_elem);

			CComPtr<IMgaFCOs> aspect_elements;
			COMTHROW( a_set->get_Members( &aspect_elements));
			
			long d = 0;
			if( aspect_elements) COMTHROW( aspect_elements->get_Count( &d));

			for( long j = 1; j <= d; ++j)
			{
				CComPtr<IMgaFCO> asp_elem;
				COMTHROW( aspect_elements->get_Item( j, &asp_elem));
				// an aspect member may be of type atom (any kind) or reference type (proxy) or
				// connection (like containment = role)
				// it cannot be of type set (aspect), or type model

				CComPtr<IMgaMetaFCO> asp_elem_meta;
				COMTHROW( asp_elem->get_Meta( &asp_elem_meta));

				objtype_enum meta_obj_type;
				COMTHROW( asp_elem_meta->get_ObjType( &meta_obj_type));

				CComBSTR meta_obj_kind;
				COMTHROW( asp_elem_meta->get_Name( &meta_obj_kind));

				if( meta_obj_type == OBJTYPE_ATOM ||
				    meta_obj_type == OBJTYPE_REFERENCE)
				{ // if an atom or reference is to be an aspect member
					
					Relation rela( Relation::ASPECT_MEMBER_OP, a_set, asp_elem);

					if( m_relations.end() == std::find( m_relations.begin(), m_relations.end(), rela))
						storeRelation( rela);
					else
						global_vars.err << MSG_ERROR << "Internal warning: Relation ASPECT_MEMBER \"" << asp_elem << "\" found already in relations.\n";
				}
				else if( meta_obj_type == OBJTYPE_CONNECTION &&
				         meta_obj_kind == Relation::containment_str.c_str())
				{ // if a role is intended to be an aspect member
					CComPtr<IMgaFCO> src_fco, dst_model;
					CComQIPtr<IMgaSimpleConnection> containment( asp_elem);
					if( containment)
					{
						COMTHROW( containment->get_Src( &src_fco));
						COMTHROW( containment->get_Dst( &dst_model));
					}
					
					Relation rela( Relation::ASPECT_MEMBER_OP, a_set, src_fco, asp_elem, dst_model); // special ASPECT_MEMBER_OP

					if ( m_relations.end() == std::find( m_relations.begin(), m_relations.end(), rela))
						storeRelation( rela);
					else
						global_vars.err << MSG_ERROR << "Internal warning: Relation ASPECT_MEMBER \"" << asp_elem << "\" found already in relations\n";
				}
				else
					global_vars.err << MSG_ERROR << "Cannot handle AspectMember operation. Op1: " << a_set << " Op2: " << asp_elem << "\n";
			}
		}

	
		if( a_con) // handling connections
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

			std::string conn_kind = Util::kind( a_con);

			if ( conn_kind == Relation::containment_str ||
				conn_kind == Relation::folder_containment_str ||
				conn_kind == Relation::set_membership_str ||
				conn_kind == Relation::refer_to_str ||
				conn_kind == Relation::has_aspect_str ||
				conn_kind == Relation::has_constraint_str ||
				conn_kind == Relation::has_attribute_str)
			{
				CComPtr<IMgaFCO> src, dst;
				CComQIPtr<IMgaSimpleConnection> s_con( a_con);
				COMTHROW( s_con->get_Src( &src));
				COMTHROW( s_con->get_Dst( &dst));

				Relation rela( Relation::CONTAINMENT_OP, dst, src); // create a relation object

				if ( conn_kind == Relation::containment_str)
				{
					rela.setOperation( Relation::CONTAINMENT_OP); 
					rela.setOp3( a_con);
				}
				else if ( conn_kind == Relation::folder_containment_str)
				{
					rela.setOperation( Relation::FOLDER_CONTAINMENT_OP); 
					rela.setOp3( a_con);
				}
				else if ( conn_kind == Relation::set_membership_str)
					rela.setOperation( Relation::SET_MEMBER_OP);
				else if ( conn_kind == Relation::refer_to_str)
					rela.setOperation( Relation::REFER_TO_OP);
				else if ( conn_kind == Relation::has_aspect_str)
					rela.setOperation( Relation::HAS_ASPECT_OP);
				else if ( conn_kind == Relation::has_constraint_str)
					rela.setOperation( Relation::HAS_CONSTRAINT_OP);
				else if ( conn_kind == Relation::has_attribute_str)
					rela.setOperation( Relation::HAS_ATTRIBUTE_OP);
				else
					global_vars.err << MSG_ERROR << "Unknown connection kind.\n";

				storeRelation( rela);
			}
		}

		if( a_ref) // handling proxies
		{
			Entity new_elem( parent, a_ref);
			storeEntity( new_elem);

			try
			{
				CComPtr<IMgaFCO> referred;
				COMTHROW( a_ref->get_Referred( &referred));

				this->m_realObj[ CComPtr<IMgaFCO>( a_ref)] = referred; //! a NULL proxy is part of m_realObj, having a NULL value attached
				if ( referred) // if not a null reference
					this->m_equivBag[ CComPtr<IMgaFCO>( referred)].insert( CComPtr<IMgaFCO>( a_ref));
				else // notify about null proxies
					global_vars.err << MSG_ERROR << "Null proxy object found: " << a_ref << "\n";
			}
			catch( ... )
			{
				global_vars.err << MSG_ERROR << "Handling exeception thrown by Null proxy " << a_ref << "\n";
			}
 		}
	
		if( a_ato) // handling atoms
		{
			Entity new_elem( parent, a_ato);
			std::string kind_name = Util::kind( a_ato);

			if ( kind_name != Relation::connector_str.c_str() && 
				kind_name != Relation::inheritance_str.c_str() && 
				kind_name != Relation::int_inheritance_str.c_str() && 
				kind_name != Relation::imp_inheritance_str.c_str() && 
				kind_name != Relation::equivalence_str.c_str() &&
				kind_name != Relation::same_folder_str.c_str() && 
				kind_name != Relation::same_aspect_str.c_str())
			{
				storeEntity( new_elem); // deserves the Entity status
			}
			else if ( kind_name == Relation::connector_str)
			{
				// part of a few connections
				CComPtr<IMgaConnPoints> conn_pts;
				COMTHROW( a_ato->get_PartOfConns( &conn_pts));

				long c = 0;
				if( conn_pts) COMTHROW( conn_pts->get_Count( &c));

				CComPtr<IMgaFCO> obj1, obj2, obja;
				CComPtr<IMgaSimpleConnection> in_connection_line, out_connection_line;

				// for all connections a_ato takes part in
				for( long j = 1; j <= c; ++j)
				{
					// get one connpoint at a time
					CComPtr<IMgaConnPoint> conn_pt;
					COMTHROW( conn_pts->get_Item( j, &conn_pt));

					// the connection which is part of
					CComPtr<IMgaConnection> conn;
					COMTHROW( conn_pt->get_Owner( &conn));

					// is casted to a simple connection for simpler inquiry
					CComQIPtr<IMgaSimpleConnection> simple_conn( conn);

					// get its kind	
					std::string conn_kind = Util::kind( simple_conn);

					// src, dst 
					CComPtr<IMgaFCO> t_src, t_dst;
					COMTHROW( simple_conn->get_Src( &t_src));
					COMTHROW( simple_conn->get_Dst( &t_dst));

					// sorting out based on the connection kind
					if( conn_kind == Relation::connector_src && t_dst == a_chi) // incoming conn to a_ato
					{
						in_connection_line = simple_conn;
						obj1 = t_src;
					}
					else if( conn_kind == Relation::connector_dst && t_src == a_chi) // outgoing conn from a_ato)
					{
						out_connection_line = simple_conn;
						obj2 = t_dst;
					}
					else if( conn_kind == Relation::connector_descr)
					{
						if( t_src == a_ato) // this connection might go both ways between Connector and AssociationClass
							obja = t_dst;
						else if( t_dst == a_ato)
							obja = t_src;
					}
				}

				if ( !in_connection_line || !out_connection_line)
					global_vars.err << MSG_ERROR << "Connector \"" << a_ato << "\" does not have both SourceToConnector and ConnectorToDestination connections attached.\n";

				
				if ( !obja)
					global_vars.err << MSG_ERROR << "Connector \"" << a_ato << "\" has no Associated Class!\n";


				// insert into the relations table an association with 
				// src: obj1, dest: obj2, association class: obja, in line, and out_line
				if ( !obj1 || !obj2 || !obja || !in_connection_line || !out_connection_line)
				{
					global_vars.err << MSG_ERROR << "Association \"" << obja << "\" disregarded.\n";
				}
				else
				{
					Relation rela( 
						Relation::ASSOCIATION_OP, 
						obj1,
						obj2,
						obja,
						in_connection_line,
						out_connection_line);
					storeRelation( rela);
				}
			}
			else if ( kind_name == Relation::inheritance_str
			    ||    kind_name == Relation::imp_inheritance_str
                ||    kind_name == Relation::int_inheritance_str)
			{
				// will collect here the found info
				CComPtr<IMgaFCO>  base; // just 1
				CComPtr<IMgaFCOs> derds;// more than 1 usually
				COMTHROW( derds.CoCreateInstance( L"Mga.MgaFCOs"));

				// part of a few connections
				CComPtr<IMgaConnPoints> conn_pts;
				COMTHROW( a_ato->get_PartOfConns( &conn_pts));

				long c = 0;
				if( conn_pts) COMTHROW( conn_pts->get_Count( &c));

				// for all connections a_ato takes part in
				for( long j = 1; j <= c; ++j)
				{
					// get one connpoint at a time
					CComPtr<IMgaConnPoint> conn_pt;
					COMTHROW( conn_pts->get_Item( j, &conn_pt));

					// the connection which is part of
					CComPtr<IMgaConnection> conn;
					COMTHROW( conn_pt->get_Owner( &conn));

					// is casted to a simple connection for simpler inquiry
					CComQIPtr<IMgaSimpleConnection> simple_conn( conn);

					// get its kind	
					std::string conn_kind = Util::kind( simple_conn);

					// src, dst 
					CComPtr<IMgaFCO> t_src, t_dst;
					COMTHROW( simple_conn->get_Src( &t_src));
					COMTHROW( simple_conn->get_Dst( &t_dst));

					// sorting out based on the connection kind
					if( conn_kind == Relation::inheritance_base && t_dst == a_chi) // incoming conn to a_ato (base2inh)
					{
						// t_src must be the base FCO
						if( base) // already found one, now yet another
							global_vars.err << MSG_WARNING << "Too many base classes at " << a_ato << ". Multiple inheritance should be used with two different operators.\n";
						else
							base = t_src;
					}
					else if( conn_kind == Relation::inheritance_derived && t_src == a_chi) // outgoing conn from a_ato (inh2derd)
					{
						// t_dst must be one of the derd
						COMTHROW( derds->Append( t_dst));
					}
				}

				Relation::OPER_TYPE ot = Relation::INHERITANCE_OP; // default
				// overwrite if it was imp or int
				if ( kind_name == Relation::imp_inheritance_str)
					ot = Relation::IMP_INHERITANCE_OP;
                else if ( kind_name == Relation::int_inheritance_str)
					ot = Relation::INT_INHERITANCE_OP;

				// store the found relations now 
				long d = 0;
				if( base && derds) COMTHROW( derds->get_Count( &d));
				for( long j = 1; j <= d; ++j)
				{
					CComPtr<IMgaFCO> derd_item;
					COMTHROW( derds->get_Item( j, &derd_item));

					Relation rela( ot, base, derd_item); // store a relation of type ot
					storeRelation( rela);
				}

				while( d > 0)
					COMTHROW( derds->Remove( d--));
			} /* end if*/
			else if ( kind_name == Relation::equivalence_str
			      ||  kind_name == Relation::same_aspect_str
			      ||  kind_name == Relation::same_folder_str)
			{
				// will collect here the found info
				CComPtr<IMgaFCOs> peers_left;
				CComPtr<IMgaFCOs> peers_right;
				peers_left.CoCreateInstance( L"Mga.MgaFCOs");
				peers_right.CoCreateInstance( L"Mga.MgaFCOs");

				// part of a few connections
				CComPtr<IMgaConnPoints> conn_pts;
				COMTHROW( a_ato->get_PartOfConns( &conn_pts));

				long c = 0;
				if( conn_pts) COMTHROW( conn_pts->get_Count( &c));

				// for all connections a_ato takes part in
				for( long j = 1; j <= c; ++j)
				{
					// get one connpoint at a time
					CComPtr<IMgaConnPoint> conn_pt;
					COMTHROW( conn_pts->get_Item( j, &conn_pt));

					// the connection which is part of
					CComPtr<IMgaConnection> conn;
					COMTHROW( conn_pt->get_Owner( &conn));

					// is casted to a simple connection for simpler inquiry
					CComQIPtr<IMgaSimpleConnection> simple_conn( conn);

					// get its kind
					std::string conn_kind = Util::kind( simple_conn);

					// src, dst 
					CComPtr<IMgaFCO> t_src, t_dst;
					COMTHROW( simple_conn->get_Src( &t_src));
					COMTHROW( simple_conn->get_Dst( &t_dst));

					if( conn_kind == Relation::equivalence_right
					 || conn_kind == Relation::same_aspect_right
					 || conn_kind == Relation::same_folder_right)
					{
						ASSERT( t_dst == a_ato);
						COMTHROW( peers_left->Append( t_src));
					}
					else if( conn_kind == Relation::equivalence_left
					      || conn_kind == Relation::same_aspect_left
					      || conn_kind == Relation::same_folder_left)
					{
						ASSERT( t_src == a_ato);
						COMTHROW( peers_right->Append( t_dst));
					}
				}

				long l_count( 0), r_count( 0);
				if( peers_left) COMTHROW( peers_left->get_Count( &l_count));
				if( peers_right) COMTHROW( peers_right->get_Count( &r_count));

				if( !l_count || !r_count)
					global_vars.err << MSG_ERROR << "Equivalence \"" << a_ato << "\" disregarded.\n";
				else for( long l_index = 1; l_index <= l_count; ++l_index)
				{
					CComPtr<IMgaFCO> left;
					COMTHROW( peers_left->get_Item( l_index, &left));

					for( long r_index = 1; r_index <= r_count; ++r_index)
					{
						CComPtr<IMgaFCO> right;
						COMTHROW( peers_right->get_Item( r_index, &right));

						if( !left || !right)
							global_vars.err << MSG_ERROR << "Equivalence \"" << a_ato << "\" disregarded.\n";
						else
						{
							Relation::OPER_TYPE ot = Relation::EQUIVALENCE_OP; // default
							// overwrite if it was SameAspect or SameFolder
							if ( kind_name == Relation::same_aspect_str)
								ot = Relation::SAME_ASPECT_OP;
							else if ( kind_name == Relation::same_folder_str)
								ot = Relation::SAME_FOLDER_OP;

							Relation rela( ot, left, right, a_ato);
							storeEquivRelation( rela);
						}
					}
				}

				while( l_count > 0) COMTHROW( peers_left->Remove( l_count--));
				while( r_count > 0) COMTHROW( peers_right->Remove( r_count--));

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
void RawComponent::selectFromSameAspectsFolders()
{
	Relation_Iterator rel_it = m_equivRelations.begin();
	for( ; rel_it != m_equivRelations.end(); ++rel_it)
	{
		if ( rel_it->getOperation() == Relation::SAME_ASPECT_OP || 
			rel_it->getOperation() == Relation::SAME_FOLDER_OP || 
			rel_it->getOperation() == Relation::EQUIVALENCE_OP)
		{
			{
				int p1 = isProxy( rel_it->getOp1());
				int p2 = isProxy( rel_it->getOp2());
				if( p1 == 2 || p2 == 2) // check for Null proxies
				{
					global_vars.err << MSG_ERROR << rel_it->getOperationStr() << " relation disregarded between " << rel_it->getOp1() << " and " << rel_it->getOp2() << ".\n";
					continue;
				}

				bool is_proxy_first  = p1 == 1;
				bool is_proxy_second = p2 == 1;
				
				ObjPointer selected_ptr = 0;
				if (is_proxy_first == is_proxy_second) // both or neither is proxy
					selected_ptr = rel_it->getOp3(); //set the sameaspect operator as resp pointer
				else if (is_proxy_first) // the second is not proxy so set is as the responsible object
					selected_ptr = rel_it->getOp2();
				else // the first is not a proxy
					selected_ptr = rel_it->getOp1();

				// the selected_ptr never points to a proxy -> later on it won't be replaced
				// with another object by RawComponent::OperandSearchAndReplace

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


Entity RawComponent::entitySearch( const ObjPointer& p_ptr)
{
	Entity_Iterator it( m_entities.begin());
	while ( it != m_entities.end() && p_ptr != it->getPointer())
		++it;
	
	if ( it == m_entities.end())
		return Entity( CComPtr<IMgaFolder>(0), CComPtr<IMgaFCO>(0));
	else 
		return *it;
}

void RawComponent::storeEntity( const Entity& p_ent)
{
	m_entities.push_back( p_ent);

	//char buff[256];
	//sprintf( buff, "0x%x Rp: 0x%x Pf: 0x%x", (long) p_ent.m_pointer, (long) p_ent.m_respPointer, (long) p_ent.m_parentFolder);
	//m_console.sendMsg( buff, MSG_INFO);

	if( !m_safe)
		COMTHROW( m_safe.CoCreateInstance( L"Mga.MgaObjects"));

	//if( p_ent.m_pointer) COMTHROW( m_safe->Append( p_ent.m_pointer));
	//if( p_ent.m_respPointer) COMTHROW( m_safe->Append( p_ent.m_respPointer));
	//if( p_ent.m_parentFolder) COMTHROW( m_safe->Append( p_ent.m_parentFolder));
	if( p_ent.getPointer()) COMTHROW( m_safe->Append( p_ent.getPointer()));
	if( p_ent.getRespPointer()) COMTHROW( m_safe->Append( p_ent.getRespPointer()));
	if( p_ent.getParentFolder()) COMTHROW( m_safe->Append( p_ent.getParentFolder()));

}

void RawComponent::storeRelation( Relation& p_rel)
{
	m_relations.push_back( p_rel);

	//char buff[256];
	//sprintf( buff, "0x%x Rp: 0x%x Pf: 0x%x", (long) p_ent.m_pointer, (long) p_ent.m_respPointer, (long) p_ent.m_parentFolder);
	//m_console.sendMsg( buff, MSG_INFO);

	if( !m_safe)
		COMTHROW( m_safe.CoCreateInstance( L"Mga.MgaObjects"));

	if( p_rel.getOp1()) COMTHROW( m_safe->Append( p_rel.getOp1()));
	if( p_rel.getOp2()) COMTHROW( m_safe->Append( p_rel.getOp2()));
	if( p_rel.getOp3()) COMTHROW( m_safe->Append( p_rel.getOp3()));
	if( p_rel.getOp4()) COMTHROW( m_safe->Append( p_rel.getOp4()));
	if( p_rel.getOp5()) COMTHROW( m_safe->Append( p_rel.getOp5()));
}

void RawComponent::storeEquivRelation( Relation& p_rel)
{
	m_equivRelations.push_back( p_rel);

	//char buff[256];
	//sprintf( buff, "0x%x Rp: 0x%x Pf: 0x%x", (long) p_ent.m_pointer, (long) p_ent.m_respPointer, (long) p_ent.m_parentFolder);
	//m_console.sendMsg( buff, MSG_INFO);

	if( !m_safe)
		COMTHROW( m_safe.CoCreateInstance( L"Mga.MgaObjects"));

	if( p_rel.getOp1()) COMTHROW( m_safe->Append( p_rel.getOp1()));
	if( p_rel.getOp2()) COMTHROW( m_safe->Append( p_rel.getOp2()));
	if( p_rel.getOp3()) COMTHROW( m_safe->Append( p_rel.getOp3()));
	if( p_rel.getOp4()) COMTHROW( m_safe->Append( p_rel.getOp4()));
	if( p_rel.getOp5()) COMTHROW( m_safe->Append( p_rel.getOp5()));
}

/*
Searches the relation container and replaces the proxy pointers with their real object peer
and removes the proxy from the entities container

Based on the assumption that a proxy cannot refer to another proxy
*/
void RawComponent::proxyFinder()
{
	RealMap_Iterator real_map_it = this->m_realObj.begin();
	for( ; real_map_it != m_realObj.end(); ++real_map_it)
	{
		ObjPointer proxy_for_sure = real_map_it->first;
		ObjPointer real_for_sure = real_map_it->second;

#ifdef _DEBUG
		std::string n1, n2;
		if ( proxy_for_sure != CComPtr<IMgaFCO>(0))
			n1 = Util::name( proxy_for_sure);
		if ( real_for_sure != CComPtr<IMgaFCO>(0))
			n2= Util::name( real_for_sure);
#endif
		if ( proxy_for_sure != CComPtr<IMgaFCO>(0) && real_for_sure != CComPtr<IMgaFCO>(0))
		{
			Entity_Iterator it( m_entities.begin());
			while ( it != m_entities.end() && proxy_for_sure != it->getPointer())
				++it;

			if ( it == m_entities.end())
			{
				global_vars.err << MSG_ERROR << "Entity not found during proxyFinder: " << proxy_for_sure << "\n";
			}
			else
			{
				operandSearchAndReplace( proxy_for_sure, real_for_sure);
				//proxies are in equivBag, so it will be marked, no need for it->deleted( true);//m_toBeDeletedEntities.push_back( proxy);
			}
		}
	}
}


void RawComponent::equivalenceFinder()
{
	Relation_Iterator rel_it = m_equivRelations.begin();
	while ( rel_it != m_equivRelations.end())
	{
		if( rel_it->getOperation() == Relation::EQUIVALENCE_OP ||
			rel_it->getOperation() == Relation::SAME_FOLDER_OP ||
			rel_it->getOperation() == Relation::SAME_ASPECT_OP )
		{ // 
			ObjPointer obj1 = rel_it->getOp1(), obj2 = rel_it->getOp2();

			
			if( obj1 != obj2) //avoid trivial case: "A equiv A"
			{
				// obj1 will have obj2 and proxies of obj2 as its alter egos
				insertIntoEquivBag( obj2, obj1);
				operandSearchAndReplace( obj2, obj1); //"Right law": repl left (op2) with right(op1)
			}
			
			rel_it = m_equivRelations.erase( rel_it); // <- relies on that erase increments rel_it

		}	
		else 
		{
			ASSERT(0); // no other relations are part of m_equivRelations
			++rel_it;
		}
	}
	ASSERT( m_equivRelations.empty()); // no relation should have remained
}


// collects the equivalent objects into a bag
// obj1 is the key in the map
// obj2 is the later-to-be-removed object from the entities
void RawComponent::insertIntoEquivBag( const ObjPointer& obj2, const ObjPointer& obj1)
{
	if ( obj1 == obj2) return; // avoid trivial case

	std::set < ObjPointer > bag2;

	// check if obj2 has its own bag?
	EquivBag_Iterator it = m_equivBag.find( obj2);
	if ( it != m_equivBag.end())
	{
		bag2 = m_equivBag[ obj2];
		m_equivBag.erase( it);
	}

	m_equivBag[obj1].insert( bag2.begin(), bag2.end());
	m_equivBag[obj1].insert( obj1);
	m_equivBag[obj1].insert( obj2);

#ifdef _DEBUG
	std::string n1 = Util::name( obj1);
	std::string n2 = Util::name( obj2);

	std::set < ObjPointer >:: const_iterator ii = m_equivBag[obj1].begin();
	for( ; ii != m_equivBag[obj1].end(); ++ii)
	{
		n2 = Util::name( *ii);
	}
#endif

}


void RawComponent::markEquivEntities()
{
	EquivBag_Iterator it = m_equivBag.begin();
	for( ; it != m_equivBag.end(); ++it)
	{
		//ASSERT( !it->first->isDeleted());
		long stat = 0;
		COMTHROW( it->first->get_Status( &stat));
		ASSERT( stat == 0);
		std::set< ObjPointer > & clique = it->second;
		std::set< ObjPointer > :: const_iterator jt = clique.begin();
		//std::string n1 = it->first->getName();

		for( ; jt != clique.end(); ++jt)
		{
			//std::string n2 = (*jt)->getName();
			if ( *jt != it->first) // the responsible might be in its equiv bag
			{
				Entity_Iterator kt( m_entities.begin());
				while ( kt != m_entities.end() && *jt != kt->getPointer())
					++kt;

				if ( kt != m_entities.end())
				{
					kt->deleted( true);//m_toBeDeletedEntities.push_back( ent);
				}
				else
				{
					global_vars.err << MSG_ERROR << "Entity not found during markEquivEntities: " << *jt << "\n";
				}
			}
		}
	}
}


/*
Searches the releation container and replaces all occurences of find_obj 
with real_obj.
Important: It replaces only the first three pointer operands (since 4th and 5th operands are
connections which cannot be proxies)
*/
void RawComponent::operandSearchAndReplace( const std::vector<ObjPointer>& find_obj_vec, const ObjPointer& real_obj)
{
	const static int len = 2;
	Relations* reldb[ len] = { &m_relations, &m_equivRelations};
	for ( int k = 0; k < len; ++k)
	{
		Relation_Iterator rel_it = reldb[k]->begin();
		for( ; rel_it != reldb[k]->end(); ++rel_it)
		{
			if (!rel_it->getOp1()) global_vars.err << MSG_ERROR << "First operand is Null Pointer\n";
			if (!rel_it->getOp2()) global_vars.err << MSG_ERROR << "Second operand is Null Pointer\n";

			ObjPointer obj = CComPtr<IMgaFCO>(0); obj = rel_it->getOp1();
			//if ( obj == find_obj) 
			if ( std::find( find_obj_vec.begin(), find_obj_vec.end(), obj) != find_obj_vec.end()) 
				rel_it->setOp1( real_obj); 

			obj = CComPtr<IMgaFCO>(0); obj = rel_it->getOp2();
			//if ( obj == find_obj) 
			if ( std::find( find_obj_vec.begin(), find_obj_vec.end(), obj) != find_obj_vec.end()) 
				rel_it->setOp2( real_obj); 

			// obj at this time may be CComPtr<IMgaFCO>(0) (in most case it is)
			obj = CComPtr<IMgaFCO>(0); obj = rel_it->getOp3();
			//if ( obj != CComPtr<IMgaFCO>(0) && obj == find_obj) 
			if ( obj != CComPtr<IMgaFCO>(0) && std::find( find_obj_vec.begin(), find_obj_vec.end(), obj) != find_obj_vec.end()) 
				rel_it->setOp3( real_obj); 

			// added recently, to be tested well <!>
			obj = CComPtr<IMgaFCO>(0); obj = rel_it->getOp4();
			//if ( obj != CComPtr<IMgaFCO>(0) && obj == find_obj) 
			if ( obj != CComPtr<IMgaFCO>(0) && std::find( find_obj_vec.begin(), find_obj_vec.end(), obj) != find_obj_vec.end()) 
				rel_it->setOp4(real_obj); 

			obj = CComPtr<IMgaFCO>(0); obj = rel_it->getOp5();
			//if ( obj != CComPtr<IMgaFCO>(0) && obj == find_obj) 
			if ( obj != CComPtr<IMgaFCO>(0) && std::find( find_obj_vec.begin(), find_obj_vec.end(), obj) != find_obj_vec.end()) 
				rel_it->setOp5(real_obj); 
		}
	}
}


void RawComponent::operandSearchAndReplace( const ObjPointer& find_obj, const ObjPointer& real_obj)
{
	operandSearchAndReplace( std::vector< ObjPointer>( 1, find_obj), real_obj);
}


void RawComponent::removeProxiesAndEquiv()
{
	markEquivEntities();
}


bool RawComponent::nameSelector()
{
	// imagine an fco has several equivalence relationships
	// the set of names that are considered (mainly for historical , but for practical reasons as well)
	// are the names of the 
	//      -non proxy equivalents
	//      -the operator (Equivalence, SameAspect, SameFolder) itself
	// 
	// but beware that, the operator is chosen sometimes as the ''Name responsible''
	// and this pointer is not among the equivalent objects set ( m_equivs ) 
	// -in such cases the original resp pointer remains unchanged
	// -if another name is selected, than the resp pointer is changed 
	//  with the non-proxy equivalent's pointer
	// 
	// the display name can be selected independently from the name, so that it may come
	// from another equivalent than the name comes from

	bool res = true;

	dlg = new NameSpecDlg();

	Entity_Iterator it_1( m_entities.begin());
	for( ; it_1 != m_entities.end(); ++it_1 )
	{
		if( it_1->isDeleted()) continue;

		CComPtr<IMgaFCO> fco( it_1->getPointer());
		CComPtr<IMgaFCO> resp( it_1->getRespPointer());
		
		EquivBag_Iterator it_2 = m_equivBag.find( fco);
		if( it_2 == m_equivBag.end()) continue;
		
		if( !resp) resp = fco;

		// m_equivBag[ fco] already exists , is not empty
		// it_2->first = fco
		// it_2->second = m_equivBag[ fco];
		std::string defname = Util::name( resp); // take its name from its name responsible
		std::string defdispname = "";          // initial value = "". This "" value will always be added as a dispname possibility (see NameSpecDlg::GetDispNames method)
		std::string regname, regdispname;      // the registry contained name
		std::string kind = Util::kind( fco);
		// load information from registry
		if( kind == "Aspect")
		{
			regname = Util::gvbp( AspectRep::getMyRegistry( fco, it_1->getParentFolder()), Any::NameSelectorNode_str);
			regdispname = Util::gvbp( AspectRep::getMyRegistry( fco, it_1->getParentFolder()), Any::DisplayedNameSelectorNode_str);
		}
		else
		{
			regname = Util::gvbp( Any::getMyRegistry( fco, it_1->getParentFolder()), Any::NameSelectorNode_str);
			regdispname = Util::gvbp( Any::getMyRegistry( fco, it_1->getParentFolder()), Any::DisplayedNameSelectorNode_str);
		}

		
		bool is_any_alternative = false;
		bool is_def_among_names = false; // when the equivalance's name is used, that is not among the equivs
		bool is_reg_among_names = false; // check whether the registry value is among the valid choices
		std::set < ObjPointer >::iterator jt = it_2->second.begin();
		for( ; jt != it_2->second.end(); ++jt)
		{
			if( !isProxy( *jt))
			{
				std::string eqname = Util::name( *jt); // the name of one equivalent

				if( eqname == defname)
					is_def_among_names = true;
				else
					is_any_alternative = true;

				if( eqname == regname)
					is_reg_among_names = true;
			}
		}

		if( is_any_alternative)
		{
			CString dd = defname.c_str();
			CString kind = Util::kind( fco).c_str();
			
			if( is_reg_among_names)	// if valid info in registry use it
				dlg->m_dn[ fco] = make_pair( regname, regdispname);
			else					// otherwise use the default name
				dlg->m_dn[ fco] = make_pair( defname, defdispname);

			if( !is_def_among_names)
			{
				dlg->m_map[ fco].insert( resp);
			}
			
			// fill up the equiv pointer map , leaving out proxies
			jt = it_2->second.begin();
			for( ; jt != it_2->second.end(); ++jt)
			{
				if( !isProxy( *jt))
				{
					dlg->m_map[ fco].insert( *jt);
				}
			}
		}
	}

	if( global_vars.silent_mode)
	{
		res = true;
		dlg->m_result = dlg->m_dn;
	}
	else
	{
		res = false;
		if( !dlg->m_dn.empty())	res = dlg->DoModal() == IDOK;
	}

	if( res)
	{
		NameSpecDlg::DEFNAMES_MAP::iterator it_0 = dlg->m_result.begin();
		for( ; it_0 != dlg->m_result.end(); ++it_0)
		{
			CComPtr<IMgaFCO> key_fco = it_0->first;
			std::string newsel_name     = it_0->second.first;	// the newly selected name
			std::string newsel_dispname = it_0->second.second;	//                    display name

			bool found = false;
			Entity_Iterator it_1( m_entities.begin());
			for( ; !found && it_1 != m_entities.end(); ++it_1 )
			{
				if( it_1->isDeleted()) continue;

				if( it_1->getPointer() == key_fco) // found the entity: *it_1
				{
					found = true;

					// search for the object among non-proxy equivalents which has the selected name
					CComPtr<IMgaFCO> newsel_resp; // this will store the new value if found

					// get the equivset of the key_fco
					EquivBag_Iterator it_2 = m_equivBag.find( key_fco);
					if( it_2 != m_equivBag.end()) 
					{
						// find the new resppointer value in the equivBag[key_fco] set: it_2->second
						std::set < ObjPointer >::iterator it_3 = it_2->second.begin();
						for( ; !newsel_resp && it_3 != it_2->second.end(); ++it_3)
						{
							if( !isProxy( *it_3))
							{
								std::string eqname = Util::name( *it_3); // the name of one equivalent

								if( eqname == newsel_name)
									newsel_resp = *it_3;
							}
						}
					}
					else
					{
						ASSERT( 0 ); // the key_fco should have equivalents, thus must be present in the equivBag as a key
						continue;
					}


					// if the pointer having the selected name is found
					// then set it as the new "name responsible" pointer
					// if not found then we leave the default resp pointer 
					// unchanged, since that was the only name coming not
					// from the equivalents, but from the old resp pointer
					if( newsel_resp) // found
					{
						it_1->setRespPointer( newsel_resp); // set the new name resp
					}

					// the dispName has to be set all the time
					it_1->setDispName( newsel_dispname);

					// save back into registry the user selection
					if( Util::kind( key_fco) == "Aspect")
					{
						Util::svbp( AspectRep::getMyRegistry( key_fco, it_1->getParentFolder()), Any::NameSelectorNode_str, newsel_name);
						Util::svbp( AspectRep::getMyRegistry( key_fco, it_1->getParentFolder()), Any::DisplayedNameSelectorNode_str, newsel_dispname);
					}
					else
					{
						Util::svbp( Any::getMyRegistry( key_fco, it_1->getParentFolder()), Any::NameSelectorNode_str, newsel_name);
						Util::svbp( Any::getMyRegistry( key_fco, it_1->getParentFolder()), Any::DisplayedNameSelectorNode_str, newsel_dispname);
					}
				}
			}
			if( !found) 
			{ 
				ASSERT( 0 ); 
			} // the key_fco must be a non-deleted entity in the m_entities
		}
	}

	delete dlg;
	return res;
}


int RawComponent::isProxy( const ObjPointer& ptr)
{
	if( ptr == CComPtr<IMgaFCO>(0)) return 0;
	RealMap_Iterator it = m_realObj.find( ptr);
	if( it != m_realObj.end() && it->second != CComPtr<IMgaFCO>(0)) return 1;//if (m_realObj.find[ ptr] != CComPtr<IMgaFCO>(0)) return 1;
	if( Util::isproxy( ptr)) return 2;

	return 0;
}


bool RawComponent::checkForProxies()
{
	std::vector< ObjPointer> to_delete;
	bool correct = true;
	Entity_Iterator it(m_entities.begin());
	for( ; it != m_entities.end(); ++it)
	{
		if ( it->isDeleted()) continue;

		int res;
		if ( res = isProxy( it->getPointer()))
		{
			if ( res == 1)
				global_vars.err << MSG_ERROR << "Internal error: entity " << it->getPointer() << " is a proxy.";
			else if ( res == 2)
				global_vars.err << MSG_ERROR << "Entity " << it->getPointer() << " is a NULL proxy.";

			//continuing
			global_vars.err << " Disregarding it from the Paradigm sheet.\n";
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

	rel_it = m_equivRelations.begin();
	for( ; rel_it != m_equivRelations.end(); ++rel_it)
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
		rel_it = m_equivRelations.begin();
		while( rel_it != m_equivRelations.end())
		{
			if ( rel_it->getOp1() != *ee &&
				rel_it->getOp2() != *ee &&
				rel_it->getOp3() != *ee &&
				rel_it->getOp4() != *ee &&
				rel_it->getOp5() != *ee )
				++rel_it;
			else
				rel_it = m_equivRelations.erase( rel_it);
		}
	}
	if( !correct)
		global_vars.err << MSG_ERROR << "Some objects/relations disregarded by the Proxy Checker.\n";

	return correct;
}


void RawComponent::inheritancesManager( Relation & rel_it)
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
			}
			else
			{
				if ( base == 0 )
					global_vars.err << MSG_ERROR << "No base peer present in inheritance relation: " << obj1 << " <|---- " << obj2 << "\n";
				if ( derived == 0 )
					global_vars.err << MSG_ERROR << "No derived peer present in inheritance relation: " << obj1 << " <|---- " << obj2 << "\n";
			} // if
		} // if
	} // for inheritance
}


void RawComponent::associationClassManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::ASSOCIATION_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();
		ObjPointer obj3 = rel_it.getOp3();
		// the obj4 points to the connection line between the source and the connector
		// the obj5 points to the connection line between the connector and destination
		CComQIPtr<IMgaConnection> obj4( rel_it.getOp4());
		CComQIPtr<IMgaConnection> obj5( rel_it.getOp5());

		FCO* op1 = m_sheet->findFCO( rel_it.getOp1());
		FCO* op2 = m_sheet->findFCO( rel_it.getOp2());
		FCO* op3 = m_sheet->findFCO( rel_it.getOp3());

		if ( op1 != 0 && op2 != 0 && op3 != 0)
		{
			// asking the rolenames and cardinalities
			std::string src_role = "src", dst_role = "dst";
			std::string src_card = "0..*", dst_card = "0..*";

			src_card = Util::getStrAttr( obj4, "Cardinality");
			dst_card = Util::getStrAttr( obj5, "Cardinality");

			src_role = Util::getStrAttr( obj4, "srcRolename");
			if ( src_role != "" && src_role != "src") 
				global_vars.err << MSG_ERROR << "Incorrect Rolename attribute: <" << src_role << "> of " << obj4 << "\n";

			dst_role = Util::getStrAttr( obj5, "dstRolename");
			if ( dst_role != "" && dst_role != "dst") 
				global_vars.err << MSG_ERROR << "Incorrect Rolename attribute: <" << dst_role << "> of " << obj5 << "\n";


			ConnJoint::SDList list_op1, list_op2;
			list_op1.push_back( op1);
			list_op2.push_back( op2);

			if ( op3->getMyKind() != Any::CONN ) global_vars.err << MSG_ERROR << "How can happen that the association class is Not a Connection.\n";
			ConnectionRep * conn_obj = dynamic_cast< ConnectionRep * > ( op3 );

			ConnJoint assoc( conn_obj,
				list_op1, list_op2, src_role == dst_role,
				src_card, dst_card); 

			if (conn_obj) conn_obj->addJoint( assoc ); // op3 describes the association of op1 and op2
			else global_vars.err << MSG_ERROR << "After dynamic_cast - conn" << obj3 << "\n";
		}
		else if ( obj3 == CComPtr<IMgaFCO>(0) )
			global_vars.err << MSG_ERROR << "Association relation is not complete. Association class missing. Op1: " << obj1 << " Op2: " << obj2 << "\n";
		else 
			global_vars.err << MSG_ERROR << "Association relation is not complete. Some part missing. Op1: " << obj1 << " Op2: " << obj2 << " Association class: " << obj3 << "\n";
	} // if
}


void RawComponent::setMemberManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::SET_MEMBER_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();

		::FCO* set = m_sheet->findFCO( rel_it.getOp1());
		::FCO* member = m_sheet->findFCO( rel_it.getOp2());
		if ( set != 0 && member != 0)
		{
			if ( set->getMyKind() != Any::SET ) global_vars.err  << MSG_ERROR << "Internal error: Not a set on left hand side of set_member relation\n";
			SetRep * set_obj = dynamic_cast< SetRep * > ( set );
			if (set_obj) set_obj->addMember( member);
			else global_vars.err  << MSG_ERROR << "Internal error: After dynamic_cast - set" << obj1 << "\n";

		}
		else
		{
			if ( set == 0 )
				global_vars.err << MSG_ERROR << "No set peer present in set_member relation. " << obj1 << " missing.\n";
			if ( member == 0 )
				global_vars.err << MSG_ERROR << "No member peer present in set_member relation. " << obj2 << " missing.\n";
		} // if
	} // if
}


void RawComponent::refersToManager( Relation & rel_it)
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
				global_vars.err << MSG_ERROR << "Not reference " << obj1 << " referring\n";
			else
				ref_obj->addInitialReferee( elem);
			elem->addRefersToMe( ref_obj);
		}
		else
		{
			if ( elem == 0 )
				global_vars.err << MSG_ERROR << "No referee peer present in RefersTo relation. " << obj1 << " missing.\n";
			if ( ref == 0 )
				global_vars.err << MSG_ERROR << "No reference peer present in RefersTo relation. " << obj2 << " missing.\n";
		} // if
	} // if
}


void RawComponent::containmentManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::CONTAINMENT_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();
		CComQIPtr<IMgaConnection> obj3( rel_it.getOp3());

		::FCO* model = m_sheet->findFCO( rel_it.getOp1());
		::FCO* fco = m_sheet->findFCO( rel_it.getOp2());

		if ( model != 0 && fco != 0)
		{
			ModelRep * model_obj = dynamic_cast< ModelRep * > ( model);
			if (!model_obj || model->getMyKind() != Any::MODEL) 
				global_vars.err << MSG_ERROR << "ERROR: after dynamic_cast - containment - model is 0 / Not model " << obj1 << " contains an FCO\n";

			if ( !obj3) 
				global_vars.err << MSG_ERROR << "ERROR: Null containment line class - containmentManager\n";

			bool is_a_port = Util::getBoolAttr( obj3, "IsPort");
			std::string comp_role = Util::getStrAttr( obj3, "Rolename");
			std::string card = Util::getStrAttr( obj3, "Cardinality");

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
				global_vars.err << MSG_ERROR << "No model peer present in containment relation. " << obj1 << " missing.\n";
			if ( fco == 0 )
				global_vars.err << MSG_ERROR << "No fco peer present in containment relation. " << obj2 << " missing.\n";
		} // if
	} // if
}


void RawComponent::folderContainmentManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::FOLDER_CONTAINMENT_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();
		CComQIPtr<IMgaConnection> obj3( rel_it.getOp3());

		Any* folder = m_sheet->findAny( rel_it.getOp1());
		Any* any = m_sheet->findAny( rel_it.getOp2());
		if ( folder != 0 && any != 0)
		{
			if ( folder->getMyKind() != Any::FOLDER ) global_vars.err << MSG_ERROR << "Not a folder " << obj1 << " contains an FCO\n";

			FolderRep * folder_obj = dynamic_cast< FolderRep * > ( folder );
			if (!folder_obj) global_vars.err << MSG_ERROR << "ERROR after dynamic_cast - folder_containment - folder " << obj1 << " is 0\n";
			
			std::string card = "0..*";//obj3->getAttribute( "Cardinality")->getStringValue();

			if ( any->getMyKind() != Any::FOLDER) 
			{
				::FCO * fco = dynamic_cast< ::FCO *>( any);
				if ( !fco) global_vars.err << MSG_ERROR << "ERROR after dynamic cast - folder containment - fco " << obj2 << " is 0\n";
				else folder_obj->addFCO( fco, card);
			}
			else 
			{
				FolderRep * sub_f = dynamic_cast< FolderRep *>( any);
				if ( !sub_f) global_vars.err << MSG_ERROR << "ERROR after dynamic cast - folder containment - subfolder " << obj2 << " is 0\n";
				else folder_obj->addSubFolderRep( sub_f, card);
			}
		}
		else
		{
			if ( folder == 0 )
				global_vars.err << MSG_ERROR << "No folder peer present in folder_containment relation. " <<  obj1 << " missing.\n";
			if ( any == 0 )
				global_vars.err << MSG_ERROR << "No element peer present in folder_containment relation. " << obj2 << " missing.\n";
		} // if
	} // if
}


void RawComponent::hasAspectManager( Relation & rel_it)
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
				global_vars.err << MSG_ERROR << "ERROR after dynamic_cast - has aspect - aspect " << obj2 << " is 0\n";
			if (!model_obj || !aspect_obj || model->getMyKind() != Any::MODEL ) 
				global_vars.err << MSG_ERROR << "ERROR after dynamic_cast " << (aspect_obj?"aspect is 0":(model_obj?"model is 0":"wrong kind")) << "\n";
			else
				model_obj->addAspect( aspect_obj); //adding the aspect_ptr to the model
		}
		else
		{
			if ( model == 0 )
				global_vars.err << MSG_ERROR << "No model peer present in has_aspect relation. " << obj1 << " missing.\n";
			if ( aspect == 0 )
				global_vars.err << MSG_ERROR << "No aspect peer present in has_aspect relation. " << obj2 << " missing.\n";
		} // if
	} // if
}


void RawComponent::aspectMemberManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::ASPECT_MEMBER_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();

		Any* aspect = m_sheet->findAny( rel_it.getOp1());
		::FCO* member = m_sheet->findFCO( rel_it.getOp2());
		if ( aspect != 0 && member != 0)
		{
			if ( aspect->getMyKind() != Any::ASPECT ) global_vars.err << MSG_ERROR << "Not an aspect " << obj1 << "\n";

			AspectRep * aspect_obj = dynamic_cast< AspectRep * > ( aspect );
			if ( !aspect_obj) global_vars.err << MSG_ERROR << "ERROR after dynamic_cast - aspect member - aspect " << obj1 << " is 0\n";

			if ( rel_it.getOp3() != CComPtr<IMgaFCO>(0) && 
				rel_it.getOp4() != CComPtr<IMgaFCO>(0)) // means a role is only the aspect member
			{
				std::string rolename = Util::getStrAttr( rel_it.getOp3(), "Rolename");
				bool is_a_port = Util::getBoolAttr( rel_it.getOp3(), "IsPort");
				std::string card = Util::getStrAttr( rel_it.getOp3(), "Cardinality");

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
					global_vars.err << MSG_ERROR << "Interal error: No model present in aspect_member relation. " << rel_it.getOp4() << " missing.\n";
			}
			else // means regular aspect membership
				aspect_obj->addFCO( member);
		}
		else
		{
			if ( aspect == 0 )
				global_vars.err << MSG_ERROR << "No aspect peer present in aspect_member relation. " << obj1 << " missing.\n";
			if ( member == 0 )
				global_vars.err << MSG_ERROR << "No member peer present in aspect_member relation. " << obj2 << " missing.\n";
		} // if
	} // if
}


void RawComponent::hasConstraintManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::HAS_CONSTRAINT_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();

		Any* any = m_sheet->findAny( rel_it.getOp1());
		Any* constraint = m_sheet->findAny( rel_it.getOp2());
		if ( any != 0 && constraint != 0)
		{
			ConstraintRep *constraint_obj = dynamic_cast< ConstraintRep * >(constraint);
			if (any && (any->isFCO() || any->getMyKind() == Any::FOLDER)) 
			{
				any->addInitialConstraintRep( constraint_obj);
				constraint_obj->attachedTo();
			}
			else
				global_vars.err << MSG_ERROR << obj2 << " constraint is owned by " << obj1 << " which is neither FCO nor Folder\n";
		}
		else
		{
			if ( any == 0 )
				global_vars.err << MSG_ERROR << "No owner (FCO or Folder) peer present in has_constraint relation. " << obj1 << " missing.\n";
			if ( constraint == 0 )
				global_vars.err << MSG_ERROR << "No Constraint peer present in has_constraint relation. " << obj2 << " missing.\n";
		} // if
	} // if
}


void RawComponent::hasAttributeManager( Relation & rel_it)
{
	if ( rel_it.getOperation() == Relation::HAS_ATTRIBUTE_OP )
	{
		ObjPointer obj1 = rel_it.getOp1();
		ObjPointer obj2 = rel_it.getOp2();

		::FCO* fco = m_sheet->findFCO( rel_it.getOp1());
		Any* attr = m_sheet->findAny( rel_it.getOp2());
		if ( fco != 0 && attr != 0)
		{
			AttributeRep * attr_obj = dynamic_cast< AttributeRep *>( attr);
			fco->addInitialAttribute( attr_obj);
			if ( !attr_obj->isGlobal())
				attr_obj->addOwner( fco);
		}
		else
		{
			if ( fco == 0 )
				global_vars.err << MSG_ERROR << "No fco peer present in has_attribute relation. " << obj1 << " missing.\n";
			if ( attr == 0 )
				global_vars.err << MSG_ERROR << "No attribute peer present in has_attribute relation. " << obj2 << " missing.\n";
		} // if
	} // if
}


/**
 * Does the hard work for the aspects also like: 
 * inserting into model, inquering the aspect members
 */
void RawComponent::CHECK()
{
#ifdef _DEBUG
	Relation_Iterator rel_it = m_relations.begin();
	// check if all the m_relations have their correct number of operands
	for( ; rel_it != m_relations.end(); ++rel_it)
	{
		if (rel_it->getOperation() == Relation::ASSOCIATION_OP)
		{
			bool three_op = rel_it->getOp3() != CComPtr<IMgaFCO>(0);
			if( rel_it->getOp1() == CComPtr<IMgaFCO>(0) || 
				rel_it->getOp2() == CComPtr<IMgaFCO>(0) || 
				rel_it->getOp3() == CComPtr<IMgaFCO>(0) || 
				rel_it->getOp4() == CComPtr<IMgaFCO>(0) || 
				rel_it->getOp5() == CComPtr<IMgaFCO>(0) )
				global_vars.err << MSG_ERROR << "Internal error: Assocation has one operand 0\n";
			Entity ent1 = entitySearch( rel_it->getOp1());
			Entity ent2 = entitySearch( rel_it->getOp2());
			Entity ent3 = entitySearch( rel_it->getOp3());

			ObjPointer o1 = rel_it->getOp1();
				
			ObjPointer ptr, o2 = rel_it->getOp2();

			if ( ent1 == Entity( CComPtr<IMgaFolder>(0), CComPtr<IMgaFCO>(0)) )
			{
				ptr = rel_it->getOp1();
				storeEntity( Entity( CComPtr<IMgaFolder>(0), rel_it->getOp1()));
				if ( ptr != CComPtr<IMgaFCO>(0))
					global_vars.err << "Internal error: Operand 1 of " << rel_it->getOperationStr() << " is not present in Entities\n" <<
					Util::name( ptr) << " : " << Util::kind( ptr) << " has been inserted";
				else
					global_vars.err << "Internal error: Operand 1 of " << rel_it->getOperationStr() << " is null\n";
			}
			if ( ent2 == Entity( CComPtr<IMgaFolder>(0), CComPtr<IMgaFCO>(0)))
			{
				ptr = rel_it->getOp2();
				storeEntity( Entity( CComPtr<IMgaFolder>(0), rel_it->getOp2()));
				if ( ptr != CComPtr<IMgaFCO>(0))
					global_vars.err << "Internal error: Operand 2 of " << rel_it->getOperationStr() << " is not present in Entities\n" << 
					Util::name( ptr) << " : " << Util::kind( ptr) << " has been inserted";
				else
					global_vars.err << "Internal error: Operand 2 of " << rel_it->getOperationStr() << " is null\n";
			}
			if ( ent3 == Entity( CComPtr<IMgaFolder>(0), CComPtr<IMgaFCO>(0)))
			{
				if ( three_op )
				{
					ptr = rel_it->getOp3();
					storeEntity( Entity( CComPtr<IMgaFolder>(0), rel_it->getOp3()));
					global_vars.err << "Internal error: Operand 3 of " << rel_it->getOperationStr() << " is not present in Entities\n" << 
						Util::name( ptr) << " : " << Util::kind( ptr) << " has been inserted";
				}
				else 
				{
					global_vars.err << "Internal error: Association without Connection class: " << Util::name( o1) << " o " << Util::name( o2) << "\n"; 
				}
			}
		}
		else
		{
			if( rel_it->getOp1() == CComPtr<IMgaFCO>(0) ||
				rel_it->getOp2() == CComPtr<IMgaFCO>(0) )
				global_vars.err << "Internal error: " << rel_it->getOperationStr() << " has one operand 0\n";

			Entity ent1 = entitySearch( rel_it->getOp1());
			Entity ent2 = entitySearch( rel_it->getOp2());
			ObjPointer ptr = CComPtr<IMgaFCO>(0);
			if ( ent1 == Entity( CComPtr<IMgaFolder>(0), CComPtr<IMgaFCO>(0)))
			{
				ptr = rel_it->getOp1();
				storeEntity( Entity( CComPtr<IMgaFolder>(0), rel_it->getOp1()));
				if ( ptr != CComPtr<IMgaFCO>(0))
					global_vars.err << "Internal error: Operand 1 of " << rel_it->getOperationStr() << " is not present in Entities\n" << 
					Util::name( ptr) << " : " << Util::kind( ptr) << " has been inserted";
				else
					global_vars.err << "Internal error: Operand 1 of " << rel_it->getOperationStr() + " is null\n"; 
			}
			if ( ent2 == Entity( CComPtr<IMgaFolder>(0), CComPtr<IMgaFCO>(0)))
			{
				ptr = rel_it->getOp2();
				storeEntity( Entity( CComPtr<IMgaFolder>(0), rel_it->getOp2()));
				ObjPointer ptr2 = rel_it->getOp1();
				std::string peer1, peer2;
				if ( ptr2 != CComPtr<IMgaFCO>(0))
					peer1 = Util::name( ptr2) + " " + Util::kind( ptr2);
				if ( rel_it->getOp2())
					peer2 = Util::name( rel_it->getOp2()) + " " + Util::kind( rel_it->getOp2());
				global_vars.err << "Internal error: Operand 2 of " << rel_it->getOperationStr() << " is not present in Entities\n" <<
					Util::name( ptr) << " : " << Util::kind( ptr) << " has been inserted\n" << 
					"Operand1: " << peer1 << "\n" <<
					"Operand2: " << peer2 << "\n";
				
				// try to check the members of a set
				if (rel_it->getOperation() == Relation::HAS_ASPECT_OP )
				{
					// we have an aspect pointed by op2
					ObjPointer t_ptr = rel_it->getOp2();
					ObjPointer obj = t_ptr;
					//BON::Set set = dynamic_cast<BON::Set>(obj);
					CComQIPtr<IMgaSet> set( obj);
					if (!set) global_vars.err << "Internal error: during set manipulation\n";
					
					CComPtr<IMgaFCOs> list;
					COMTHROW( set->get_Members( &list));
					
					std::string mmm;
					long d = 0;
					if( list) COMTHROW( list->get_Count( &d));
					for( long i = 1; i <= d; ++i)
					{
						CComPtr<IMgaFCO> actual;
						COMTHROW( list->get_Item( i, &actual));
						Relation rela( Relation::ASPECT_MEMBER_OP, t_ptr, actual);
						storeRelation( rela);
						mmm += Util::name( actual) + "/" + Util::kind( actual) + "\n";
					}
					global_vars.err << "Internal error: Aspect members are:\n" << mmm << "\n";
				}
			}
			if ( rel_it->getOperation() == Relation::CONTAINMENT_OP ||
				rel_it->getOperation() == Relation::FOLDER_CONTAINMENT_OP )
			{
				if (rel_it->getOp3() == CComPtr<IMgaFCO>(0))
					global_vars.err << "Internal error: (Folder)Containment line object not present in m_relations list\n";
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
					global_vars.err << "Internal error: Same attribute " << Util::name( o2) <<
						" contained twice by " << Util::name( o1) << "\n";
				}
			}
		}
	}
#endif
}
