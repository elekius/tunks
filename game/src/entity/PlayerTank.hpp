//
// Created by kido on 11/6/23.
//

#ifndef TUNKS_PLAYERTANK_HPP
#define TUNKS_PLAYERTANK_HPP


#include "TK/engine/graphics/ModelObject.hpp"
#include "TK/engine/graphics/RenderWindow.hpp"

class PlayerTank {
public:
    PlayerTank();
    void draw(RenderWindow &renderWindow);
private:
    bool left=false,right=false,up=false,down=false;
    ModelObject* modelObject;
};


#endif
