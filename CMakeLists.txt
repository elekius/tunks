cmake_minimum_required(VERSION 3.27)
project(Tunks)

set(CMAKE_CXX_STANDARD 17)


set(SOURCE_FILES
    src/main.cpp
)

include_directories(
        src
        libs/nlohmannjson
)

add_executable(Tunks ${SOURCE_FILES})



if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Configuring for Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
    add_definitions(-DDEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Configuring for Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    add_definitions(-DDEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Game-Release")
    message("Configuring for Game-Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -fomit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -flto")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffast-math")
endif ()