:: Setting up glfw
git clone https://github.com/glfw/glfw.git
cd glfw
mkdir build
cd build
cmake .. 
cmake --build . --config Release
cd ../..

:: Setting up glew
git clone https://github.com/Perlmint/glew-cmake.git glew
cd glew/build
cmake ..
cmake --build . --config Release
cd ../..

:: Setting up glm
git clone https://github.com/g-truc/glm.git

:: Setting up stb
mkdir stb
cd stb
git clone https://github.com/nothings/stb.git
cd ..