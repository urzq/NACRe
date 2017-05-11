#include "Renderer.h"

#include "mesh/VertexBufferManager.h"
#include "shader/ShaderProgramManager.h"

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
}

ServiceLocator::~ServiceLocator()
{
	delete m_Renderer;
	delete m_VertexBuferManager;
	delete m_ShaderProgramManager;
}

Renderer* ServiceLocator::GetRenderer()
{
	return m_Renderer;
}

VertexBufferManager* ServiceLocator::GetVertexBuferManager()
{
	return m_VertexBuferManager;
}

ShaderProgramManager* ServiceLocator::GetShaderProgramManager()
{
	return m_ShaderProgramManager;
}
