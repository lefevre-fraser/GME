#ifndef CONSTRAINTREP_H
#define CONSTRAINTREP_H

#include "Any.h"
#include "string"

class ConstraintRep : public Any
{
public:
  //ConstraintRep() { }
  ConstraintRep( BON::FCO& ptr);
  virtual ~ConstraintRep();
  /*virtual*/ std::string getName() const;
  /*virtual*/ std::string getDispName() const;
  void init( const std::string&, int m, const std::string& depth, int p, const std::string&, const std::string&);
  Any::KIND_TYPE getMyKind() const { return Any::CONSTRAINT; }

  void attachedTo();
  bool isAttached() const;

  //---additional method
  std::string doDump();
protected:
  void fetchEventAttribute( const std::string& event_name, unsigned int event_flag);
  void fetch();

  /**
   * attached: means is used by some FCO so upon dumping 
   *    is dumped as local constraint of that FCO
   *  if not attached then it will be dumped along with global attributes
   */
  bool m_attached;
  std::string m_name; // used because artificial constraints must have a name
  std::string m_description;
  std::string m_defaultParams;
  std::string m_equation;
  int m_priority;
  std::string m_depth;
  int m_eventMask;

private: // forbiding copy
  ConstraintRep( const ConstraintRep&);
  const ConstraintRep& operator=( const ConstraintRep &);

};
#endif //CONSTRAINTREP_H
