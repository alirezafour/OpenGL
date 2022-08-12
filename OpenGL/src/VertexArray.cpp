#include "VertexArray.h"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertextBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	uint32_t offset = 0;
	const auto& elements = layout.GetElements();
	for (uint32_t i = 0; i < elements.size();i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i); // you should enable doesn't matter after next line or not cuz opengl is state machine way as long as binded it works
		glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(), (const void*)offset); // this code link buffer to vao ( vertex array ) index 0
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}
