#pragma once

#include "GLCommon.h"

namespace glb {

	class VertexBuffer;
	class VertexBufferLayout;

	class GLB_API VertexArray
	{
	public:
		VertexArray();

		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		inline void Bind() const { glBindVertexArray(m_rendererID); }
		inline void Unbind() const { glBindVertexArray(0); }

	private:
		unsigned int m_index;
		unsigned int m_rendererID;
	};

}