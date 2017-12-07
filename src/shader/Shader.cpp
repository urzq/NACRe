#include <vector>
#include <string>
#include <fstream>
#include <exception>

#include "Shader.h"

Shader::Shader(int shaderType, const std::string& filename)
{
	m_ShaderID = glCreateShader(shaderType);
	
	std::string sourceCode = GetShaderCode(filename);
	CompileShaderCode(sourceCode.c_str());
}

Shader::~Shader()
{
	glDeleteShader(m_ShaderID);
}

GLuint Shader::GetShaderID() const
{
	return m_ShaderID;
}

std::string Shader::GetShaderCode(const std::string& filename) const
{
	// TODO: This confused me. Do I want to have full path in my engine or just filename ?
	std::ifstream shaderStream("data/shader/" + filename, std::ios::in);

	if (! shaderStream.is_open())
	{
		throw "Impossible to open " + std::string(filename);
	}

	std::string shaderCode;
	std::string line = "";
	while (getline(shaderStream, line))
	{
		shaderCode += "\n" + line;
	}

	return shaderCode;
}

void Shader::CompileShaderCode(const std::string& shaderCode) const
{
	GLint result = GL_FALSE;
	int infoLogLength;

	const char* codePointer = shaderCode.c_str();
	glShaderSource(m_ShaderID, 1, &codePointer, NULL);
	glCompileShader(m_ShaderID);

	glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 0)
	{
		char errorMessage[4096];
		glGetShaderInfoLog(m_ShaderID, infoLogLength, NULL, &errorMessage[0]);

		throw std::string(errorMessage);
	}
}