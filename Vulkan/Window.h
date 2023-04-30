#pragma once 
#include <GLFW/glfw3.h> 
#include <string>

class Window { 
public:
	GLFWwindow* window; 
	Window(); 
	void initWindow(const char *wName, const int width, const int height);
	int windowShouldClose();
	void terminateAndDestroyWindow();

};
 