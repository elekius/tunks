#ifndef TUNKS_RENDERWINDOW_HPP
#define TUNKS_RENDERWINDOW_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Camera.hpp"
#include "Model.hpp"
#include "Shader.hpp"
#include "ModelObject.hpp"
#include "ShaderStorageBuffer.hpp"

/**
 * @brief The wrapper class for the Glfw window and OpenGL initialization. It contains the camera
 * and is responsible for rendering RenderModels. It also manages the basic shader.
 *
 * @see RenderModel.hpp
 * @author ChikyuKido
 */
class RenderWindow {
public:
    /**
     * @brief Constructs a new RenderWindow with the given width and height.
     *
     * @param width The width of the window.
     * @param height The height of the window.
     */
    RenderWindow(int width, int height);
    virtual ~RenderWindow();

    /**
     * @brief Adds a model to the renderQueue.
     *
     * @param modelObject The model object to draw.
     */
    void draw(ModelObject &modelObject);

    /**
     * @brief Renders all the models in the queue with instanced Rendering.
     */
    void display();

    /**
     * @brief Resizes the window to the specified width and height.
     *
     * @param newWidth The new width of the window.
     * @param newHeight The new height of the window.
     */
    void resize(int newWidth, int newHeight);


    [[nodiscard]] GLFWwindow *getWindow() const;
    [[nodiscard]] const std::shared_ptr<Camera> &getCamera() const;
    void setLightPosition(glm::vec3 position);
    void setLightColor(glm::vec3 color);

private:
    GLFWwindow *m_window;
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<Shader> m_shader;
    std::vector<ModelObject*> m_renderQueue;
    std::unordered_map<const Mesh*, std::vector<glm::mat4>> m_matrices;
    ShaderStorageBuffer m_uniformBuffer;
    glm::vec3 m_lightPos;

    void initWindow(int width, int height);
    void initOpenGL();
    void initCamera();
};

#endif
