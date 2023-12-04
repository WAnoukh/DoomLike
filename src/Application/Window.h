#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Application;

class Window
{
public:
	Window(Application& app): application(app), window(nullptr) {}
	Window(const Window&) = delete;
	Window& operator=(Window const&) = delete;

	GLFWwindow * getGLFWwindow() { return window; };

    int init();
	void PreRender() const;
    void PostRender() const;
	void terminate() const;
    bool shouldClose() const { return glfwWindowShouldClose(window); }

private:
	const Application& application;

	
    GLFWwindow* window;
};

