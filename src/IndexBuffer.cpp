#include "IndexBuffer.h"

namespace glb {

    void IndexBuffer::Init(void* indices, unsigned int count, BufferUsage usage, unsigned int type)
	{
		GLBAssertEL(type == Enum::Ubyte ||
			        type == Enum::Uint ||
			        type == Enum::Ushort,
					UnknowType,
			        "The type of the indices has to be "
			        "Enum::Ubyte, Enum::Uint, or Enum::Ushort!");

		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
		if (count != 0)
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * Enum::GetSizeOfType(type), indices, (unsigned int) usage);
	}

	IndexBuffer::IndexBuffer(BufferUsage usage, unsigned int type)
		: m_count(1), m_usage(usage), m_type(type)
	{
		Init(nullptr, 1, usage, type);
	}

	IndexBuffer::IndexBuffer(unsigned int count, BufferUsage usage, unsigned int type)
		: m_count(count), m_usage(usage), m_type(type)
	{
		Init(nullptr, count, usage, type);
	}

	IndexBuffer::IndexBuffer(void* indices, int count, BufferUsage usage, unsigned int type)
		: m_count(count), m_usage(usage), m_type(type)
	{
		Init(indices, count, usage, type);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_rendererID);
	}

	void IndexBuffer::SetData(unsigned int count, void* indices)
	{
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * Enum::GetSizeOfType(m_type), indices, (unsigned int) m_usage);
		m_count = count;
	}

}