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
	Remove par_shape, and load basic models from obj (cube, sphere etc.)
	Smarted handling of textures in renderer.cpp
	Indexes.
	Easier binding between vertexbuffer and shader (based on name ?)
	Model loading
	Material system.
	Textured cube !
	Handle all the TODO left in the code.
	Less duplication between minecraftCube, WhiteCube and sceneNode.
	Template the ServiceLocator : ServiceLocator.Get<Renderer>();
	Create a templated ResourceCache (cf. Urho3D)
	Shader hot reload :)
	Implement more shaders -> Wireframe effect.
	Try to understand shadows.
	Dynamic number of lights.
	Have a clean separation between the engine and the game (lib).
*/

int main()
{
	ServiceLocator::Init();

	auto renderer = ServiceLocator::Get<Renderer>();
	renderer->Init("NACRe", glm::uvec2(1024, 768));
	renderer->SetClearColor(Color(0x84A5FF));

	auto inputManager = ServiceLocator::Get<InputManager>();
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
