#ifndef __SHADER_PROGRAM_MANAGER_H__
#define __SHADER_PROGRAM_MANAGER_H__

#include <string>
#include <unordered_map>

class ShaderProgram;

class ShaderProgramManager
{
public:
	ShaderProgramManager();
	ShaderProgramManager(const ShaderProgramManager& other) = delete;
	ShaderProgramManager& operator=(const ShaderProgramManager& other) = delete;
	ShaderProgramManager(ShaderProgramManager&& other) = delete;
	ShaderProgramManager& operator=(ShaderProgramManager&& other) = delete;
	~ShaderProgramManager();

	ShaderProgram* GetShaderProgram(const std::string& vertex_file_path, const std::string& fragment_file_path);

private:
	std::unordered_map<std::string, ShaderProgram*> m_ShaderPrograms;
};

#endif