cmake_minimum_required(VERSION 3.26)
project(Tunks)

set(CMAKE_CXX_STANDARD 17)

option(DIST_RELEASE "Enable distribution release flags" OFF)

include_directories(
        engine/src
        libs/nlohmannjson/include
        libs/easyloggingpp/include
        libs/glm/include
        libs/glad/include
        libs/stbimage/include
)

add_subdirectory(libs/glad)
add_subdirectory(libs/easyloggingpp)
add_subdirectory(engine)
add_subdirectory(game)


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Configuring for Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
    add_definitions(-DDEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Configuring for Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    add_definitions(-DDEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release" AND DIST_RELEASE)
    message("Configuring for Game-Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fomit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")
endif ()
