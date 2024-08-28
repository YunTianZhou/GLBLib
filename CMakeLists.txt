cmake_minimum_required(VERSION 3.6)
project(GLB)

# Set CXX standard
set(CMAKE_CXX_STANDARD 17)

# Output directories for different build -p
if (WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/bin/Release")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/lib/Release")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/lib/Release")

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/bin/Debug")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/lib/Debug")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/lib/Debug")

else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/")

endif()

# Collect source files
file(GLOB SRC_FILES "src/*.cpp")

# Option to select between static and shared library
option(BUILD_STATIC_LIBS "Build static libraries instead of shared" OFF)

if (BUILD_STATIC_LIBS)
    add_library(${CMAKE_PROJECT_NAME} STATIC ${SRC_FILES})
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME "GLB_s")
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE GLB_STATIC)
else()
    add_library(${CMAKE_PROJECT_NAME} SHARED ${SRC_FILES})
endif()

# Define GLB_EXPORTS and GLEW_STATIC when building the library
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE GLB_EXPORTS)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE GLEW_STATIC)

include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/GLBConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/GLBConfig.cmake"
    INSTALL_DESTINATION lib/cmake/GLB
)

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
    find_package(GLEW REQUIRED)

    target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE "include/GLB")

    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
    )

endif()