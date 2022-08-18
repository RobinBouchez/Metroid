#include "pch.h"
#include "GameOverScreen.h"
#include "Texture.h"
#include "TextureManager.h"

GameOverScreen::GameOverScreen(const Point2f& position) : Screen(position)
	, m_pTexture{ nullptr }
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("GameOver");
}

void GameOverScreen::Draw() const
{
	m_pTexture->Draw(m_ScreenPos);
}
