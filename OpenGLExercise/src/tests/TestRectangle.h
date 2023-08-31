#pragma once

#include "tests/Test.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

namespace test {
	class TestRectangle : public Test {
	public:
		TestRectangle(GLFWwindow* window);
		~TestRectangle();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		Shader* m_Shader{nullptr};
		VertexArray* va{ nullptr };
		IndexBuffer* ib{nullptr};
		VertexBuffer* vb{ nullptr };
		VertexBufferLayout* layout{ nullptr };

		float* m_Positions;
		unsigned short* m_Indices;
		float m_Color[4];
	};
}
