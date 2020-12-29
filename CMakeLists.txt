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
        Include/Train/Regional_Train.h
        Source/Train/Regional_Train.cpp
        Include/Train/High_Speed_Train.h
        Source/Train/High_Speed_Train.cpp
        Include/Train/Super_High_Speed_Train.h
        Source/Train/Super_High_Speed_Train.cpp
        )
add_library(Station Include/Station/Station.h
        Source/Station/Station.cpp
        Include/Station/Local_Station.h
        Source/Station/Local_Station.cpp
        Include/Station/Principal_Station.h
        Source/Station/Principal_Station.cpp
        )
add_library(Schedule Include/Schedule/Schedule.h
        Source/Schedule/Schedule.cpp
        )


set(CMAKE_CXX_STANDARD 11)

add_executable(Assegnameto2 main.cpp)