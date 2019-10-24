#include "stdafx.h"
#include "Input.h"

const bool Input::isKeyDown(int KeyCode)
{
	if (!glfwGetWindowAttrib(appDesc.pWindow, GLFW_FOCUSED)) return false;
	if (GetAsyncKeyState(KeyCode) & 0x8000) {
		if (!bKeyDown[KeyCode]) {
			bKeyDown[KeyCode] = 0x01;
			return true;
		}
	}
	else bKeyDown[KeyCode] = 0x00;
	return false;
}

const bool Input::isKeyPress(int KeyCode)
{
	if (!glfwGetWindowAttrib(appDesc.pWindow, GLFW_FOCUSED)) return false;
	if (GetAsyncKeyState(KeyCode) & 0x8000) {
		PrevKey[KeyCode] = 0x01;
		return true;
	}
	return false;
}

const bool Input::isKeyUp(int KeyCode)
{
	if (!glfwGetWindowAttrib(appDesc.pWindow, GLFW_FOCUSED)) return false;
	if (!isKeyPress(KeyCode)) {
		if (PrevKey[KeyCode]) {
			PrevKey[KeyCode] = 0x00;
			return true;
		}
	}
	return false;
}

const bool Input::isKeyToggle(int KeyCode)
{
	if (!glfwGetWindowAttrib(appDesc.pWindow, GLFW_FOCUSED)) return false;
	if (GetKeyState(KeyCode) & 0x0001) return true;
	return false;
}

const bool Input::isMouseDown(int KeyCode)
{
	if (!glfwGetWindowAttrib(appDesc.pWindow, GLFW_FOCUSED)) return false;
	int state = glfwGetMouseButton(appDesc.pWindow, KeyCode);
	return state == GLFW_PRESS;
}

const bool Input::isMouseUp(int KeyCode)
{
	if (!glfwGetWindowAttrib(appDesc.pWindow, GLFW_FOCUSED)) return false;
	int state = glfwGetMouseButton(appDesc.pWindow, KeyCode);
	return state == GLFW_RELEASE;
}