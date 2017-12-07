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

	static ServiceLocator* GetInstance();

	Renderer* GetRenderer();
	VertexBufferManager* GetVertexBufferManager();
	ShaderProgramManager* GetShaderProgramManager();
	TextureManager* GetTextureManager();
	InputManager* GetInputManager();

private:
	ServiceLocator();
	~ServiceLocator();

private:
	static ServiceLocator* s_Instance;

	Renderer* m_Renderer;
	VertexBufferManager* m_VertexBuferManager;
	ShaderProgramManager* m_ShaderProgramManager;
	TextureManager* m_TextureManager;
	InputManager* m_InputManager;
};

#endif