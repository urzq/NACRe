#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <GL/glew.h>
#include <glfw3.h>

#include <glm/glm.hpp>

class Renderer
{
public:
	Renderer(const char* windowName, glm::uvec2 windowSize);
	~Renderer();

	void Render();
	bool IsRunning();

	GLFWwindow* GetGLFWwindow() const;

private:
	GLFWwindow* m_Window;
};

#endif