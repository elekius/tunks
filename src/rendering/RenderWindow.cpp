/**
 * @author ChikyuKido
 */

#include "RenderWindow.hpp"
#include "utils/Log.hpp"

RenderWindow::RenderWindow(int width, int height) {
    m_window = SDL_CreateWindow("Tunks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    if (m_window == nullptr) {
        SDL_Quit();
        TK_LOG_F <<  "Window creation failed: " << SDL_GetError();
    }
    m_glContext = SDL_GL_CreateContext(m_window);
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        SDL_Quit();
        TK_LOG_F << "GLEW initialization failed: " << glewGetErrorString(glewError);
    }
    if (!GLEW_VERSION_2_1) {
        SDL_Quit();
        TK_LOG_F << "OpenGL 2.1 not supported ";
    }
    TK_LOG << "Running with OpenGL version: " << glGetString(GL_VERSION);
    m_camera = std::make_shared<Camera>(90,width,height);
    m_shader = std::make_unique<Shader>("rsc/shaders/basic/basic_shader.vert",
                                        "rsc/shaders/basic/basic_shader.frag");

    m_camera->translate(glm::vec3(0.0f,0.0f,5.0f));
    m_camera->rotateY(30);
    m_camera->update();
    init();
}

void RenderWindow::draw(RenderModel &model) {
    m_camera->update();
    m_shader->bind();
    m_shader->setUniformMatrix4fv("u_modelViewProj",m_camera->getViewProj() * model.getMatrix());
    model.draw();
    m_shader->unbind();
}

void RenderWindow::display() {
    SDL_GL_SwapWindow(m_window);
}

void RenderWindow::init() {
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}
