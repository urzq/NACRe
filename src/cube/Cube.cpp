#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/ServiceLocator.h"

#include "Graphics/Renderer.h"
#include "Graphics/Renderable.h"

#include "Shader/ShaderProgram.h"

#include "Cube.h"

Cube::Cube(float initTime) :
	m_TotalTime(initTime)
{
	Renderer* renderer = ServiceLocator::GetInstance()->GetRenderer();
	m_Renderable = renderer->CreateRenderable("sphere", "Cube.vert", "Cube.frag");

	m_OffsetPosition = glm::vec3(0, 0, 0);
}

Cube::Cube(Cube&& other)
{
	this->m_Renderable = other.m_Renderable;
	other.m_Renderable = nullptr;

	this->m_StartPosition = other.m_StartPosition;
	this->m_OffsetPosition = other.m_OffsetPosition;

	this->m_TotalTime = other.m_TotalTime;
}

Cube::~Cube()
{
	Renderer* renderer = ServiceLocator::GetInstance()->GetRenderer();
	renderer->DestroyRenderable(m_Renderable);
}

void Cube::SetStartPosition(const glm::vec3& startPosition)
{
	m_StartPosition = startPosition;
}

void Cube::SetColor(const glm::vec3& color)
{
	m_Renderable->SetColor(color);
}

void Cube::Update(float dT)
{
	m_TotalTime += dT;
	m_OffsetPosition.z = sin(m_TotalTime);

	m_Renderable->GetTransform().SetPosition(m_StartPosition + m_OffsetPosition);
}

