cmake_minimum_required(VERSION 3.6)
project(GLB)

# Set CXX standard
set(CMAKE_CXX_STANDARD 17)

# Output directories for different build -p
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/Release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/Debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/Release)

# Collect source files
file(GLOB SRC_FILES
    "${PROJECT_SOURCE_DIR}/vendor/stb_image/stb_image.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

# Create a shared library (DLL)
add_library(${CMAKE_PROJECT_NAME} SHARED ${SRC_FILES} "include/CallbackManager.h")

# Define GLB_EXPORTS when building the library
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE GLB_EXPORTS)

# GLFW and GLEW settings
set(GLFW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/GLFW/include")
set(GLEW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/external/GLEW/include")

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(VENDOR_DIR "${CMAKE_SOURCE_DIR}/vendor")

include_directories(${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${INCLUDE_DIR} ${VENDOR_DIR})

# Platform-specific settings
if (WIN32)
    # Windows-specific settings
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        # x64 architecture
        set(SUF "x64")
    else()
        # Win32 architecture
        set(SUF "win32")
    endif()

    set(GLFW_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/external/GLFW/lib/Release/${SUF}")
    set(GLEW_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/external/GLEW/lib/Release/${SUF}")
    set(GLFW_BIN_DIR "${CMAKE_SOURCE_DIR}/external/GLFW/bin/Release/${SUF}")
    set(GLEW_BIN_DIR "${CMAKE_SOURCE_DIR}/external/GLEW/bin/Release/${SUF}")
    
    set(GLFW_LIBRARY "${GLFW_LIBRARY_DIR}/glfw3dll.lib")
    set(GLEW_LIBRARY "${GLEW_LIBRARY_DIR}/glew32.lib")

    target_link_libraries(${CMAKE_PROJECT_NAME} ${GLFW_LIBRARY} ${GLEW_LIBRARY} OpenGL32.lib)

    # Copy the GLFW and GLEW DLLs to the output directory
    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${GLFW_BIN_DIR}/glfw3.dll"
        $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
        COMMAND ${CMAKE_COMMAND} -E copy
        "${GLEW_BIN_DIR}/glew32.dll"
        $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
    )
elseif (UNIX)
    # Find OpenGL, GLFW, and GLEW libraries on UNIX
    find_package(OpenGL REQUIRED)
    find_package(PkgConfig REQUIRED)
    
    pkg_search_module(GLFW REQUIRED glfw3)
    pkg_search_module(GLEW REQUIRED glew)

    # Include directories for GLFW and GLEW
    include_directories(${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

    # Link directories for GLFW and GLEW (if needed)
    link_directories(${GLFW_LIBRARY_DIRS} ${GLEW_LIBRARY_DIRS})

    # Link against the UNIX-specific libraries
    target_link_libraries(${CMAKE_PROJECT_NAME} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES})
endif()