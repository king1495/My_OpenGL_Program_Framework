#pragma once
#include "IWidget.h"
#include "Widget/TestPopup.h"
#include "Widget/BrowserPopup.h"

class TestWidget final : public IWidget
{
public:
	TestWidget(const std::wstring& _title)
		:IWidget(_title)
	{
		popup.reset(new TestPopup("testpopup"));
		browser.reset(new BrowserPopup("browser"));
		idx = 0;
		vItem.emplace_back("1");
		vItem.emplace_back("12");
		vItem.emplace_back("13");
		vItem.emplace_back("14");
	};
	virtual ~TestWidget() {};

	// IWidget을(를) 통해 상속됨
	virtual void Update() override;

private:
	int idx;
	std::vector<std::string> vItem;

	std::shared_ptr<TestPopup> popup;
	std::shared_ptr<BrowserPopup> browser;

	virtual void GuiUpdate() override;
};