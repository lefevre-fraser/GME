#ifndef FOLDERREP_H
#define FOLDERREP_H

#include "Any.h"
#include "PartRep.h"
#include "FCO.h"
#include "ConstraintFuncRep.h"
#include "FolderRep.h"
#include "ModelRep.h"
#include "AtomRep.h"
#include "ConnectionRep.h"
#include "SetRep.h"
#include "ReferenceRep.h"
#include "FcoRep.h"

#include "list"
#include "vector"

class FolderRep : virtual public Constrained
{
public: // types
  typedef std::vector<FCO*>::iterator FCO_Iterator;
  typedef std::vector<FolderRep*>::iterator SubFolder_Iterator;
  typedef std::vector<FolderRep*>::const_iterator SubFolder_ConstIterator;

public:
/*
A FolderRep is created by using the id, ptr and resp_ptr which is the object 
selected using the SameFolder Selection Mechanism when SameFolder relation is met.
That is why a folder has to redefine the getName, getDispName operations
*/
  FolderRep( BON::FCO& ptr, BON::FCO& resp_ptr) :
       Any( ptr)
    ,  Constrained( ptr), 
    m_fcoList(), m_fcoCardList(),
    m_subFolderList(), m_subCardList(),
    m_respPointer( resp_ptr)
  { 
  }

  virtual ~FolderRep() 
  { 
    m_fcoList.clear();
    m_fcoCardList.clear();
    m_subFolderList.clear();
    m_subCardList.clear();
  }

  /*virtual*/ Any::KIND_TYPE getMyKind() const { return Any::FOLDER; }
  /*virtual*/ std::string getName() const;
  /*virtual*/ std::string getDispName() const;

  void addFCO( FCO * ptr, const std::string & card);
  bool isFCOContained( FCO * otr);

  void addSubFolderRep( FolderRep * ptr, const std::string & card);
  
protected:
  std::vector<FCO *> m_fcoList;
  std::vector<std::string> m_fcoCardList;

  /**
   * contains all subfolders (including itself)
   */
  std::vector<FolderRep*> m_subFolderList;
  /* Cardinality for the folders above */
  std::vector<std::string> m_subCardList;

  /**
   * This pointer is in charge of the aspect name, 
   * may point to a Folder or a SameFolder operator
   */
  BON::FCO m_respPointer;

private: // forbiding copy
  FolderRep( const FolderRep&);
  const FolderRep& operator=( const FolderRep&);

};
#endif //FOLDERREP_H
