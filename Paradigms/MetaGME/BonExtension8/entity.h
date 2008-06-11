#ifndef ENTITY_H
#define ENTITY_H

#include "MyUtil.h"

class Entity
{

public:
	explicit Entity( IMgaFolder* parent, IMgaFCO* p, IMgaFCO* p2 = (IMgaFCO*)0)
		: m_pointer( p), m_respPointer( p2), m_parentFolder( parent), m_deleted( false) { }

	Entity( const Entity & operand )
		: m_pointer(operand.m_pointer)
		, m_respPointer( operand.m_respPointer)
		, m_parentFolder( operand.m_parentFolder)
		, m_deleted( operand.m_deleted)
	{ }

	const Entity& operator=(const Entity& operand) 
	{ 
		if (&operand == this) return *this;

		m_pointer = operand.m_pointer;
		m_respPointer = operand.m_respPointer;
		m_parentFolder = operand.m_parentFolder;
		m_deleted = operand.m_deleted;
		
		return *this;
	}

	~Entity() { }

	bool operator==( const Entity& peer) { return (m_pointer == peer.m_pointer) && (m_respPointer == peer.m_respPointer) && (m_parentFolder == peer.m_parentFolder) && (m_deleted == peer.m_deleted); }
	bool operator!=( const Entity& peer) { return !(*this==peer); }
	bool operator<( const Entity& peer) const
	{
		IMgaFCO* f1 ( getPointer());
		IMgaFCO* f2 ( peer.getPointer());
		return ( Util::name( f1).compare( Util::name( f2)) < 0);
	}

	IMgaFCO* getPointer() const { return m_pointer; }
	IMgaFCO* getRespPointer() const { return m_respPointer; }
	IMgaFolder* getParentFolder() const { return m_parentFolder; }
	void setPointer( IMgaFCO* p) { m_pointer = p; }
	void setRespPointer( IMgaFCO* r_p) { m_respPointer = r_p; }
	void setParentFolder( IMgaFolder* pf) { m_parentFolder = pf; }
	bool isDeleted() const { return m_deleted; }
	void deleted( const bool val) { m_deleted = val; }

//private:
	IMgaFCO* m_pointer;
	IMgaFCO* m_respPointer;
	IMgaFolder* m_parentFolder;
	bool m_deleted;
};


#endif // ENTITY_H


