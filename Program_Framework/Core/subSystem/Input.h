#pragma once
#include "ISubSystem.h"

class Input final : public ISubSystem
{
public:
	static Input& GetInstance() {
		static Input* _instance = new Input();
		return *_instance;
	}

	const bool isKeyDown(int KeyCode);
	const bool isKeyPress(int KeyCode);
	const bool isKeyUp(int KeyCode);
	const bool isKeyToggle(int KeyCode);

	const bool isMouseDown(int KeyCode);
	const bool isMouseUp(int KeyCode);

private:
	Input() {
		ZeroMemory(bKeyDown, sizeof bKeyDown);
		ZeroMemory(bKeyToggle, sizeof bKeyToggle);
		ZeroMemory(PrevKey, sizeof PrevKey);
	}

	BYTE bKeyDown[GLFW_KEY_LAST + 1];
	BYTE bKeyToggle[GLFW_KEY_LAST + 1];
	BYTE PrevKey[GLFW_KEY_LAST + 1];
};

#define _Input Input::GetInstance()