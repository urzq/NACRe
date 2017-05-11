#include "ServiceLocator.h"
#include "mesh/VertexBufferManager.h"
#include "shader/ShaderProgramManager.h"

#include "Renderable.h"

Renderable::Renderable(const std::string& meshName, const std::string& vertexFilePath, const std::string& fragmentFilePath)
{
	auto serviceLocator = ServiceLocator::GetInstance();
	
	auto vertexBufferMgr = serviceLocator->GetVertexBuferManager();
	m_VertexBuffer = vertexBufferMgr->GetVertexBuffer(meshName);

	auto shaderProgramMgr = serviceLocator->GetShaderProgramManager();
	m_ShaderProgram = shaderProgramMgr->GetShaderProgram(vertexFilePath, fragmentFilePath);

	m_ObjectColor = glm::vec3(1, 1, 1);
}

Renderable::~Renderable()
{
	// TODO: Handle the deallocation.
}

VertexBuffer* Renderable::GetVertexBuffer()
{
	return m_VertexBuffer;
}

ShaderProgram* Renderable::GetShaderProgram()
{
	return m_ShaderProgram;
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