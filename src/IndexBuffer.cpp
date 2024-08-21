#include "IndexBuffer.h"

namespace glb {

    void IndexBuffer::Init(void* indices, unsigned int count, unsigned int usage, unsigned int type)
	{
		GLASSERT(type == GL_UNSIGNED_BYTE ||
			     type == GL_UNSIGNED_INT ||
			     type == GL_UNSIGNED_SHORT,
			     "The type of the indices have to be "
			     "GL_UNSIGNED_BYTE, GL_UNSIGNED_INT, or GL_UNSIGNED_SHORT!");

		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
		if (count != 0)
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * GetSizeOfType(type), indices, usage);
	}

	IndexBuffer::IndexBuffer(unsigned int usage, unsigned int type)
		: m_count(1), m_usage(usage), m_type(type)
	{
		Init(nullptr, 1, usage, type);
	}

	IndexBuffer::IndexBuffer(unsigned int count, unsigned int usage, unsigned int type)
		: m_count(count), m_usage(usage), m_type(type)
	{
		Init(nullptr, count, usage, type);
	}

	IndexBuffer::IndexBuffer(void* indices, int count, unsigned int usage, unsigned int type)
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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * GetSizeOfType(m_type), indices, m_usage);
		m_count = count;
	}

}