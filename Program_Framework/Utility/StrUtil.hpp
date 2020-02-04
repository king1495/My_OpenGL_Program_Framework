#pragma once
#include <string>
#include <stringapiset.h>
#include <vector>
#include <algorithm>

namespace StrUtil
{
	inline void SplitString(std::vector<std::string>& result, std::string origin, const std::string& tok)
	{
		result.clear();

		int cutAt = 0; //자를 위치s
		while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
		{
			result.emplace_back(origin.substr(0, cutAt));
			origin.erase(0, cutAt + tok.length());
		}

		if (origin.length() > 0) //자르고도 남은 것이 있다면
			result.emplace_back(origin);
	}

	inline void SplitString(std::vector<std::wstring>& result, std::wstring origin, const std::wstring& tok)
	{
		result.clear();

		int cutAt = 0; //자를 위치s

		while ((cutAt = (int)origin.find_first_of(tok)) != origin.npos)
		{
			result.emplace_back(origin.substr(0, cutAt));
			origin.erase(0, cutAt + tok.length());
		}

		if (origin.length() > 0) //자르고도 남은 것이 있다면
			result.emplace_back(origin);
	}

	inline const bool StartsWith(const std::string& str, const std::string& comp)
	{
		std::string::size_type index = str.find(comp);
		if (index != std::string::npos && (int)index == 0)
			return true;

		return false;
	}

	inline const bool StartsWith(const std::wstring& str, const std::wstring& comp)
	{
		std::wstring::size_type index = str.find(comp);
		if (index != std::wstring::npos && (int)index == 0)
			return true;

		return false;
	}

	inline const bool Contain(const std::string& str, const std::string& comp)
	{
		size_t found = str.find(comp);
		return found != std::string::npos;
	}

	inline const bool Contain(const std::wstring& str, const std::wstring& comp)
	{
		size_t found = str.find(comp);
		return found != std::wstring::npos;
	}

	inline void Replace(std::string* const str, const std::string& comp, const std::string& rep)
	{
		std::string temp = *str;

		size_t start_pos = 0;
		while ((start_pos = temp.find(comp, start_pos)) != std::wstring::npos)
		{
			temp.replace(start_pos, comp.length(), rep);
			start_pos += rep.length();
		}

		*str = temp;
	}

	inline void Replace(std::wstring* const str, const std::wstring& comp, const std::wstring& rep)
	{
		std::wstring temp = *str;
		size_t start_pos = 0;
		while ((start_pos = temp.find(comp, start_pos)) != std::wstring::npos)
		{
			temp.replace(start_pos, comp.length(), rep);
			start_pos += rep.length();
		}
		*str = temp;
	}

	inline std::string ToString(std::wstring value, UINT CodePage = CP_UTF8) {
		char buf[256];
		WideCharToMultiByte(CodePage, 0, value.c_str(), -1, buf, ARRAYSIZE(buf), NULL, NULL);
		return std::string(buf);
	}

	inline std::wstring ToWString(std::string value, UINT CodePage = CP_UTF8) {
		wchar_t buf[256];
		MultiByteToWideChar(CodePage, 0, value.c_str(), -1, buf, ARRAYSIZE(buf));
		return std::wstring(buf);
	}

	// trim from start (in place)
	inline void ltrim(std::string& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
			return !isspace(ch);
			}));
	}

	// trim from end (in place)
	inline void rtrim(std::string& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
			return !isspace(ch);
			}).base(), s.end());
	}

	// trim from both ends (in place)
	inline void trim(std::string& s) {
		ltrim(s);
		rtrim(s);
	}

	inline void toUpperCase(std::wstring& str) {
		std::transform(str.begin(), str.end(), str.begin(), towupper);
	}

	inline void toLowerCase(std::wstring& str) {
		std::transform(str.begin(), str.end(), str.begin(), towlower);
	}

	template<typename T>
	inline std::string numToString(const T& _val, const int& _precision) {
		std::stringstream ss;
		ss << std::fixed << std::setprecision(_precision) << _val;
		std::string result = ss.str();
		return result;
	}

	template<typename T>
	inline std::wstring numToWstring(const T& _val, const int& _precision) {
		std::wstringstream ss;
		ss << std::fixed << std::setprecision(_precision) << _val;
		std::wstring result = ss.str();
		return result;
	}
}
