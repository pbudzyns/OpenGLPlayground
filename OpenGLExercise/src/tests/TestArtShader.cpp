#include "TestArtShader.h"

#include <imgui/imgui.h>
#include <iostream>
#include "Renderer.h"
#include "VertexBufferLayout.h"

namespace test {
	TestArtShader::TestArtShader(GLFWwindow* window)
		: Test(window)
		, m_Shader{nullptr}
		, m_VertexBuffer(m_Vertices, 8 * sizeof(float))
		, m_IndexBuffer(m_Indices, 6)
	{
		VertexBufferLayout layout;
		layout.Push<float>(2);
		m_VertexArray.AddBuffer(m_VertexBuffer, layout);
		m_Shader = new Shader(
			"res/shaders/artVertex.glsl",
			"res/shaders/artFragment.glsl"
		);
	}
	TestArtShader::~TestArtShader()
	{
		m_VertexArray.Unbind(); m_VertexBuffer.Unbind(); m_IndexBuffer.Unbind();
		m_Shader->Unbind();
		delete m_Shader;
		
	}
	void TestArtShader::OnUpdate(float deltaTime)
	{
	}
	void TestArtShader::OnRender()
	{
		glfwGetWindowSize(m_Window, &m_Width, &m_Height);
		m_Shader->SetUniform1f("time", (float)glfwGetTime());
		m_Shader->SetUniform1f("xScale", m_Scales[0]);
		m_Shader->SetUniform1f("yScale", m_Scales[1]);
		m_Shader->SetUniform1f("zScale", m_Scales[2]);
		m_Shader->SetUniform1f("width", (float)m_Width);
		m_Shader->SetUniform1f("height", (float)m_Height);
		Renderer::Clear();
		Renderer::Draw(m_VertexArray, m_IndexBuffer, *m_Shader);
	}
	void TestArtShader::OnImGuiRender()
	{
		ImGui::DragFloat3("Frequency", m_Scales, 0.1f);
	}
}