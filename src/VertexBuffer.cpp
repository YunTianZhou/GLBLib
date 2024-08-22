#include "VertexBuffer.h"

namespace glb {
	
	VertexBuffer::VertexBuffer(BufferUsage usage)
		: m_size(1), m_usage(usage)
	{
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, 1, nullptr, (unsigned int) usage);
	}

	VertexBuffer::VertexBuffer(int size, BufferUsage usage)
		: m_size(size), m_usage(usage)
	{
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, (unsigned int) usage);
	}

	VertexBuffer::VertexBuffer(float vertices[], int size, BufferUsage usage)
		: m_size(size), m_usage(usage)
	{
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, (unsigned int) usage);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_rendererID);
	}

	void VertexBuffer::SetData(float vertices[], int size)
	{
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, vertices, (unsigned int) m_usage);
		m_size = size;
	}

}