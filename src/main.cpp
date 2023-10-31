#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "utils/Log.hpp"
#include "rendering/Vertex.hpp"
#include "rendering/RenderModel.hpp"

int main(int argc, char* argv[]) {
    TK_INIT_LOG
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        TK_LOG_F << "SDL initialization failed: " << SDL_GetError();
    }
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window* window = SDL_CreateWindow("Tunks", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        SDL_Quit();
        TK_LOG_F <<  "Window creation failed: " << SDL_GetError();
    }
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        TK_LOG_F << "GLEW initialization failed: " << glewGetErrorString(glewError);
    }

    if (!GLEW_VERSION_2_1) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        TK_LOG_F << "OpenGL 2.1 not supported ";
    }
    TK_LOG << "Running with OpenGL version: " << glGetString(GL_VERSION);

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

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
