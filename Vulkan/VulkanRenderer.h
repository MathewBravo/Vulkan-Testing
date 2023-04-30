#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>

class VulkanRenderer
{
private:
	GLFWwindow *window;

	// Vulkan Components
	VkInstance instance; 
	void createInstance(); 

public:
	VulkanRenderer();
	int vulkanInit(GLFWwindow* createdWindow);

	~VulkanRenderer();
};

