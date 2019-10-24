#pragma once
#include "Widget/IWidget.h"

class GUI final
{
public:
	GUI();
	virtual ~GUI();

	void AddWidget(const string& name, class IWidget* widget);
	void DeleteWidget(const string& name);
	void ActiveWidget(const string& name);
	void DeactiveWidget(const string& name);

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

	std::map<string, class IWidget*> widgets;
	std::vector<string> widgetLists;

	double alpha;
};