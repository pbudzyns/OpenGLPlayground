#pragma once

#include <string>
#include <unordered_map>

#include <GL/glew.h>

#include <glm/glm.hpp>

struct ShaderProgramSource
{
	std::string VertexShader;
	std::string FragmentShader;
};

class Shader
{
public:
	Shader() = default;
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int v);
	void SetUniform1f(const std::string& name, float v);
	void SetUniform3f(const std::string& name, float v1, float v2, float v3);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat3(const std::string& name, const glm::mat3& mat);
	void SetUniformMat4(const std::string& name, const glm::mat4& mat);

	GLuint GetUniformLocation(const std::string& name) const;


private:
	mutable std::unordered_map<std::string, GLuint> m_NameToLocation;

	std::string m_VertexShaderFilePath;
	std::string m_FragmentShaderFilePath;

	unsigned int m_RendererId;
	std::string LoadShaderCode(const std::string& shaderFilePath) const;
	unsigned int CompileShader(unsigned int type, const std::string& source) const;
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const;
};