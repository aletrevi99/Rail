project(Assegnamento2)
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include_directories(Include/Train
        Include/Station
        Include/Schedule
        Include/Deposit
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

add_library(Deposit Include/Deposit/Deposit.h
        Source/Deposit/Deposit.cpp
        )

set(CMAKE_CXX_STANDARD 11)

add_executable(Assegnamento2 main.cpp)