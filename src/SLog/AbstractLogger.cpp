#include "stdafx.h"
#include "AbstractLogger.h"
#include <stdarg.h>
#include <ctime>
#include <assert.h>
#include "util.h"

#define MAX_LOG_SIZE 2048

AbstractLogger::AbstractLogger(){}
AbstractLogger::~AbstractLogger(){}


void AbstractLogger::debug(const std::string format, ...) {
	va_list list;
	va_start(list, format);
	log(Level::L_DEBUG, std::move(format), list);
	va_end(list);
}

void AbstractLogger::info(const std::string format, ...) {
	va_list list;
	va_start(list, format);
	log(Level::L_INFO, std::move(format), list);
	va_end(list);
}

void AbstractLogger::error(const std::string format, ...) {
	va_list list;
	va_start(list, format);
	log(Level::L_ERROR, std::move(format), list);
	va_end(list);
}

void AbstractLogger::log(Level level, const std::string format, va_list list){
	char logstr[MAX_LOG_SIZE];
	std::string levelstr;
	switch (level) {
	case Level::L_DEBUG:
		levelstr = "DEBUG";
		break;
	case Level::L_INFO:
		levelstr = "INFO";
		break;
	case Level::L_ERROR:
		levelstr = "ERROR";
		break;
	default:
		break;
	}

	auto cnt1 = sprintf_s(logstr, MAX_LOG_SIZE, "%s\t%s\t", util::getCurrentTime("%Y/%m/%d %H:%M:%S").c_str(), levelstr.c_str());
	auto cnt2 = vsprintf_s(logstr + cnt1, MAX_LOG_SIZE -1 - cnt1, format.c_str(), list);
	
	if (cnt2 < 0) {
		char msg[256];
		sprintf_s(msg, 256, "vsprintf_s failed: %d", GetLastError());
		throw std::runtime_error(msg);
	}

	logstr[cnt1 + cnt2] = '\n';
	logstr[cnt1 + cnt2 + 1] = '\0';

	writeInternal(logstr, cnt1 + cnt2 + 1);

}