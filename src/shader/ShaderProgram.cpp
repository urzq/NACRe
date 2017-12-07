#include <assert.h>
#include <vector>
#include <string>

#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string& vertex_file_path, const std::string& fragment_file_path)
{
	Shader vertexShader(GL_VERTEX_SHADER, vertex_file_path);
	Shader fragmentShader(GL_FRAGMENT_SHADER, fragment_file_path);

	m_ProgramID = glCreateProgram();
	glAttachShader(m_ProgramID, vertexShader.GetShaderID());
	glAttachShader(m_ProgramID, fragmentShader.GetShaderID());
	glLinkProgram(m_ProgramID);

	GLint result = GL_FALSE;
	int infoLogLength;

	// Check the program
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
	
	if (infoLogLength > 0) 
	{
		std::vector<char> errorMessage(infoLogLength + 1);
		glGetProgramInfoLog(m_ProgramID, infoLogLength, NULL, &errorMessage[0]);
		
		throw std::string(errorMessage.begin(), errorMessage.end());
	}

	glDetachShader(m_ProgramID, vertexShader.GetShaderID());
	glDetachShader(m_ProgramID, fragmentShader.GetShaderID());

	m_ModelLoc = glGetUniformLocation(m_ProgramID, "model");
	assert(m_ModelLoc != -1);

	m_ViewLoc = glGetUniformLocation(m_ProgramID, "view");
	assert(m_ViewLoc != -1);

	m_ProjectionLoc = glGetUniformLocation(m_ProgramID, "projection");
	assert(m_ProjectionLoc != -1);

	m_ObjectColorLoc = glGetUniformLocation(m_ProgramID, "objectColor");

	// Use the shader before setting uniforms!
	Use(); 

	// Tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	glUniform1i(GetUniformLocation("texture0"), 0);
	glUniform1i(GetUniformLocation("texture1"), 1);
	glUniform1i(GetUniformLocation("texture2"), 2);
	glUniform1i(GetUniformLocation("texture3"), 3);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ProgramID);
}

void ShaderProgram::Use()
{
	glUseProgram(m_ProgramID);
}

void ShaderProgram::Disable()
{
	glUseProgram(0);
}

GLint ShaderProgram::GetUniformLocation(const std::string& name)
{
	auto lower_bound = m_UniformLocations.lower_bound(name);

	if (lower_bound != m_UniformLocations.end() && !(m_UniformLocations.key_comp()(name, lower_bound->first)))
	{
		return lower_bound->second;
	}
	else
	{
		GLint uniform = glGetUniformLocation(m_ProgramID, name.c_str());
		m_UniformLocations.insert(lower_bound, { name, uniform });
		return uniform;
	}
}

void ShaderProgram::SetModel(const glm::mat4& model)
{
	glUniformMatrix4fv(m_ModelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void ShaderProgram::SetView(const glm::mat4& view)
{
	glUniformMatrix4fv(m_ViewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void ShaderProgram::SetProjection(const glm::mat4& projection)
{
	glUniformMatrix4fv(m_ProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void ShaderProgram::SetColor(const glm::vec3& color)
{
	glUniform3f(m_ObjectColorLoc, color.x, color.y, color.z);
}
