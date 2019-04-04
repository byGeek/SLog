#ifndef _D_SIMPLE_LOGGER_H

#define _D_SIMPLE_LOGGER_H

#include "AbstractLogger.h"
#include <string>

class SimpleLogger : public AbstractLogger {
public:
	SimpleLogger(std::string filename, bool append = false);
	~SimpleLogger();

private:
	std::string m_filename;
	FILE* m_file;

	//void log(Level level, const char* format, ...);
	void writeInternal(const char* buf, int len) override;

};



#endif // !_D_SIMPLE_LOGGER_H
