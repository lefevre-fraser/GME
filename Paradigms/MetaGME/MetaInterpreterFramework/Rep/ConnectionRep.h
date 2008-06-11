#ifndef CONNECTIONREP_H
#define CONNECTIONREP_H

#include "FCO.h"
#include "ConnJoint.h"
#include "list"

/** Represents a Connection kind. */
class ConnectionRep : virtual public FCO 
{
public:
  //ConnectionRep() { }
  ConnectionRep( BON::FCO& ptr);
  virtual ~ConnectionRep();

public:
  /*virtual*/ Any::KIND_TYPE getMyKind() const { return Any::CONN; }
  virtual ConnJoint* createJoint
    ( 
      ConnectionRep *, 
      const ConnJoint::SDList& op1, 
      const ConnJoint::SDList& op2,
      bool bidirect, 
      std::string card1 = "", 
      std::string card2 = ""
    );
  virtual void addJoint( ConnJoint * joint);

protected:
  std::list<ConnJoint *> m_jointPtrList;

private: // forbiding copy
  ConnectionRep( const ConnectionRep&);
  const ConnectionRep& operator=( const ConnectionRep&);
};

#endif //CONNECTIONREP_H
