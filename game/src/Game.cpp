#include <glad/glad.h>
#include <chrono>
#include <iostream>
#include "Game.hpp"
#include "TK/engine/graphics/RenderWindow.hpp"
#include "TK/engine/utils/Log.hpp"

Game::~Game() {
}

Game::Game() : m_window(std::make_shared<RenderWindow>(1200, 600)) {}

void Game::run() {
    init();
    Model model;
    model.loadFromFile("rsc/models/test-monkey.tk");
    ModelObject modelObject(&model);
    modelObject.translate(glm::vec3(-2,0,0));
    ModelObject modelObject2(&model);
    modelObject2.translate(glm::vec3(2,0,0));

    int frameCount = 0;
    double totalTime = 0.0;
    double fps = 0.0;
    auto startTime = std::chrono::high_resolution_clock::now();

    bool quit = false;
    while (!quit) {
        static auto prevTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - prevTime).count();
        prevTime = currentTime;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        modelObject.rotate(1.0f * deltaTime, glm::vec3(0, 1, 0));
        modelObject2.rotate(1.0f * deltaTime, glm::vec3(0, -1, 0));
        m_window->draw(modelObject);
        m_window->draw(modelObject2);
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

        glfwPollEvents();
        if (glfwWindowShouldClose(m_window->getWindow())) {
            quit = true;
        }
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
