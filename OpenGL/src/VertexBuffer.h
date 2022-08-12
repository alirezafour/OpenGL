#pragma once

#include <cstdint>

class VertextBuffer
{
public:
	VertextBuffer(const void* data, uint32_t size);
	~VertextBuffer();

	void Bind() const;
	void UnBind() const;

private:
	uint32_t m_RendererID; // relevant id for opengl
};

