#ifndef ENTITY_H
#define ENTITY_H

#include "BON.h"

class Entity
{

public:
	explicit Entity( const BON::Folder& parent, const BON::Object& p, const BON::Object& p2 = BON::Object())
		: m_pointer( p), m_respPointer( p2), m_parentFolder( parent) { }

	Entity( const Entity & operand )
		: m_pointer(operand.m_pointer)
		, m_respPointer( operand.m_respPointer)
		, m_parentFolder( operand.m_parentFolder)
	{ }

	const Entity& operator=(const Entity& operand) 
	{ 
		if (&operand == this) return *this;

		m_pointer = operand.m_pointer;
		m_respPointer = operand.m_respPointer;
		m_parentFolder = operand.m_parentFolder;
		
		return *this;
	}

	~Entity() { }

	bool operator==( const Entity& peer) { return (m_pointer == peer.m_pointer) && (m_respPointer == peer.m_respPointer) && (m_parentFolder == peer.m_parentFolder); }
	bool operator!=( const Entity& peer) { return !(*this==peer); }

	BON::Object getPointer() const { return m_pointer; }
	BON::Object getRespPointer() const { return m_respPointer; }
	BON::Folder getParentFolder() const { return m_parentFolder; }
	void setPointer( const BON::Object& p) { m_pointer = p; }
	void setRespPointer( const BON::Object& r_p) { m_respPointer = r_p; }
	void setParentFolder( const BON::Folder& pf) { m_parentFolder = pf; }

private:
	BON::Object m_pointer;
	BON::Object m_respPointer;
	BON::Folder m_parentFolder;
};


#endif // ENTITY_H


