#include "IndexBuffer.h"

#include "Renderer.h"

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count)
	: m_Count(count)
{
	ASSERT(sizeof(uint32_t) == sizeof(GLuint));

	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::UnBind() const 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
