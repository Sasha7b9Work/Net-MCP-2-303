cmake_minimum_required(VERSION 3.10)

project (RES-Network)

set (TARGET_NAME )

set(CMAKE_UNITY_BUILD ON)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_definitions(-DDEBUG)
endif()

add_subdirectory(MS-1)
