#include "stdafx.h"

#include "myutil.h"
#include "AtomRep.h"
#include "logger.h"

AtomRep::AtomRep( IMgaFCO* ptr, IMgaFCO* resp_ptr)
	: FCO( ptr, resp_ptr)
{ 
}

std::string AtomRep::doDump()
{
	std::string h_file, c_file;

	dumpPre( h_file, c_file);

	dumpFCO( h_file, c_file);

	h_file += hideAndExpose();

	dumpPost( h_file, c_file);

	sendOutH( h_file);//DMP_H( h_file);
	sendOutS( c_file);//DMP_S( c_file);

	return "";
}
