#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "Any.h"
#include "logger.h"
class FCO;

class AttributeRep : virtual public Any
{
public:
  typedef enum {
    ENUM,
    BOOL,
    FIELD
  } ATTR_TYPE;

  //AttributeRep() { }
  AttributeRep( BON::FCO& ptr);
  virtual ~AttributeRep();
  /*virtual*/ Any::KIND_TYPE  getMyKind() const { return Any::ATTRIBUTE; }

  virtual ATTR_TYPE getType() = 0;

  void addOwner( FCO * owner_fco);
  int hasAnyOwner() const;
  bool isGlobal();

  bool isViewable();
  std::string getPrompt();
  std::string getHelp();

protected:
  std::vector<FCO*> m_ownerList;

private:
  AttributeRep( const AttributeRep&);
  const AttributeRep& operator=( const AttributeRep &);
};


class EnumAttributeRep : virtual public AttributeRep
{
public:
  EnumAttributeRep( BON::FCO& ptr);
  virtual ~EnumAttributeRep() { }
  ATTR_TYPE getType() { return ENUM; }

  // methods
  bool getMenuItems();

protected:
  std::vector<std::string> m_items;
  std::vector<std::string> m_itemsVal;
  int m_noOfItems;
  int m_noOfDefault;
};

class BoolAttributeRep : virtual public AttributeRep
{
public:
  BoolAttributeRep( BON::FCO& ptr): Any(ptr), AttributeRep( ptr) { }
  virtual ~BoolAttributeRep() { }
  ATTR_TYPE getType() { return BOOL; }

  // methods
  bool getDefaultValue();

};

class FieldAttributeRep : virtual public AttributeRep
{
public:
  FieldAttributeRep( BON::FCO& ptr): Any(ptr), AttributeRep( ptr) { }
  virtual ~FieldAttributeRep() { }
  ATTR_TYPE getType() { return FIELD; }

  // methods
  std::string getDataType();
  std::string getFieldDefault();
  int getMultiLine();
};

#endif // ATTRIBUTE_H

