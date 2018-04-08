#include <stdexcept>  

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION

#include <stb/stb_image.h>

#include "GLTexture.h"

GLTexture::GLTexture(const std::string& path)
{
	glGenTextures(1, &m_TextureID);
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

	// set texture wrapping to GL_REPEAT (default wrapping method) S, T = U, V. 
	// The GL_REPEAT mode has textures repeat when you go past (0,0) to (1,1) range
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	// When MINifying the image, use a LINEAR filtering		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// When MAGnifying the image use a LINEAR filtering		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// tell stb_image.h to flip loaded texture's on the y-axis.
	stbi_set_flip_vertically_on_load(true); 

	// load image.
	unsigned char *data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_NbChannels, 0);

	if (data == nullptr)
	{
		// TODO: create an in memory texture instead, with a debug color (pink).
		throw new std::exception("Failed to load texture");
	}
	
	// create texture 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}


GLTexture::~GLTexture()
{
	glDeleteTextures(1, &m_TextureID);
}

GLuint GLTexture::GetTextureID() const
{
	return m_TextureID;
}
