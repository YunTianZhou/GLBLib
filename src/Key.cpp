#include "Key.h"

#include "Window.h"
#include "CallbackManager.h"

namespace glb {

	bool Key::IsPressed(Type key)
	{
		int state = glfwGetKey(Window::GetGLFWwindow(), (int) key);
		return state == GLFW_PRESS;
	}

	void Key::SetInputMode(Mode mode, bool value)
	{
		glfwSetInputMode(Window::GetGLFWwindow(), static_cast<int>(mode), value ? GLFW_TRUE : GLFW_FALSE);
	}

	int Key::GetScanCode(Type key)
	{
		return glfwGetKeyScancode((int) key);
	}

	std::string Key::ToString(Type key)
	{
		const char* name = glfwGetKeyName((int) key, 0);
		return name ? std::string(name) : "Unknown Key";
	}

	std::string Key::ToString(int scancode)
	{
		const char* name = glfwGetKeyName((int) Type::Unknow, scancode);
		return name ? std::string(name) : "Unknown Key";
	}

	bool Key::SetCallback(Callback type, void* callback)
	{
		// Enum, func, Parameters, CallbackFuncType, Args
		#define Case(e, f, p, t, a) \
            case Callback:: ## e: \
            { \
                Manager.Key. ## e = callback;\
                if (callback) \
                { \
					f(Window::GetGLFWwindow(), \
						+[] p { \
							void* func = ((CallbackManager*) glfwGetWindowUserPointer(Window::GetGLFWwindow()))->Key. ## e; \
							(t func) a; \
						}); \
					} \
                else \
                    f(Window::GetGLFWwindow(), nullptr); \
            } \
                break

		switch (type)
		{
			Case(Key, glfwSetKeyCallback, (GLFWwindow* window, int key, int scancode, int action, int mods), (void (*) (int, int, int, int)), (key, scancode, action, mods));
			Case(Char, glfwSetCharCallback, (GLFWwindow* window, unsigned int codepoint), (void (*) (unsigned int)), (codepoint));
		default:
			GLBWarnH(InvalidCallbackType, "Invalid key callback type '" << (int) type << "'");
			return false;
		}
		return true;

		#undef Case
	}

	bool Key::DisableCallback(Callback type)
	{
		return SetCallback(type, nullptr);
	}

}