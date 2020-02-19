#include "stdafx.h"
#include "Task.h"

void Task::Init()
{
	pGUI = make_unique<GUI>();
	pGUI->AddWidget("Test", new TestWidget(L"Test Window"));
	pGUI->AddPopup("Test Popup", new TestPopup("Test Popup"));
	pGUI->AddPopup("Browser Popup", new BrowserPopup("Browser Popup"));
}

void Task::Update()
{
	pGUI->Update();
}

void Task::Render()
{

}

void Task::GuiRender()
{
	pGUI->GuiRender();
}

void Task::Destroy()
{
	_DB->DestroyInstance();
}
