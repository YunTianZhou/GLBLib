# GLBLib

**GLBLib** is a C++ graphics library built on top of OpenGL. It simplifies creating and managing OpenGL contexts and provides utilities for handling shaders, textures, and window management through GLFW and GLEW.

## Features
- **Window Management:** Easy creation and control of OpenGL windows.
- **Shader Handling:** Load, compile, and manage shaders.
- **Texture Management:** Simplified texture loading with stb_image.
- **Event Handling:** Manage input events like key presses and mouse movements.

## Documentation

For more information and detailed descriptions, please refer to the project documentation located at `doc/index.html`. You can view and navigate the documentation by opening this file in your web browser.

## Getting Started
### Building
#### 1. Clone the Repository
```sh
git clone https://github.com/YunTianZhou/GLBLib.git
cd GLBLib
```

#### 2. External Libraries
  The following are the dependencies of GLB:
  
  - [GLFW](https://www.glfw.org/): Handles window creation and input.
  - [GLEW](https://glew.sourceforge.net/): Manages OpenGL extensions.
  - [GLM](https://github.com/g-truc/glm): Provides a math library for graphics.
  - [stb_image](https://github.com/nothings/stb/tree/master): Facilitates image loading.

  To setup these libraries, you can use the provided setup scripts:
  - **Windows**: Run `external/Windows-Setup.bat` to automatically clone and build the required libraries.
```sh
external\Windows-Setup.bat
```
  - **Linux**: Run `external/Linux-Setup.sh` to automatically download and install the required libraries.
```sh
chmod +x external/Linux-Setup.sh
sudo ./external/Linux-Setup.sh
```

  If the scripts don't work, you can download these libraries manually.

#### 3.  Configure the Project with CMake
  Make a build directory:
```sh
mkdir build
cd build
```
  Run CMake to configure the project:
```sh
cmake ..
```
  To build a static library, use:
```sh
 cmake .. -D BUILD_STATIC_LIBS=ON
```

#### 4. Build the Project
  Compile the project:
```sh
make
```
 On Windows, use:
```sh
cmake --build . --config Release
```

## Usage
To use GLBLib in your project, link against the GLBLib library and include the necessary headers.
Here’s a simple example:
```cpp
// Uncomment the following line if using the static library
// #define GLB_STATIC
#include <GLB/GLB.h>

int main()
{
    // Create a window with the specified width, height, and title.
    glb::Window& window = glb::Window::Create(800, 600, "Hello GLB");

    // Check if the window was successfully created.
    if (!window.IsExist())
        return -1; // Exit if the window creation failed.

    // Main loop to keep the window open and responsive.
    while (window.IsOpen())
    {
        // Clear the screen using the renderer.
        glb::Renderer::Clear();

        // Swap the front and back buffers to display the rendered image.
        window.SwapBuffers();

        // Poll for and process input events (e.g., keyboard, mouse).
        window.PollEvents();
    }

    // Clean up resources and destroy the window when done.
    window.Destroy();
}
```

If you are using the static library, ensure you define the `GLB_STATIC` macro before including the GLBLib headers.