#ifndef __GL_TEXTURE_H__
#define __GL_TEXTURE_H__

#include <string>
#include <glad/glad.h>

class GLTexture
{
public:
	GLTexture(const std::string& path);
	GLTexture(const GLTexture& other) = delete;
	GLTexture& operator=(const GLTexture& other) = delete;
	GLTexture(GLTexture&& other) = delete;
	GLTexture& operator=(GLTexture&& other) = delete;
	
	~GLTexture();

	GLuint GetTextureID() const;

private:
	int m_Width;
	int m_Height;
	int m_NbChannels;

	GLuint m_TextureID;
};

#endif