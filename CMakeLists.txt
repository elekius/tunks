cmake_minimum_required(VERSION 3.26)
project(Tunks)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
        libs/nlohmannjson
        libs/easyloggingpp
        libs/glm
)

add_subdirectory(engine)
add_subdirectory(game)