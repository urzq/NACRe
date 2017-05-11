#include <vector>

#include "Graphics/Renderer.h"
#include "Graphics/Light.h"
#include "Graphics/Camera.h"

#include "Shader/ShaderProgram.h"

#include "Core/Clock.h"
#include "Core/Color.h"
#include "Core/ServiceLocator.h"

#include "Scene/SceneNode.h"
#include "Scene/WhiteCube.h"

/* TODO:
	PUSHER !
	Trouver un chouette nom
	Transformer cette liste en anglais.
	Passer à travers les différents TODO
	Renommer les shaders avec de meillers noms.
	Est-ce que le vertex buffer manager & le shader manager doivent être accédés comme ca ?
	Templater le ServiceLocator.
	Créer une scène cool.
	Mettre en place un système de GameObject (héritage)
	Essayer de mettre en place un nombre de light dynamique (multipass)
	S'essayer aux textures.
	Mettre en place un système de matérial.
	Structures de données custom ? Nottament le hash string.
	ImGUI !!!
	Quoi faire comme démo ? Mini gameplay ?
	La lightsur les sphere bug.
	Test avec terrain
	Skybox at some point.
	Projet organisé en lib -> lib moteur & lib jeu.

*/

struct NodeDescriptor
{
	const char* VertexBufferName;
	glm::vec3 Position;
	Color Color;
};

std::vector<SceneNode> GetSceneNodes()
{
	NodeDescriptor SceneDescriptor[] =
	{
		{"cube",		{ 0,	0,	   0.0},  0xF6C4FF},
		{"sphere",		{ 0,	0.934, 0.0 }, 0xC4DCFF},
		{"dodecahedron",{ 1,	0.0,   3.5 }, 0x81FF68},
		{"tetrahedron",	{-2.25, 0.9,   -.5 }, 0xBAFFC3},
		{"octahedron",	{-1,	0.8,   3.5 }, 0xE6CEFF},
		{"icosahedron", { 1,	0.0,   0.5 }, 0xFFA100}
	};

	std::vector<SceneNode> nodes;
	
	for (auto& nodeDescriptor : SceneDescriptor)
	{
		SceneNode node(nodeDescriptor.VertexBufferName);
		node.SetPosition(nodeDescriptor.Position);
		node.SetColor(nodeDescriptor.Color);

		nodes.push_back( std::move(node) );
	}

	return nodes;
}

//void SetCubeColors(std::vector<Cube>& cubes)
//{
//	Color colors[] = 
//	{
//		0xF6C4FF, 0xC4DCFF, 0x81FF68, 0xBAFFC3, 0xE6CEFF,
//		0xFFA100, 0xFF2D1E, 0xFFA928, 0xFFC249, 0xFFFFA3,
//		0xAAFFBE, 0xFF7298, 0x30FF5D, 0xFF7298, 0xFFBD5B,
//		0xFFE100, 0xFF7F00, 0xFFFB8E, 0xAFFFF4, 0x81FF68,
//		0xFF0C00, 0xC6FFD2, 0xFFBD23, 0xFF431E, 0x00FFB6 
//	};
//
//	for(size_t i = 0; i<cubes.size(); ++i)
//	{ 
//		cubes[i].SetColor(colors[i]);
//	}
//}

int main()
{
	ServiceLocator::Init();

	Renderer* renderer = ServiceLocator::GetInstance()->GetRenderer();
	renderer->Init("Cubes", glm::uvec2(1024, 768));
	renderer->SetClearColor(Color(0x84A5FF));

	Clock clock;
	Camera camera;

	std::vector<SceneNode> sceneNodes = GetSceneNodes();

	WhiteCube cubeLight;

	while (renderer->IsRunning())
	{
		clock.Update();

		camera.Update(clock.dT());

		cubeLight.Update(clock.dT());
		renderer->GetLight().SetParameters(cubeLight.GetPosition(), camera.GetPosition(), cubeLight.GetLightColor());

		for (auto& node : sceneNodes)
		{
			node.Update(clock.dT());
		}

		renderer->Render(camera.GetProjectionMatrix(), camera.GetViewMatrix());
	}

	return EXIT_SUCCESS;
}
