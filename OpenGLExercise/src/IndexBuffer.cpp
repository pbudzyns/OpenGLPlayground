#include "IndexBuffer.h"
#include "Renderer.h"

//IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
//    : m_Count(count)
//{
//    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
//    GLCall(glGenBuffers(1, &m_RrendererId));
//    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RrendererId));
//    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
//}

IndexBuffer::IndexBuffer(const unsigned short* data, unsigned int count)
    : m_Count(count)
{
    //ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    GLCall(glGenBuffers(1, &m_RrendererId));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RrendererId));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned short), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RrendererId));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RrendererId));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
