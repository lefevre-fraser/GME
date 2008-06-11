#ifndef ATOMREP_H
#define ATOMREP_H
#include "Any.h"
#include "RoleRep.h"
#include "FCO.h"

/** Represents an Atom kind in a model. */
class AtomRep : virtual public FCO 
{
public:
  //AtomRep() { }
  AtomRep( BON::FCO& ptr);
  virtual ~AtomRep();
  /*virtual*/ Any::KIND_TYPE getMyKind() const { return Any::ATOM; }

private: // forbiding copy
  AtomRep( const AtomRep&);
  const AtomRep& operator=( const AtomRep&);

};
#endif //ATOMREP_H
