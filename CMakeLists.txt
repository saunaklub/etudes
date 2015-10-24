set(LIBRARY etudes)
set(CLIENT  etudes-client)

project(etudes)
cmake_minimum_required(VERSION 3.0)

# can I set a list of packages in find_package?
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

target_include_directories(${CLIENT}
  ${GLFW_INCLUDE_DIRS})

target_link_libraries(${CLIENT}
  PUBLIC ${GLFW_LIBRARIES}
  PUBLIC ${OPENGL_LIBRARIES}
  public etudes)

add_executable(${CLIENT}
  src/main.cpp
  )

add_library(${LIBRARY}
  src/lib/Renderers/LineRenderer.cpp
  src/lib/ShaderRegistry.cpp
  )
