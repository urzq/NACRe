#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/ServiceLocator.h"

#include "Graphics/Renderer.h"
#include "Graphics/Renderable.h"

#include "Shader/ShaderProgramManager.h"
#include "Shader/ShaderProgram.h"

#include "VertexBuffer/VertexBuffer.h"
#include "VertexBuffer/VertexBufferData.h"

#include "Texture/TextureManager.h"
#include "Texture/GLTexture.h"

#include "MinecraftCube.h"

MinecraftCube::MinecraftCube()
{
	auto vertexBuffer = CreateVertexBuffer();

	auto shaderProgramManager = ServiceLocator::Get<ShaderProgramManager>();
	ShaderProgram* shaderProgram = shaderProgramManager->GetShaderProgram("BasicDiffuse.vert", "BasicDiffuse.frag");

	auto textureManager = ServiceLocator::Get<TextureManager>();
	auto texture = textureManager->GetTexture("data/Texture/MinecraftCube.png");

	auto renderer = ServiceLocator::Get<Renderer>();
	m_Renderable = renderer->CreateRenderable(std::move(vertexBuffer), shaderProgram, {texture});

	m_Renderable->GetTransform().SetScale({ 1.0f, 1.0f, 1.0f });
}

std::shared_ptr<VertexBuffer> MinecraftCube::CreateVertexBuffer()
{
	float vertices[] = { -1, 1, 0, 1, 1, 0, 1, -1, 0, -1, 1, 0, 1, -1, 0, -1, -1, 0 };
	float uv[] = { 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0};

	VertexBufferData vbd;
	vbd.NbVertices = 6;
	vbd.Vertices = vertices;
	vbd.Normals = nullptr;
	vbd.UV = uv;

	return std::make_shared<VertexBuffer>(vbd);
}

void MinecraftCube::SetPosition(const glm::vec3& position)
{
	m_Renderable->GetTransform().SetPosition(position);
}

glm::vec3 MinecraftCube::GetPosition()
{
	return m_Renderable->GetTransform().GetPosition();
}

void MinecraftCube::Update(float dT)
{
}