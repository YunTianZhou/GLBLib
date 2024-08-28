#pragma once

#include "Enum.h"

namespace glb {

	class GLB_API VertexBuffer
	{
	public:
		explicit VertexBuffer(BufferUsage usage);

		VertexBuffer(int size, BufferUsage usage);

		VertexBuffer(float vertices[], int size, BufferUsage usage);

		~VertexBuffer();

		inline void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_rendererID); }
		inline void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

		inline int GetSize() const;
		inline BufferUsage GetUsage() const { return m_usage; }

		void SetData(float vertices[], int size);
		void SetSubData(const void* data, int offset, int size);
		float* Map(BufferAccess access) const;
		void Unmap() const;

	private:
		BufferUsage m_usage;
		unsigned int m_rendererID;
	};


	inline int VertexBuffer::GetSize() const
	{
		Bind();
		int size = 0;
		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
		return size;
	}

}