#pragma once

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
	unsigned int m_RendererID;
};

