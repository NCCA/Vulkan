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
#include "VulkanApplication.h"

void keyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);


int main() {
    VulkanApplication app;

    try {
        app.setKeyCallback(keyCallback);
        app.run();
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void keyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
  if (_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS)
  {
    exit(EXIT_SUCCESS);
  }
//    if (_key == GLFW_KEY_W && _action == GLFW_PRESS)
//    {
//      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
//    }
//    if (_key == GLFW_KEY_S && _action == GLFW_PRESS)
//    {
//      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//    }

}
