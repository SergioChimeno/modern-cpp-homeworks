add_library(serialization serialize.cpp convert_dataset.cpp)
add_library(kmeans kMeans.cpp)
add_library(bow_dictionary BowDictionary.cpp)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(kmeans ${OpenCV_LIBS})
target_link_libraries(serialization ${OpenCV_LIBS})
target_link_libraries(bow_dictionary ${OpenCV_LIBS} kmeans)


target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} kmeans serialization bow_dictionary)