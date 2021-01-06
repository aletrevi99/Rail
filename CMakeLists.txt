# Alessandro Trevisan 1221819

project(Assegnamento2)
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

include_directories(Include/Train
        Include/Station
        Include/Data
        Include/Deposit
        Include/Rail
        )

add_library(Train Include/Train/Train.h
        Source/Train/Train.cpp
        )

add_library(Station Include/Station/Station.h
        Source/Station/Station.cpp
        )

add_library(Data Include/Data/Data.h
        Source/Data/Data.cpp
        )

add_library(Deposit Include/Deposit/Deposit.h
        Source/Deposit/Deposit.cpp
        )

add_library(Rail Include/Rail/Rail.h
        Source/Rail/Rail.cpp
        )

set(CMAKE_CXX_STANDARD 11)

add_executable(Assegnamento2 main.cpp)

# Alessandro Trevisan 1221819