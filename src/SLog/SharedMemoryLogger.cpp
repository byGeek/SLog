#include "stdafx.h"
#include "SharedMemoryLogger.h"
#include "util.h"

#define LOG_FILE_SIZE (1024*1024*8)

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

	if (len > LOG_FILE_SIZE) {
		throw std::runtime_error("log file size too small");
	}

	if (m_bytesWritten > LOG_FILE_SIZE
		|| m_bytesWritten + len > LOG_FILE_SIZE) {
		initNewLogFile();  //init new log file
	}

	memcpy_s(getCurrentPointer(), bytesRemain(),buf, len);
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
	DWORD r = SetFilePointer(m_hFile, LOG_FILE_SIZE, NULL, FILE_BEGIN);
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
	/*
#if WIN32
	WIN32_FIND_DATAA ffd;
	HANDLE hfind = INVALID_HANDLE_VALUE;

	std::string pattern = m_filename;
	std::size_t pos = m_filename.find_last_of(".");
	if (pos == std::string::npos) {
		pattern = m_filename.substr(0, pos);
		pattern += "*" + m_filename.substr(pos);
	}

	//hfind = FindFirstFileA(m_filename.c_str(), &ffd);
	hfind = FindFirstFileA(pattern.c_str(), &ffd);

	if (hfind == INVALID_HANDLE_VALUE) {
		char msg[1024];
		sprintf_s(msg, 1024, "FindFirstFile failed with %d\n", GetLastError());
		throw std::runtime_error(msg);
	}

	do {
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			//is directory, do nothing
		}
		else {
			//todo:
			//ffd.cFileName
		}
	}
#endif
*/
	std::size_t pos = m_filename.find_last_of('.');
	std::string filename(m_filename);
	if (pos != std::string::npos) {
		filename = m_filename.substr(0, pos) + "_" + util::getCurrentTime("%Y_%m_%d_%H_%M_%S") +
			m_filename.substr(pos);
	}

	return filename;
}