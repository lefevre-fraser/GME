#ifndef SHEET_H
#define SHEET_H

#include "Any.h"
#include "PartRep.h"
#include "FCO.h"
#include "ConstraintFuncRep.h"
#include "ConstraintRep.h"
#include "FolderRep.h"
#include "ModelRep.h"
#include "AtomRep.h"
#include "ConnectionRep.h"
#include "SetRep.h"
#include "ReferenceRep.h"
#include "FcoRep.h"
#include "AttributeRep.h"

#include "list"
#include "vector"
#include "strstream"

class Sheet;

class Sheet 
{

protected:
  static Sheet * m_theOnlyInstance;
  Sheet();

public:
  //static Sheet * getInstance() ; to be implented in Derived classes
  static bool checkInstance() { return m_theOnlyInstance != 0; }
  virtual ~Sheet();
  virtual bool build() = 0;
  virtual bool finalize();
  void setProjName( const std::string& name);

  virtual FcoRep* createFcoRep( BON::FCO& ptr) ;
  virtual AtomRep* createAtomRep( BON::FCO& ptr) ;
  virtual ModelRep* createModelRep( BON::FCO& ptr) ;
  virtual SetRep* createSetRep( BON::FCO& ptr) ;
  virtual ReferenceRep* createReferenceRep( BON::FCO& ptr) ;
  virtual ConnectionRep* createConnectionRep( BON::FCO& ptr) ;

  virtual AspectRep* createAspectRep( BON::FCO& ptr, BON::FCO& resp_ptr) ;
  virtual FolderRep* createFolderRep( BON::FCO& ptr, BON::FCO& resp_ptr) ;
  virtual ConstraintRep* createConstraintRep( BON::FCO& ptr) ;
  virtual ConstraintFuncRep* createConstraintFuncRep( BON::FCO& ptr) ;
  virtual AttributeRep* createBoolAttributeRep( BON::FCO& ptr) ;
  virtual AttributeRep* createEnumAttributeRep( BON::FCO& ptr) ;
  virtual AttributeRep* createFieldAttributeRep( BON::FCO& ptr) ;

  void addModelRep( ModelRep * ptr); // just moved from protected to public
  void addSetRep( SetRep * ptr);
  void addReferenceRep( ReferenceRep * ptr);
  void addAtomRep( AtomRep * ptr);
  void addConnectionRep( ConnectionRep * ptr);
  void addAspectRep( AspectRep * ptr);
  void addFolderRep( FolderRep * ptr);
  void addConstraintFuncRep( ConstraintFuncRep *ptr);
  void addConstraintRep( ConstraintRep *ptr);
  void addAttributeRep( AttributeRep* ptr);
  void addFcoRep( FcoRep * ptr);

  FCO* findFCO( const BON::FCO& );
  ReferenceRep* findRef( const BON::FCO&);
  Constrained* findConstrained( const BON::FCO&);
  Any* findAny( const BON::FCO&);

protected:
  typedef std::vector<FCO*>::iterator FCO_Iterator;
  typedef std::vector<Any*>::iterator Any_Iterator;

  typedef std::vector<FcoRep*>::iterator FcoRep_Iterator;
  typedef std::vector<AtomRep*>::iterator AtomRep_Iterator;
  
  typedef std::vector<ModelRep*>::iterator ModelRep_Iterator;
  
  typedef std::vector<ConnectionRep*>::iterator ConnectionRep_Iterator;
  typedef std::vector<ReferenceRep*>::iterator ReferenceRep_Iterator;
  typedef std::vector<SetRep*>::iterator SetRep_Iterator;
  typedef std::vector<FolderRep*>::iterator FolderRep_Iterator;
  typedef std::vector<AspectRep*>::iterator AspectRep_Iterator;
  typedef std::vector<ConstraintRep*>::iterator ConstraintRep_Iterator;
  typedef std::vector<ConstraintFuncRep*>::iterator ConstraintFuncRep_Iterator;
  typedef std::vector<AttributeRep*>::iterator AttributeRep_Iterator;

  void addAny( Any * ptr);//<!>

  std::vector<FcoRep*> m_fcoRepList;
  std::vector<AtomRep*> m_atomList;
  std::vector<ModelRep*> m_modelList;
  std::vector<ConnectionRep*> m_connList;
  std::vector<ReferenceRep*> m_refList;
  std::vector<SetRep*> m_setList;

  std::vector<FolderRep*> m_folderList;

  std::vector<AspectRep*> m_aspectList;
  std::vector<ConstraintRep*> m_constraintList;
  std::vector<ConstraintFuncRep*> m_constraintFuncList;
  std::vector<AttributeRep*> m_attributeList;

  std::string m_projName;

  // just moved from private to protected visibility
  void initRoleNames();
  bool doInheritance( FCO::INHERITANCE_TYPE inh_type);

private:

  typedef std::vector< unsigned int > UI_LIST;
  typedef std::vector< unsigned int > CLIQUE_VECTOR;
  typedef std::vector< FCO *> NODE_VECTOR;
  void gatherNodes( std::vector< FCO *>& nodes);
  void assignCliqueId( CLIQUE_VECTOR & clique, const NODE_VECTOR & nodes);
  bool edge( unsigned int i, unsigned int j, const NODE_VECTOR & nodes, FCO::INHERITANCE_TYPE inh_type);
  void vectorCopy( UI_LIST & target, const UI_LIST & source, UI_LIST & duplicates);
  void getChildren( unsigned int base, const NODE_VECTOR & nodes, UI_LIST & children, FCO::INHERITANCE_TYPE inh_type);
  unsigned int howManyCliques( CLIQUE_VECTOR & clique_id);
  void replaceCliqueId( CLIQUE_VECTOR & clique_id, unsigned int id1, unsigned int id2);
};
#endif //SHEET_H
