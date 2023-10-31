
#include <GL/glew.h>
#include "Game.hpp"
#include "utils/Log.hpp"
#include "rendering/RenderModel.hpp"

Game::~Game() {
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

Game::Game() : m_window(SDL_CreateWindow("Tunks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL)){
    if (m_window == nullptr) {
        SDL_Quit();
        TK_LOG_F <<  "Window creation failed: " << SDL_GetError();
    }
    m_glContext = SDL_GL_CreateContext(m_window);

    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        TK_LOG_F << "GLEW initialization failed: " << glewGetErrorString(glewError);
    }
    if (!GLEW_VERSION_2_1) {
        TK_LOG_F << "OpenGL 2.1 not supported ";
    }
    TK_LOG << "Running with OpenGL version: " << glGetString(GL_VERSION);
}

void Game::run() {
    init();
    RenderModel model;
    model.createFromFile("");
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        model.draw();
        SDL_GL_SwapWindow(m_window);
    }
}

void Game::init() {
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}
