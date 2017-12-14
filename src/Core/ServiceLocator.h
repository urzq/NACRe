#ifndef __SERVICE_LOCATOR_H__
#define __SERVICE_LOCATOR_H__

class Renderer;
class VertexBufferManager;
class ShaderProgramManager;
class InputManager;
class TextureManager;

class ServiceLocator
{
public:
	static void Init();
	static void Shutdown();

	template<class T> static T* Get();

private:
	static Renderer* s_Renderer;
	static VertexBufferManager* s_VertexBuferManager;
	static ShaderProgramManager* s_ShaderProgramManager;
	static TextureManager* s_TextureManager;
	static InputManager* s_InputManager;
};

#endif