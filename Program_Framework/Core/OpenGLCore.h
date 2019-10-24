#pragma once

class OpenGLCore
{
public:
	OpenGLCore();
	virtual ~OpenGLCore();

	void Run();

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void GuiRender() = 0;
	virtual void Destroy() = 0;

protected:
	static bool bIconify;
	static bool bFocus;

private:
	void InitOpenGL();
	void InitImGui();

	void BeginScene();
	void EndScene();

	void BeginImGui();
	void EndImGui();

	void SetImGuiStyle();

private: // Callbacks
	static void ErrorCallback(int error, const char* description) {
		std::cout << description << std::endl;
	}

	static void WindowSizeChangeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
		glfwSetWindowSize(window, width, height);
		appDesc.Width = width;
		appDesc.Height = height;
	}

	static void WindowIconifyCallback(GLFWwindow* window, int flag) {
		bIconify = flag;
	}
	static void WindowFocusCallback(GLFWwindow* window, int flag) {
		bFocus = flag;
	}

	static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}
};