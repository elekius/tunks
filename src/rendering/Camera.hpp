#ifndef TUNKS_CAMERA_HPP
#define TUNKS_CAMERA_HPP
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
public:
    Camera(float fov,float width,float height);
    [[nodiscard]] const glm::mat4 &getViewProj() const;
    void update();
    void translate(glm::vec3 move);
    void rotateY(float degrees);
private:
    glm::mat4 m_projection;
    glm::mat4 m_view;
    glm::mat4 m_viewProj; // cached result of view * projection
};


#endif
