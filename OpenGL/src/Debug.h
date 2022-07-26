#pragma once

#include <GL/glew.h>
#include <cstdint>

void GLAPIENTRY glDebugOutput(GLenum source,
	GLenum type,
	uint32_t id,
	GLenum severity,
	GLsizei length,
	const char* message,
	const void* userParam);

void EnableOpenGLDebug();