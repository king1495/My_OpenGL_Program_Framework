#pragma once
#include <Windows.h>

namespace FilePathUtil
{
	inline std::string Combine(std::string path1, std::string path2)
	{
		return path1 + "/" + path2;
	}

	inline std::wstring Combine(std::wstring path1, std::wstring path2)
	{
		return path1 + L"/" + path2;
	}

	inline std::string Combine(std::vector<std::string> paths)
	{
		if (paths.empty()) return "";
		std::string temp = paths[0];
		for (int i = 1; i < paths.size(); ++i)
			temp += ("/" + paths[i]);
		return temp;
	}

	inline std::wstring Combine(std::vector<std::wstring> paths)
	{
		if (paths.empty()) return L"";
		std::wstring temp = paths[0];
		for (int i = 1; i < paths.size(); ++i)
			temp += (L"/" + paths[i]);
		return temp;
	}

	inline std::string GetDirectoryName(std::string path)
	{
		size_t index = path.find_last_of('/');
		return path.substr(0, index + 1);
	}

	inline std::wstring GetDirectoryName(std::wstring path)
	{
		size_t index = path.find_last_of('/');
		return path.substr(0, index + 1);
	}

	inline std::string GetExtension(std::string path)
	{
		size_t index = path.find_last_of('.');
		return path.substr(index + 1, path.length());;
	}

	inline std::wstring GetExtension(std::wstring path)
	{
		size_t index = path.find_last_of('.');
		return path.substr(index + 1, path.length());;
	}

	inline std::string GetFileName(std::string path)
	{
		size_t index = path.find_last_of('/');
		return path.substr(index + 1, path.length());
	}

	inline std::wstring GetFileName(std::wstring path)
	{
		size_t index = path.find_last_of('/');
		return path.substr(index + 1, path.length());
	}

	inline std::string GetFileNameWithoutExtension(std::string path)
	{
		std::string fileName = GetFileName(path);
		size_t index = fileName.find_last_of('.');
		return fileName.substr(0, index);
	}

	inline std::wstring GetFileNameWithoutExtension(std::wstring path)
	{
		std::wstring fileName = GetFileName(path);
		size_t index = fileName.find_last_of('.');
		return fileName.substr(0, index);
	}

	inline void MakeDirectory(wstring full_path)
	{
		namespace fs = std::filesystem;
		fs::create_directories(full_path);
	}

	inline void MakeDirectory(string full_path)
	{
		namespace fs = std::filesystem;
		fs::create_directories(full_path);
	}
}