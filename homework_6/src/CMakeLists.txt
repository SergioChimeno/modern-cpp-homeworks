add_library(image image.cpp)
target_link_libraries(image io_tools)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} image)