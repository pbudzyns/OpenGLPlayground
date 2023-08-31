#pragma once


class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	unsigned int getId() { return m_RrendererId; }


private:
	unsigned int m_RrendererId;
};
