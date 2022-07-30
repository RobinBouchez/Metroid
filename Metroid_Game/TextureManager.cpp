#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"
#include <map>


TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	DeleteTextures();
}

void TextureManager::Draw() const
{
	for (std::pair<std::string, Texture*> elements : m_TextureMap)
	{
		elements.second->Draw();
	}
}

Texture* TextureManager::GetTexture(const std::string& filename)
{
	return m_TextureMap.at(filename);
}

void TextureManager::CreateTexture(const std::string& filename)
{
	m_TextureMap[filename] = new Texture("Resources/" + filename + ".png");
}

void TextureManager::DeleteTextures()
{
	for (std::pair<std::string, Texture*> e : m_TextureMap)
	{
		delete e.second;
		e.second = nullptr;
	}
}
