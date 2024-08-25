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

		inline int GetSize() const { return m_size; }
		inline BufferUsage GetUsage() const { return m_usage; }

		void SetData(float vertices[], int size);

	private:
		int m_size;
		BufferUsage m_usage;
		unsigned int m_rendererID;
	};

}