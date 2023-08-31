#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <utility>
#include <functional>

namespace test {
	class Test {
	private:
		Test() = default;
		GLFWwindow* m_Window;
	public:
		Test(GLFWwindow* window) : m_Window{ window } {};
		virtual ~Test() = default;

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*& currentTestPointer);
		~TestMenu() = default;

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name, GLFWwindow* window = nullptr) {
			m_Tests.push_back(std::make_pair(name, [window]() {return new T(window); }));
		}

	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};
}