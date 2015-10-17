set(PROJECT etudes)

project(${PROJECT})
cmake_minimum_required(VERSION 3.0)

set(openFrameworks_DIR $ENV{OPENFRAMEWORKS_ROOT}/cmake)
find_package(openFrameworks REQUIRED)

add_executable(${PROJECT}
    src/main.cpp
    src/ofApp.cpp)


target_include_directories(${PROJECT}
    PUBLIC ${openFrameworks_INCLUDES})

target_link_libraries(${PROJECT}
    PUBLIC ${openFrameworks_LIBRARIES})
