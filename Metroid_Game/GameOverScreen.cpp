#include "pch.h"
#include "GameOverScreen.h"
#include "Texture.h"
#include "TextureManager.h"

GameOverScreen::GameOverScreen(const Point2f& position, const Window& window) : Screen(position, window)
	, m_pTexture{ nullptr }
{
	m_pTexture = TextureManager::GetInstance().CreateTexture("GameOver");
}

void GameOverScreen::Draw() const
{
	//Screen::Draw();
	m_pTexture->Draw(m_ScreenPos, GetBoundaries());
}

void GameOverScreen::Update(float elapsedSec)
{
	//Screen::Update(elapsedSec);
}
