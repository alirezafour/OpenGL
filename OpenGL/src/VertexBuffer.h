#pragma once

class VertextBuffer
{
public:
	VertextBuffer(const void* data, unsigned int size);
	~VertextBuffer();

	void Bind() const;
	void UnBind() const;

private:
	unsigned int m_RendererID; // relevant id for opengl
};

