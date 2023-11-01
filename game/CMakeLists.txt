cmake_minimum_required(VERSION 3.26)
project(TK_Game)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        src
)

add_executable(TK_Game
    src/main.cpp
    src/Game.cpp
    src/Game.hpp
)

target_include_directories(TK_Game PRIVATE
        ${CMAKE_SOURCE_DIR}/engine/src
)
target_link_libraries(TK_Game PRIVATE TK_Engine)