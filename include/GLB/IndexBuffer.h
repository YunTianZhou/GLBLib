#pragma once

#include "Enum.h"

namespace glb {

	class GLB_API IndexBuffer
	{
	public:
		explicit IndexBuffer(BufferUsage usage, Enum_t type = Enum::Uint);

		IndexBuffer(unsigned int count, BufferUsage usage, Enum_t type = Enum::Uint);

		IndexBuffer(void* indices, int count, BufferUsage usage, Enum_t type = Enum::Uint);

		~IndexBuffer();

		inline void Bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID); }
		inline void Unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

		inline int GetCount() const;
		inline unsigned int GetType() const { return m_type; }
		inline BufferUsage GetUsage() const { return m_usage; }

		void SetData(unsigned int count, void* indices);
		void SetSubData(const void* data, int offset, int size);
		void* Map(BufferAccess access) const;
		void Unmap() const;

	private:
		void Init(void* indices, unsigned int count, BufferUsage usage, Enum_t type);

	private:
		BufferUsage m_usage;
		Enum_t m_type;
		unsigned int m_rendererID;
	};

	inline int IndexBuffer::GetCount() const
	{
		int bufferSize = 0;
		Bind();
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &bufferSize);
		return bufferSize / Enum::GetSizeOfType(m_type);
	}

}