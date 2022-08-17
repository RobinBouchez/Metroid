#include "pch.h"
#include "HUD.h"
#include "Texture.h"
#include "Player.h"

HUD::HUD()
	: m_FontSize{ 22 }
	, m_ColorScore{ 1.f, 1.f, 1.f, 1.f }
	, m_ColorLang{ 0.f, 0.f, 1.f, 1.f }
	, m_Ypos{}
	, m_pMainTexture{nullptr}
	, m_pENTexture{ nullptr }
	, m_Score{ 0 }
	, m_StringText{ "00" }
{
	m_pMainTexture = new Texture(m_StringText, "Resources/Fonts/nintendo-nes-font.otf", m_FontSize, m_ColorScore);
	m_pENTexture = new Texture("EN", "Resources/Fonts/nintendo-nes-font.otf", m_FontSize, m_ColorLang);
}

HUD::~HUD()
{
	delete m_pMainTexture;
	m_pMainTexture = nullptr;

	delete m_pENTexture;
	m_pENTexture = nullptr;
}

void HUD::Draw(float& Xpos, float& Ypos) const
{
	m_pMainTexture->Draw(Point2f(Xpos, Ypos));
	m_pENTexture->Draw(Point2f(Xpos - 50, Ypos));
}

void HUD::UpdateScore(int score)
{
	m_Score += score;

	std::string scoreText = std::to_string(m_Score);

	if (score < 10)
	{
		scoreText = "0" + scoreText;
	}
	m_StringText = "" + scoreText;

	delete m_pMainTexture;
	m_pMainTexture = new Texture(m_StringText, "Resources/Fonts/nintendo-nes-font.otf", m_FontSize, m_ColorScore);

}
