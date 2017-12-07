#include "Graphics/Renderer.h"
#include "VertexBuffer/VertexBufferManager.h"
#include "Shader/ShaderProgramManager.h"
#include "Texture/TextureManager.h"
#include "Input/InputManager.h"
#include "ServiceLocator.h"

ServiceLocator* ServiceLocator::s_Instance = nullptr;

void ServiceLocator::Init()
{
	s_Instance = new ServiceLocator();
}

void ServiceLocator::Shutdown()
{
	delete s_Instance;
	s_Instance = nullptr;
}

ServiceLocator* ServiceLocator::GetInstance()
{
	return s_Instance;
}

ServiceLocator::ServiceLocator()
{
	m_Renderer = new Renderer();
	m_VertexBuferManager = new VertexBufferManager();
	m_ShaderProgramManager = new ShaderProgramManager();
	m_TextureManager = new TextureManager();
	m_InputManager = new InputManager();
}

ServiceLocator::~ServiceLocator()
{
	delete m_Renderer;
	delete m_VertexBuferManager;
	delete m_ShaderProgramManager;
	delete m_TextureManager;
	delete m_InputManager;
}

Renderer* ServiceLocator::GetRenderer()
{
	return m_Renderer;
}

VertexBufferManager* ServiceLocator::GetVertexBufferManager()
{
	return m_VertexBuferManager;
}

ShaderProgramManager* ServiceLocator::GetShaderProgramManager()
{
	return m_ShaderProgramManager;
}

TextureManager* ServiceLocator::GetTextureManager()
{
	return m_TextureManager;
}

InputManager* ServiceLocator::GetInputManager()
{
	return m_InputManager;
}