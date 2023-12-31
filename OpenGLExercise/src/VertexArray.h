#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

#include <vector>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;


private:
	size_t m_Counter;
	unsigned int m_RendererId;
	std::vector<const VertexBuffer*> vbs;
	std::vector<const VertexBufferLayout*> vls;
};

