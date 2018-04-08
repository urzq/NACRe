#ifndef __SHADER_PROGRAM_H__
#define __SHADER_PROGRAM_H__

#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertex_file_path, const std::string& fragment_file_path);
	~ShaderProgram();

	void Use();
	void Disable();

	// TODO: use an optimized string (hashed ? view ?)
	GLint GetUniformLocation(const std::string& name);

	void SetModel(const glm::mat4& model);
	void SetView(const glm::mat4& view);
	void SetProjection(const glm::mat4& projection);
	void SetColor(const glm::vec3& color);

private:
	GLuint m_ProgramID;
	
	// Mandatory uniforms
	GLint m_ModelLoc;
	GLint m_ViewLoc;
	GLint m_ProjectionLoc;

	// Probably here, but not mandatory.
	GLint m_ObjectColorLoc;

	// All others "exotic" uniforms that may appear in the shader.
	std::unordered_map<std::string, GLint> m_UniformLocations;
};

#endif