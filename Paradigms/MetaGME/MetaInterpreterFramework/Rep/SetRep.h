#ifndef SETREP_H
#define SETREP_H

#include "BON.h"
#include "BONImpl.h"
#include "Any.h"
#include "FCO.h"
#include "ModelRep.h"
#include "logger.h"

class SetRep : virtual public FCO 
{
public: // types
  typedef std::vector<FCO*> SetMemberList;
  typedef std::vector<FCO*>::iterator SetMemberList_Iterator;
  typedef std::vector<FCO*>::const_iterator SetMemberList_ConstIterator;

public:
  //SetRep() { }
  SetRep( BON::FCO& ptr) :
      Any( ptr)
    , Constrained( ptr)
    , FCO( ptr)
    , m_memberList()
  { }

  virtual ~SetRep()
  { 
    m_memberList.clear();
  }

  /*virtual*/ Any::KIND_TYPE getMyKind() const { return Any::SET; }

  // adds new elements to the m_memberList vector
  void addMember( FCO * member);

protected:
  // stores those FCO-s which are in SET_MEMBER relationship with (*this)
  SetMemberList m_memberList;

private: // forbiding copy
  SetRep( const SetRep&);
  const SetRep& operator=( const SetRep&);
};

#endif //SETREP_H
