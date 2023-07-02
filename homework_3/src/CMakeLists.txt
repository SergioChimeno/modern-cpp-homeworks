add_library(html_writer html_writer.cpp)
add_library(image_browser image_browser.cpp html_writer.cpp)
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} html_writer image_browser)