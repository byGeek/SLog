#ifndef _D_LOG_API_H
#define _D_LOG_API_H

#ifdef SLOG_EXPORTS
#define SLOG_API __declspec(dllexport)
#else
#define SLOG_API __declspec(dllimport)
#endif // SLOG_EXPORT


#include "Slog.h"
#include <memory>

//typedef std::unique_ptr<SLog> ISLog;
using ISLog = std::unique_ptr<SLog>;

enum class LogType {
	SIMPLE_FILE,
	STD,
	SHARE_MEM
};

//extern "C" SLOG_API ISLog getLogger(LogType t);
SLOG_API ISLog getLogger(LogType t,...);


#endif // !_D_LOG_API_H
