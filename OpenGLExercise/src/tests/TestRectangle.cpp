#include "tests/TestRectangle.h"

#include <imgui/imgui.h>

#include "Renderer.h"

namespace test {



	TestRectangle::TestRectangle()
		: m_Color{0.2f, 0.4f, 0.8f, 1.0f}
	{
		m_Positions = new float[8]{
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};

		m_Indices = new unsigned int[6]{
			0, 1, 2,
			2, 3, 0
		};

		va = new VertexArray();
		vb = new VertexBuffer(m_Positions, 2 * 4 * sizeof(float));

		layout = new VertexBufferLayout();
		layout->Push<float>(2);
		va->AddBuffer(*vb, *layout);

		ib = new IndexBuffer(m_Indices, 6);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		m_Shader = new Shader("res/shaders/Basic.shader");
	}

	TestRectangle::~TestRectangle()
	{
		delete[] m_Positions;
		delete[] m_Indices;
		delete va;
		delete ib;
		delete m_Shader;
		delete vb;
		delete layout;
	}

	void TestRectangle::OnUpdate(float deltaTime)
	{
	}
	void TestRectangle::OnRender()
	{
		Renderer::Clear();
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
		Renderer::Draw(*va, *ib, *m_Shader);
	}
	void TestRectangle::OnImGuiRender()
	{
		ImGui::ColorEdit4("Color", m_Color);
	}
}