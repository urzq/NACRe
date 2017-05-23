#ifndef __INPUT_MANAGER_H__
#define __INPUT_MANAGER_H__

#include <thread>
#include <mutex>
#include <queue>

struct GLFWwindow;

enum class KeyState
{
	UP,
	PRESSED,
	HELD_DOWN,
	RELEASED,
};

struct GLFWKeyEvent
{
	int key;
	int scancode;
	KeyState state;
	int mods;
};

class InputManager
{
public:
	void Init();
	void Update();

	// glfw_key : GLFW_KEY_A, GLFW_KEY_B etc...
	// glfw_key is a physical key, based on its position on a US keyboard.
	bool IsKeyPressed(int glfw_key) const;
	bool IsKeyDown(int glfw_key) const;
	bool IsKeyReleased(int glfw_key) const;
	bool IsKeyUp(int glfw_key) const;

private:

	// window	The window that received the event.
	// key		The keyboard key that was pressed or released.
	// scancode	The system - specific scancode of the key.
	// action	GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
	// mods		Bit field describing which modifier keys were held down.
	static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
	void InputManager::KeyCallback(int key, int scancode, int action, int mods);

private:
	std::queue<GLFWKeyEvent> m_queuedEvents;
	std::mutex m_queuedEventsMutex;

};
#endif