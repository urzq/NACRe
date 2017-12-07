#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>

#include "Core/ServiceLocator.h"

#include "Graphics/Renderer.h"
#include "Graphics/Renderable.h"

#include "Shader/ShaderProgramManager.h"
#include "Shader/ShaderProgram.h"

#include "VertexBuffer/VertexBufferManager.h"
#include "VertexBuffer/VertexBuffer.h"

#include "SceneNode.h"

SceneNode::SceneNode(const char* vertexBuferName):
	m_VertexBufferName(vertexBuferName)
{	
	auto vertexBufferManager = ServiceLocator::GetInstance()->GetVertexBufferManager();
	auto vertexBuffer = vertexBufferManager->GetVertexBuffer(vertexBuferName);

	auto shaderProgramManager = ServiceLocator::GetInstance()->GetShaderProgramManager();
	ShaderProgram* shaderProgram = shaderProgramManager->GetShaderProgram("BasicPhong.vert", "BasicPhong.frag");

	auto renderer = ServiceLocator::GetInstance()->GetRenderer();
	m_Renderable = renderer->CreateRenderable(vertexBuffer, shaderProgram);
}

SceneNode::~SceneNode()
{
	Renderer* renderer = ServiceLocator::GetInstance()->GetRenderer();
	renderer->DestroyRenderable(m_Renderable);
}

void SceneNode::SetPosition(const glm::vec3& position)
{
	glm_pos = position;
	m_Renderable->GetTransform().SetPosition(position);
}

void SceneNode::SetScale(const glm::vec3& scale)
{
	glm_scale = scale;
	m_Renderable->GetTransform().SetScale(scale);
}

void SceneNode::SetColor(const glm::vec3& color)
{
	glm_color = color;
	m_Renderable->SetColor(color);
}

void SceneNode::Update(float dT)
{
	ImGui::Begin(m_VertexBufferName);

	if (ImGui::DragFloat3("position", glm::value_ptr(glm_pos)))
	{
		m_Renderable->GetTransform().SetPosition(glm_pos);
	}

	if (ImGui::DragFloat3("scale", glm::value_ptr(glm_scale)))
	{
		m_Renderable->GetTransform().SetScale(glm_scale);
	}

	if (ImGui::DragFloat3("euler", glm::value_ptr(glm_euler)))
	{
		m_Renderable->GetTransform().SetEuler(glm_euler);
	}
	
	ImGui::ColorEditMode(ImGuiColorEditMode_RGB);

	if (ImGui::ColorEdit3("color 1", glm::value_ptr(glm_color)))
	{
		m_Renderable->SetColor(glm_color);
	}

	ImGui::End();
}

