//
// Created by kido on 11/6/23.
//

#include "PlayerTank.hpp"
#include "TK/engine/events/Events.hpp"

void PlayerTank::draw(RenderWindow &renderWindow) {
    if(down) {
        modelObject->translate(glm::vec3(0,0,0.1f));
        modelObject->setRotation(0,glm::vec3(0,1,0));
    }
    if(up) {
        modelObject->translate(glm::vec3(0,0,-0.1f));
        modelObject->setRotation(180,glm::vec3(0,1,0));
    }
    if(left) {
        modelObject->translate(glm::vec3(-0.1,0,0.0f));
        modelObject->setRotation(270,glm::vec3(0,1,0));
    }
    if(right) {
        modelObject->translate(glm::vec3(0.1,0,0.0f));
        modelObject->setRotation(90,glm::vec3(0,1,0));
    }
    renderWindow.draw(*modelObject);
}

PlayerTank::PlayerTank() {
    Model* model = new Model();
    model->loadFromFile("rsc/models/test.tk");
    modelObject = new ModelObject(model);
    Events::subscribe<KeyPressedEvent>([this](const KeyPressedEvent *event) {
       if(event->keyCode == GLFW_KEY_W) {
           this->up = true;
       }
        if(event->keyCode == GLFW_KEY_S) {
            this->down = true;
        }
        if(event->keyCode == GLFW_KEY_A) {
            this->left = true;
        }
        if(event->keyCode == GLFW_KEY_D) {
            this->right = true;

        }

    });
    Events::subscribe<KeyReleasedEvent>([this](const KeyReleasedEvent *event) {
        if(event->keyCode == GLFW_KEY_W) {
            this->up = false;
        }
        if(event->keyCode == GLFW_KEY_S) {
            this->down = false;
        }
        if(event->keyCode == GLFW_KEY_A) {
            this->left = false;
        }
        if(event->keyCode == GLFW_KEY_D) {
            this->right = false;
        }
    });
}
