#ifndef FCOREP_H
#define FCOREP_H
#include "Any.h"
#include "RoleRep.h"
#include "FCO.h"

class FcoRep : virtual public FCO 
{
public:

  FcoRep( BON::FCO& ptr) : 
      Any( ptr)
    , Constrained( ptr)
    , FCO( ptr) 
  { }
  virtual ~FcoRep() { }
  Any::KIND_TYPE getMyKind() const { return Any::FCO_REP; }

private: // forbiding copy
  FcoRep( const FcoRep&);
  const FcoRep& operator=( const FcoRep&);
};
#endif //FCOREP_H