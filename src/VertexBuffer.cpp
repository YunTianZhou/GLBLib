#include "VertexBuffer.h"

namespace glb {
	
	VertexBuffer::VertexBuffer(unsigned int usage)
		: m_size(1), m_usage(usage)
	{
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, 1, nullptr, usage);
	}

	VertexBuffer::VertexBuffer(int size, unsigned int usage)
		: m_size(size), m_usage(usage)
	{
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, usage);
	}

	VertexBuffer::VertexBuffer(float vertices[], int size, unsigned int usage)
		: m_size(size), m_usage(usage)
	{
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_rendererID);
	}

	void VertexBuffer::SetData(int size, float vertices[])
	{
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, m_usage);
		m_size = size;
	}

}