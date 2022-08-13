#pragma once

#include <GL/glew.h>
#include <cstdint>
#include <iostream>

class VertexArray;
class IndexBuffer;
class Shader;

void GLAPIENTRY glDebugOutput(GLenum source,
	GLenum type,
	uint32_t id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam);

void EnableOpenGLDebug();

// break point on error with VS only
#define ASSERT(x) if (!(x)) __debugbreak();

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};