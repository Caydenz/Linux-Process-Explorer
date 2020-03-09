cmake_minimum_required(VERSION 3.15)
project(Linux_Process_Explorer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(.)

add_executable(Linux_Process_Explorer
        main.cpp
        process.cpp
        process.h ProcessExplorer.cpp ProcessExplorer.h utils.cpp utils.h)
