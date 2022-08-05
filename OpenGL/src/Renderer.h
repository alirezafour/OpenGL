#pragma once

#include <GL/glew.h>

class VertexArray;
class IndexBuffer;
class Shader;

// break point on error with VS only
#define ASSERT(x) if (!(x)) __debugbreak();

// Error Checking with x macro
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};