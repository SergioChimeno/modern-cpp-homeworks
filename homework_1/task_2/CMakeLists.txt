cmake_minimum_required(VERSION 3.16.3)
project(test_ipb_arithmetic)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

# Results directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/results/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/results/lib)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)

include_directories(include)
add_subdirectory(src)
