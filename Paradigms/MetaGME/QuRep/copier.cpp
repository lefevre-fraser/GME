#include "stdafx.h"
#include ".\Copier.h"
#include "NullExc.h"
#include "RelationInfo.h"

Copier::Copier( CComPtr<IMgaFCO> p_oldFco, CComPtr<IMgaFCO> p_newFco)
	: m_oldFco( p_oldFco)
	, m_newFco( p_newFco)
{

}

Copier::~Copier(void)
{
}

//static
bool Copier::COMEQUAL( CComPtr<IMgaFCO> p1, CComPtr<IMgaFCO> p2)
{
	CComPtr<IUnknown> u1( p1);
	CComPtr<IUnknown> u2( p2);
	return u1 == u2;
}
//static 
void Copier::name( CComPtr<IMgaFCO> p_oldFco, CComPtr<IMgaFCO> p_newFco)
{
	CComBSTR nm;
	COMTHROW( p_oldFco->get_Name( &nm));
	COMTHROW( p_newFco->put_Name( nm));
}

//static
void Copier::traverseRegNds( CComPtr<IMgaRegNodes>& p_rnds, CComPtr<IMgaFCO>& p_newFco)
{
	long c = 0;
	if( p_rnds) COMTHROW( p_rnds->get_Count( &c));
	for( long i = 1; i <= c; ++i)
	{
		CComPtr<IMgaRegNode> rnd;
		COMTHROW( p_rnds->get_Item( i, &rnd));
		if( !rnd)
			continue;

		CComBSTR path;
		COMTHROW( rnd->get_Path( &path));

		CComBSTR valu;
		COMTHROW( rnd->get_Value( &valu));
		
		long stat; // 0: here, -1: in meta, >=1: inherited
		COMTHROW( rnd->get_Status( &stat));

		if( stat == 0)
			COMTHROW( p_newFco->put_RegistryValue( path, valu));

		CComPtr<IMgaRegNodes> sub_nodes;
		COMTHROW( rnd->get_SubNodes( VARIANT_FALSE, &sub_nodes));

		Copier::traverseRegNds( sub_nodes, p_newFco);
	}
}

//static 
void Copier::regNodes( CComPtr<IMgaFCO> p_oldFco, CComPtr<IMgaFCO> p_newFco)
{
	CComPtr<IMgaRegNodes> rnds;
	p_oldFco->get_Registry( VARIANT_FALSE, &rnds);
	Copier::traverseRegNds( rnds, p_newFco);
}


//static 
void Copier::attribs( CComPtr<IMgaFCO> p_oldFco, CComPtr<IMgaFCO> p_newFco)
{
	CComPtr<IMgaAttributes> attrs;
	COMTHROW( p_oldFco->get_Attributes( &attrs));

	long c = 0;
	if( attrs) COMTHROW( attrs->get_Count( &c));
	for( long i = 1; i <= c; ++i)
	{
		CComPtr<IMgaAttribute> atr;
		COMTHROW( attrs->get_Item( i, &atr));
		if( !atr)
			continue;

		long stat; // 0: here, -1: in meta, >=1: inherited, -2: undefined
		COMTHROW( atr->get_Status( &stat));

		if( stat == 0)
		{
			CComVariant var;
			COMTHROW( atr->get_Value( &var));

			CComPtr<IMgaMetaAttribute> mattr;
			COMTHROW( atr->get_Meta( &mattr));
			
			metaref_type mattr_mref;
			COMTHROW( mattr->get_MetaRef( &mattr_mref));

			CComPtr<IMgaAttribute> peer_attr;
			try // find the counterpart of this attribute owned by p_newFco
			{
				CComPtr<IMgaMetaFCO> newfco_meta;
				COMTHROW( p_newFco->get_Meta( &newfco_meta));
				
				// find out if newfco has an attribute identified by mattr_mref
				CComPtr<IMgaMetaAttribute> new_fco_mattr;
				if( SUCCEEDED( newfco_meta->get_AttributeByRef( mattr_mref, &new_fco_mattr)))
				{
					COMTHROW( p_newFco->get_Attribute( mattr, &peer_attr));
					COMTHROW( peer_attr->put_Value( var));
				}
			}catch( ...)//hresult_exception)
			{
				int k = 0;
				++k;
			}
		}
	}

}

void Copier::copyInnerProperties( CComPtr<IMgaFCO> p_anOldFco, CComPtr<IMgaFCO> p_aNewFco)
{
	// name
	Copier::name( p_anOldFco, p_aNewFco);

	// registry
	Copier::regNodes( p_anOldFco, p_aNewFco);

	// attribute values
	Copier::attribs( p_anOldFco, p_aNewFco);
}

void Copier::task( RelationInfo* p_rels, int p_sz)
{
	CComPtr<IMgaConnPoints> cps;
	COMTHROW( m_oldFco->get_PartOfConns( &cps));
	long c = 0;
	if( cps)
		COMTHROW( cps->get_Count( &c));

	for( long i = 1; i <= c; ++i)
	{
		CComPtr<IMgaConnPoint> cp;
		COMTHROW( cps->get_Item( i, &cp));

		CComPtr<IMgaConnection> conn;
		COMTHROW( cp->get_Owner( &conn));

		CComPtr<IMgaModel> parent;
		COMTHROW( conn->get_ParentModel( &parent));

		if( !parent) 
			throw NullExc( "Null model parent found in Copier::task()");

		CComPtr<IMgaMetaRole> mr;
		COMTHROW( conn->get_MetaRole( &mr));

		CComBSTR conn_kind;
		COMTHROW( mr->get_Name( &conn_kind));

		int found_index = -1;
		for( int j = 0; found_index == -1 && j < p_sz; ++j)
		{
			if( p_rels[j].getRelName() == conn_kind)
				found_index = j;
		}
		
		if( found_index >= 0 && found_index < p_sz) // to be copied
		{
			CComQIPtr<IMgaSimpleConnection> sc( conn);
			if( sc)
			{
				CComPtr<IMgaFCO> newconn;
				CComPtr<IMgaFCO> src, dst;
				sc->get_Src( &src);
				sc->get_Dst( &dst);

				if( COMEQUAL( src, m_oldFco))
				{
					// if connection ran from m_oldFCO and dst
					// then new conn will run from m_newFCO and dst
					
					// certain limitations apply: if Containments were drawn
					// from Models to Fco, and the Model is replaced by an
					// Atom, then the same connection can'be be redrawn again
					// this will be finetuned by the p_canBeSrc
					if( p_rels[ found_index].mayBeSrc())
					{
						COMTHROW( parent->CreateSimpleConn( mr, m_newFco, dst, 0, 0, &newconn));
						if( !newconn)
							throw NullExc( "Could not create connection type in Copier::task()");
					}
				}
				else if( COMEQUAL( dst, m_oldFco))
				{
					// the opposite
					if( p_rels[ found_index].mayBeDst())
					{
						COMTHROW( parent->CreateSimpleConn( mr, src, m_newFco, 0, 0, &newconn));
						if( !newconn)
							throw NullExc( "Could not create connection type in Copier::task()");
					}
				}
				else 
					throw NullExc( "Invalid connection type found in Copier::task()");

				if( newconn)
					copyInnerProperties( CComPtr<IMgaFCO>( conn), newconn);
			}
			else
			{
				int k = 0;
				++k;
				throw NullExc( "Undesired kind of connection in Copier::task()");
			}
		}
	}
}

void Copier::relations()
{
	// AssociationClass = no other class can be than Connection
	// HasAspect        = no other class can be than Model

	RelationInfo rels[] = { 
		  RelationInfo( "SourceToConnector")
		, RelationInfo( "ConnectorToDestination")
		, RelationInfo( "Containment",       true,  false) // runs from Element to Container => any fco can't be a Destination
		, RelationInfo( "SetMembership",     true,  false) // runs form Element to Set       => any fco can't be a Destination
		, RelationInfo( "ReferTo",           false, true ) // runs from Reference to Target  => any fco can't be a Source
		, RelationInfo( "HasAttribute")
		, RelationInfo( "HasConstraint")
		, RelationInfo( "BaseInheritance")
		, RelationInfo( "DerivedInheritance")
		, RelationInfo( "BaseImpInheritance")
		, RelationInfo( "BaseIntInheritance")
		, RelationInfo( "DerivedImpInheritance")
		, RelationInfo( "DerivedIntInheritance")
		, RelationInfo( "EquivLeft")
		, RelationInfo( "EquivRight")
	};

	task( rels, 15); // sizeof( rels)/sizeof( RelationInfo)
}

void Copier::aspMemberships()
{
	CComPtr<IMgaFCOs> aspects;
	COMTHROW( m_oldFco->get_MemberOfSets( &aspects));
	long c = 0;
	COMTHROW( aspects->get_Count( &c));
	for( long i = 1; i <= c; ++i)
	{
		CComPtr<IMgaFCO> aspect;
		COMTHROW( aspects->get_Item( i, &aspect));
		if( !aspect)
			throw NullExc( "Null aspect fco in collection at Copier::aspMemberships()");

		CComQIPtr<IMgaSet> aspect_as_set( aspect);
		if( !aspect_as_set)
			throw NullExc( "Null aspect set in collection at Copier::aspMemberships()");

		// preserve membership status of m_oldFco, by setting as member the m_newFco too
		COMTHROW( aspect_as_set->AddMember( m_newFco));
	}
}

