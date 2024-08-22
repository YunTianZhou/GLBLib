#pragma once
#include <iostream>
#include <string>
#include <sstream>

#include "Export.h"

#define GLBSay(x) std::cout << x << std::endl
#define GLBLog(x) std::cout << "GLB Log: [" << __FUNCTION__ << "] " << x << std::endl

#define GLBDebug(p, l, t, m) Debug::Log(p, __FILE__, __FUNCTION__, __LINE__, l, glb::Debug::Type:: ## t, (std::stringstream() << m).str())
#define GLBWarnL(t, m) GLBDebug("Warn Low", glb::Debug::Level::WarnLow, t, m)
#define GLBWarnH(t, m) GLBDebug("Warn High", glb::Debug::Level::WarnHigh, t, m)
#define GLBErrL(t, m) GLBDebug("Error Low", glb::Debug::Level::ErrorLow, t, m)
#define GLBErrH(t, m) GLBDebug("Error High", glb::Debug::Level::ErrorHigh, t, m)

#define GLBAssertWL(c, t, m) if (!(c)) { GLBWarnL(t, m); }
#define GLBAssertWH(c, t, m) if (!(c)) { GLBWarnH(t, m); }
#define GLBAssertEL(c, t, m) if (!(c)) { GLBErrL(t, m); }
#define GLBAssertEH(c, t, m) if (!(c)) { GLBErrH(t, m); }

namespace glb {

	class GLB_API Debug
	{
	private:
		Debug() = delete;
	public:
		enum class Level
		{
			WarnLow, 
			WarnHigh, 
			ErrorLow, 
			ErrorHigh, 
		};

		enum class Type
		{
			// Invalid / Unknow stuff
			InvalidCallbackType,
			InvalidEnum,
			UnknowType,
			UnknowUniform,
			UnknowUserPointer,

			// Memory
			ObjectNonExist,
			DoubleFree,
			CopyLargeMemory,

			// Falid
			OpenFileFaild,
			ShaderCompiledFaild,
			LoadImageFaild,

			// GLFW / GL Error
			GLFWErr,
			GLEWErr,
			OpenGLErr,
		};

		using CallbackFunc = void (*) (const std::string& file,
									   const std::string& function,
									   int line,
									   Level level, 
									   Type type, 
									   const std::string& message);
	public:
		inline static void SetCallback(CallbackFunc callback);
		inline static void DisableCallback();
		inline static void Log(const std::string& prefix,
							   const std::string& file,
							   const std::string& function,
							   int line,
							   Level level,
							   Type type,
							   const std::string& message);
	private:
		static CallbackFunc func;
	};

	inline void glb::Debug::SetCallback(CallbackFunc callback)
	{
		func = callback;
	}

	inline void Debug::DisableCallback()
	{
		func = nullptr;
	}

	inline void Debug::Log(const std::string& prefix, const std::string& file, const std::string& function, int line, Level level, Type type, const std::string& message)
	{
		std::cout << "GLB " << prefix << ": [" << function << "] " << message << std::endl;
		if (func)
			func(file, function, line, level, type, message);
	}

}