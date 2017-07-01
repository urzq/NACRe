#include "Core/Color.h"
#include "SceneNode.h"
#include "Scene.h"

struct NodeDescriptor
{
	const char* VertexBufferName;
	glm::vec3 Position;
	glm::vec3 Scale;
	Color Color;
};

Scene::Scene()
{
	NodeDescriptor SceneDescriptor[] =
	{
		{ "cube",		  { 1.38, 0.75,-1.13 }, { 1.5, 1.5, 1.5}, 0xF6C4FF },
		{ "sphere",	      { 0.00, 0.93, 0.00 }, { 1.0, 1.0, 1.0}, 0xC4DCFF },
		{ "dodecahedron", { 0.98, 0.02, 3.50 }, { 0.7, 0.7, 0.7}, 0x81FF68 },
		{ "tetrahedron",  {-0.98, 1.42,-0.50 }, { 1.3, 1.3, 1.3}, 0xBAFFC3 },
		{ "octahedron",   {-1.25, 0.79, 1.79 }, { 1.0, 1.0, 1.0}, 0xE6CEFF },
		{ "icosahedron",  { 2.42, 0.00, 0.50 }, { 1.0, 1.0, 1.0}, 0xFFA100 }
	};

	for (auto& nodeDescriptor : SceneDescriptor)
	{
		auto node = std::make_unique<SceneNode>(nodeDescriptor.VertexBufferName);
		node->SetPosition(nodeDescriptor.Position);
		node->SetScale(nodeDescriptor.Scale);
		node->SetColor(nodeDescriptor.Color);

		m_SceneNodes.push_back(std::move(node));
	}
}

void Scene::Update(float dT, glm::vec3 cameraPosition)
{
	for (auto& node : m_SceneNodes)
	{
		node->Update(dT);
	}

	m_WhiteCube.Update(dT, cameraPosition);

}