#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Debug.h"

namespace glb {

	enum class BufferUsage
	{
		Stream = GL_STREAM_DRAW,
		Static = GL_STATIC_DRAW,
		Dynamic = GL_DYNAMIC_DRAW,
	};

	class Enum
	{
	public:
		inline static unsigned int GetSizeOfType(unsigned int type);

	public:
		inline static const int DontCare = GLFW_DONT_CARE;
		inline static const int True = GLFW_TRUE;
		inline static const int False = GLFW_FALSE;

		inline static const unsigned int Int = GL_INT;
		inline static const unsigned int Float = GL_FLOAT;
		inline static const unsigned int Uint = GL_UNSIGNED_INT;
		inline static const unsigned int Double = GL_DOUBLE;
		inline static const unsigned int Short = GL_SHORT;
		inline static const unsigned int Ushort = GL_UNSIGNED_SHORT;
		inline static const unsigned int Ubyte = GL_UNSIGNED_BYTE;
		inline static const unsigned int Byte = GL_BYTE;
		inline static const unsigned int HalfFloat = GL_HALF_FLOAT;
		inline static const unsigned int Fixed = GL_FIXED;
	};

	inline unsigned int glb::Enum::GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case Int:              return 4;
		case Float:            return 4;
		case Uint:			   return 4;
		case Double:           return 8;
		case Short:            return 2;
		case Ushort:		   return 2;
		case Ubyte:			   return 1;
		case Byte:             return 1;
		case HalfFloat:        return 2;
		case Fixed:            return 4;
		}
		GLBWarnH(UnknowType, "Unsupported type '" << type << "'!");
		return 0;
	}

}