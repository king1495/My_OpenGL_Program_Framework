#pragma once
#include "IWidget.h"

class FileSelectWidget : public IWidget
{
public:
	FileSelectWidget(std::wstring _title)
		:IWidget(_title)
	{}
	virtual ~FileSelectWidget() {};

	virtual void Update() override;
	virtual void GuiUpdate() override;

private:

	std::wstring dir_path;
	std::wstring file_path;

	std::vector<std::wstring> filelist;

};