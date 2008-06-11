#ifndef CONSTRAINED_H
#define CONSTRAINED_H

#include "vector"
#include "Any.h"
#include "ConstraintRep.h"

class Constrained : virtual public Any
{
public:
  //Constrained() { }
  Constrained( BON::FCO& ptr);
  virtual ~Constrained();
  typedef std::vector< ConstraintRep* > ConstraintRepPtrList;
  typedef std::vector< ConstraintRep* >::const_iterator ConstraintRepPtrList_ConstIterator;

  // constraints
  void addInitialConstraintRep( ConstraintRep * );
  const ConstraintRepPtrList& getInitialConstraintRepPtrList() const;

protected:
  // initial
  ConstraintRepPtrList m_initialConstraintList;
};

#endif // CONSTRAINED_H