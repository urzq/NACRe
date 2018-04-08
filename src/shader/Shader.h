#ifndef __SHADER_H__
#define __SHADER_H__

#include <string>
#include <glad/glad.h>

//GL_FRAGMENT_SHADER
//GL_VERTEX_SHADER

class Shader
{
public:
	Shader(int shaderType, const std::string& filename);
	~Shader();

	GLuint GetShaderID() const;

private:
	std::string GetShaderCode(const std::string& filename) const;
	void CompileShaderCode(const std::string& shaderCode) const;

private:
	GLuint m_ShaderID;
	int m_ShaderType;
};

#endif