#ifndef TUNKS_PLAYERTANK_HPP
#define TUNKS_PLAYERTANK_HPP


#include "TK/engine/graphics/ModelObject.hpp"
#include "TK/engine/graphics/RenderWindow.hpp"
#include "Tank.hpp"
/**
 *
 * @author ChikyuKido
 */
class PlayerTank : public Tank{
public:
    PlayerTank();
    void update(float deltaTime) override;
    void draw(RenderWindow &window) override;
private:
    bool left=false,right=false,up=false,down=false;
};


#endif
