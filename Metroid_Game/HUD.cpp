#include "pch.h"
#include "HUD.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Player.h"

HUD::HUD()
	: m_FontSize{ 24 }
	, m_ColorScore{ 1.f, 1.f, 1.f, 1.f }
	, m_ColorBlue{ 0.f, 0.f, 1.f, 1.f }
	, m_ColorOrange{ 1.f, 0.64f, 0.f, 1.f }
	, m_pScoreTexture{ nullptr }
	, m_pENTexture{ nullptr }
	, m_pDotTexture{ nullptr }
	, m_Score{ 0 }
	, m_StringText{ "00" }
{
	m_pScoreTexture = TextureManager::GetInstance().CreateFontTexture(m_StringText); 
	m_pENTexture = TextureManager::GetInstance().CreateFontTexture("EN", m_ColorBlue);
	m_pDotTexture = TextureManager::GetInstance().CreateFontTexture("..", m_ColorOrange);
}

void HUD::Draw(const float& Xpos, const float& Ypos) const
{
	m_pScoreTexture->Draw(Point2f(Xpos, Ypos));
	m_pDotTexture->Draw(Point2f(Xpos - 50, Ypos));
	m_pENTexture->Draw(Point2f(Xpos - 100, Ypos));
}

void HUD::UpdateScore(const int& score)
{
	m_Score += score;

	std::string scoreText = std::to_string(m_Score);

	if (score < 10)
	{
		scoreText = "0" + scoreText;
	}
	m_StringText = "" + scoreText;

	//delete m_pScoreTexture;
	//m_pScoreTexture = nullptr;
	m_pScoreTexture = TextureManager::GetInstance().Replace(m_StringText);

}
