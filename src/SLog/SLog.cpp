// SLog.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "log_api.h"
#include "SimpleLogger.h"
#include "StdLogger.h"
#include "SharedMemoryLogger.h"


//todo: how to pass filename if logger type is simple file logger?
//todo: singleton?
ISLog getLogger(LogType t) {
	ISLog logger;
	switch (t)
	{
	case SIMPLE_FILE:
		logger = std::make_unique<SimpleLogger>("text.txt", true);
		break;
	case STD:
		logger = std::make_unique<StdLogger>();
		break;
	case SHARE_MEM:
		logger = std::make_unique<SharedMemoryLogger>("mmp_test.txt");
		break;
	default:
		break;
	}

	return logger;
}