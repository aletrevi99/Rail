# Alessandro Trevisan 1221819

project(Rail)
cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-O2")
set(CMAKE_CXX_FLAGS_DEBUG "-O2")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

include_directories(Include/Train
        Include/Station
        Include/Data
        Include/Deposit
        Include/Line
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

add_library(Line Include/Line/Line.h
        Source/Line/Line.cpp
        )

add_executable(Rail main.cpp
        Source/Line/Line.cpp
        Source/Deposit/Deposit.cpp
        Source/Data/Data.cpp
        Source/Station/Station.cpp
        Source/Train/Train.cpp
        )

target_link_libraries(Rail Line Deposit Train Data Station)

# Alessandro Trevisan 1221819