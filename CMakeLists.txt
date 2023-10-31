cmake_minimum_required(VERSION 3.26)
project(Tunks)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(GLEW REQUIRED)

set(SOURCE_FILES
        src/main.cpp
        src/utils/Log.hpp
        src/rendering/RenderModel.cpp
        src/rendering/RenderModel.hpp
        src/rendering/Vertex.hpp
        src/Game.cpp
        src/Game.hpp
        src/rendering/VertexBuffer.cpp
        src/rendering/VertexBuffer.hpp
        src/rendering/Shader.cpp
        src/rendering/Shader.hpp
)
set(LIBRARY_FILES
       libs/easyloggingpp/easylogging++.cc
        src/Defines.hpp
)

include_directories(
        src
        libs/nlohmannjson
        libs/easyloggingpp
)

add_executable(Tunks ${SOURCE_FILES} ${LIBRARY_FILES})

target_include_directories(Tunks PRIVATE
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIRS}
)

target_link_libraries(Tunks PRIVATE
        ${SDL2_IMAGE_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        ${GLEW_LIBRARIES}
        GL
)

target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        SDL2::SDL2
        SDL2::SDL2main
)



if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Configuring for Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
    add_definitions(-DDEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Configuring for Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    add_definitions(-DDEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Disk-Release")
    message("Configuring for Game-Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -fomit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -flto")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")
endif ()