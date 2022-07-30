#pragma once
class map;
class Texture;

class TextureManager
{
public:
	TextureManager();
	virtual ~TextureManager();
	
	void Draw() const;

	Texture* GetTexture(const std::string& filename);
	void CreateTexture(const std::string& filename);


private:
	std::map<const std::string, Texture*> m_TextureMap;
	const std::string m_TextureFilename;
	void DeleteTextures();
};

