#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/ServiceLocator.h"

#include "Graphics/Renderer.h"
#include "Graphics/Renderable.h"

#include "Shader/ShaderProgram.h"

#include "WhiteCube.h"

WhiteCube::WhiteCube():
	m_TotalTime(0.0f)
{
	Renderer* renderer = ServiceLocator::GetInstance()->GetRenderer();
	m_Renderable = renderer->CreateRenderable("cube", "FlatColor.vert", "FlatColor.frag");

	m_Renderable->GetTransform().SetScale({ 0.2f, 0.2f, 0.2f });
}

WhiteCube::~WhiteCube()
{
	Renderer* renderer = ServiceLocator::GetInstance()->GetRenderer();
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

