#ifndef RELATION_H
#define RELATION_H

#include "string"
#include "Myutil.h"


class Relation
{
public:
	// basic relations 
	static const std::string containment_str;//"Containment"
	static const std::string folder_containment_str;//"FolderContainment"
	static const std::string set_membership_str;//"SetMembership"
	static const std::string refer_to_str;//"ReferTo"
	static const std::string has_aspect_str;//"HasAspect"
	static const std::string aspect_member_str;//"AspectMember"
	static const std::string has_constraint_str;//"HasConstraint"
	static const std::string has_attribute_str;//"HasAttribute"

	// complex relations
	static const std::string connector_str;//("Connector");
	static const std::string connector_src;//("SourceToConnector");
	static const std::string connector_dst;//("ConnectorToDestination");
	static const std::string connector_descr;//("AssociationClass");

	static const std::string equivalence_str;//("Equivalence");
	static const std::string equivalence_right;//("EquivRight");
	static const std::string equivalence_left;//("EquivLeft");

	static const std::string inheritance_str;//("Inheritance");
	static const std::string inheritance_base;//("BaseInheritance");
	static const std::string inheritance_derived;//("DerivedInheritance");

	static const std::string int_inheritance_str;//("InterfaceInheritance");
	static const std::string int_inheritance_base;//("BaseIntInheritance");
	static const std::string int_inheritance_derived;//("DerivedIntInheritance");

	static const std::string imp_inheritance_str;//("ImplementationInheritance");
	static const std::string imp_inheritance_base;//("BaseImpInheritance");
	static const std::string imp_inheritance_derived;//("DerivedImpInheritance");

	static const std::string same_folder_str;//("SameFolder");
	static const std::string same_folder_right;//("SameFolderRight");
	static const std::string same_folder_left;//("SameFolderLeft");

	static const std::string same_aspect_str;//("SameAspect");
	static const std::string same_aspect_right;//("SameAspectRight");
	static const std::string same_aspect_left;//("SameAspectLeft");


	typedef enum
	{
		// connections which make direct relationship
		CONTAINMENT_OP,
		FOLDER_CONTAINMENT_OP,
		SET_MEMBER_OP,
		REFER_TO_OP,
		HAS_ASPECT_OP,
		ASPECT_MEMBER_OP,
		HAS_CONSTRAINT_OP,
		HAS_ATTRIBUTE_OP,
		// connections which establish indirect relationship
		ASSOCIATION_OP, // replaces CONNECTOR
		EQUIVALENCE_OP, // replaces EquivLeft, EquivRight // elim
		INHERITANCE_OP, 
		INT_INHERITANCE_OP,
		IMP_INHERITANCE_OP,
		SAME_FOLDER_OP,	// elim
		SAME_ASPECT_OP  // elim
	} OPER_TYPE;

	inline std::string getOperationStr() const {
		const std::string strings[] = {
			"CONTAINMENT_OP",
			"FOLDER_CONTAINMENT_OP", 
			"SET_MEMBER_OP",
			"REFER_TO_OP",
			"HAS_ASPECT_OP",
			"ASPECT_MEMBER_OP",
			"HAS_CONSTRAINT_OP",
			"HAS_ATTRIBUTE_OP",
			"ASSOCIATION_OP", 
			"EQUIVALENCE_OP", 
			"INHERITANCE_OP",
			"INT_INHERITANCE_OP",
			"IMP_INHERITANCE_OP",
			"SAME_FOLDER_OP",
			"SAME_ASPECT_OP"
		};
		return strings[m_operation]; 
	}

	inline OPER_TYPE getOperation() { return m_operation; }
	inline IMgaFCO* getOp1() { return m_operand1; }
	inline IMgaFCO* getOp2() { return m_operand2; }
	inline IMgaFCO* getOp3() { return m_operand3; }
	inline IMgaFCO* getOp4() { return m_operand4; }
	inline IMgaFCO* getOp5() { return m_operand5; }

	inline void setOperation( OPER_TYPE oper_t) { m_operation = oper_t; }
	inline void setOp1(IMgaFCO* op_1) { m_operand1 = op_1; }
	inline void setOp2(IMgaFCO* op_2) { m_operand2 = op_2; }
	inline void setOp3(IMgaFCO* op_3) { m_operand3 = op_3; }
	inline void setOp4(IMgaFCO* op_4) { m_operand4 = op_4; }
	inline void setOp5(IMgaFCO* op_5) { m_operand5 = op_5; }

	explicit Relation( 
		OPER_TYPE oper_t, 
		IMgaFCO* operd1 = (IMgaFCO*)0,
		IMgaFCO* operd2 = (IMgaFCO*)0,
		IMgaFCO* operd3 = (IMgaFCO*)0,
		IMgaFCO* operd4 = (IMgaFCO*)0,
		IMgaFCO* operd5 = (IMgaFCO*)0)
		:	m_operation( oper_t),
		m_operand1( operd1),
		m_operand2( operd2),
		m_operand3( operd3),
		m_operand4( operd4),
		m_operand5( operd5) { };

	~Relation() { }
	
	Relation( const Relation & operand):
		m_operation( operand.m_operation),
		m_operand1( operand.m_operand1),
		m_operand2( operand.m_operand2),
		m_operand3( operand.m_operand3),
		m_operand4( operand.m_operand4),
		m_operand5( operand.m_operand5) { };
	
	const Relation & operator=(const Relation & operand)
	{
		if ( this == &operand) return *this;
		m_operation = operand.m_operation;
		m_operand1 = operand.m_operand1;
		m_operand2 = operand.m_operand2;
		m_operand3 = operand.m_operand3;
		m_operand4 = operand.m_operand4;
		m_operand5 = operand.m_operand5;
		return *this;
	}

	bool operator==( const Relation& peer) 
	{
		return (m_operation==peer.m_operation) && 
			(m_operand1 == peer.m_operand1) && 
			(m_operand2 == peer.m_operand2) &&
			(m_operand3 == peer.m_operand3) && 
			(m_operand4 == peer.m_operand4) &&
			(m_operand5 == peer.m_operand5);
	}

	bool operator<( const Relation& peer) const
	{
		if ( m_operation != peer.m_operation) return m_operation < peer.m_operation;
		
		int k;
		k = Util::name( m_operand1).compare( Util::name( peer.m_operand1));
		if( k != 0) return k < 0;
		k = Util::name( m_operand2).compare( Util::name( peer.m_operand2));
		if( k != 0) return k < 0;
		k = Util::name( m_operand3).compare( Util::name( peer.m_operand3));
		return ( k < 0);
	}

private:
	OPER_TYPE m_operation;
	IMgaFCO* m_operand1;
	IMgaFCO* m_operand2;
	IMgaFCO* m_operand3;
	IMgaFCO* m_operand4;
	IMgaFCO* m_operand5;
};


#endif //RELATION_H


