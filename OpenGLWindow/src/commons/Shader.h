#pragma once
#include <GL/glew.h>

#include <string>


class Shader
{
public:
	static GLuint LoadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

private:
	std::string m_VertexShaderFile, m_FragmentShaderFile;
	static std::string LoadShaderCode(const std::string& shaderFilePath);
};
