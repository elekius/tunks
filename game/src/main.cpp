#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "easylogging++.h"
#include "TK/engine/utils/Log.hpp"
#include "Game.hpp"
#include "TK/engine/debug/Instrumentor.hpp"
#include "manager/ResourceManager.hpp"

void initResourceLoader();

INITIALIZE_EASYLOGGINGPP


int main(int argc, char *argv[]) {
    TK_INIT_LOG;
    initResourceLoader();
    if (!glfwInit()) {
        TK_LOG_F("Game") << "GLFW initialization failed";
    }
    TK_PROFILE_BEGIN_SESSION("Startup","startup.json");
    Game game;
    TK_PROFILE_END_SESSION();
    TK_PROFILE_BEGIN_SESSION("Gameloop","GameLoop.json");
    game.run();
    TK_PROFILE_END_SESSION();
}

void initResourceLoader() {
    ResourceManager::get().addResourceLoader<Model>([](const std::string &path) -> std::shared_ptr<Model>{
        std::shared_ptr<Model> modelPtr = std::make_shared<Model>();
        modelPtr->loadFromFile(path);
        return modelPtr;
    });
}
