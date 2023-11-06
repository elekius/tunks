#include "PlayerTank.hpp"
#include "TK/engine/events/Events.hpp"

PlayerTank::PlayerTank() {
    //TODO: Resource manager. Currently this is a memory leak but who cares
    Model* model = new Model();
    model->loadFromFile("rsc/models/test.tk");
    m_tank = std::make_shared<ModelObject>(model);
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

void PlayerTank::update(float deltaTime) {
    if(down) {
        m_tank->setRotation(0,glm::vec3(0,1,0));
    }
    if(up) {
        m_tank->setRotation(180,glm::vec3(0,1,0));
    }
    if(left) {
        m_tank->setRotation(270,glm::vec3(0,1,0));
    }
    if(right) {
        m_tank->setRotation(90,glm::vec3(0,1,0));
    }
    if(left || right || up || down) {
        m_tank->translate(glm::vec3(0,0,1.0f*deltaTime));
    }
}

void PlayerTank::draw(RenderWindow &window) {
    Tank::draw(window);
}
