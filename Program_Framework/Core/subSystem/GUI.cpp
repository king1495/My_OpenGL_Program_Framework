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
	, iHeight(appDesc.Height)
	, iWidth(appDesc.Width)
{
}

GUI::~GUI()
{
	for (auto popup : popups)
		SAFE_DELETE(popup.second);

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

void GUI::AddPopup(const string& name, IPopup* popup)
{
	assert(popups.count(name) < 1);
	popups[name] = popup;
}

void GUI::DeletePopup(const string& name)
{
	if (popups.count(name) < 1) return;
	SAFE_DELETE(popups[name]);
	popups.erase(name);
}

void GUI::ActivePopup(const string& name)
{
	if (popups.count(name) < 1) return;
	popups[name]->SetisActive(true);
}

void GUI::Update()
{
	if (!isActive) return;

	for (auto widget : widgets)
		widget.second->Update();

	for (auto popup : popups)
		popup.second->Update();

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

	for (auto popup : popups)
		popup.second->Render();

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
			if (ImGui::MenuItem("V-Sync", NULL, appDesc.bVsync)) {
				appDesc.bVsync = !appDesc.bVsync;
				glfwSwapInterval(appDesc.bVsync);
			}

			if (ImGui::MenuItem("Full Screen", NULL, appDesc.bFullScreen)) {
				appDesc.bFullScreen = !appDesc.bFullScreen;
				int width = GetSystemMetrics(SM_CXSCREEN);
				int height = GetSystemMetrics(SM_CYSCREEN);

				if (appDesc.bFullScreen) {
					glfwSetWindowAttrib(appDesc.pWindow, GLFW_RESIZABLE, GLFW_FALSE);
					glfwSetWindowAttrib(appDesc.pWindow, GLFW_DECORATED, GLFW_FALSE);
					glfwSetWindowAttrib(appDesc.pWindow, GLFW_FLOATING, GLFW_TRUE);
					iWidth = appDesc.Width;
					iHeight = appDesc.Height;
					appDesc.Width = width;
					appDesc.Height = height;
				}
				else {
					glfwSetWindowAttrib(appDesc.pWindow, GLFW_FLOATING, GLFW_FALSE);
					glfwSetWindowAttrib(appDesc.pWindow, GLFW_DECORATED, GLFW_TRUE);
					if (!appDesc.bFixWindow) glfwSetWindowAttrib(appDesc.pWindow, GLFW_RESIZABLE, GLFW_TRUE);
					appDesc.Width = iWidth;
					appDesc.Height = iHeight;
				}

				glfwSetWindowPos(appDesc.pWindow, 0.5 * (width - appDesc.Width), 0.5 * (height - appDesc.Height));
				glfwSetWindowSize(appDesc.pWindow, appDesc.Width, appDesc.Height);
			}

			ImGui::Separator();

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

		if (!popups.empty()) {
			if (ImGui::BeginMenu("Option"))
			{
				for (auto popup : popups) {
					if (ImGui::MenuItem(popup.second->GetName().c_str())) {
						popup.second->SetisActive(true);
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
