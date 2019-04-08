#ifndef _D_SHARED_MEMORY_LOGGER_H
#define _D_SHARED_MEMORY_LOGGER_H

#include "AbstractLogger.h"
#include <string>

class SharedMemoryLogger : public AbstractLogger {
public:

	SharedMemoryLogger(std::string filename);
	~SharedMemoryLogger();

	
private:
	std::string m_filename;
	HANDLE m_hFile;
	HANDLE m_hMapping;
	BYTE* m_pView;
	size_t m_bytesWritten;
	void writeInternal(const char* buf, int len) override;
	bool initNewLogFile();
	void closeFile();
	BYTE* getCurrentPointer() const;
	size_t bytesRemain() const;
	std::string getNewFilename() const;

};

#endif // !_D_SHARED_MEMEORY_LOGGER_H
