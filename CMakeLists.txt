cmake_minimum_required(VERSION 3.20)
project(graphics)

set(CMAKE_CXX_STANDARD 14)

include_directories(Computer-Graphics)

add_executable(graphics
        Computer-Graphics/allCircles.h
        Computer-Graphics/allLines.h
        Computer-Graphics/Circle.h
        Computer-Graphics/Clipping.h
        Computer-Graphics/CurveFilling.h
        Computer-Graphics/elipses.h
        Computer-Graphics/FillingAlgorithms.h
        Computer-Graphics/Line.h
        Computer-Graphics/LineFillingCircle.h
        Computer-Graphics/main.cpp
        Computer-Graphics/transformation.h)
