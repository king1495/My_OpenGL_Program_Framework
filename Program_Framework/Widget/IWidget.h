#pragma once
#include <string>
#include <stringapiset.h>
#include "ImGui/imgui.h"

class IWidget
{
public:
	IWidget(const std::wstring& _title = L"Widget")
		:bOpen(true), widgetFlags(ImGuiWindowFlags_None)
	{
		char title[256];
		WideCharToMultiByte(CP_UTF8, 0, _title.c_str(), -1, title, IM_ARRAYSIZE(title), NULL, NULL);
		widgetTitle = title;
	};
	virtual ~IWidget() = default;

	virtual void Update() = 0;

	virtual void Render() {
		if (!bOpen) return;
		ImGui::Begin(widgetTitle.c_str(), &bOpen, widgetFlags);
		GuiUpdate();
		ImGui::End();
	}

	std::string& GetName() { return widgetTitle; }

	bool GetisActive() { return bOpen; };
	void SetisActive(const bool& _b) { bOpen = _b; };

protected:
	bool bOpen;
	std::string widgetTitle;
	//ImVec2 widgetSize;
	//float widgetAlpha;
	ImGuiWindowFlags widgetFlags;
	
	virtual void GuiUpdate() = 0;
};