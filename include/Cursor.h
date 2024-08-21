#pragma once 

#include "Common.h"

namespace glb {

    class GLB_API Cursor
    {
    private:
        Cursor() = delete;
    public:
        struct Position
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
            Position = 0,       // Cursor position callback (glfwSetCursorPosCallback)
            Enter = 1,          // Cursor enter/leave callback (glfwSetCursorEnterCallback)
            MouseButton = 2,    // Mouse button callback (glfwSetMouseButtonCallback)
            Scroll = 3,         // Scroll callback (glfwSetScrollCallback)
        };
    public:
        static bool IsButtonPressed(Button button);
        static Position GetPosition();
        static bool SetCallback(Callback type, void* callback);
    };

}