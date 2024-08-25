cmake_minimum_required(VERSION 3.6)
project(GLB)

# Set CXX standard
set(CMAKE_CXX_STANDARD 17)

# Output directories for different build -p
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/Release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/Debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/Release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/Debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/Release)

# Collect source files
file(GLOB SRC_FILES "src/*.cpp")

# Create a shared library (DLL)
add_library(${CMAKE_PROJECT_NAME} SHARED ${SRC_FILES})

# Define GLB_EXPORTS and GLEW_STATIC when building the library
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE GLB_EXPORTS)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE GLEW_STATIC)


# Platform-specific settings
if (WIN32)
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE 
	    "include/GLB"
	    "external/glfw/include"
	    "external/glew/include"
	    "external/glm"
	    "external/stb"
    )

    set(GLFW_LIB_DIR "${CMAKE_SOURCE_DIR}/external/glfw/build/src/Release")
    set(GLEW_LIB_DIR "${CMAKE_SOURCE_DIR}/external/glew/build/lib/Release")

    target_link_libraries(${CMAKE_PROJECT_NAME} 
	    "opengl32.lib"
	    "${GLFW_LIB_DIR}/glfw3.lib"
	    "${GLEW_LIB_DIR}/glew.lib"
    )
elseif (UNIX)
    find_package(OpenGL REQUIRED)
    find_package(glfw3 REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(glm REQUIRED)
    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE 
        "include/GLB" 
        ${GLFW_INCLUDE_DIRS} 
        ${GLEW_INCLUDE_DIRS} 
        ${GLM_INCLUDE_DIRS}
    )
    target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_LIBRARIES} glfw glew_s glm)
endif()