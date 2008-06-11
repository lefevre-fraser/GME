#include "stdafx.h"
#include "logger.h"

#include "string"

void TO(const char * msg) { AfxMessageBox(msg); }
void TO(const CString msg) { AfxMessageBox(msg); }
void TO(const std::string msg) { AfxMessageBox(msg.c_str()); }


