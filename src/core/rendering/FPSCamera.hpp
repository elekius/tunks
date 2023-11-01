

#ifndef TUNKS_FPSCAMERA_HPP
#define TUNKS_FPSCAMERA_HPP
/**
 * Just a test camera for easier debugging
 * @author ChikyuKido
 */
#include "Camera.hpp"
#include <glm/glm.hpp>

class FPSCamera : public Camera {
public:
    FPSCamera(float fov, float width, float height) : Camera(fov, width, height) {
        up = glm::vec3(0.0f, 1.0f, 0.0f);
        yaw = -90.0f;
        pitch = 0.0f;
        onMouseMoved(0.0f, 0.0f);
        update();
    }

    void onMouseMoved(float xRel, float yRel) {
        yaw += xRel * mouseSensitivity;
        pitch -= yRel * mouseSensitivity;
        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 front;
        front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
        front.y = sin(glm::radians(pitch));
        front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
        lookAt = glm::normalize(front);
        update();
    }

    void update() override {
        m_view = glm::lookAt(m_position, m_position+lookAt, up);
        m_viewProj = m_projection * m_view;
    }

    void moveFront(float amount) {
        translate(glm::normalize(glm::vec3(1.0f, 0.0f, 1.0f)*lookAt) * amount);
        update();
    }

    void moveSideways(float amount) {
        translate(glm::normalize(glm::cross(lookAt, up)) * amount);
        update();
    }

protected:
    float yaw;
    float pitch;
    glm::vec3 lookAt;
    const float mouseSensitivity = 0.3f;
    glm::vec3 up;
};
class FloatingCamera : public FPSCamera {
public:
    FloatingCamera(float fov, float width, float height) : FPSCamera(fov, width, height) {}

    void moveUp(float amount) {
        translate(up * amount);
    }
};
#endif
