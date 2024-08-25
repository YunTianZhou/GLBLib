#include "Cursor.h"

#include "Window.h"
#include "CallbackManager.h"

namespace glb {

    bool Cursor::IsButtonPressed(Button button)
    {
        int id = (int)button;
        if (id < 0 || id >(int) Button::Last)
        {
            GLBWarnH(InvalidEnum, "Invalid mouse button '" << id << "'");
            return false;
        }
        return glfwGetMouseButton(Window::GetGLFWwindow(), id);
    }

    Cursor::Position_t Cursor::GetPosition()
    {
        double xpos, ypos;
        glfwGetCursorPos(Window::GetGLFWwindow(), &xpos, &ypos);
        return { xpos, ypos };
    }

    bool Cursor::SetCallback(Callback type, void* callback)
    {
        // Enum, func, Parameters, CallbackFuncType, Args
        #define Case(e, f, p, t, a) \
            case Callback::e: \
            { \
                Manager.Cursor.e = callback;\
                if (callback) \
                { \
                    f(Window::GetGLFWwindow(), \
                        +[] p { \
                            void* func = ((CallbackManager*) glfwGetWindowUserPointer(Window::GetGLFWwindow()))->Cursor.e; \
                            (t func) a; \
                        }); \
		            } \
                else \
                    f(Window::GetGLFWwindow(), nullptr); \
            } \
                break

        switch (type)
        {
            Case(Position, glfwSetCursorPosCallback, (GLFWwindow * window, double xpos, double ypos), (void (*) (double, double)), (xpos, ypos));
            Case(Enter, glfwSetCursorEnterCallback, (GLFWwindow * window, int enter), (void (*) (int)), (enter));
            Case(MouseButton, glfwSetMouseButtonCallback, (GLFWwindow * window, int button, int action, int mods), (void (*) (int, int, int)), (button, action, mods));
            Case(Scroll, glfwSetScrollCallback, (GLFWwindow * window, double xoffset, double yoffset), (void (*) (double, double)), (xoffset, yoffset));
        default:
            GLBWarnH(InvalidCallbackType, "Invalid cursor callback type '" << (int)type << "'");
            return false;
        }
        return true;

        #undef Case
    }
    bool Cursor::DisableCallback(Callback type)
    {
        return SetCallback(type, nullptr);
    }
}
