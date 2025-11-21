# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

cmake_minimum_required(VERSION 3.15)

# Set project name
project (RES-Network-GUI)

set (TARGET_NAME RES-Network-GUI)

set(CMAKE_UNITY_BUILD ON)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_definitions(-DDEBUG)
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")         # Установка флага линковки /MT

add_subdirectory(MS-1)
