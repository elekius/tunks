#ifndef TUNKS_RENDERWINDOW_HPP
#define TUNKS_RENDERWINDOW_HPP

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <memory>
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "RenderModel.hpp"
#include "FPSCamera.hpp"

/**
 * The wrapper class for the SDL window. It contains the camera and is responsible for the drawing of the RenderModel.
 * It also manage the basic shader
 * @see RenderModel.hpp
 * @author ChikyuKido
 */
class RenderWindow {
public:
    /**
     * A new RenderWindow with the given height und width.
     * It also tries to init glew and checks the opengl version
     * @param width the width of the window
     * @param height the height of the window
     */
    RenderWindow(int width, int height);
    virtual ~RenderWindow();

    /**
     * Draws a model with the basic shader.
     * @param model The model to draw
     */
    void draw(RenderModel &model);

    /**
     * debug code for camera movement
     * /
    void handleEvent(SDL_Event &event,float delta);

    /**
     * Waits for the current frame to finsish. Uses SDL_GL_SwapWindow
     */
    void display();

private:
    SDL_Window *m_window;
    SDL_GLContext m_glContext;
    std::shared_ptr<FloatingCamera> m_camera;
    std::shared_ptr<Shader> m_shader;

    /**
     * Inits the sdl and opengl attributes
     */
    void init();
};


#endif
