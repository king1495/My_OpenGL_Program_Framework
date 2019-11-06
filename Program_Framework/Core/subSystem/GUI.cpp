#include "stdafx.h"
#include "GUI.h"

GUI::GUI()
	:windowFlags(ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoDecoration |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_MenuBar |
		//ImGuiWindowFlags_NoBackground |
		ImGuiWindowFlags_NoSavedSettings
	)
	, dockFlags(ImGuiDockNodeFlags_AutoHideTabBar)
	, isShowSysteminfo(false)
	, isShowStyleeditor(false)
	, isShowDemo(false)
	, isActive(true)
	, alpha(1.f)
{
}

GUI::~GUI()
{
	for (auto widget : widgets)
		SAFE_DELETE(widget.second);
}

void GUI::AddWidget(const string& name, IWidget* widget)
{
	assert(widgets.count(name) < 1);
	widgets[name] = widget;
}

void GUI::DeleteWidget(const string& name)
{
	if (widgets.count(name) < 1) return;
	SAFE_DELETE(widgets[name]);
	widgets.erase(name);
}

void GUI::ActiveWidget(const string& name)
{
	if (widgets.count(name) < 1) return;
	widgets[name]->SetisActive(true);
}

void GUI::DeactiveWidget(const string& name)
{
	if (widgets.count(name) < 1) return;
	widgets[name]->SetisActive(false);
}

void GUI::Update()
{
	if (!isActive) return;
	for (auto widget : widgets)
		widget.second->Update();

#ifdef _DEBUG
	if (_Input.isKeyDown(VK_F1)) isShowSysteminfo = !isShowSysteminfo;
	if (_Input.isKeyDown(VK_F2)) isShowStyleeditor = !isShowStyleeditor;
#endif
}

void GUI::GuiRender()
{
	if (!isActive) return;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("Background", NULL, ImVec2(appDesc.Width, appDesc.Height), alpha, windowFlags);
	ImGui::SetWindowSize(ImVec2(appDesc.Width, appDesc.Height));
	ImGui::PopStyleVar(3);

	ImGuiID dockspace_id = ImGui::GetID("Background");
	ImGui::DockSpace(dockspace_id, ImVec2(0, 0), dockFlags);

	showMenuBar();

	for (auto widget : widgets)
		widget.second->Render();

	ImGui::End();

#ifdef _DEBUG
	if (isShowSysteminfo) showSysteminfo();
	if (isShowStyleeditor) showStyleEditor();
	if (isShowDemo) ImGui::ShowDemoWindow();
#endif
}

void GUI::showMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Quit", "Alt + F4"))
				glfwSetWindowShouldClose(appDesc.pWindow, GLFW_TRUE);

			ImGui::EndMenu();
		}
		ImGui::Separator();

		if (!widgets.empty()) {
			if (ImGui::BeginMenu("View"))
			{
				for (auto widget : widgets) {
					if (ImGui::MenuItem(widget.second->GetName().c_str())) {
						widget.second->SetisActive(true);
					}
				}

				ImGui::EndMenu();
			}
			ImGui::Separator();
		}

#ifdef _DEBUG
		if (ImGui::BeginMenu("Debug")) {
			if (ImGui::MenuItem("System Info", "F1")) isShowSysteminfo = !isShowSysteminfo;
			if (ImGui::MenuItem("Style Editor", "F2")) isShowStyleeditor = !isShowStyleeditor;
			if (ImGui::MenuItem("Show Demo")) isShowDemo = !isShowDemo;
			if (ImGui::MenuItem("V-Sync", "V-Sync On/Off")) {
				appDesc.bVsync = !appDesc.bVsync;
				glfwSwapInterval(appDesc.bVsync);
			}
			ImGui::EndMenu();
		}
#endif // DEBUG
		ImGui::EndMenuBar();
	}
}

void GUI::showSysteminfo()
{
	ImGui::Begin("System Info", NULL, ImVec2(0, 0), 0.4f, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking);
	ImGui::Text("World Time   : %.3f s", _Timer.GetTime());
	ImGui::Text("Elapsed Time : %.3f ms", 1000.0 * _Timer.GetElapsedTime());
	ImGui::Text("Frame/Second : %5.0f", _Timer.GetFPS());
	ImGui::Separator();
	ImGui::Text("Win. Size  (w, h) : %5.0f , %5.0f", appDesc.Width, appDesc.Height);
	ImGui::Text("Mouse Pos. (x, y) : %5.0f , %5.0f", appDesc.xpos, appDesc.ypos);
	ImGui::End();
}

void GUI::showStyleEditor()
{
	ImGui::Begin("Style Editor");
	ImGui::ShowStyleEditor();
	ImGui::End();
}
