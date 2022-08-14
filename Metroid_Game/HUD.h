#pragma once
#include "Manager.h"

class Texture;

class HUD final : public Manager<HUD>
{
public:
	HUD();
	~HUD();

	void Draw(float& pos, float &Ypos) const;

	void UpdateScore(int score);

private:
	std::string m_StringText;

	//Data members
	Texture* m_pTexture;
	const int m_FontSize;
	const Color4f m_ColorScore;
	const Color4f m_ColorLang;
	const float m_Ypos;

	int m_Score;
};

