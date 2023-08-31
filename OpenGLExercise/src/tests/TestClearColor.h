#pragma once
#include "Test.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace test {

	class TestClearColor : public Test {
	public:
		TestClearColor(GLFWwindow* window);
		~TestClearColor();

		void OnUpdate(float delatTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		float m_Color[4];
	};
}
