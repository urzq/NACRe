#include "GLTexture.h"
#include "TextureManager.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	for (auto& entry : m_Textures)
	{
		delete entry.second;
	}
}

GLTexture* TextureManager::GetTexture(const std::string& path)
{
	auto lower_bound = m_Textures.lower_bound(path);

	if (lower_bound != m_Textures.end() && !(m_Textures.key_comp()(path, lower_bound->first)))
	{
		return lower_bound->second;
	}
	else
	{
		auto texture = new GLTexture(path);
		m_Textures.insert(lower_bound, { path, texture });
		return texture;
	}
}