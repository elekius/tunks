#ifndef TUNKS_GAME_HPP
#define TUNKS_GAME_HPP

#include <memory>
#include "TK/engine/graphics/RenderWindow.hpp"

/**
 * The main game class that contains the main loop and the window
 * @author ChikyuKido
 */
class Game {
public:
    Game();
    void resize(int width, int height);
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
