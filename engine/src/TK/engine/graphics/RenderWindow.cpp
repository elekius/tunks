#include "RenderWindow.hpp"
#include "RenderModel.hpp"
#include "engine/utils/Log.hpp"

RenderWindow::RenderWindow(int width, int height) {
    initSDL();
    initOpenGL();
    initCamera();
    m_shader = std::make_shared<Shader>("rsc/shaders/basic/basic_shader.vert", "rsc/shaders/basic/basic_shader.frag");
}

RenderWindow::~RenderWindow() {
    SDL_Quit();
    SDL_GL_DeleteContext(m_glContext);
}

void RenderWindow::draw(RenderModel &model) {
    m_camera->update();
    m_shader->bind();
    glm::mat4 modelView = m_camera->getView() * model.getMatrix();
    glm::mat4 invModelView = glm::transpose(glm::inverse(modelView));

    // Set vertex shader uniforms
    m_shader->setUniformMatrix4fv("u_modelViewProj", m_camera->getViewProj() * model.getMatrix());
    m_shader->setUniformMatrix4fv("u_modelView", modelView);
    m_shader->setUniformMatrix4fv("u_invModelView", invModelView);

    model.draw(m_shader);
    m_shader->unbind();
}

void RenderWindow::display() {
    SDL_GL_SwapWindow(m_window);
}

void RenderWindow::initSDL() {
    m_window = SDL_CreateWindow("Tunks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    if (m_window == nullptr) {
        SDL_Quit();
        TK_LOG_F << "Window creation failed: " << SDL_GetError();
    }
}

void RenderWindow::initOpenGL() {
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
}

void RenderWindow::initCamera() {
    m_camera = std::make_shared<Camera>(90.0f, 800, 600);
    m_camera->translate(glm::vec3(0.0f, 0.0f, 5.0f));
    m_camera->update();
}
