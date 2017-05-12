#include <iostream>
#include <exception>
#include <algorithm>

#include <GL/glew.h>
#include <glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw_gl3.h>

#include "Shader/ShaderProgram.h"
#include "VertexBuffer/VertexBuffer.h"

#include "Renderable.h"
#include "Renderer.h"

Renderer::Renderer() :
	m_Window(nullptr),
	m_CurrentVertexBuffer(nullptr),
	m_CurrentShaderProgram(nullptr),
	m_ImGuiActivated(false),
	m_GraveAccentPressed(false)
{
}

Renderer::~Renderer()
{
	glfwTerminate();
}

void Renderer::Init(const char* windowName, glm::uvec2 windowSize)
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

	ImGui_ImplGlfwGL3_Init(m_Window, true);

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

void Renderer::SetClearColor(glm::vec3 clearColor)
{
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 0.0f);
}

bool Renderer::IsRunning() const
{
	// Check if the ESC key was pressed or the window was closed
	return glfwGetKey(m_Window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(m_Window) == 0;
}

bool Renderer::IsImGuiActivated() const
{
	return m_ImGuiActivated;
}

void Renderer::NewFrame()
{
	glfwPollEvents();

	// TODO: input manager. This is ugly.
	if ( !m_GraveAccentPressed && glfwGetKey(m_Window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS )
	{
		m_ImGuiActivated = !m_ImGuiActivated;
		m_GraveAccentPressed = true;
		std::cout << "coucuo\n";

		auto cursorMode = m_ImGuiActivated ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
		glfwSetInputMode(m_Window, GLFW_CURSOR, cursorMode);

		if (!m_ImGuiActivated)
		{
			glfwSetCursorPos(m_Window, 1024 / 2, 768 / 2);
		}
	}
	
	if (m_GraveAccentPressed && glfwGetKey(m_Window, GLFW_KEY_GRAVE_ACCENT) == GLFW_RELEASE)
	{
		m_GraveAccentPressed = false;
	}

	ImGui_ImplGlfwGL3_NewFrame();
}

void Renderer::Render(const glm::mat4& projection, const glm::mat4& view)
{
	// TODO: sort the renderable vector, to minimize the state change (not really needed now)
	for (Renderable* renderable : m_Renderables)
	{
		RefreshShader(renderable->GetShaderProgram(), projection, view);
		RefreshVertexBuffer(renderable->GetVertexBuffer());

		glm::mat4 transform = renderable->GetTransform().GetMatrix();
		m_CurrentShaderProgram->SetModel(transform);

		glm::vec3 color = renderable->GetColor();
		m_CurrentShaderProgram->SetColor(color);

		int nbVertice = m_CurrentVertexBuffer->GetNbVertice();
		glDrawArrays(GL_TRIANGLES, 0, nbVertice);
	}

	if (m_ImGuiActivated)
	{
		ImGui::Render();
	}

	glfwSwapBuffers(m_Window);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::RefreshShader(ShaderProgram* newShader, const glm::mat4& projection, const glm::mat4& view)
{
	if (m_CurrentShaderProgram != newShader)
	{
		m_CurrentShaderProgram = newShader;
		m_CurrentShaderProgram->Use();
		m_Light.SetShaderProgram(newShader);

		m_CurrentShaderProgram->SetProjection(projection);
		m_CurrentShaderProgram->SetView(view);
	}
}

void Renderer::RefreshVertexBuffer(VertexBuffer* newVertexBuffer)
{
	if (m_CurrentVertexBuffer = newVertexBuffer)
	{
		m_CurrentVertexBuffer = newVertexBuffer;
		m_CurrentVertexBuffer->Use();
	}
}


GLFWwindow* Renderer::GetGLFWwindow() const
{
	return m_Window;
}

Light& Renderer::GetLight()
{
	return m_Light;
}

Renderable* Renderer::CreateRenderable(VertexBuffer* refVertexBuffer, ShaderProgram* refShaderProgram)
{
	auto renderable = new Renderable(refVertexBuffer, refShaderProgram);
	m_Renderables.push_back(renderable);
	
	return renderable;
}

void Renderer::DestroyRenderable(Renderable* renderable)
{
	m_Renderables.erase(std::remove(m_Renderables.begin(), m_Renderables.end(), renderable), m_Renderables.end());
	delete renderable;
}