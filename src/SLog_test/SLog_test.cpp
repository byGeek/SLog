#include "log_api.h"
#include <string>


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

//todo: stress test for shared memory logger?

int main() {
	
	//test_stdlogger();
	//test_simple_file_logger();
	test_mmf_logger_exceed_log_file_size();

	//test_mmp_logger();

}