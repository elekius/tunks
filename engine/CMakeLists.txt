cmake_minimum_required(VERSION 3.26)
project(TK_Engine)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)


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
        src/TK/engine/graphics/Model.cpp
        src/TK/engine/graphics/Model.hpp
        src/TK/engine/graphics/ModelObject.cpp
        src/TK/engine/graphics/ModelObject.hpp
)
set(LIBRARY_FILES
        ${CMAKE_SOURCE_DIR}/libs/easyloggingpp/easylogging++.cc

)
add_library(TK_Engine
      ${SOURCE_FILES} ${LIBRARY_FILES}
)

target_include_directories(TK_Engine PUBLIC
        ${GLFW_INCLUDE_NONE}
)

target_link_libraries(TK_Engine PUBLIC
        GLAD
        GL
        glfw
)