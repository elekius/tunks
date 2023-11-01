#include "Camera.hpp"


Camera::Camera(float fov, float width, float height) {
    m_projection = glm::perspective(fov / 2.0f, width / height, 0.1f, 1000.0f);
    m_view = glm::mat4(1.0f);
    m_position = glm::vec3(0.0f);
    update();
}

void Camera::update() {
    m_viewProj = m_projection * m_view;
}


void Camera::translate(glm::vec3 move) {
    m_position += move;
    m_view = glm::translate(m_view, move*-1.0f);
}

void Camera::rotate(float degrees, glm::vec3 axis) {
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(degrees), axis);
    m_view = rotation * m_view;
    update();
}

const glm::mat4 &Camera::getViewProj() const {
    return m_viewProj;
}


const glm::mat4 &Camera::getView() const {
    return m_view;
}
