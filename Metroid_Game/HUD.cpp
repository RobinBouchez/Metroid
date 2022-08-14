#include "pch.h"
#include "HUD.h"
#include "Texture.h"
#include "Player.h"

HUD::HUD()
	: m_FontSize{ 22 }
	, m_ColorScore{ 1.f, 1.f, 1.f, 1.f }
	, m_ColorLang{ 0.f, 0.f, 1.f, 1.f }
	, m_Ypos{}
	, m_pTexture{nullptr}
	, m_Score{ 0 }
	, m_StringText{ "EN..00" }
{
	m_pTexture = new Texture(m_StringText, "Resources/Fonts/nintendo-nes-font.otf", m_FontSize, m_ColorScore);
}

HUD::~HUD()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void HUD::Draw(float& Xpos, float& Ypos) const
{
	m_pTexture->Draw(Point2f(Xpos, Ypos));
}

void HUD::UpdateScore(int score)
{
	m_Score += score;

	std::string scoreText = std::to_string(m_Score);

	if (score < 10)
	{
		scoreText = "0" + scoreText;
	}
	m_StringText = "EN.." + scoreText;

	delete m_pTexture;
	m_pTexture = new Texture(m_StringText, "Resources/Fonts/nintendo-nes-font.otf", m_FontSize, m_ColorScore);

}
