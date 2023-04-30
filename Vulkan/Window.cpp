#include "Window.h"

Window::Window()
{
}

void Window::initWindow(const char *wName, const int width, const int height)
{
	glfwInit();

	// Set GLFW for non-opengl systems
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	this->window = glfwCreateWindow(width, height, wName, nullptr, nullptr);
}

int Window::windowShouldClose()
{
	return glfwWindowShouldClose(this->window);
}

void Window::terminateAndDestroyWindow()
{
	glfwDestroyWindow(this->window);
	glfwTerminate();
}
