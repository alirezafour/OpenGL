#include "VertexBuffer.h"

#include "Renderer.h"

VertextBuffer::VertextBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID)); // your buffer will be accessed by this int
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); //need to bind our buffer to be drawn if you bind something else it draw the other thing
	GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * size, data, GL_STATIC_DRAW)); // static means it's a hint that doesn't going to be change and will be draw every frame or something

}

VertextBuffer::~VertextBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertextBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertextBuffer::UnBind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
