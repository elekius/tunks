cmake_minimum_required(VERSION 3.26)
project(GLAD)

set(GLAD_SOURCES
        src/glad.c
)
set(GLAD_HEADERS
        include/glad/glad.h
)
include_directories(include)
add_library(GLAD ${GLAD_SOURCES} ${GLAD_HEADERS})