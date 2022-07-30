#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"

TextureManager::TextureManager(const std::string& texture)
	: m_TextureFilename{ texture }
	, m_TextureMap{}
{
}

TextureManager::~TextureManager()
{
	DeleteTextures();
}

void TextureManager::Draw(const Point2f& destBottomLeft, const Rectf& sourceRect) const
{
	for (std::pair<std::string, Texture*> elements : m_TextureMap)
	{
		elements.second->Draw(destBottomLeft, sourceRect);
	}
}

void TextureManager::Draw(const Rectf& destRect, const Rectf& sourceRect) const
{
	for (std::pair<std::string, Texture*> elements : m_TextureMap)
	{
		elements.second->Draw(destRect, sourceRect);
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

const float TextureManager::GetWidth(const std::string& filename)
{
	return m_TextureMap[filename]->GetWidth();
}

const float TextureManager::GetHeight(const std::string& filename) 
{
	return m_TextureMap[filename]->GetHeight();
}

void TextureManager::DeleteTextures()
{
	for (std::pair<std::string, Texture*> e : m_TextureMap)
	{
		delete e.second;
		e.second = nullptr;
	}
}
