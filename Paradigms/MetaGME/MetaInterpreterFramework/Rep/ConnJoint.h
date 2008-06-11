#ifndef CONNJOINT_H
#define CONNJOINT_H

#include "Any.h"
#include "RoleRep.h"
#include "FCO.h"

class Sheet;
class ConnectionRep;

#include "list"

class ConnJoint 
{
public: // types
  typedef std::vector< FCO *> SDList;
  typedef std::vector< FCO *>::iterator SDList_Iterator;
  typedef std::vector< FCO *>::const_iterator SDList_ConstIterator;

public:
  static const std::string m_srcLabel;
  static const std::string m_dstLabel;

  ConnJoint( 
    ConnectionRep *, const SDList& op1, const SDList& op2, bool bidirect,
    std::string card1 = "", std::string card2 = ""
    );
  ConnJoint( const ConnJoint& peer);
  const ConnJoint& operator=( const ConnJoint& peer);
  virtual ~ConnJoint();
  virtual ConnJoint * clone() const;

  const SDList& getOp1() const;
  const SDList& getOp2() const;
  bool isBidirect() const;

protected:

  // pointer to the container Connection, this ConnJoint is part of
  ConnectionRep * m_connPtr;

  // initial 
  SDList m_oper1;
  SDList m_oper2; 
  
  // if label1 == label2
  bool m_bidirect;

  // cardinality
  std::string m_oper1Card;
  std::string m_oper2Card;
};

#endif //CONNJOINT_H
