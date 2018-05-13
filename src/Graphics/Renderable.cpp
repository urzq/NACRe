#include "Core/ServiceLocator.h"
#include "VertexBuffer/VertexBufferManager.h"
#include "Shader/ShaderProgramManager.h"
#include "Texture/GLTexture.h"

#include "Renderable.h"

Renderable::Renderable(std::shared_ptr<VertexBuffer> vertexBuffer, ShaderProgram* refShaderProgram, std::vector<GLTexture*> textures):
	m_VertexBuffer(std::move(vertexBuffer)),
	m_RefShaderProgram(refShaderProgram),
	m_Textures(std::move(textures)),
	Color(1,1,1)
{
}

VertexBuffer* Renderable::GetVertexBuffer()
{
	return m_VertexBuffer.get();
}

std::vector<GLTexture*>& Renderable::GetTextures()
{
	return m_Textures;
}

ShaderProgram* Renderable::GetShaderProgram()
{
	return m_RefShaderProgram;
}

Transform& Renderable::GetTransform()
{
	return m_Transform;
}