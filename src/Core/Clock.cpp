#include <GLFW/glfw3.h>

#include "Clock.h"

Clock::Clock()
{
	m_LastTime = glfwGetTime();
	m_CurrentTime = glfwGetTime();
}

void Clock::Update()
{
	m_LastTime = m_CurrentTime;
	m_CurrentTime = glfwGetTime();
}

float Clock::dT()
{
	return m_CurrentTime - m_LastTime;
}


