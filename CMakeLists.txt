cmake_minimum_required(VERSION 3.28)
project(Algorithms)

set(CMAKE_CXX_STANDARD 17)

add_executable(Algorithms Examples/main.cpp
        Examples/Bresenham.cpp
        Examples/Bresenham.h
        Examples/Breadcrumbing.cpp
        Examples/Breadcrumbing.h
        Chocobo.cpp
        Chocobo.h
        Game.cpp
        Game.h
        Rat.cpp
        Rat.h
        SpectralEye.cpp
        SpectralEye.h
        Spectre.cpp
        Spectre.h
        Examples/Backtrack.cpp
        Examples/Backtrack.h)
