#include "Shader.h"

#include <glm/glm.hpp>

#include <sstream>
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
    : m_VertexShaderFilePath{ vertexShaderPath }, m_FragmentShaderFilePath{fragmentShaderPath}
{
    std::string sourceVertex{ LoadShaderCode(vertexShaderPath) };
    std::string  sourceFragment{ LoadShaderCode(fragmentShaderPath) };
    m_RendererId = CreateShader(sourceVertex, sourceFragment);
    glUseProgram(m_RendererId);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererId);
}

void Shader::Bind() const
{
    glUseProgram(m_RendererId);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int v)
{
    glUniform1i(GetUniformLocation(name), v);
}

void Shader::SetUniform1f(const std::string& name, float v)
{
    glUniform1f(GetUniformLocation(name), v);
}

void Shader::SetUniform3f(const std::string& name, float v1, float v2, float v3)
{
    glUniform3f(GetUniformLocation(name), v1, v2, v3);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat3(const std::string& name, const glm::mat3& mat)
{
    glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}
void Shader::SetUniformMat4(const std::string& name, const glm::mat4& mat)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

GLuint Shader::GetUniformLocation(const std::string& name) const
{
    auto it = m_NameToLocation.find(name);
    if (it != m_NameToLocation.end())
        return it->second;

    int location{ glGetUniformLocation(m_RendererId, name.c_str()) };
    m_NameToLocation[name] = location;
    return location;
}

std::string Shader::LoadShaderCode(const std::string& shaderFilePath) const
{
    std::string shaderCode;
    std::ifstream shaderStream(shaderFilePath, std::ios::in);
    if (shaderStream.is_open()) {
        std::stringstream sstr;
        sstr << shaderStream.rdbuf();
        shaderCode = sstr.str();
        shaderStream.close();
    }
    else {
        std::cerr << "Cannot load shader code from file " << shaderFilePath << std::endl;
        return "";
    }
    return shaderCode;
}


unsigned int Shader::CompileShader(unsigned int type, const std::string& source) const
{
    unsigned int id{ glCreateShader(type) };
    const char* src{ source.c_str() };
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message{ (char*)alloca(length * sizeof(char)) };
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " <<
            (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const
{
    unsigned int program = glCreateProgram();
    unsigned int vs{ CompileShader(GL_VERTEX_SHADER, vertexShader) };
    unsigned int fs{ CompileShader(GL_FRAGMENT_SHADER, fragmentShader) };

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
