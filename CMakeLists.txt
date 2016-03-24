set(LIBRARY etudes)
set(CLIENT  etudes-host)

project(etudes)
cmake_minimum_required(VERSION 3.0)

set(LIBRARY_SOURCES
    src/lib/Utility/Utility.cpp
    src/lib/Utility/Logging.cpp
    src/lib/Utility/Configuration.cpp
    src/lib/Utility/ShaderRegistry.cpp
    src/lib/Utility/ImageLoader.cpp
    src/lib/Factories/ElementFactory.cpp
    src/lib/Factories/EtudeFactory.cpp
    src/lib/Receivers/Receiver.cpp
    src/lib/Receivers/Etude.cpp
    src/lib/Rendering/ModulationFuncs.cpp
    src/lib/Rendering/Painter.cpp
    src/lib/Rendering/Texture.cpp
    src/lib/Rendering/TextureTiled.cpp
    src/lib/Elements/Lines.cpp
    src/lib/Elements/Particles.cpp
    src/lib/Elements/ImageView.cpp
    )

set(CLIENT_SOURCES
    src/host/main.cpp
    src/host/EtudesHost.cpp
    src/host/IO/OSCInput.cpp
    src/host/IO/VideoOutput.cpp
    )

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    list(APPEND CLIENT_SOURCES
        src/host/IO/VideoOutputV4L2.cpp)
endif()

add_library(${LIBRARY} SHARED ${LIBRARY_SOURCES})
add_executable(${CLIENT} ${CLIENT_SOURCES})

set_property(TARGET ${LIBRARY} PROPERTY CXX_STANDARD 14)
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
    )

target_include_directories(${LIBRARY}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/lib
    PUBLIC ${GLM_INCLUDE_DIRS}
    PUBLIC ${GLBINDING_INCLUDES}
    PUBLIC ${YAML_CPP_INCLUDE_DIRS}
    )

target_link_libraries(${CLIENT}
    PUBLIC ${LIBLO_LIBRARIES}
    PUBLIC ${GLFW3_LIBRARY}
    PUBLIC ${LIBRARY}
    )

target_link_libraries(${LIBRARY}
    PUBLIC ${OPENGL_LIBRARIES}
    PUBLIC ${GLBINDING_LIBRARIES}
    PUBLIC ${YAML_CPP_LIBRARIES}
    freeimageplus
    )
