#ifndef TUNKS_RENDERWINDOW_HPP
#define TUNKS_RENDERWINDOW_HPP

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <memory>
#include "Camera.hpp"
#include "Model.hpp"
#include "Shader.hpp"
#include "ModelObject.hpp"

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

    /**
     * Waits for the current frame to finish. Uses SDL_GL_SwapWindow.
     */
    void display();

    void resize(int newWidth,int newHeight);

private:
    SDL_Window *m_window;
    SDL_GLContext m_glContext;
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<Shader> m_shader;

    void initSDL(int width,int height);
    void initOpenGL();
    void initCamera();
};

#endif
