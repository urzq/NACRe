#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/ServiceLocator.h"

#include "Graphics/Renderer.h"
#include "Graphics/Renderable.h"

#include "Shader/ShaderProgramManager.h"
#include "Shader/ShaderProgram.h"

#include "VertexBuffer/VertexBufferManager.h"
#include "VertexBuffer/VertexBuffer.h"

#include "SceneNode.h"

SceneNode::SceneNode(const char* vertexBuferName)
{	
	auto vertexBufferManager = ServiceLocator::GetInstance()->GetVertexBuferManager();
	VertexBuffer* vertexBuffer = vertexBufferManager->GetVertexBuffer(vertexBuferName);

	auto shaderProgramManager = ServiceLocator::GetInstance()->GetShaderProgramManager();
	ShaderProgram* shaderProgram = shaderProgramManager->GetShaderProgram("BasicPhong.vert", "BasicPhong.frag");

	auto renderer = ServiceLocator::GetInstance()->GetRenderer();
	m_Renderable = renderer->CreateRenderable(vertexBuffer, shaderProgram);
}

SceneNode::SceneNode(SceneNode&& other)
{
	this->m_Renderable = other.m_Renderable;
	other.m_Renderable = nullptr;
}

SceneNode::~SceneNode()
{
	Renderer* renderer = ServiceLocator::GetInstance()->GetRenderer();
	renderer->DestroyRenderable(m_Renderable);
}

void SceneNode::SetPosition(const glm::vec3& position)
{
	m_Renderable->GetTransform().SetPosition(position);
}

void SceneNode::SetColor(const glm::vec3& color)
{
	m_Renderable->SetColor(color);
}

void SceneNode::Update(float dT)
{
}

