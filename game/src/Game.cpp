#include <GL/glew.h>
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
    RenderModel model;
    model.loadFromFile("rsc/models/tree.tk");
    model.translate(glm::vec3(0.0f, -1.0f, 1.0f));
    RenderModel model2;
    model2.loadFromFile("rsc/models/enemy-tank.tk");
    model2.translate(glm::vec3(0.0f, -2.0f, 1.0f));


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
        m_window->draw(model2);
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
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                        int newWidth = event.window.data1;
                        int newHeight = event.window.data2;
                        m_window->resize(newWidth,newHeight);
                    }
                    break;
            }
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
