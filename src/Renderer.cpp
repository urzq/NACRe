#include <iostream>
#include <exception>

#include <GL/glew.h>
#include <glfw3.h>

#include "Renderer.h"

Renderer::Renderer(const char* windowName, glm::uvec2 windowSize) :
	m_Window(nullptr)
{
	if (!glfwInit())
	{
		throw std::exception("Failed to initialize GLFW");
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	m_Window = glfwCreateWindow(windowSize.x, windowSize.y, windowName, nullptr, nullptr);

	if (m_Window == nullptr)
	{
		glfwTerminate();
		throw std::exception("Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible");
	}

	glfwMakeContextCurrent(m_Window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		throw std::exception("Failed to initialize GLEW\n");
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	glfwPollEvents();
	glfwSetCursorPos(m_Window, windowSize.x / 2, windowSize.y / 2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
}

Renderer::~Renderer()
{
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

bool Renderer::IsRunning()
{
	// Check if the ESC key was pressed or the window was closed
	return glfwGetKey(m_Window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(m_Window) == 0;
}

void Renderer::Render()
{
	// Swap buffers
	glfwSwapBuffers(m_Window);
	glfwPollEvents();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

GLFWwindow* Renderer::GetGLFWwindow() const
{
	return m_Window;
}