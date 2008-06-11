#include "stdafx.h"
#include "BON.h"
#include "BONImpl.h"
#include "Any.h"


//---this is an additional method
bool AnyLexicographicSort::operator()( Any * op1, Any * op2) const
{
  std::string s1 = op1->getName();
  std::string s2 = op2->getName();
  return ( s1.compare(s2) < 0);
}


/*static*/ const std::string Any::KIND_TYPE_STR[] =
{
  "ATOM",
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
};


bool Any::isFCO()
{
  bool fco = false;
  fco = (getMyKind() == ATOM ||
    getMyKind() == MODEL ||
    getMyKind() == CONN ||
    getMyKind() == SET ||
    getMyKind() == REF ||
    getMyKind() == FCO_REP);
  return fco;
}


std::string Any::getName() const
{
  if ( this->m_ptr)
  {
    return m_ptr->getName();
  }
  return "NullPtrError";
}


std::string Any::getDispName() const
{
  if ( this->m_ptr)
  {
    return m_ptr->getAttribute("DisplayedName")->getStringValue();
  }
  return "NullPtrError";
}


std::string Any::getMyPrefix() const
{
  if ( this->m_ptr)
  {
    std::string id = m_ptr->getID();
    std::string name = m_ptr->getName();
    return id + ":" + name;
  }
  throw "Error: inquiring prefix for a null object\n";
  return "Error\n";
}


BON::RegistryNode Any::getMyRegistry() const
{
  if ( this->m_ptr && this->m_parentFolder)
  {
    return m_parentFolder->getRegistry()->getChild( getMyPrefix());
  }
  throw 1;
}


