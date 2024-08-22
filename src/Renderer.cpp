#include "Renderer.h"

#include "Enum.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace glb {

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::DrawArray(Mode mode, const VertexArray& va, const Shader& shader, unsigned int first, unsigned int count)
	{
		shader.Bind();
		va.Bind();
		glDrawArrays((unsigned int) mode, first, count);
	}

	void Renderer::DrawElements(Mode mode, const VertexArray& va, const IndexBuffer& ib, const Shader& shader, int count, unsigned int first)
	{
		shader.Bind();
		va.Bind();
		ib.Bind();
		if (count < 0) count = ib.GetCount();
		glDrawElements((unsigned int) mode, count, ib.GetType(),
			(void*) (first * Enum::GetSizeOfType(ib.GetType())));
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Renderer::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}
}
