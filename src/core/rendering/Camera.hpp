#ifndef TUNKS_CAMERA_HPP
#define TUNKS_CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
/**
 * A simple camera class that holds the view and the projection. Used for the projectionView
 * @author ChikyuKido
 */
class Camera {
public:
    /**
     * Creates a new camera with the given FOV and the given height and width for the ratio
     * @param fov the fov of the camera
     * @param width the width for the ratio
     * @param height the height for the ratio
     */
    Camera(float fov, float width, float height);

    /**
     * Creates the view projection for the model.
     * @return The combined view and projection
     */
    [[nodiscard]] const glm::mat4 &getViewProj() const;

    /**
     * Updates the view projection each frame
     */
    void update();

    /**
     * Moves the camera with the given distance
     * @param move the distance to move
     */
    void translate(glm::vec3 move);

    /**
     * Rotates the camera along the y axis.
     * @param degrees the angle in degrees
     */
    void rotateY(float degrees);

private:
    glm::mat4 m_projection;
    glm::mat4 m_view;
    glm::mat4 m_viewProj; // cached result of view * projection
};


#endif