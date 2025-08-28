# (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by

cmake_minimum_required(VERSION 3.5)

# Set project name
project (RES-Network-GUI)

set (TARGET_NAME RES-Network-GUI)

set(CMAKE_UNITY_BUILD ON)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
    add_definitions(-DDEBUG)
endif()


macro(wx_string_append var str)
    set(${var} ${${var}}${str})
endmacro()

if(BUILD_USE_STATIC_RUNTIME)
    set(MSVC_LIB_USE "/MTd")
    set(MSVC_LIB_REPLACE "/MDd")
 
    # Set MSVC runtime flags for all configurations
    foreach(cfg "" ${CMAKE_CONFIGURATION_TYPES})
        set(c_flag_var CMAKE_C_FLAGS)
        set(cxx_flag_var CMAKE_CXX_FLAGS)
        if(cfg)
            string(TOUPPER ${cfg} cfg_upper)
            wx_string_append(c_flag_var "_${cfg_upper}")
            wx_string_append(cxx_flag_var "_${cfg_upper}")
        endif()
        if(${c_flag_var} MATCHES ${MSVC_LIB_REPLACE})
            string(REPLACE ${MSVC_LIB_REPLACE} ${MSVC_LIB_USE} ${c_flag_var} "${${c_flag_var}}")
            set(${c_flag_var} ${${c_flag_var}} CACHE STRING
            "Flags used by the C compiler during ${cfg_upper} builds." FORCE)
        endif()
        if(${cxx_flag_var} MATCHES ${MSVC_LIB_REPLACE})
            string(REPLACE ${MSVC_LIB_REPLACE} ${MSVC_LIB_USE} ${cxx_flag_var} "${${cxx_flag_var}}")
            set(${cxx_flag_var} ${${cxx_flag_var}} CACHE STRING
            "Flags used by the CXX compiler during ${cfg_upper} builds." FORCE)
        endif()
    endforeach()
endif()

add_subdirectory(MS-1)
