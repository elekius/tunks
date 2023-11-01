#include <GL/glew.h>
#include <chrono>
#include "Game.hpp"
#include "core/utils/Log.hpp"
#include "core/rendering/Mesh.hpp"
#include "core/rendering/RenderModel.hpp"

Game::~Game() {
}

Game::Game() : m_window(std::make_shared<RenderWindow>(800, 600)) {}

void Game::run() {
    init();
    RenderModel model;
    model.loadFromFile("rsc/models/tree.tk");
    model.translate(glm::vec3(0.0f, -1.0f, 1.0f));


    int frameCount = 0;
    double totalTime = 0.0;
    double fps = 0.0;
    auto startTime = std::chrono::high_resolution_clock::now();

    bool quit = false;
    SDL_Event event;
    while (!quit) {
        static auto prevTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - prevTime).count();
        prevTime = currentTime;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //model.rotate(0.2f * deltaTime, glm::vec3(0, 1, 0));
        m_window->draw(model);
        m_window->display();

        frameCount++;
        auto endTime = std::chrono::high_resolution_clock::now();
        double frameTime = std::chrono::duration<double>(endTime - startTime).count();

        if (frameTime >= 1.0) {
            fps = frameCount;
            totalTime += frameTime;
            frameCount = 0;
            startTime = endTime;
            std::cout << "FPS: " << fps << std::endl;
        }
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            m_window->handleEvent(event,deltaTime);
        }
        m_window->handleEvent(event,deltaTime);
    }
}

void openGLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message,
                         const void *userParam) {
    TK_LOG << "[OpenGL] " << message;
}

void Game::init() {
#ifdef DEBUG
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS,SDL_GL_CONTEXT_DEBUG_FLAG);
#endif
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(openGLDebugCallback, nullptr);
}
