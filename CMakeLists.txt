cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Assegnamento2)

include_directories(Include/Train
        Include/Station
        Include/Schedule
        )
include_directories(Source/Train
        Source/Station
        Source/Schedule
        )

add_library(Train Include/Train/Train.h
        Source/Train/Train.cpp
        )
add_library(Station Include/Station/Station.h
        Source/Station/Station.cpp
        )
add_library(Schedule Include/Schedule/Schedule.h
        Source/Schedule/Schedule.cpp
        )


set(CMAKE_CXX_STANDARD 11)

add_executable(Assegnamento2 main.cpp)