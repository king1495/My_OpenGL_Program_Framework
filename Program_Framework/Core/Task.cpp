#include "stdafx.h"
#include "Task.h"

void Task::Init()
{
	pGUI.reset(new GUI);
	pGUI->AddWidget("Test", new TestWidget(L"�׽�Ʈ"));
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
