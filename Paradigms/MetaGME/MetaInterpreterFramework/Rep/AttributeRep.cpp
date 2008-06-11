#include "stdafx.h"
#include "BON.h"
#include "BONImpl.h"
#include "AttributeRep.h"
#include "FCO.h"
#include "globals.h"
extern Globals global_vars;


AttributeRep::AttributeRep( BON::FCO& ptr)
: Any( ptr) 
{ }


AttributeRep::~AttributeRep()
{ }


bool AttributeRep::isGlobal()
{
	return m_ptr->getAttribute("GlobalScope")->getBooleanValue();
}


void AttributeRep::addOwner( FCO * owner)
{
	std::vector<FCO*>::iterator it =
		std::find( m_ownerList.begin(), m_ownerList.end(), owner);

	if ( it == m_ownerList.end()) // not found so insert it
		m_ownerList.push_back( owner);
	else
		global_vars.err << getName() << " attribute owned by " << owner->getName() << " twice\n";
}


int AttributeRep::hasAnyOwner() const
{
	return m_ownerList.size();
}


bool AttributeRep::isViewable()
{
	return m_ptr->getAttribute("IsViewable")->getBooleanValue();
}


std::string AttributeRep::getPrompt()
{
	return m_ptr->getAttribute("Prompt")->getStringValue();
}


std::string AttributeRep::getHelp()
{
	std::string help = m_ptr->getAttribute("Help")->getStringValue();
	return help;
}


EnumAttributeRep::EnumAttributeRep( BON::FCO& ptr)
: Any(ptr), AttributeRep( ptr), m_noOfItems(0), m_noOfDefault(0)
{
	m_items.clear();
	m_itemsVal.clear();
}


bool EnumAttributeRep::getMenuItems()
{
/*
this method is capable of parsing enumerations like
elem1, value1
elem2
elem3, value3
, value4			-error case
elem4,				-error case
*/

	std::string items = m_ptr->getAttribute("MenuItems")->getStringValue();

	items += '\n'; // like an EOF sign
	int len = items.length();

	std::string whitespace = "\r\n\t ";
	int start_i = 0;
	while (start_i < len && whitespace.find(items[start_i]) != std::string::npos )
		++start_i;//skip heading multiple newlines

	int i = start_i, comma_i = 0;
	//TO(items);
	while( i < len )
	{
		if ( items[i] == '\n' && i - start_i > 0) // pass till end of line
		{ 
			if ( comma_i != 0) // there is value also
			{
				int st,end;
				// from start_i, to comma_i
				st = start_i;
				while( st < comma_i && whitespace.find( items[st]) != std::string::npos) ++st; //leading whsp
				end = comma_i-1;
				while( end > start_i && whitespace.find( items[end]) != std::string::npos) --end; //tailing whsp

				if ( end>=st)
					m_items.push_back(items.substr( st, end - st + 1));//m_items.push_back(items.substr( start_i, comma_i - start_i));
				else
					m_items.push_back("Error");
				
				// from comma_i+1 to i
				st = comma_i+1;
				while( st < i && whitespace.find( items[st]) != std::string::npos) ++st; //leading whsp
				end = i;
				while( end > comma_i+1 && whitespace.find( items[end]) != std::string::npos) --end; //tailing whsp
				
				if ( end>=st)
					m_itemsVal.push_back(items.substr( st, end - st + 1));//m_itemsVal.push_back(items.substr( comma_i + 1, i - comma_i - 1));
				else
					m_items.push_back("Error");

				//TO( std::string("K") + items.substr( start_i, comma_i - start_i) +  std::string("V"));
				//TO( std::string("K") + items.substr( comma_i + 1, i - comma_i - 1)+  std::string("V"));
				comma_i = 0;
			}
			else // no comma means no value
			{
				int st,end;
				// from start_i to i
				st = start_i;
				while( st < i && whitespace.find( items[st]) != std::string::npos) ++st; //leading whsp
				end = i;
				while( end > start_i && whitespace.find( items[end]) != std::string::npos) --end; //tailing whsp

				if ( end>=st)
				{
					m_items.push_back(items.substr( st, end - st + 1));//m_items.push_back(items.substr( start_i, i - start_i));
					m_itemsVal.push_back(items.substr( st, end - st + 1));//m_itemsVal.push_back(items.substr( start_i, i - start_i));
				}
				//TO( std::string("K") + items.substr( start_i, i - start_i) + std::string("V"));
				//TO( std::string("K") + items.substr( start_i, i - start_i) + std::string("V"));
			}
			++m_noOfItems; 
			start_i = i+1;
			while (start_i < len && whitespace.find(items[start_i]) != std::string::npos) ++start_i;//skip multiple newlines, tabs, spaces
			i = start_i-1;
		}
		else if ( items[i] == ',') 
		{ 
			comma_i = i;
		}
		++i;
	}

	std::string def_item = m_ptr->getAttribute("DefaultItem")->getStringValue();

	bool found ( false);
	i = 0;
	while (i < m_noOfItems && !found)
	{
		if ( m_items[i] == def_item ) found = true;
		else ++i;
	}

	if (found) m_noOfDefault = i;

	return true;
}


bool BoolAttributeRep::getDefaultValue()
{
	return m_ptr->getAttribute("BooleanDefault")->getBooleanValue();
}


std::string FieldAttributeRep::getDataType()
{
	return m_ptr->getAttribute("DataType")->getStringValue();
}


std::string FieldAttributeRep::getFieldDefault()
{
	return m_ptr->getAttribute("FieldDefault")->getStringValue();
}


int FieldAttributeRep::getMultiLine()
{
	return m_ptr->getAttribute("Multiline")->getIntegerValue();
}
