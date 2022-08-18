#pragma once
#include <map>
#include "Manager.h"

class Texture;
class TextureManager final : public Manager<TextureManager>
{
public:
	TextureManager() = default;
	~TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;

	Texture* CreateTexture(const std::string& filename);
	Texture* CreateFontTexture(const std::string& name, const Color4f& color = Color4f{ 1.f, 1.f, 1.f, 1.f }, const int& size = 24);
	Texture* Replace(const std::string& filename);

	void Cleanup();
	
protected:
	void Draw(const Point2f& destBottomLeft, const Rectf& sourceRect) const;
	void Draw(const Rectf& destRect, const Rectf& sourceRect) const;

private:
	std::map<const std::string, Texture*> m_TextureMap;

	const std::string m_TextureFilename;
};

