cmake_minimum_required(VERSION 3.26)
project(TK_Engine)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(GLEW REQUIRED)


include_directories(
        src/TK
)
set(SOURCE_FILES
        src/TK/engine/Defines.hpp
        src/TK/engine/utils/Log.hpp
        src/TK/engine/graphics/Mesh.cpp
        src/TK/engine/graphics/Mesh.hpp
        src/TK/engine/graphics/Vertex.hpp
        src/TK/engine/graphics/VertexBuffer.cpp
        src/TK/engine/graphics/VertexBuffer.hpp
        src/TK/engine/graphics/Shader.cpp
        src/TK/engine/graphics/Shader.hpp
        src/TK/engine/graphics/Camera.cpp
        src/TK/engine/graphics/Camera.hpp
        src/TK/engine/graphics/RenderWindow.cpp
        src/TK/engine/graphics/RenderWindow.hpp
        src/TK/engine/graphics/RenderModel.cpp
        src/TK/engine/graphics/RenderModel.hpp
        src/TK/engine/graphics/FPSCamera.hpp
)
set(LIBRARY_FILES
        ${CMAKE_SOURCE_DIR}/libs/easyloggingpp/easylogging++.cc

)
add_library(TK_Engine
      ${SOURCE_FILES} ${LIBRARY_FILES}
)

target_include_directories(TK_Engine PUBLIC
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(TK_Engine PUBLIC
        SDL2::SDL2
        SDL2::SDL2main
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        ${GLEW_LIBRARIES}
        GL
)