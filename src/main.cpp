#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "core/utils/Log.hpp"
#include "core/Game.hpp"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[]) {
    TK_INIT_LOG;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        TK_LOG_F << "SDL initialization failed: " << SDL_GetError();
    }
    Game game;
    game.run();
}
