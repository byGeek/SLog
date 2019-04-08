// SLog.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "log_api.h"
#include "SimpleLogger.h"
#include "StdLogger.h"
#include "SharedMemoryLogger.h"
#include <stdarg.h>


/*
if LogType is related to write to file, varadic argument 
should pass a filename

eg:
	getLogger(LogType::SIMPLE_FILE, std::string("test.txt").c_str());
*/
ISLog getLogger(LogType t,...) {

	va_list list;
	va_start(list, t);


	char* pFileName = nullptr;
	ISLog logger;
	switch (t)
	{
	case SIMPLE_FILE:
		pFileName = va_arg(list, char*);
		logger = std::make_unique<SimpleLogger>(std::string(pFileName), true);
		break;
	case STD:
		logger = std::make_unique<StdLogger>();
		break;
	case SHARE_MEM:
		pFileName = va_arg(list, char*);
		assert(pFileName != nullptr);
		logger = std::make_unique<SharedMemoryLogger>(std::string(pFileName));
		break;
	default:
		break;
	}

	va_end(list);

	return logger;
}
