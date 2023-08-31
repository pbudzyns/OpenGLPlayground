#include <GL/glew.h>

#include "Shader.h"

#include <sstream>
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& filepath) : m_FilePath(filepath)
{
    ShaderProgramSource source{ ParseShaders(m_FilePath) };
    m_RendererId = CreateShader(source.VertexShader, source.FragmentShader);
    glUseProgram(m_RendererId);
}

Shader::~Shader()
{
}

void Shader::Bind() const
{
    glUseProgram(m_RendererId);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

int Shader::GetUniformLocation(const std::string& name) const
{
    auto it = m_NameToLocation.find(name);
    if (it != m_NameToLocation.end())
        return it->second;

    int location{ glGetUniformLocation(m_RendererId, name.c_str()) };
    m_NameToLocation[name] = location;
    return location;
}

ShaderProgramSource Shader::ParseShaders(const std::string& filepath) const
{
    enum class ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];
    ShaderType type{ ShaderType::NONE };

    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[static_cast<int>(type)] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
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
