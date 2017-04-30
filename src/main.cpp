#include <vector>

#include "Renderer.h"
#include "shader/Program.h"
#include "Camera.h"

#include "mesh/MeshCube.h"
#include "mesh/MeshLight.h"

#include "Cube.h"
#include "Light.h"

#include "Clock.h"

std::vector<Cube> GetCubes(const Program& program)
{
	std::vector<Cube> cubes;
	int size = 2;

	for (int x = -size; x <= size; ++x)
	{
		for (int y = -size; y <= size; ++y)
		{
			float dist = glm::distance(glm::vec2(x, y), glm::vec2(0, 0));
			Cube cube(program, dist);
			cube.SetPosition(glm::vec3(x, y, 0));
			cubes.push_back(cube);
		}
	}

	return cubes;
}

int main()
{
	Clock clock;
	Renderer renderer("Cubes", glm::uvec2(1024, 768));
	
	MeshCube meshCube;
	MeshLight meshLight;

	Program programCube("Cube.vert", "Cube.frag");
	Program programLight("Light.vert", "Light.frag");

	// Utiliser les 3 matrices séparées comme pour les cubes.
	GLuint lightMatrixID = programLight.GetUniformLocation("MVP");

	Camera camera( renderer.GetGLFWwindow() );

	std::vector<Cube> cubes = GetCubes(programCube);
	Light light(lightMatrixID);

	while (renderer.IsRunning())
	{
		clock.Update();

		camera.Update(clock.dT());

		glm::mat4 projection = camera.GetProjectionMatrix();
		glm::mat4 view = camera.GetViewMatrix();
		
		meshCube.Use();
		programCube.Use();

		light.Update(clock.dT());
		glm::vec3 lightPos = light.GetPosition();

		for (auto& cube : cubes)
		{
			cube.Update(clock.dT());
			cube.Render(projection, view, lightPos);
		}

		meshLight.Use();
		programLight.Use();
		light.Render(projection, view);

		renderer.Render();

	}

	return EXIT_SUCCESS;
}
