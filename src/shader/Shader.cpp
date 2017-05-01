#include <vector>
#include <string>
#include <fstream>
#include <exception>

#include "Shader.h"

Shader::Shader(int shaderType, const char* filename)
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

std::string Shader::GetShaderCode(const char* c_filename) const
{
	std::string filename = std::string("data/shader/") + c_filename;
	std::ifstream shaderStream(filename, std::ios::in);

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

void Shader::CompileShaderCode(const char* shaderCode) const
{
	GLint result = GL_FALSE;
	int infoLogLength;

	char const * codePointer = shaderCode;
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