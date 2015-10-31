set(LIBRARY etudes)
set(CLIENT  etudes-client)

project(etudes)
cmake_minimum_required(VERSION 3.0)

add_executable(${CLIENT}
    src/main.cpp
    src/host/EtudesHost.cpp
    )

set_property(TARGET ${CLIENT} PROPERTY CXX_STANDARD 14)

add_library(${LIBRARY}
    SHARED
    src/lib/Renderers/LineRenderer.cpp
    src/lib/ShaderRegistry.cpp
    src/lib/Source/Source.cpp
    src/lib/Source/OSCSource.cpp
    )

set_property(TARGET ${LIBRARY}
    PROPERTY CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glbinding REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(LIBLO REQUIRED liblo)

target_include_directories(${CLIENT}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/host
    PUBLIC ${LIBLO_INCLUDE_DIRS}
    PUBLIC ${GLFW_INCLUDE_DIRS}
    PUBLIC ${GLBINDING_INCLUDES}
    )

target_link_libraries(${CLIENT}
    PUBLIC ${LIBLO_LIBRARIES}
    PUBLIC ${OPENGL_LIBRARIES}
    PUBLIC ${GLBINDING_LIBRARIES}
    PUBLIC ${GLFW_LIBRARIES}
    PUBLIC ${LIBRARY}
    )
