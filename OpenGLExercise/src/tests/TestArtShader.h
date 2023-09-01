#pragma once

#include "Test.h"

#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"


namespace test {
	class TestArtShader : public Test {
	public:
		TestArtShader(GLFWwindow* window);
		~TestArtShader();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		int m_Width, m_Height;

		float m_Vertices[8] = {
			-1.0f, -1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f,
			-1.0f,  1.0f,
		};

		unsigned short m_Indices[6] = {
			0, 1, 2,
			2, 3, 0,
		};

		float m_Scales[3] = { 2.0f, 4.0f, 6.0f };

		Shader* m_Shader;
		VertexBuffer m_VertexBuffer;
		VertexArray m_VertexArray;
		IndexBuffer m_IndexBuffer;
	};
}
