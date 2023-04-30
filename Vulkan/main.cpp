#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

#include "Window.h";
#include "VulkanRenderer.h"


int main() {
	Window* window = new Window();
	VulkanRenderer* vulkanRenderer = new VulkanRenderer();
	window->initWindow("Test Window", 800, 600);	
	if (vulkanRenderer->vulkanInit(window->window) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	while (!window->windowShouldClose()) {
		glfwPollEvents(); 
	}

	vulkanRenderer->vulkanCleanUp(); 
	window->terminateAndDestroyWindow(); 
	return 0;
}