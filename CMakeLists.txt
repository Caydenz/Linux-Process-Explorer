cmake_minimum_required(VERSION 3.15)
project(Linux_Process_Explorer)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(Linux_Process_Explorer
        main.cpp
        process.cpp
        process.h ProcessExplorer.cpp ProcessExplorer.h)
