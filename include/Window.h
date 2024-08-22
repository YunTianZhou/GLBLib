#pragma once

#include "Icon.h"
#include "Enum.h"

namespace glb {

    class Icon;

    class GLB_API Window
    {
    public:
        struct Size_t { int width = 0, height = 0; };
        struct Position_t { int x = 0, y = 0; };
        enum class Callback
        {
            Close = 0,              // Close window callback (None)
            Size = 1,               // Resize window resize callback (int width, int height)
            FramebufferSize = 2,    // Set Framebuffer size callback (int width, int height)
            Position = 3,           // Move window callback (int xpos, int ypos)
            Iconify = 4,            // Window iconification callback (int iconified)
            Maximize = 5,           // Window maximization callback (int maximized)
            Focus = 6,              // Window Focus callback (int focused)
            Refresh = 7,            // Window damage and refresh callback (None)
        };
    public:
        inline static Window& GetInstance(int width, int height, std::string name) 
        {
            static Window instance(width, height, name);
            return instance;
        }

        static Window& GetInstance() 
        {
            if (!s_initialized) 
            {
                GLBErrL(ObjectNonExist, "Window instance has not been initialized!");
            }
            return s_instance;
        }

        inline static GLFWwindow* GetGLFWwindow() { return s_window; }

        Window(Window const&) = delete;              // Disallow copy
        void operator=(Window const&) = delete;      // Disallow asign
        ~Window();

        void Destory();

        bool SetCallback(Callback type, void* callback);
        bool DisableCallback(Callback type);

        // Get Functions
        inline int IsExist() const { return m_isExist; }
        inline int IsOpen() const { return glfwWindowShouldClose(s_window) == GL_FALSE; }
        inline std::string GetTitle() const { return m_title; }
        inline Size_t GetSize() const;
        inline Size_t GetFramebufferSize() const;
        inline Position_t GetPosition() const;
        inline bool IsIconified() const { return glfwGetWindowAttrib(s_window, GLFW_ICONIFIED); }
        inline bool IsMaximized() const { return glfwGetWindowAttrib(s_window, GLFW_MAXIMIZED); }
        inline bool IsVisible() const { return glfwGetWindowAttrib(s_window, GLFW_VISIBLE); }
        inline bool IsPinned() const { return glfwGetWindowAttrib(s_window, GLFW_FOCUSED); }
        inline float GetOpacity() const { return glfwGetWindowOpacity(s_window); }

        // Set functions
        inline void SetSzie(int width, int height) const { glfwSetWindowSize(s_window, width, height); }
        inline void SetSzie(Size_t size) const { glfwSetWindowSize(s_window, size.width, size.height); }
        inline void SetSizeLimit(int minWidth, int minHeight, int maxWidth, int maxHeight) const { glfwSetWindowSizeLimits(s_window, minWidth, minHeight, maxWidth, maxHeight); }
        inline void SetSizeLimit(Size_t min, Size_t max) const { glfwSetWindowSizeLimits(s_window, min.width, min.height, max.width, max.height); }
        inline void DisableSizeLimit() const { glfwSetWindowSizeLimits(s_window, Enum::DontCare, Enum::DontCare, Enum::DontCare, Enum::DontCare); }

        inline void SetTitle(std::string title);
        inline void SetIcon(const Icon& icon) const;
        inline void SetIconAndFree(Icon& icon) const;
        inline void SetIcon(const Icon icons[], int size) const;
        inline void SetIconAndFree(Icon icons[], int size) const;
        inline void SetDefaultIcon() const { glfwSetWindowIcon(s_window, 0, nullptr); }

        inline void SetAspectRatio(int numer, int denom) const { glfwSetWindowAspectRatio(s_window, numer, denom); }
        inline void DisableAspectRatio() const { glfwSetWindowAspectRatio(s_window, Enum::DontCare, Enum::DontCare); }
        inline void SetPosition(int xpos, int ypos) const { glfwSetWindowPos(s_window, xpos, ypos); }
        inline void SetOpacity(float opacity) const { glfwSetWindowOpacity(s_window, opacity); }
        inline void SetSwapInterval(int interval) const { glfwSwapInterval(1); }

        inline void Iconify() const { glfwIconifyWindow(s_window); }
        inline void Maximize() const { glfwMaximizeWindow(s_window); }
        inline void Restore() const { glfwRestoreWindow(s_window); }
        inline void EnableResize() const { glfwSetWindowAttrib(s_window, GLFW_RESIZABLE, GL_TRUE); }
        inline void DisableResize() const { glfwSetWindowAttrib(s_window, GLFW_RESIZABLE, GL_FALSE); }

        inline void Hide() const { glfwHideWindow(s_window); }
        inline void Show() const { glfwShowWindow(s_window); }
        inline void Focus() const { glfwFocusWindow(s_window); }
        inline void RequestAttention() const { glfwRequestWindowAttention(s_window); }

        // Other functions
        inline void PollEvents() const { glfwPollEvents(); }
        inline void SwapBuffers() const { glfwSwapBuffers(s_window); }

    private:
        Window();
        Window(int width, int height, std::string title);
        static void GLFWErrorCallback(int errorCode,
                                        const char* description);
        static void GLLogMessageCallback(GLenum source,
                                         GLenum type,
                                         GLuint id,
                                         GLenum severity,
                                         GLsizei length,
                                         const GLchar* message,
                                         const void* userParam);

    private:
        static bool s_initialized;
        static Window s_instance;
        static GLFWwindow* s_window;
        std::string m_title;
        bool m_isExist;
    };

    inline Window::Size_t Window::GetSize() const
    {
        Size_t size;
        glfwGetWindowSize(s_window, &size.width, &size.height);
        return size;
    }

    inline Window::Size_t Window::GetFramebufferSize() const
    {
        Size_t size;
        glfwGetFramebufferSize(s_window, &size.width, &size.height);
        return size;
    }

    inline Window::Position_t Window::GetPosition() const
    {
        Position_t position;
        glfwGetWindowPos(s_window, &position.x, &position.y);
        return position;
    }

    inline void Window::SetTitle(std::string title)
    {
        glfwSetWindowTitle(s_window, title.c_str());
        m_title = title;
    }

    inline void Window::SetIcon(const Icon& icon) const
    {
        glfwSetWindowIcon(s_window, 1, &icon.GetImage());
    }

    inline void Window::SetIconAndFree(Icon& icon) const
    {
        glfwSetWindowIcon(s_window, 1, &icon.GetImage());
        icon.Free();
    }

    inline void Window::SetIcon(const Icon icons[], int size) const
    {
        if (!size)
        {
            glfwSetWindowIcon(s_window, 0, nullptr);
            return;
        }
        GLFWimage* images = new GLFWimage[size];
        for (int i = 0; i < size; i++)
        {
            images[i] = icons[i].GetImage();
        }
        glfwSetWindowIcon(s_window, size, images);
        delete[] images;
    }

    inline void Window::SetIconAndFree(Icon icons[], int size) const
    {
        SetIcon(icons, size);
        Icon::Free(icons, size);
    }

}