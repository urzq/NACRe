#include "Core/ServiceLocator.h"
#include "VertexBuffer/VertexBufferManager.h"
#include "Shader/ShaderProgramManager.h"

#include "Renderable.h"

Renderable::Renderable(VertexBuffer* refVertexBuffer, ShaderProgram* refShaderProgram):
	m_RefVertexBuffer(refVertexBuffer),
	m_RefShaderProgram(refShaderProgram),
	m_ObjectColor(1,1,1)
{
}

Renderable::~Renderable()
{
}

VertexBuffer* Renderable::GetVertexBuffer()
{
	return m_RefVertexBuffer;
}

ShaderProgram* Renderable::GetShaderProgram()
{
	return m_RefShaderProgram;
}

Transform& Renderable::GetTransform()
{
	return m_Transform;
}

glm::vec3 Renderable::GetColor() const
{
	return m_ObjectColor;
}

void Renderable::SetColor(const glm::vec3& color)
{
	m_ObjectColor = color;
}