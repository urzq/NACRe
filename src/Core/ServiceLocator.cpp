#include "Core/Memory.h"
#include "Graphics/Renderer.h"
#include "VertexBuffer/VertexBufferManager.h"
#include "Shader/ShaderProgramManager.h"
#include "Texture/TextureManager.h"
#include "Input/InputManager.h"
#include "ServiceLocator.h"

using namespace Memory;

Renderer* ServiceLocator::s_Renderer;
VertexBufferManager* ServiceLocator::s_VertexBuferManager;
ShaderProgramManager* ServiceLocator::s_ShaderProgramManager;
TextureManager* ServiceLocator::s_TextureManager;
InputManager* ServiceLocator::s_InputManager;

void ServiceLocator::Init()
{
	safe_new<Renderer>(s_Renderer);
	safe_new<VertexBufferManager>(s_VertexBuferManager);
	safe_new<ShaderProgramManager>(s_ShaderProgramManager);
	safe_new<TextureManager>(s_TextureManager);
	safe_new<InputManager>(s_InputManager);
}

void ServiceLocator::Shutdown()
{
	safe_delete(s_Renderer);
	safe_delete(s_VertexBuferManager);
	safe_delete(s_ShaderProgramManager);
	safe_delete(s_TextureManager);
	safe_delete(s_InputManager);
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