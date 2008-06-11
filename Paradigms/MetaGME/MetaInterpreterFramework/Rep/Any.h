#ifndef ANY_H
#define ANY_H

#include "BON.h"
#include "BONImpl.h"

#include "Any.h"
#include "string"
#include "vector"
#include "logger.h"

/** This class is the abstract base of all kinds of parts/FCOs that can occur during a modeling process. */
class Any;

class AnyLexicographicSort
{
public:
  bool operator()( Any * op1, Any * op2) const;
};


class Any 
{
public: // types
  typedef enum
  {
    ATOM,
    MODEL,
    CONN,
    SET,
    REF,
    FCO_REP, // abstract term only
    ASPECT,
    FOLDER,
    CONSTRAINT,
    CONSTRAINTFUNC,
    ATTRIBUTE
  } KIND_TYPE;

  const static std::string KIND_TYPE_STR[];/* =
    {
    "ATOM", // defined in Any.cpp If the order changes update there please
    "MODEL",
    "CONN",
    "SET",
    "REF",
    "FCO",
    "ASPECT",
    "FOLDER",
    "CONSTRAINT",
    "CONSTRAINFUNC",
    "ATTRIBUTE"
    };*/

public:
  //Any() { }
  Any( BON::FCO& ptr): m_ptr( ptr) { }
  virtual ~Any() { }

public: 
  virtual KIND_TYPE getMyKind() const = 0;
  bool isFCO();

  virtual std::string getName() const;
  virtual std::string getDispName() const;

  void setPtr( BON::FCO& ptr) { m_ptr = ptr; }
  BON::FCO getPtr() const { return m_ptr; }

  BON::Folder getParentFolder() const { return m_parentFolder; }
  void setParentFolder( const BON::Folder& folder) { m_parentFolder = folder; }

  std::string getMyPrefix() const;
  BON::RegistryNode getMyRegistry() const;

protected:
  // pointer of the BON object
  BON::FCO m_ptr;

  // pointer of the parent folder
  BON::Folder m_parentFolder;

private: // forbiding copy
  Any( const Any&);
  const Any& operator=( const Any&);
};

#endif //ANY_H
