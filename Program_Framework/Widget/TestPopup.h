#pragma once
#include "IPopup.h"

class TestPopup : public IPopup
{
public:
	TestPopup(const std::string& _title)
		:IPopup(_title)
	{
		popupFlags = ImGuiWindowFlags_MenuBar;
	}
	virtual ~TestPopup() {};

	// IPopup��(��) ���� ��ӵ�
	virtual void Update() override;

private:
	virtual void GuiUpdate() override;
};
