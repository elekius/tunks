#ifndef TUNKS_CAMERA_HPP
#define TUNKS_CAMERA_HPP

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

/**
 * @brief A simple camera class that holds the view and projection matrices.
 *
 * The Camera class is responsible for managing the view and projection matrices, which are crucial for
 * rendering 3D scenes. It provides methods for camera manipulation and updates the view projection each frame.
 * @author ChikyuKido
 */
class Camera {
public:
    /**
     * @brief Creates a new camera with the given field of view (FOV) and aspect ratio.
     *
     * @param fov The field of view (FOV) of the camera.
     * @param aspectRatio The aspect ratio (width / height) for the camera.
     */
    Camera(float fov, float aspectRatio);
    virtual void update();

    /**
     * @brief Resizes the camera to a new viewport.
     *
     * @param width The new width of the viewport.
     * @param height The new height of the viewport.
     */
    void resize(int width, int height);

    /**
     * @brief Moves the camera by the given distance.
     *
     * @param move The distance to move the camera.
     */
    void translate(glm::vec3 move);

    /**
     * @brief Rotates the camera along the specified axis by the given degrees.
     *
     * @param degrees The angle in degrees to rotate.
     * @param axis The axis of rotation.
     */
    void rotate(float degrees, glm::vec3 axis);

    [[nodiscard]] const glm::mat4 &getViewProj() const;
    [[nodiscard]] const glm::mat4 &getView() const;

protected:
    glm::vec3 m_position;  // The position of the camera.
    glm::mat4 m_projection; // The projection matrix.
    glm::mat4 m_view;       // The view matrix.
    glm::mat4 m_viewProj;   // Cached result of view * projection.
    float m_aspectRatio;   // The aspect ratio (width / height) of the camera.
    float m_fov;           // The field of view (FOV) of the camera.
};


#endif
