#ifndef _D_SLOG_H
#define _D_SLOG_H

class SLog {
public:
	virtual ~SLog() = default;
	virtual void debug(const char* format, ...) = 0;
	virtual void info(const char* format, ...) = 0;
	virtual void error(const char* format, ...) = 0;
};



#endif // !_D_SLOG_H
