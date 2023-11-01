#ifndef TUNKS_GAME_HPP
#define TUNKS_GAME_HPP


#include <memory>
#include <SDL2/SDL.h>
#include "core/rendering/RenderWindow.hpp"

/**
 * The main game class that contains the main loop and the window
 * @author ChikyuKido
 */
class Game {
public:
    Game();
    /**
     * starts the game
     */
    void run();
    /**
     * init the basic stuff
     */
    void init();
    virtual ~Game();
private:
    std::shared_ptr<RenderWindow> m_window;
};


#endif
