#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <iostream>
#include "Game.hpp"
#include "TK/engine/graphics/RenderWindow.hpp"
#include "TK/engine/utils/Log.hpp"
#include "manager/ResourceManager.hpp"

Game::~Game() {
}
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    Game* gameInstance = static_cast<Game*>(glfwGetWindowUserPointer(window));
    gameInstance->resize(width,height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    Game* gameInstance = static_cast<Game*>(glfwGetWindowUserPointer(window));
    gameInstance->m_keyHandler.handlerKeyEvent(window,key,scancode,action,mods);
}

Game::Game() : m_window(std::make_shared<RenderWindow>(1200, 600)) {
    glfwSetWindowUserPointer(m_window->getWindow(), this);
    glfwSetFramebufferSizeCallback(m_window->getWindow(), framebuffer_size_callback);
    glfwSetKeyCallback(m_window->getWindow(), key_callback);
}


void Game::run() {
    init();

    //TODO: Remove the loading into a loading screen
    ResourceManager::get().loadResourceDirectly<Model>("rsc/models/test.tk");
    ResourceManager::get().loadResourceDirectly<Model>("rsc/models/floor.tk");

    m_tank = std::make_shared<PlayerTank>();

    //   m_tank.scale(glm::vec3(0.1,0.1,0.1));

    ModelObject floor(ResourceManager::get().getResource<Model>("rsc/models/floor.tk"));
    floor.scale(glm::vec3(4));
    floor.rotate(90.0f,glm::vec3(-1,0,0));
    floor.translate(glm::vec3(0, 0, 0));

    int frameCount = 0;
    double totalTime = 0.0;
    double fps = 0.0;
    auto startTime = std::chrono::high_resolution_clock::now();
    int value;
    glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &value);
    std::cout <<  value << std::endl;
    bool quit = false;
    while (!quit) {
        static auto prevTime = std::chrono::high_resolution_clock::now();
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - prevTime).count();
        prevTime = currentTime;
//        m_window->getCamera()->rotate(100.0f*deltaTime,glm::vec3(0, -1, 0));
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        m_tank.rotate(10.0f * deltaTime, glm::vec3(0, -1, 0),2);
//
        m_tank->draw(*m_window);
        m_tank->update(deltaTime);

        m_window->draw(floor);
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
    TK_LOG("OpenGL")  << message;
}
void Game::init() {
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(openGLDebugCallback, nullptr);
}

void Game::resize(int width, int height) {
    m_window->resize(width,height);
}

