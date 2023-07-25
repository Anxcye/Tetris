cmake_minimum_required(VERSION 3.25)
project(tetris)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(tetris
        src/common.h src/common.cpp
        main.cpp
        src/dmap.h src/dmap.cpp
        src/id_generator.cpp  src/id_generator.h
        src/cursor.cpp src/cursor.h
        src/ui.cpp src/ui.h
        src/ranklist.cpp src/ranklist.h )
