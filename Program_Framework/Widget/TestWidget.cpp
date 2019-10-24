#include "stdafx.h"
#include "TestWidget.h"

void TestWidget::Update()
{
	popup->Update();
	browser->Update();
}

void TestWidget::GuiUpdate()
{
	using namespace ImGuiKR;
	{
		if (Button(L"Popup Test"))
			ImGui::OpenPopup("testpopup");

		if (Button(L"Browser Open"))
			ImGui::OpenPopup("browser");

		popup->Render();
		browser->Render();
	}
}
