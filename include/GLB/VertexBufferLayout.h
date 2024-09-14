#pragma once

#include <vector>
#include <unordered_map>
#include "Enum.h"

namespace glb {

    class GLB_API VertexBufferLayout
    {
    private:
        struct Element
        {
            Enum_t type;
            unsigned int count;
            unsigned char normalized;
        };

        struct TypeAttrib
        {
            unsigned int size;
            unsigned char normalized;
        };

    public:
        VertexBufferLayout()
            : m_stride(0)
        {
        }

        template<Enum_t type>
        inline void Push(unsigned int count)
        {
            auto it = s_typeToAttrib.find(type);
            if (it != s_typeToAttrib.end())
            {
                const TypeAttrib& attrib = it->second;
                m_elements.push_back({ type, count, attrib.normalized });
                m_stride += count * attrib.size;
            }
            else
            {
                GLBErrL(UnknownType, "Unsupported vertex buffer element type '" << type << "'");
            }
        }

    private:
        friend class VertexArray;
        inline const std::vector<Element>& GetElements() const { return m_elements; }
        inline unsigned int GetStride() const { return m_stride; }

    private:
        static std::unordered_map<Enum_t, TypeAttrib> s_typeToAttrib;

    private:
        std::vector<Element> m_elements;
        unsigned int m_stride;
    };

}