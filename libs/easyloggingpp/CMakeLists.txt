cmake_minimum_required(VERSION 3.26)
project(easylogging)

set(EASYLOGGING_SOURCES
        src/easylogging++.cc
)
set(EASYLOGGING_HEADERS
        include/easylogging++.h
)
include_directories(include)
add_library(easylogging ${EASYLOGGING_SOURCES} ${EASYLOGGING_HEADERS})