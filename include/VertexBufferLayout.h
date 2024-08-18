#pragma once

#include "Common.h"

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
			GLError("Unsupport this type!");
		}

		template<>
		void Push<float>(unsigned int count)
		{
			m_elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_stride += count * GetSizeOfType(GL_FLOAT);
		}

		template<>
		void Push<unsigned int>(unsigned int count)
		{
			m_elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			m_stride += count * GetSizeOfType(GL_UNSIGNED_INT);
		}

		template<>
		void Push<unsigned char>(unsigned int count)
		{
			m_elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
			m_stride += count * GetSizeOfType(GL_UNSIGNED_BYTE);
		}

		inline const std::vector <VertexBufferElement>GetElements() const { return m_elements; }
		inline unsigned int GetStride() const { return m_stride; }

	private:
		std::vector <VertexBufferElement> m_elements;
		unsigned int m_stride;
	};

}