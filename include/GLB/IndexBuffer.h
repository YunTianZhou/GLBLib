#pragma once

#include "Enum.h"

namespace glb {

	class GLB_API IndexBuffer
	{
	private:
		void Init(void* indices, unsigned int count, BufferUsage usage, unsigned int type);

	public:
		IndexBuffer(BufferUsage usage, unsigned int type = Enum::Uint);

		IndexBuffer(unsigned int count, BufferUsage usage, unsigned int type = Enum::Uint);

		IndexBuffer(void* indices, int count, BufferUsage usage, unsigned int type = Enum::Uint);

		~IndexBuffer();

		inline void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID); }
		inline void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

		inline int GetCount() const { return m_count; }
		inline unsigned int GetType() const { return m_type; }
		inline BufferUsage GetUsage() const { return m_usage; }

		void SetData(unsigned int count, void* indices);

	private:
		unsigned int m_count;
		BufferUsage m_usage;
		unsigned int m_type;
		unsigned int m_rendererID;
	};

}