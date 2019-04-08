#ifndef _D_UTIL_H
#define _D_UTIL_H

#include <string>
#include <ctime>

#define LOW_LONG(x) ((x) & (0xffffffff))
#define HIGH_LONG(x) (((x) >> 32) & (0xffffffff))

class util {

public:
	util() = default;
	~util() = default;


	static std::string getCurrentTime(const char* format) {
		char timestr[128];
		std::time_t t = std::time(nullptr);
		//std::strftime(timestr, sizeof(timestr), "%Y/%m/%d %H:%M:%S", std::localtime(&t));
		tm ttm;
		localtime_s(&ttm, &t);
		std::strftime(timestr, sizeof(timestr), format, &ttm);  //"%Y/%m/%d %H:%M:%S"
		return std::string(timestr);
	}

	static DWORD getSystemGranularity() {
		static SYSTEM_INFO info;
		GetSystemInfo(&info);
		return info.dwAllocationGranularity;
	}
};

#endif // !_D_UTIL_H
