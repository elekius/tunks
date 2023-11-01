/**
 * @author ChikyuKido
 */

#ifndef TUNKS_RENDERWINDOW_HPP
#define TUNKS_RENDERWINDOW_HPP

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <memory>
#include "Camera.hpp"
#include "RenderModel.hpp"
#include "Shader.hpp"

class RenderWindow {
public:
    RenderWindow(int width,int height);
    void draw(RenderModel& model);
    void display();
private:
    SDL_Window* m_window;
    SDL_GLContext m_glContext;
    std::shared_ptr<Camera> m_camera;
    std::unique_ptr<Shader> m_shader;

    void init();
};


#endif
