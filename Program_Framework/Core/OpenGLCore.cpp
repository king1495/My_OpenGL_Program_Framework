#include "stdafx.h"
#include "OpenGLCore.h"

bool OpenGLCore::bIconify = false;
bool OpenGLCore::bFocus = true;

OpenGLCore::OpenGLCore()
{
	InitOpenGL();
	InitImGui();
}

OpenGLCore::~OpenGLCore()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// 윈도우 제거
	glfwDestroyWindow(appDesc.pWindow);

	// GLFW 종료
	glfwTerminate();
}

void OpenGLCore::InitOpenGL()
{
	// 에러 핸들러 등록
	glfwSetErrorCallback(ErrorCallback);

	// GLFW 초기화
	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	if (appDesc.bFullScreen) {
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		appDesc.bFixWindow = true;
		appDesc.Width = width;
		appDesc.Height = height;
	}

	if (appDesc.bFixWindow) glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	appDesc.pWindow = glfwCreateWindow(appDesc.Width, appDesc.Height, appDesc.AppName, NULL, NULL);

	if (!appDesc.pWindow) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetWindowPos(appDesc.pWindow, 0.5 * (width - appDesc.Width), 0.5 * (height - appDesc.Height));

	// Set Callback Function
	glfwSetKeyCallback(appDesc.pWindow, KeyboardCallback);
	glfwSetWindowIconifyCallback(appDesc.pWindow, WindowIconifyCallback);
	glfwSetWindowFocusCallback(appDesc.pWindow, WindowFocusCallback);
	glfwSetWindowSizeCallback(appDesc.pWindow, WindowSizeChangeCallback);

	glfwMakeContextCurrent(appDesc.pWindow);

	// GLEW 초기화
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSwapInterval(appDesc.bVsync);
	glClearColor(1.0, 1.0, 1.0, 1.0);

	cout << "OpenGL Info" << endl;
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
	cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
	cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
}

void OpenGLCore::InitImGui()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Font Setting
	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/malgunbd.ttf", 16.f, NULL, io.Fonts->GetGlyphRangesKorean());
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableSetMousePos;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	//io.ConfigViewportsNoTaskBarIcon = true;
	io.ConfigDockingWithShift = true;

	// Setup Style
	SetImGuiStyle();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(appDesc.pWindow, true);
	ImGui_ImplOpenGL3_Init();
}

void OpenGLCore::BeginScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLCore::EndScene()
{
	glfwSwapBuffers(appDesc.pWindow);
}

void OpenGLCore::BeginImGui()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void OpenGLCore::EndImGui()
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(appDesc.Width, appDesc.Height);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		//GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(appDesc.pWindow);
	}
}

void OpenGLCore::SetImGuiStyle()
{
	float roundness = 2.0f;

	ImGui::StyleColorsDark();
	ImGuiStyle& style = ImGui::GetStyle();

	ImVec4 white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	ImVec4 black = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 text = ImVec4(0.76f, 0.77f, 0.8f, 1.0f);
	ImVec4 backgroundVeryDark = ImVec4(0.08f, 0.086f, 0.094f, 1.00f);
	ImVec4 backgroundDark = ImVec4(0.117f, 0.121f, 0.145f, 1.00f);
	ImVec4 backgroundMedium = ImVec4(0.26f, 0.26f, 0.27f, 1.0f);
	ImVec4 backgroundLight = ImVec4(0.37f, 0.38f, 0.39f, 1.0f);
	ImVec4 highlightBlue = ImVec4(0.172f, 0.239f, 0.341f, 1.0f);
	ImVec4 highlightBlueHovered = ImVec4(0.202f, 0.269f, 0.391f, 1.0f);
	ImVec4 highlightBlueActive = ImVec4(0.382f, 0.449f, 0.561f, 1.0f);
	ImVec4 barBackground = ImVec4(0.078f, 0.082f, 0.09f, 1.0f);
	ImVec4 bar = ImVec4(0.164f, 0.180f, 0.231f, 1.0f);
	ImVec4 barHovered = ImVec4(0.411f, 0.411f, 0.411f, 1.0f);
	ImVec4 barActive = ImVec4(0.337f, 0.337f, 0.368f, 1.0f);

	// Spatial
	style.WindowBorderSize = 1.0f;
	style.FrameBorderSize = 1.0f;
	style.FramePadding = ImVec2(5, 5);
	style.ItemSpacing = ImVec2(6, 5);
	style.Alpha = 1.0f;
	style.WindowRounding = roundness;
	style.FrameRounding = roundness;
	style.PopupRounding = roundness;
	style.GrabRounding = roundness;
	style.ScrollbarSize = 20.0f;
	style.ScrollbarRounding = roundness;

	// Colors
	style.Colors[ImGuiCol_Text] = text;
	style.Colors[ImGuiCol_WindowBg] = backgroundDark;
	style.Colors[ImGuiCol_Border] = black;
	style.Colors[ImGuiCol_FrameBg] = bar;
	style.Colors[ImGuiCol_FrameBgHovered] = highlightBlue;
	style.Colors[ImGuiCol_FrameBgActive] = highlightBlueHovered;
	style.Colors[ImGuiCol_TitleBg] = backgroundVeryDark;
	style.Colors[ImGuiCol_TitleBgActive] = bar;
	style.Colors[ImGuiCol_MenuBarBg] = backgroundVeryDark;
	style.Colors[ImGuiCol_ScrollbarBg] = barBackground;
	style.Colors[ImGuiCol_ScrollbarGrab] = bar;
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = barHovered;
	style.Colors[ImGuiCol_ScrollbarGrabActive] = barActive;
	style.Colors[ImGuiCol_CheckMark] = white;
	style.Colors[ImGuiCol_SliderGrab] = bar;
	style.Colors[ImGuiCol_SliderGrabActive] = barActive;
	style.Colors[ImGuiCol_Button] = barActive;
	style.Colors[ImGuiCol_ButtonHovered] = highlightBlue;
	style.Colors[ImGuiCol_ButtonActive] = highlightBlueActive;
	style.Colors[ImGuiCol_Header] = highlightBlue; // selected items (tree, menu bar etc.)
	style.Colors[ImGuiCol_HeaderHovered] = highlightBlueHovered; // hovered items (tree, menu bar etc.)
	style.Colors[ImGuiCol_HeaderActive] = highlightBlueActive;
	style.Colors[ImGuiCol_Separator] = backgroundLight;
	style.Colors[ImGuiCol_ResizeGrip] = backgroundMedium;
	style.Colors[ImGuiCol_ResizeGripHovered] = highlightBlue;
	style.Colors[ImGuiCol_ResizeGripActive] = highlightBlueHovered;
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.7f, 0.77f, 1.0f);
	style.Colors[ImGuiCol_PlotHistogram] = highlightBlue; // Also used for progress bar
	style.Colors[ImGuiCol_PlotHistogramHovered] = highlightBlueHovered;
	style.Colors[ImGuiCol_TextSelectedBg] = highlightBlue;
	style.Colors[ImGuiCol_PopupBg] = backgroundDark;
	style.Colors[ImGuiCol_DragDropTarget] = backgroundLight;
}

void OpenGLCore::Run()
{
	assert(appDesc.pWindow);

	//Main Initialize
	Init();

	while (!glfwWindowShouldClose(appDesc.pWindow))
	{
		_Timer.Update();
		glfwPollEvents();

		if (bIconify) continue;
		Update();

		BeginScene();

		Render();

		BeginImGui();
		GuiRender();
		EndImGui();

		EndScene();
	}
	//Main Shutdown
	Destroy();
}
