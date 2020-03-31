#pragma once
#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <Windows.h>
#include <io.h>
#include <assert.h>
#include <math.h>
#include <time.h>

//STL
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <queue>
#include <map>
#include <functional>
#include <thread>
#include <mutex>
#include <random>
using namespace std;

// OpenGL Library
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")

// OpenGL Mathmetics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/color_encoding.hpp>
using namespace glm;

// ImGui Library
#define IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>
#include <ImGuiPlotter/ImGuiPlotter.hpp>
#include <imGuiKR/ImGuiKR.h>

// Frameworks
#include "defines.h"
#include "utility.h"

#include "Core/subSystem/Config.h"
#include "Core/subSystem/Timer.h"
#include "Core/subSystem/Logger.h"
#include "Core/subSystem/Input.h"
#include "Core/subSystem/ThreadPool.h"
#include "Core/subSystem/GUI.h"

// AppSettings
struct APPDESC
{
	char* AppName;
	GLFWwindow* pWindow;
	float Width;
	float Height;
	float xpos;
	float ypos;
	bool bVsync;
	bool bFixWindow;
	bool bFullScreen;
};
extern APPDESC appDesc;
