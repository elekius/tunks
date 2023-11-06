#ifndef TUNKS_GAME_HPP
#define TUNKS_GAME_HPP

#include <memory>
#include "TK/engine/graphics/RenderWindow.hpp"
#include "TK/engine/handler/KeyHandler.hpp"
#include "entity/PlayerTank.hpp"

/**
 * The main game class that contains the main loop and the window
 * @author ChikyuKido
 */
class Game {
public:
    KeyHandler m_keyHandler;
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
    void move(glm::vec2 move);
private:
    std::shared_ptr<RenderWindow> m_window;
    std::shared_ptr<PlayerTank> m_tank;

};


#endif
