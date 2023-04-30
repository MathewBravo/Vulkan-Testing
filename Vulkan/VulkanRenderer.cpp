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

	// Extensions 
	std::vector<const char*> instanceExtensions = std::vector<const char*>(); 

	// Extension Instance 
	uint32_t glfwExtensionCount = 0; 
	const char** glfwExtensions;
	// Get extensions from vulkan
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	// Add extensions to list of extensions
	for (size_t i = 0; i < glfwExtensionCount; i++) {
		instanceExtensions.push_back(glfwExtensions[i]);
	}

	// Check support for Instance Extensions
	if (!checkExtensionsSupport(&instanceExtensions)) {
		throw std::runtime_error("KkInstance extension not supported");
	}

	createInfo.enabledExtensionCount = static_cast<uint32_t>(instanceExtensions.size()); 
	createInfo.ppEnabledExtensionNames = instanceExtensions.data(); 

	// !TODO: Set Validation Layers
	createInfo.enabledLayerCount = 0;
	createInfo.ppEnabledLayerNames = nullptr;

	// Create instance
	VkResult res = vkCreateInstance(&createInfo, nullptr, &instance);
	if (res != VK_SUCCESS) {
		throw std::runtime_error("Failed to instantiate a vulkan instance");
	}
}

bool VulkanRenderer::checkExtensionsSupport(std::vector<const char*>* checkExtensions)
{
	// Get amount of extensions for array of extension creation
	uint32_t extensionCount = 0; 
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	// Create extension property list
	std::vector<VkExtensionProperties> extensions(extensionCount);
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

	// Compare extensions to availible extentions
	for (const auto& checkExtension : *checkExtensions) {
		bool hasExtension = false;
		for (const auto& extension : extensions) {
			if (strcmp(checkExtension, extension.extensionName)) {
				hasExtension = true;
				break;
			}
		}
		if (!hasExtension) {
			return false;
		}
	}
	return true; 
}

bool VulkanRenderer::checkDeviceCompatable(VkPhysicalDevice device)
{
	VkPhysicalDeviceProperties deviceProperties;
	vkGetPhysicalDeviceProperties(device, &deviceProperties);

	VkPhysicalDeviceFeatures deviceFeatures;
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

	QueueFamilyIndices indicies = getQueueFamilies(device); 

	return indicies.isValid();
}

QueueFamilyIndices VulkanRenderer::getQueueFamilies(VkPhysicalDevice device)
{
	QueueFamilyIndices indicies;

	// Get QF info for the device
	uint32_t queueFamilyCount = 0; 
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr); 

	std::vector<VkQueueFamilyProperties> queueFamilyList(queueFamilyCount); 
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyList.data()); 
	
	// Iterate QF's check that it has one of the required types
	int i = 0; 
	for (const auto& queueFamily : queueFamilyList) {
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indicies.graphicsFamily = i;
		}

		// Check if QF Indicies are valid if yes break and stop looping
		if (indicies.isValid()) {
			break;
		}
		i++; 
	}

	return indicies; 
}

void VulkanRenderer::getPhysicalDevice()
{
	// Find count of Physical Devices
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(this->instance, &deviceCount, nullptr);

	// Make sure that there are devices available.
	if (deviceCount == 0)
		throw std::runtime_error("No Vulkan Supported GPUs found");

	// Create a list of Physical Devices based on count
	std::vector<VkPhysicalDevice> deviceList(deviceCount);
	vkEnumeratePhysicalDevices(this->instance, &deviceCount, deviceList.data());

	// Pick Device
	for (const auto& device : deviceList) {
		if (checkDeviceCompatable(device)) {
			mainDevice.physicalDevice = device;
			break;
		}
	}
}

void VulkanRenderer::createLogicalDevice()
{
	QueueFamilyIndices indicides = getQueueFamilies(mainDevice.physicalDevice);

	// Queue Logical device needs create with required info
	VkDeviceQueueCreateInfo queueCreateInfo = {};
	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	queueCreateInfo.queueFamilyIndex = indicides.graphicsFamily;
	queueCreateInfo.queueCount = 1; 
	float priority = 1.0f; 
	queueCreateInfo.pQueuePriorities = &priority;
	

	VkDeviceCreateInfo deviceCreateInfo = {};
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.queueCreateInfoCount = 1;
	deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
	deviceCreateInfo.enabledExtensionCount = 0;
	deviceCreateInfo.ppEnabledExtensionNames = nullptr;

	// Physical Device Featrues the device will use
	VkPhysicalDeviceFeatures deviceFeatures = {};
	deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

	VkResult res = vkCreateDevice(mainDevice.physicalDevice, &deviceCreateInfo, nullptr, &mainDevice.logicalDevice);
	if (res != VK_SUCCESS) {
		throw std::runtime_error("Failed to create logical device");
	}

	// From logical device, queue family, and index place reference in queue
	vkGetDeviceQueue(mainDevice.logicalDevice, indicides.graphicsFamily, 0, &graphicsQueue);

}

VulkanRenderer::VulkanRenderer()
{
}

int VulkanRenderer::vulkanInit(GLFWwindow* createdWindow)
{
	this->window = createdWindow;

	try {
		createInstance();
		getPhysicalDevice(); 
		createLogicalDevice(); 
	}
	catch (const std::runtime_error &err) {
		printf("ERR: %s\n", err.what());
		return EXIT_FAILURE;
	}

	return 0;
}

void VulkanRenderer::vulkanCleanUp()
{
	vkDestroyInstance(this->instance, nullptr); 
}
