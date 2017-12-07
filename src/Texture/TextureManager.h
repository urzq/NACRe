#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <string>
#include <unordered_map>

class GLTexture;

class TextureManager
{
public:
	TextureManager();
	TextureManager(const TextureManager& other) = delete;
	TextureManager& operator=(const TextureManager& other) = delete;
	TextureManager(TextureManager&& other) = delete;
	TextureManager& operator=(TextureManager&& other) = delete;

	~TextureManager();

	GLTexture* GetTexture(const std::string& path);

private:
	std::unordered_map<std::string, GLTexture*> m_Textures;
};

#endif