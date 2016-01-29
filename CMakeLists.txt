set(LIBRARY etudes)
set(CLIENT  etudes-host)

project(etudes)
cmake_minimum_required(VERSION 3.0)

add_executable(${CLIENT}
    src/host/main.cpp
    src/host/EtudesHost.cpp
    src/host/IO/OSCInput.cpp
    )

set_property(TARGET ${CLIENT} PROPERTY CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions("-DDEBUG")
endif()

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_definitions("-DLINUX")
endif()

add_library(${LIBRARY}
    SHARED
    src/lib/Utility/Utility.cpp
    src/lib/Utility/Logging.cpp
    src/lib/Utility/Configuration.cpp
    src/lib/Shader/ShaderRegistry.cpp
    src/lib/Factories/ElementFactory.cpp
    src/lib/Factories/EtudeFactory.cpp
    src/lib/Receivers/Receiver.cpp
    src/lib/Receivers/Etude.cpp
    src/lib/Drawing/DrawPrimitives.cpp
    src/lib/Drawing/ModulationFuncs.cpp
    src/lib/Elements/ElementLine.cpp
    )

set_property(TARGET ${LIBRARY} PROPERTY CXX_STANDARD 14)

find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glbinding REQUIRED)
find_package(glm REQUIRED)
find_package(glfw CONFIG NAMES glfw glfw3)

pkg_search_module(YAML_CPP REQUIRED yaml-cpp)
pkg_search_module(LIBLO REQUIRED liblo)

target_include_directories(${CLIENT}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/host
    PUBLIC ${LIBLO_INCLUDE_DIRS}
    PUBLIC ${GLFW_INCLUDE_DIRS}
    PUBLIC ${GLBINDING_INCLUDES}
    )

target_include_directories(${LIBRARY}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/lib
    PUBLIC ${GLM_INCLUDE_DIRS}
    PUBLIC ${YAML_CPP_INCLUDE_DIRS}
    )

target_link_libraries(${CLIENT}
    PUBLIC ${LIBLO_LIBRARIES}
    PUBLIC ${OPENGL_LIBRARIES}
    PUBLIC ${GLBINDING_LIBRARIES}
    PUBLIC ${GLFW3_LIBRARY}
    PUBLIC ${LIBRARY}
    )

target_link_libraries(${LIBRARY}
    PUBLIC ${YAML_CPP_LIBRARIES}
    PUBLIC ${LIBLO_LIBRARIES}
    PUBLIC ${OPENGL_LIBRARIES}
    PUBLIC ${GLBINDING_LIBRARIES}
    PUBLIC ${GLM_LIBRARIES}
    )
