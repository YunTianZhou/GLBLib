#pragma once

#include <vector>
#include "Enum.h"

namespace glb {

	struct GLB_API VertexBufferElement
	{
		unsigned int type;
		unsigned int count;
		unsigned char normalized;
	};

	class GLB_API VertexBufferLayout
	{
	public:
		VertexBufferLayout()
			: m_stride(0)
		{

		}

		template<typename T>
		void Push(unsigned int count)
		{
			GLBErrL(UnknowType, "Unsupport the type '" << typeid(T) << "'!");
		}

		template<>
		void Push<float>(unsigned int count)
		{
			m_elements.push_back({ Enum::Float, count, GL_FALSE });
			m_stride += count * Enum::GetSizeOfType(Enum::Float);
		}

		template<>
		void Push<unsigned int>(unsigned int count)
		{
			m_elements.push_back({ Enum::Uint, count, GL_FALSE });
			m_stride += count * Enum::GetSizeOfType(Enum::Uint);
		}

		template<>
		void Push<unsigned char>(unsigned int count)
		{
			m_elements.push_back({ Enum::Ubyte, count, GL_TRUE });
			m_stride += count * Enum::GetSizeOfType(Enum::Ubyte);
		}

		inline const std::vector <VertexBufferElement>GetElements() const { return m_elements; }
		inline unsigned int GetStride() const { return m_stride; }

	private:
		std::vector <VertexBufferElement> m_elements;
		unsigned int m_stride;
	};

}