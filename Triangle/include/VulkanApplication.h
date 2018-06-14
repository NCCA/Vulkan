#ifndef VULKANAPPLICATION_H_
#define VULKANAPPLICATION_H_

#include <vector>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/glm.hpp>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <array>
#include <set>
struct QueueFamilyIndices {
    int graphicsFamily = -1;
    int presentFamily = -1;

    bool isComplete() {
        return graphicsFamily >= 0 && presentFamily >= 0;
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};



class VulkanApplication {
public:
    VulkanApplication();
    void run() ;
    void setKeyCallback(GLFWkeyfun keyCallback)
    {
      glfwSetKeyCallback(window, keyCallback);
    }

private:
    GLFWwindow* window;

    VkInstance instance;
    VkDebugReportCallbackEXT callback;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkDescriptorSetLayout descriptorSetLayout;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    VkCommandPool commandPool;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;

    std::vector<VkCommandBuffer> commandBuffers;
    VkBuffer uniformBuffer;
    VkDeviceMemory uniformBufferMemory;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    size_t currentFrame = 0;

    VkDescriptorPool descriptorPool;
    VkDescriptorSet descriptorSet;
    void initWindow();

    void initVulkan();


    void mainLoop() ;

    void cleanupSwapChain() ;

    void cleanup() ;

    void recreateSwapChain() ;

    void createInstance();

    void setupDebugCallback();

    void createSurface() ;

    void createDescriptorSetLayout() ;
    void createDescriptorSet() ;

    void pickPhysicalDevice();

    void createLogicalDevice() ;

    void createDescriptorPool();
    void createSwapChain();

    void createImageViews() ;

    void createRenderPass();

    void createGraphicsPipeline() ;

    void createFramebuffers() ;

    void createCommandPool();

    void createVertexBuffer();

    void createCommandBuffers() ;

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) ;


    void createUniformBuffer();

    void updateUniformBuffer() ;
    void createSyncObjects() ;
    void drawFrame() ;
    VkShaderModule createShaderModule(const std::vector<char>& code) ;
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) ;
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes) ;

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) ;

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device) ;
    bool isDeviceSuitable(VkPhysicalDevice device) ;
    bool checkDeviceExtensionSupport(VkPhysicalDevice device) ;

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    std::vector<const char*> getRequiredExtensions() ;

    bool checkValidationLayerSupport() ;

    static std::vector<char> readFile(const std::string& filename) ;

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData)
    ;
};

#endif
