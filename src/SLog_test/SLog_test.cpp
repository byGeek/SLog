#include "log_api.h"


void test_stdlogger() {
	ISLog logger = getLogger(LogType::STD);

	logger->debug("debug");
	logger->error("error");
	logger->info("info");
}

void test_simple_file_logger() {
	ISLog logger = getLogger(LogType::SIMPLE_FILE);

	logger->debug("debug");
	logger->error("error");
	logger->info("info");
}

void test_mmp_logger() {
	ISLog logger = getLogger(LogType::SHARE_MEM);

	logger->debug("debug");
	logger->error("error");
	logger->info("info");
}

void test_max_log_size_case() {
	ISLog logger = getLogger(LogType::SIMPLE_FILE);

	const int MAX_LOG_SIZE = 2048;
	char buf[MAX_LOG_SIZE] = { 0 };
	memcpy_s(buf, MAX_LOG_SIZE, "start", sizeof("start"));
	memcpy_s(buf + MAX_LOG_SIZE - 3, MAX_LOG_SIZE, "end", sizeof("end"));

	logger->info("%s", buf);
}


//todo: stress test for shared memory logger?

int main() {
	
	/*
	test_stdlogger();
	test_simple_file_logger();
	*/

	test_mmp_logger();

}