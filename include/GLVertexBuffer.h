#pragma once

#include "GLCommon.h"

namespace glb {

	class GLB_API VertexBuffer
	{
	public:
		VertexBuffer(unsigned int usage);

		VertexBuffer(int size, unsigned int usage);

		VertexBuffer(float vertices[], int size, unsigned int usage);

		~VertexBuffer();

		inline void Bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_rendererID); }
		inline void Unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }

		inline int GetSize() const { return m_size; }

		void SetData(int size, float vertices[]);

	private:
		int m_size;
		unsigned int m_usage;
		unsigned int m_rendererID;
	};

}