#include "ShaderProgram.h"
#include "ShaderProgramManager.h"

ShaderProgramManager::ShaderProgramManager()
{

}

ShaderProgramManager::~ShaderProgramManager()
{
	for (auto& entry : m_ShaderPrograms)
	{
		delete entry.second;
	}
}

ShaderProgram* ShaderProgramManager::GetShaderProgram(const std::string& vertex_file_path, const std::string& fragment_file_path)
{
	std::string name = vertex_file_path + fragment_file_path;

	auto lower_bound = m_ShaderPrograms.lower_bound(name);

	if (lower_bound != m_ShaderPrograms.end() && !(m_ShaderPrograms.key_comp()(name, lower_bound->first)))
	{
		return lower_bound->second;
	}
	else
	{
		ShaderProgram* shaderProgram = new ShaderProgram(vertex_file_path, fragment_file_path);
		m_ShaderPrograms.insert(lower_bound, { name, shaderProgram });
		return shaderProgram;
	}
}