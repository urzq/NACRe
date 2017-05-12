#include <vector>

#include "Graphics/Renderer.h"
#include "Graphics/Light.h"
#include "Graphics/Camera.h"

#include "Shader/ShaderProgram.h"

#include "Core/Clock.h"
#include "Core/Color.h"
#include "Core/ServiceLocator.h"

#include "Scene/Scene.h"
#include "Scene/WhiteCube.h"

/* TODO LIST:
	Find a cool name.
	Implement an Input manager (key, mouse).
	Handle the activation / deactivation of imgui in a better way.
	LUA ?
	Handle all the TODO left in the code.
	Template the ServiceLocator : ServiceLocator.Get<Renderer>();
	Create a templated ResourceCache (cf. Urho3D)
	Improve the Node system. 
	Shader hot reload :)
	Implement more shaders -> Wireframe effect.
	Gameobject Picker + manipulation (like Unity scene with arrows).
	Try to understand shadows.
	Dynamic number of lights.
	Textured cube !
	Material system.
	Get rid of the STL (?)  At least develop a hash string.
	Terrain system.
	Skybox
	Have a clean separation between the engine and the game (lib).
*/

int main()
{
	ServiceLocator::Init();

	Renderer* renderer = ServiceLocator::GetInstance()->GetRenderer();
	renderer->Init("Cubes", glm::uvec2(1024, 768));
	renderer->SetClearColor(Color(0x84A5FF));

	Clock clock;
	Camera camera;
	Scene scene;

	WhiteCube cubeLight;

	while (renderer->IsRunning())
	{
		clock.Update();

		renderer->NewFrame();

		if (! renderer->IsImGuiActivated())
		{
			camera.Update(clock.dT());
		}

		scene.Update(clock.dT());

		cubeLight.Update(clock.dT());
		renderer->GetLight().SetParameters(cubeLight.GetPosition(), camera.GetPosition(), cubeLight.GetLightColor());

		renderer->Render(camera.GetProjectionMatrix(), camera.GetViewMatrix());
	}

	return EXIT_SUCCESS;
}
