#pragma once

#include "Test.h"

#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"


namespace test {
	class TestTrippy : public Test {
	public:
		TestTrippy(GLFWwindow* window);
		~TestTrippy();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
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
