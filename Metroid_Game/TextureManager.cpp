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

Texture* TextureManager::CreateFontTexture(const std::string& name, const Color4f& color, const int& size)
{
	if (m_TextureMap.find(name) == m_TextureMap.end())
	{
		m_TextureMap.emplace(name, new Texture(name, "Resources/Fonts/nintendo-nes-font.otf", size, color));
	}
	return m_TextureMap[name];
}

Texture* TextureManager::Replace(const std::string& filename)
{
	if (!m_TextureMap.empty())
	{
		m_TextureMap.erase(filename);

		CreateFontTexture(filename);
		return m_TextureMap[filename];
	}
	return nullptr;
}

void TextureManager::Cleanup()
{
	if (!m_TextureMap.empty())
	{
		for (auto& e : m_TextureMap)
		{
			delete e.second;
			e.second = nullptr;
		}
		m_TextureMap.clear();
	}
}
