#include <vector>
#include <iostream>

#include "Graphics/Renderer.h"
#include "Graphics/Light.h"
#include "Graphics/Camera.h"

#include "Input/InputManager.h"
#include "Shader/ShaderProgram.h"

#include "Core/Clock.h"
#include "Core/Color.h"
#include "Core/ServiceLocator.h"

#include "Scene/Scene.h"

/* TODO LIST:
	Textured cube !
	Find a cool name.
	Handle all the TODO left in the code.
	Skybox
	Template the ServiceLocator : ServiceLocator.Get<Renderer>();
	Create a templated ResourceCache (cf. Urho3D)
	Improve the Node system. 
	Shader hot reload :)
	Implement more shaders -> Wireframe effect.
	Gameobject Picker + manipulation (like Unity scene with arrows).
	Try to understand shadows.
	Dynamic number of lights.
	Material system.
	Get rid of the STL (?)  At least develop a hash string.
	Terrain system.
	Have a clean separation between the engine and the game (lib).
	Render to texture, multipass, bloom.

*/

int main()
{
	ServiceLocator::Init();

	Renderer* renderer = ServiceLocator::GetInstance()->GetRenderer();
	renderer->Init("Cubes", glm::uvec2(1024, 768));
	renderer->SetClearColor(Color(0x84A5FF));

	InputManager* inputManager = ServiceLocator::GetInstance()->GetInputManager();
	inputManager->Init();

	Clock clock;
	Camera camera;
	Scene scene;


	while (renderer->IsRunning() && ! inputManager->IsKeyDown(GLFW_KEY_ESCAPE) )
	{
		clock.Update();

		renderer->NewFrame();
		inputManager->Update();

		if ( inputManager->IsKeyPressed(GLFW_KEY_GRAVE_ACCENT) )
		{
			renderer->ToggleImGuiEnabled();
			camera.SetEnabled( ! renderer->IsImGuiEnabled());
		}

		camera.Update(clock.dT());
		scene.Update(clock.dT(), camera.GetPosition());

		renderer->Render(camera.GetProjectionMatrix(), camera.GetViewMatrix());
	}

	return EXIT_SUCCESS;
}
