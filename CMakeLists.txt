cmake_minimum_required(VERSION 3.22)
project(hawk)

set(CMAKE_CXX_STANDARD 17)

FIND_PACKAGE(BISON REQUIRED)
FIND_PACKAGE(FLEX REQUIRED)

set(CMAKE_CXX_FLAGS "-lfl")


add_executable(hawk src/lex.yy.c src/parser.tab.c src/main.cpp src/lang.cpp
        src/engine.cpp)

