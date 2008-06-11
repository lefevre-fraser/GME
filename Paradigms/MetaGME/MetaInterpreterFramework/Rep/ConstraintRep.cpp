#include "stdafx.h"
#include "BON.h"
#include "BONImpl.h"
#include "ConstraintRep.h"
#include "globals.h"
extern Globals global_vars;


ConstraintRep::ConstraintRep( BON::FCO& ptr) : 
  Any( ptr),
	m_attached( false), m_name(""), m_description(""),
	m_defaultParams(""), m_equation(""), 
	m_priority(0), m_depth(), m_eventMask(0)
{
	if (m_ptr) 
	{
		fetch();
		m_name = Any::getName();
	}
}

ConstraintRep::~ConstraintRep()
{ }


void ConstraintRep::attachedTo()
{
	m_attached = true;
}


bool ConstraintRep::isAttached() const
{
	return m_attached;
}


void ConstraintRep::fetch()
{
	std::string desc = m_ptr->getAttribute("ConstraintDescription")->getStringValue();
	if(desc.empty()) global_vars.err << "No description found for constraint " << getName();
	m_description = desc;

	std::string expr = m_ptr->getAttribute("ConstraintEqn")->getStringValue();
	if(expr.empty()) global_vars.err << "No equation found for constraint " << getName();
	m_equation = expr;

	std::string priority_str = m_ptr->getAttribute("ConstraintPriority")->getStringValue();
	if(sscanf(priority_str.c_str(),"%d",&m_priority) != 1)
		m_priority = 2;
	m_priority = max(0,min(5,m_priority));

	m_depth = m_ptr->getAttribute("Depth")->getStringValue();

	m_eventMask = 0;
	fetchEventAttribute("CloseEvent",OBJEVENT_CLOSEMODEL);
	fetchEventAttribute("NewChildEvent",OBJEVENT_NEWCHILD);
	fetchEventAttribute("LostChildEvent",OBJEVENT_LOSTCHILD);
	fetchEventAttribute("CreateEvent",OBJEVENT_CREATED);
	fetchEventAttribute("DeleteEvent",OBJEVENT_DESTROYED);
	fetchEventAttribute("ConnectEvent",OBJEVENT_CONNECTED);
	fetchEventAttribute("DisconnectEvent",OBJEVENT_DISCONNECTED);
	fetchEventAttribute("ReferenceEvent",OBJEVENT_REFERENCED);
	fetchEventAttribute("UnReferenceEvent",OBJEVENT_REFRELEASED);
	fetchEventAttribute("AddSetEvent",OBJEVENT_SETINCLUDED);
	fetchEventAttribute("RemoveSetEvent",OBJEVENT_SETEXCLUDED);
	fetchEventAttribute("ChangeRelationEvent",OBJEVENT_RELATION);
	fetchEventAttribute("ChangeAttributeEvent",OBJEVENT_ATTR);
	fetchEventAttribute("ChangePropertyEvent",OBJEVENT_PROPERTIES);
	fetchEventAttribute("DeriveEvent",OBJEVENT_SUBT_INST);
	fetchEventAttribute("MoveEvent",OBJEVENT_PARENT);
}


void ConstraintRep::fetchEventAttribute( const std::string& event_name, unsigned int event_flag)
{
	bool flag;
	flag = m_ptr->getAttribute(event_name)->getBooleanValue();
	if ( flag)
		m_eventMask |= event_flag;
}


/*virtual*/ std::string ConstraintRep::getName() const
{
	// if real object (existing in the BON) the constructor has initialized m_name
	// if artificial object then the init() did it
	return m_name;
}


/*virtual*/ std::string ConstraintRep::getDispName() const
{
	return m_description;
}


void ConstraintRep::init( const std::string& name, 
												 int mask, const std::string& depth, int priority, 
												 const std::string& equation, const std::string& disp_name)
{
	m_name = name;
	m_description = disp_name;
	//m_defaultParams = ...
	m_equation = equation;
	m_priority = priority;
	m_depth = depth;
	m_eventMask = mask;
}


//---additional method
std::string ConstraintRep::doDump()
{
	std::string mmm = "";

	char mask[64]; sprintf(mask,"%x", m_eventMask);
	char priority_str[2]; sprintf( priority_str, "%d", m_priority);
	mmm += indStr() + "<constraint name=\"" + m_name + "\" eventmask = \"0x" + std::string(mask) + 
		"\" depth = \"" + m_depth;
	mmm += "\" priority = \"" + std::string(priority_str) + "\">\n";

	++ind;
	mmm += indStr() + "<![CDATA[" + m_equation + "]]>\n";
	mmm += indStr() + "<dispname>" + getDispName() +"</dispname>\n";
	--ind;
	mmm += indStr() + "</constraint>\n";

	return mmm;
}
