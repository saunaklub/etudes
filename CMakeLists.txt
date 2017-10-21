set(LIBRARY etudes)
set(CLIENT  etudes-host)

set(PROJECT etudes)
project(${PROJECT})
cmake_minimum_required(VERSION 3.1)

set(LIBRARY_SOURCES
	src/lib/EtudesConfig.hpp
    src/lib/Utility/Utility.cpp
    src/lib/Utility/Utility.hpp
    src/lib/Utility/Logging.cpp
	src/lib/Utility/Logging.hpp
    src/lib/Utility/Configuration.cpp
	src/lib/Utility/Configuration.hpp
    src/lib/Utility/ScopedProfiler.cpp
	src/lib/Utility/ScopedProfiler.hpp
    src/lib/Utility/AccumulativeProfiler.cpp
	src/lib/Utility/AccumulativeProfiler.hpp
    src/lib/Utility/ModulationFuncs.cpp
	src/lib/Utility/ModulationFuncs.hpp
    src/lib/Factories/ElementFactory.cpp
	src/lib/Factories/ElementFactory.hpp
    src/lib/Factories/SceneFactory.cpp
	src/lib/Factories/SceneFactory.hpp
    src/lib/IO/OSCInput.cpp
	src/lib/IO/OSCInput.hpp
    src/lib/IO/VideoOutput.cpp
	src/lib/IO/VideoOutput.hpp
    src/lib/Graphics/ShaderRegistry.cpp
	src/lib/Graphics/ShaderRegistry.hpp
    src/lib/Graphics/Context.cpp
	src/lib/Graphics/Context.hpp
    src/lib/Graphics/Painter.cpp
	src/lib/Graphics/Painter.hpp
    src/lib/Graphics/Texture.cpp
	src/lib/Graphics/Texture.hpp
    src/lib/Graphics/Image.cpp
	src/lib/Graphics/Image.hpp
    src/lib/Graphics/SimplexNoise.cpp
	src/lib/Graphics/SimplexNoise.hpp
    #    src/lib/Graphics/TextureTiled.cpp
    src/lib/Graphics/PanZoom.cpp
	src/lib/Graphics/PanZoom.hpp
    src/lib/Graphics/PanZoomParallel.cpp
	src/lib/Graphics/PanZoomParallel.hpp
    src/lib/Graphics/Geometry/Transforms.cpp
	src/lib/Graphics/Geometry/Transforms.hpp
    src/lib/Graphics/Geometry/Rect.cpp
	src/lib/Graphics/Geometry/Rect.hpp
    src/lib/Graphics/Drawable/Quad.cpp
	src/lib/Graphics/Drawable/Quad.hpp
    src/lib/Receivers/Receiver.cpp
	src/lib/Receivers/Receiver.hpp
    src/lib/Receivers/Element.cpp
	src/lib/Receivers/Element.hpp
    src/lib/Receivers/Scene.cpp
	src/lib/Receivers/Scene.hpp
    src/lib/Elements/Lines.cpp
	src/lib/Elements/Lines.hpp
    src/lib/Elements/Particles.cpp
	src/lib/Elements/Particles.hpp
    src/lib/Elements/ImageView.cpp
	src/lib/Elements/ImageView.hpp
    src/lib/Elements/Sinusoids.cpp
	src/lib/Elements/Sinusoids.hpp
    src/lib/Elements/CellularAutomaton.cpp
	src/lib/Elements/CellularAutomaton.hpp
    src/lib/Elements/AlgoSynth.cpp
	src/lib/Elements/AlgoSynth.hpp
    src/lib/Elements/BlobTraces.cpp
	src/lib/Elements/BlobTraces.hpp
    src/lib/Elements/Spiral.cpp
	src/lib/Elements/Spiral.hpp
    src/lib/Elements/DomainWarp.cpp
	src/lib/Elements/DomainWarp.hpp
    src/lib/Elements/Truchet.cpp
	src/lib/Elements/Truchet.hpp
    src/lib/Elements/MultiFractal.cpp
	src/lib/Elements/MultiFractal.hpp
    src/lib/Elements/Clouds.cpp
	src/lib/Elements/Clouds.hpp
    src/lib/Elements/Testbed.cpp
	src/lib/Elements/Testbed.hpp
    )

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    list(APPEND LIBRARY_SOURCES
        src/lib/IO/VideoOutputV4L2.cpp)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    list(APPEND LIBRARY_SOURCES
        src/lib/IO/VideoOutputSyphon.mm)
    set_source_files_properties(src/lib/IO/VideoOutputSyphon.mm PROPERTIES
        COMPILE_FLAGS "-x objective-c++")
endif()

set(CLIENT_SOURCES
    src/host/main.cpp
    src/host/EtudesHost.cpp
	src/host/EtudesHost.hpp
    src/host/Renderer.cpp
	src/host/Renderer.hpp
    )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions("-DDEBUG")
endif()

set(ADDITIONAL_LIBRARIES "")
set(ADDITIONAL_DIRS "")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_definitions("-DLINUX")
    set(GLFW glfw)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_definitions("-DDARWIN")
    find_library(SYPHON_LIBRARY Syphon)
    find_path(SYPHON_INCLUDE_DIR Syphon/Syphon.h)
    find_library(COCOA_LIBRARY Cocoa)
    find_path(COCOA_INCLUDE_DIR Cocoa/Cocoa.h)
    #find_package(glfw CONFIG NAMES glfw glfw3)

    set(GLFW glfw3)
    set(ADDITIONAL_LIBRARIES 
		${SYPHON_LIBRARY}
        ${COCOA_LIBRARY}
        )
    set(ADDITIONAL_DIRS 
		${SYPHON_INCLUDE_DIR}
        ${COCOA_INCLUDE_DIR}
        )
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	add_definitions("-DWINDOWS")
	set(GLFW glfw)
	
	if(CMAKE_BUILD_TOOL MATCHES "(msdev|devenv|nmake)")
    add_definitions(/W2)
	endif()
endif()

option(Test "Build tests" OFF)

find_package(OpenGL REQUIRED)
find_package(glbinding REQUIRED)
find_package(glm REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(liblo REQUIRED)
find_package(glfw3 REQUIRED)

set(FREEIMAGE_LIBRARY_DIR "" CACHE PATH "FreeImage library directory")
set(FREEIMAGE_INCLUDE_DIR "" CACHE PATH "FreeImage include directory")
set(FREEIMAGEPLUS_LIBRARY_DIR "" CACHE PATH "FreeImagePlus library directory")
set(FREEIMAGEPLUS_INCLUDE_DIR "" CACHE PATH "FreeImagePlus include directory")

link_directories(${YAML_CPP_LIBRARY_DIRS})
link_directories(${FREEIMAGEPLUS_LIBRARY_DIR})

add_library(${LIBRARY} SHARED ${LIBRARY_SOURCES})
add_executable(${CLIENT} ${CLIENT_SOURCES})

set_property(TARGET ${LIBRARY} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${CLIENT} PROPERTY CXX_STANDARD 14)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
	target_compile_definitions(${LIBRARY} PRIVATE "-DDLLEXPORT")
	set_target_properties(${CLIENT} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
endif()

target_include_directories(${CLIENT}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/host
    PUBLIC ${LIBLO_INCLUDE_DIRS}
    )

target_include_directories(${LIBRARY}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/lib
    PUBLIC ${GLM_INCLUDE_DIRS}
    PUBLIC ${GLBINDING_INCLUDES}
    PUBLIC ${LIBLO_INCLUDE_DIRS}
    PUBLIC ${YAML_CPP_INCLUDE_DIRS}
	PUBLIC ${FREEIMAGE_INCLUDE_DIR}
	PUBLIC ${FREEIMAGEPLUS_INCLUDE_DIR}
    PUBLIC ${ADDITIONAL_DIRS}
    )

target_link_libraries(${CLIENT}
    PUBLIC ${LIBLO_LIBRARIES}
    PUBLIC ${LIBRARY}
    PUBLIC ${GLFW}
    )

target_link_libraries(${LIBRARY}
    PUBLIC ${LIBLO_LIBRARIES}
    PUBLIC ${OPENGL_LIBRARIES}
    PUBLIC ${YAML_CPP_LIBRARIES}
    PUBLIC ${ADDITIONAL_LIBRARIES}
    glbinding::glbinding
    freeimageplus
    )

configure_file(
    ${PROJECT}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT}Config.cmake)

install(
    TARGETS ${LIBRARY} ${CLIENT}
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/lib/ DESTINATION include/${PROJECT}
    FILES_MATCHING PATTERN "*.hpp")

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT}Config.cmake
    DESTINATION lib/cmake/${PROJECT})

if(Test)
    enable_testing()
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/etudes-test)
endif()
