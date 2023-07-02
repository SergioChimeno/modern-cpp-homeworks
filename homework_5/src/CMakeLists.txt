add_library(mat_serialization serialize.cpp)
add_library(convert_dataset convert_dataset.cpp)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(mat_serialization ${OpenCV_LIBS})
target_link_libraries(convert_dataset ${OpenCV_LIBS} mat_serialization)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} mat_serialization convert_dataset)
