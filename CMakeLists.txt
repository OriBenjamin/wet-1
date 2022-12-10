cmake_minimum_required(VERSION 3.22)

project(wet-1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        main.cpp
        Tree.h
        Node.h
        Team.cpp
        Team.h
        wet1util.h
        worldcup23a1.cpp
        worldcup23a1.h
        Player.cpp
        Player.h
        main.cpp main23a1.cpp)