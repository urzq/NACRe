#include <iostream>
#include <exception>
#include <algorithm>

#include <imgui/imgui.h>
#include <ImGUiImpl/imgui_impl_glfw_gl3.h>

#include "Shader/ShaderProgram.h"
#include "VertexBuffer/VertexBuffer.h"
#include "Texture/GLTexture.h"

#include "Renderable.h"
#include "Renderer.h"

using namespace memory;

Renderer::Renderer() :
	m_Window(nullptr),
	m_CurrentVertexBuffer(nullptr),
	m_CurrentShaderProgram(nullptr),
	m_ImGuiEnabled(false)
{
}

Renderer::~Renderer()
{
	ImGui::DestroyContext();
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

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplGlfwGL3_Init(m_Window, true);
	ImGui::StyleColorsDark();

	glfwMakeContextCurrent(m_Window);

	if ( !gladLoadGL())
	{
		glfwTerminate();
		throw std::exception("Failed to initialize GLEW\n");
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set the mouse at the center of the screen
	m_WindowSize = windowSize;
	glfwPollEvents();

	// Todo: move this to input
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
	// Check if the window was closed
	return glfwWindowShouldClose(m_Window) == 0;
}

void Renderer::ToggleImGuiEnabled()
{
	m_ImGuiEnabled = ! m_ImGuiEnabled;

	// TODO: somehow, move this to input manager.
	if (m_ImGuiEnabled)
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPos(m_Window, m_WindowSize.x / 2, m_WindowSize.y / 2);
	}
}

bool Renderer::IsImGuiEnabled() const
{
	return m_ImGuiEnabled;
}

void Renderer::NewFrame()
{
	glfwPollEvents();
	ImGui_ImplGlfwGL3_NewFrame();
}

void Renderer::Render(const glm::mat4& projection, const glm::mat4& view)
{
	// TODO: sort the renderable vector, to minimize the state change (not really needed now)
	for (Renderable* renderable : m_Renderables)
	{
		RefreshShader(renderable->GetShaderProgram(), projection, view);
		RefreshVertexBuffer(renderable->GetVertexBuffer());
		RefreshTextures(renderable->GetTextures());

		glm::mat4 transform = renderable->GetTransform().GetMatrix();
		m_CurrentShaderProgram->SetModel(transform);

		glm::vec3 color = renderable->GetColor();
		m_CurrentShaderProgram->SetColor(color);

		int nbVertice = m_CurrentVertexBuffer->GetNbVertice();
		glDrawArrays(GL_TRIANGLES, 0, nbVertice);
	}

	ImGui::Render();

	if (m_ImGuiEnabled)
	{
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
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
		m_Light.ApplyParametersToShader(newShader);

		m_CurrentShaderProgram->SetProjection(projection);
		m_CurrentShaderProgram->SetView(view);
	}
}

void Renderer::RefreshVertexBuffer(VertexBuffer* newVertexBuffer)
{
	if (m_CurrentVertexBuffer != newVertexBuffer)
	{
		m_CurrentVertexBuffer = newVertexBuffer;
		m_CurrentVertexBuffer->Use();
	}
}

// TODO: do more testing, and see if it can be cached ?
// If a texture is bind, and then the shader is swaped, is the texture still usable by the shader ? 
void Renderer::RefreshTextures(const std::vector<GLTexture*>& textures)
{
	for (std::size_t i = 0; i < textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]->GetTextureID());
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

unique_ptr_del<Renderable>
Renderer::CreateRenderable(std::shared_ptr<VertexBuffer> vertexBuffer, ShaderProgram* refShaderProgram, std::vector<GLTexture*> textures)
{
	auto renderable = new Renderable(std::move(vertexBuffer), refShaderProgram, std::move(textures));
	m_Renderables.push_back(renderable);
	
	auto destroyRenderable = [this](Renderable* renderable){
		m_Renderables.erase(std::remove(m_Renderables.begin(), m_Renderables.end(), renderable), m_Renderables.end());
		delete renderable;
	};

	return { renderable, destroyRenderable };
}

