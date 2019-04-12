#ifndef _D_SLOG_H
#define _D_SLOG_H

#include <string>

class SLog {
public:
	virtual ~SLog() = default;
	virtual void debug(const std::string format, ...) = 0;
	virtual void info(const std::string format, ...) = 0;
	virtual void error(const std::string format, ...) = 0;
};



#endif // !_D_SLOG_H
