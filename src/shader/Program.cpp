#include <vector>
#include <string>

#include "Program.h"
#include "Shader.h"

Program::Program(const char* vertex_file_path, const char* fragment_file_path)
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
}

Program::~Program()
{
	glDeleteProgram(m_ProgramID);
}

void Program::Use()
{
	glUseProgram(m_ProgramID);
}

void Program::Disable()
{
	glUseProgram(0);
}

GLuint Program::GetUniformLocation(const char* name) const
{
	return glGetUniformLocation(m_ProgramID, name);
}
