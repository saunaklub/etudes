set(LIBRARY etudes)
set(CLIENT  etudes-client)

project(etudes)
cmake_minimum_required(VERSION 3.0)

set(openFrameworks_DIR $ENV{OPENFRAMEWORKS_ROOT}/cmake)
find_package(openFrameworks REQUIRED)

add_executable(${CLIENT}
    src/main.cpp
    src/ofApp.cpp
    )

target_include_directories(${CLIENT}
    PUBLIC ${openFrameworks_INCLUDES})

target_link_libraries(${CLIENT}
    PUBLIC ${openFrameworks_LIBRARIES}
    PUBLIC etudes)

add_library(${LIBRARY}
    src/lib/Renderers/LineRenderer.cpp
    )
