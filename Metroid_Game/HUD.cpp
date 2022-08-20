#include "pch.h"
#include "HUD.h"
#include "Texture.h"
#include "TextureManager.h"
#include "Player.h"

HUD::HUD()
	: m_pScoreTexture{ nullptr }
	, m_pHUDTexture{ nullptr }
	, m_Score{ 0 }
	, m_StringText{ "00" }
{
	m_pScoreTexture = TextureManager::GetInstance().CreateFontTexture(m_StringText); 
	m_pHUDTexture = TextureManager::GetInstance().CreateTexture("HUD");
}

void HUD::Draw(const float& Xpos, const float& Ypos) const
{
	m_pScoreTexture->Draw(Point2f(Xpos + m_pHUDTexture->GetWidth(), Ypos));
	m_pHUDTexture->Draw(Point2f(Xpos, Ypos));

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
