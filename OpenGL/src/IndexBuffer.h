#pragma once

#include <cstdint>

class IndexBuffer
{
public:
	IndexBuffer(const uint32_t* data, uint32_t count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const ;

	inline uint32_t GetCount() const { return m_Count; }

private:
	uint32_t m_RendererID; // relevant id for opengl
	uint32_t m_Count;
};

