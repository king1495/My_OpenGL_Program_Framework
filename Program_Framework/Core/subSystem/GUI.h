#pragma once
#include "Widget/IWidget.h"
#include "Widget/IPopup.h"

class GUI final : public ISubSystem
{
public:
	GUI();
	virtual ~GUI();

	void AddWidget(const string& name, class IWidget* widget);
	void DeleteWidget(const string& name);
	void ActiveWidget(const string& name);
	void DeactiveWidget(const string& name);

	void AddPopup(const string& name, class IPopup* popup);
	void DeletePopup(const string& name);
	void ActivePopup(const string& name);

	void Update();
	void GuiRender();

	void SetAlpha(double _val) { alpha = _val; }
	void SetActive(bool _val) { isActive = _val; }

private:
	ImGuiWindowFlags windowFlags;
	ImGuiDockNodeFlags dockFlags;
	bool isShowSysteminfo;
	bool isShowStyleeditor;
	bool isShowDemo;
	bool isActive;

	void showMenuBar();
	void showSysteminfo();
	void showStyleEditor();

	std::map<std::string, class IWidget*> widgets;
	std::map<std::string, class IPopup*> popups;

	double alpha;
	int iWidth, iHeight;
};