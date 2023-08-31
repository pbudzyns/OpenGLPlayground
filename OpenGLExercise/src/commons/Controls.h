#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Controls
{
public:
	Controls(GLFWwindow* window);
	~Controls() = default;
	glm::mat4 getProjectionMatrix();
	glm::mat4 getViewMatrix();
	glm::mat4 getModelMatrix();
	glm::mat4 getMVP();
private:
	glm::vec3 m_Position{ 0, 0, 5 };
	float m_HorizontalAngle{ 3.14f };
	float m_VerticalAngle{ 0.0f };
	float m_InitialFoV{ 45.0f };
	float m_CurrentFoV{ 45.0f };
	double m_LastTime{ glfwGetTime() };

	float m_WCenter{ 512.0f };
	float m_HCenter{ 768.0f / 2.0f };

	float m_Speed{ 3.0f };
	float m_MouseSpeed{ 0.002f };

	int m_W, m_H;

	GLFWwindow* m_Window;

};

