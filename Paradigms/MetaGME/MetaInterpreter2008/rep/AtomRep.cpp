#include "stdafx.h"

#include "MyUtil.h"
#include "AtomRep.h"
#include "logger.h"
#include "ConstraintRep.h"
#include "ConstraintFuncRep.h"

extern int ind;

AtomRep::AtomRep( IMgaFCO* ptr, IMgaFCO* resp_ptr)
	: FCO( ptr, resp_ptr)
{
}


std::string AtomRep::doDump()
{
	std::string m_ref = askMetaRef();

	std::string mmm = indStr() + "<atom name = \"" + getName() + "\" metaref = \"" + m_ref + "\" ";

	mmm += dumpAttributeList();
	mmm += ">\n";
	++ind;
	mmm += dumpDispName();
	++ind;
	mmm += dumpNamePosition();
	mmm += dumpGeneralPref();
	--ind;
	mmm += dumpConstraints();
	mmm += dumpAttributes();
	++ind;
	mmm += dumpIcon();
	mmm += dumpPortIcon();
	mmm += dumpDecorator();
	mmm += dumpHotspotEnabled();
	mmm += dumpTypeShown();
	mmm += dumpSubTypeIcon();
	mmm += dumpInstanceIcon();
	mmm += dumpNameWrap();
	mmm += dumpNameEnabled();

	--ind;
	--ind;
	mmm += indStr() + "</atom>\n";
	return mmm;
}
