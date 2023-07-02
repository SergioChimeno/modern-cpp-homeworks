add_subdirectory(io_strategies)

add_library(image image.cpp)
target_link_libraries(image strategies)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} image strategies)