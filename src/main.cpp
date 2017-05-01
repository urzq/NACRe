#include <vector>

#include "Renderer.h"
#include "shader/Program.h"
#include "Camera.h"

#include "mesh/MeshCube.h"
#include "mesh/MeshLight.h"

#include "cube/Cube.h"
#include "cube/CubePreRender.h"

#include "Light.h"
#include "Clock.h"
#include "core/Color.h"


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
	Clock clock;
	Renderer renderer("Cubes", glm::uvec2(1024, 768));
	renderer.SetClearColor( Color(0x84A5FF) );

	MeshCube meshCube;
	MeshLight meshLight;

	Program programCube("Cube.vert", "Cube.frag");
	Program programLight("Light.vert", "Light.frag");

	GLuint lightMatrixID = programLight.GetUniformLocation("MVP");

	Camera camera( renderer.GetGLFWwindow() );

	CubePreRender cubePreRender(programCube);
	std::vector<Cube> cubes = GetCubes(programCube);
	SetCubeColors(cubes);

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
		cubePreRender.PreRender(light.GetPosition(), camera.GetPosition(), glm::vec3(1));

		for (auto& cube : cubes)
		{
			cube.Update(clock.dT());
			cube.Render(projection, view);
		}

		meshLight.Use();
		programLight.Use();
		light.Render(projection, view);

		renderer.Render();
	}

	return EXIT_SUCCESS;
}
