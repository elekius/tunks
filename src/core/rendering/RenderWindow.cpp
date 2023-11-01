#include "RenderWindow.hpp"
#include "core/utils/Log.hpp"
#include "RenderModel.hpp"

RenderWindow::RenderWindow(int width, int height) {
    m_window = SDL_CreateWindow("Tunks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    if (m_window == nullptr) {
        SDL_Quit();
        TK_LOG_F << "Window creation failed: " << SDL_GetError();
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
   // m_camera = std::make_shared<Camera>(90, width, height);
    m_camera = std::make_shared<FloatingCamera>(90.0f, width, height);
    m_shader = std::make_shared<Shader>("rsc/shaders/basic/basic_shader.vert",
                                        "rsc/shaders/basic/basic_shader.frag");

    m_camera->translate(glm::vec3(0.0f, 0.0f, 5.0f));
   // m_camera->rotateY(30);
    m_camera->update();
    init();
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
    //vertex shader uniforms
    m_shader->setUniformMatrix4fv("u_modelViewProj", m_camera->getViewProj() * model.getMatrix());
    m_shader->setUniformMatrix4fv("u_modelView", modelView);
    m_shader->setUniformMatrix4fv("u_invModelView", invModelView);
    model.draw(m_shader);
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

    //glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}
//debug code
bool buttonW = false;
bool buttonS = false;
bool buttonA = false;
bool buttonD = false;
bool buttonSpace = false;
bool buttonShift = false;
float cameraSpeed = 6.0f;
//debug code
void RenderWindow::handleEvent(SDL_Event &event,float delta) {
if(event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
            case SDLK_w:
                buttonW = true;
                break;
            case SDLK_s:
                buttonS = true;
                break;
            case SDLK_a:
                buttonA = true;
                break;
            case SDLK_d:
                buttonD = true;
                break;
            case SDLK_SPACE:
                buttonSpace = true;
                break;
            case SDLK_LSHIFT:
                buttonShift = true;
                break;
            case SDLK_ESCAPE:
                SDL_SetRelativeMouseMode(SDL_FALSE);
                break;
        }
    } else if(event.type == SDL_KEYUP) {
        switch(event.key.keysym.sym)  {
            case SDLK_w:
                buttonW = false;
                break;
            case SDLK_s:
                buttonS = false;
                break;
            case SDLK_a:
                buttonA = false;
                break;
            case SDLK_d:
                buttonD = false;
                break;
            case SDLK_SPACE:
                buttonSpace = false;
                break;
            case SDLK_LSHIFT:
                buttonShift = false;
                break;
        }
    } else if(event.type == SDL_MOUSEMOTION) {
        if(SDL_GetRelativeMouseMode()) {
            m_camera->onMouseMoved(event.motion.xrel, event.motion.yrel);
        }
    } else if(event.type == SDL_MOUSEBUTTONDOWN) {
        if(event.button.button == SDL_BUTTON_LEFT) {
            SDL_SetRelativeMouseMode(SDL_TRUE);
        }
    }
    if(buttonW) {
        m_camera->moveFront(delta * cameraSpeed);
    }
    if(buttonS) {
        m_camera->moveFront(-delta * cameraSpeed);
    }if(buttonA) {
        m_camera->moveSideways(-delta * cameraSpeed);
    }if(buttonD) {
        m_camera->moveSideways(delta * cameraSpeed);
    }if(buttonSpace) {
        m_camera->moveUp(delta * cameraSpeed);
    }if(buttonShift) {
        m_camera->moveUp(-delta * cameraSpeed);
    }

    m_camera->update();

}

