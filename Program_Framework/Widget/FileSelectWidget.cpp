#include "stdafx.h"
#include "FileSelectWidget.h"

void FileSelectWidget::Update()
{
}

void FileSelectWidget::GuiUpdate()
{
	using namespace ImGuiKR;
	{
		if (DirectorySelect(L"폴더 경로", dir_path, "dir_path", 150, 200)) {
			filelist.clear();
			filelist.shrink_to_fit();
			FilePathUtil::GetFileList(filelist, dir_path, L"", true);
		}
		if (MultiFileSelect(L"파일 경로", filelist, "file_path", 150, 200,L"*.*\0*.*")) {
			//wcout << file_path << endl;
		}
		ImGui::BeginChild("filelistTable", ImVec2(400, 400), true);
		for (int i = 0; i < filelist.size(); i++)
		{
			Selectable(filelist[i]);
		}
		ImGui::EndChild();
		Button(L"실행");
	}
}
