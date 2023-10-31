#ifndef TUNKS_GAME_HPP
#define TUNKS_GAME_HPP


#include <memory>
#include <SDL2/SDL.h>

class Game {
public:
    Game();
    void run();
    void init();
    virtual ~Game();
private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
};


#endif
