#include "VulkanRenderer.h"

void VulkanRenderer::createInstance()
{

	// Creating information for app
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Vulkan App";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "N/A";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_3;

	// Creating information for vkinstance
	VkInstanceCreateInfo createInfo = {}; 
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

}

VulkanRenderer::VulkanRenderer()
{
}

int VulkanRenderer::vulkanInit(GLFWwindow* createdWindow)
{
	this->window = createdWindow;

	try {
		createInstance();
	}
	catch (const std::runtime_error &err) {
		printf("ERR: %s\n", err.what());
		return EXIT_FAILURE;
	}

	return 0;
}
