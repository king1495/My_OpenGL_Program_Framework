#include "stdafx.h"
#include "BrowserPopup.h"

namespace fs = std::filesystem;

void BrowserPopup::Update()
{
}

void BrowserPopup::GuiUpdate()
{
	using namespace ImGuiKR;
	{
		if (ImGui::ArrowButtonEx("back", ImGuiDir_Left, ImVec2(20, 20), ImGuiButtonFlags_PressedOnClickRelease))
		{
			if (!undo.empty()) {
				redo.push(current_path);
				current_path = undo.top();
				undo.pop();
			}
		}
		SameLine();
		if (ImGui::ArrowButtonEx("front", ImGuiDir_Right, ImVec2(20, 20), ImGuiButtonFlags_PressedOnClickRelease))
		{
			if (!redo.empty()) {
				undo.push(current_path);
				current_path = redo.top();
				redo.pop();
			}
		}
		SameLine();
		TextUnformatted(current_path);

		if (ImGui::BeginChild("dictBrowser", ImVec2(180, 500), true, ImGuiWindowFlags_HorizontalScrollbar)) {
			if (TreeNodeEx(L"내 컴퓨터", ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick)) {
				for (int i = 0; i < vDrives.size(); i++)
				{
					GetDirectoryTree(vDrives[i], vDrives[i]);
				}
				TreePop();
			}
			ImGui::EndChild();
		}

		SameLine();

		if (ImGui::BeginChild("fileBrowser", ImVec2(620, 500), true)) {
			if (current_path != L"") {
				if (Selectable(L"..", false, ImGuiSelectableFlags_AllowDoubleClick))
					if (ImGui::IsMouseDoubleClicked(0)) {
						undo.push(current_path);
						while (!redo.empty()) redo.pop();
						current_path = fs::path(current_path).parent_path().wstring();
					}

				int file_count = 0;
				for (auto& p : fs::directory_iterator(current_path, fs::directory_options::skip_permission_denied))
				{
					if (Selectable(p.path().filename().wstring(), selected_file == file_count, ImGuiSelectableFlags_AllowDoubleClick)) {
						selected_file = file_count;
						if (ImGui::IsMouseDoubleClicked(0) & p.is_directory()) {
							undo.push(current_path);
							while (!redo.empty()) redo.pop();
							current_path = p.path();
						}
					}
					file_count++;
				}
			}
			ImGui::EndChild();
		}
	}
}

void BrowserPopup::GetDriveList(std::vector<std::wstring>& _vDrives)
{
	_vDrives.clear();
	WCHAR myDrives[105];
	WCHAR volumeName[MAX_PATH];
	WCHAR fileSystemName[MAX_PATH];
	DWORD serialNumber, maxComponentLen, fileSystemFlags;
	UINT driveType;

	if (!GetLogicalDriveStrings(ARRAYSIZE(myDrives) - 1, myDrives))
	{
		wprintf(L"GetLogicalDrives() failed with error code: %lu\n", GetLastError());
	}
	else
	{
		wprintf(L"This machine has the following logical drives:\n");

		for (LPWSTR drive = myDrives; *drive != 0; drive += 4)
		{
			_vDrives.emplace_back(drive);
			driveType = GetDriveType(drive);
			wprintf(L"Drive %s is type %d - ", drive, driveType);

			switch (driveType)
			{
			case DRIVE_UNKNOWN:
				wprintf(L"Cannot be determined!");
				break;
			case DRIVE_NO_ROOT_DIR:
				wprintf(L"Invalid root path/Not available.");
				break;
			case DRIVE_REMOVABLE:
				wprintf(L"Removable.");
				break;
			case DRIVE_FIXED:
				wprintf(L"Fixed.");
				break;
			case DRIVE_REMOTE:
				wprintf(L"Network.");
				break;
			case DRIVE_CDROM:
				wprintf(L"CD-ROM.");
				break;
			case DRIVE_RAMDISK:
				wprintf(L"RAMDISK.");
				break;
			default:
				wprintf(L"Unknown value!");
			}
			wprintf(L"\n");

			if (driveType == DRIVE_CDROM)
			{
				if (GetVolumeInformation(drive, volumeName, ARRAYSIZE(volumeName), &serialNumber, &maxComponentLen, &fileSystemFlags, fileSystemName, ARRAYSIZE(fileSystemName)))
				{
					wprintf(L"  There is a CD/DVD in the drive:\n");
					wprintf(L"  Volume Name: %s\n", volumeName);
					wprintf(L"  Serial Number: %08X\n", serialNumber);
					wprintf(L"  File System Name: %s\n", fileSystemName);
					wprintf(L"  Max Component Length: %lu\n", maxComponentLen);
				}
				else
				{
					wprintf(L"  There is NO CD/DVD in the drive");
				}
			}
		}
	}
}

void BrowserPopup::GetDirectoryTree(const std::filesystem::path& _path, const std::wstring& _rootName)
{
	using namespace ImGuiKR;
	{
		wstring rootName = (_rootName != L"") ? _rootName : _path.filename().wstring().c_str();
		bool node_open = TreeNodeEx(rootName, ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick);
		if (ImGui::IsItemClicked()) {
			wcout << _path.wstring() << endl;
			if (current_path != L"") undo.push(current_path);
			while (!redo.empty()) redo.pop();
			current_path = _path.wstring();
			selected_file = -1;
		}
		if (node_open) {
			for (auto& p : fs::directory_iterator(_path, fs::directory_options::skip_permission_denied))
			{
				if (p.is_directory())
					GetDirectoryTree(p.path());
			}
			TreePop();
		}
	}

}
