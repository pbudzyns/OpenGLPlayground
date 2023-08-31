#include "TestClearColor.h"

#include <GL/glew.h>
#include <imgui/imgui.h>
#include "Renderer.h"

namespace test {
	TestClearColor::TestClearColor()
		: m_Color{0.2f, 0.3f, 0.8f, 1.0f}
	{
	}

	TestClearColor::~TestClearColor()
	{
	}

	void TestClearColor::OnUpdate(float delatTime)
	{
	}

	void TestClearColor::OnRender()
	{
		glClearColor(m_Color[0], m_Color[1], m_Color[2], m_Color[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_Color);
	}
}