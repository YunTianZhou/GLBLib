#pragma once 

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Export.h"

namespace glb {

    class GLB_API Cursor
    {
    private:
        Cursor() = delete;
    public:
        struct Position_t
        {
            double x = 0.0;
            double y = 0.0;
        };
        enum class Button
        {
            Left = GLFW_MOUSE_BUTTON_LEFT,
            Right = GLFW_MOUSE_BUTTON_RIGHT,
            Middle = GLFW_MOUSE_BUTTON_MIDDLE,
            Last = GLFW_MOUSE_BUTTON_LAST,

            Button4 = GLFW_MOUSE_BUTTON_4,
            Button5 = GLFW_MOUSE_BUTTON_5,
            Button6 = GLFW_MOUSE_BUTTON_6,
            Button7 = GLFW_MOUSE_BUTTON_7,
        };

        enum class Callback
        {
            Position,          // Cursor position callback (double xpos, double ypos)
            Enter,             // Cursor enter/leave callback (int enter)
            MouseButton,       // Mouse button callback (int button, int action, int mods)
            Scroll,            // Scroll callback (double xoffset, double yoffset)
        };
    public:
        static bool IsButtonPressed(Button button);
        static Position_t GetPosition();
        static bool SetCallback(Callback type, void* callback);
        static bool DisableCallback(Callback type);
    };

}