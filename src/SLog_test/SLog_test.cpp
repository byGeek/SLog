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

int main() {
	
	test_stdlogger();
	test_simple_file_logger();

}