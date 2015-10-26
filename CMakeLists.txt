set(LIBRARY etudes)
set(CLIENT  etudes-client)

project(etudes)
cmake_minimum_required(VERSION 3.0)

add_executable(${CLIENT}
  src/main.cpp
  )

set_property(TARGET ${CLIENT} PROPERTY CXX_STANDARD 14)

add_library(${LIBRARY}
  src/lib/Renderers/LineRenderer.cpp
  src/lib/ShaderRegistry.cpp
  )

set_property(TARGET ${LIBRARY} PROPERTY CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glbinding REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

target_include_directories(${CLIENT}
  PUBLIC ${GLFW_INCLUDE_DIRS}
  PUBLIC ${GLBINDING_INCLUDES}
  )

target_link_libraries(${CLIENT}
  PUBLIC ${GLFW_LIBRARIES}
  PUBLIC ${OPENGL_LIBRARIES}
  PUBLIC ${GLBINDING_LIBRARIES}
  )
