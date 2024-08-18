#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

#ifdef _WIN32
    #ifdef GLB_EXPORTS
        #define GLB_API __declspec(dllexport)
    #else
        #define GLB_API __declspec(dllimport)
    #endif
#else
    #define GLB_API
#endif

#ifdef NDEBUG
    #define GLDebugbreak()
#else
    #if defined(_MSC_VER) // For Microsoft Visual Studio
        #define GLDebugbreak() __debugbreak()
    #elif defined(__GNUC__) // For GCC or Clang
        #define GLDebugbreak() __builtin_trap()
    #else
        #define GLDebugbreak() (*(volatile int*)0 = 0) // Default to a simple crash
    #endif
#endif

#define GLSay(x) std::cout << x << std::endl
#define GLLog(x) std::cout << "GLB Log: [" << __FUNCTION__ << "] " << x << std::endl
#define GLWarn(x) std::cerr << "GLB Warn: [" << __FUNCTION__ << "] " << x << std::endl
#define GLError(x) std::cerr << "GLB Error: [" << __FUNCTION__ << "] " << x << std::endl

#define GLASSERT(c, x) if (!(c)) { GLError(x); GLDebugbreak(); }

namespace glb {

    inline unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:            return 4;
        case GL_UNSIGNED_INT:     return 4;
        case GL_UNSIGNED_SHORT:   return 2;
        case GL_UNSIGNED_BYTE:    return 1;
        }
        GLError("Unsupported type!");
        return 0;
    }

}
