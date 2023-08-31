#include <GL/glew.h>

#include "VertexArray.h"

#include <iostream>

VertexArray::VertexArray() : m_Counter{0}
{
	glGenVertexArrays(1, &m_RendererId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererId);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	const auto& elements{ layout.GetElements() };
	unsigned int offset{ 0 };
	vb.Bind();

	for (const auto& element: elements)
	{
		std::cout << "Registering attribute " << m_Counter << std::endl;
		glEnableVertexAttribArray(m_Counter);
		glVertexAttribPointer(
			m_Counter,
			element.count,
			element.type,
			element.normalized,
			layout.GetStride(),
			(const void*)0
		);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		++m_Counter;
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererId);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
