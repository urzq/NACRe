#include "Graphics/Renderer.h"
#include "VertexBuffer/VertexBufferManager.h"
#include "Shader/ShaderProgramManager.h"
#include "Texture/TextureManager.h"
#include "Input/InputManager.h"
#include "ServiceLocator.h"

Renderer* ServiceLocator::s_Renderer;
VertexBufferManager* ServiceLocator::s_VertexBuferManager;
ShaderProgramManager* ServiceLocator::s_ShaderProgramManager;
TextureManager* ServiceLocator::s_TextureManager;
InputManager* ServiceLocator::s_InputManager;

void ServiceLocator::Init()
{
	s_Renderer = new Renderer();
	s_VertexBuferManager = new VertexBufferManager();
	s_ShaderProgramManager = new ShaderProgramManager();
	s_TextureManager = new TextureManager();
	s_InputManager = new InputManager();
}

void ServiceLocator::Shutdown()
{
	delete s_Renderer;
	delete s_VertexBuferManager;
	delete s_ShaderProgramManager;
	delete s_TextureManager;
	delete s_InputManager;
}

template<>
Renderer* ServiceLocator::Get<Renderer>()
{
	return s_Renderer;
}

template<>
VertexBufferManager* ServiceLocator::Get<VertexBufferManager>()
{
	return s_VertexBuferManager;
}

template<>
ShaderProgramManager* ServiceLocator::Get<ShaderProgramManager>()
{
	return s_ShaderProgramManager;
}

template<>
TextureManager* ServiceLocator::Get<TextureManager>()
{
	return s_TextureManager;
}

template<>
InputManager* ServiceLocator::Get<InputManager>()
{
	return s_InputManager;
}