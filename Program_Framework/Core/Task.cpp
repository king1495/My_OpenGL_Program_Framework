#include "stdafx.h"
#include "Task.h"

int ThreadFunc(int temp) {
	for (int i = 0; i < temp; i++)
	{
		cout << temp << " : " << i << endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	return temp * temp;
}

void Task::Init()
{
	pGUI = make_unique<GUI>();
	pGUI->AddWidget("Test", new TestWidget(L"Test Window"));
	pGUI->AddPopup("Test Popup", new TestPopup("Test Popup"));
	pGUI->AddPopup("Browser Popup", new BrowserPopup("Browser Popup"));

	for (int i = 0; i < 10; ++i) {
		std::future<int> temp = _ThreadPool.EnqueueTask(ThreadFunc, i);
		if (std::future_status::ready == temp.wait_for(std::chrono::milliseconds(1)))
			cout << "Result : " << temp.get() << endl;
	}
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
