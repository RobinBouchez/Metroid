#pragma once
#include <map>

class Texture;

class TextureManager final
{
public:
	TextureManager(const std::string& texture);
	virtual ~TextureManager();
	
	void Draw(const Point2f& destBottomLeft, const Rectf& sourceRect) const;
	void Draw(const Rectf& destRect, const Rectf& sourceRect) const;

	const float GetWidth(const std::string& filename);
	const float GetHeight(const std::string& filename);

	void CreateTexture(const std::string& filename);

protected:
	
	Texture* GetTexture(const std::string& filename);

private:
	std::map<const std::string, Texture*> m_TextureMap;

	const std::string m_TextureFilename;

	void DeleteTextures();
};

