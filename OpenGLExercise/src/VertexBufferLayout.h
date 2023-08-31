#pragma once

#include <GL/glew.h>

#include <vector>


struct VertexBufferElement
{
	GLenum type;
	GLint count;
	GLboolean normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		default:
			return 0;
		}
	}
};


class VertexBufferLayout
{
public:
	VertexBufferLayout() : m_Stride{ 0 } {};

	template<typename T>
	void Push(unsigned int count)
	{
		//static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, static_cast<GLint>(count), static_cast<GLint>(false) });
		m_Stride += count * sizeof(GLfloat);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, static_cast<GLint>(count), static_cast<GLint>(false) });
		m_Stride += count * sizeof(GLuint);
	}

	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
	inline unsigned int GetStride() const { return m_Stride; }

private:
	unsigned int m_Stride;
	std::vector<VertexBufferElement> m_Elements;
};

