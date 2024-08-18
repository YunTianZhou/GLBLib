#pragma once

#include "GLCommon.h"

namespace glb {

	class GLB_API IndexBuffer
	{
	private:
		void Init(void* indices, unsigned int count, unsigned int usage, unsigned int type);

	public:
		IndexBuffer(unsigned int usage, unsigned int type = GL_UNSIGNED_INT);

		IndexBuffer(unsigned int count, unsigned int usage, unsigned int type = GL_UNSIGNED_INT);

		IndexBuffer(void* indices, int count, unsigned int usage, unsigned int type = GL_UNSIGNED_INT);

		~IndexBuffer();

		inline void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID); }
		inline void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

		inline int GetCount() const { return m_count; }
		inline unsigned int GetType() const { return m_type; }

		void SetData(unsigned int count, void* indices);

	private:
		unsigned int m_count;
		unsigned int m_usage;
		unsigned int m_type;
		unsigned int m_rendererID;
	};

}