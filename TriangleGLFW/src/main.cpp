#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <array>
#include <set>

const size_t WIDTH=1024;
const size_t HEIGHT=720;

VkPhysicalDevice pickPhysicalDevice(const VkInstance &instance, const VkSurfaceKHR &surface);





int main()
{


  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow* window=glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
  // create our Vulkan Instance
  VkApplicationInfo appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Triangle";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;
  VkInstance instance;
  if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
  {
      std::cerr<<"failed to create instance!\n";
      std::exit(EXIT_FAILURE);
  }
  // now we attach a surface to our vulkan instance
  VkSurfaceKHR surface;

  if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
  {
      std::cerr<<"failed to create window surface!\n";
      std::exit(EXIT_FAILURE);
  }

  VkPhysicalDevice device = pickPhysicalDevice(instance,surface);
  if(device == nullptr)
  {
    std::cerr<<"cant find physical device\n";
    std::exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}



struct QueueFamilyIndices
{
  int graphicsFamily = -1;
  int presentFamily = -1;

  bool isComplete()
  {
    return graphicsFamily >= 0 && presentFamily >= 0;
  }
};

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice &device,const VkSurfaceKHR &surface)
{
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies)
    {
      if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
      {
          indices.graphicsFamily = i;
      }

      VkBool32 presentSupport = false;
      vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

      if (queueFamily.queueCount > 0 && presentSupport)
      {
          indices.presentFamily = i;
      }

      if (indices.isComplete())
          {
              break;
          }

        i++;
      }

  return indices;
}

const std::vector<const char*> deviceExtensions =
{
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};


bool checkDeviceExtensionSupport(VkPhysicalDevice device)
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    for (const auto& extension : availableExtensions)
    {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

SwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice &device,const VkSurfaceKHR &surface)
{
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

    if (formatCount != 0)
    {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

    if (presentModeCount != 0)
    {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
    }

    return details;
}


bool isDeviceSuitable(const VkPhysicalDevice &device,const VkSurfaceKHR &surface)
{
  QueueFamilyIndices indices = findQueueFamilies(device,surface);

  bool extensionsSupported = checkDeviceExtensionSupport(device);

  bool swapChainAdequate = false;
  if (extensionsSupported)
  {
      SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device,surface);
      swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
  }

  return indices.isComplete() && extensionsSupported && swapChainAdequate;
}




VkPhysicalDevice pickPhysicalDevice(const VkInstance &instance, const VkSurfaceKHR &surface)
{
    uint32_t deviceCount = 0;
    VkPhysicalDevice dev=nullptr;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0)
    {
        std::cerr<<"failed to find GPUs with Vulkan support!\n";
        std::exit(EXIT_FAILURE);
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& device : devices)
    {
      if (isDeviceSuitable(device,surface))
      {
        dev=device;

      }
    }
  return dev;
}
