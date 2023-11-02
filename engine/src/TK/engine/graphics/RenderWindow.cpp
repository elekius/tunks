#include "RenderWindow.hpp"
#include "Model.hpp"
#include "engine/utils/Log.hpp"
#include "ModelObject.hpp"

RenderWindow::RenderWindow(int width, int height) {
    initSDL(width,height);
    initOpenGL();
    initCamera();
    m_shader = std::make_shared<Shader>("engine/shaders/basic/basic_shader.vert", "engine/shaders/basic/basic_shader.frag");
    m_shader->bind();
    m_shader->setUniformVec3("u_lightColor",glm::vec3(1.0f,1.f,1.0f));
    m_shader->unbind();
    resize(width,height);
    m_renderQueue.reserve(1000);
}

RenderWindow::~RenderWindow() {
    SDL_Quit();
    SDL_GL_DeleteContext(m_glContext);
}
void RenderWindow::draw(ModelObject &modelObject) {
    m_camera->update();
    m_renderQueue.push_back(&modelObject);
}
glm::vec3 sunDirection = glm::vec3(1.0f);
void RenderWindow::display() {
    glm::vec4 lightDirection = glm::transpose(glm::inverse(m_camera->getView())) * glm::vec4(sunDirection,1.0f);
    m_shader->bind();
    m_shader->setUniformVec3("u_lightDirection",lightDirection);
    for (const auto &model : m_renderQueue) {
        glm::mat4 modelView = m_camera->getView() * model->getMatrix();
        glm::mat4 invModelView = glm::transpose(glm::inverse(modelView));

        // Set vertex shader uniforms
        m_shader->setUniformMatrix4fv("u_modelViewProj", m_camera->getViewProj() * model->getMatrix());
        m_shader->setUniformMatrix4fv("u_modelView", modelView);
        m_shader->setUniformMatrix4fv("u_invModelView", invModelView);
        model->draw(m_shader);
    }
    m_shader->unbind();
    m_renderQueue.clear();

    SDL_GL_SwapWindow(m_window);
}


void RenderWindow::initSDL(int width, int height) {
    m_window = SDL_CreateWindow("Tunks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
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
    glEnable(GL_DEPTH_TEST);
    SDL_GL_SetSwapInterval(0);
}

void RenderWindow::initCamera() {
    m_camera = std::make_shared<Camera>(90.0f,16/9);
    m_camera->translate(glm::vec3(0.0f, 0.0f, 10.0f));
    m_camera->update();
}

void RenderWindow::resize(int newWidth, int newHeight) {
    glViewport(0, 0, newWidth, newHeight);
}

