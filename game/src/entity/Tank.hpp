#ifndef TUNKS_TANK_HPP
#define TUNKS_TANK_HPP

#include "TK/engine/graphics/RenderWindow.hpp"

/**
 *
 * @author ChikyuKido
 */
class Tank {
public:
    virtual void update(float deltaTime);
    virtual void draw(RenderWindow &window);
protected:
    std::shared_ptr<ModelObject> m_tank;

};


#endif
