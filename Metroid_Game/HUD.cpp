#include "pch.h"
#include "HUD.h"
#include "Texture.h"
#include "Player.h"

HUD::HUD()
	: m_FontSize{ 22 }
	, m_FontColor{ 1.f, 1.f, 1.f, 1.f }
	, m_StringText{"EN..00"}
	, m_pTexture{nullptr}
	, m_Ypos{}
{
	m_pTexture = new Texture(m_StringText, "Resources/Fonts/nintendo-nes-font.otf", m_FontSize, m_FontColor);
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

void HUD::Update(float elapsedSec)
{
	UpdateScore();
}

void HUD::UpdateScore()
{
	if (Player::m_Score <= 9)
	{
		m_StringText.pop_back();
	}
	else
	{
		m_StringText.pop_back();
		m_StringText.pop_back();
	}
	m_StringText.append(std::to_string(Player::m_Score));
}
