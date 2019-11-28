#pragma once
#include <string>
#include <stringapiset.h>
#include <vector>
#include <Utility/StrUtil.hpp>
#include <Utility/tinyfiledialogs.h>
#include <ImGui/imgui.h>

inline bool wstringgetter(void* vec, int idx, const char** out_text)
{
	std::vector<std::wstring>& vector = *static_cast<std::vector<std::wstring>*>(vec);
	if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
	char buf[256];
	WideCharToMultiByte(CP_UTF8, 0, vector[idx].c_str(), -1, buf, IM_ARRAYSIZE(buf), NULL, NULL);
	*out_text = buf;
	return true;
}

inline bool stringgetter(void* vec, int idx, const char** out_text)
{
	std::vector<std::string>& vector = *static_cast<std::vector<std::string>*>(vec);
	if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
	*out_text = vector.at(idx).c_str();
	return true;
}

template<typename T>
inline float valuegetter(void* data, int idx)
{
	std::vector<T>& vector = *static_cast<std::vector<T>*>(data);
	if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
	return vector[idx];
}

namespace ImGuiKR
{
	inline void SameLine() {
		ImGui::SameLine();
	}

	inline void Separator() {
		ImGui::Separator();
	}

	inline bool Selectable(const std::wstring& _title, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size_arg = ImVec2()) {
		char title[256];
		WideCharToMultiByte(CP_UTF8, 0, _title.c_str(), -1, title, IM_ARRAYSIZE(title), NULL, NULL);
		return ImGui::Selectable(title, selected, flags, size_arg);
	}

	inline bool TreeNodeEx(const std::wstring& _title, ImGuiTreeNodeFlags _flags = 0) {
		char title[256];
		WideCharToMultiByte(CP_UTF8, 0, _title.c_str(), -1, title, IM_ARRAYSIZE(title), NULL, NULL);
		return ImGui::TreeNodeEx(title, _flags);
	}

	inline void TreePop() {
		ImGui::TreePop();
	}

	inline bool Button(const std::wstring& _title, const ImVec2& _size = ImVec2(0, 0)) {
		char title[256];
		WideCharToMultiByte(CP_UTF8, 0, _title.c_str(), -1, title, IM_ARRAYSIZE(title), NULL, NULL);
		return ImGui::Button(title, _size);
	}

	inline void TextUnformatted(const std::wstring& _title) {
		char title[256];
		WideCharToMultiByte(CP_UTF8, 0, _title.c_str(), -1, title, IM_ARRAYSIZE(title), NULL, NULL);
		ImGui::TextUnformatted(title);
	}

	inline void BulletText(const std::wstring& _title) {
		char title[256];
		WideCharToMultiByte(CP_UTF8, 0, _title.c_str(), -1, title, IM_ARRAYSIZE(title), NULL, NULL);
		ImGui::BulletText(title);
	}

	inline bool titleCheckBox(const std::wstring& _title, bool& _val, const std::string& id, const float& textWidth = 100, const float& itemWidth = 200) {
		ImGui::AlignTextToFramePadding();
		TextUnformatted(_title);
		ImGui::SameLine(textWidth);
		ImGui::PushItemWidth(itemWidth);
		return ImGui::Checkbox(("##check" + id).c_str(), &_val);
	}

	inline bool titleCombo(const std::wstring& _title, int& _val, const std::string& id, vector<string> _items, const float& textWidth = 100, const float& itemWidth = 200) {
		ImGui::AlignTextToFramePadding();
		TextUnformatted(_title);
		ImGui::SameLine(textWidth);
		ImGui::PushItemWidth(itemWidth);
		return ImGui::Combo(("##list" + id).c_str(), &_val, &stringgetter, static_cast<void*>(&_items), _items.size());
	}

	inline bool titleInputDouble(const std::wstring& _title, double& _val, const std::string& id, const float& textWidth = 100, const float& itemWidth = 200) {
		ImGui::AlignTextToFramePadding();
		TextUnformatted(_title);
		ImGui::SameLine(textWidth);
		ImGui::PushItemWidth(itemWidth);
		return ImGui::InputDouble(("##double" + id).c_str(), &_val, 0, 0, "%.3f");
	}

	inline bool titleInputFloat(const std::wstring& _title, float& _val, const std::string& id, const float& textWidth = 100, const float& itemWidth = 200) {
		ImGui::AlignTextToFramePadding();
		TextUnformatted(_title);
		ImGui::SameLine(textWidth);
		ImGui::PushItemWidth(itemWidth);
		return ImGui::InputFloat(("##float" + id).c_str(), &_val, 0, 0, "%.3f");
	}

	inline bool titleInputInt(const std::wstring& _title, int& _val, const std::string& id, const float& textWidth = 100, const float& itemWidth = 200) {
		ImGui::AlignTextToFramePadding();
		TextUnformatted(_title);
		ImGui::SameLine(textWidth);
		ImGui::PushItemWidth(itemWidth);
		return ImGui::InputInt(("##int" + id).c_str(), &_val);
	}

	inline bool titleInputText(const std::wstring& _title, wstring& _buf, const std::string& id, const float& textWidth = 100, const float& itemWidth = 200) {
		char buf[256];
		WideCharToMultiByte(CP_UTF8, 0, _buf.c_str(), -1, buf, IM_ARRAYSIZE(buf), NULL, NULL);
		ImGui::AlignTextToFramePadding();
		TextUnformatted(_title);
		ImGui::SameLine(textWidth);
		ImGui::PushItemWidth(itemWidth);
		if (ImGui::InputText(("##text" + id).c_str(), buf, IM_ARRAYSIZE(buf))) {
			wchar_t newbuf[256];
			MultiByteToWideChar(CP_UTF8, 0, buf, -1, newbuf, IM_ARRAYSIZE(newbuf));
			_buf = wstring(newbuf);
			return true;
		}
		return false;
	}

	inline bool titleInputVector2(const std::wstring& _title, vec2& _val, const std::string& id, const float& textWidth = 100, const float& itemWidth = 200) {
		ImGui::AlignTextToFramePadding();
		TextUnformatted(_title);
		ImGui::SameLine(textWidth);
		ImGui::PushItemWidth(itemWidth);
		bool flag1 = ImGui::InputFloat(("##vec2x" + id).c_str(), &(_val.x), 0, 0, "%.3f");
		ImGui::SameLine();
		bool flag2 = ImGui::InputFloat(("##vec2y" + id).c_str(), &(_val.y), 0, 0, "%.3f");
		return flag1 | flag2;
	}

	inline bool titleInputVector3(const std::wstring& _title, vec3& _val, const std::string& id, const float& textWidth = 100, const float& itemWidth = 200) {
		ImGui::AlignTextToFramePadding();
		TextUnformatted(_title);
		ImGui::SameLine(textWidth);
		ImGui::PushItemWidth(itemWidth);
		bool flag1 = ImGui::InputFloat(("##vec3x" + id).c_str(), &(_val.x), 0, 0, "%.3f");
		ImGui::SameLine();
		bool flag2 = ImGui::InputFloat(("##vec3y" + id).c_str(), &(_val.y), 0, 0, "%.3f");
		ImGui::SameLine();
		bool flag3 = ImGui::InputFloat(("##vec3z" + id).c_str(), &(_val.z), 0, 0, "%.3f");
		return flag1 | flag2 | flag3;
	}

	inline bool FileSelect(wstring _title, wstring& _buf, string id, float textWidth = 100, float boxwidth = 200, const WCHAR* filter = L"*.*\0*.*") {
		bool result = false;
		char buf[256];
		char title[256];
		WideCharToMultiByte(CP_UTF8, 0, _buf.c_str(), -1, buf, IM_ARRAYSIZE(buf), NULL, NULL);
		WideCharToMultiByte(CP_UTF8, 0, _title.c_str(), -1, title, IM_ARRAYSIZE(title), NULL, NULL);
		ImGui::AlignTextToFramePadding();
		ImGui::Text(title);
		ImGui::SameLine(textWidth);
		ImGui::PushItemWidth(boxwidth);
		result += ImGui::InputText(("##fileinput" + id).c_str(), buf, IM_ARRAYSIZE(buf));
		ImGui::SameLine();
		if (ImGui::Button(("...##button" + id).c_str())) {
			wstring temp = tinyfd_openFileDialogW(L"파일을 선택하세요.", _buf.c_str(), 0, filter, NULL, 0);
			if (!temp.empty()) {
				StrUtil::Replace(&temp, L"\\", L"/");
				_buf = temp;
				result += true;
			}
		}
		else {
			wchar_t newbuf[256];
			MultiByteToWideChar(CP_UTF8, 0, buf, -1, newbuf, IM_ARRAYSIZE(newbuf));
			_buf = wstring(newbuf);
		}
		return result;
	}

	inline bool DirectorySelect(wstring _title, wstring& _buf, string id, float textWidth = 100, float boxwidth = 200) {
		bool result = false;
		char buf[256];
		char title[256];
		WideCharToMultiByte(CP_UTF8, 0, _buf.c_str(), -1, buf, IM_ARRAYSIZE(buf), NULL, NULL);
		WideCharToMultiByte(CP_UTF8, 0, _title.c_str(), -1, title, IM_ARRAYSIZE(title), NULL, NULL);
		ImGui::AlignTextToFramePadding();
		ImGui::Text(title);
		ImGui::SameLine(textWidth);
		ImGui::PushItemWidth(boxwidth);
		result += ImGui::InputText(("##pathinput" + id).c_str(), buf, IM_ARRAYSIZE(buf));
		ImGui::SameLine();
		if (ImGui::Button(("...##button" + id).c_str())) {
			wstring temp = tinyfd_selectFolderDialogW(L"폴더를 선택하세요.", _buf.c_str());
			if (!temp.empty()) {
				StrUtil::Replace(&temp, L"\\", L"/");
				_buf = temp;
				result += true;
			}
		}
		else {
			wchar_t newbuf[256];
			MultiByteToWideChar(CP_UTF8, 0, buf, -1, newbuf, IM_ARRAYSIZE(newbuf));
			_buf = wstring(newbuf);
		}
		return result;
	}
}