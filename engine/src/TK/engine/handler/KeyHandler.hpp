#ifndef TUNKS_KEYHANDLER_HPP
#define TUNKS_KEYHANDLER_HPP


#include <GLFW/glfw3.h>
#include <unordered_map>

class KeyHandler {
public:
    void handlerKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
};


#endif
