#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "utils/Log.hpp"
#include "rendering/RenderModel.hpp"
#include "Game.hpp"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char* argv[]) {
    TK_INIT_LOG;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        TK_LOG_F << "SDL initialization failed: " << SDL_GetError();
    }
    Game game;
    game.run();
}
