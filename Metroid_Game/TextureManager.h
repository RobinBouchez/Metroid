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
	void Cleanup();
	
protected:
	void Draw(const Point2f& destBottomLeft, const Rectf& sourceRect) const;
	void Draw(const Rectf& destRect, const Rectf& sourceRect) const;

private:
	std::map<const std::string, Texture*> m_TextureMap;

	const std::string m_TextureFilename;
};

