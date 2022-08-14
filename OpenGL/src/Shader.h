#pragma once

#include <string>
#include <cstdint>
#include <unordered_map>
#include <Tuple>
#include "glm/gtc/matrix_transform.hpp"


class Shader
{
public:
	Shader(const std::string& filePath);
	~Shader();

	void Bind() const; 
	void UnBind() const;

	// Set Uniforms
	void SetUniform1i(const std::string& name, int32_t value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
	uint32_t CompileShader(uint32_t type, const std::string& source);
	uint32_t CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	std::tuple<std::string, std::string> ParseShader(const std::string& filepath);
	int32_t GetUniformLocation(const std::string& name);

private:
	uint32_t m_RendererID;
	std::string m_FilePath;
	std::unordered_map<std::string, int32_t> m_UniformLocationCache;
};

