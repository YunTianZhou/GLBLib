#include "VertexBuffer.h"

namespace glb {
	
	VertexBuffer::VertexBuffer(BufferUsage usage)
		: m_usage(usage)
	{
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, 1, nullptr, (unsigned int) usage);
	}

	VertexBuffer::VertexBuffer(int size, BufferUsage usage)
		: m_usage(usage)
	{
		glGenBuffers(1, &m_rendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, (unsigned int) usage);
	}

	VertexBuffer::VertexBuffer(float vertices[], int size, BufferUsage usage)
		: m_usage(usage)
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
	}

	void VertexBuffer::SetSubData(const void* data, int offset, int size)
	{
		Bind();
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}

	float* VertexBuffer::Map(BufferAccess access) const
	{
		Bind();
		void* pointer = glMapBuffer(GL_ARRAY_BUFFER, (unsigned int) access);
		GLBAssertWH(pointer, MapBufferFailed, "Failed to map the vertex buffer!");
		return (float*) pointer;
	}

	void VertexBuffer::Unmap() const
	{
		Bind();
		GLBAssertWH(glUnmapBuffer(GL_ARRAY_BUFFER), UnmapBufferFailed, "Failed to unmap the vertex buffer!");
	}

}