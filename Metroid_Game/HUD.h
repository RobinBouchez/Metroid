#pragma once
#include "Manager.h"

class Texture;

class HUD final : public Manager<HUD>
{
public:
	HUD();
	~HUD() = default;

	void Draw(const float& pos, const float &Ypos) const;
	void UpdateScore(const int& score);

private:
	std::string m_StringText;

	//TEXTURES
	Texture* m_pScoreTexture;
	Texture* m_pENTexture;
	Texture* m_pDotTexture;

	//COLORS
	const Color4f m_ColorScore;
	const Color4f m_ColorBlue;
	const Color4f m_ColorOrange;


	const int m_FontSize;

	int m_Score;
};

