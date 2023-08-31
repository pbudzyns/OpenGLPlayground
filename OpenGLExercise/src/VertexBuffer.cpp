#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_RrendererId));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RrendererId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RrendererId));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RrendererId));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
