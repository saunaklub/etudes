set(LIBRARY etudes)
set(CLIENT  etudes-host)

project(etudes)
cmake_minimum_required(VERSION 3.0)

add_executable(${CLIENT}
    src/main.cpp
    src/host/EtudesHost.cpp
    src/host/OSCInput.cpp
    )

set_property(TARGET ${CLIENT} PROPERTY CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

add_library(${LIBRARY}
    SHARED
    src/lib/Util/Logging.cpp
    src/lib/Shader/ShaderRegistry.cpp
    src/lib/Receiver/Receiver.cpp
    src/lib/Receiver/ReceiverRegistry.cpp
    src/lib/Drawing/DrawPrimitives.cpp
    src/lib/Drawing/ModulationFuncs.cpp
    src/lib/Etudes/EtudeTemplate.cpp
    src/lib/Etudes/EtudeTriangles.cpp
    src/lib/Etudes/EtudeLines.cpp
    )

set_property(TARGET ${LIBRARY} PROPERTY CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(glbinding REQUIRED)
find_package(glm REQUIRED)
find_package(glfw REQUIRED NAMES glfw glfw3)
find_package(liblo REQUIRED)

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
    )

target_link_libraries(${CLIENT}
    PUBLIC ${OPENGL_LIBRARIES}
    PUBLIC ${GLBINDING_LIBRARIES}
    PUBLIC ${GLFW3_LIBRARY}
    PUBLIC ${LIBRARY}
    )

target_link_libraries(${LIBRARY}
    PUBLIC ${LIBLO_LIBRARY}
    PUBLIC ${OPENGL_LIBRARIES}
    PUBLIC ${GLBINDING_LIBRARIES}
    PUBLIC ${GLM_LIBRARIES}
    )
