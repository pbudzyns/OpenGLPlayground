#pragma once

#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
	std::string VertexShader;
	std::string FragmentShader;
};

class Shader
{
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	mutable std::unordered_map<std::string, int> m_NameToLocation;
	std::string m_FilePath;
	unsigned int m_RendererId;
	int GetUniformLocation(const std::string& name) const;
	ShaderProgramSource ParseShaders(const std::string& filepath) const;
	unsigned int CompileShader(unsigned int type, const std::string& source) const;
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const;
};