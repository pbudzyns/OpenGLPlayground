#include <GL/glew.h>

#include "VertexArray.h"

#include <iostream>

VertexArray::VertexArray()
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
	static int i{ 0 };
	const auto& elements{ layout.GetElements() };
	unsigned int offset{ 0 };
	vb.Bind();

	for (const auto& element: elements)
	{
		std::cout << "Registering attribute " << i << std::endl;
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type,
			element.normalized, 0, (const void*)0);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
		i++;
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
