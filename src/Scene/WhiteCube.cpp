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

#include "WhiteCube.h"

WhiteCube::WhiteCube():
	m_TotalTime(0.0f)
{
	auto vertexBufferManager = ServiceLocator::Get<VertexBufferManager>();
	auto vertexBuffer = vertexBufferManager->GetVertexBuffer("cube");

	auto shaderProgramManager = ServiceLocator::Get<ShaderProgramManager>();
	ShaderProgram* shaderProgram = shaderProgramManager->GetShaderProgram("FlatColor.vert", "FlatColor.frag");

	auto renderer = ServiceLocator::Get<Renderer>();
	m_Renderable = renderer->CreateRenderable(std::move(vertexBuffer), shaderProgram);

	m_Renderable->GetTransform().SetScale({ 0.2f, 0.2f, 0.2f });
}

WhiteCube::~WhiteCube()
{
	Renderer* renderer = ServiceLocator::Get<Renderer>();
	renderer->DestroyRenderable(m_Renderable);
}

void WhiteCube::SetPosition(const glm::vec3& position)
{
	m_Renderable->GetTransform().SetPosition(position);
}

glm::vec3 WhiteCube::GetPosition()
{
	return m_Renderable->GetTransform().GetPosition();
}

glm::vec3 WhiteCube::GetLightColor()
{
	return m_Renderable->GetColor();
}

void WhiteCube::Update(float dT)
{
	m_TotalTime += dT;

	const float radius = 3.0f;

	float x = cos(m_TotalTime) * radius;
	float y = sin(m_TotalTime) * radius;
	float z = 5.0f;

	m_Renderable->GetTransform().SetPosition({ x, y, z });
}

