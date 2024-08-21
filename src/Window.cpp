#include "Window.h"

#include "CallbackManager.h"

namespace glb {

    bool Window::s_initialized = false;
    Window Window::s_instance;
    GLFWwindow* Window::s_window = nullptr;

    Window::Window()
        : m_isExist(false)
    {

    }

    Window::Window(int width, int height, std::string title)
        : m_title(title), m_isExist(false)
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

        s_window = glfwCreateWindow(width, height, m_title.c_str(), nullptr, nullptr);

        if (!s_window) {
            GLError("Window creation failed!");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(s_window);

        // Init glew
        if (glewInit() != GLEW_OK) {
            GLError("GLEW init failed!");
            glfwDestroyWindow(s_window);
            glfwTerminate();
            return;
        }

        // Set GLDebug Callback and enable
        glDebugMessageCallback(GLLogMessageCallback, nullptr);
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glfwSetWindowUserPointer(s_window, &Manager);

        // Set blend func and enable
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_BLEND);

        s_initialized = true;
        m_isExist = true;

        GLLog("GLB init successfully!");
    }

    Window::~Window()
    {
        if (m_isExist)
            Destory();
        glfwTerminate();
    }

    void Window::Destory()
    {
        if (!m_isExist)
        {
            GLWarn("Window already terminated!");
            return;
        }
        glfwSetWindowShouldClose(s_window, GL_TRUE);
        glfwDestroyWindow(s_window);
        m_isExist = false;
    }

    void Window::GLFWErrorCallback(int errorCode,
                                   const char* description)
    {
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