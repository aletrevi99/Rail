# Alessandro Trevisan 1221819

project(Assegnamento2)
cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

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

add_executable(Assegnamento2 main.cpp
        Source/Rail/Rail.cpp
        Source/Deposit/Deposit.cpp
        Source/Data/Data.cpp
        Source/Station/Station.cpp
        Source/Train/Train.cpp
        )

target_link_libraries (Assegnamento2 Rail Deposit Train Data Station)

# Alessandro Trevisan 1221819