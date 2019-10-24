#pragma once
#include "IWidget.h"
#include "Widget/TestPopup.h"
#include "Widget/BrowserPopup.h"

class TestWidget final : public IWidget
{
public:
	TestWidget(const std::wstring& _title);
	virtual ~TestWidget() {};

	// IWidget을(를) 통해 상속됨
	virtual void Update() override;
	virtual void GuiUpdate() override;

private:
	float t0;

	std::vector<float> xdata;
	std::vector<float> ydata1;
	std::vector<float> ydata2;

	std::shared_ptr<ImGuiPlotter<float>> sPlotter;
	std::shared_ptr<ImAxes<float>> sAxes1;
	std::shared_ptr<ImAxes<float>> sAxes2;
	std::shared_ptr<ImPlot<float>> sPlot1;
	std::shared_ptr<ImPlot<float>> sPlot2;
};