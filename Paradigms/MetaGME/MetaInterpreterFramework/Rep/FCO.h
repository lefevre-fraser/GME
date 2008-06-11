#ifndef FCO_H
#define FCO_H

#include "Any.h"
#include "FCO.h"
#include "AttributeRep.h"
#include "Constrained.h"

#include "vector"
#include "string"
#include "map"

class ModelRep;
class ReferenceRep;
#include "RoleRep.h"

class FCO : virtual public Constrained
{
public: // typedefs
  typedef std::vector<ModelRep *> ModelRepPtrList;
  typedef std::vector<ModelRep *>::iterator ModelRepPtrList_Iterator;
  typedef std::vector<ModelRep *>::const_iterator ModelRepPtrList_ConstIterator;

  typedef std::vector<ReferenceRep *> ReferenceRepList;
  typedef std::vector<ReferenceRep *>::const_iterator ReferenceRepList_ConstIterator;
  typedef std::vector<ReferenceRep *>::iterator ReferenceRepList_Iterator;

  typedef std::vector<AttributeRep *> AttributeRepPtrList;
  typedef std::vector<AttributeRep *>::iterator AttributeRepPtrList_Iterator;
  typedef std::vector<AttributeRep *>::const_iterator AttributeRepPtrList_ConstIterator;

  typedef enum
  {
    REGULAR,
    INTERFACE,
    IMPLEMENTATION,
    NUMBER_OF_INHERITANCES // = 3
  } INHERITANCE_TYPE;

public:
  //FCO() { }
  FCO( BON::FCO& ptr);
  virtual ~FCO(); 
  virtual KIND_TYPE getMyKind() const = 0;

  // abstract
  bool isAbstract() const;
  void abstract( bool is);

  // attributes of "this"
  void addInitialAttribute( AttributeRep * attr);
  const AttributeRepPtrList& getInitialAttributeRepPtrList() const;

  // stores the references that refer to "this"
  void addRefersToMe( ReferenceRep * ref_obj);
  // gives back the reference list
  const ReferenceRepList& getReferences() const;
  
  // stores the information that this is part of a ModelRep
  void iAmPartOf(ModelRep * mod_ptr); // nn

  // which models is this part of
  const ModelRepPtrList& modelsIAmPartOf(); // nn

  bool amIPartOf(const ModelRep * mod_ptr) const; // nn

  // checker if this is part of any model
  bool checkIsPartOf(); // nn



  //
  // Inheritance related methods
  //

  // checker
  bool checkInheritance();

  // adds one parent to the parent list
  void addParent( INHERITANCE_TYPE type, FCO * ptr);
  // adds one child to the children list
  void addChild( INHERITANCE_TYPE type,  FCO * ptr);
  // get all parents
  const std::vector<FCO *>&  getParents( INHERITANCE_TYPE type);
  // get all children
  const std::vector<FCO *>& getChildren( INHERITANCE_TYPE type);

  // sets the Ancestors and Descendants lists (currently only the INTERFACE and IMPLEMENTATION)
  void setAncestors( INHERITANCE_TYPE type, const std::vector<FCO*> &);
  void setDescendants( INHERITANCE_TYPE type, const std::vector<FCO*> &);

  // finds out if "this" has "par" as a "type" parent (permissive: if INTERFACE is asked about a regular base class true is given back) 
  bool hasParent( const FCO * par, INHERITANCE_TYPE type) const;

  // finds out if "this" has "par" exactly a "type" parent
  bool hasExactParent( const FCO * par, INHERITANCE_TYPE type) const;

  std::vector<FCO *> getAllChildren();
  std::vector<FCO *> getAllParents();

  std::vector<FCO *> getAllAncestors();
  std::vector<FCO *> getAllDescendants();


  // the desc's/ancest's who share the same intface (REGULAR and INTERFACE combined)
  void getIntDescendants( std::vector<FCO*> & descendants) const;
  void getIntAncestors( std::vector<FCO*> & ancestors) const;

  // the desc's/ancest's who should have the same constraints and attributes (REGULAR and IMPLEMENTATION combined)
  void getImpDescendants( std::vector<FCO*> & descendants) const;
  void getImpAncestors( std::vector<FCO*> & ancestors) const;

protected:
  // the IsAbstract attribute value
  bool m_isAbstract;

  // attributes
  AttributeRepPtrList m_initialAttributeList;

  // store the list of references which refer to this
  std::vector<ReferenceRep *> m_references;

  // models this FCO is Part OF (Containment)
  ModelRepPtrList m_partOf;

  // stores the direct descendant list according to 
  // Regular, Interface and Interface inheritance types
  std::vector<FCO *> m_childList[ NUMBER_OF_INHERITANCES ];
  
  // stores the direct ancestors
  std::vector<FCO *> m_parentList[ NUMBER_OF_INHERITANCES ];

  // stores all ancestors : currently REGULAR is empty
  std::vector<FCO*> m_ancestors[ NUMBER_OF_INHERITANCES ];

  // stores all descendants : currently REGULAR is empty
  std::vector<FCO*> m_descendants[ NUMBER_OF_INHERITANCES ];

private: // forbiding copy
  FCO( const FCO &);
  const FCO& operator=( const FCO&);

};
#endif //FCO_H
