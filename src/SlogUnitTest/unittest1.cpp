#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SLog\log_api.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SlogUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		//fixture

		TEST_METHOD_INITIALIZE(test_setup) {

		}

		TEST_METHOD_CLEANUP(test_teardown) {

		}

		TEST_METHOD(test_std_logger)
		{
			// TODO: Your test code here
			auto logger = getLogger(LogType::STD);
			logger->debug("%s name is %s", "robert", "robert");
		}

		TEST_METHOD(test_simple_file_logger) {
			auto logger = getLogger(LogType::SIMPLE_FILE, "tt.text");
			logger->info("%s name is %s", "robert", "robert");
		}

		TEST_METHOD(test_mmp_logger) {
			auto logger = getLogger(LogType::SHARE_MEM, "tt.mmp");
			logger->info("%s name is %s", "robert", "robert");
		}

	};
}