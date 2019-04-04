#include "stdafx.h"
#include "StdLogger.h"
#include <iostream>
#include <string>

StdLogger::StdLogger(){ }
StdLogger::~StdLogger(){ }

void StdLogger::writeInternal(const char* buf, int len) {
	std::string str(buf, len);
	std::cout << str << std::flush;
}
