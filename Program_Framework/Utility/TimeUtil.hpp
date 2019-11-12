#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <chrono>

namespace TimeUtil
{
	inline double GetTimeMs() {
		auto now = std::chrono::system_clock::now();
		auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
		return ((double)now_ns.time_since_epoch().count()) * 1e-6;
	}

	inline tm GetTimeStruct() {
		time_t tm;
		time(&tm);
		struct tm t2;
		localtime_s(&t2, &tm);
		return t2;
	}

	inline std::string convertTimeString(time_t& _tm, const std::string& format = "%Y%m%d_%H%M%S") {
		struct tm t2;
		localtime_s(&t2, &_tm);
		char out_string[256];
		try
		{
			strftime(out_string, sizeof(out_string) - 1, format.c_str(), &t2);
		}
		catch (const std::exception& err)
		{
			std::cout << err.what() << std::endl;
		}
		return std::string(out_string);
	}

	inline std::wstring convertTimeWString(time_t& _tm, const std::wstring& format = L"%Y%m%d_%H%M%S") {
		struct tm t2;
		localtime_s(&t2, &_tm);
		wchar_t out_string[256];
		try
		{
			wcsftime(out_string, 0.5 * sizeof(out_string) - 1, format.c_str(), &t2);
		}
		catch (const std::exception& err)
		{
			std::wcout << err.what() << std::endl;
		}
		return std::wstring(out_string);
	}

	inline std::string convertTimeString(tm& _tm, const std::string& format = "%Y%m%d_%H%M%S") {
		char out_string[256];
		try
		{
			strftime(out_string, sizeof(out_string) - 1, format.c_str(), &_tm);
		}
		catch (const std::exception& err)
		{
			std::cout << err.what() << std::endl;
		}
		return std::string(out_string);
	}

	inline std::wstring convertTimeWString(tm& _tm, const std::wstring& format = L"%Y%m%d_%H%M%S") {
		wchar_t out_string[256];
		try
		{
			wcsftime(out_string, 0.5 * sizeof(out_string) - 1, format.c_str(), &_tm);
		}
		catch (const std::exception& err)
		{
			std::wcout << err.what() << std::endl;
		}
		return std::wstring(out_string);
	}

	inline std::wstring GetTimeWString(const std::wstring& format = L"%Y%m%d_%H%M%S") {
		struct tm ts = GetTimeStruct();
		return convertTimeWString(ts, format);
	}

	inline std::string GetTimeString(const std::string& format = "%Y%m%d_%H%M%S") {
		struct tm ts = GetTimeStruct();
		return convertTimeString(ts, format);
	}
}