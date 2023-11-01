#ifndef TUNKS_RENDERWINDOW_HPP
#define TUNKS_RENDERWINDOW_HPP

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <memory>
#include "Camera.hpp"
#include "RenderModel.hpp"
#include "Shader.hpp"

/**
 * The wrapper class for the SDL window. It contains the camera and is responsible for rendering RenderModels.
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
    void draw(RenderModel &model);

    /**
     * Waits for the current frame to finish. Uses SDL_GL_SwapWindow.
     */
    void display();

private:
    SDL_Window *m_window;
    SDL_GLContext m_glContext;
    std::shared_ptr<Camera> m_camera;
    std::shared_ptr<Shader> m_shader;

    /**
     * Inits the SDL and OpenGL attributes.
     */
    void initSDL();
    void initOpenGL();
    void initCamera();
};

#endif
