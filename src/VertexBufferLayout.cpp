#include "VertexBufferLayout.h"

namespace glb {

    std::unordered_map<Enum_t, VertexBufferLayout::TypeAttrib> VertexBufferLayout::s_typeToAttrib = {
        { Enum::Float, { Enum::GetSizeOfType(Enum::Float), GL_FALSE } },
        { Enum::Uint, { Enum::GetSizeOfType(Enum::Uint), GL_FALSE } },
        { Enum::Ubyte, { Enum::GetSizeOfType(Enum::Ubyte), GL_TRUE } },
        { Enum::Int, { Enum::GetSizeOfType(Enum::Int), GL_FALSE } },
        { Enum::Double, { Enum::GetSizeOfType(Enum::Double), GL_FALSE } },
        { Enum::Short, { Enum::GetSizeOfType(Enum::Short), GL_FALSE } },
        { Enum::Ushort, { Enum::GetSizeOfType(Enum::Ushort), GL_FALSE } },
        { Enum::Byte, { Enum::GetSizeOfType(Enum::Byte), GL_TRUE } },
        { Enum::HalfFloat, { Enum::GetSizeOfType(Enum::HalfFloat), GL_FALSE } },
    };

}