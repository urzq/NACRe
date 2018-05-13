#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>

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
	auto shaderProgram = shaderProgramManager->GetShaderProgram("data/shader/BasicDiffuse.vert", "data/shader/BasicDiffuse.frag");

	auto textureManager = ServiceLocator::Get<TextureManager>();
	auto texture = textureManager->GetTexture("data/Texture/MinecraftCube.png");

	auto renderer = ServiceLocator::Get<Renderer>();
	m_Renderable = renderer->CreateRenderable(std::move(vertexBuffer), shaderProgram, { texture });

	Transform& t = m_Renderable->GetTransform();
	t.Position = { -3.20, 0.72, 0.57 };
	t.Scale = { 0.3f, 0.3f, 0.3f };
	t.Euler = { -0.020f, -0.160, -0.450 };
}

std::shared_ptr<VertexBuffer> MinecraftCube::CreateVertexBuffer()
{
	const int nbVertices = 36;
	float vertices[nbVertices * 3] = {
		-1, 1, 1,   1,-1, 1,   1, 1, 1,   // front
		-1, 1, 1,  -1,-1, 1,   1,-1, 1,
		-1, 1, 1,  -1, 1,-1,  -1,-1,-1,   // left
		-1, 1, 1,  -1,-1,-1,  -1,-1, 1,
		 1, 1, 1,   1,-1,-1,   1, 1,-1,   // right
		 1, 1, 1,   1,-1, 1,   1,-1,-1,
		-1, 1,-1,   1, 1,-1,   1,-1,-1,   // back
		-1, 1,-1,   1,-1,-1,  -1,-1,-1,
		-1, 1, 1,   1, 1, 1,   1, 1,-1,   // top
		-1, 1, 1,   1, 1,-1,  -1, 1,-1,
		-1,-1, 1,   1,-1,-1,   1,-1, 1,   // bottom
		-1,-1, 1,  -1,-1,-1,   1,-1,-1,
	};

	float uv[nbVertices * 2] = {
		0.0, 1.0,  0.5, 0.5,  0.5, 1.0,   // front
		0.0, 1.0,  0.0, 0.5,  0.5, 0.5,
		0.0, 1.0,  0.5, 1.0,  0.5, 0.5,   // left
		0.0, 1.0,  0.5, 0.5,  0.0, 0.5,
		0.0, 1.0,  0.5, 0.5,  0.5, 1.0,   // right
		0.0, 1.0,  0.0, 0.5,  0.5, 0.5,
		0.0, 1.0,  0.5, 1.0,  0.5, 0.5,   // back
		0.0, 1.0,  0.5, 0.5,  0.0, 0.5,
		0.0, 0.5,  0.5, 0.5,  0.5, 0.0,   // top
		0.0, 0.5,  0.5, 0.0,  0.0, 0.0,
		0.5, 1.0,  1.0, 0.5,  1.0, 1.0,   // bottom
		0.5, 1.0,  0.5, 0.5,  1.0, 0.5,
	};

	VertexBufferData vbd;
	vbd.NbVertices = nbVertices;
	vbd.Vertices = vertices;
	vbd.Normals = nullptr;
	vbd.UV = uv;

	return std::make_shared<VertexBuffer>(vbd);
}

void MinecraftCube::SetPosition(const glm::vec3& position)
{
	m_Renderable->GetTransform().Position = position;
}

glm::vec3 MinecraftCube::GetPosition()
{
	return m_Renderable->GetTransform().Position;
}

void MinecraftCube::Update(float dT)
{
	m_TotalTime += dT * 1.7;
	
	Transform& t = m_Renderable->GetTransform();
	t.Euler.y = m_TotalTime;

	ImGui::Begin("minecraft");

	ImGui::DragFloat3("position", glm::value_ptr(t.Position));
	ImGui::DragFloat3("scale", glm::value_ptr(t.Scale));
	ImGui::DragFloat3("euler", glm::value_ptr(t.Euler));

	ImGui::End();
}