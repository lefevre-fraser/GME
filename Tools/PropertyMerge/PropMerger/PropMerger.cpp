// PropMerger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Traverser.h"

void exec( const std::string& p_inoutFilePath, const std::string& p_inDirRoot, bool p_h1, bool p_h2)
{
	try
	{
		Traverser * e = new Traverser( p_inoutFilePath, p_inDirRoot, p_h1, p_h2);
		e->exec();
		delete e;
	}
	catch(...)
	{
		std::cout << "Error: Exception caught" << std::endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	if( argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " <file.mga> [-1|-2|-f] [-d inDir]" << std::endl;
		std::cout << "       -1: look for input files in one digit hashed subdirectories" << std::endl;
		std::cout << "       -2: look for input files in two digit hashed subdirectories" << std::endl;
		std::cout << "       -f: look for flat input files in one directory" << std::endl;
		std::cout << "       -d: directory root for the input files. Default: <input file's dir>/clip/" << std::endl;
	}
	else
	{
		std::string inout_file;
		std::string in_dir;

		bool one_dig_subdirs       = false;
		bool two_dig_subdirs       = false;
		bool inout_file_collected  = false;
		bool in_dir_collect_mode   = false;

		for( int i = 1; i < argc; ++i)
		{
			std::string curr( argv[i]);
			if( curr.size() <= 0) continue;

			if( in_dir_collect_mode)
			{
				in_dir = curr;
				in_dir_collect_mode = false;
			}
			else if( curr[0] == '-' || curr[0] == '/')
			{
				if( curr.substr(1) == "1")
					one_dig_subdirs = true;
				else if( curr.substr(1) == "2")
					two_dig_subdirs = true;
				else if( curr.substr(1, 1) == "d" || curr.substr(1, 1) == "D")
					in_dir_collect_mode = true;
			}
			else
			{
				if( !inout_file_collected)
				{
					inout_file = curr;
					inout_file_collected = true;
				}
			}
		}

		// some validation:
		if( one_dig_subdirs && two_dig_subdirs)
		{
			std::cout << "-1 and -2 can't be used in the same time.Defaulting to -1." << std::endl;
			two_dig_subdirs = false;
		}

		//
		exec( inout_file, in_dir, one_dig_subdirs, two_dig_subdirs);
	}

	return 0;
}

