# GLBLib

GLBLib is a C++ graphics library built on top of OpenGL. It simplifies creating and managing OpenGL contexts and provides utilities for handling shaders, textures, and window management through GLFW and GLEW.

## Features
- **Window Management:** Easy creation and control of OpenGL windows.
- **Shader Handling:** Load, compile, and manage shaders.
- **Texture Management:** Simplified texture loading with stb_image.
- **Event Handling:** Manage input events like key presses and mouse movements.

## Getting Started
### Prerequisites
- CMake
- GLFW
- GLEW
- GLM
- stb_image

### Building
#### 1. Clone the repository
 ```sh
 git clone https://github.com/YunTianZhou/GLBLib.git
 cd GLBLib
 ```
#### 2. External Libraries
  Ensure the following libraries are available:
  
  - GLFW: Handles window creation and input.
  - GLEW: Manages OpenGL extensions.
  - GLM: Provides a math library for graphics.
  - stb_image: Facilitates image loading.

  You can either download these libraries manually or use a package manager.

#### 3.  Build the Project
  Run CMake to configure the project:
 ```sh
 mkdir build
 cd build
 cmake ..
 ```
  Compile the project:
 ```sh
 make
 ```
  On Windows, use:
 ```sh
 cmake --build . --config Release
 ```
   
