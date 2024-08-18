#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace glb {

	VertexArray::VertexArray()
		: m_index(0)
	{
		glGenVertexArrays(1, &m_rendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_rendererID);
	}

	void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		vb.Bind();
		Bind();
		const auto& elements = layout.GetElements();
		unsigned int offset = 0;
		for (auto& element : elements)
		{
			glEnableVertexAttribArray(m_index);
			glVertexAttribPointer(m_index, element.count, element.type, element.normalized,
				layout.GetStride(), (void*)offset);
			offset += GetSizeOfType(element.type) * element.count;
			m_index++;
		}
	}

}