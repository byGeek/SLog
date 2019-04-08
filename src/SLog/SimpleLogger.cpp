#include "stdafx.h"
#include "SimpleLogger.h"


SimpleLogger::SimpleLogger(std::string filename, bool append) : m_filename(filename) {
	const char* mode = "w+";
	if (append) {
		mode = "a+";
	}

	auto ret = fopen_s(&m_file, filename.c_str(), mode);
	if (ret != 0 || m_file == NULL) {
		//todo: fopen failed
		assert(0);
	}
}

SimpleLogger::~SimpleLogger() {
	if (m_file != NULL) {
		fclose(m_file);
	}
}

void SimpleLogger::writeInternal(const char* buf, int len) {
	int ret = fwrite(buf, sizeof(char), len, m_file);
	if (ret < len) {
		//todo: fwrite failed?
		assert(0);
	}
}
