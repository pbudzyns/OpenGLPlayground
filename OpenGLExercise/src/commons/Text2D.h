#pragma once

#include <GL/glew.h>

class Text2D
{
public:
	Text2D(const std::string& texturePath);
	~Text2D();
	void print(const std::string& text, int x, int y, int size);

private:
	GLuint m_Program, m_Text2DUniformID;
	GLuint m_Text2DTextureID;
	GLuint m_TextureSamplerId, m_Text2DVertexBufferID, m_Text2DUVBufferID;

};