#ifndef REFERENCEREP_H
#define REFERENCEREP_H

#include "Any.h"
#include "FCO.h"
#include "vector"

class ReferenceRep : virtual public FCO 
{
public: // types
  typedef std::vector<FCO *> RefereeList;
  typedef std::vector<FCO *>::iterator RefereeList_Iterator;
  typedef std::vector<FCO *>::const_iterator RefereeList_ConstIterator;

public:
  //ReferenceRep() { }
  ReferenceRep( BON::FCO& ptr);
  virtual ~ReferenceRep(); 
  /*virtual*/ Any::KIND_TYPE getMyKind() const { return Any::REF; }

  void addInitialReferee( FCO * refd );
  FCO * getInitialReferee() const;
  const RefereeList& getInitialReferees() const;

  bool checkNotEmpty() const;
  
protected:
  // initialy "this" refers to
  RefereeList m_initialReferees;

private: // forbiding copy
  ReferenceRep( const ReferenceRep&);
  const ReferenceRep& operator=( const ReferenceRep&);

};

#endif //REFERENCEREP_H