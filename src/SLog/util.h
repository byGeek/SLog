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

	static std::string getFileExtension(std::string filename) {

		int pos1 = filename.find_last_of('.');
		int pos2 = filename.find_last_of("/\\");
		if (pos1 != std::string::npos){
			if (((pos2 != std::string::npos) && (pos1 > pos2))
				|| pos2 == std::string::npos) {
				return filename.substr(pos1 + 1);

			}
		}

		return std::string("");
	}

	static std::string getFileNameWithoutExt(std::string filename) {
		int pos1 = filename.find_last_of("/\\");
		int pos2 = filename.find_last_of('.');

		int start = 0;
		int len = 0;
		if (pos1 != std::string::npos) {
			start = pos1 + 1;
		}
		if (pos2 != std::string::npos) {
			len = pos2 - pos1 - 1;
		}

		if (len > 0) {
			return filename.substr(start, len);
		}
		else {
			return filename.substr(start);
		}
	}
};

#endif // !_D_UTIL_H
