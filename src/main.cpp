#include <vector>

#include "ServiceLocator.h"
#include "Renderer.h"
#include "shader/ShaderProgram.h"
#include "Camera.h"

#include "cube/Cube.h"

#include "Light.h"
#include "Clock.h"
#include "core/Color.h"

/* TODO:
	PUSHER !
	---> Cleaner <---
	Trouver un chouette nom
	Transformer cette liste en anglais.
	Passer à travers les différents TODO
	Afficher la light avec un cube et le shader blanc.
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

std::vector<Cube> GetCubes()
{
	std::vector<Cube> cubes;
	int size = 1;

	for (int x = -size*2; x <= size*2; x = x + 2)
	{
		for (int y = -size*2; y <= size*2; y = y + 2)
		{
			float dist = glm::distance(glm::vec2(x, y), glm::vec2(0, 0));
			Cube cube(dist);
			cube.SetStartPosition(glm::vec3(x, y, 0));
			cubes.push_back(std::move(cube));
		}
	}

	return cubes;
}

void SetCubeColors(std::vector<Cube>& cubes)
{
	Color colors[] = 
	{
		0xF6C4FF, 0xC4DCFF, 0x81FF68, 0xBAFFC3, 0xE6CEFF,
		0xFFA100, 0xFF2D1E, 0xFFA928, 0xFFC249, 0xFFFFA3,
		0xAAFFBE, 0xFF7298, 0x30FF5D, 0xFF7298, 0xFFBD5B,
		0xFFE100, 0xFF7F00, 0xFFFB8E, 0xAFFFF4, 0x81FF68,
		0xFF0C00, 0xC6FFD2, 0xFFBD23, 0xFF431E, 0x00FFB6 
	};

	for(size_t i = 0; i<cubes.size(); ++i)
	{ 
		cubes[i].SetColor(colors[i]);
	}
}

int main()
{
	ServiceLocator::Init();

	Renderer* renderer = ServiceLocator::GetInstance()->GetRenderer();
	renderer->Init("Cubes", glm::uvec2(1024, 768));
	renderer->SetClearColor(Color(0x84A5FF));

	Clock clock;
	Camera camera;

	std::vector<Cube> cubes = GetCubes();
	SetCubeColors(cubes);

	while (renderer->IsRunning())
	{
		clock.Update();

		camera.Update(clock.dT());

		// TODO : create a gameobject that moves the light.
		renderer->GetLight().SetParameters(glm::vec3(-5,-5,-5), camera.GetPosition(), glm::vec3(1));

		for (auto& cube : cubes)
		{
			cube.Update(clock.dT());
		}

		// TODO: maybe Renderer with a pointer to camera? 
		renderer->Render(camera.GetProjectionMatrix(), camera.GetViewMatrix());
	}

	return EXIT_SUCCESS;
}
