#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"

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

Texture* TextureManager::CreateTexture(const std::string& filename)
{
	if(m_TextureMap.find(filename) == m_TextureMap.end())
	{
		m_TextureMap.emplace(filename, new Texture("Resources/" + filename + ".png"));
	}
	return m_TextureMap[filename];
}

void TextureManager::Cleanup()
{
	for (auto& e : m_TextureMap)
	{
		delete e.second;
		e.second = nullptr;
	}
}
