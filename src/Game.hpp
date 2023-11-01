#ifndef TUNKS_GAME_HPP
#define TUNKS_GAME_HPP


#include <memory>
#include <SDL2/SDL.h>
#include "rendering/RenderWindow.hpp"

class Game {
public:
    Game();
    void run();
    void init();
    virtual ~Game();
private:
    std::shared_ptr<RenderWindow> m_window;
};


#endif
