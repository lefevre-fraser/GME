#ifndef ATOMREP_H
#define ATOMREP_H
#include "Any.h"
#include "RoleRep.h"
#include "FCO.h"

/** Represents an Atom kind in a model. */
class AtomRep : public FCO 
{
public:
	AtomRep( IMgaFCO* ptr, IMgaFCO* resp_ptr);

	/*virtual*/ std::string doDump();

	inline Any::KIND_TYPE getMyKind() const { return Any::ATOM; }


private: // forbiding copy
	AtomRep( const AtomRep&);
	const AtomRep& operator=( const AtomRep&);

};
#endif //ATOMREP_H
