#ifndef MODELREP_H
#define MODELREP_H
#include "Any.h"
#include "AspectRep.h"
#include "RoleRep.h"
#include "FCO.h"

class Sheet;
#include "list"
#include "map"
#include "vector"

class ModelRep : virtual public FCO 
{
public: // types
  // roles
  typedef RoleRep RoleSeriesValue;
  typedef std::vector<RoleSeriesValue> RoleSeries;
  typedef RoleSeries::iterator RoleSeries_Iterator;
  typedef RoleSeries::const_iterator RoleSeries_ConstIterator;
  typedef FCO * RoleMapKey;
  typedef RoleSeries RoleMapValue;
  typedef std::map< RoleMapKey, RoleMapValue> RoleMap;
  typedef RoleMap::iterator RoleMap_Iterator;
  typedef RoleMap::const_iterator RoleMap_ConstIterator;
  // aspects
  typedef std::vector<AspectRep*> AspectRepPtrList;

public:
  //ModelRep() { }
  ModelRep( BON::FCO& ptr) : 
      Any( ptr)
    , Constrained( ptr)
    , FCO( ptr)
  { 
    m_initialRoleMap.clear();
    m_initialAspectList.clear();
  }
  virtual ~ModelRep()
  {
    m_initialRoleMap.clear();
    m_initialAspectList.clear();
  }

  /*virtual*/ Any::KIND_TYPE getMyKind() const { return Any::MODEL; }

  // Roles
  void addRole( RoleMapKey whose, RoleRep& role);
  void initRoles();
  bool getRoles( FCO * ptr, RoleMapValue& map_val) const;

  // Inner Models
  std::vector< ModelRep *> getInnerModels() const;

  // Aspects
  void addAspect( AspectRep * asp);
  const AspectRepPtrList& getAspectRepPtrList() const;

protected:
  RoleMap m_initialRoleMap;
  AspectRepPtrList m_initialAspectList;

private: // forbid copying
  ModelRep( const ModelRep&);
  const ModelRep& operator=( const ModelRep&);

};
#endif //MODELREP_H