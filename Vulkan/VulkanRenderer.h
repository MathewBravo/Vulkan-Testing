#pragma once

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>

#include "Utilities.h"

class VulkanRenderer
{
private:
	GLFWwindow *window;

	// Vulkan Components & Functions
	VkInstance instance; 
	void createInstance(); 

	// Helper Functions
	bool checkExtensionsSupport(std::vector<const char*>* checkExtensions);
	bool checkDeviceCompatable(VkPhysicalDevice device);
	QueueFamilyIndices getQueueFamilies(VkPhysicalDevice device);

	
	// Vulkan Device
	struct
	{
		VkPhysicalDevice physicalDevice;
		VkDevice logicalDevice;
	} mainDevice;
	VkQueue graphicsQueue; 

	// Vulkan Device Functions
	void getPhysicalDevice();
	void createLogicalDevice(); 

public:
	VulkanRenderer();
	int vulkanInit(GLFWwindow* createdWindow);
	void vulkanCleanUp();
	~VulkanRenderer();
};

