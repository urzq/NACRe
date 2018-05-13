#include <random>

#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp> // glm::to_string

#include <imgui/imgui.h>

#include "Core/ServiceLocator.h"

#include "Graphics/Renderer.h"
#include "Graphics/Renderable.h"

#include "Shader/ShaderProgramManager.h"
#include "Shader/ShaderProgram.h"

#include "VertexBuffer/VertexBufferManager.h"
#include "VertexBuffer/VertexBuffer.h"

#include "SceneNode.h"

SceneNode::SceneNode(const char* nodeName, const char* vertexBuferName):
	m_NodeName(nodeName)
{	
	auto vertexBufferManager = ServiceLocator::Get<VertexBufferManager>();
	auto vertexBuffer = vertexBufferManager->GetVertexBuffer(vertexBuferName);

	auto shaderProgramManager = ServiceLocator::Get<ShaderProgramManager>();
	auto shaderProgram = shaderProgramManager->GetShaderProgram("data/shader/BasicPhong.vert", "data/shader/BasicPhong.frag");

	auto renderer = ServiceLocator::Get<Renderer>();
	m_Renderable = renderer->CreateRenderable(vertexBuffer, shaderProgram);

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist_time(-10.0, 10.0);
	std::uniform_real_distribution<float> dist_oscillation(0.01f, 0.1f);

	m_totalTime = dist_time(mt);
	m_oscillationDistance = dist_oscillation(mt);
}

void SceneNode::SetPosition(const glm::vec3& position)
{
	m_originalPosition = position;
}

void SceneNode::SetScale(const glm::vec3& scale)
{
	m_Renderable->GetTransform().Scale = scale;
}

void SceneNode::SetColor(const glm::vec3& color)
{
	m_Renderable->Color = color;
}

void SceneNode::Update(float dT)
{
	m_totalTime += dT / 4.0f;
	glm::vec3 pos = m_originalPosition;
	pos.y += sin(m_totalTime) * m_oscillationDistance;

	m_Renderable->GetTransform().Position = pos;

	ImGui::Begin(m_NodeName);

	Transform& t = m_Renderable->GetTransform();

	ImGui::DragFloat3("position", glm::value_ptr(t.Position));
	ImGui::DragFloat3("scale", glm::value_ptr(t.Scale));
	ImGui::DragFloat3("euler", glm::value_ptr(t.Euler));
	ImGui::ColorEdit3("color", glm::value_ptr(m_Renderable->Color));

	ImGui::End();
}

std::ostream& operator<<(std::ostream &os, const SceneNode& node) 
{
	Transform& t = node.m_Renderable->GetTransform();

	return os << node.m_NodeName << ": " 
		<< glm::to_string(t.Position) << " " 
		<< glm::to_string(t.Scale) << " "
		<< glm::to_string(t.Euler) << "\n";
}