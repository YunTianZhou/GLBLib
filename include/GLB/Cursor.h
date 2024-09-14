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

        enum class Action
        {
            Release = GLFW_RELEASE,
            Press = GLFW_PRESS,
            Repeat = GLFW_REPEAT,
        };

        enum class Mode
        {
            Shift = GLFW_MOD_SHIFT,
            Control = GLFW_MOD_CONTROL,
            Alt = GLFW_MOD_ALT,
            Super = GLFW_MOD_SUPER,
            CapsLock = GLFW_MOD_CAPS_LOCK,
            NumLock = GLFW_MOD_NUM_LOCK,
        };

        enum class Callback
        {
            Position,          // Cursor position callback (Position_t position)
            Enter,             // Cursor enter/leave callback (int enter)
            MouseButton,       // Mouse button callback (Button button, Action action, int mods)
            Scroll,            // Scroll callback (double xoffset, double yoffset)
        };
    public:
        static bool IsButtonPressed(Button button);
        static Position_t GetPosition();
        static bool SetCallback(Callback type, void* callback);
        static bool DisableCallback(Callback type);
        static inline bool ContainMode(Mode mods, Mode mode);
    };

    inline bool Cursor::ContainMode(Mode mods, Mode mode)
    {
        return (int) mods & (int) mode;
    }

}