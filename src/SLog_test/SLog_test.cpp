#include "log_api.h"
#include <string>
#include <Windows.h>
#include <iostream>

#include "util.h"


void test_stdlogger() {
	ISLog logger = getLogger(LogType::STD);

	logger->debug("debug");
	logger->error("error");
	logger->info("info");
}

void test_simple_file_logger() {
	//ISLog logger = getLogger(LogType::SIMPLE_FILE);
	ISLog logger = getLogger(LogType::SIMPLE_FILE, std::string("test.txt").c_str());

	logger->debug("debug");
	logger->error("error");
	logger->info("info");
}

void test_mmp_logger() {
	ISLog logger = getLogger(LogType::SHARE_MEM, std::string("mmf_test.txt").c_str());

	logger->debug("debug");
	logger->error("error");
	logger->info("info");
}

void test_max_log_size_case() {
	ISLog logger = getLogger(LogType::SIMPLE_FILE, std::string("test.txt").c_str());

	const int MAX_LOG_SIZE = 2048;
	char buf[MAX_LOG_SIZE] = { 0 };
	memcpy_s(buf, MAX_LOG_SIZE, "start", sizeof("start"));
	memcpy_s(buf + MAX_LOG_SIZE - 3, MAX_LOG_SIZE, "end", sizeof("end"));

	logger->info("%s", buf);
}

void test_mmf_logger_exceed_log_file_size() {
	//change LOG_FILE_SIZE macro to 1024

	ISLog logger = getLogger(LogType::SHARE_MEM, std::string("test.txt").c_str());

	const int MAX_LOG_SIZE = 1024;
	char buf[MAX_LOG_SIZE] = { 0 };

	const char tbuf[] = "hello, world";
	int len = 0;
	for (int i = 0; i < MAX_LOG_SIZE / strlen(tbuf);++i) {
		memcpy_s(buf + len, MAX_LOG_SIZE - len, tbuf, strlen(tbuf));
		len += strlen(tbuf);
	}

	logger->info("%s", buf);
}

std::string test_find_file() {

	std::string m_filename("test.txt");

	WIN32_FIND_DATAA ffd;
	HANDLE hfind = INVALID_HANDLE_VALUE;

	std::string pattern = m_filename;
	std::size_t pos = m_filename.find_last_of(".");
	if (pos != std::string::npos) {
		pattern = m_filename.substr(0, pos);
		pattern += "_*" + m_filename.substr(pos);
	}

	//hfind = FindFirstFileA(m_filename.c_str(), &ffd);
	hfind = FindFirstFileA(pattern.c_str(), &ffd);

	if (hfind == INVALID_HANDLE_VALUE) {
		char msg[1024];
		sprintf_s(msg, 1024, "FindFirstFile failed with %d\n", GetLastError());
		throw std::runtime_error(msg);
	}

	auto max_index = 0;
	do {
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			//is directory, do nothing
		}
		else {
			std::string fullpath(ffd.cFileName);
			std::string friendly_filename = fullpath;
			auto pos2 = friendly_filename.find_last_of("_");
			if (pos2 != std::string::npos) {
				auto len = friendly_filename.find_last_of('.') - pos2 - 1;
				if (len > 0) {
					auto index = atoi(friendly_filename.substr(pos2 + 1, len).c_str());
					if (index > max_index) {
						max_index = index;
					}
				}
			}
		}
	} while (FindNextFileA(hfind, &ffd) != 0);

	return m_filename.substr(0, m_filename.find_last_of('.')) + "_" + std::to_string(max_index + 1)
		+ m_filename.substr(m_filename.find_last_of('.'));

}

void test_getFileExtension() {
	std::string filename = "123.txt";
	std::string ext = util::getFileExtension(filename);

	ext = util::getFileExtension("1234");

	ext = util::getFileExtension(".\\123.txt");
	ext = util::getFileExtension(".\\123");
}

void test_getFileNameWithoutExt() {
	std::string filename = util::getFileNameWithoutExt("c:\\123.txt");
	filename = util::getFileNameWithoutExt("123.txt");
	filename = util::getFileNameWithoutExt(".\\234.txt");
	filename = util::getFileNameWithoutExt(".\\123");
}

//todo: stress test for shared memory logger?

int main() {

	//test_stdlogger();
	//test_simple_file_logger();
//	test_mmf_logger_exceed_log_file_size();

	//auto filename = test_find_file();
	//test_getFileExtension();
	//test_getFileNameWithoutExt();
	//std::cout << filename << std::endl;
	test_mmp_logger();

	std::cin.get();

}