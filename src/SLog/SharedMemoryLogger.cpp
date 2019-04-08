#include "stdafx.h"
#include "SharedMemoryLogger.h"
#include "util.h"

#define LOG_FILE_SIZE (8*1024*1024)

//todo: implement on both unix and windows

SharedMemoryLogger::SharedMemoryLogger(std::string filename) : m_filename(filename),
	m_hFile(INVALID_HANDLE_VALUE), m_hMapping(NULL), m_pView(nullptr), m_bytesWritten(0)
{
	initNewLogFile();

	assert(m_hFile != INVALID_HANDLE_VALUE);
	assert(m_hMapping != NULL);
	assert(m_pView != nullptr);

}


SharedMemoryLogger::~SharedMemoryLogger() {
	closeFile();
}

void SharedMemoryLogger::writeInternal(const char* buf, int len) {
	assert(buf != nullptr);

	memcpy_s(getCurrentPointer(), bytesRemain(), buf, len);
	m_bytesWritten += len;
}

bool SharedMemoryLogger::initNewLogFile() {

	closeFile();

	auto tfile = getNewFilename();
	m_hFile = CreateFileA(tfile.c_str(),
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_NEW,
		0,
		NULL
	);

	if (m_hFile == INVALID_HANDLE_VALUE) {
		return false;
	}

	//set file size to log file size
	DWORD r = SetFilePointer(m_hFile, LOW_LONG(LOG_FILE_SIZE), HIGH_LONG(LOG_FILE_SIZE), FILE_BEGIN);
	if (r == INVALID_SET_FILE_POINTER) {
		return false;
	}
	SetEndOfFile(m_hFile);
	SetFilePointer(m_hFile, 0, 0, FILE_BEGIN);

	m_hMapping = CreateFileMappingA(m_hFile,
		NULL,
		PAGE_READWRITE,
		0,
		0,
		NULL
	);

	if (m_hMapping == NULL) {
		return false;
	}

	auto size_mapped = util::getSystemGranularity();
	m_pView = (BYTE*)MapViewOfFile(m_hMapping,
		FILE_MAP_READ | FILE_MAP_WRITE,
		0,
		0,
		LOG_FILE_SIZE
	);
	return true;
}

void SharedMemoryLogger::closeFile() {
	if (m_pView != nullptr) {
		UnmapViewOfFile(m_pView);
		CloseHandle(m_hMapping);
	}

	if (m_hFile != INVALID_HANDLE_VALUE) {
		CloseHandle(m_hFile);
	}

	m_bytesWritten = 0;

	m_pView = nullptr;
	m_hMapping = NULL;
	m_hFile = INVALID_HANDLE_VALUE;
}

BYTE* SharedMemoryLogger::getCurrentPointer() const {
	assert(m_pView != nullptr);

	return m_pView + m_bytesWritten;
}

size_t SharedMemoryLogger::bytesRemain() const {
	return LOG_FILE_SIZE - m_bytesWritten;
}

std::string SharedMemoryLogger::getNewFilename() const {
	//todo: find files and append _1, _2 subfix
	return m_filename;
}