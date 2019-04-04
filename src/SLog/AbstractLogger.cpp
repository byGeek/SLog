#include "stdafx.h"
#include "AbstractLogger.h"
#include <stdarg.h>
#include <ctime>
#include <assert.h>

#define MAX_LOG_SIZE 2048

AbstractLogger::AbstractLogger(){}
AbstractLogger::~AbstractLogger(){}


//todo: rewrite this, msg -> format?
void AbstractLogger::debug(const char* format, ...) {
	//todo: call internal log func
	va_list list;
	va_start(list, format);
	log(Level::L_DEBUG, format, list);
	va_end(list);
}

void AbstractLogger::info(const char* format, ...) {
	va_list list;
	va_start(list, format);
	log(Level::L_INFO, format, list);
	va_end(list);
}

void AbstractLogger::error(const char* format, ...) {
	va_list list;
	va_start(list, format);
	log(Level::L_ERROR, format, list);
	va_end(list);
}

void AbstractLogger::log(Level level, const char* format, va_list list) {
	char logstr[MAX_LOG_SIZE];
	char timestr[128];
	std::time_t t = std::time(nullptr);
	//std::strftime(timestr, sizeof(timestr), "%Y/%m/%d %H:%M:%S", std::localtime(&t));
	tm ttm;
	localtime_s(&ttm, &t);
	std::strftime(timestr, sizeof(timestr), "%Y/%m/%d %H:%M:%S", &ttm);

	char levelstr[128];
	switch (level) {
	case Level::L_DEBUG:
		memcpy_s(levelstr, sizeof(levelstr), "DEBUG", sizeof("DEBUG"));
		break;
	case Level::L_INFO:
		memcpy_s(levelstr, sizeof(levelstr), "INFO", sizeof("INFO"));
		break;
	case Level::L_ERROR:
		memcpy_s(levelstr, sizeof(levelstr), "ERROR", sizeof("ERROR"));
		break;
	default:
		break;
	}

	auto cnt1 = sprintf_s(logstr, sizeof(logstr), "%s\t%s\t", timestr, levelstr);
	auto cnt2 = vsprintf_s(logstr + cnt1, sizeof(logstr) -1 - cnt1, format, list);
	
	if (cnt2 < 0) {
		//todo: vsprintf_f error return
		assert(0);
	}

	logstr[cnt1 + cnt2] = '\n';
	logstr[cnt1 + cnt2 + 1] = '\0';

	writeInternal(logstr, cnt1 + cnt2 + 1);
	/*
	if (stream.good) {
		stream.write(logstr, cnt1 + cnt2 + 1);
	}

	*/


}