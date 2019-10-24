#include "stdafx.h"
#include "Task.h"

void Task::Init()
{
	pGUI = make_unique<GUI>();
	pGUI->AddWidget("Test", new TestWidget(L"Test Window"));
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

}
