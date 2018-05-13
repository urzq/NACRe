#include <iostream>
#include <imgui/imgui.h>

#include "Core/ServiceLocator.h"
#include "Core/Color.h"

#include "Graphics/Renderer.h"

#include "SceneNode.h"
#include "Scene.h"

struct NodeDescriptor
{
	const char* NodeName;
	glm::vec3 Position;
	glm::vec3 Scale;
	Color Color;
};

Scene::Scene()
{
	NodeDescriptor SceneDescriptor[] =
	{
		{ "sphere_1", {-0.24, 0.19,-0.58 }, { 1.5, 1.5, 1.5}, 0x479BFA },
		{ "sphere_2", { 0.69, 1.89,-0.11 }, { 0.5, 0.5, 0.5}, 0x479BFA },
		{ "sphere_3", { 1.94, 0.52, 2.89 }, { 0.2, 0.2, 0.2}, 0x7A80FE },
		{ "sphere_4", { 0.10, 2.48,-0.50 }, { 0.4, 0.4, 0.4}, 0xAE38C3 },
		{ "sphere_5", { 2.44, 0.03,-1.28 }, { 0.6, 0.6, 0.6}, 0xF3A600 },
		{ "sphere_6", {-2.41,-0.99,-0.41 }, { 0.4, 0.4, 0.4}, 0x479BFA }
	};

	for (auto& nodeDescriptor : SceneDescriptor)
	{
		auto node = std::make_unique<SceneNode>(nodeDescriptor.NodeName, "sphere");
		node->SetPosition(nodeDescriptor.Position);
		node->SetScale(nodeDescriptor.Scale);
		node->SetColor(nodeDescriptor.Color);

		m_SceneNodes.push_back(std::move(node));
	}
}

Scene::~Scene()
{
}

void Scene::Update(float dT, glm::vec3 cameraPosition)
{
	for (auto& node : m_SceneNodes)
	{
		node->Update(dT);
	}

	m_MinecraftCube.Update(dT);

	UpdateLight(dT, cameraPosition);
}

void Scene::UpdateLight(float dT, glm::vec3 cameraPosition)
{
	m_WhiteCube.Update(dT);

	auto renderer = ServiceLocator::Get<Renderer>();
	auto lightPos = m_WhiteCube.GetPosition();
	auto lightColor = m_WhiteCube.GetLightColor();

	renderer->GetLight().SetParameters(lightPos, cameraPosition, lightColor);
}