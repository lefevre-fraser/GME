#ifndef LOGGER_H
#define LOGGER_H

#include "string"
#include "fstream"

void TO(const char * msg);
void TO(const std::string msg);
void TO(const CString msg);

#endif // LOGGER_H