#ifndef LOGSTREAM_H
#define LOGSTREAM_H

#include <fstream>
#include <string>
#include "MyUtil.h"

class LogStream : public std::ofstream
{
public:
	LogStream();
	~LogStream();
	void flushit();

	// friend put-to operators
	friend LogStream& operator<<( LogStream& s, msgtype_enum msgtype);
	friend LogStream& operator<<( LogStream& s, IMgaFCO* fco);
	friend LogStream& operator<<( LogStream& s, const char * r);
	friend LogStream& operator<<( LogStream& s, const std::string& r);
	friend LogStream& operator<<( LogStream& s, const int i);

	CComPtr<IMgaProject> m_proj;
	msgtype_enum m_msgtype;
	std::string  m_buff;
};

#endif //LOGSTREAM_H
