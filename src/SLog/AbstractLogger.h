#ifndef _D_ABSTRACT_LOGGER_H
#define _D_ABSTRACT_LOGGER_H

#include "Slog.h"
#include <ostream>

class AbstractLogger : public SLog {
public:

	enum class Level {
		L_INFO,
		L_DEBUG,
		L_ERROR
	};

	AbstractLogger();
	virtual ~AbstractLogger();

	virtual void debug(const std::string format, ...);
	virtual void info(const  std::string format, ...);
	virtual void error(const  std::string format, ...);

protected:
	//virtual void log(Level level, std::string& msg, ...);
	virtual void log(Level level, const std::string format, va_list list);
	virtual void writeInternal(const char* buf, int len) = 0;

};

#endif // !_D_ABSTRACT_LOGGER_H
