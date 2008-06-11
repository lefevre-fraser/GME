#ifndef ASPECTREP_H
#define ASPECTREP_H

#include "Any.h"
#include "PartRep.h"

#include "map"
#include "vector"
#include "FCO.h"

class PartRep;
class RoleRep;
class ModelRep;

class AspectRep : virtual public Any 
{
public: // types
  typedef std::vector< PartRep > PartRepSeries;
  typedef PartRepSeries::iterator PartRepSeries_Iterator;
  typedef PartRepSeries::const_iterator PartRepSeries_ConstIterator;
  typedef ModelRep* Key;
  typedef std::map< Key, PartRepSeries> ModelPartsMap;
  typedef ModelPartsMap::iterator ModelPartsMap_Iterator;

public:
  AspectRep( BON::FCO& ptr, BON::FCO& resp_ptr);
  ~AspectRep();

  void addFCO( FCO* fco); // to the initial list
  void addRRole( RoleRep & role);

  /*virtual*/ Any::KIND_TYPE getMyKind() const;
  /*virtual*/ std::string getName() const;
  /*virtual*/ std::string getDispName() const;


protected:
  /**
   * inital and final list of FCO-s intended to be part of the Aspect
   *
   */
  std::vector<FCO*> m_fcoInitialList;
  std::vector<RoleRep> m_roleInitialList;

  /**
   * This pointer is in charge of the aspect name, 
   * NOTE: it may be an Aspect or SameAspect BON object
   */
  BON::FCO m_respPointer;

private: // forbiding copy
  AspectRep(const AspectRep&);
  const AspectRep& operator=(const AspectRep&);

};
#endif //ASPECTREP_H
