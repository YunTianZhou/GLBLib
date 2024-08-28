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

    Window::Window(int width, int height, const std::string& title)
        : m_isExist(false)
    {
        // Set glfw error callback
        glfwSetErrorCallback(GLFWErrorCallback);

        // Init glfw
        if (!glfwInit()) {
            GLBErrH(GLFWErr, "GLFW init failed!");
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

        s_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        if (!s_window) {
            GLBErrH(GLFWErr, "Window creation failed!");
            glfwTerminate();
            return;
        }

        glfwMakeContextCurrent(s_window);

        // Init glew
        if (glewInit() != GLEW_OK) {
            GLBErrH(GLEWErr, "GLEW init failed!");
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

        GLBLog("GLB init successfully!");
    }

    Window::~Window()
    {
        if (m_isExist)
            Destroy();
        glfwTerminate();
    }

    void Window::Destroy()
    {
        if (!m_isExist)
        {
            GLBWarnL(DoubleFree, "Window already destroyed!");
            return;
        }
        GLBLog("Destroy window!");
        glfwSetWindowShouldClose(s_window, GL_TRUE);
        glfwDestroyWindow(s_window);
        m_isExist = false;
    }

    bool Window::SetCallback(Callback type, void* callback)
    {
        // Enum, func, Parameters, CallbackFuncType, Args
        #define Case(e, f, p, t, a) \
            case Callback::e: \
            { \
                Manager.Window.e = callback;\
                if (callback) \
                { \
                    f(s_window, \
                        + [] p{ \
                            void* func = ((CallbackManager*)glfwGetWindowUserPointer(s_window))->Window.e; \
                            (t func) a; \
                        }); \
                } \
                else \
                    f(s_window, nullptr); \
            } \
                break

        switch (type)
        {
            Case(Close, glfwSetWindowCloseCallback, (GLFWwindow * window), (void (*) ()), ());
            Case(Size, glfwSetWindowSizeCallback, (GLFWwindow * window, int width, int height), (void (*) (int, int)), (width, height));
            Case(FramebufferSize, glfwSetFramebufferSizeCallback, (GLFWwindow * window, int width, int height), (void (*) (int, int)), (width, height));
            Case(Position, glfwSetWindowPosCallback, (GLFWwindow * window, int xpos, int ypos), (void (*) (int, int)), (xpos, ypos));
            Case(Iconify, glfwSetWindowIconifyCallback, (GLFWwindow * window, int iconified), (void (*) (int)), (iconified));
            Case(Maximize, glfwSetWindowMaximizeCallback, (GLFWwindow * window, int maximized), (void (*) (int)), (maximized));
            Case(Focus, glfwSetWindowFocusCallback, (GLFWwindow * window, int focused), (void (*) (int)), (focused));
            Case(Refresh, glfwSetWindowRefreshCallback, (GLFWwindow * window), (void (*) ()), ());
        default:
            GLBWarnH(InvalidCallbackType, "Invalid window callback type '" << (int)type << "'");
            return false;
        }
        return true;

        #undef Case
    }

    bool Window::DisableCallback(Callback type)
    {
        return SetCallback(type, nullptr);
    }

    void Window::GLFWErrorCallback(int errorCode,
        const char* description)
    {
        GLBErrH(GLFWErr, "[GLFW " << errorCode << "] " << description);
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
            GLBErrH(OpenGLErr, "[OpenGL Debug HIGH] " << message);
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            GLBErrL(OpenGLErr, "[OpenGL Debug MEDIUM] " << message);
            break;
        case GL_DEBUG_SEVERITY_LOW:
            GLBWarnH(OpenGLErr, "[OpenGL Debug LOW] " << message);
            break;
        }
    }

}





















