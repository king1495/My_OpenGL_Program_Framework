#pragma once
#include <Windows.h>

namespace FilePathUtil
{
	inline std::string Combine(const std::string& path1, const std::string& path2)
	{
		return path1 + "/" + path2;
	}

	inline std::wstring Combine(const std::wstring& path1, const std::wstring& path2)
	{
		return path1 + L"/" + path2;
	}

	inline std::string Combine(const std::vector<std::string>& paths)
	{
		if (paths.empty()) return "";
		std::string temp = paths[0];
		for (int i = 1; i < paths.size(); ++i)
			temp += ("/" + paths[i]);
		return temp;
	}

	inline std::wstring Combine(const std::vector<std::wstring>& paths)
	{
		if (paths.empty()) return L"";
		std::wstring temp = paths[0];
		for (int i = 1; i < paths.size(); ++i)
			temp += (L"/" + paths[i]);
		return temp;
	}

	inline std::string GetDirectoryName(const std::string& path)
	{
		size_t index = path.find_last_of('/');
		return path.substr(0, index + 1);
	}

	inline std::wstring GetDirectoryName(const std::wstring& path)
	{
		size_t index = path.find_last_of('/');
		return path.substr(0, index + 1);
	}

	inline std::string GetExtension(const std::string& path)
	{
		size_t index = path.find_last_of('.');
		return path.substr(index + 1, path.length());;
	}

	inline std::wstring GetExtension(const std::wstring& path)
	{
		size_t index = path.find_last_of('.');
		return path.substr(index + 1, path.length());;
	}

	inline std::string GetFileName(const std::string& path)
	{
		size_t index = path.find_last_of('/');
		return path.substr(index + 1, path.length());
	}

	inline std::wstring GetFileName(const std::wstring& path)
	{
		size_t index = path.find_last_of('/');
		return path.substr(index + 1, path.length());
	}

	inline std::string GetFileNameWithoutExtension(const std::string& path)
	{
		std::string fileName = GetFileName(path);
		size_t index = fileName.find_last_of('.');
		return fileName.substr(0, index);
	}

	inline std::wstring GetFileNameWithoutExtension(const std::wstring& path)
	{
		std::wstring fileName = GetFileName(path);
		size_t index = fileName.find_last_of('.');
		return fileName.substr(0, index);
	}

	inline void MakeDirectory(const std::wstring& full_path)
	{
		namespace fs = std::filesystem;
		fs::path _path = full_path;
		if (fs::is_directory(_path))
			fs::create_directories(_path);
		else
			fs::create_directories(_path.remove_filename());
	}

	inline void MakeDirectory(const std::string& full_path)
	{
		namespace fs = std::filesystem;
		fs::path _path = full_path;
		if (fs::is_directory(_path))
			fs::create_directories(_path);
		else
			fs::create_directories(_path.remove_filename());
	}

	inline void GetFileList(std::vector<std::wstring>& result, const std::wstring& path, const std::wstring& filter = L"", const bool& findAll = false) {
		namespace fs = std::filesystem;
		for (auto& p : fs::directory_iterator(path, fs::directory_options::skip_permission_denied))
		{
			if (p.is_directory() & findAll) {
				GetFileList(result, p.path().wstring(), filter, findAll);
			}
			else
			{
				if (filter != L"") {
					std::wstring ext = p.path().extension().wstring();
					StrUtil::toLowerCase(ext);
					if (ext != filter) continue;
				}
				std::wstring fullpath = p.path().wstring();
				StrUtil::Replace(&fullpath, L"\\", L"/");
				result.emplace_back(fullpath);
			}
		}
	}
}