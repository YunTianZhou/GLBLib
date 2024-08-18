#include "Window.h"

namespace glb {

    Window::Window(int width, int height, std::string title)
        : m_width(width), m_height(height), m_title(title),
          m_aspectRatio(0), m_window(nullptr), m_isExist(false)
    {
        // Set glfw error callback
        glfwSetErrorCallback(GLFWErrorCallback);

        // Init glfw
        if (!glfwInit()) {
            GLError("GLFW init failed!");
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

        if (!m_window) {
            GLError("Window creation failed!");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(m_window);

        m_aspectRatio = (float) m_width / (float)m_height;

        // Init glew
        if (glewInit() != GLEW_OK) {
            GLError("GLEW init failed!");
            glfwDestroyWindow(m_window);
            glfwTerminate();
            return;
        }

        // Set GLDebug Callback and enable
        glDebugMessageCallback(GLLogMessageCallback, nullptr);
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

        // Set blend func and enable
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        m_isExist = true;

        GLLog("GLB init successfully!");
    }

    Window::~Window()
    {
        ShutDown();
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Window::ShutDown()
    {
        m_isExist = false;
        glfwSetWindowShouldClose(m_window, GL_TRUE);
    }

    void Window::GLFWErrorCallback(int errorCode,
                                   const char* description)
    {
        GLDebugbreak();
        GLError("[GLFW " << errorCode << "] " << description);
    }

    void Window::GLLogMessageCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar* message,
        const void* userParam)
    {
        GLDebugbreak();

        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            GLError("[OpenGL Debug HIGH] " << message);
            throw std::runtime_error(message);
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            GLError("[OpenGL Debug MEDIUM] " << message);
            break;
        case GL_DEBUG_SEVERITY_LOW:
            GLError("[OpenGL Debug LOW] " << message);
            break;
        }
    }


}