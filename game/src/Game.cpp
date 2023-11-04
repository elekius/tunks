#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <iostream>
#include "Game.hpp"
#include "TK/engine/graphics/RenderWindow.hpp"
#include "TK/engine/utils/Log.hpp"

Game::~Game() {
}

Game::Game() : m_window(std::make_shared<RenderWindow>(1200, 600)) {
    glfwSetWindowUserPointer(m_window->getWindow(), this);
}


void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    Game* gameInstance = static_cast<Game*>(glfwGetWindowUserPointer(window));
    gameInstance->resize(width,height);
}

void Game::run() {
    init();
    std::vector<ModelObject> models;
    Model model;
    model.loadFromFile("rsc/models/fen.tk");
    for (int j = -1; j < 2; ++j) {
        for (int i = -1; i < 2; ++i) {
            models.emplace_back(&model);
            models[models.size() - 1].translate(glm::vec3(i*250, j*250, -350.0f));
        }
    }
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
        for (auto &model: models) {
            model.rotate(1.0f * deltaTime, glm::vec3(0, 1, 0));
            m_window->draw(model);
        }
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

        glfwSetFramebufferSizeCallback(m_window->getWindow(), framebuffer_size_callback);
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

void Game::resize(int width, int height) {
    m_window->resize(width,height);
}
