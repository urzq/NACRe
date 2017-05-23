#ifndef __SERVICE_LOCATOR_H__
#define __SERVICE_LOCATOR_H__

class Renderer;
class VertexBufferManager;
class ShaderProgramManager;
class InputManager;

class ServiceLocator
{
public:
	static void Init();
	static void Shutdown();

	static ServiceLocator* GetInstance();

	Renderer* GetRenderer();
	VertexBufferManager* GetVertexBuferManager();
	ShaderProgramManager* GetShaderProgramManager();
	InputManager* GetInputManager();

private:
	ServiceLocator();
	ServiceLocator(const ServiceLocator& other) = delete;
	ServiceLocator& operator=(const ServiceLocator& other) = delete;
	ServiceLocator(ServiceLocator&& other) = delete;
	ServiceLocator& operator=(ServiceLocator&& other) = delete;
	~ServiceLocator();

private:
	static ServiceLocator* s_Instance;

	Renderer* m_Renderer;
	VertexBufferManager* m_VertexBuferManager;
	ShaderProgramManager* m_ShaderProgramManager;
	InputManager* m_InputManager;
};

#endif