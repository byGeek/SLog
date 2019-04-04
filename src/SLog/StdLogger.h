#ifndef _D_STD_LOGGER_H
#define _D_STD_LOGGER_H

#include "AbstractLogger.h"

class StdLogger : public AbstractLogger {
public:
	StdLogger();
	~StdLogger();

private:
	void writeInternal(const char* buf, int len) override;
};

#endif // !_D_STD_LOGGER_H
