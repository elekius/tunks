#ifndef TUNKS_RENDERWINDOW_HPP
#define TUNKS_RENDERWINDOW_HPP

#include <GLFW/glfw3.h>
#include <memory>
#include "Camera.hpp"
#include "Model.hpp"
#include "Shader.hpp"
#include "ModelObject.hpp"
#include "UniformBuffer.hpp"

/**
 * The wrapper class for the SDL window and the opengl initialization. It contains the camera and is responsible for rendering RenderModels.
 * It also manages the basic shader.
 * @see RenderModel.hpp
 * @author ChikyuKido
 */
class RenderWindow {
public:
    /**
     * A new RenderWindow with the given height and width.
     * @param width The width of the window
     * @param height The height of the window
     */
    RenderWindow(int width, int height);
    virtual ~RenderWindow();
    /**
     * Draws a model with the basic shader.
     * @param model The model to draw
     */
    void draw(ModelObject &modelObject);

    void display();
    void resize(int newWidth,int newHeight);
    [[nodiscard]] GLFWwindow *getWindow() const;
    [[nodiscard]] const std::shared_ptr<Camera> &getCamera() const;
    void setLightPosition(glm::vec3 position);
    void setLightColor(glm::vec3 color);


private:
    GLFWwindow *m_window;
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<Shader> m_shader;
    std::vector<ModelObject*> m_renderQueue;
    std::map<Mesh*,std::vector<glm::mat4>> m_matrices;
    UniformBuffer m_uniformBuffer;
    glm::vec3 m_lightPos;

    void initWindow(int width, int height);
    void initOpenGL();
    void initCamera();
};

#endif
