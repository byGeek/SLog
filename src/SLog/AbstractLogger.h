#ifndef _D_ABSTRACT_LOGGER_H
#define _D_ABSTRACT_LOGGER_H

#include "Slog.h"
#include <ostream>

class AbstractLogger : public SLog {
public:

	enum Level {
		L_INFO,
		L_DEBUG,
		L_ERROR
	};

	AbstractLogger();
	virtual ~AbstractLogger();

	virtual void debug(const char* format, ...);
	virtual void info(const char* format, ...);
	virtual void error(const char* format, ...);

protected:
	//virtual void log(Level level, std::string& msg, ...);
	virtual void log(Level level, const char* format, va_list list);
	virtual void writeInternal(const char* buf, int len) = 0;

};

#endif // !_D_ABSTRACT_LOGGER_H
