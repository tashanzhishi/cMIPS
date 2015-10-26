cmake_minimum_required(VERSION 3.3)
project(cMIPS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        src/register.c
        src/register.h src/compiler.c src/compiler.h src/test.c src/test.h)

add_executable(cMIPS ${SOURCE_FILES})