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

	// IPopup을(를) 통해 상속됨
	virtual void Update() override;

private:
	virtual void GuiUpdate() override;
};
