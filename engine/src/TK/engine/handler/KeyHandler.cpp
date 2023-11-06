#include "KeyHandler.hpp"
#include "engine/events/Events.hpp"

void KeyHandler::handlerKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        Events::fire(new KeyPressedEvent(key));
    }else if(action == GLFW_RELEASE) {
        Events::fire(new KeyReleasedEvent(key));
    }
}
