#include <iostream>
#include <assert.h>

#include <ImGUiImpl/imgui_impl_glfw_gl3.h>

#include "Core/ServiceLocator.h"
#include "Graphics/Renderer.h"

#include "InputManager.h"

static KeyState s_KeyStates[GLFW_KEY_LAST + 1];

void InputManager::Init()
{
	GLFWwindow* window = ServiceLocator::Get<Renderer>()->GetGLFWwindow();
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, KeyCallback);
}

void InputManager::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	auto inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
	inputManager->KeyCallback(key, scancode, action, mods);

	// Imgui Needs to know which keys are pressed are released, like the ALT key.
	ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}

void InputManager::KeyCallback(int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_RELEASE)
	{
		std::lock_guard<std::mutex> lock(m_queuedEventsMutex);

		GLFWKeyEvent keyEvent;
		keyEvent.key = key;
		keyEvent.scancode = scancode;
		keyEvent.state = action == GLFW_PRESS ? KeyState::PRESSED : KeyState::RELEASED;
		keyEvent.mods = mods;

		m_queuedEvents.push(keyEvent);
	}
}

void InputManager::Update()
{
	for (KeyState& keyState : s_KeyStates)
	{
		if (keyState == KeyState::PRESSED)
		{
			keyState = KeyState::HELD_DOWN;
		}
		else if (keyState == KeyState::RELEASED)
		{
			keyState = KeyState::UP;
		}
	}

	std::lock_guard<std::mutex> lock(m_queuedEventsMutex);

	while (!m_queuedEvents.empty())
	{
		GLFWKeyEvent keyEvent = m_queuedEvents.front();
		s_KeyStates[keyEvent.key] = keyEvent.state;
		m_queuedEvents.pop();
	}
}

bool InputManager::IsKeyPressed(int glfw_key) const
{
	return s_KeyStates[glfw_key] == KeyState::PRESSED;
}

bool InputManager::IsKeyDown(int glfw_key) const
{
	auto keyState = s_KeyStates[glfw_key];
	return keyState == KeyState::PRESSED || keyState == KeyState::HELD_DOWN;
}

bool InputManager::IsKeyReleased(int glfw_key) const
{
	return s_KeyStates[glfw_key] == KeyState::UP;
}

bool InputManager::IsKeyUp(int glfw_key) const
{
	auto keyState = s_KeyStates[glfw_key];
	return keyState == KeyState::RELEASED || keyState == KeyState::UP;
}