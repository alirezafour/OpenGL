#pragma once

#include <cstdint>

class VertextBuffer;
class VertexBufferLayout;

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertextBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void UnBind() const;
private:
	uint32_t m_RendererID;
};

