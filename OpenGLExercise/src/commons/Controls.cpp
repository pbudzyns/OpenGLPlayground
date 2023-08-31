#include "Controls.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

static float yOffset;
static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    yOffset = static_cast<float>(yoffset);
}

static float mouseXpos, mouseYpos;
static void coursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    mouseXpos = static_cast<float>(xpos);
    mouseYpos = static_cast<float>(ypos);
}

enum class ArrowPressed
{
    NONE, LEFT, RIGHT, UP, DOWN
};
static ArrowPressed arrow{ ArrowPressed::NONE };
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        arrow = ArrowPressed::UP;
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        arrow = ArrowPressed::DOWN;
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        arrow = ArrowPressed::RIGHT;
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        arrow = ArrowPressed::LEFT;
    else
        arrow = ArrowPressed::NONE;
}


Controls::Controls(GLFWwindow* window) : m_Window{window}
{
    //glfwSetScrollCallback(window, scroll_callback);
    glfwGetWindowSize(window, &m_W, &m_H);
    glfwSetCursorPosCallback(window, coursor_position_callback);
    glfwSetKeyCallback(window, key_callback);
}

Controls::~Controls()
{
}

glm::mat4 Controls::getProjectionMatrix()
{
    m_CurrentFoV = m_InitialFoV;
    return glm::perspective(glm::radians(m_CurrentFoV), 4.0f / 3.0f, 0.1f, 100.0f);
}

glm::mat4 Controls::getViewMatrix()
{
    
    // glfwGetTime is called only once, the first time this function is called
    static double lastTime = glfwGetTime();

    // Compute time difference between current and last frame
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    // Get mouse position
    double xpos, ypos;
    glfwGetCursorPos(m_Window, &xpos, &ypos);

    // Reset mouse position for next frame
    glfwSetCursorPos(m_Window, m_W / 2, m_H / 2);

    // Compute new orientation
    m_HorizontalAngle += m_MouseSpeed * float(m_W / 2 - xpos);
    m_VerticalAngle += m_MouseSpeed * float(m_H / 2 - ypos);

    glm::vec3 direction(
        cos(m_VerticalAngle) * sin(m_HorizontalAngle),
        sin(m_VerticalAngle),
        cos(m_VerticalAngle) * cos(m_HorizontalAngle)
    );

    glm::vec3 right = glm::vec3(
        sin(m_HorizontalAngle - 3.14f / 2.0f),
        0,
        cos(m_HorizontalAngle - 3.14f / 2.0f)
    );

    glm::vec3 up = glm::cross(right, direction);

    switch (arrow)
    {
    case ArrowPressed::UP:
        m_Position += direction * deltaTime * m_Speed;
        break;
    case ArrowPressed::DOWN:
        m_Position -= direction * deltaTime * m_Speed;
        break;
    case ArrowPressed::RIGHT:
        m_Position -= right * deltaTime * m_Speed;
        break;
    case ArrowPressed::LEFT:
        m_Position += right * deltaTime * m_Speed;
        break;
    case ArrowPressed::NONE:
    default:
        break;
    }
    //float radius = 1.0f;/*
    //double time = glfwGetTime();
    //m_Position = glm::ve*/c3(radius * (float)cos(time*0.001), 2.0f, radius * (float)sin(time*0.001));
    lastTime = currentTime;
    return glm::lookAt(
        m_Position,           // Camera is here
        m_Position + direction, // and looks here : at the same position, plus "direction"
        up                  // Head is up (set to 0,-1,0 to look upside-down)
    );
}

glm::mat4 Controls::getModelMatrix()
{
    return glm::mat4(1.0);
}

glm::mat4 Controls::getMVP()
{
    glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();
    glm::mat4 ModelMatrix = getModelMatrix();
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
    return MVP;
}


