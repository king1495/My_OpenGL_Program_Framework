#include "stdafx.h"
#include "Core/Task.h"

APPDESC appDesc;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	ZeroMemory(&appDesc, sizeof(APPDESC));

	std::srand((unsigned int)time(NULL));

	appDesc.AppName = (char*)"Base_framework";
	appDesc.pWindow = nullptr;
	appDesc.Width = 1280;
	appDesc.Height = 720;
	appDesc.xpos = NULL;
	appDesc.ypos = NULL;
	appDesc.bFixWindow = true;
	appDesc.bVsync = true;

	std::unique_ptr<OpenGLCore> task = std::make_unique<Task>();
	task->Run();

	return 0;
}