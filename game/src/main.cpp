#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "easylogging++.h"
#include "TK/engine/utils/Log.hpp"
#include "TK/engine/loader/ModelLoader.hpp"
#include "Game.hpp"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]) {
    if (!glfwInit()) {
        TK_LOG_F("Game") << "GLFW initialization failed";
    }
    Game game;
    game.run();

}
