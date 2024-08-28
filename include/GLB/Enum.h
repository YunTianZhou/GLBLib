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

	enum class BufferAccess
	{
		ReadOnly = GL_READ_ONLY,
		WriteOnly = GL_WRITE_ONLY,
		ReadWrite = GL_READ_WRITE,
	};

	using Enum_t = unsigned int;

	class Enum
	{
	public:
		inline static unsigned int GetSizeOfType(Enum_t type);

	public:
		inline static const Enum_t Int = GL_INT;
		inline static const Enum_t Float = GL_FLOAT;
		inline static const Enum_t Uint = GL_UNSIGNED_INT;
		inline static const Enum_t Double = GL_DOUBLE;
		inline static const Enum_t Short = GL_SHORT;
		inline static const Enum_t Ushort = GL_UNSIGNED_SHORT;
		inline static const Enum_t Ubyte = GL_UNSIGNED_BYTE;
		inline static const Enum_t Byte = GL_BYTE;
		inline static const Enum_t HalfFloat = GL_HALF_FLOAT;
	};

	inline unsigned int glb::Enum::GetSizeOfType(Enum_t type)
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
		}
		GLBWarnH(UnknowType, "Unsupported enum type '" << type << "'");
		return 0;
	}

}