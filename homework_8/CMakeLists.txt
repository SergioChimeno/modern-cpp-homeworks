cmake_minimum_required(VERSION 3.16.3)
project(homework8)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

include_directories(include)

add_subdirectory(task_1)
add_subdirectory(task_2)