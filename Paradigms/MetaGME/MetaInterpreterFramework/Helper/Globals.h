#ifndef GLOBALS_H
#define GLOBALS_H

#include "fstream"
#include "string"

class Globals
{
public:
	Globals(): 
			xmp_file_name("\\Paradigm.xmp"),
			err_file_name("\\Paradigm.xmp.log")
		{ }

	std::ofstream err;
	std::ofstream dmp;

	std::string xmp_file_name;
	std::string err_file_name;

};

#endif // GLOBALS_H