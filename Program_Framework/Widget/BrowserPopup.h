#pragma once
#include <stack>
#include "IPopup.h"

class BrowserPopup : public IPopup
{
public:
	BrowserPopup(const std::string& _title)
		:IPopup(_title), current_path(L""), selected_file(-1)
	{
		popupFlags |= ImGuiWindowFlags_NoResize;
		popupFlags |= ImGuiWindowFlags_AlwaysAutoResize;
		//popupFlags |= ImGuiWindowFlags_MenuBar;
		GetDriveList(vDrives);
	}
	virtual ~BrowserPopup() {};

	virtual void Update() override;

private:
	virtual void GuiUpdate() override;

	void GetDriveList(std::vector<std::wstring>& _vDrives);
	void GetDirectoryTree(const std::filesystem::path& _path, const std::wstring& _rootName = L"");

	std::stack<wstring> undo;
	std::stack<wstring> redo;

	vector<wstring> vDrives;
	wstring current_path;
	int selected_file;
};