add_library(ipb_arithmetic sum.cpp subtract.cpp)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ipb_arithmetic)

install(TARGETS ipb_arithmetic)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION ${PROJECT_SOURCE_DIR}/install/include)
