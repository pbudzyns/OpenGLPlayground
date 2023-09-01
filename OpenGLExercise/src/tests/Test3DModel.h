#pragma once

#include "Test.h"

#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

#include "commons/loadObj.h"
#include "commons/Controls.h"


namespace test {
	class Test3DModel : public Test {
	public:
		Test3DModel(GLFWwindow* window);
		~Test3DModel();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		OBJModelIndexed modelIndexed;
		GLuint VertexArrayID, vertexbuffer, uvbuffer, normalbuffer, elementbuffer;
		GLuint texture;

		float m_RotateSpeed{ 1.0f };
		float m_MaterialGlow{ 50.0f };
		float m_LightPower;
		float m_LightPosition[3];
		float m_LightColor[3];

		Shader* m_Shader{ nullptr };
		VertexArray* va{ nullptr };
		IndexBuffer* ib{ nullptr };
		VertexBuffer* vb{ nullptr };
		VertexBuffer* uvb{ nullptr };
		VertexBuffer* norb{ nullptr };

		VertexBufferLayout* layout_vb{ nullptr };
		VertexBufferLayout* layout_uv{ nullptr };
		VertexBufferLayout* layout_nor{ nullptr };

		Controls* m_Controls{ nullptr };
	};
}
